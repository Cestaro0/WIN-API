#include <iostream>
#include <windows.h>

auto main(void) -> int
{
    /*
        Semaphore:
            1 - Semaphore é uma variável inteira (Mutex é um objeto)
            2 - Semaphore é um mecanismo de signals (Mutex é um mecanismo de locking)
            3 - No Semaphore o valor pode ser modificado usando operações WAIT & SIGNAL (Mutex - Somente Locked e Unlocked)
            4 - Semaphore tem dois tipos (Mutex não tem categoria)
                i. Semaphore Binário(Binary Semaphore)
                ii. Semaphor de contagem(Counting Semaphore)
            5 - O valor de um Semaphore pode ser modiciado por um processo adquirindo ou liberando o Semaphore
                (Mutex - Somente quem adquiriu o lock pode fazer unlocking por exemplo um Mutual Ownership)
    */
    
    HANDLE hSemaphore = CreateSemaphore(
        _In_opt_ NULL,
        _In_ 1,
        _In_ 1,
        _In_opt_ L"MySemaphore"//NULL
    );

    if (!hSemaphore)
        std::operator<<(std::cout, "Erro ao criar unamed semaphore: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar unamed semaphore ").operator<<(std::endl);

    BOOL bClosed = CloseHandle(
        _In_ hSemaphore
    );

    if (!bClosed)
        std::operator<<(std::cout, "Erro ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::cin.get();

    hSemaphore = CreateSemaphore(
        _In_opt_ NULL,
        _In_ 1,
        _In_ 1,
        _In_opt_ L"MySemaphore"
    );

    if (!hSemaphore)
        std::operator<<(std::cout, "Erro ao criar semaphore named: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Semaphore named criado com sucesso ").operator<<(std::endl);

    bClosed = CloseHandle(
        _In_ hSemaphore
    );

    if (!bClosed)  
        std::operator<<(std::cout, "Erro ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);
     
    return 0;
}