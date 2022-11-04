#include <iostream>
#include <windows.h>

auto main(void) -> int
{
	BOOL bMove = MoveFile(
		_In_ L"C:\\MyDir\\a.txt",
		_In_ L"C:\\MyDir\\Moved.txt"
	);

	if (!bMove)
		std::operator<<(std::cout, "Erro ao mover arquivo ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao mover o arquivo !").operator<<(std::endl);

	return 0;
}