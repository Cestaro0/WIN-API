#include <iostream>
#include <windows.h>

auto main(void) -> int 
{
	BOOL bCpyFile = CopyFile(
		_In_ L"C:\\MyDir\\File.txt", 
		_In_ L"C:\\MyDirNew\\FileCopy.txt", 
		_In_ TRUE
	);

	if (!bCpyFile)
		std::operator<<(std::cout, "Erro ao copiar o arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao copiar o arquivo ").operator<<(std::endl);

	std::cin.get();

	return 0;
}