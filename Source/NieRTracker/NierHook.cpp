#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <vector>
#include <iostream>

DWORD GetProcessID(void)
{
	HWND hwnd = FindWindowA(NULL, "NieR:Automata");
	if (hwnd == NULL)
	{
		std::cout << ("Game window not found") << std::endl;
		exit(-1);
	}

	DWORD pID;
	GetWindowThreadProcessId(hwnd, &pID);
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (pHandle == INVALID_HANDLE_VALUE)
	{
		std::cout << ("Failed to open process") << std::endl;
		exit(-1);
	}
	return pID;
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}