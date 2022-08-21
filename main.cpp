#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>


void checkProcess(wchar_t* pName) {
	PROCESSENTRY32 pe32;
	HANDLE allProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (Process32Next(allProcessSnapshot, &pe32))
	{
		std::wcout << pe32.szExeFile << "\t" << pe32.th32ProcessID << "\tNot found Process" << "\n";

		if ((wchar_t *)&pe32.szExeFile == pName)
		{
			std::wcout << pe32.szExeFile << "Found Process" << "\n";
			break;
		}
	}
}

int main()
{
	wchar_t pName[] = L"PathOfExileSteam.exe";

	checkProcess(pName);

	return 0;
}