#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	HANDLE hReadFile, hWriteFile;
	char cBuff[13]{ "Ola mundo !!" };
	DWORD dwBuffSize = strlen(cBuff), dwWritten;

	BOOL bPipe = CreatePipe(
		_Out_ &hReadFile,
		_Out_ &hWriteFile,
		_In_opt_ NULL,
		_In_ dwBuffSize
	);

	if (!bPipe)
		std::operator<<(std::cout, "Falhou ao criar o pipe: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao criar o pipe: ").operator<<(std::endl);

	bPipe = WriteFile(
		_In_ hWriteFile,
		_In_ cBuff,
		_In_ dwBuffSize,
		_Out_opt_ &dwWritten,
		_In_opt_z_ NULL
	);

	if (!bPipe)
		std::operator<<(std::cout, "Falhou ao escrever o arquivo: ").operator<<(GetLastError()).operator<<(std::endl);
	
	std::operator<<(std::cout, "Sucesso ao escrever o arquivo ").operator<<(std::endl);

	bPipe = CloseHandle(
		_In_ hWriteFile
	);

	if (!bPipe)
		std::operator<<(std::cout, "Falhou ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

	bPipe = ReadFile(
		_In_ hReadFile,
		_Out_ cBuff,
		_In_ dwBuffSize,
		_Out_opt_ &dwWritten,
		_In_opt_z_ NULL
	);

	if (!bPipe)
		std::operator<<(std::cout, "Falhou ao ler o arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao ler o arquivo").operator<<(std::endl);

	bPipe = CloseHandle(
		_In_ hReadFile
	);

	if (!bPipe)
		std::operator<<(std::cout, "Falhou ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

	std::printf("Valor lido pelo pipe -> %s", cBuff);

	return 0;
}