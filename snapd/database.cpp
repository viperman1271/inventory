#include "stdafx.h"
#include "database.h"

#include <utilities/fileutilities.h>
#include <utilities/mutexutilities.h>

#include <libsnap/user.h>

#include <cryptopp/config.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <cryptopp/osrng.h>

const unsigned int iterations = 1000;

database::database()
{
    if (!file::utils::fileExists("users.json"))
    {
        writeUsers();
    }

    loadUsers();
}

database::~database()
{

}

bool database::userExists(const user& in_user) const
{
    return getStoredUser(in_user) != nullptr;
}

bool database::addUser(const user& in_user)
{
    auto_lock<std::recursive_mutex> lock(m_Mutex);

    user _user(in_user);

    if (m_Users.empty())
    {
        _user.setUserId(1);
    }
    else
    {
        const unsigned int lastUserId = m_Users.back().getUserId();
        _user.setUserId(lastUserId + 1);
    }

    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::SecByteBlock pwsalt(CryptoPP::SHA256::DIGESTSIZE);
    rng.GenerateBlock(pwsalt, pwsalt.size());

    CryptoPP::SecByteBlock derivedkey(CryptoPP::SHA256::DIGESTSIZE);

    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf;
    pbkdf.DeriveKey(derivedkey
        , derivedkey.size()
        , 0x00
        , reinterpret_cast<const CryptoPP::byte*>(in_user.getPassword().c_str())
        , in_user.getPassword().length()
        , pwsalt
        , pwsalt.size()
        , iterations
    );

    CryptoPP::HexEncoder encoder;

    std::string hexEncodedPassword;
    encoder.Attach(new CryptoPP::StringSink(hexEncodedPassword));
    encoder.Put(derivedkey, derivedkey.size());
    encoder.MessageEnd();

    std::string hexEncodedSalt;
    encoder.Attach(new CryptoPP::StringSink(hexEncodedSalt));
    encoder.Put(pwsalt, pwsalt.size());
    encoder.MessageEnd();

    _user.setPasswordHash(hexEncodedPassword);
    _user.setSalt(hexEncodedSalt);

    m_Users.push_back(_user);

    writeUsers();

    return true;
}

bool database::validatePassword(const user& in_user) const
{
    if (!userExists(in_user))
    {
        return false;
    }

    const user* storedUser = getStoredUser(in_user);
    if (storedUser == nullptr)
    {
        return false;
    }

    const std::string& encoded = storedUser->getSalt();
    std::string decoded = decodeString(encoded);

    CryptoPP::SecByteBlock passwordSalt(reinterpret_cast<const CryptoPP::byte*>(decoded.c_str()), decoded.size());

    std::string encodedPassword = hashAndEncodePassword(in_user.getPassword(), passwordSalt);

    return encodedPassword == storedUser->getPassword();
}

void database::writeUsers()
{
    auto_lock<std::recursive_mutex> lock(m_Mutex);

    json_object* jobj = json_object_new_object();
    json_object* jarray = json_object_new_array();
    {
        for (const user& _user : m_Users)
        {
            json_object_array_add(jarray, _user.getJsonObject());
        }
    }
    json_object_object_add(jobj, "Users", jarray);

    const char* jsonString = json_object_to_json_string(jobj);

    m_UsersFile = std::ofstream("users.json");
    m_UsersFile.write(jsonString, strlen(jsonString));
    m_UsersFile.close();
}

void database::loadUsers()
{
    std::ifstream usersFile = std::ifstream("users.json");
    usersFile.seekg(0, std::ios::end);
    const size_t size = usersFile.tellg();

    usersFile.seekg(0, std::ios::beg);

    std::unique_ptr<char> fileBuffer(new char[size + 1]);
    memset(fileBuffer.get(), 0, size + 1);
    usersFile.read(reinterpret_cast<char*>(fileBuffer.get()), size);


    json_object* jobj = json_tokener_parse(fileBuffer.get());
    json_object_object_foreach(jobj, key, val)
    {
        json_object* jarray = json_object_object_get(jobj, key);
        json_type type = json_object_get_type(val);

        assert(type == json_type_array);
        const size_t arraylen = json_object_array_length(jarray);

        for (unsigned int i = 0; i < arraylen; ++i)
        {
            json_object* userValue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
            user _user;
            _user.deserialize(userValue);
            m_Users.push_back(_user);
        }
    }
}

void database::loadSessions()
{

}

std::string database::hashAndEncodePassword(const std::string& in_plainTextPassword, const CryptoPP::SecByteBlock& in_passwordSalt) const
{
    CryptoPP::SecByteBlock derivedkey(CryptoPP::SHA256::DIGESTSIZE);

    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf;
    pbkdf.DeriveKey(derivedkey
        , derivedkey.size()
        , 0x00
        , reinterpret_cast<const CryptoPP::byte*>(in_plainTextPassword.c_str())
        , in_plainTextPassword.length()
        , in_passwordSalt
        , in_passwordSalt.size()
        , iterations
    );

    return encodeString(derivedkey);
}

std::string database::encodeString(const CryptoPP::SecByteBlock& in_textToEncode) const
{
    CryptoPP::HexEncoder encoder;

    std::string hexEncodedPassword;
    encoder.Attach(new CryptoPP::StringSink(hexEncodedPassword));
    encoder.Put(in_textToEncode, in_textToEncode.size());
    encoder.MessageEnd();

    return hexEncodedPassword;
}

std::string database::decodeString(const std::string& in_encodedString) const
{
    std::string decoded;

    CryptoPP::HexDecoder decoder;
    decoder.Put((CryptoPP::byte*)in_encodedString.data(), in_encodedString.size());
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if (size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        decoder.Get((CryptoPP::byte*)&decoded[0], decoded.size());
    }

    return decoded;
}

const user* database::getStoredUser(const user& in_user) const
{
    auto_lock<std::recursive_mutex> lock(m_Mutex);

    for (const user& _user : m_Users)
    {
        if (_user == in_user)
        {
            return &_user;
        }
    }

    return nullptr;
}
