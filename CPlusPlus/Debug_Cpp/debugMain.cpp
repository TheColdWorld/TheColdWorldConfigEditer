#include "../TheColdWorldConfigEditer_Windows/TheColdWorldConfigEditer_Windows_Dll_Header.h"
int main()
{
	std::vector<std::wstring> AllLines{ L"1:",L"{",L"key1=1",L"key2=2",L"}",L"2:",L"{",L"key1=3",L"key2=4",L"}",L"3:",L"{",L"key1=5",L"key2=6",L"}" };
	std::wstring AllStr = L"1:\n{\nkey1=1\nkey2=2\n}\n2:\n{\nkey1=3\nkey2=4\n}\n3:\n{\nkey1=5\nkey2=6\n}";
	TheColdWorldConfigEditer::For_String::Headers Headerss(AllStr);
	TheColdWorldConfigEditer::For_String::Key key(std::wstring(L"114514"), TheColdWorldConfigEditer::For_String::Value(L"19191280"));
	std::vector< TheColdWorldConfigEditer::For_String::Key> keys;
	keys.push_back(key);
	Headerss[L"2"].Add(key);
	std::wcout << Headerss[L"2"][L"114514"].Serializedstring();
	return 0;
}