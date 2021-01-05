#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <vector>

//Hook
#include "NierHook.hpp"
//Offsets
#include "defineOffsets.hpp"

int main()
{

	DWORD pID = GetProcessID();
	uintptr_t baseAddress = GetModuleBaseAddress(pID, L"NieRAutomata.exe");
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	//Entity address static pointer
	uintptr_t entityAddPointer = baseAddress + 0x16053B8;
	uintptr_t entityAddress;
	//Get entity address from static pointer
	ReadProcessMemory(pHandle, (LPCVOID)entityAddPointer, &entityAddress, sizeof(entityAddress), NULL);
	float Xpos;
	float Ypos;
	float Zpos;
	while (entityAddress == 0) {
		std::cout << "Please load a savefile" << std::endl;
		//Get entity address from pointer at offset 0x16053B8
		ReadProcessMemory(pHandle, (LPCVOID)entityAddPointer, &entityAddress, sizeof(entityAddress), NULL);
		Sleep(500);
		system("cls");
	}
	//Get coordinate memory address
	uintptr_t XAddress = static_cast<uintptr_t>((DWORD)entityAddress) + X;
	uintptr_t YAddress = static_cast<uintptr_t>((DWORD)entityAddress) + Y;
	uintptr_t ZAddress = static_cast<uintptr_t>((DWORD)entityAddress) + Z;
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