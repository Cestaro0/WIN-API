#include <iostream>
#include <windows.h>

auto main(void) -> int
{
    /*
        1 - Um arquivo pode ter diferentes nomes
        2 - Soft link pode ser criado para arquivos e diretórios
        3 - Se o arquivo original for excluído, então vou não pode acessar o arquivo soft link  
        4 - Soft link é um atalho para o arquivo original
    */

    BOOL bSym = CreateSymbolicLink(
        _In_ L"C:\\MyDir\\Moved.txt",
        _In_ L"C:\\MyDir\\WMoved2.txt",
        _In_ NULL       // 0(NULL) para arquivos, SYMBOLIC_LINK_FLAG_DIRECTORY(Para diretórios)
    );

    if (!bSym)
        std::operator<<(std::cout, "Falhou ao criar o symboliclink ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o symboliclink !").operator<<(std::endl);

    return 0;
}