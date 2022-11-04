#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	/*
		1º Mutex é um mecanismo de bloqueio
		2º Mutex tem somente um estado entre locked e unlocked
		3º Mutex tem dois "proprietarios" o que adiquire o lock e o que libera o lock
		4º Se o mutex é locked com NON-RECURSIVE um deadlock vai ocorrer
		5º Mutex só é usado para sincronização de thread
		6º No Windows:
		   i. Mutex nomeada
		   ii. Mutex não nomeada
	*/

	HANDLE hMutex = CreateMutex(
		_In_opt_ NULL,
		_In_ FALSE,
		_In_opt_ NULL	//Mutex não nomeado
	);

	if (hMutex == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "Não foi possível criar o mutex: ").operator<<(GetLastError()).operator<<(std::endl);
	
	std::operator<<(std::cout, "Sucesso ao criar o mutex ").operator<<(std::endl);

	if (!CloseHandle(
		_In_ hMutex
	))
		std::operator<<(std::cout, "O handle para o mutex não pode ser fechado: ").operator<<(GetLastError()).operator<<(std::endl);

	//Exemplo com o mutex nomeado

	hMutex = CreateMutex(
		_In_opt_ NULL,
		_In_ FALSE,
		_In_opt_ L"MeuMutex"
	);

	if (hMutex == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "Não foi possível criar o mutex: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao criar o mutex !").operator<<(std::endl);

	std::cin.get();

	if (!CloseHandle(
		hMutex
	))
		std::operator<<(std::cout, "O Handle para o mutex não pode ser fechado: ").operator<<(GetLastError()).operator<<(std::endl);

	return 0;
}