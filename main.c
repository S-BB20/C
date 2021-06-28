#include<stdio.h>
#include<stdlib.h> //rand, strcmp 함수를 사용
#include<time.h> //time 함수를 사용
#include<windows.h> //system 함수를 사용
#include<stdbool.h>//while(true)함수를 사용
#include<conio.h> //getch 함수 사용
#include<string.h> //strcpy 함수 사용

/*  number_ani('0', 14, 10);
	number_ani('S', 30, 10);
	number_ani('5', 46, 10);
	number_ani('B', 62, 10); */

int title();

void set_player(int arr[], int turn);
void set_com(int arr[]);
void arr_compare(int player[], int com[], int x, int y);

void background(void);

void ball_dot(int number_i, int x, int y); //number_ani('0', 14, 10);
void ball_p(char a, char b, char c, char d);

void gotoxy(int x, int y);

int main(void)
{
	system("mode con cols=90 lines=42");
	while (true)
	{
		switch (title())
		{
		case 0:
			system("cls");
			break;   //게임시작

		case 1:
			system("cls");
			exit(0); //게임종료
		}

		system("cls");
		background();


		int player[5] = { -1, -1, -1, -1, -1 };
		int com[5] = { -1, -1, -1, -1, -1 };

		set_com(com);
		ball_p('E', 'S', 'E', 'B');
		//ball_p(com[0] + 48, com[1] + 48, com[2] + 48, com[3] + 48);

		int x = 19;
		int y = 24;

		for (int i = 0; i < 27; i++)
		{
			set_player(player, i);
			arr_compare(player, com, x, y);

			if (y < 32)
			{
				y++;
			}

			else
			{
				y = 24;
				x += 20;
			}
		}

		system("cls");
	}
	system("cls");
	return 0;
}


