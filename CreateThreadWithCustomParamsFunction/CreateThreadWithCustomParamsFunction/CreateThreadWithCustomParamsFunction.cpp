#include <iostream>
#include <windows.h>

typedef struct blastruct 
{
	std::int32_t idade;
	bool isInfeliz;
};

auto WINAPI MinhaThread(LPVOID params)-> DWORD
{
	auto bla = *reinterpret_cast<blastruct*>(params);
	
	std::printf("\nIdade: %d, Feliz: %d", bla.idade, bla.isInfeliz);
	
	return 0;
}

auto main(void) -> int 
{
	DWORD dwTid;

	blastruct* bla = reinterpret_cast<blastruct*>(malloc(sizeof(blastruct)));

	ZeroMemory(bla, sizeof(bla));

	bla->idade = 400;

	bla->isInfeliz = false;

	HANDLE hThread = CreateThread(
		_In_opt_ NULL,
		_In_ 0,
		_In_ MinhaThread,
		_In_opt_(void*)bla,
		_In_ NULL,
		_Out_opt_ & dwTid
	);

	if (hThread == INVALID_HANDLE_VALUE)
		std::operator<<(std::cout, "Ocorreu um erro ao abrir um handle para a trhead: ").operator<<(GetLastError()).operator<<(std::endl);

	std::operator<<(std::cout, "Sucesso ao criar um handle para a thread, ela comecou a executar !");

	return 0;
}