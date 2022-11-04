#include <iostream>
#include <windows.h>
#include <winsock.h>

auto main(void) -> int
{
        /*
        Programando o socket do Windows
    
         O que é o socket:
            Socket é um endpoint no qual é usado para comunicação entre dois nós de rede.
            Socket é uma interface que segue a arquitetura cliente-servidor
                            Socket
            [ Server ]    ---------------  [Cliente]
        Tipos de socket:
            - Sockets de internet
            - Unix sockets
            - x.25 sockets entre outros.
        Internet sockets:
            Internet socket é caracterizado por um endereço ip(4 Bytes) e uma porta(2 bytes)
            é um protocolo de transporte
        Tipos:
            1. Sockets de stream(Stream Sock)
                i. Orientado a conexão
                ii. Confiar no TCP que provê dois caminhos de conexão
            2. Sockets de datagram(Dgram Sock)
                i. A conexão não é confiável
                ii. Confiar no UDP
        User Datagram Protocol:
            1. Orientado a mensagem
            2. perdas de conexão por exemplo: sem conexão ou manutenções
            3. Tamanho pequeno(Cabeçalho do UDP é 60% menor que o cabeçalho do TCP)
            4. Pequeno tamanho do pacote, cabeçalho do UDP tem 8 Bytes.
            5. Não possui detecção de erros
            6. Se perder data então não é possivel recuperar
            7. Dados corrompidos podem ser descartados conforme a ordem
            8. Exemplo é um e-mail
            [ABCDE] ----------------------> [ABDE]
                                             [C]
       Protocolo de conexão:
        Servidor                  Cliente
           [Socket]                 [Socket]
           [Bind]                   [Bind]
           [Recv]                   [Send]
           [Send]                   [Recv]
           [Close]                  [Close]
        Passos para programar o UDP:
            Servidor:                                                                               Cliente:
                [WSAStartUp]                                                                             [WSAStartUp]
                [Preencher a struct do cliente Cliente ou Servidor]                                      [Preencher a struct do cliente ou servidor]
                [Socket]                                                                                 [Socket]
                [Bind]                                                                                   [Send e Recv]
                [Recv e send]                                                                            [CloseSocket]
                [closesocket]                                                                            [WSACleanUp]
                [WSACleanUp]
    */

    WSADATA wSocketData{ 0 };
    
    SOCKET uDPSocketServer{ 0 };
    struct sockaddr_in UDPCliente { 0 };

    char buffer[512]{ 0 };
    int iBufferLen = sizeof(buffer);

    int iUDPClienteLen = sizeof(UDPCliente) + 1;
    
    int iWsaStartup = WSAStartup(
        _In_ MAKEWORD(2, 2),
        _Out_ &wSocketData
    );

    if (iWsaStartup != 0)
        std::operator<<(std::cout, "Falhou em iniciar o socket com WSAStartup !\n");

    std::operator<<(std::cout, "Sucesso ao criar socket com WSAStartup !\n");

    UDPCliente.sin_family = AF_INET;

    UDPCliente.sin_addr.S_un.S_addr = inet_addr(
        _In_ "127.0.0.1"
    );

    UDPCliente.sin_port = htons(
        _In_ 8001
    );

    uDPSocketServer = socket(
        _In_ AF_INET,
        _In_ SOCK_DGRAM,
        _In_ IPPROTO_UDP
    );

    if (uDPSocketServer == INVALID_SOCKET)
        std::operator<<(std::cout, "Falhou em iniciar o socket: !").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao criar socket !\n");

    int iBind = bind(
        _In_ uDPSocketServer,
        _In_reads_bytes_(UDPCliente) (SOCKADDR*) &UDPCliente,
        _In_ sizeof(UDPCliente)
    );

    if (iBind == SOCKET_ERROR)
        std::operator<<(std::cout, "O Bind falhou ao ser efetuado: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fazer o bind !\n");

    int iReceiveFrom = recvfrom(
        _In_ uDPSocketServer,
        _Out_ buffer,
        _In_ iBufferLen,
        _In_ MSG_PEEK,
        _Out_writes_bytes_to_opt_(*iUDPClienteLen, *iUDPClienteLen) (SOCKADDR*) &UDPCliente,
        _In_opt_z_ &iUDPClienteLen
    );

    if (iReceiveFrom == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao receber: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao receber dados !\n");

    std::printf("Recebido: %s\n", buffer);

    int iCloseSocket = closesocket(
        _In_ uDPSocketServer 
    );

    if (iCloseSocket == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao fechar socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao fechar socket !\n");

    int iWsaCleanup = WSACleanup(
    );

    if (iWsaCleanup == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao limpar socket: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao limpar o socket !\n");

    return 0;
}