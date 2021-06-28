#include "main.h"

int win, lose, draw;
int player_coin, com_coin, bet_coin;


int title();// 타이틀 화면 출력

float set_level();
void set_coin(float level); //초기 코인개수 설정

void betting();
int select_player(); //플레이어 rsp 
int select_computer(); //컴퓨터 rsp
int match();

void stats(int result);

void ani_1(); //around
void ani_2(int mode); //flash 0:red 1:blue 2:green
void ani_3(int mode); //drop 0:red 1:green

void rdot(int x, int y);
void sdot(int x, int y); // 인수, 도트 첫줄의 시작 좌표
void pdot(int x, int y);

void clear();
void clear_cursor(char show);
void gotoxy(int x, int y);



int main(void)
{
    system("mode con cols=100 lines=25 | title 가위바위보 게임!");
    clear_cursor(0);

    while (true)
    {
        win, lose, draw = 0;
        player_coin, com_coin, bet_coin = 0;
        gotoxy(0, 0);

        switch (title())

        {
        case 0:
            system("cls");
            break; //게임시작

        case 1:
            system("cls");
            exit(0); //게임종료
        }

        set_coin(set_level()); //초기 코인 설정

        //초기 인터페이스 세팅
        ani_1();

        gotoxy(45, 3);
        printf("판돈: %d", bet_coin);   //판돈

        gotoxy(27, 15);
        printf("P: %d", player_coin);
        gotoxy(65, 15);                 //코인개수
        printf("COM: %d", com_coin);

        clear_cursor(0);

        rdot(21, 5);
        rdot(59, 5);                    //가위바위보 도트

        gotoxy(11, 17);
        printf("------------------------------------------------------------------------------");
        gotoxy(11, 23);                                                                             //글상자
        printf("------------------------------------------------------------------------------");


        while (true)
        {
            rewind(stdin);
            betting();

            int result = match(); //무승부(0)  승리(1)  패배(2)

            switch (result)
            {
            case 0:
                gotoxy(11, 20);
                printf("                                   무승부~~~");
                ani_2(1); //파란색

                break;

            case 1:
                gotoxy(11, 20);
                printf("                                   승리!!!");
                ani_2(2); //초록색

                com_coin -= bet_coin;
                player_coin += bet_coin;
                break;

            case 2:
                gotoxy(11, 20);
                printf("                                   패배...");
                ani_2(0); //빨간색

                player_coin -= bet_coin;
                com_coin += bet_coin;
                break;
            }

            gotoxy(27, 15);
            printf("P: %d          ", player_coin);
            gotoxy(65, 15);
            printf("COM: %d          ", com_coin);
            Sleep(3000);

            stats(result);

            if (com_coin == 0)
            {
                gotoxy(11, 20);
                printf("                                      -WIN- ");
                Sleep(5000);
                ani_3(1);
                break;

            }

            else if (player_coin == 0)
            {
                gotoxy(11, 20);
                printf("                                   -YOU DIED- ");
                Sleep(5000);
                ani_3(0);
                break;
            }
        }
    }

    return 0;
}



