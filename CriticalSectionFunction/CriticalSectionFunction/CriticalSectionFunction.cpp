#include <iostream>
#include <windows.h>

int GCount = 1;

CRITICAL_SECTION GCriticalSection { 0 };

auto WINAPI FuncEven(LPVOID params) -> DWORD 
{
	while (GCount < 10) 
	{
		EnterCriticalSection(
			_Inout_ &GCriticalSection
		);
		
		if (GCount % 2 == 0)
			std::cout << "Par -> " << GCount++ << std::endl;

		LeaveCriticalSection(
			_Inout_ &GCriticalSection
		);
	}
	
	return 0;

}

auto WINAPI FuncOdd(LPVOID params) -> DWORD
{
	while (GCount < 10) 
	{
		EnterCriticalSection(
			_Inout_ &GCriticalSection
		);

		if (GCount % 2 == 1)
			std::cout << "Ímpar -> " << GCount++ << std::endl;

		LeaveCriticalSection(
			_Inout_ &GCriticalSection
		);
	}
	
	return 0;

}

auto main(void) -> int 
{
    /*
        Critical Section no Windows
        Seção creitica é uma região de código que precisa ser executada atomicamente ou com operação indivisivel
        Seção critica usada para sincronização
        Isso provê um "lock" similar ao do mutex
        O Processo só é responsável por alocar memória usada pelo critical section.
        Exemplo:
        do {
            Entry_Section();
            //CRITICAL_SECTION
            Exit_Section();
        }while(TRUE);
        Diferenças entre o CRITICAL_SECTION e o MUTEX
        Critical section:
            1. Objeto C.S não é compartilhado pelo processo
            2. C.S é usado por somente uma thread de um processo
            3. Ele não consegue comunicar com o kernel
            4. É consideravelmente mais rápido que Event, Mutex e Semaphore
            
        Mutex:
            1. Objeto Mutex é compartilhado pelos processos
            2. É usado em mais de um processo
            3. Ele pode comunicar com o Kernel
            4. Ele é lento e pode ocasionar um risco de deadlock
        Critical Section API's:
            1. InitializeCriticalSection
            2. InitializeCriticalSectionAndSpinCount
            3. EnterCriticalSection
            4. TryEnterCriticalSection
            5. LeaveCriticalSection
            6. SetCriticalSectionSpinCount
            7. DeleteCriticalSection
*/

    InitializeCriticalSection(
        _Out_ &GCriticalSection
    );

    HANDLE hThread = CreateThread(
        _In_opt_ NULL,
        _In_ 0,
        _In_ FuncEven,
        _In_opt_ __drv_aliasesMem NULL,
        _In_ 0,
        _Out_opt_ 0
    );

    if (hThread == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou ao criar a thread: ").operator<<(GetLastError());

    std::operator<<(std::cout, "Sucesso ao criar a thread !\n");

    HANDLE hThread2 = CreateThread(
        _In_opt_ NULL, 
        _In_ 0,
        _In_ FuncOdd, 
        _In_opt_ __drv_aliasesMem NULL, 
        _In_ 0,
        _Out_opt_ 0 
    );

    if (hThread2 == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou ao criar a thread: ").operator<<(GetLastError());

    std::operator<<(std::cout, "Sucesso ao criar a thread !\n");

    DWORD dwWaitForSingle = WaitForSingleObject(
        _In_ hThread,
        _In_ INFINITE   
    );
    
    if (dwWaitForSingle == WAIT_FAILED)
        std::operator<<(std::cout, "Falhou ao esperar pelo objeto: ").operator<<(GetLastError());
    
    dwWaitForSingle = WaitForSingleObject(
        _In_ hThread2,
        _In_ INFINITE
    );

    if (dwWaitForSingle == WAIT_FAILED)
        std::operator<<(std::cout, "Falhou ao esperar pelo objeto: ").operator<<(GetLastError());
    
    if (!CloseHandle(
        _In_ _Post_ptr_invalid_ hThread 
    ))
        std::operator<<(std::cout, "Falhou ao fechar o HANDLE !\n");
    
    if (!CloseHandle(
        _In_ _Post_ptr_invalid_ hThread2
    ))
        std::operator<<(std::cout, "Falhou ao fechar o HANDLE !\n");
    
    DeleteCriticalSection(
        _Inout_ &GCriticalSection
    );

    return 0;
}