#pragma once
#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>
#include <codecvt>
#include "structures.h"
#ifdef  TheColdWorldConfigEditer_Windows_Dll
#define TheColdWorldConfigEditer_Windows_Dll_Api __declspec(dllexport) 
#else
#define TheColdWorldConfigEditer_Windows_Dll_Api __declspec(dllimport) 
#endif // ! TheColdWorldConfigEditer_Windows_Dll

TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileAllLines(const wchar_t* FilePath, std::vector<std::wstring>& OutArray, int32& ArrayLength);
TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileAllLines(const wchar_t* FilePath, std::vector<std::wstring>& OutArray, int64& ArrayLength);
TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileAllLines(const wchar_t* FilePath, std::vector<std::wstring>& OutArray, int16& ArrayLength);
TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileAllHeadersList(const wchar_t* FilePath, std::vector<std::wstring>& Headers);
TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileAllKeys_Value(const wchar_t* FilePath, const wchar_t* Header, std::vector<std::wstring>& Keys_Values);
TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileAllKeyList(const wchar_t* FilePath, const wchar_t* Header, std::vector<std::wstring>& KeyList);
TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileValue(const std::vector<std::wstring> Keys, const wchar_t* Key, std::wstring& Value);
TheColdWorldConfigEditer_Windows_Dll_Api int32 GetFileValue(const wchar_t* FilePath, const wchar_t* Header, const wchar_t* Key, std::wstring& Value);