int title()
{

    int select;

    char dote[8][90] = { 0 };

    printf("\n\n\n\n\n");
    strcpy(dote[0], "                    ##########@@           ##########@@           #########@@   ");
    strcpy(dote[1], "                   #@@        #@@         #@@        #@@         #@@       #@@  ");
    strcpy(dote[2], "                   #@@        #@@         #@@        #@@         #@@            ");
    strcpy(dote[3], "                   ###########@           ###########@@           #########@@   ");
    strcpy(dote[4], "                   #@@        #@@         #@@                              #@@  ");
    strcpy(dote[5], "                   #@@         #@@        #@@                    #@@       #@@  ");
    strcpy(dote[6], "                   #@@          #@@       #@@                     #########@@   ");
    strcpy(dote[7], "                                                                                ");

    Sleep(1000);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 90; j++)
        {
            if (dote[i][j] == '@')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (rand() % 3) + 3);
                printf("%c", dote[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                printf("%c", dote[i][j]);

            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        printf("\n");
    }

    Sleep(1000);



    ani_1();

    select = 0;

    gotoxy(19 + 25, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("게임시작");

    gotoxy(19 + 25, 19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("게임종료");

    while (1)
    {
        int key = getch();

        if (key == 224)
        {
            switch (getch())
            {

            case 72:
                select = 0;

                gotoxy(19 + 25, 16);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                printf("게임시작");


                gotoxy(19 + 25, 19);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                printf("게임종료");

                break;


            case 80:
                select = 1;

                gotoxy(19 + 25, 16);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                printf("게임시작");

                gotoxy(19 + 25, 19);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                printf("게임종료");

                break;

            }
        }

        else if (key == 13)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            return select;
        }


    }
}


float set_level()
{
    system("cls");

    ani_1();

    int select = 0;

    gotoxy(19 + 25, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("LEVEL 1");

    gotoxy(19 + 25, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    printf("LEVEL 2");

    gotoxy(19 + 25, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    printf("LEVEL 3");


    while (1)
    {
        int key = getch();

        if (key == 224)
        {
            switch (getch())
            {

            case 72:

                if (select > 0)
                {
                    select--;
                }
                break;


            case 80:

                if (select < 2)
                {
                    select++;
                }
                break;

            }
        }

        else if (key == 13)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

            if (select == 0)
            {
                return 2;
            }

            else if (select == 1)
            {
                return 3;
            }

            else if (select == 2)
            {
                return 5;
            }
        }

        switch (select)
        {
        case 0:
            gotoxy(19 + 25, 10);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            printf("LEVEL 1");

            gotoxy(19 + 25, 13);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("LEVEL 2");

            gotoxy(19 + 25, 16);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            printf("LEVEL 3");

            break;

        case 1:
            gotoxy(19 + 25, 10);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("LEVEL 1");

            gotoxy(19 + 25, 13);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            printf("LEVEL 2");

            gotoxy(19 + 25, 16);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            printf("LEVEL 3");

            break;

        case 2:
            gotoxy(19 + 25, 10);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("LEVEL 1");

            gotoxy(19 + 25, 13);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("LEVEL 2");

            gotoxy(19 + 25, 16);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            printf("LEVEL 3");

            break;

        }

    }
}

void set_coin(float level)
{
    while (true)
    {
        system("cls");

        ani_1();

        gotoxy(32, 10);
        printf("초기 코인을 설정해주세요:");
        scanf("%d", &player_coin);

        if (player_coin <= 0)
        {
            player_coin = -1;
            system("cls"); //출력 화면 초기화
            gotoxy(35, 10);
            printf("다시 입력해 주세요.");
            rewind(stdin);
            Sleep(1000);
        }

        else
        {
            com_coin = player_coin * level;
            rewind(stdin);
            break;
        }
    }


    system("cls"); //출력 화면 초기화

    return;
}


void betting()
{
    while (1)
    {
        clear();

        gotoxy(11, 20);
        printf("                           판돈을 정해주세요: ");
        scanf("%d", &bet_coin);

        if (bet_coin <= 0 || bet_coin > player_coin || bet_coin > com_coin)
        {
            clear();
            gotoxy(11, 20);
            printf("                            다시 입력해주세요 ");
            rewind(stdin);
            Sleep(1000);
        }

        else
        {
            rewind(stdin);
            break;
        }
    }

    gotoxy(45, 3);
    printf("판돈: %d                             ", bet_coin);

    clear();
    return;
}

int select_player()
{
    clear();

    int key;
    int select = 1;

    while (1)
    {
        switch (select)
        {
        case 1: //가위
            gotoxy(11, 20);
            printf("                      가위            바위            보");
            gotoxy(33, 20);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            printf("가위");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            break;


        case 2: //바위
            gotoxy(11, 20);
            printf("                      가위            바위            보");
            gotoxy(49, 20);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            printf("바위");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            break;

        case 3: //보
            gotoxy(11, 20);
            printf("                      가위            바위            보");
            gotoxy(65, 20);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            printf("보");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            break;
        }


        key = getch();

        if (key == 224)
        {
            switch (getch())
            {

            case 75:
                if (select > 1)
                {
                    select--;
                }
                break;



            case 77:
                if (select < 3)
                {
                    select++;
                }
                break;

            }
        }

        else if (key == 13)
        {
            break;
        }

    }

    switch (select)
    {
    case 1:
        sdot(21, 5);
        break;
    case 2:
        rdot(21, 5);
        break;
    case 3:
        pdot(21, 5);
        break;
    }

    clear();

    return select;
}

int select_computer()
{
    int select;
    srand(time(NULL));

    for (int i = 0; i < 40; i++)
    {
        select = (rand() % 3) + 1;

        switch (select)
        {
        case 1: //가위
            sdot(59, 5);
            Sleep(1 + (i * 5));
            break;

        case 2: //바위
            rdot(59, 5);
            Sleep(1 + (i * 5));
            break;

        case 3: //보
            pdot(59, 5);
            Sleep(1 + (i * 5));
            break;
        }

    }

    return select;
}

int match()
{
    int player = select_player();
    int computer = select_computer();

    int result = (3 + player - computer) % 3;

    switch (result)
    {
    case 0: //무승부
        return 0;
    case 1: //승리
        return 1;
    case 2: //패배
        return 2;
    }

    return -1;
}

void stats(int result)
{
    clear();

    switch (result)
    {
    case 0:
        draw++;
        break;
    case 1:
        win++;
        break;
    case 2:
        lose++;
        break;
    }

    gotoxy(11, 20);
    printf("                             %d전- 승:%d 무:%d 패:%d 승률:%.2lf%%", draw + win + lose, win, draw, lose, 100 * ((double)win / ((double)win + (double)lose + (double)draw)));
    Sleep(3000);

    clear();
    return;
}


void ani_1()
{
    for (int i = 0; i < 100; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(i, 0);
        printf("O");
        Sleep(1);
    }

    for (int i = 0; i < 24; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(99, i);
        printf("O");
        Sleep(1);
    }

    for (int i = 0; i < 100; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(99 - i, 24);
        printf("O");
        Sleep(1);
    }

    for (int i = 0; i < 24; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        gotoxy(0, 24 - i);
        printf("O");
        Sleep(1);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    return;
}

void ani_2(int mode) //0:red 1:blue 2:green
{
    int n;

    if (mode == 0)
    {
        n = 12;
    }

    else if (mode == 1)
    {
        n = 9;
    }
    else
    {
        n = 10;
    }

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 100; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
            gotoxy(i, 0);
            printf("O");
        }

        for (int i = 0; i < 24; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
            gotoxy(99, i);
            printf("O");
        }

        for (int i = 0; i < 100; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
            gotoxy(99 - i, 24);
            printf("O");
        }

        for (int i = 0; i < 24; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
            gotoxy(0, 24 - i);
            printf("O");
        }
        /////////////////////
        Sleep(500);
        /////////////////////
        for (int i = 0; i < 100; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            gotoxy(i, 0);
            printf("O");
        }

        for (int i = 0; i < 24; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            gotoxy(99, i);
            printf("O");
        }

        for (int i = 0; i < 100; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            gotoxy(99 - i, 24);
            printf("O");
        }

        for (int i = 0; i < 24; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            gotoxy(0, 24 - i);
            printf("O");
        }
        ////////////////////////
        Sleep(50);
    }

    return;
}

void ani_3(int mode) //0:red 1:green
{
    int n = 0;

    if (mode == 0)
    {
        n = 12;
    }

    else if (mode == 1)
    {
        n = 10;
    }

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
            gotoxy(j, i);
            printf("O");

        }
        Sleep(50);

    }

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            gotoxy(j, i);
            printf(" ");

        }
        Sleep(50);

    }
}


