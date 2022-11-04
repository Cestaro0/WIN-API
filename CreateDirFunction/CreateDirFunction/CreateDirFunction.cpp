#include <iostream>
#include <windows.h>

auto main(void) -> int 
{
	BOOL bDir = CreateDirectory(
		_In_ L"C:\\MyDir\\NewDir",
		_In_opt_ NULL
	);

	if (!bDir) 
	{
		DWORD dwErr = GetLastError();
		std::operator<<(std::cout, "Não foi possivel criar o diretorio! ").operator<<(dwErr).operator<<(std::endl);
	}
		
	std::operator<<(std::cout, "O diretorio foi criado com sucesso!").operator<<(std::endl);

	std::cin.get();

	bDir = RemoveDirectory(
		_In_ L"C:\\MyDir\\NewDir"
	);

	if (!bDir) 
	{
		DWORD dwErr = GetLastError();
		std::operator<<(std::cout, "Não foi possivel excluir o diretorio! ").operator<<(dwErr).operator<<(std::endl);
	}

	std::operator<<(std::cout, "O diretorio foi excluido com sucesso!").operator<<(std::endl);

	return 0;
}