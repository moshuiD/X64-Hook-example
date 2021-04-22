#pragma once
#include<Windows.h>

extern uintptr_t address;
//extern BYTE originalBytes[30]{ 0 };
void Hook(uintptr_t addr, void* fucPtr);
void Hook(void*fucPtr);
void Patch(BYTE* dst, BYTE* src, unsigned int size);
void UnHook();