void rdot(int x, int y)
{
    gotoxy(x, y);
    printf("                      \n");
    gotoxy(x, y + 1);
    printf("                      \n");
    gotoxy(x, y + 2);
    printf("                      \n");
    gotoxy(x, y + 3);
    printf("    ## ## ## ##       \n");
    gotoxy(x, y + 4);
    printf("   ##############     \n");
    gotoxy(x, y + 5);
    printf("  ################    \n");
    gotoxy(x, y + 6);
    printf("  ################    \n");
    gotoxy(x, y + 7);
    printf("   ##############     \n");
    gotoxy(x, y + 8);
    printf("    ############      \n");

    return;
}

void sdot(int x, int y)
{
    gotoxy(x, y);
    printf(" #####        #####   \n");
    gotoxy(x, y + 1);
    printf("  #####      #####    \n");
    gotoxy(x, y + 2);
    printf("   #####    #####     \n");
    gotoxy(x, y + 3);
    printf("    ############      \n");
    gotoxy(x, y + 4);
    printf("   ##############     \n");
    gotoxy(x, y + 5);
    printf("  ################    \n");
    gotoxy(x, y + 6);
    printf("  ################    \n");
    gotoxy(x, y + 7);
    printf("   ##############     \n");
    gotoxy(x, y + 8);
    printf("    ############      \n");

    return;
}

void pdot(int x, int y)
{
    gotoxy(x, y);
    printf("   ###  ###  ###      \n");
    gotoxy(x, y + 1);
    printf("   ###  ###  ###      \n");
    gotoxy(x, y + 2);
    printf("   ###  ###  ###      \n");
    gotoxy(x, y + 3);
    printf("## ###  ###  ###      \n");
    gotoxy(x, y + 4);
    printf("## #############   ## \n");
    gotoxy(x, y + 5);
    printf("################# ### \n");
    gotoxy(x, y + 6);
    printf(" #################### \n");
    gotoxy(x, y + 7);
    printf("  #################   \n");
    gotoxy(x, y + 8);
    printf("   ##############     \n");

    return;
}


void clear()
{
    for (int i = 0; i < 5; i++)
    {
        gotoxy(11, 18 + i);
        printf("                                                              ");
    }

    return;
}

void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clear_cursor(char show)//커서숨기기
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
// 21.5  //플레이어쪽 이미지 좌표
// 59,5  //컴퓨터쪽 이미지 좌표
