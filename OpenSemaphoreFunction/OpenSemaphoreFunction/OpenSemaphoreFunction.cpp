#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	HANDLE hSem = OpenSemaphore(
		_In_ SEMAPHORE_ALL_ACCESS,
		_In_ FALSE,
		_In_ L"MySemaphore"
	);

	if (!hSem)
		std::operator<<(std::cout, "Erro ao abrir semaphore nomeado: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao abrir o semaphore nomeado ").operator<<(std::endl);

	BOOL bClosed = CloseHandle(
		_In_ hSem
	);

	if (!bClosed)
		std::operator<<(std::cout, "Erro ao fechar handle").operator<<(GetLastError()).operator<<(std::endl);

	return 0;
}