#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>

#define BUFSIZE 1024 // 최대 입력값을 설정

void ErrorHandling(char *); // 에러 메시지 출력 함수 선언

int main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr;

    int szClntAddr;
    int nRecv;
    char message[BUFSIZE];

    // 인자를 입력받지 못했을 때
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // ws2_32 초기화 선언
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");
    
    // 서버 소켓을 생성
    hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if(hServSock == INVALID_SOCKET)
        ErrorHandling("socket() error");

    // 서버 소켓의 설정
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    // 설정을 서버 소켓에 바인딩
    if(bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("bind() error");

    // 클라이언트 접속 요청을 받도록 설정
    if(listen(hServSock, 5) == SOCKET_ERROR)
        ErrorHandling("listen() error");

    // 클라이언트의 접속 요청 대기 및 허락하며, 클라이언트의 소켓을 생성
    szClntAddr = sizeof(clntAddr);
    hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
    if(hClntSock == INVALID_SOCKET)
    {
        ErrorHandling("accept() error");
    }
    else
    {
        printf("%s Connection Complete! \n", inet_ntoa(clntAddr.sin_addr));
        printf("Start ... \n");
    }

    // 서버 소켓을 소멸
    closesocket(hServSock);

    // 데이터를 송수신
    while(1)
    {  
        printf("Message Receives ...\n");
        nRecv = recv(hClntSock, message, sizeof(message) - 1, 0);

        if (nRecv == SOCKET_ERROR)
        {
            printf("Receive Error...\n");
            break;
        }

        printf("Receive Message : %s\n", message);
        printf("Send Message :");
        gets(message);

        if(strcmp(message, "exit") == 0)
        {
            send(hClntSock, message, strlen(message), 0);
            break;
        }

        send(hClntSock, message, strlen(message), 0);
    }

    // 클라이언트 소켓을 소멸
    closesocket(hClntSock);
    WSACleanup();

    printf("Close Connction.. \n");
    _getch();

    return 0;
}


void ErrorHandling(char *message) // 에러 메시지 출력 함수 
{
    fputs(message, stderr);
    fputc('\n', stderr);
    _getch();
    exit(1);
}

