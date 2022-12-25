#include "../TheColdWorldConfigEditer_Windows/TheColdWorldConfigEditer_Windows_Dll_Header.h"

int main()
{
	std::vector<std::wstring> wstArray;
	int32 ArrayLength = 0;
	int32 returns = GetFileAllKeyList(L"1.txt", L"1", wstArray);
	return returns;
}