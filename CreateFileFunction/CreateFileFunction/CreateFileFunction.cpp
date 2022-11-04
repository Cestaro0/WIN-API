#include <iostream>
#include <Windows.h>

auto main(void) -> int
{
	HANDLE hFile = CreateFile(
		_In_ L"C:\\MyDir\\file.txt",
		_In_ GENERIC_READ | GENERIC_WRITE,
		_In_ FILE_SHARE_READ | FILE_SHARE_WRITE,
		_In_opt_ NULL,
		_In_ CREATE_NEW,
		_In_ FILE_ATTRIBUTE_NORMAL,
		_In_opt_ NULL
	);

	if (hFile == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "O handle para o arquivo não foi aberto").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "O arquivo foi criado com sucesso").operator<<(std::endl);

	//	<summary>
	//		Write File 
	//	</summary>
	
	char buff[]{ "Olá mundo real!" };
	DWORD dwNumbBytesBuff = strlen(buff);
	DWORD dwNumbBytesWrite = 0;

	BOOL bFile = WriteFile(
		_In_ hFile,
		_In_ buff,
		_In_ dwNumbBytesBuff,
		_Out_opt_ &dwNumbBytesWrite,
		_Out_opt_ NULL
	);

	if (!bFile)
		std::operator<<(std::cout, "O arquivo não foi escrito").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao escrever no arquivo, bytes escritos: ").operator<<(dwNumbBytesWrite).operator<<(std::endl);

	//	<summary>
	//		Read File
	//	</summary>

	bFile = ReadFile(
		_In_ hFile,
		_Out_ buff,
		_In_ dwNumbBytesBuff,
		_Out_opt_ &dwNumbBytesWrite,
		_Inout_ NULL
	);

	if (!bFile)
		std::operator<<(std::cout, "O arquivo não foi lido corretamente").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao ler o arquivo").operator<<(std::endl);
	std::cout << buff << std::endl;

	BOOL bClose = CloseHandle(
		_In_ hFile
	);

	if (!bClose)
		std::operator<<(std::cout, "Não foi possivel fechar o handle").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "O handle foi fechado com sucesso").operator<<(std::endl);
	
	return 0;
}