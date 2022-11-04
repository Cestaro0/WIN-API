#include <iostream>
#include <Windows.h>

auto main(void) -> int
{
	HANDLE hFileMap = OpenFileMapping(
		_In_ FILE_MAP_ALL_ACCESS,
		_In_ FALSE,
		_In_ L"Local\\KeowuFileMapp"
	);

	PCHAR buffer = (PCHAR)MapViewOfFile(
		_In_ hFileMap,
		_In_ FILE_MAP_ALL_ACCESS,
		_In_ 0,
		_In_ 0,
		_In_ 256
	);
	
	if (!buffer)
		std::operator<<(std::cout, "Não foi possível mapear arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso em mapear arquivo !").operator<<(std::endl);

	std::printf("Enviado do servidor -> %s", buffer);

	BOOL bUnmapFile = UnmapViewOfFile(
		_In_ buffer
	);

	if (!bUnmapFile)
		std::operator<<(std::cout, "Não foi possível fazer unmap do arquivo: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso em unmapear arquivo !").operator<<(std::endl);

	if (!CloseHandle(
		hFileMap
	))
		std::operator<<(std::cout, "O Handle não pode ser fechado: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao fechar o handle !").operator<<(std::endl);

	return 0;
}