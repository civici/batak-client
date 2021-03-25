#include "network.h"


SOCKET openconn()
{
    char* host = "localhost";
    char* port = "54322";

    WSADATA wsaData = {0};

    WSAStartup(MAKEWORD(2,2), &wsaData);

    struct addrinfo hints, *result;
    ZeroMemory(&hints, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(host, port, &hints, &result) != 0)
    {
        puts("getaddrinfo failed");
        exit(0);
    }

    SOCKET fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    int flag = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(int));

    if (fd == INVALID_SOCKET)
    {
        puts("socket failed");
        exit(0);
    }

    if (connect(fd, result->ai_addr, (int) result->ai_addrlen) != 0)
    {
        puts("connect failed");
        int err = WSAGetLastError();
        printf("err %d\n", err);
        exit(0);
    }
    return fd;
}