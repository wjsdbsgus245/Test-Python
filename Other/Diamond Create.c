#include <stdio.h>
#include <stdlib.h>

int main(void){
    int k, k1, c;
    
    while (1){
        printf("*����) Ȧ�� ũ�⸸ �����մϴ�.\n");
        printf("���̾Ƹ���� ũ�⸦ �������ּ���! : ");
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

    printf("%d ũ���� ���̾Ƹ�尡 �����Ǿ����ϴ�!!", c);

    return 0;
}