// dllmain.cpp : Defines the entry point for the DLL application.
//#include "stdafx.h"
#include <Windows.h>

char path[MAX_PATH] = { 0 };

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    char* ptr = NULL;
    GetModuleFileNameA(hModule, path, MAX_PATH);
    ptr = strrchr(path, '\\');
    if (strcmp(ptr + 1, "AR_Env.dll"))
        return FALSE;

	switch (ul_reason_for_call){
	    case DLL_PROCESS_ATTACH:
	    case DLL_THREAD_ATTACH:
	    case DLL_THREAD_DETACH:
	    case DLL_PROCESS_DETACH:
		    break;
	}
	return TRUE;
}

