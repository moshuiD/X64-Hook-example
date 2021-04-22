#include"Hook.h"
#include<Windows.h>
#include"MyMethod.h"
uintptr_t address;
BYTE originalBytes[30]{ 0 };
void Hook(uintptr_t addr,void* fucPtr)
{
	address = addr;
	memcpy(originalBytes, (void*)addr, 15);
	Hook(fucPtr);
}

void Hook(void* fucPtr)
{
	BYTE stub[14] = {
	0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
    void* pTrampoline = VirtualAlloc(0, 15 + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    DWORD dwOld = 0;
    VirtualProtect((LPVOID)address,15, PAGE_EXECUTE_READWRITE, &dwOld);
    //»°2¥Œµÿ÷∑£°£°£°
   
    memcpy(stub + 6, &fucPtr, 8);

    memcpy((void*)address, stub, sizeof(stub));
    for (int i = 14; i < 15; i++)
    {
        *(BYTE*)((DWORD_PTR)address + i) = 0x90;
    }
    VirtualProtect((LPVOID)address, 15, dwOld, &dwOld);
	
}
void UnHook()
{
    Patch((BYTE*)address, originalBytes, 15);
}
void Patch(BYTE* dst, BYTE* src, unsigned int size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}
