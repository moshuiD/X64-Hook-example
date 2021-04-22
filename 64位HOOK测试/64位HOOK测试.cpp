
#include <windows.h>
#include <iostream>
#include"Hook.h"
#include"MyMethod.h"
int main()
{
    //Hook((uintptr_t)GetProcAddress(GetModuleHandle(L"user32.dll"), "MessageBoxW"),&MyMessageBoxW);
    Hook((uintptr_t)GetProcAddress(GetModuleHandleW(L"Kernel32.dll"), "ReadProcessMemory"),&MyReadProcessMemory);
    byte a[2]{ 0x00,0x11 };
    ReadProcessMemory(GetCurrentProcess(),(LPCVOID)0x111111,a,2,(size_t*)2);
    //MessageBoxW(NULL, L"shit", L"shit1", NTE_OP_OK);
    std::cin.get();
}