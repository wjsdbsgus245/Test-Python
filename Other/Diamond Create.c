#include <stdio.h>
#include <stdlib.h>

int main(void){
    int k, k1, c;
    
    while (1){
        printf("*주의) 홀수 크기만 가능합니다.\n");
        printf("다이아몬드의 크기를 지정해주세요! : ");
        scanf("%d", &c);
        if (c % 2 != 0) { break; }
    }

    for(int i = 0; i <= c; i++){

        k = abs(i - (c / 2));
        k1 = c - (abs(i - (c / 2)) * 2);

        for(int j = 0; j <= k; j++){
            printf(" ");
        }
        for(int j = 0; j < k1; j++){
            printf("*");
        }
        printf("\n");
    }

    printf("%d 크기의 다이아몬드가 생성되었습니다!!", c);

    return 0;
}