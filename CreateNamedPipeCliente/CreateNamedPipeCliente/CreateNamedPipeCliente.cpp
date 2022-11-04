#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	HANDLE hCreateFile = CreateFile(
		_In_ L"\\\\.\\pipe\\CestaroPipe",
		_In_ GENERIC_READ | GENERIC_WRITE,
		_In_ 0,
		_In_opt_ NULL,
		_In_ OPEN_EXISTING,
		_In_ FILE_ATTRIBUTE_NORMAL,
		_In_opt_ NULL
	);

	if (hCreateFile == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "Erro ao criar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Handle aberto com sucesso ").operator<<(std::endl);

	DWORD dwNumberBytesWrite = 0;
	char cBufferWrite[25]{ "Olá mundo, from Cestaro" };
	DWORD dwSizeOfBuffer = sizeof(cBufferWrite);

	BOOL bWriteFile = WriteFile(
		_In_ hCreateFile,
		_In_ cBufferWrite,
		_In_ dwSizeOfBuffer,
		_Out_opt_ & dwNumberBytesWrite,
		_In_opt_z_ NULL
	);

	if (!bWriteFile)
		std::operator<<(std::cout, "Erro ao escrever o arquivo pipe: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao escrever o arquivo pipe ").operator<<(std::endl);

	DWORD dwNumberBytesRead = 0;
	char cBufferRead[1024]{ 0 };
	DWORD dwSizeOfBufferRead = sizeof(cBufferRead);

	BOOL bReadFile = ReadFile(
		_In_ hCreateFile,
		_Out_ cBufferRead,
		_In_ dwSizeOfBufferRead,
		_Out_opt_ & dwNumberBytesRead,
		_In_opt_z_ NULL
	);

	if (!bReadFile)
		std::operator<<(std::cout, "Não foi possível ler o arquivo pipe: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao ler o arquivo pipe ").operator<<(std::endl);

	std::printf("Dados obtidos pelo cliente (este) do servidor (pipe server): %s", cBufferRead);

	std::cin.get();

	return 0;
}