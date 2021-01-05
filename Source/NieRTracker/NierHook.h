#ifndef NIERHOOK_H
#define NIERHOOK_H

DWORD GetProcessID(void);
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

#endif