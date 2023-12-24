#pragma once
#define DLL_METASPLOIT_ATTACH	4
#define DLL_METASPLOIT_DETACH	5
#define DLL_QUERY_HMODULE		6

#define DEREF( name )*(UINT_PTR *)(name)
#define DEREF_64( name )*(DWORD64 *)(name)
#define DEREF_32( name )*(DWORD *)(name)
#define DEREF_16( name )*(WORD *)(name)
#define DEREF_8( name )*(BYTE *)(name)
#define BreakForError(reason){MessageBoxA(NULL,reason,"ERROR",MB_OK); break;}
typedef void (*ShowMessageFunc)(const char*);
typedef int (*dllmain)();
void WINAPI dllFuncs() {//dll编程测试
    HINSTANCE hDll;
    ShowMessageFunc showMessage;

    hDll = LoadLibrary(L"C:\\Users\\YJ\\Desktop\\codes\\cpp\\Dll_TEST\\x64\\Debug\\Dll_TEST.dll");
    if (hDll != NULL)
    {
        showMessage = (ShowMessageFunc)GetProcAddress(hDll, "ShowMessage");
        dllmain dllmainFunc = (dllmain)GetProcAddress(hDll, "main");
        if (showMessage != NULL)
        {
            const char* message = "dll测试成功";
            showMessage(message);
        }
        else
        {
            printf("从dll中调用show函数失败\n");
        }
        if (dllmainFunc != NULL)
        {
            dllmainFunc();
        }
        else
        {
            printf("从dll中调用main函数失败\n");
        }
        FreeLibrary(hDll);
    }
    else
    {
        printf("加载dll失败\n");
    }
}
typedef HOOKPROC(*func)(void);
void WINAPI TestDllInject()
{
    HWND  hwnd = ::FindWindowA(NULL, "Win32_From Test TARGET");
    DWORD pid;
    DWORD thread_id = ::GetWindowThreadProcessId(hwnd, &pid);

    HMODULE mod = LoadLibraryA("C:\\Users\\YJ\\Desktop\\codes\\cpp\\Dll_TEST\\x64\\Debug\\Dll_TEST.dll");
    func proc = (func)::GetProcAddress(mod, "getDllPoint");//要注入的方法

    HOOKPROC fp = proc();

    HHOOK hhk = ::SetWindowsHookEx(WH_KEYBOARD, fp, mod, thread_id);
}
void RemoteDllInject()
{
    const char* path = "C:\\Users\\YJ\\Desktop\\codes\\cpp\\Dll_TEST\\x64\\Debug\\Dll_TEST.dll";//要注入的dll路径

    HWND  hwnd = ::FindWindowA(NULL, "Win32_From Test TARGET");
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    LPVOID lpAddr = VirtualAllocEx(hProc, NULL, strlen(path) + 1, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(hProc, lpAddr, path, strlen(path), NULL);

    HMODULE sysMod = LoadLibraryA("Kernel32.dll");



    LPTHREAD_START_ROUTINE fp = (LPTHREAD_START_ROUTINE)GetProcAddress(sysMod, "LoadLibraryA");

    CreateRemoteThread(hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)fp, lpAddr, 0, NULL);


}
//反射dll注入
/*
FARPROC WINAPI GetProcAddressR( HANDLE hModule, LPCSTR lpProcName )
{
	UINT_PTR uiLibraryAddress = 0;
	FARPROC fpResult          = NULL;

	if( hModule == NULL )
		return NULL;

	// a module handle is really its base address
	uiLibraryAddress = (UINT_PTR)hModule;

	__try
	{
		UINT_PTR uiAddressArray = 0;
		UINT_PTR uiNameArray    = 0;
		UINT_PTR uiNameOrdinals = 0;
		PIMAGE_NT_HEADERS pNtHeaders             = NULL;
		PIMAGE_DATA_DIRECTORY pDataDirectory     = NULL;
		PIMAGE_EXPORT_DIRECTORY pExportDirectory = NULL;
			
		// get the VA of the modules NT Header
		pNtHeaders = (PIMAGE_NT_HEADERS)(uiLibraryAddress + ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew);

		pDataDirectory = (PIMAGE_DATA_DIRECTORY)&pNtHeaders->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];

		// get the VA of the export directory
		pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)( uiLibraryAddress + pDataDirectory->VirtualAddress );
			
		// get the VA for the array of addresses
		uiAddressArray = ( uiLibraryAddress + pExportDirectory->AddressOfFunctions );

		// get the VA for the array of name pointers
		uiNameArray = ( uiLibraryAddress + pExportDirectory->AddressOfNames );
				
		// get the VA for the array of name ordinals
		uiNameOrdinals = ( uiLibraryAddress + pExportDirectory->AddressOfNameOrdinals );

		// test if we are importing by name or by ordinal...
		if( ((DWORD)lpProcName & 0xFFFF0000 ) == 0x00000000 )
		{
			// import by ordinal...

			// use the import ordinal (- export ordinal base) as an index into the array of addresses
			uiAddressArray += ( ( IMAGE_ORDINAL( (DWORD)lpProcName ) - pExportDirectory->Base ) * sizeof(DWORD) );

			// resolve the address for this imported function
			fpResult = (FARPROC)( uiLibraryAddress + DEREF_32(uiAddressArray) );
		}
		else
		{
			// import by name...
			DWORD dwCounter = pExportDirectory->NumberOfNames;
			while( dwCounter-- )
			{
				char * cpExportedFunctionName = (char *)(uiLibraryAddress + DEREF_32( uiNameArray ));
				
				// test if we have a match...
				if( strcmp( cpExportedFunctionName, lpProcName ) == 0 )
				{
					// use the functions name ordinal as an index into the array of name pointers
					uiAddressArray += ( DEREF_16( uiNameOrdinals ) * sizeof(DWORD) );
					
					// calculate the virtual address for the function
					fpResult = (FARPROC)(uiLibraryAddress + DEREF_32( uiAddressArray ));
					
					// finish...
					break;
				}
						
				// get the next exported function name
				uiNameArray += sizeof(DWORD);

				// get the next exported function name ordinal
				uiNameOrdinals += sizeof(WORD);
			}
		}
	}
	__except( EXCEPTION_EXECUTE_HANDLER )
	{
		fpResult = NULL;
	}

	return fpResult;
}
DWORD Rva2Offset(DWORD dwRva, UINT_PTR uiBaseAddress)
{
	WORD wIndex = 0;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeaders = NULL;

	pNtHeaders = (PIMAGE_NT_HEADERS)(uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew);

	pSectionHeader = (PIMAGE_SECTION_HEADER)((UINT_PTR)(&pNtHeaders->OptionalHeader) + pNtHeaders->FileHeader.SizeOfOptionalHeader);

	if (dwRva < pSectionHeader[0].PointerToRawData)
		return dwRva;

	for (wIndex = 0; wIndex < pNtHeaders->FileHeader.NumberOfSections; wIndex++)
	{
		if (dwRva >= pSectionHeader[wIndex].VirtualAddress && dwRva < (pSectionHeader[wIndex].VirtualAddress + pSectionHeader[wIndex].SizeOfRawData))
			return (dwRva - pSectionHeader[wIndex].VirtualAddress + pSectionHeader[wIndex].PointerToRawData);
	}

	return 0;
}

DWORD GetReflectiveLoaderOffset(VOID* lpReflectiveDllBuffer)
{
	UINT_PTR uiBaseAddress = 0;
	UINT_PTR uiExportDir = 0;
	UINT_PTR uiNameArray = 0;
	UINT_PTR uiAddressArray = 0;
	UINT_PTR uiNameOrdinals = 0;
	DWORD dwCounter = 0;
#ifdef WIN_X86
	DWORD dwCompiledArch = 1;
#else
	// This will catch Win64
	DWORD dwCompiledArch = 2;
#endif

	uiBaseAddress = (UINT_PTR)lpReflectiveDllBuffer;

	// get the File Offset of the modules NT Header
	uiExportDir = uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew;

	// currenlty we can only process a PE file which is the same type as the one this fuction has  
	// been compiled as, due to various offset in the PE structures being defined at compile time.
	if (((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.Magic == 0x010B) // PE32
	{
		if (dwCompiledArch != 1)
			return 0;
	}
	else if (((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.Magic == 0x020B) // PE64
	{
		if (dwCompiledArch != 2)
			return 0;
	}
	else
	{
		return 0;
	}

	// uiNameArray = the address of the modules export directory entry
	uiNameArray = (UINT_PTR) & ((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

	// get the File Offset of the export directory
	uiExportDir = uiBaseAddress + Rva2Offset(((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress, uiBaseAddress);

	// get the File Offset for the array of name pointers
	uiNameArray = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNames, uiBaseAddress);

	// get the File Offset for the array of addresses
	uiAddressArray = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfFunctions, uiBaseAddress);

	// get the File Offset for the array of name ordinals
	uiNameOrdinals = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNameOrdinals, uiBaseAddress);

	// get a counter for the number of exported functions...
	dwCounter = ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->NumberOfNames;

	// loop through all the exported functions to find the ReflectiveLoader
	while (dwCounter--)
	{
		char* cpExportedFunctionName = (char*)(uiBaseAddress + Rva2Offset(DEREF_32(uiNameArray), uiBaseAddress));

		if (strstr(cpExportedFunctionName, "ReflectiveLoader") != NULL)
		{
			// get the File Offset for the array of addresses
			uiAddressArray = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfFunctions, uiBaseAddress);

			// use the functions name ordinal as an index into the array of name pointers
			uiAddressArray += (DEREF_16(uiNameOrdinals) * sizeof(DWORD));

			// return the File Offset to the ReflectiveLoader() functions code...
			return Rva2Offset(DEREF_32(uiAddressArray), uiBaseAddress);
		}
		// get the next exported function name
		uiNameArray += sizeof(DWORD);

		// get the next exported function name ordinal
		uiNameOrdinals += sizeof(WORD);
	}

	return 0;
}

HANDLE WINAPI LoadRemoteLibraryR(HANDLE hProcess, LPVOID lpBuffer, DWORD dwLength, LPVOID lpParameter)
{
	BOOL bSuccess = FALSE;
	LPVOID lpRemoteLibraryBuffer = NULL;
	LPTHREAD_START_ROUTINE lpReflectiveLoader = NULL;
	HANDLE hThread = NULL;
	DWORD dwReflectiveLoaderOffset = 0;
	DWORD dwThreadId = 0;

	__try
	{
		do
		{
			if (!hProcess || !lpBuffer || !dwLength)
				break;

			// check if the library has a ReflectiveLoader...
			dwReflectiveLoaderOffset = GetReflectiveLoaderOffset(lpBuffer);
			if (!dwReflectiveLoaderOffset)
				break;

			// alloc memory (RWX) in the host process for the image...
			lpRemoteLibraryBuffer = VirtualAllocEx(hProcess, NULL, dwLength, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (!lpRemoteLibraryBuffer)
				break;

			// write the image into the host process...
			if (!WriteProcessMemory(hProcess, lpRemoteLibraryBuffer, lpBuffer, dwLength, NULL))
				break;

			// add the offset to ReflectiveLoader() to the remote library address...
			lpReflectiveLoader = (LPTHREAD_START_ROUTINE)((ULONG_PTR)lpRemoteLibraryBuffer + dwReflectiveLoaderOffset);

			// create a remote thread in the host process to call the ReflectiveLoader!
			hThread = CreateRemoteThread(hProcess, NULL, 1024 * 1024, lpReflectiveLoader, lpParameter, (DWORD)NULL, &dwThreadId);

		} while (0);

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		hThread = NULL;
	}

	return hThread;
}

BOOL PrivilegeEscalation()
{

	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tp;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
		return FALSE;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;

	if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
		return FALSE;
	CloseHandle(hToken);
	return TRUE;
}
void refInject() {
	HANDLE hModule = NULL;
	HANDLE hProcess = NULL;
	HANDLE hToken = NULL;
	DWORD dwBytesRead = 0;
	DWORD dwProcessId = 0;
	TOKEN_PRIVILEGES priv = { 0 };
	do
	{
		HWND  hwnd = ::FindWindowA(NULL, "Win32_From Test TARGET");
		GetWindowThreadProcessId(hwnd, &dwProcessId);
		LPCSTR injectionDll = "C:\\Users\\YJ\\Desktop\\codes\\cpp\\Dll_TEST\\x64\\Debug\\Dll_TEST.dll";
		//Get the Handle of the DLL file.
		HANDLE hFile = CreateFileA(injectionDll, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			BreakForError("Failed to open the DLL file.");

		//Get the DLL file size.
		DWORD dwLength = GetFileSize(hFile, NULL);
		if (dwLength == INVALID_FILE_SIZE || dwLength == 0)
			BreakForError("Failed to get the DLL file size.");

		//在当前进程分配缓冲区
		LPVOID lpBuffer = HeapAlloc(GetProcessHeap(), 0, dwLength);
		if (!lpBuffer)
			BreakForError("Failed to alloc a buffer.");
		//Read the DLL file.
		DWORD dwBytesRead = 0;
		if (ReadFile(hFile, lpBuffer, dwLength, &dwBytesRead, NULL) == false)
			BreakForError("Failed to read the DLL file");
		if (!PrivilegeEscalation())
			BreakForError("Failed to Escalate Privilege.");

		//Open target process
		hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwProcessId);
		MessageBoxA(NULL, LPCSTR(GetLastError), "ERRO", MB_OK);
		if (!hProcess)
			BreakForError("Failed to Open the Target Process.");

		//Inject into target process
		HANDLE hMoudle = LoadRemoteLibraryR(hProcess, lpBuffer, dwLength, NULL);
		if (!hMoudle) {
			MessageBoxA(NULL, "failed inject dll", "ERROR", MB_OK);
		}
		WaitForSingleObject(hModule, -1);
	} while (0);
}
*/
void openDebugPri() {
	HANDLE hToken = NULL;

	BOOL bRet = OpenProcessToken(GetCurrentProcess(),
		TOKEN_ALL_ACCESS, &hToken);

	if (bRet == TRUE)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL,
			SE_DEBUG_NAME,
			&tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken,
			FALSE, &tp, sizeof(tp),
			NULL, NULL);

		CloseHandle(hToken);
	}
}