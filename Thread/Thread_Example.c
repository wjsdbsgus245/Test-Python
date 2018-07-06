#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h>
#include <time.h>

#define WORKING_MIN 10
#define WORKING_MAX (20) - WORKING_MIN + 1
#define NUM_OF_PEOPLE 100

int Working(DWORD);
unsigned int WINAPI ThreadProc(LPVOID);

int _tmain(int argc,TCHAR *argv[])
{
    HANDLE hThread[NUM_OF_PEOPLE];
    DWORD dwThreadID[NUM_OF_PEOPLE];
    DWORD WorkingTime[NUM_OF_PEOPLE];
    DWORD random;

    srand(time(NULL));
    for(DWORD i = 0; i < NUM_OF_PEOPLE; i++)
    {
        random = ((rand() %
        _tprintf(_T("random[%d] : %d \n"), (i + 1), random);
    }

    /*
    for(DWORD i = 0; i < NUM_OF_PEOPLE; i++)
        WorkingTime[i] = (DWORD)((rand() % WORKING_MAX) + 10);

    for(DWORD i = 0; i < NUM_OF_PEOPLE; i++)
        _tprintf(_T("Time[%d] : %d \n"), (i + 1), WorkingTime[i]);
    */
    return 0;
}

int Working(DWORD Time)
{
    _tprintf(_T("Time : %d \n"), Time);
    return 0;
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
    Working((DWORD)lpParam);
    return 0;
}