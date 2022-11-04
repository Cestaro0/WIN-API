#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	HANDLE hFileMailSlots = CreateFile(
		_In_ L"\\\\.\\mailslot\\Cestaro",
		_In_ GENERIC_READ | GENERIC_WRITE,
		_In_ 0,
		_In_opt_ NULL,
		_In_ OPEN_EXISTING,
		_In_ FILE_ATTRIBUTE_NORMAL,
		_In_opt_ NULL
	);

	if (hFileMailSlots == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "falhou ao criar o handle para obter o mailslots: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao obter o handle para o mailslots").operator<<(std::endl);

	char cBufferToWrite[44]{ "Olá mundo do Cestaro atraves do MailSlots" };
	DWORD dwBufferSizeWrite = sizeof(cBufferToWrite);
	DWORD dwNumberOfBytesWrittern = 0;

	BOOL bWriteFile = WriteFile(
		_In_ hFileMailSlots,
		_In_ cBufferToWrite,
		_In_ dwBufferSizeWrite,
		_Out_opt_ &dwNumberOfBytesWrittern,
		_In_opt_z_ NULL
	);

	if (!bWriteFile)
		std::operator<<(std::cout, "Falhou em escrever no MailSlots").operator<<(GetLastError()).operator<<(std::endl);
	
	std::operator<<(std::cout, "Sucesso ao escrever no MailSlots").operator<<(std::endl);

	BOOL bClose = CloseHandle(
		_In_ hFileMailSlots
	);

	if (!bClose)
		std::operator<<(std::cout, "Falha ao fechar o handle").operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao fechar o handle").operator<<(std::endl);

	return 0;
}