// trick mingw64 to link dlls directly when -m32 is used
#ifndef __amd64__
#define _KERNEL32_
#define _USER32_
#define _ADVAPI32_
#define _SHLWAPI_
#define _COMDLG32_
#define _SHELL32_
#endif
#define __USE_W32_SOCKETS
#define WINSOCK_API_LINKAGE
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include <shlwapi.h>
#include <tlhelp32.h>
#include <string.h>
#include <windowsx.h>
#include <shlobj.h>

#define strcpy lstrcpyA
#define strcmp lstrcmpA
#define strcat lstrcatA
#define strlenW lstrlenW

// error complaining
static char *serre(int e)
{
	static char buf[512];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, e, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
	buf, sizeof(buf)-1,NULL);
	return buf;
}
#define serr() serre(GetLastError())

static inline DWORD win64()
{
	DWORD ret;
	// On pure win32, gs is 0
	asm ("mov %%gs, %0" : "=r" (ret));
	return ret;
}


