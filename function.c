#include "main.h"



void titleDot() {
	textcolor(15);
	gotoxy(0, 0);
	printf("\n\n\n\n\n\n");
	printf("                                    ####     ####   #     #     ####      ####      #       \n");
	printf("                                   #        #       #     #    #    #    #    #     #       \n");
	printf("                                   ####     #       # ### #    #    #    #    #     #       \n");
	printf("                                       #    #       #     #    #    #    #    #     #       \n");
	printf("                                   ####      ####   #     #     ####      ####      ####### \n");
}

int start_option(char option1[30], char option2[30], char option3[30], int x, int y, int n, int enter)
{

	int select = 1;
	int key;
	char start[5][15] = { "", "", "", "", "" };

	clear_cursor(0);
	strcpy(start[1], option1);
	strcpy(start[2], option2);
	strcpy(start[3], option3);

	gotoxy(x, y);
	textcolor(14);
	printf("%s", start[1]);

	gotoxy(x, y + enter);
	textcolor(15);
	printf("%s", start[2]);

	gotoxy(x, y + enter * 2);
	textcolor(15);
	printf("%s", start[3]);

	while (1)
	{
		fseek(stdin, 0, SEEK_END);
		key = getch();

		if (key == 224)
		{
			key = getch();
			switch (key)
			{
			case 72://선택지를 위로 올린다. (=2, 3의 위치에 있다.)
				if ((1 < select) && (n >= select))
				{
					select--;

					gotoxy(x, y + (select - 2) * enter);
					textcolor(15);
					printf("%s", start[select - 1]);

					gotoxy(x, y + (select - 1) * enter); //선택된 친구
					textcolor(14);
					printf("%s", start[select]);

					gotoxy(x, y + select * enter);
					textcolor(15);
					printf("%s", start[select + 1]);


					if (select != 2)
					{
						gotoxy(x, y + (select + 1) * enter);
						textcolor(15);
						printf("%s", start[select + 2]);
					}
				}
				break;

			case 80: //선택지를 아래로 내린다. (= 1, 2의 위치에 있다.)
				if (n > select)
				{
					select++;

					if (select > 2)
					{
						gotoxy(x, y + (select - 3) * enter);
						textcolor(15);
						printf("%s", start[select - 2]);
					}

					gotoxy(x, y + (select - 2) * enter);
					textcolor(15);
					printf("%s", start[select - 1]);

					gotoxy(x, y + (select - 1) * enter); //선택된 친구
					textcolor(14);
					printf("%s", start[select]);

					if (select != 3)
					{
						gotoxy(x, y + select * enter);
						textcolor(15);
						printf("%s", start[select + 1]);
					}
				}
				break;

			}
		}
		else if (key == 13)
		{
			textcolor(15);
			return select;
		}

	}
}

void set_name(char name[30])
{
	int answer;
	int re;
	clear_cursor(0);

	while (1)
	{
		int re = 0;

		cls;
		//콘솔 가로 총 길이 120

		gotoxy(43, 12);
		printf("나의 이름을 정해주세요 : ________\n"); //32 60-16
		gotoxy(42, 13);
		printf("한글 이름만 가능합니다. (최대 4글자)"); //36 60-18

		//입력버퍼를 초기화 시켜준다.
		fseek(stdin, 0, SEEK_END);

		//유니코드 기준 한글은 2바이트이므로 크기를 최소 (입력받는 글자수)x2 + 1로 설정해야 한다. 
		gotoxy(68, 12);
		fgets(name, 10, stdin);

		if (name[0] == '\n')
			re = 1;

		//fgets사용시, 마지막은 \n값이 들어오므로 \n 대신 NULL값을 넣어준다. 
		name[strlen(name) - 1] = '\0';

		// 한글이인지 아닌지 파악하고 한글이면 re를 1로 바꾼다. 1바이트는 최대 1111 1111이므로 1 0000 0000(0x80)과 &연산을 하면 2바이트인지 구분 가능하다. 
		for (int i = 0; i < strlen(name); i += 2)
			if ((name[i] & 0x80) != 0x80)
				re = 1;

		clear_cursor(1);
		if (re == 1)
		{
			textcolor(12);
			gotoxy(36, 12);
			printf("지원하지 않는 입력 방식입니다. 다시 시도하세요.\n"); //60 24
			Sleep(1000);
			textcolor(15);
			continue;
		}

		gotoxy(44, 16);
		printf("당신의 이름은 %s입니다.\n", name);
		answer = start_option(" 맞아", "아니야", "", 56, 18, 2, 2);

		gotoxy(29, 14);
		if (answer == 1)
			break;
		else if (answer == 2)
			continue;
	}
	return;

}

