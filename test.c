#include <stdio.h>      // ���� ����� �������
#include <stdlib.h>
#include <tchar.h>      // ���ڿ� ó�� �������
#include <winsock2.h>   // ���� ��� �������
#include <conio.h>      // _getch �Լ� ���
#include <windows.h>    // ������ �������
#include <process.h>    

#define CLIENT_MAX 100
#define BUFSIZE 1024    // ���� ������ 

void ErrorHandling(LPVOID); // ���� �޼��� ���

unsigned int WINAPI clntConn(LPVOID);   // Ŭ�� ���� �Լ� 
void sendMsg(LPVOID, int);  // �޼��� �Լ�

DWORD clntNumber = 0; // Ŭ�� ��
SOCKET clntSocks[CLIENT_MAX]; // Ŭ�� ���� �迭
HANDLE hMutex;  // ����ȭ �ڵ�

int _tmain(int argc, TCHAR *argv[])
{
    WSADATA wsaData;    // winsock 2.2 DLL �ε�
    SOCKET servSock, clntSock;  // ���� �� Ŭ�� ����
    SOCKADDR_IN servAddr, clntAddr; // ���� �� Ŭ�� ����

    int clntAddrSize;

    HANDLE hTread;  // ������ �ڵ�
    DWORD dwThreadID;   // ������ ���̵�

    // ��Ʈ ��ȣ�� ���� ���ҽ�
    if(argc != 2)
    {
        _tprintf("Please, Insert Port Number \n");
        exit(1);
    }

    // DLL �ε�
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("Load WinSock 2.2 DLL error");

    // ���ؽ� ����ȭ ��ü ����
    hMutex = (HANDLE)CreateMutex(NULL, FALSE, NULL);
    if(hMutex == NULL)
        ErrorHandling("CreatMutex Error");

    // ���� ���� ����
    servSock = socket(PF_INET, SOCK_STREAM, 0);
    if(servSock == INVALID_SOCKET)
        ErrorHandling("Server Sock Error");

    // ������ ���� ������ �ʱ�ȭ
    memset(&servAddr, 0, sizeof(SOCKADDR_IN));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    // ���� ���� ���ε�
    if(bind(servSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("Bind Error");
    
    // Ŭ�� ������ ���
    if(listen(servSock, CLIENT_MAX) == SOCKET_ERROR)
        ErrorHandling("Listen Error");

    while(1)
    {
        // Ŭ�� �ּ� �ޱ�
        clntAddrSize = sizeof(clntAddr);

        // Ŭ�� ���� ���
        clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &clntAddrSize);
        if(clntSock == INVALID_SOCKET)
            ErrorHandling("Accept Error");

        // ����ȭ
        WaitForSingleObject(hMutex, INFINITE);

        // Ŭ�� ���� �迭�� ���� ������ ����, Ŭ�� ���Ӽ��� ����
        clntSocks[clntNumber++] = clntSock;

        // ����ȭ ����
        ReleaseMutex(hMutex);

        // Ŭ�� ���� ������ ���
        _tprintf(_T("New Connect, Client IP : %s \n"), inet_ntoa(clntAddr.sin_addr));
    
        // ������ ����
        hTread = (HANDLE)_beginthreadex(NULL, 0, clntConn, (LPVOID)clntSock, 0, (unsigned *)&dwThreadID);
        if(hTread == 0)
            ErrorHandling("Beginthreadex Error");
    }

    WSACleanup();
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

// ������ �Լ�
unsigned int WINAPI clntConn(LPVOID lpParam)
{
    SOCKET clntSock = (SOCKET)lpParam;
    DWORD strLen = 0;

    TCHAR message[BUFSIZE];

    // Ŭ���̾�Ʈ �޼����� ����
    while((strLen = recv(clntSock, message, BUFSIZE, 0)) != 0)
        sendMsg(message, strLen);

    WaitForSingleObject(hMutex, INFINITE);

    // Ŭ�� ������ ���� ������ 
    for(DWORD i = 0; i < clntNumber; i++)
    {
        if(clntSock == clntSocks[i])
        {
            for(DWORD j; j < (clntNumber - 1); j++)
                clntSocks[j] = clntSocks[j + 1];
        }

        break;
    }

    ReleaseMutex(hMutex);
    closesocket(clntSock);
    return 0;
}

// Ŭ�� �޼��� ���� �Լ�
void sendMsg(LPVOID message, int len)
{
    // ����ȭ
    WaitForSingleObject(hMutex, INFINITE);

    // ��� Ŭ�󿡰� �޼��� ����
    for(DWORD i = 0; i < clntNumber; i++)
        send(clntSocks[i], (char *)message, len, 0);

    // ����ȭ ����
    ReleaseMutex(hMutex);
}