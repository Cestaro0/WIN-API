#include <iostream>
#include <windows.h>

DWORD WINAPI MinhaThread(LPVOID params) 
{
	for (;;)
		std::operator<<(std::cout, "AEEEE BROTHER ESTOU EM OUTRO ENDEREÇO VIRTUAL LMAO").operator<<(std::endl);

	return 0;
}

auto main(void) -> int
{
	HWND hwProc = FindWindowA(
		_In_opt_ NULL,
		_In_opt_ "Name window"
	);

	if (!hwProc)
		std::operator<<(std::cout, "Não foi possivel encontrar o processo, erro: ").operator<<(GetLastError()).operator<<(std::endl);

	DWORD dwPid = 0;

	GetWindowThreadProcessId(
		_In_ hwProc,
		_Out_opt_ &dwPid
	);

	HANDLE hProc = OpenProcess(
		_In_ PROCESS_ALL_ACCESS,
		_In_ TRUE,
		_In_ dwPid
	);

	if (!hProc)
	{
		std::operator<<(std::cout, "Não foi possivel encontrar o processo, erro: ").operator<<(GetLastError()).operator<<(std::endl);

		exit(-1);
	}

	DWORD dwTid = 0;

	HANDLE hTidProcMem = CreateRemoteThread(
		_In_ hProc,
		_In_ NULL,
		_In_ 0,
		_In_ MinhaThread,
		_In_ NULL,
		_In_ NULL,
		_Out_ &dwTid
	);

	if (hTidProcMem == INVALID_HANDLE_VALUE)
	{
		std::operator<<(std::cout, "Não foi possivel inicar a thread remota: ").operator<<(GetLastError()).operator<<(std::endl);
		
		exit(-1);
	}

	std::cin.get();

	return 0;	
}