void story_square(int x, int y, int r, int h) //(시작 x위치, y위치, r가로크기, h세로크기) 기본 : (3, 20, 110, 7)
{
	clear_cursor(0);

	gotoxy(x, y);
	printf("┏");
	for (int i = 1; i <= r; i++)
	{
		gotoxy(x + i, y);
		printf("━");
	}
	gotoxy(x + r + 1, y);
	printf("┓\n");


	for (int j = 0; j < h; j++)
	{
		y++;
		gotoxy(x, y);
		printf("┃");
		for (int i = 1; i <= r; i++)
		{
			gotoxy(x + i, y);
			printf(" ");
		}
		gotoxy(x + r + 1, y);
		printf("┃\n");
	}

	y++;
	gotoxy(x, y);
	printf("┗");
	for (int i = 1; i <= r; i++)
	{
		gotoxy(x + i, y);
		printf("━");
	}
	gotoxy(x + r + 1, y);
	printf("┛\n");
	gotoxy(0, 0);
}


void map_print(struct player* pl, int startX, int map[ROWS][COLS])
{
	int helper, helper2;

	cls;

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("이동 : ←↕→ 방향키로 캐릭터를 이동시킬 수 있습니다. ");
	gotoxy(8, 24);
	printf("플레이어 캐릭터가 적과 마추치면 전투가 시작됩니다. ");
	Sleep(500);
	gotoxy(8, 26);
	printf("몬스터를 죽이면 플레이어가 자신감을 얻게 됩니다. 자신감 3을 얻으면 승리합니다. ");

	if (map[1][1] == 0)
	{

		for (int i = 0; i < ROWS; i++) //세로
		{
			for (int j = 2; j < COLS; j++) //가로
			{
				if ((i == 0) || (i == ROWS - 1) || (j >= COLS - 2) || (j == startX - 4))
				{
					if (j % 2 == 0)
						map[i][j] = 1;
					if (j % 2 != 0)
						map[i][j] = 9;
				}
				else
				{
					if (j % 2 == 0)
						map[i][j] = 0;
					if (j % 2 != 0)
						map[i][j] = 9;
				}

				if (j < startX - 4)
					map[i][j] = 0;

			}
		}
	}
	gotoxy(6, 1); textcolor(15); printf("현재 상태 : 이름 \"%s\", 자신감 %d (나 : '@')           가해자(■) 방관자(▲) 동조자(●)", pl->name, pl->confidence);
	gotoxy(0, 2);

	for (helper = 0; helper < ROWS; helper++) // 배열의 벽과 공간 표현
	{
		for (helper2 = 0; helper2 < COLS; helper2++)
		{
			if (map[helper][helper2] == 1)
			{

				textcolor(8);
				printf("■");
			}
			else if (map[helper][helper2] == 0)
			{
				printf("  ");
			}
		}
		printf("\n");
	}


}

