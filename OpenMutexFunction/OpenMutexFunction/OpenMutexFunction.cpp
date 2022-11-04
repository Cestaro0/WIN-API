#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	HANDLE hOpenMutex = OpenMutex(
		_In_ MUTEX_ALL_ACCESS,
		_In_ FALSE,
		_In_ L"MeuMutex"
	);

	if (hOpenMutex == INVALID_HANDLE_VALUE)	
		std::operator<<(std::cout, "Não foi possível abrir o mutex: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao abrir o mutex ").operator<<(std::endl);

	std::cin.get();

	if (!CloseHandle(
		_In_ hOpenMutex
	))
		std::operator<<(std::cout, "O handle para o mutex não foi fechado: ").operator<<(GetLastError()).operator<<(std::endl);

	return 0;
}