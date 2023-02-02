/*
    Copyright (©) 2022-2023  TheColdWorld

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#include <iostream> 
#include <fstream> 
#include <string>
#include <vector>
#include <codecvt>
#include <algorithm>
#include "structures.h"
#ifdef  THECOLDWORLDCONFIGEDITERWINDOWS_EXPORTS
#define TheColdWorldConfigEditer_Windows_Dll_Api __declspec(dllexport) 
#else
#define TheColdWorldConfigEditer_Windows_Dll_Api __declspec(dllimport) 
#endif // ! TheColdWorldConfigEditer_Windows_Dll
namespace TheColdWorldConfigEditer
{
	const std::wstring Version = std::wstring(L"1.0.1");
	const std::wstring Auther = std::wstring(L"TheColdWorld");
	namespace For_String
	{
		TheColdWorldConfigEditer_Windows_Dll_Api class Headers;
		TheColdWorldConfigEditer_Windows_Dll_Api class Header;
		TheColdWorldConfigEditer_Windows_Dll_Api class Key;
		TheColdWorldConfigEditer_Windows_Dll_Api class Value;
		TheColdWorldConfigEditer_Windows_Dll_Api std::wstring RandonString(uint64 StringLength);
	}
	TheColdWorldConfigEditer_Windows_Dll_Api class NotSerializationExpection;
	TheColdWorldConfigEditer_Windows_Dll_Api class NotFindedExpection;
	TheColdWorldConfigEditer_Windows_Dll_Api class WrongValueExpection;
}
class TheColdWorldConfigEditer::For_String::Value
{
public:
	TheColdWorldConfigEditer_Windows_Dll_Api Value(std::wstring Value);
	TheColdWorldConfigEditer_Windows_Dll_Api Value(const Value& Others,Key* FatherPointer);
	TheColdWorldConfigEditer_Windows_Dll_Api void operator =(const Value& WillReplaceValue);
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring ToString();
	TheColdWorldConfigEditer_Windows_Dll_Api int32 ToInt32();
	TheColdWorldConfigEditer_Windows_Dll_Api int64 ToInt64();
	TheColdWorldConfigEditer_Windows_Dll_Api uint64 ToUInt64();
	TheColdWorldConfigEditer_Windows_Dll_Api double ToDouble();
	TheColdWorldConfigEditer_Windows_Dll_Api bool ToBool();
	TheColdWorldConfigEditer_Windows_Dll_Api ~Value();
	TheColdWorldConfigEditer_Windows_Dll_Api void RefResh();
private:
	std::wstring _Value;
	bool HaveFatherAble = false;
	Key* FatherPotinter = nullptr;
protected:
	Value() {}
};
class TheColdWorldConfigEditer::For_String::Key
{
public:
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring ToString();
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring Serializedstring();
	TheColdWorldConfigEditer_Windows_Dll_Api Key(std::wstring KeyName,Value value);
	TheColdWorldConfigEditer_Windows_Dll_Api Key(std::wstring& Serializedstring);
	TheColdWorldConfigEditer_Windows_Dll_Api Key(const Key& Others, Header* fatherPotinter);
	TheColdWorldConfigEditer_Windows_Dll_Api Value& value();
	TheColdWorldConfigEditer_Windows_Dll_Api Key& operator =(const Key& WillreplaceKey);
	TheColdWorldConfigEditer_Windows_Dll_Api void value(Value& NewValue);
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring Name();
	TheColdWorldConfigEditer_Windows_Dll_Api void Name(std::wstring NewName);
	TheColdWorldConfigEditer_Windows_Dll_Api void Refresh();
	TheColdWorldConfigEditer_Windows_Dll_Api void Update();
	TheColdWorldConfigEditer_Windows_Dll_Api ~Key();
private:
	std::wstring _Name;
	Value _Value=Value(L"");
	bool HaveFather = false;
	Header* FatherPointer = 0;
	std::wstring _Serializedstring;
protected:
	Key() {}
};
class TheColdWorldConfigEditer::For_String::Header
{
public:
	TheColdWorldConfigEditer_Windows_Dll_Api void Refresh();
	TheColdWorldConfigEditer_Windows_Dll_Api void Update();
	TheColdWorldConfigEditer_Windows_Dll_Api Header(std::wstring Serializedstring);
	TheColdWorldConfigEditer_Windows_Dll_Api Header(std::vector<std::wstring> SerializedstringArray);
	TheColdWorldConfigEditer_Windows_Dll_Api Header(std::wstring Name,std::vector<Key>& KeyArray);
	TheColdWorldConfigEditer_Windows_Dll_Api Header(const Header& Others,Headers* FartherPointer);
	TheColdWorldConfigEditer_Windows_Dll_Api void Add(Key& NewKey);
	TheColdWorldConfigEditer_Windows_Dll_Api void Delete(std::wstring WillDeleteKeyName);
	TheColdWorldConfigEditer_Windows_Dll_Api uint64 Length();
	TheColdWorldConfigEditer_Windows_Dll_Api Key& operator [](const std::wstring& KeyName);
	TheColdWorldConfigEditer_Windows_Dll_Api Header& operator =(const Header ReplaceHeader);
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring Serializedstring();
	TheColdWorldConfigEditer_Windows_Dll_Api const std::vector<std::wstring> SerializedstringArray();
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring ToString();
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring Name();
	TheColdWorldConfigEditer_Windows_Dll_Api ~Header();
private:
	std::wstring _Name;
	std::vector<std::wstring> _KeyNameArray;
	std::vector<Key> _KeyArray;
	std::wstring _Serializedstring;
	std::vector<std::wstring> _SerializedstringArray;
	bool HaveFather = false;
	Headers* FatherPointer = 0;
protected:
	Header() {}
};
class TheColdWorldConfigEditer::For_String::Headers
{
public:
	TheColdWorldConfigEditer_Windows_Dll_Api Headers(const std::wstring Serializedstring);
	TheColdWorldConfigEditer_Windows_Dll_Api Headers(const std::vector<std::wstring> SerializedstringArray);
	TheColdWorldConfigEditer_Windows_Dll_Api Headers(const Headers& Others);
	TheColdWorldConfigEditer_Windows_Dll_Api const std::vector<std::wstring> SerializedstringArray();
	TheColdWorldConfigEditer_Windows_Dll_Api const std::wstring Serializedstring();
	TheColdWorldConfigEditer_Windows_Dll_Api Header& operator [](const std::wstring& HeaderName);
	TheColdWorldConfigEditer_Windows_Dll_Api void Update();

	TheColdWorldConfigEditer_Windows_Dll_Api ~Headers();
private:
	std::wstring _Serializedstring;
	std::vector<std::wstring> _SerializedstringArray;
	std::vector<std::wstring> _HeaderNameArray;
	std::vector<Header> _HeaderArray;
protected:
	Headers() { }
};

class TheColdWorldConfigEditer::NotSerializationExpection : std::exception
{
public:
	TheColdWorldConfigEditer_Windows_Dll_Api NotSerializationExpection(std::wstring Message);
protected:
	NotSerializationExpection() {}
};
class TheColdWorldConfigEditer::NotFindedExpection : std::exception
{
public:
	TheColdWorldConfigEditer_Windows_Dll_Api NotFindedExpection(std::wstring Message);
protected:
	NotFindedExpection() {}
};
class TheColdWorldConfigEditer::WrongValueExpection : std::exception
{
public:
	TheColdWorldConfigEditer_Windows_Dll_Api WrongValueExpection(std::wstring Message);
};
