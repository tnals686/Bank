#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h>



typedef struct account {
    char name[20];
    char id[10];
    int passwd;
    char address[100];
    char phone[20];
    long long balance;
} account; //계좌를 나타내는 구조체 

const int HEADLEFT = 0;
const int LEFT = 0;

account person[100];
int count = 0;
char anyKey;

void gotoxy(int x, int y)
{
    // 콘솔의 X, Y 좌표 지정    
    COORD position = { 0,0 };
    position.X = x; position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int mainmenu()
{
    system("cls");//화면 지우기 
    int x, y;
    int menu = -1;

    x = HEADLEFT, y = 1;
    gotoxy(x, y); printf("[은행 관리 시스템]");

    x = LEFT, y += 2;
    gotoxy(x, y); printf("[1] 계좌 개설");
    y++; gotoxy(x, y); printf("[2] 계좌 조회");
    y++; gotoxy(x, y); printf("[3] 입금");
    y++; gotoxy(x, y); printf("[4] 출금");
    y += 2; gotoxy(x, y); printf("[0] 종료");

    x = HEADLEFT; y += 2; gotoxy(x, y); printf("<메뉴선택> : ");

    scanf("%d%c", &menu, &anyKey); //아무키나 뒤에 붙여서 에러 수정 
    return menu;
}

int main(void)
{
    int op;
    int f_index;
    int x, y;
    char id[10];
    int passwd;
    int in_money, out_money;

    while (1)
    {
        op = mainmenu();

        switch (op)
        {
        case 1://계좌 개설 

            system("cls");
            x = HEADLEFT, y = 1;
            gotoxy(x, y); printf_s("[1] 계좌 개설");

            y += 2; gotoxy(x, y); printf("입력 후 Enter키를 누르세요.");

            x = LEFT, y += 2;
            gotoxy(x, y); printf("이름: "); scanf("%s", person[count].name, 20);
            y++; gotoxy(x, y); printf("ID: "); scanf("%s", person[count].id, 10);
            y++; gotoxy(x, y); printf("암호: "); scanf("%d%c", &person[count].passwd, &anyKey);
            y++; gotoxy(x, y); printf("주소: "); gets_s(person[count].address, 100);
            y++; gotoxy(x, y); printf("전화번호: "); gets_s(person[count].phone, 20);
            y++; gotoxy(x, y); printf("입금액: "); scanf("%lld", &person[count].balance);

            y += 2; gotoxy(x, y); printf("계좌가 개설되었습니다.\n\n");

            count++;

            system("pause");
            break;

        case 2://계좌 조회 

            system("cls");

            x = HEADLEFT, y = 1;
            gotoxy(x, y); printf("[2] 계좌 조회");

            y += 2; gotoxy(x, y); printf("입력 후 Enter키를 누르세요.");

            x = LEFT, y += 2;
            gotoxy(x, y); printf("ID: "); scanf("%s", id, 10);
            y++; gotoxy(x, y); printf("암호: "); scanf("%d", &passwd);

            f_index = searchIndex(id, passwd);

            if (f_index == -1) {
                printf("\n조회된 결과가 없습니다.\n\n");
                system("pause");
                break;
            }
            else if (f_index == -2) {
                printf("\n암호가 틀립니다.\n\n");
                system("pause");
                break;
            }

            system("cls");
            x = HEADLEFT, y = 1;
            gotoxy(x, y); printf_s("[2] 계좌 조회 결과");

            x = LEFT, y += 2;
            gotoxy(x, y); printf("이름: %s", person[f_index].name);
            x += 15; gotoxy(x, y); printf("잔고: %lld", person[f_index].balance);
            x = LEFT; y++; gotoxy(x, y); printf("ID: %s", person[f_index].id);
            x += 15; gotoxy(x, y); printf("암호: %d", person[f_index].passwd);
            x = LEFT; y++; gotoxy(x, y); printf("전화번호: %s", person[f_index].phone);
            y++; gotoxy(x, y); printf("주소: %s", person[f_index].address);

            x = LEFT; y += 2; gotoxy(x, y); printf("계좌를 조회하였습니다.\n\n");
            system("pause");
            break;

        case 3://입금             
            system("cls");

            x = HEADLEFT, y = 1;
            if (passwd)gotoxy(x, y); printf("[3] 입금");

            y += 2; gotoxy(x, y); printf("입력 후 Enter키를 누르세요.");

            x = LEFT, y += 2;
            gotoxy(x, y); printf("ID: "); scanf("%s", &id);
            y++; gotoxy(x, y); printf("암호: "); scanf("%d", &passwd);
            y++; gotoxy(x, y); printf("입금액: "); scanf("%d", &in_money);

            f_index = searchIndex(id, passwd);

            if (f_index == -1) {
                printf("\n조회된 결과가 없습니다.\n\n");
                system("pause");
                break;
            }
            else if (f_index == -2) {
                printf("\n입금 실패: 암호가 틀립니다.\n\n");
                system("pause");
                break;
            }

            person[f_index].balance += in_money;

            y += 2; gotoxy(x, y); printf("입금 성공: 금액 %d원이 입금되었습니다.", in_money);
            y++; gotoxy(x, y); printf("잔     고: %d원입니다.\n\n", person[f_index].balance);

            system("pause");

            break;

        case 4://출금 
            system("cls");

            x = HEADLEFT, y = 1;
            if (passwd)gotoxy(x, y); printf_s("[4] 출금");

            y += 2; gotoxy(x, y); printf("입력 후 Enter키를 누르세요.");

            x = LEFT, y += 2;
            gotoxy(x, y); printf("ID: "); scanf("%s", &id);
            y++; gotoxy(x, y); printf("암호: "); scanf("%d", &passwd);
            y++; gotoxy(x, y); printf("출금액: "); scanf("%d", &out_money);

            f_index = searchIndex(id, passwd);

            if (f_index == -1) {
                printf("\n조회된 결과가 없습니다.\n\n");
                system("pause");
                break;
            }
            else if (f_index == -2) {
                printf("\n출금 실패: 암호가 틀립니다.\n\n");
                system("pause");
                break;
            }

            if (person[f_index].balance - out_money < 0) {
                printf("\n출금 실패: 잔고가 부족합니다.\n\n");
                system("pause");
                break;
            }

            person[f_index].balance -= out_money;

            y += 2; gotoxy(x, y); printf("출금 성공: 금액 %d원이 출금되었습니다.", out_money);
            y++; gotoxy(x, y); printf("잔     고: %d원입니다.\n\n", person[f_index].balance);

            system("pause");

            break;

        case 0:
            exit(-1);
            break;

        }
        rewind(stdin);
    }
    return 0;
}

int searchIndex(char* id, int passwd) {
    int f_index = -1;

    for (int i = 0; i < count; i++) {
        if (strcmp(person[i].id, id) == 0 && person[i].passwd == passwd) {
            f_index = i;
            break;
        }
        else if (strcmp(person[i].id, id) == 0 && person[i].passwd != passwd) {
            f_index = -2; //-2는 암호가 틀린것으로 설정
            break;
        }
    }

    return f_index;
}
