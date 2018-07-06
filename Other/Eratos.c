#if 0   //version 1.0
#include <stdio.h>
#include <stdlib.h>

int PlatterOfEratostenes(int *, int);

int main(void)
{
    int SizeOfArray;
    int *str;

    // 입력값을 받는다.
    printf("Please enter number : ");
    scanf("%d", &SizeOfArray);

    // 동적변수 선언 및 사용
    str = (int *)malloc(sizeof(int) * SizeOfArray);

    // 입력받은 크기 많큼 배열을 생성 및 데이터 삽입
    for(int i = 0; i < SizeOfArray; i++)
    {
        str[i] = (i + 1);
    }   
    // 함수 동작
    PlatterOfEratostenes(str, SizeOfArray);

    printf("\n--- Platter of Eratostenes Start ---\n");
    // 데이터 출력
    printf("Prime Number :");
    for(int i = 0; i < SizeOfArray; i++)
    {
        if(str[i] == 0)
            continue;

        printf("%3d ",str[i]);
    }
    printf("\n--- Platter of Eratostenes End ---\n");
    free(str);
    return 0;
}

int PlatterOfEratostenes(int *str, int SizeOfArray)
{
    for(int i = 0; i < SizeOfArray ; i++)
    {
        if (i == 0)
            str[i] = 0;

        for(int j = (i + 1); j < SizeOfArray; j++)
        {
            if(str[i] == 0)
                continue;

            if(str[j] % str[i] == 0)
                str[j] = 0;
        }
    }
    
    return 0;
}
#endif

#if 1   //version 2.0
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int Eratos(int);

int main(void)
{
    int n;

    // 원하는값 입력
    printf("Please Enter Number : ");
    scanf("%d", &n);

    // Eratos 함수 동작
    printf("Prime Number : ");
    Eratos(n);

    return 0;
}

int Eratos(int num)
{
    // 동적배열 포인터 선언
    bool *arr;

    if (num <=1 ) return -1;

    // 동적배열 할당
    arr = (bool *)malloc(sizeof(bool) * (num + 1));

    // 배열 초기화
    for(int i = 2; i <= num; i++) arr[i] = true;

    // 에라토스테네스의체 실행
    for(int i = 2; i <= num; i++)
    {
        if(arr[i])
        {
            for(int j = i * i; j <= num; j += i) arr[j] = false;
        }
    }

    // 결과 출력
    for(int i = 2; i <= num; i++)
    {
        if(arr[i]) printf("%3d ", i);
    }

    free(arr);
    return 0;
}
#endif