int move_player(struct player* pl, struct monster* mon) // 플레이어의 움직임 구현 함수
{
	int map_re = 0;
	int X = 8, Y = 1; //플레이어 초기 출력 위치 
	int startX = 6, startY = 3; //플레이어 움직임 제한 벽 위치 (짝수로만)
	int direction, checker; // 방향키
	int save_on;

	int map[ROWS][COLS] = { 0, };

	cls;
	map_print(pl, startX, map); // 맵 출력하기 
	clear_cursor(0); // 커서 지우기

	monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);

	while (1) // 플레이어의 움직임
	{
		if (pl->confidence >= 3)
			return 0;
		if (map_re == 1)
		{
			cls;
			gotoxy(50, 15);
			printf("세이브 하시겠습니까?");
			save_on = start_option(" 세이브", "계속하기", "", 56, 20, 2, 3);
			cls;
			if (save_on == 1)
				return 1;

			map_print(pl, startX, map);
			map_re = 0;
		}

		fseek(stdin, SEEK_END, 0); // 입력버퍼 지우기
		direction = getch(); // 플레이어가 움직일 방향키 입력 받음

		textcolor(14);
		gotoxy(X, Y + 2); // 플레이어의 현재 좌표
		printf("@");

		textcolor(14);

		switch (direction) // 플레이어 방향키 입력 받았을 때
		{
		case UP: // 위 방향키 입력 시 
			gotoxy(X, Y + 2); // 플레이어의 현재 좌표
			printf(" "); // 이전에 출력된 좌표의 문자 지우기
			Y -= 1; // Y좌표의 -1 만큼 이동
			checker = keeper(map, X, Y, startX - 4); // map배열 주소와 좌표 넘겨줌

			if (checker == 1) // 이동 가능한 경우(map벽 안) 
			{
				gotoxy(X, Y + 2); // 플레이어의 현재 좌표
				printf("@"); // Y-1 만큼 이동한 좌표에 출력
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}
			else if (checker == 0) // 이동 불가능한 경우(map벽 앞)
			{
				Y += 1; // 이동한 Y-1 좌표를 +1 하여 다시 처음 좌표로 바꿈
				gotoxy(X, Y + 2); // 플레이어의 현재 좌표
				printf("@"); // 현재 좌표에 플레이어 출력
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}
		case DOWN: // 아래 방향키 입력 시
			gotoxy(X, Y + 2); // 플레이어의 현재 좌표
			printf(" "); // 이전에 출력된 좌표의 문자 지우기
			Y += 1; // Y좌표의 +1 만큼 이동
			checker = keeper(map, X, Y, startX - 4); // map배열 주소와 좌표 넘겨줌

			if (checker == 1) // 이동 가능한 경우(map벽 안) 
			{
				gotoxy(X, Y + 2); // 플레이어의 현재 좌표
				printf("@"); // Y + 1 만큼 이동한 좌표에 출력
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}
			else if (checker == 0) // 이동 불가능한 경우(map벽 앞)
			{
				Y -= 1; // 이동한 Y+1 좌표를 -1 하여 다시 처음 좌표로 바꿈
				gotoxy(X, Y + 2); // 플레이어의 현재 좌표
				printf("@"); // 현재 좌표에 플레이어 출력
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}

		case LEFT: // 왼쪽 방향키 입력 시
			gotoxy(X, Y + 2); // 플레이어의 현재 좌표
			printf(" "); // 이전에 출력된 좌표의 문자 지우기
			X -= 2; //  X좌표의 -2 만큼 이동 (2바이트의 유니코드를 고려함)
			checker = keeper(map, X, Y, startX - 4); // map배열 주소와 좌표 넘겨줌

			if (checker == 1) // 이동 가능한 경우(map벽 안) 
			{
				gotoxy(X, Y + 2); // 플레이어의 현재 좌표
				printf("@"); //  X-2 만큼 이동한 좌표에 출력
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}
			else if (checker == 0) // 이동 불가능한 경우(map벽 앞)
			{
				X += 2; // 이동한 X-2 좌표를 +2 하여 다시 처음 좌표로 바꿈
				gotoxy(X, Y + 2); // 플레이어의 현재 좌표
				printf("@"); // 현재 좌표에 플레이어 출력
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}

		case RIGHT: // 오른쪽 방향키 이동 시
			gotoxy(X, Y + 2); // 플레이어의 현재 좌표
			printf(" "); // 이전에 출력된 좌표의 문자 지우기
			X += 2; //  Y좌표의 +2 만큼 이동 (2바이트의 유니코드를 고려함)
			checker = keeper(map, X, Y, startX - 4); // map배열 주소와 좌표 넘겨줌

			if (checker == 1)
			{
				gotoxy(X, Y + 2); // 플레이어의 현재 좌표
				printf("@"); //  X+2 만큼 이동한 좌표에 출력
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}
			else if (checker == 0)
			{
				X -= 2; // 이동한 X+2 좌표를 -2 하여 다시 처음 좌표로 바꿈
				gotoxy(X, Y + 2);
				printf("@");
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//몬스터 구현 함수
				break;
			}
		}
	}
}

