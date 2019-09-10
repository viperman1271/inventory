#include <libsnap/object.h>

bool object::deserializeFromFile(object* instance, const std::string& file)
{
    std::ifstream sessionFile = std::ifstream(file);
    if (!sessionFile.is_open() || instance == nullptr)
    {
        return false;
    }
    sessionFile.seekg(0, std::ios::end);
    const size_t size = sessionFile.tellg();

    sessionFile.seekg(0, std::ios::beg);

    std::unique_ptr<char> fileBuffer(new char[size + 1]);
    memset(fileBuffer.get(), 0, size + 1);
    sessionFile.read(reinterpret_cast<char*>(fileBuffer.get()), size);

    json_object* jobj = json_tokener_parse(fileBuffer.get());
    instance->deserialize(jobj);

    return true;
}

const std::wstring object::getJsonStr(json_object* jobj) const
{
    const char* jsonString = json_object_to_json_string(jobj);
    const size_t length = strlen(jsonString);

    std::unique_ptr<wchar_t> wcharArray = std::unique_ptr<wchar_t>(new wchar_t[length + 1]);
    memset(wcharArray.get(), 0, (length + 1) * sizeof(wchar_t));

    mbstowcs(wcharArray.get(), jsonString, length);
    return std::wstring(wcharArray.get());
}

void object::deserialize(object* instance, const std::wstring& data)
{
    std::unique_ptr<char> pszData(new char[data.size() + 1]);
    wcstombs(pszData.get(), data.c_str(), data.size() + 1);
    instance->deserialize(pszData.get());
}
