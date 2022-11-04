#include <iostream>
#include <windows.h>

HANDLE gMutex, gThreadId, gThreadId2;
int gCount = 1;

auto WINAPI FuncEven(LPVOID params) -> DWORD
{
	while (gCount < 10) 
	{
		WaitForSingleObject(
			_In_ gMutex,
			_In_ INFINITE
		);

		if (gCount % 2 == 0)
			std::cout << "Par -> " << gCount++ << std::endl;

		ReleaseMutex(
			_In_ gMutex
		);
	}

	return 0;

}

auto WINAPI FuncOdd(LPVOID params) -> DWORD 
{
	while (gCount < 10) 
	{
		WaitForSingleObject(
			_In_ gMutex,
			_In_ INFINITE
		);

		if (gCount % 2 == 1)
			std::cout << "Impar -> " << gCount++ << std::endl;

		ReleaseMutex(
			_In_ gMutex
		);
	} 

	return 0;
	
}

auto main(void) -> int 
{
	std::operator<<(std::cout, "Sincronizando as threads").operator<<(std::endl);

	DWORD dwPid = 0;

	gMutex = CreateMutex(
		_In_opt_ NULL,
		_In_ FALSE,
		_In_opt_ NULL
	);

	gThreadId = CreateThread(
		_In_opt_ NULL,
		_In_ NULL,
		_In_ FuncEven,
		_In_opt_ NULL,
		_In_ NULL,
		_In_opt_ &dwPid
	);

	gThreadId2 = CreateThread(
		_In_opt_ NULL,
		_In_ NULL,
		_In_ FuncOdd,
		_In_opt_ NULL,
		_In_ NULL,
		_In_opt_ & dwPid
	);

	BOOL bClosed = CloseHandle(
		_In_ gThreadId
	);

	if (!bClosed)
		std::operator<<(std::cout, "Erro ao fechar o HANDLE: ").operator<<(GetLastError()).operator<<(std::endl);

	bClosed = CloseHandle(
		_In_ gThreadId2
	);

	if (!bClosed)
		std::operator<<(std::cout, "Erro ao fechar o HANDLE: ").operator<<(GetLastError()).operator<<(std::endl);

	return 0;
}