int keeper(int(*map)[COLS], int X, int Y, int n)
{
	int x = X - n;
	int checker;

	if (*(*(map + Y) + x) == 0)
	{
		checker = 1;
	}
	else
	{
		checker = 0;
	}
	return checker;
}

void monster_move(struct player* pl, struct monster* mon, int X, int Y, int startX, int startY, int* map_re)
{
	char monster_name[5] = { 0, };

	do
	{

		while (((mon->at.monsterX == 0) && (mon->at.monsterY == 0)) || (((mon->at.monsterX <= 8) && (mon->at.monsterY <= 5)))) //ROWS COLS/2
		{
			srand((unsigned int)time(NULL));
			mon->at.monsterX = rand() % (COLS - 25);

			srand((unsigned int)time(NULL) + 5);
			mon->at.monsterY = rand() % (ROWS - 4);


			if (mon->at.monsterX % 2 == 1)
				mon->at.monsterX += (startX + 3);
			mon->at.monsterX += (startX + 4);
			mon->at.monsterY += startY;
		}

		while (((mon->by.monsterX == 0) && (mon->by.monsterY == 0)) || ((mon->by.monsterX <= 8) && (mon->by.monsterY <= 5))) //ROWS COLS/2
		{
			srand((unsigned int)time(NULL) + 10);
			mon->by.monsterX = rand() % (COLS - 25);

			srand((unsigned int)time(NULL) + 15);
			mon->by.monsterY = rand() % (ROWS - 4);

			if (mon->by.monsterX % 2 == 1)
				mon->by.monsterX += (startX + 5);
			mon->by.monsterX += (startX + 4);
			mon->by.monsterY += startY;
		}

		while (((mon->sy.monsterX == 0) && (mon->sy.monsterY == 0)) || (((mon->sy.monsterX <= 8) && (mon->sy.monsterY <= 5)))) //ROWS COLS/2
		{
			srand((unsigned int)time(NULL) + 20);
			mon->sy.monsterX = rand() % (COLS - 25);

			srand((unsigned int)time(NULL) + 25);
			mon->sy.monsterY = rand() % (ROWS - 4);


			if (mon->sy.monsterX % 2 == 1)
				mon->sy.monsterX += (startX + 1);
			mon->sy.monsterX += (startX + 4);
			mon->sy.monsterY += startY;
		}
	} while (((mon->at.monsterX == mon->by.monsterX) && (mon->at.monsterY == mon->by.monsterY)) || ((mon->by.monsterX == mon->sy.monsterX) && (mon->by.monsterY == mon->sy.monsterY)) || ((mon->sy.monsterX == mon->at.monsterX) && (mon->sy.monsterY == mon->at.monsterY)));


	if (pl->monster_kill_at == 0)
	{
		gotoxy(mon->at.monsterX, mon->at.monsterY);
		printf("■");
		if ((X == mon->at.monsterX) && (Y == mon->at.monsterY))
		{
			strcpy(monster_name, "at");
			cls;
			monster_fight(pl, mon, monster_name);

			pl->monster_kill_at = '2';
			*map_re = 1;
			cls;
		}
	}
	if (pl->monster_kill_by == 0)
	{
		gotoxy(mon->by.monsterX, mon->by.monsterY);
		printf("▲");
		if ((X == mon->by.monsterX) && (Y == mon->by.monsterY))
		{
			strcpy(monster_name, "by");
			cls;
			monster_fight(pl, mon, monster_name);

			*map_re = 1;
			pl->monster_kill_by = '2';
			cls;
		}
	}
	if (pl->monster_kill_sy == 0)
	{
		gotoxy(mon->sy.monsterX, mon->sy.monsterY);
		printf("●");
		if ((X == mon->sy.monsterX) && (Y == mon->sy.monsterY))
		{
			strcpy(monster_name, "sy");
			cls;
			monster_fight(pl, mon, monster_name);

			*map_re = 1;
			pl->monster_kill_sy = '2';
			cls;
		}
	}
}

