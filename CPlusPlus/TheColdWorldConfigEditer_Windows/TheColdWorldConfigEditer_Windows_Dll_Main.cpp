#include "pch.h"
#include "TheColdWorldConfigEditer_Windows_Dll_Header.h"
#include "structures.h"
namespace std
{
	inline std::wstring to_wstring(const std::string& input)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(input);
	}
}
int32 GetFileAllLines(const wchar_t* FilePath,std::vector<std::wstring>& OutArray, int32& ArrayLength)
{
	if (_waccess_s(FilePath, 0) != 0) return -1;
	FILE* FileStream = 0;
	_wfopen_s(&FileStream, FilePath, L"r");
	if (FileStream == 0) return -2;
	fseek(FileStream, -1L, 2);
	int32 FileLength = ftell(FileStream);
	int32 Lines = 0;
	rewind(FileStream);
	while (!feof(FileStream))
	{
		char* buf = new char[FileLength];
		fgets(buf, FileLength, FileStream);
		memset(buf, 0, sizeof(char));
		Lines++;
	}
	rewind(FileStream);
	std::vector<std::string> FileInfo;
	for (int32 l = 0; !feof(FileStream); l++)
	{
		char* buf = new char[FileLength];
		fgets(buf, FileLength, FileStream);
		FileInfo.push_back(buf);
		memset(buf, 0, sizeof(char));
	}
	fclose(FileStream);
	for (int32 i = 0; i < FileInfo.size()-1; i++)
	{
		FileInfo[i].replace(FileInfo[i].find_last_of("\n"), sizeof(char), "\0");
	}
	ArrayLength = FileInfo.size();
	if (OutArray.size() != 0)	OutArray.clear();
	for (int32 i = 0; i < FileInfo.size(); i++)
	{
		OutArray.push_back(std::to_wstring(FileInfo[i]));
	}
	memset(FileStream, 0, sizeof(FILE*));
	memset(&FileLength, 0, sizeof(int32));
	memset(&FileInfo, 0, sizeof(std::vector<std::string>));
	memset(&Lines, 0, sizeof(int32));
	return 0;
}
int32 GetFileAllLines(const wchar_t* FilePath, std::vector<std::wstring>& OutArray, int64& ArrayLength)
{
	if (_waccess_s(FilePath, 0) != 0) return -1;
	FILE* FileStream = 0;
	_wfopen_s(&FileStream, FilePath, L"r");
	if (FileStream == 0) return -2;
	fseek(FileStream, -1L, 2);
	int32 FileLength = ftell(FileStream);
	int32 Lines = 0;
	rewind(FileStream);
	while (!feof(FileStream))
	{
		char* buf = new char[FileLength];
		fgets(buf, FileLength, FileStream);
		memset(buf, 0, sizeof(char));
		Lines++;
	}
	rewind(FileStream);
	std::vector<std::string> FileInfo;
	for (int32 l = 0; !feof(FileStream); l++)
	{
		char* buf = new char[FileLength];
		fgets(buf, FileLength, FileStream);
		FileInfo.push_back(buf);
		memset(buf, 0, sizeof(char));
	}
	fclose(FileStream);
	for (int32 i = 0; i < FileInfo.size() - 1; i++)
	{
		FileInfo[i].replace(FileInfo[i].find_last_of("\n"), sizeof(char), "\0");
	}
	ArrayLength = FileInfo.size();
	if (OutArray.size() != 0)	OutArray.clear();
	for (int32 i = 0; i < FileInfo.size(); i++)
	{
		OutArray.push_back(std::to_wstring(FileInfo[i]));
	}
	memset(FileStream, 0, sizeof(FILE*));
	memset(&FileLength, 0, sizeof(int32));
	memset(&FileInfo, 0, sizeof(std::vector<std::string>));
	memset(&Lines, 0, sizeof(int32));
	return 0;
}
int32 GetFileAllLines(const wchar_t* FilePath, std::vector<std::wstring>& OutArray, int16& ArrayLength)
{
	if (_waccess_s(FilePath, 0) != 0) return -1;
	FILE* FileStream = 0;
	_wfopen_s(&FileStream, FilePath, L"r");
	if (FileStream == 0) return -2;
	fseek(FileStream, -1L, 2);
	int32 FileLength = ftell(FileStream);
	int32 Lines = 0;
	rewind(FileStream);
	while (!feof(FileStream))
	{
		char* buf = new char[FileLength];
		fgets(buf, FileLength, FileStream);
		memset(buf, 0, sizeof(char));
		Lines++;
	}
	rewind(FileStream);
	std::vector<std::string> FileInfo;
	for (int32 l = 0; !feof(FileStream); l++)
	{
		char* buf = new char[FileLength];
		fgets(buf, FileLength, FileStream);
		FileInfo.push_back(buf);
		memset(buf, 0, sizeof(char));
	}
	fclose(FileStream);
	for (int32 i = 0; i < FileInfo.size()-1; i++)
	{
		FileInfo[i].replace(FileInfo[i].find_last_of("\n"), sizeof(char), "\0");
	}
	ArrayLength = FileInfo.size();
	if (OutArray.size() != 0)	OutArray.clear();
	for (int32 i = 0; i < FileInfo.size(); i++)
	{
		OutArray.push_back(std::to_wstring(FileInfo[i]));
	}
	memset(FileStream, 0, sizeof(FILE*));
	memset(&FileLength, 0, sizeof(int32));
	memset(&FileInfo, 0, sizeof(std::vector<std::string>));
	memset(&Lines, 0, sizeof(int32));
	return 0;
}
int32 GetFileAllHeadersList(const wchar_t* FilePath, std::vector<std::wstring>& Headers)
{
	if (_waccess_s(FilePath, 0) != 0) return -1;
	int64 FileLines;
	std::vector<std::wstring> FileAllLines;
	int32 Returns = GetFileAllLines(FilePath, FileAllLines, FileLines);
	if (Returns != 0) return Returns;
	memset(&Returns, 0, sizeof(int32));
	if (Headers.size() != 0)	Headers.clear();
	for (int64 i = 0; i < FileLines; i++)
	{
		if (FileAllLines[i][0] == L'/' && FileAllLines[i][1] == L'/')continue;
		if (FileAllLines[i].length() == 0) continue;
		if (FileAllLines[i][FileAllLines[i].length()-1] == L':')
		{
			if (FileAllLines[i + 1] != L"{") continue;
			std::wstring str= FileAllLines[i];
			str.replace(str.find_last_of(L":"), sizeof(L":"), L"");
			Headers.push_back(str);
			memset(&str, 0, sizeof(std::wstring));
		}
	}
	memset(&FileLines, 0, sizeof(int32));
	memset(&FileAllLines, 0, sizeof(std::vector<std::wstring>));
	return 0;
}
int32 GetFileAllKeys_Value(const wchar_t* FilePath, const wchar_t* Header, std::vector<std::wstring>& Keys_Values)
{
	if (_waccess_s(FilePath, 0) != 0) return -1;
	std::vector<std::wstring> HeaderList;
	GetFileAllHeadersList(FilePath, HeaderList);
	bool HaveHeaderAble=false;
	for (int32 i = 0; i < HeaderList.size(); i++)
	{
		if (HeaderList[i] == Header) HaveHeaderAble = true;
	}
	if (!HaveHeaderAble) return -2;
	memset(&HeaderList, 0, sizeof(std::vector<std::wstring>));
	int64 FileLines;
	std::vector<std::wstring> FileAllLines;
	int32 Returns = GetFileAllLines(FilePath, FileAllLines, FileLines);
	if (Returns != 0) return Returns;
	memset(&Returns, 0, sizeof(int32));
	Keys_Values.clear();
	for (int64 i = 0; i < FileLines; i++)
	{
		if (FileAllLines[i][0] == L'/' && FileAllLines[i][1] == L'/')continue;
		if (FileAllLines[i].length() == 0) continue;
		if (FileAllLines[i][FileAllLines[i].length()-1] ==L':')
		{
			if(FileAllLines[i].replace(FileAllLines[i].find_last_of(L":"),sizeof(wchar_t),L"")== Header)
			{
				FileAllLines[i] += L":";
				if (FileAllLines[++i] != L"{") continue;
				i++;
				while (i < FileLines)
				{
					if (FileAllLines[i] == L"}") { break; }
					Keys_Values.push_back(FileAllLines[i++]);
					
				}
			}
		}
	}
	memset(&FileLines, 0, sizeof(int32));
	memset(&FileAllLines, 0, sizeof(std::vector<std::wstring>));
	return 0;
}
int32 GetFileAllKeyList(const wchar_t* FilePath, const wchar_t* Header, std::vector<std::wstring>& KeyList)
{
	if (_waccess_s(FilePath, 0) != 0) return -1;
	std::vector<std::wstring> HeaderList;
	GetFileAllHeadersList(FilePath, HeaderList);
	bool HaveHeaderAble = false;
	for (int32 i = 0; i < HeaderList.size(); i++)
	{
		if (HeaderList[i] == Header) HaveHeaderAble = true;
	}
	if (!HaveHeaderAble) return -2;
	memset(&HeaderList, 0, sizeof(std::vector<std::wstring>));
	int64 FileLines;
	std::vector<std::wstring> FileAllLines;
	int32 Returns = GetFileAllLines(FilePath, FileAllLines, FileLines);
	if (Returns != 0) return Returns;
	memset(&Returns, 0, sizeof(int32));
	KeyList.clear();
	for (int64 i = 0; i < FileLines; i++)
	{
		if (FileAllLines[i][0] == L'/' && FileAllLines[i][1] == L'/')continue;
		if (FileAllLines[i].length() == 0) continue;
		if (FileAllLines[i][FileAllLines[i].length() - 1] == L':')
		{
			if (FileAllLines[i].replace(FileAllLines[i].find_last_of(L":"), sizeof(wchar_t), L"") == Header)
			{
				FileAllLines[i] += L":";
				if (FileAllLines[++i] != L"{") continue;
				i++;
				while (i < FileLines)
				{
					if (FileAllLines[i] == L"}") { break; }
					std::wstring wstr= FileAllLines[i++];
					KeyList.push_back(wstr.substr(0, wstr.find_last_of(L"=")));
				}
			}
		}
	}
	memset(&FileLines, 0, sizeof(int32));
	memset(&FileAllLines, 0, sizeof(std::vector<std::wstring>));
	return 0;
}
int32 GetFileValue(const std::vector<std::wstring> Keys, const wchar_t* Key, std::wstring& Value)
{
	return 0;
}
int32 GetFileValue(const wchar_t* FilePath, const wchar_t* Header, const wchar_t* Key, std::wstring& Value)
{
	return 0;
}