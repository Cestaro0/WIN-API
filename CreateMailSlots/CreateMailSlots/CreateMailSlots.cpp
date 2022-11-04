#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	HANDLE hSlots = CreateMailslot(
		_In_ L"\\\\.\\mailslot\\Cestaro",
		_In_ NULL,
		_In_ MAILSLOT_WAIT_FOREVER,
		_In_opt_ NULL
	);

	if (hSlots == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "Erro ao tentar criar o mailsots ").operator<<(GetLastError()).operator<<(std::endl);
	
	std::operator<<(std::cout, "Sucesso ao criar o mailslots").operator<<(std::endl);

	char cBufferRead[1024]{ 0 };
	DWORD dwBufferSizeRead = sizeof(cBufferRead);
	DWORD dwBUfferSizeReaded = 0;

	BOOL bReadFile = ReadFile(
		_In_ hSlots,
		_Out_ cBufferRead,
		_In_ dwBufferSizeRead,
		_Out_opt_ &dwBUfferSizeReaded,
		_In_opt_z_ NULL
	);

	if (!bReadFile)
		std::operator<<(std::cout, "Falha ao ler o arquivo").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "O arquivo foi lido corretamente").operator<<(std::endl);

	std::printf("Cliente retornou: %s \n", cBufferRead);

	BOOL bClose = CloseHandle(
		_In_ hSlots
	);

	if (!bClose)
		std::operator<<(std::cout, "Falha ao fechar o handle").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "O handle foi fechado corretamente").operator<<(std::endl);

	return 0;
}