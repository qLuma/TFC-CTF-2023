#include <iostream>
#include <windows.h>
#include <intrin.h>
#include <winternl.h>
#include <libloaderapi.h>
#include <wincrypt.h>
#include <Psapi.h>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>


#define LODWORD(_qw)    ((DWORD)(_qw))

void NTAPI __stdcall TLSCallbacks(PVOID DllHandle, DWORD dwReason, PVOID Reserved);

#ifdef _M_IX86
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:__tls_callback")
#else
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback")
#endif
EXTERN_C
#ifdef _M_X64
#pragma const_seg (".CRT$XLB")
const
#else
#pragma data_seg (".CRT$XLB")
#endif

PIMAGE_TLS_CALLBACK _tls_callback = TLSCallbacks;
#pragma data_seg ()
#pragma const_seg ()

struct {
	char usl[100];
	int a, b, d;
	char usl2[100];
}dbg;

void NTAPI __stdcall TLSCallbacks(PVOID DllHandle, DWORD dwReason, PVOID Reserved)
{
	ULONGLONG tsc1;
	ULONGLONG tsc2;
	ULONGLONG tsc3;
	DWORD i = 0;

	for (i = 0; i < 10; i++)
	{
		tsc1 = __rdtsc();
		GetProcessHeap();

		tsc2 = __rdtsc();
		CloseHandle(0);

		tsc3 = __rdtsc();
		if ((LODWORD(tsc3) - LODWORD(tsc2)) / (LODWORD(tsc2) - LODWORD(tsc1)) <= 10) {
			int b;
			while (dbg.b != 0)
			{
				b = (~dbg.a) & dbg.b;
				dbg.a = dbg.a ^ dbg.b;
				dbg.b = b << 1;
			}
			dbg.d = b ^ (dbg.a % dbg.b); //sigfpe
		}
	}
}

int inc(unsigned int i) {
	unsigned int m = 1;
	while (i & m) {
		i = i & (~m);
		m = (m << 1);
	}
	i = i | m;
	return i;
}

int mul(int x, int y)
{
	if (y == 0)
		return 0;

	if (y > 0)
		return (x + mul(x, y - 1));

	if (y < 0)
		return -mul(x, -y);
}

std::string ReverseString(const std::string& str)
{
	std::string reversedStr;
	for (int i = str.length() - 1; i >= 0; --i)
	{
		reversedStr.push_back(str[i]);
	}
	return reversedStr;
}

std::string SHA256Hash(const char* data)
{
	HCRYPTPROV hProv = NULL;
	HCRYPTHASH hHash = NULL;

	DWORD hashSize = 0;
	DWORD dataSize = static_cast<DWORD>(std::strlen(data));
	BYTE hash[32];

	std::string sha256Hash;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		return sha256Hash;
	}

	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
	{
		CryptReleaseContext(hProv, 0);
		return sha256Hash;
	}

	if (!CryptHashData(hHash, reinterpret_cast<const BYTE*>(data), dataSize, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return sha256Hash;
	}

	hashSize = sizeof(hash);
	if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashSize, 0))
	{
		std::stringstream ss;
		for (DWORD i = 0; i < hashSize; ++i)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
		}

		sha256Hash = ss.str();
	}
	else
	{
		std::cout << "Failed to retrieve hash value" << std::endl;
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);

	return sha256Hash;
}

