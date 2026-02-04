#pragma once

#include "wa_api.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


#ifdef _WIN32
#include <comdef.h>
#include "windows.h"
#else
#include <unistd.h>
#include <codecvt>
#endif // _WIN32




#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class OesisUtils
{
public:
    static wstring CreateJsonIn(int methodId, string signature_id = "");
    static int ParseCommand(int argc, char** argv, wstring& output);
    static bool CheckJsonKey(json js, string key);
    static string WStringToString(wstring wstr);
    static bool ReadFileContentIntoString(const char* sFilePath, string& sContent);
    static size_t GetSizeOfFile(const wstring& path);
    static wstring GetCurrentFolderPath();
    static wstring ReadFileContentIntoWString(const wstring& filename);
    static vector<wstring> Split(wstring str, wstring special_character);
    // Convert a wide Unicode string to an UTF8 string
    static string utf8_encode(const wstring& wstr);
    // Convert an UTF8 string to a wide Unicode String
    static wstring utf8_decode(const string& str);
    static int InvokeMethod(map<wstring, wstring> input, wstring& json_out);
    static int GetJsonValues(json& result, int rc, wstring json_out, vector<string> keys);
    static int CreateJsonIn(wstring& json_in, map<string, string> input);
};
