#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	/*
		Definição de processos:
			- Um programa em execução é chamado de processo
					ou
			- Processo é uma estrutura de dados que armazena informações sobre seu estado na memória
				1º CreateProcess - Cria um novo processo
				2º GetProcessID - obtem o PID do processo
				3º GetThreadID - obtem o TID do processo
				4º WaitForSingleObject - Espera um signal
				5º CloseHandle - fecha um processoe sua thread primária
	*/

	HANDLE hProc;
	HANDLE hTrhead;

	STARTUPINFO sInfo{ 0 };

	PROCESS_INFORMATION pInfo{ 0 };

	ZeroMemory(
		_In_ &sInfo,
		_In_ sizeof(sInfo)
	);

	ZeroMemory(
		_In_ &pInfo,
		_In_ sizeof(pInfo)
	);

	BOOL bProc = CreateProcess(
		_In_opt_ L"C:\\MyDir\\PortableExe.exe",
		_In_opt_z_  NULL,
		_In_opt_ NULL,
		_In_opt_ NULL,
		_In_ FALSE,
		_In_ NORMAL_PRIORITY_CLASS,
		_In_ NULL,
		_In_opt_ NULL,
		_In_ &sInfo,
		_Out_ &pInfo
	);

	if (!bProc)
		std::operator<<(std::cout, "Não foi possivel criar o processo, erro obtido: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "O Processo foi criado com sucesso !").operator<<(std::endl);

	std::operator<<(std::cout, "PID(PROCESS ID): ").operator<<(std::hex).operator<<(pInfo.dwProcessId).operator<<(std::endl);

	std::operator<<(std::cout, "TID(Thread ID): ").operator<<(std::hex).operator<<(pInfo.dwThreadId).operator<<(std::endl);

	std::operator<<(std::cout, "PID(WINAPI): ").operator<<(std::hex).operator<<(GetProcessId(pInfo.hProcess)).operator<<(std::endl);

	std::operator<<(std::cout, "TID(WINAPI): ").operator<<(std::hex).operator<<(GetThreadId(pInfo.hThread)).operator<<(std::endl);


	WaitForSingleObject(
		_In_ pInfo.hProcess,
		_In_ 10
	);

	CloseHandle(
		_In_ pInfo.hProcess
	);

	CloseHandle(
		_In_ pInfo.hThread
	);

	std::cin.get();

	return 0;
}