void monster_fight(struct player* pl, struct monster* mon, char monster_name[5])
{
	textcolor(15);
	char c1;

	fseek(stdin, 0, SEEK_END);

	story_square(3, 20, 110, 7);

	gotoxy(8, 22);
	printf("스페이스 바(Space bar)를 연타해서 데미지를 줄 수 있습니다.");
	getch();

	while (strcmp(monster_name, "at") == 0)
	{
		story_square(3, 20, 110, 7);
		gotoxy(8, 22);
		printf("가해자 선배, 나를 주로 괴롭히는 사람이다.");
		dot_printf(monster_name);
		gotoxy(20, 24);
		printf("        ");
		gotoxy(8, 24);
		printf("악몽 HP : %d", mon->at.hp);

		Sleep(100);
		fseek(stdin, 0, SEEK_END);
		c1 = getch();
		if (c1 == ' ') // '97'은 문자 97을 나타내서 그냥 97로 바꾸거나 'a'를 써야해
		{
			mon->at.hp--; //몬스터 hp 깎이는 함수

		}
		if (mon->at.hp == -1) //몬스터 hp가 0이면 레벨이 오름
		{
			pl->confidence++;

			break;
		}
	}

	while (strcmp(monster_name, "by") == 0)
	{
		story_square(3, 20, 110, 7);
		gotoxy(8, 22);
		printf("얼굴을 찌푸린 채로 그냥 지켜보기만 하는 사람들이다. ");
		dot_printf(monster_name);
		gotoxy(20, 24);
		printf("        ");
		gotoxy(8, 24);
		printf("악몽 HP : %d", mon->by.hp);

		Sleep(100);
		fseek(stdin, 0, SEEK_END);
		c1 = getch();
		if (c1 == ' ') // '97'은 문자 97을 나타내서 그냥 97로 바꾸거나 'a'를 써야해
		{
			mon->by.hp--; //몬스터 hp 깎이는 함수

		}
		if (mon->by.hp == -1) //몬스터 hp가 0이면 레벨이 오름
		{
			pl->confidence++;

			break;
		}
	}

	while (strcmp(monster_name, "sy") == 0)
	{
		story_square(3, 20, 110, 7);
		gotoxy(8, 22);
		printf("동조자 선배님들, 옆에서 웃으면서 지켜본다. 아직도 귀에 웃음소리가 아른거린다.");
		dot_printf(monster_name);
		gotoxy(20, 24);
		printf("        ");
		gotoxy(8, 24);
		printf("악몽 HP : %d", mon->sy.hp);

		Sleep(100);
		fseek(stdin, 0, SEEK_END);
		c1 = getch();
		if (c1 == ' ') // '97'은 문자 97을 나타내서 그냥 97로 바꾸거나 'a'를 써야해
		{
			mon->sy.hp--; //몬스터 hp 깎이는 함수

		}
		if (mon->sy.hp == -1) //몬스터 hp가 0이면 레벨이 오름
		{
			pl->confidence++;

			break;
		}
	}
	gotoxy(59, 15);
	printf("승리");
	Sleep(1000);
}



void save_data(struct player pl, struct monster mon)
{
	cls;
	int n[2] = { 0, };
	char player_savename[20] = "player_save";

	printf("현재 상태 : 이름 \"%s\", 자신감 %d,", pl.name, pl.confidence);
	n[0] = start_option("세이브 1", "세이브 2", "세이브 3", 8, 7, 3, 6) + 48; //문자열로 만들기 위해서 아스키 코드값 맞춰주기

	if (pl.name[0] != NULL)
	{
		FILE* player_save = NULL;

		strcat(player_savename, n);

		player_save = fopen(player_savename, "wb");

		if (player_save == NULL)
			printf("심각한 오류가 발생하였습니다. ");

		fwrite(&pl, sizeof(struct player), 1, player_save);
		fwrite(&mon, sizeof(struct monster), 1, player_save);

		fclose(player_save);
	}
	else
	{
		textcolor(12);
		gotoxy(40, 12);
		printf("이름을 설정한 뒤에 세이브가 가능합니다.\n");
		Sleep(700);
		textcolor(15);
		cls;
	}
	return;
} //

