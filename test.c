#include <stdio.h>      // 파일 입출력 헤더파일
#include <stdlib.h>
#include <tchar.h>      // 문자열 처리 헤더파일
#include <winsock2.h>   // 소켓 통신 헤더파일
#include <conio.h>      // _getch 함수 사용
#include <windows.h>    // 쓰레드 헤더파일
#include <process.h>    

#define CLIENT_MAX 100
#define BUFSIZE 1024    // 버퍼 사이즈 

void ErrorHandling(LPVOID); // 에러 메세지 출력

unsigned int WINAPI clntConn(LPVOID);   // 클라 연결 함수 
void sendMsg(LPVOID, int);  // 메세지 함수

DWORD clntNumber = 0; // 클라 수
SOCKET clntSocks[CLIENT_MAX]; // 클라 소켓 배열
HANDLE hMutex;  // 동기화 핸들

int _tmain(int argc, TCHAR *argv[])
{
    WSADATA wsaData;    // winsock 2.2 DLL 로드
    SOCKET servSock, clntSock;  // 서버 및 클라 소켓
    SOCKADDR_IN servAddr, clntAddr; // 서버 및 클라 정보

    int clntAddrSize;

    HANDLE hTread;  // 쓰레드 핸들
    DWORD dwThreadID;   // 쓰레드 아이디

    // 포트 번호를 받지 못할시
    if(argc != 2)
    {
        _tprintf("Please, Insert Port Number \n");
        exit(1);
    }

    // DLL 로딩
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        ErrorHandling("Load WinSock 2.2 DLL error");

    // 뮤텍스 동기화 객체 생성
    hMutex = (HANDLE)CreateMutex(NULL, FALSE, NULL);
    if(hMutex == NULL)
        ErrorHandling("CreatMutex Error");

    // 서버 소켓 생성
    servSock = socket(PF_INET, SOCK_STREAM, 0);
    if(servSock == INVALID_SOCKET)
        ErrorHandling("Server Sock Error");

    // 서버에 대한 정보를 초기화
    memset(&servAddr, 0, sizeof(SOCKADDR_IN));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    // 서버 소켓 바인딩
    if(bind(servSock, (SOCKADDR *)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        ErrorHandling("Bind Error");
    
    // 클라 접속을 대기
    if(listen(servSock, CLIENT_MAX) == SOCKET_ERROR)
        ErrorHandling("Listen Error");

    while(1)
    {
        // 클라 주소 받기
        clntAddrSize = sizeof(clntAddr);

        // 클라 접속 대기
        clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &clntAddrSize);
        if(clntSock == INVALID_SOCKET)
            ErrorHandling("Accept Error");

        // 동기화
        WaitForSingleObject(hMutex, INFINITE);

        // 클라 소켓 배열에 소켓 정보를 저장, 클라 접속수를 증가
        clntSocks[clntNumber++] = clntSock;

        // 동기화 해제
        ReleaseMutex(hMutex);

        // 클라 접속 아이피 출력
        _tprintf(_T("New Connect, Client IP : %s \n"), inet_ntoa(clntAddr.sin_addr));
    
        // 쓰레드 생성
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

// 쓰레드 함수
unsigned int WINAPI clntConn(LPVOID lpParam)
{
    SOCKET clntSock = (SOCKET)lpParam;
    DWORD strLen = 0;

    TCHAR message[BUFSIZE];

    // 클라이언트 메세지를 받음
    while((strLen = recv(clntSock, message, BUFSIZE, 0)) != 0)
        sendMsg(message, strLen);

    WaitForSingleObject(hMutex, INFINITE);

    // 클라 연결이 종료 됬을시 
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

// 클라 메세지 전송 함수
void sendMsg(LPVOID message, int len)
{
    // 동기화
    WaitForSingleObject(hMutex, INFINITE);

    // 모든 클라에게 메세지 전송
    for(DWORD i = 0; i < clntNumber; i++)
        send(clntSocks[i], (char *)message, len, 0);

    // 동기화 해제
    ReleaseMutex(hMutex);
}