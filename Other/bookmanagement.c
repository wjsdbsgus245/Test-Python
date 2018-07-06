#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define MAX 10

struct Book
{
    int no;
    char name[30], auth[30], publ[30];
    bool borrowed;
};

void CreateBook(struct Book *);
void SearchBook(struct Book (*search)[MAX]);
int count = 0;

int main()
{
    int selectMain;
    char buf;
    struct Book books[MAX];

    while(1)
    {
        // �ʱ� ��� â
        system("cls");
        printf("���� ���� ���α׷� \n");
        printf("1. å�� �߰� \n");
        printf("2. å�� �˻� \n");
        printf("3. å�� �뿩 \n");
        printf("4. å�� �ݳ� \n");
        printf("5. å�� ������ \n");
        printf("6. ���α׷� ���� \n");
        printf("�޴��� �������ּ��� : ");
        scanf("%d", &selectMain);

        // �� ��ȣ�� ���� �Լ� ȣ��
        if(selectMain == 1) { CreateBook(&books[count]); }
        else if(selectMain == 2) { SearchBook(&books); } 
        else if(selectMain == 3) {  } 
        else if(selectMain == 4) {  } 
        else if(selectMain == 5) {  } 
        else if(selectMain == 6) { break; } 
        else { printf("������ ���� �Է��� �ּ���!!"); } 

        // ���� ����
        while((buf = getchar()) != EOF && buf != '\n');
        Sleep(1000);
    }

	return 0;
}

// å �߰� SelectNo.1
void CreateBook(struct Book *add)
{
    char name[30], auth[30], publ[30];
    char buf;

    system("cls");
    printf("�߰��� å�� ���� : ");
    scanf("%s", name);
    printf("�߰��� å�� ���� : ");
    scanf("%s", auth);
    printf("�߰��� å�� ���ǻ� : ");
    scanf("%s", publ);

    count++;
    add->no = count;
    strcpy(add->name, name);
    strcpy(add->auth, auth);
    strcpy(add->publ, publ);
    add->borrowed = false;

    printf("�߰� �Ϸ�!!");
}

// å ������ SelectNo.5
void DropBook()
{
    system("cls");
    printf("");
}

// å �˻� SelectNo.2
void SearchBook(struct Book (*search)[MAX])
{
    int selectSearch, num;
    char buf, ch, str[30];

    while(1)
    {
        system("cls");
        printf("å �˻� \n");
        printf("1. ��ȣ�� �˻� \n");
        printf("2. �������� �˻� \n");
        printf("3. �����̷� �˻� \n");
        printf("4. ���ǻ�� �˻� \n");
        printf("5. �ǵ��� ���� \n");
        printf("�޴��� ������ �ּ��� : ");
        scanf("%d", &selectSearch);
        
        if(selectSearch == 1) 
        { 
            printf("��ȣ�� �Է��ϼ��� : ");
            scanf("%d", &num);

            system("cls");
            num -= 1;
            printf("��ȣ : %d \n", search[num]->no);
            printf("å �̸� : %s \n", search[num]->name);
            printf("������ : %s \n", search[num]->auth);
            printf("���ǻ� : %s \n", search[num]->publ);

        }
        else if(selectSearch == 2) {  }
        else if(selectSearch == 3) {  }
        else if(selectSearch == 4) {  }
        else if(selectSearch == 5) { break; }
        else { printf("������ ���� �Է��� �ּ���!!"); } 

        while((buf = getchar()) != EOF && buf != '\n');
        Sleep(3000);
    }

}

// å �뿩 SelectNo.3
void RentBook()
{
    system("cls");
    printf("");
}
// å �ݳ� SelectNo.4
void ReturnBook()
{
    system("cls");
    printf("");
}