void load_data(struct player* pl, struct monster* mon)
{
	cls;
	int n[2] = { 0, };
	char player_savename[20] = "player_save";


	n[0] = start_option("로드 1", "로드 2", "로드 3", 8, 7, 3, 6) + 48; //문자열로 만들기 위해서 아스키 코드값 맞춰주기

	strcat(player_savename, n);

	if ((access(player_savename, 00) == 0)) //읽기 접근이 허용되는지 조사
	{
		FILE* player_load = NULL;
		player_load = fopen(player_savename, "rb");

		if (player_load == NULL)
			printf("심각한 오류가 발생하였습니다. ");

		fread(pl, sizeof(struct player), 1, player_load);
		fread(mon, sizeof(struct monster), 1, player_load);


		Sleep(2000);

		fclose(player_load);
	}
	else
	{
		textcolor(12);
		gotoxy(35, 12);
		printf("존재하지 않는 세이브 파일입니다. 다시 시도하세요.\n");
		Sleep(700);
		textcolor(15);
		cls;
	}

}



void prolog(char name[30])
{
	clear_cursor(0);

	gotoxy(46, 4);
	printf("나는 학교폭력을 당하고 있다."); //문자열 길이 : 28
	Sleep(500);
	gotoxy(17, 6);
	printf("시작은 1학년이 여름방학이 다가올 무렵, 봉사활동 시간을 채우기 위해 선도부를 할 때였다.");//86
	Sleep(500);
	gotoxy(32, 7);
	printf("그저 지나가던 길에 담배를 피우던 선배와 마주치게 되었다."); //56
	Sleep(500);
	gotoxy(43, 9);
	printf("\"에이 씨, 뭘 꼬라봐. 담배 피잖아.\""); //34
	Sleep(500);
	gotoxy(45, 11);
	printf("당시의 내가 들은건 욕설이었다."); //30
	Sleep(500);
	gotoxy(18, 12);
	printf("원래부터 평판이 안좋은 우리 학교였지만, 선배에게 대놓고 욕설을 들은 일은 처음이었다."); //84
	Sleep(500);
	gotoxy(54, 14);
	printf("...다음날..."); //12
	Sleep(500);
	gotoxy(46, 15);
	printf("어제 마주친 선배가 찾아왔다."); //28
	Sleep(500);
	gotoxy(52, 17);
	printf("\"야, %s 나와.\"", name);//16
	Sleep(500);
	gotoxy(37, 19);
	printf("나는 그대로 어제의 그 장소로 끌려가게 되었다."); //46
	Sleep(500);
	gotoxy(42, 20);
	printf("이유조차 모르는 지옥의 시작이었다...");//36

	gotoxy(60, 28);
	printf("넘어가려면 아무 버튼이나 누르세요....");

	fseek(stdin, 0, SEEK_END);
	getch();
	cls;
}