int title()
{
	char dote[20][90];
	memset(dote, 0, sizeof(dote));
	//(x * x + y * y) <= r * r

	int x, y, R = 40;




	for (x = -R - 1; x < R + 2; x += 2) //콘솔 화면의 가로 : 세로가 1 : 2 이다. 
	{

		for (y = -R - 5; y < R + 5; y++) {

			if ((x * x + y * y) <= R * R)

				printf(" ");

			else
				printf("#");

		}

		if (x != R + 1)
			printf("\n");

	}


	strcpy(dote[1], "     #####                #                 #      ############   ");
	strcpy(dote[2], "    ##   ##     ########   #         #####   #                #   ");
	strcpy(dote[3], "    #     #           ##    #      @#######@  #               #   ");
	strcpy(dote[4], " ############        ##     #      #@#####@#  ##              #   ");
	strcpy(dote[5], "       #            ##      ##    ###@###@### #              ##   ");
	strcpy(dote[6], "                   ###      ##    ###@###@### #              #    ");
	strcpy(dote[7], "    ######        ## ##     #     ###@###@### ##    ############  ");
	strcpy(dote[8], "   ##    ##      ##   ##    #      #@######@# #          ##       ");
	strcpy(dote[9], "  ##      ##    ##     ##   #      @#######@  #          ##       ");
	strcpy(dote[10], "  #        #    #       #   #        #####    #          ##       ");
	strcpy(dote[11], "                                                                 ");


	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 65; j++)
		{
			if (dote[i][j] == '@')
			{
				gotoxy(13 + j, 10 + i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("%c", dote[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (dote[i][j] == '#')
			{
				gotoxy(13 + j, 10 + i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("#");

			}
			else
			{
				gotoxy(13 + j, 10 + i);
				printf(" ");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}

	}

	int select = 0;

	gotoxy(41, 26);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("게임시작");

	gotoxy(41, 29);
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

				gotoxy(41, 26);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("게임시작");


				gotoxy(41, 29);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("게임종료");

				break;


			case 80:
				select = 1;

				gotoxy(41, 26);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("게임시작");

				gotoxy(41, 29);
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


void set_player(int arr[], int turn)
{
	while (1)
	{
		gotoxy(14, 22);
		printf("[%d턴] 숫자를 입력해주세요:____\b\b\b\b", turn + 1);

		int n;
		if (scanf("%d", &n) == 0)
		{
			gotoxy(39, 22);
			printf("                                              ");
			rewind(stdin);
			continue;
		}
		else if (n < 1000 || n > 9999)
		{
			gotoxy(39, 22);
			printf("                                              ");
			continue;
		}

		arr[0] = n / 1000;
		n = n % 1000;
		arr[1] = n / 100;
		n = n % 100;
		arr[2] = n / 10;
		n = n % 10;
		arr[3] = n / 1;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					break;

				if (arr[i] == arr[j])
				{
					n = -1;
				}

			}

		}

		if (n != -1)
			break;

		gotoxy(39, 22);
		printf("                                              ");
	}

	return;
}

void set_com(int arr[])
{
	srand(time(NULL));

	int n;

	for (int i = 0; i < 4; i++)
	{
		while (1)
		{
			n = rand() % 10;

			for (int j = 0; j < 4; j++)
			{
				if (arr[j] == n)
				{
					n = -1;
				}
			}

			if (n != -1)
			{
				arr[i] = n;
				break;
			}
		}
	}

	return;
}

void arr_compare(int player[], int com[], int x, int y)
{
	int strike = 0;
	int ball = 0;

	gotoxy(x, y);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (player[i] == com[j] && i == j)
				strike++;
			else if (player[i] == com[j] && i != j)
				ball++;
		}

	if (strike == 0 && ball == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			printf("%d", player[i]);
		}
		ball_p('E', 'E', 'E', 'E');
		gotoxy(x + 4, y);
		printf(" / OUT\n");
	}

	else if (strike == 4)
	{
		ball_p(com[0] + 48, com[1] + 48, com[2] + 48, com[3] + 48);
		gotoxy(x + 4, y);
		printf("승리하였습니다.");
		return 1;

	}

	else
	{
		for (int i = 0; i < 4; i++)
		{
			printf("%d", player[i]);
		}
		ball_p(strike + 48, 'S', ball + 48, 'B');
		gotoxy(x + 4, y);
		printf(" / %dS %dB\n", strike, ball);

	}

	strike = 0;
	ball = 0;

	return;
}


void ball_dot(int number_i, int x, int y)
{
	char color;
	char number[10][30];
	memset(number, 0, sizeof(number));

	if (number_i == '0')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], "  ###$$$$$###   ");
		strcpy(number[3], "####$#####$#### ");
		strcpy(number[4], "####$#####$#### ");
		strcpy(number[5], "####$#####$#### ");
		strcpy(number[6], "####$#####$#### ");
		strcpy(number[7], "####$#####$#### ");
		strcpy(number[8], "  ###$$$$$###   ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '1')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ######$######  ");
		strcpy(number[3], "#####$$$####### ");
		strcpy(number[4], "#######$####### ");
		strcpy(number[5], "#######$####### ");
		strcpy(number[6], "#######$####### ");
		strcpy(number[7], "#######$####### ");
		strcpy(number[8], " ###$$$$$$$###  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '2')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ####$$$$$####  ");
		strcpy(number[3], "###$#####$$#### ");
		strcpy(number[4], "#########$##### ");
		strcpy(number[5], "######$$####### ");
		strcpy(number[6], "#####$$######## ");
		strcpy(number[7], "####$$######### ");
		strcpy(number[8], " ###$$$$$$$###  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '3')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ###$$$$$$$###  ");
		strcpy(number[3], "###$$#####$$### ");
		strcpy(number[4], "#########$$#### ");
		strcpy(number[5], "######$$$$##### ");
		strcpy(number[6], "#########$$$### ");
		strcpy(number[7], "###$$#####$$### ");
		strcpy(number[8], " ###$$$$$$$###  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '4')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ###$$########  ");
		strcpy(number[3], "####$###$###### ");
		strcpy(number[4], "###$$###$###### ");
		strcpy(number[5], "##$$####$###### ");
		strcpy(number[6], "##$$$$$$$$$#### ");
		strcpy(number[7], "########$###### ");
		strcpy(number[8], " #######$#####  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '5')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ###$$$$$$$###  ");
		strcpy(number[3], "####$########## ");
		strcpy(number[4], "####$########## ");
		strcpy(number[5], "####$$$$$$##### ");
		strcpy(number[6], "#########$$#### ");
		strcpy(number[7], "####$####$$#### ");
		strcpy(number[8], " ####$$$$$####  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '6')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ####$$$$$####  ");
		strcpy(number[3], "####$#####$#### ");
		strcpy(number[4], "####$########## ");
		strcpy(number[5], "####$$$$$$##### ");
		strcpy(number[6], "####$#####$#### ");
		strcpy(number[7], "####$#####$#### ");
		strcpy(number[8], " ####$$$$$####  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '7')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ###$$$$$$$###  ");
		strcpy(number[3], "#########$$#### ");
		strcpy(number[4], "#########$$#### ");
		strcpy(number[5], "########$$##### ");
		strcpy(number[6], "#######$$###### ");
		strcpy(number[7], "######$$####### ");
		strcpy(number[8], " ####$$#######  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '8')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], " ####$$$$$####  ");
		strcpy(number[3], "####$#####$#### ");
		strcpy(number[4], "####$#####$#### ");
		strcpy(number[5], "#####$$$$$##### ");
		strcpy(number[6], "####$#####$#### ");
		strcpy(number[7], "####$#####$#### ");
		strcpy(number[8], " ####$$$$$####  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == '9')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "   ########     ");
		strcpy(number[2], " ####$$$$$####  ");
		strcpy(number[3], "####$#####$#### ");
		strcpy(number[4], "####$#####$#### ");
		strcpy(number[5], "#####$$$$$$#### ");
		strcpy(number[6], "##########$#### ");
		strcpy(number[7], "##########$#### ");
		strcpy(number[8], " ####$$$$$####  ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == 'B')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], "  ##@@@@@@###   ");
		strcpy(number[3], "####@#####@#### ");
		strcpy(number[4], "####@#####@#### ");
		strcpy(number[5], "####@@@@@@##### ");
		strcpy(number[6], "####@#####@#### ");
		strcpy(number[7], "####@#####@#### ");
		strcpy(number[8], "  ##@@@@@@###   ");
		strcpy(number[9], "    #######     ");

	}
	else if (number_i == 'S')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], "  ###@@@@@###   ");
		strcpy(number[3], "####@#####@#### ");
		strcpy(number[4], "####@########## ");
		strcpy(number[5], "#####@@@@@##### ");
		strcpy(number[6], "##########@#### ");
		strcpy(number[7], "####@#####@#### ");
		strcpy(number[8], "  ###@@@@@###   ");
		strcpy(number[9], "    #######     ");
	}
	else if (number_i == 'E')
	{
		strcpy(number[0], "                ");
		strcpy(number[1], "    #######     ");
		strcpy(number[2], "  ###########   ");
		strcpy(number[3], "############### ");
		strcpy(number[4], "############### ");
		strcpy(number[5], "############### ");
		strcpy(number[6], "############### ");
		strcpy(number[7], "############### ");
		strcpy(number[8], "  ###########   ");
		strcpy(number[9], "    #######     ");
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 18; j++)
		{

			if (number[i][j] == '@')
			{
				gotoxy(x + j, y + i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf("@");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (number[i][j] == '#')
			{
				gotoxy(x + j, y + i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("#");
			}

			else if (number[i][j] == '$')
			{
				gotoxy(x + j, y + i);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("#");
			}

			else
			{
				gotoxy(x + j, y + i);
				printf(" ");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}


	}
}

void ball_p(char a, char b, char c, char d)
{
	ball_dot(a, 14, 10);
	ball_dot(b, 30, 10);
	ball_dot(c, 46, 10);
	ball_dot(d, 62, 10);

	return;
}

void background(void)
{
	int x, y, R = 40;

	for (x = -R - 1; x < R + 2; x += 2) //콘솔 화면의 가로 : 세로가 1 : 2 이다. 
	{

		for (y = -R - 5; y < R + 5; y++) {

			if ((x * x + y * y) <= R * R)

				printf(" ");

			else
				printf("#");

		}

		if (x != R + 1)
			printf("\n");

	}

	return;
}



void gotoxy(int x, int y)
{
	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	return;
}
