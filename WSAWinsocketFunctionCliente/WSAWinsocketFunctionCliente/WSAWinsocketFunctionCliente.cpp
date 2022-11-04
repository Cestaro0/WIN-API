#include <iostream>
#include <windows.h>
#include <winsock.h>

auto main(void) -> int
{
	//Para compilar vá em Vinculador -> input -> Dependências adicionais -> editar -> coloque WS2_32.lib
	
    WSADATA wSocketData{ 0 };

    SOCKET uDPSocketServer{ 0 };
    struct sockaddr_in UDPServer { 0 };

    char buffer[512]{ "Ola mundo !! Do Cestaro, HELLO WORLD FROM CESTARO !! " };
    int iBufferLen = sizeof(buffer) + 1;

    int iUDPServerLen = sizeof(UDPServer) + 1;

   int iWsaStartup = WSAStartup(
        _In_ MAKEWORD(2, 2), 
        _Out_ & wSocketData 
    );

    if (iWsaStartup != 0)
        std::operator<<(std::cout, "Falhou em iniciar o socket com WSAStartup !\n");

    std::operator<<(std::cout, "Sucesso ao criar socket com WSAStartup !\n");

    UDPServer.sin_family = AF_INET;
    
    UDPServer.sin_addr.S_un.S_addr = inet_addr(
        _In_ "127.0.0.1" 
    );
    
    UDPServer.sin_port = htons(
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

    int iSendFrom = sendto(
        _In_ uDPSocketServer,
        _In_ buffer,
        _In_ iBufferLen, 
        _In_ MSG_DONTROUTE, 
        _In_(SOCKADDR*) &UDPServer, 
        _In_ iUDPServerLen
    );

    if (iSendFrom == SOCKET_ERROR)
        std::operator<<(std::cout, "Erro ao enviar: ").operator<<(WSAGetLastError()).operator<<("\n");

    std::operator<<(std::cout, "Sucesso ao enviar dados !\n");

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