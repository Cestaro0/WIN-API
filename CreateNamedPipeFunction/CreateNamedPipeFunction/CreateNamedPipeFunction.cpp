#include <iostream>
#include <windows.h>

auto main(void) -> int
{
    /*
        Named Pipe
            1. Named Pipe é bidirecional ou unidirecional ou Full Duplex
            2. Pode-se fazer simultaneamente operações leitura e escrita
            3. Named Pipe é usado pra sobrepor a rede
            4. é uma extenção do Pipe Tradicional
            Passos para programar:

                Servidor:                                                         Cliente:
                1. Criar um pipe nomeado (CreateNamedPipe)                        1. CreateFile ou CallNamedPipe
                2. ConnectNamedPipe                                               2. WriteFile/ReadFile/TransactNamedPipe
                3. WriteFile ou ReadFile                                          3. CloseHandle
                4. FlushFileBuffers
                5. DisconnectNamedPipe
                6. CloseHandle
    */

    BOOL bWriteFile = 0;
    char cWriteFileBuffer[26]{ "Hello world from Cestaro" };
    DWORD dwWriteBufferSize = sizeof(cWriteFileBuffer);
    DWORD dwBytesWritten = 0;

    BOOL bReadFile = 0;
    char cReadFileBuffer[1024]{ 0 };
    DWORD dwReadBufferSize = sizeof(cReadFileBuffer);
    DWORD dwReadBytes = 0;

    char cInputBuffer[1024]{ 0 };
    char cOutputBuffer[1024]{ 0 };
    DWORD dwSizeInputBuffer = sizeof(cInputBuffer);
    DWORD dwSizeOutputBuffer = sizeof(cOutputBuffer);

    HANDLE hCreateNamedPipe = CreateNamedPipe(
        _In_ L"\\\\.\\pipe\\CestaroPipe",
        _In_ PIPE_ACCESS_DUPLEX,
        _In_ PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        _In_ PIPE_UNLIMITED_INSTANCES,
        _In_ dwSizeOutputBuffer,
        _In_ dwSizeInputBuffer,
        _In_ 0,
        _In_opt_ NULL
    );

    if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
        std::operator<<(std::cout, "Falhou ao criar o pipe: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao criar o pipe ").operator<<(std::endl);

    BOOL bConnectedNamedPipe = ConnectNamedPipe(
        _In_ hCreateNamedPipe,
        _In_opt_z_ NULL
    );

    if (!bConnectedNamedPipe)
        std::operator<<(std::cout, "Falha ao conectar no pipe: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao conectar ao pipe ").operator<<(std::endl);

    bWriteFile = WriteFile(
        _In_ hCreateNamedPipe,
        _In_ cWriteFileBuffer,
        _In_ dwWriteBufferSize,
        _Out_opt_ &dwBytesWritten,
        _In_opt_z_ NULL
    );

    if (!bWriteFile)
        std::operator<<(std::cout, "Não foi possivel escrever: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao escrever ").operator<<(std::endl);

    BOOL bFlush = FlushFileBuffers(
        _In_ hCreateNamedPipe
    );

    if (!bFlush)
        std::operator<<(std::cout, "Não foi possivel fazer o flush do buffer").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fazer o flush do buffer ").operator<<(std::endl);

    bReadFile = ReadFile(
        _In_ hCreateNamedPipe,
        _Out_ cReadFileBuffer,
        _In_ dwReadBufferSize,
        _Out_opt_ &dwReadBytes,
        _In_opt_z_ NULL
    );

    if (!bReadFile)
        std::operator<<(std::cout, "Não foi possivel ler: ").operator<<(GetLastError()).operator<<(std::endl);
    
    std::operator<<(std::cout, "Sucesso ao ler ").operator<<(std::endl);

    std::printf("Dados do cliente: %s\n", cReadFileBuffer);

    BOOL bDisconnect = DisconnectNamedPipe(
        _In_ hCreateNamedPipe
    );

    if (!bDisconnect)
        std::operator<<(std::cout, "Falhou ao desconectar: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao desconectar ").operator<<(std::endl);

    BOOL bClose = CloseHandle(
        _In_ hCreateNamedPipe
    );

    if (!bClose)
        std::operator<<(std::cout, "Falhou ao fechar o handle: ").operator<<(GetLastError()).operator<<(std::endl);

    std::operator<<(std::cout, "Sucesso ao fechar o handle ").operator<<(std::endl);

    return 0;
}