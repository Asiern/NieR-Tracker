#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <vector>

DWORD GetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID)
{
	DWORD dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID); // make snapshot of all modules within process
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32)) //store first Module in ModuleEntry32
	{
		do
		{
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) // if Found Module matches Module we look for -> done!
			{
				dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32)); // go through Module entries in Snapshot and store in ModuleEntry32
	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

int main()
{
	HWND hwnd = FindWindowA(NULL, "NieR:Automata");
	if (hwnd == NULL)
	{
		std::cout << ("Game not found") << std::endl;
		return 0;
	}

	DWORD pID;
	GetWindowThreadProcessId(hwnd, &pID);
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (pHandle == INVALID_HANDLE_VALUE)
	{
		std::cout << ("Failed to open process") << std::endl;
		return 0;
	}

	char gameName[] = "NieRAutomata.exe";
	float Xpos;
	float Ypos;
	float Zpos;
	DWORD gameBaseAddress = 0x154C; //GetModuleBaseAddress((TCHAR*)gameName, pID);
	DWORD entityAddPointer = gameBaseAddress + 0x16053B8;
	DWORD entityAddress = 0x12FE30C0;
	//ReadProcessMemory(pHandle, (LPCVOID)entityAddPointer, &entityAddress, sizeof(entityAddress), NULL);
	DWORD XAddress = (DWORD)entityAddress + 0x50;
	DWORD YAddress = (DWORD)entityAddress + 0x58;
	DWORD ZAddress = (DWORD)entityAddress + 0x54;
	while (true)
	{
		//Get Positions
		ReadProcessMemory(pHandle, (LPCVOID)XAddress, &Xpos, sizeof(Xpos), NULL);
		ReadProcessMemory(pHandle, (LPCVOID)YAddress, &Ypos, sizeof(Ypos), NULL);
		ReadProcessMemory(pHandle, (LPCVOID)ZAddress, &Zpos, sizeof(Zpos), NULL);
		std::cout << "X " << Xpos << std::endl;
		std::cout << "Y " << Ypos << std::endl;
		std::cout << "Z " << Zpos << std::endl;
		Sleep(500);
		system("cls");
	}
	return (0);
}