#include"MyMethod.h"
#include"Hook.h"
#include<Windows.h>
#include<iostream>
int WINAPI MyMessageBoxW(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_ UINT uType) 
{
	UnHook();
	MessageBoxW(NULL, L"shit", L"1", MB_OK);
	return 1;
}
BOOL
WINAPI
MyReadProcessMemory(
	_In_ HANDLE hProcess,
	_In_ LPCVOID lpBaseAddress,
	_Out_writes_bytes_to_(nSize, *lpNumberOfBytesRead) LPVOID lpBuffer,
	_In_ SIZE_T nSize,
	_Out_opt_ SIZE_T* lpNumberOfBytesRead
)
{
	
	printf("从0x%I64X读取\r\n",(uintptr_t)lpBaseAddress);
	UnHook();
	byte a[256];
	byte shit[256];
	ReadProcessMemory(hProcess, lpBuffer, a, sizeof(a),(size_t*)shit);
	Hook((uintptr_t)GetProcAddress(GetModuleHandleW(L"Kernel32.dll"), "ReadProcessMemory"), &MyReadProcessMemory);
	for (size_t i = 0; i < nSize; i++)
	{
		printf("写入内容%0x\r\n", a[i]);
		
	}
	//printf("写入内容%I64X\r\n", a);
	return true;
}