#include <WinSock2.h>
#include <sys/types.h>
#include <string.h>
#include <winsock.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080

int main(int argc, char const* argv[])
{
    WSADATA wsaData; int iResult = 0;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char* hello = "Hello from client";
    char buffer[1024] = { 0 };

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) 
    {
        std::cout << "Error at WSAStartup:" << WSAGetLastError();
        return -1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout <<"\n Socket creation error \n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "\nConnection Failed \n";
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";
    valread = recv(sock, buffer, 1024, MSG_PEEK);
    std::cout << buffer;
    return 0;
}