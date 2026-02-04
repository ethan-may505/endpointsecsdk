#define _CRT_SECURE_NO_WARNINGS
#include "OesisUtils.h"

wstring OesisUtils::ReadFileContentIntoWString(const wstring& filename)
{
#ifdef _WIN32
    wstring buffer;            // stores file contents
    FILE* file = _wfopen(filename.c_str(), L"rtS, ccs=UTF-8");
    HRESULT r = GetLastError();
    // Failed to open file
    if (file == NULL)
    {
        // ...handle some error...
        return buffer;
    }
    size_t filesize = GetSizeOfFile(filename);
    // Read entire file contents in to memory
    if (filesize > 0)
    {
        buffer.resize(filesize);
        size_t wchars_read = fread(&(buffer.front()), sizeof(wchar_t), filesize, file);
        buffer.resize(wchars_read);
        buffer.shrink_to_fit();
    }
    fclose(file);
    return buffer;

#else
    ifstream inputFile;
    string content = "";
    string tmp;
    string path = utf8_encode(filename);
    inputFile.open(path);
    while(inputFile >> tmp)
    {
        content += tmp;
    }
    inputFile.close();
    return utf8_decode(content);

#endif // 
}
//
wstring OesisUtils::GetCurrentFolderPath()
{
#ifdef _WIN32
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    string::size_type pos = wstring(buffer).find_last_of(L"\\/");
    return wstring(buffer).substr(0, pos);
#else
    char * currentFolder = getcwd(NULL, 0);
    return utf8_decode(currentFolder);
	
#endif // _WIN32
}


#ifdef _WIN32
size_t OesisUtils::GetSizeOfFile(const wstring& path)
{
    struct _stat fileinfo;
    _wstat(path.c_str(), &fileinfo);
    return fileinfo.st_size;
}
#endif // _WIN32



string OesisUtils::WStringToString(wstring wstr)
{
    setlocale(LC_ALL, "");
    const locale locale("");
    typedef codecvt<wchar_t, char, std::mbstate_t> converter_type;
    const converter_type& converter = std::use_facet<converter_type>(locale);
    vector<char> to(wstr.length() * converter.max_length());
    mbstate_t state;
    const wchar_t* from_next;
    char* to_next;
    const converter_type::result result = converter.out(state, wstr.data(), wstr.data() + wstr.length(), from_next, &to[0], &to[0] + to.size(), to_next);
    if (result == converter_type::ok or result == converter_type::noconv) {
        const string s(&to[0], to_next);
        return s;
    }
    return "";
}

wstring OesisUtils::CreateJsonIn(int methodId, string signature_id)
{
    wstring w_input(signature_id.begin(), signature_id.end());
    wstring json_in = L"{\"input\": {\"signature\":" + w_input + L", \"method\" :" + to_wstring(methodId) + L"} }";
    return json_in;
}

bool OesisUtils::CheckJsonKey(json js, string key) {
    if(js.find(key) != js.end()) {
        return true;
    }
    return false;
}
string OesisUtils::utf8_encode(const wstring& wstr){
#ifdef _WIN32
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;

#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    return convert.to_bytes(wstr);
#endif
}

wstring OesisUtils::utf8_decode(const string& str){
#ifdef _WIN32
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    return convert.from_bytes(str);
#endif
}

vector<wstring> OesisUtils::Split(wstring str, wstring special_character)
{
    size_t pos = 0;
    vector<wstring> vector;
    while ((pos = str.find(special_character)) != std::string::npos)
    {
        wstring token = str.substr(0, pos);
        vector.push_back(token);
        str.erase(0, pos + special_character.length());
    }

    if (str.length() > 0)
        vector.push_back(str);
    return vector;
}


int OesisUtils::GetJsonValues(json& result, int rc, wstring json_out, vector<string> keys)
{
    json jsonOut = json::parse(utf8_encode(json_out));
    if (rc < 0)
    {
        result = jsonOut["error"];
        return -1;
    }
    jsonOut = jsonOut["result"];
    if (keys.size() > 0)
    {
        for(string key : keys)
        {
            if (jsonOut.find(key) != jsonOut.end())
            {
                result[key] = jsonOut[key];
            }
        }
    }
    else
    {
        result = jsonOut;
    }
    return 0;
}

bool isNumber(string input)
{
    size_t index;
    size_t length;
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    length = input.length();
    for (index = 0; index < length; index++)
    {
        if (!isdigit(input.at(index)))
            return false;
    }
    return true;
}

bool isBoolean(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    if (input.compare("true") == 0 || input.compare("false") == 0)
        return true;
    else
        return false;
}

bool isIntArray(string input)
{
    stringstream str_steam(input);
    string value;
    while (std::getline(str_steam, value, ',')) {
        if (!isNumber(value)) {
            return false;
        }
    }
    return true;
}

int OesisUtils::CreateJsonIn(wstring& json_in, map<string, string> input)
{

    if (input.find("method") == input.end())
    {
        json_in = L"{ \"input\": { \"method\": -1 } }";
        return -1;
    }
    json_in = L"{\"input\": { \"method\": " +  utf8_decode(input["method"]);
    input.erase("method");
    string value;
    for (std::map<string, string>::iterator it = input.begin(); it != input.end(); ++it)
    {
        json_in = json_in + L", \"" + utf8_decode(it->first) + L"\": ";
        value = it->second;
        if (isBoolean(value) || isNumber(value))
        {
            json_in = json_in +  utf8_decode(value);
        }
        else if(isIntArray(value))
        {
            json_in = json_in + L"[" + utf8_decode(value) + L"]";
        }
        else
        {
            json_in = json_in + L"\"" + utf8_decode(value) + L"\"";
        }
    }
    json_in += L" } }";
    return 0;

}
