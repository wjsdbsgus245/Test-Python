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
        // 초기 출력 창
        system("cls");
        printf("도서 관리 프로그램 \n");
        printf("1. 책을 추가 \n");
        printf("2. 책을 검색 \n");
        printf("3. 책을 대여 \n");
        printf("4. 책을 반납 \n");
        printf("5. 책을 버리기 \n");
        printf("6. 프로그램 종료 \n");
        printf("메뉴를 선택해주세요 : ");
        scanf("%d", &selectMain);

        // 각 번호에 대한 함수 호출
        if(selectMain == 1) { CreateBook(&books[count]); }
        else if(selectMain == 2) { SearchBook(&books); } 
        else if(selectMain == 3) {  } 
        else if(selectMain == 4) {  } 
        else if(selectMain == 5) {  } 
        else if(selectMain == 6) { break; } 
        else { printf("지정된 수만 입력해 주세요!!"); } 

        // 버퍼 비우기
        while((buf = getchar()) != EOF && buf != '\n');
        Sleep(1000);
    }

	return 0;
}

// 책 추가 SelectNo.1
void CreateBook(struct Book *add)
{
    char name[30], auth[30], publ[30];
    char buf;

    system("cls");
    printf("추가할 책의 제목 : ");
    scanf("%s", name);
    printf("추가할 책의 저자 : ");
    scanf("%s", auth);
    printf("추가할 책의 출판사 : ");
    scanf("%s", publ);

    count++;
    add->no = count;
    strcpy(add->name, name);
    strcpy(add->auth, auth);
    strcpy(add->publ, publ);
    add->borrowed = false;

    printf("추가 완료!!");
}

// 책 버리기 SelectNo.5
void DropBook()
{
    system("cls");
    printf("");
}

// 책 검색 SelectNo.2
void SearchBook(struct Book (*search)[MAX])
{
    int selectSearch, num;
    char buf, ch, str[30];

    while(1)
    {
        system("cls");
        printf("책 검색 \n");
        printf("1. 번호로 검색 \n");
        printf("2. 제목으로 검색 \n");
        printf("3. 지은이로 검색 \n");
        printf("4. 출판사로 검색 \n");
        printf("5. 되돌아 가기 \n");
        printf("메뉴를 선택해 주세요 : ");
        scanf("%d", &selectSearch);
        
        if(selectSearch == 1) 
        { 
            printf("번호를 입력하세요 : ");
            scanf("%d", &num);

            system("cls");
            num -= 1;
            printf("번호 : %d \n", search[num]->no);
            printf("책 이름 : %s \n", search[num]->name);
            printf("지은이 : %s \n", search[num]->auth);
            printf("출판사 : %s \n", search[num]->publ);

        }
        else if(selectSearch == 2) {  }
        else if(selectSearch == 3) {  }
        else if(selectSearch == 4) {  }
        else if(selectSearch == 5) { break; }
        else { printf("지정된 수만 입력해 주세요!!"); } 

        while((buf = getchar()) != EOF && buf != '\n');
        Sleep(3000);
    }

}

// 책 대여 SelectNo.3
void RentBook()
{
    system("cls");
    printf("");
}
// 책 반납 SelectNo.4
void ReturnBook()
{
    system("cls");
    printf("");
}