int nrFlag[11] = { 1569, 330, 987, 977, 290, 1031, 1015, 315, 39, 1217, 1049 };
int fakeNrFlag[11] = { 382, 4, 926, 341, 398, 982, 17, 526, 994, 1026, 1605 };
const char* functionName2;
int main()
{
	const char* flag[16] = { 0 };
	const char* fake_flag[16] = { 0 };

	HMODULE hModule = GetModuleHandle(L"kernel32.dll");
	if (hModule != NULL)
	{
		// Get the module information to obtain the module base address
		MODULEINFO moduleInfo;
		if (GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(MODULEINFO)))
		{
			// Get the IMAGE_EXPORT_DIRECTORY
			IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(moduleInfo.lpBaseOfDll);
			IMAGE_NT_HEADERS* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<DWORD_PTR>(moduleInfo.lpBaseOfDll) + dosHeader->e_lfanew);
			IMAGE_EXPORT_DIRECTORY* exportDirectory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(reinterpret_cast<DWORD_PTR>(moduleInfo.lpBaseOfDll) + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

			// Get the function names
			DWORD* addressOfNames = reinterpret_cast<DWORD*>(reinterpret_cast<DWORD_PTR>(moduleInfo.lpBaseOfDll) + exportDirectory->AddressOfNames);
			int fake_index = 0;
			for (DWORD i = 0; i < exportDirectory->NumberOfNames; ++i)
			{
				DWORD functionNameRVA = addressOfNames[i];
				if (functionNameRVA > 0)
				{
					const char* functionName = reinterpret_cast<const char*>(reinterpret_cast<DWORD_PTR>(moduleInfo.lpBaseOfDll) + functionNameRVA);
					std::string hash = SHA256Hash(functionName);

					std::string IsDebuggerPresentHash;
					std::string ExitProcessHash;

					IsDebuggerPresentHash = ReverseString("d1ed5c5f5cf6f9e976461b6e12203014a259ff5fc0901b20fd820d2fcf8c78a8");
					ExitProcessHash = ReverseString("0984eb9faef20c0b07bc0df63c3c415000b5979f02a41d56cdef0e85694f207e");

					int index = 0;
					for (int k = 0; k <= 10; k++) {
						if (nrFlag[index] == i)
							flag[index] = functionName;
						index = inc(index);
					}

					int fake_index = 0;
					for (int k = 0;k <= 10;k++) {
						if (fakeNrFlag[fake_index] == i)
							fake_flag[fake_index] = functionName;
						fake_index = inc(fake_index);
					}

					if (hash == ExitProcessHash) {
						functionName2 = functionName;
					}

					if (hash == IsDebuggerPresentHash) {
						FARPROC pIsDebuggerPresent = GetProcAddress(hModule, functionName); //IsDebuggerPresent
						if (pIsDebuggerPresent != nullptr)
						{
							BOOL(WINAPI * fnIsDebuggerPresent)() = reinterpret_cast<BOOL(WINAPI*)()>(pIsDebuggerPresent);
							BOOL isDebuggerPresent = fnIsDebuggerPresent();
							if (isDebuggerPresent)
							{
								FARPROC pExitProcess = GetProcAddress(hModule, functionName2); //ExitProcess
								using ExitProcessFunc = VOID(WINAPI*)(UINT);
								ExitProcessFunc fnExitProcess = reinterpret_cast<ExitProcessFunc>(pExitProcess);
								fnExitProcess(0);
							}
						}
					}


				}
			}
		}
		else
		{
			std::cout << "Failed to get module information" << std::endl;
		}
	}
	else
	{
		std::cout << "Failed to get handle to kernel32.dll" << std::endl;
	}

	PPEB pPeb = (PPEB)__readgsqword(0x60);
	int byte = 1;
	for (int i = 0; i < 46; i++) {
		byte = inc(byte);
	}
	for (int i = 0; i < 2; i++)
		byte = mul(byte, 2);

	DWORD dwNtGlobalFlag = *(PDWORD)((PBYTE)pPeb + byte);
	int nr = 0x20;
	nr = mul(nr, 2);

	std::string welldone;
	std::string fakeflag;
	printf("You are close to the flag :)");
	if (dwNtGlobalFlag & (nr | 0x20 | 0x10)) {
		for (int k = 0; k <= 10; k++)
			fakeflag[k] = fake_flag[k][0];
	}
	else
	{
		for (int k = 0; k <= 10; k++)
			welldone[k] = flag[k][0];
	}
}

