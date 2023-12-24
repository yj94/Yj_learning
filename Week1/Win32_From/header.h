#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#define DLL_METASPLOIT_ATTACH	4
#define DLL_METASPLOIT_DETACH	5
#define DLL_QUERY_HMODULE		6

#define DEREF( name )*(UINT_PTR *)(name)
#define DEREF_64( name )*(DWORD64 *)(name)
#define DEREF_32( name )*(DWORD *)(name)
#define DEREF_16( name )*(WORD *)(name)
#define DEREF_8( name )*(BYTE *)(name)
#define BreakForError(reason){MessageBoxA(NULL,reason,"ERROR",MB_OK); break;}