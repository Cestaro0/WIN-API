#include <iostream>
#include <windows.h>

auto WINAPI MinhaThread(LPVOID params) -> DWORD
{
	while (TRUE)
		std::operator<<(std::cout, "Poxa Brother tou preso no loop, vou ficar ruim da cabeca assim!").operator<<(std::endl);

	return 0;

}

auto main(void) -> int
{
	DWORD hTid = 0;

	HANDLE hThread = CreateThread(
		_In_opt_ NULL,
		_In_ 100,
		_In_ MinhaThread,
		_In_opt_ NULL,
		_In_ NULL,
		_Out_opt_ &hTid
	);

	if (hThread == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "Não foi possivel criar a thread: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao criar a thread, para mata-la pressione qualquer tecla").operator<<(std::endl);

	std::cin.get();

	std::operator<<(std::cout, "Matei a thread: ").operator<<(std::hex).operator<<(hTid).operator<<(std::endl);
	
	BOOL bThread = TerminateThread(
		_Inout_  hThread,
		_In_ 0x00
	);

	if (!bThread)
		std::operator<<(std::cout, "A thread nao pode ser encerrada: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "A thread foi encerrada com sucesso ").operator<<(std::endl);

	BOOL bClosed = CloseHandle(
		_In_ hThread
	);

	if (!bClosed)
		std::operator<<(std::cout, "Não foi possivel fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Handle foi fechado com sucesso ").operator<<(std::endl);

	hThread = CreateThread(
		_In_opt_ NULL,
		_In_ 100,
		_In_ MinhaThread,
		_In_opt_ NULL,
		_In_ CREATE_SUSPENDED,
		_Out_opt_ &hTid
	);

	if (hThread == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "Não foi possivel encontrar o processo, erro: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao criar a thread ").operator<<(std::endl);

	std::operator<<(std::cout, "Aperte um tecla para iniciar a tecla que estava em espera").operator<<(std::endl);

	std::cin.get();

	if (!ResumeThread(
		_In_ hThread
	) == -1)
		std::operator<<(std::cout, "Sucesso ao criar a thread ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao resumar a thread").operator<<(std::endl);

	return 0;
}