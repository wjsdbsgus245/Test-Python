#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <winsock2.h>
#include <conio.h>

#define BUFSIZE 1024

void ErrorHandling(LPVOID);

int _tmain(int argc, TCHAR *argv[])
{
    WSADATA wsaData;
    SOCKET clntSock;
    SOCKADDR_IN servAddr;

    TCHAR message[BUFSIZE];
    int strLen;
    int fromLen, nRcv;

    if(argc != 3)
    {
        _tprintf("Please, Insert IP Address AND Port Number \n");
        exit(1);
    }

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("Load WinSock 2.2 DLL error");

    clntSock = socket(PF_INET, SOCK_STREAM, 0);
    if(clntSock == INVALID_SOCKET)
        ErrorHandling("Client Sock Error");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(connect(clntSock, (void *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("Connection Error");
    else
    {
        _tprintf(_T("Connect OK! \n"));
        _tprintf(_T("Start... \n"));
    }

    while(1)
    {
        _tprintf(_T("Send Message : "));
        gets(message);

        if(_tcscmp(message, "exit") == 0)
        {
            send(clntSock, message, (int)_tcslen(message), 0);
            break;
        }

        send(clntSock, message, (int)_tcslen(message), 0);
        _tprintf(_T("Message Recevies ... \n"));

        nRcv = recv(clntSock, message, sizeof(message) - 1, 0);
        if(nRcv == SOCKET_ERROR)
        {
            _tprintf("Receive Error ... \n");
            break;
        }

        message[nRcv] = '\0';
        if(_tcscmp(message, "exit") == 0)
        {
            _tprintf(_T("Close Server Connection .. \n"));
            break;
        }

        _tprintf(_T("Receive Message : %s \n"), message);
    }

    closesocket(clntSock);
    WSACleanup();

    _tprintf(_T("Close Connection.. \n"));
    _getch();

    return 0;
}

void ErrorHandling(LPVOID message)
{
    WSACleanup();
    fputs((char *)message, stderr);
    fputc('\n', stderr);
    _getch();
    exit(1);
}