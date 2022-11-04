#include <iostream>
#include <windows.h>

auto main(void) -> int
{
    /*
    Hardlink
        1 - Um arquivo pode ter dois diferentes nomes
        2 - Hardlink somente pode ser criado para arquivos e não para diretórios
        3 - Se você excluir o arquivo original, então ele podera ser acessivel via um hardlink do arquivo
        4 - Isso é criado na memória(Memória Física)
    */

    BOOL hFile = CreateHardLink(
        _In_ L"C:\\Mydir\\a.txt",
        _In_ L"C:\\MyDir\\arquivo.txt",
        _In_ NULL
    );

    if (!hFile)
        std::operator<<(std::cout, "Erro ao criar um hardlink").operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar hardlink").operator<<(std::endl);

    return 0;
}