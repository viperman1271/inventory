#include <libsnap/session.h>

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#include <sstream>

session::session(const unsigned int in_userId) 
    : m_UserId(in_userId)
{
    const uint64_t timeSinceEpoch = getSecondsSinceEpoch();
    m_SessionStartTime = timeSinceEpoch;

    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    std::stringstream message;
    message << timeSinceEpoch;

    CryptoPP::SHA256 hash;
    hash.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(message.str().c_str()), message.str().length());

    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(m_SessionKey));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
}

const std::wstring session::serialize() const
{
    json_object* jobj = getJsonObject();
    return getJsonStr(jobj);
}

json_object* session::getJsonObject() const
{
    json_object* jobj = json_object_new_object();
    {
        json_object_object_add(jobj, "UserId", json_object_new_int(m_UserId));
        json_object_object_add(jobj, "SessionKey", json_object_new_string(m_SessionKey.c_str()));
        json_object_object_add(jobj, "SessionStart", json_object_new_int64(m_SessionStartTime));
    }
    return jobj;
}

void session::deserialize(json_object* jobj)
{
    json_object_object_foreach(jobj, key, val)
    {
        json_object* jobjval = json_object_object_get(jobj, key);
        if (strcmp(key, "UserId") == 0)
        {
            m_UserId = json_object_get_int(jobjval);
        }
        else if (strcmp(key, "SessionKey") == 0)
        {
            m_SessionKey = json_object_get_string(jobjval);
        }
        else if (strcmp(key, "SessionStart") == 0)
        {
            m_SessionStartTime = json_object_get_int64(jobjval);
        }
    }
}