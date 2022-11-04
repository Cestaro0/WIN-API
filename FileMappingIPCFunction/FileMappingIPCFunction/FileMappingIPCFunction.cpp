#include <iostream>
#include <windows.h>

auto main(void) -> int
{
    /*
    Mapeamento de arquivos intermédio do IPC(Inter comunication process):
        1 - Mapeamento de arquivo é semelhante ao conceito da memória compartilhada
        2 - Mapeamento é local do sistema e não pode ser usado em rede
        3 - Sem que que criamos um objeto de arquivo mapeado esse objeto é tratado como um block e memória compartilhada
        4 - Isso é útil quando informações entre processos mudam com frequencia
            Por exemplo:
                    Suponha que eu tenho muitas informações de recursos então:
                        i. 1º O Processo obtem informações
                        ii. 2º Processo muda essas informações
                        iii. 3º Processo mostrara essas informações na tela
        5 - Sempre que um objeto de arquivo mapeado requer alguma técnica de sincronização outro processo contamina a informação.
        Como funciona o mapeamento de arquivos:
            Temos três maneiras que uma aplicação compartilha um objeto de arquivo mapeado:
                1 - Herança
                2 - Arquivo nomeado mapeado
                3 - Duplicação de Handle
            Exemplo de funcionamento:
                i. 1º O Processo sempre cria um objeto de arquivo mapeado
                ii. 2º Process(filho) obtem um handle do processo pai
        Servidor ou "Pai"                               Cliente ou "Filho"
        1 - CreateFileMapping                           1 - OpenFileMapping
        2 - MapViewOfFile                               2 - MapViewOfFile
        3 - CopyMemory                                  3 - Escrever o conteúdo do arquivo
        4 - UnMapViewOfFile                             4 - UnMapViewOfFile
                                                        5 - CloseHandle
        //Seria Keowu - kernel + Owu
*/

    char BufferMap[38]{ "Hello world, Cestaro Cestaro Cestaro" };
    size_t szBufferMap = sizeof(BufferMap);

    HANDLE hFile = CreateFileMapping(
        _In_ INVALID_HANDLE_VALUE, 
        _In_ NULL, 
        _In_ PAGE_EXECUTE_READWRITE, 
        _In_ 0, 
        _In_ 256, 
        _In_opt_ L"Local\\KeowuFileMapp" 
    );

    if (hFile == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou ao criar handle código: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o handle").operator<<(std::endl);
    
    PCHAR lpBuffer = (PCHAR)MapViewOfFile(
        _In_ hFile,
        _In_ FILE_MAP_ALL_ACCESS,
        _In_ 0,
        _In_ 0,
        _In_ 256
    );

    if (!lpBuffer)
        std::operator<<(std::cout, "Falhou ao usar mapviewoffile: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao usar mapviewoffile !").operator<<(std::endl);

    CopyMemory(
        _In_ lpBuffer,
        _In_ BufferMap,
        _In_ szBufferMap
    );

    BOOL bUnmap = UnmapViewOfFile(
        _In_ lpBuffer
    );

    if (!bUnmap)
        std::operator<<(std::cout, "Falhou ao usar UnmapViewOfFile: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao usar UnmapViewOfFile !").operator<<(std::endl);

    std::cin.get();

    if (!CloseHandle(
        _In_ hFile 
    ))
        std::operator<<(std::cout, "Falhou ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fechar o handle !").operator<<(std::endl);

    return 0;
}