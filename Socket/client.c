#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>

#define BUFSIZE 1024 // 최대 입력값을 설정

void ErrorHandling(char *); // 에러 메시지 출력 함수 선언

int main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET hClntSock;
    SOCKADDR_IN servAddr;

    int nRecv;
    char message[BUFSIZE];

    // 인자를 입력받지 못했을 때
    if (argc != 3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // ws2_32 초기화 선언
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        ErrorHandling("WSAStartup() error!");
    
    // 클라이언트 소켓을 생성
    hClntSock = socket(PF_INET, SOCK_STREAM, 0);
    if(hClntSock == INVALID_SOCKET)
        ErrorHandling("socket() error");

    // 서버 설정
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    // 클라이언트 소켓에 서버 설정을 사용하여 서버에 연결
    if(connect(hClntSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    {
        ErrorHandling("connect error");
    }
    else
    {
        printf("%s Connection Complete! \n", inet_ntoa(servAddr.sin_addr));
        printf("Start ... \n");
    }

    // 데이터를 송수신
    while(1)
    {
        printf("Send Message : ");
        gets(message);

        if(strcmp(message, "exit") == 0)
        {
            send(hClntSock, message, strlen(message), 0);
            break;
        }

        send(hClntSock, message, strlen(message), 0);
        printf("Message Receives ...\n");

        nRecv = recv(hClntSock, message, sizeof(message) - 1, 0);
        if(nRecv == SOCKET_ERROR)
        {
            printf("Receive Error...\n");
            break;
        }

        message[nRecv] = '\0';

        if(strcmp(message, "exit") == 0) {

            printf("Close Server Connection..\n");

            break;

        }

        printf("Receive Message : %s\n", message); 

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

    