void story()
{
	fseek(stdin, 0, SEEK_END);

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("오늘도 평소와 같은 하루였다.");
	Sleep(500);
	gotoxy(8, 24);
	printf("매일매일 기도하고는 한다. 제발 평화로운 하루가 찾아오기를...하고");
	Sleep(500);
	gotoxy(8, 26);
	printf("이 상황을 벗어나기 위한 노력은 해봤다.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("어느 하루는 소리치며 도움을 요청했고, 어느 하루는 인생 처음으로 등교거부를 해봤다.");
	Sleep(500);
	gotoxy(8, 24);
	printf("그렇게 노력해보아도 바뀌는 일은 없었다.");
	Sleep(500);
	gotoxy(8, 26);
	printf("그저 몸에 상처만 늘어갈 뿐이었다.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("점차 포기하는 법을 배워나갔다.");
	Sleep(500);
	gotoxy(8, 24);
	printf("아무리 노력해보아도 바뀌는 일은 없었다.");
	Sleep(500);
	gotoxy(8, 26);
	printf("....");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"아, 아무것도 하기 싫다..\"");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("거실에 누워서 멍하니 중얼거렸다. ");
	Sleep(500);
	gotoxy(8, 24);
	printf("엄마는 안계셨고, 아빠는 3개월 전에 해외로 출장 나가셨다.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("사실 이번 일을 겪게 되고서 제일 먼저 울며 아빠에게 연락했었다. ");
	Sleep(500);
	gotoxy(8, 24);
	printf("연락을 받지 않는 아빠를 원망하며 눈물을 쏟아내기도 하였다.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"...");
	Sleep(500);
	printf("결국 연락은 안 받으셨지... \"");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("참으로 어리석었던 과거를 떠올리며 나는 눈을 감았다. ");
	getch();

	for (int i = 0; i < 2; i++)
	{
		gotoxy(0, 2);
		printf("                                                                                                                      \n");
		printf("       ■■■■■■■■■■■■                                          ■■■■■■■■■■■■                     \n");
		printf("         ■■■■■■■■■■                                              ■■■■■■■■■                         \n");
		printf("                     ■■■              ■■■■■■■■■                          ■■■                           \n");
		printf("                 ■■■■                  ■■■■■■■                         ■■■■                            \n");
		printf("               ■■■■                          ■■■                         ■■■■                              \n");
		printf("          ■■■■■                          ■■■                        ■■■■■                                \n");
		printf("      ■■■■■■■■■■                  ■■■                        ■■■■■■■■■■                        \n");
		printf("    ■■■■■■■■■■■■              ■■■■■■■■              ■■■■■■■■■■■■                      \n");
		printf("                                        ■■■■■■■■■■                                                          \n");

		gotoxy(105, 11);
		for (int j = i; j < 3; j++)
		{
			printf("■ ");
			Sleep(500);
		}
	}
	cls;
}

void ending()
{
	clear_cursor(0);
	cls;

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("가해자, 난 너한테 지지 않을거야!!!");
	Sleep(500);
	getch();

	cls;

	gotoxy(50, 4);
	printf("아하... 아, 어라...?"); //20
	Sleep(500);
	gotoxy(55, 6);
	printf("여기는...."); //10
	Sleep(500);
	gotoxy(43, 7);
	printf("틀림없이 나의 방에 나의 침대 위다."); //34
	Sleep(500);
	getch();

	gotoxy(32, 9);
	printf("이젠 결국 가해자가 꿈에서 괴물로 나오는 지경에 이르렀다.");//56
	Sleep(500);
	gotoxy(47, 11);
	printf("하지만 기분이 나쁘진 않다.");//26
	Sleep(500);
	gotoxy(44, 12);
	printf("왠지 뭐랄까.. 기운이 난다고 할까"); //32
	Sleep(500);
	gotoxy(51, 14);
	printf("뭐지 이 자신감은..");//18
	Sleep(500);
	gotoxy(49, 16);
	printf("\"난 너한테 지지 않아!!!\"");//22
	Sleep(500);
	gotoxy(38, 18);
	printf("이건 가해자를 물리쳤을 때의 순간의 감각이다."); //44
	Sleep(500);
	gotoxy(39, 20);
	printf("속에서부터 차오르는 자신감이 느껴졌다.");//38
	Sleep(500);
	getch();

	cls;

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("..따르르릉..");
	Sleep(500);
	gotoxy(8, 24);
	printf("\"여보세요?\"");
	Sleep(500);
	gotoxy(8, 26);
	printf("-애야, 아빠야 잘 지내니?");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"아빠? 어째서 이제야 연락하시는 거예요!!\"");
	Sleep(500);
	gotoxy(8, 24);
	printf("-미안하구나, 일이 생기는 바람에 연락을 못 했단다...");
	Sleep(500);
	gotoxy(8, 26);
	printf(".....");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("-그래 무슨 일 없고?");
	Sleep(500);
	gotoxy(8, 24);
	printf("\"...네\"");
	Sleep(500);
	gotoxy(8, 26);
	printf("-정말?");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"...네, 정말로...\"");
	Sleep(500);
	gotoxy(8, 24);
	printf("-......");
	Sleep(500);
	gotoxy(8, 26);
	printf("......");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("-애야 잘 들으렴, 넌 혼자가 아니란다.");
	Sleep(500);
	gotoxy(8, 24);
	printf(" 평소에는 잘 모르겠고 느껴지지 않아도");
	Sleep(500);
	gotoxy(8, 26);
	printf(" 네 주위에는 언제나 누군가가 있다는 걸 잊지마렴.");
	getch();

	system(cls);

	gotoxy(22, 9);
	printf("그래, 나는 아빠의 진심어린 말과 꿈 속에서 쓰러트린 괴물을 떠올리고 다짐했다."); //76
	Sleep(500);
	gotoxy(51, 11);
	printf("\"아빠... 사실은..\""); //18
	Sleep(500);
	gotoxy(41, 14);
	printf("이제 모두 마무리 지을 수 있을 것 같다."); //38
	Sleep(500);
	getch();


	system(cls);

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("[며칠 후]");
	Sleep(500);
	gotoxy(8, 24);
	printf("다음 소식 전해 드립니다. 지난 xx월 집단 따돌림을 주도하던 청소년 4명이 구속되었습니다.");
	Sleep(500);
	gotoxy(8, 26);
	printf("경찰은 피해 학생의 신고로 빠르게 조취를 취할 수 있었다고 밝혔습니다.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("학교폭력 신고는 112 혹은 117로 신고하시면 도움을 받으실 수 있습니다.");
	Sleep(500);
	gotoxy(8, 24);
	printf("이 소식을 듣고 계신 여러분의 주변에는 언제나 도움의 손길이 있다는 걸 잊지 말아 주시길 바랍니다.");
	Sleep(500);
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("이것으로 오늘 소식은 여기까지 전해드립니다.");
	Sleep(500);
	gotoxy(8, 24);
	printf("시청해주신 여러분 감사합니다.");
	Sleep(500);

	cls;
}

void dot_printf(char monster_name[5])
{
	if (strcmp(monster_name, "at") == 0)
	{
		gotoxy(0, 5);
		printf("                                         ■■■■■                                                           \n");
		printf("                                     ■■■■■■■■■          친하게 지내자는 건데, 너무하네               \n");
		printf("                                  ■■■■ ■■■■■■■                                                     \n");
		printf("                                 ■■■■ ─ ■ ─ ■■■■                                                   \n");
		printf("                                 ■■■■ ■    ■  ■■■                                                    \n");
		printf("                                 ■■■■           ■■■                                                    \n");
		printf("                                 ■■■■   └─┘  ■■■                                                    \n");
		printf("      요즘 OOO이랑 친하다며?    ■■  ■■─┬─┬─■■■                                                    \n");
		printf("                                ■■    ■■└─┘  ■■■                                                    \n");
		printf("                               ■■     ■■       ■■■                                                     \n");
	}
	else if (strcmp(monster_name, "by") == 0)
	{
		gotoxy(0, 5);
		printf("                                                ■■■■■               쟤가 선배에게 불려간 친구지?          \n");
		printf("     우리 학교 일진 소문은 들었는데 무섭네  ■■■■■■■■■                                                 \n");
		printf("                                           ■■■■■■■■■■■                                              \n");
		printf("                                          ■■■■■■■■■■■■                                             \n");
		printf("                                         ■■■■■■■■■■■■■                                            \n");
		printf("                                         ■■■■■■■■■■■■■                                            \n");
		printf("                                          ■■■■■■■■■■■■                                             \n");
		printf("        신고해야하나?                       ■■■■■■■■■■                                               \n");
		printf("                                              ■■■■■■■■                나까지 휘말리면 어쩌지..         \n");
		printf("                                          ■■■■■■■■■■■■                                             \n");
		printf("                                        ■■■■■■■■■■■■■■                                           \n");
	}
	else if (strcmp(monster_name, "sy") == 0)
	{
		gotoxy(0, 5);
		printf("                                            ■■■■■■                                                        \n");
		printf("                                         ■■■■■■■■■                                                     \n");
		printf("                                      ■■■■     ■  ■■■                                                   \n");
		printf("                                     ■■■■ ─    ─  ■■■                                                  \n");
		printf("                                     ■■■■ ■    ■  ■■■                                                  \n");
		printf("                                     ■■■■           ■■■                                                  \n");
		printf("                                     ■■■■■ └─   ■■■■                                                 \n");
		printf("                                    ■■■■■■┬─┬■■■■■                                                \n");
		printf("                                       ■■■   └─┘   ■■■                                                 \n");
		printf("                                          ┃               ┃                                                   \n");
	}


}



//콘솔의 x, y의 좌표로 커서를 이동한다. 
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서숨기기
void clear_cursor(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//텍스트 색깔 변경하기
void textcolor(int color_number)

{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
