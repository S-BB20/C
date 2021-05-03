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
			case 72://�������� ���� �ø���. (=2, 3�� ��ġ�� �ִ�.)
				if ((1 < select) && (n >= select))
				{
					select--;

					gotoxy(x, y + (select - 2) * enter);
					textcolor(15);
					printf("%s", start[select - 1]);

					gotoxy(x, y + (select - 1) * enter); //���õ� ģ��
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

			case 80: //�������� �Ʒ��� ������. (= 1, 2�� ��ġ�� �ִ�.)
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

					gotoxy(x, y + (select - 1) * enter); //���õ� ģ��
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
		//�ܼ� ���� �� ���� 120

		gotoxy(43, 12);
		printf("���� �̸��� �����ּ��� : ________\n"); //32 60-16
		gotoxy(42, 13);
		printf("�ѱ� �̸��� �����մϴ�. (�ִ� 4����)"); //36 60-18

		//�Է¹��۸� �ʱ�ȭ �����ش�.
		fseek(stdin, 0, SEEK_END);

		//�����ڵ� ���� �ѱ��� 2����Ʈ�̹Ƿ� ũ�⸦ �ּ� (�Է¹޴� ���ڼ�)x2 + 1�� �����ؾ� �Ѵ�. 
		gotoxy(68, 12);
		fgets(name, 10, stdin);

		if (name[0] == '\n')
			re = 1;

		//fgets����, �������� \n���� �����Ƿ� \n ��� NULL���� �־��ش�. 
		name[strlen(name) - 1] = '\0';

		// �ѱ������� �ƴ��� �ľ��ϰ� �ѱ��̸� re�� 1�� �ٲ۴�. 1����Ʈ�� �ִ� 1111 1111�̹Ƿ� 1 0000 0000(0x80)�� &������ �ϸ� 2����Ʈ���� ���� �����ϴ�. 
		for (int i = 0; i < strlen(name); i += 2)
			if ((name[i] & 0x80) != 0x80)
				re = 1;

		clear_cursor(1);
		if (re == 1)
		{
			textcolor(12);
			gotoxy(36, 12);
			printf("�������� �ʴ� �Է� ����Դϴ�. �ٽ� �õ��ϼ���.\n"); //60 24
			Sleep(1000);
			textcolor(15);
			continue;
		}

		gotoxy(44, 16);
		printf("����� �̸��� %s�Դϴ�.\n", name);
		answer = start_option(" �¾�", "�ƴϾ�", "", 56, 18, 2, 2);

		gotoxy(29, 14);
		if (answer == 1)
			break;
		else if (answer == 2)
			continue;
	}
	return;

}

void story_square(int x, int y, int r, int h) //(���� x��ġ, y��ġ, r����ũ��, h����ũ��) �⺻ : (3, 20, 110, 7)
{
	clear_cursor(0);

	gotoxy(x, y);
	printf("��");
	for (int i = 1; i <= r; i++)
	{
		gotoxy(x + i, y);
		printf("��");
	}
	gotoxy(x + r + 1, y);
	printf("��\n");


	for (int j = 0; j < h; j++)
	{
		y++;
		gotoxy(x, y);
		printf("��");
		for (int i = 1; i <= r; i++)
		{
			gotoxy(x + i, y);
			printf(" ");
		}
		gotoxy(x + r + 1, y);
		printf("��\n");
	}

	y++;
	gotoxy(x, y);
	printf("��");
	for (int i = 1; i <= r; i++)
	{
		gotoxy(x + i, y);
		printf("��");
	}
	gotoxy(x + r + 1, y);
	printf("��\n");
	gotoxy(0, 0);
}


void map_print(struct player* pl, int startX, int map[ROWS][COLS])
{
	int helper, helper2;

	cls;

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("�̵� : ��ա� ����Ű�� ĳ���͸� �̵���ų �� �ֽ��ϴ�. ");
	gotoxy(8, 24);
	printf("�÷��̾� ĳ���Ͱ� ���� ����ġ�� ������ ���۵˴ϴ�. ");
	Sleep(500);
	gotoxy(8, 26);
	printf("���͸� ���̸� �÷��̾ �ڽŰ��� ��� �˴ϴ�. �ڽŰ� 3�� ������ �¸��մϴ�. ");

	if (map[1][1] == 0)
	{

		for (int i = 0; i < ROWS; i++) //����
		{
			for (int j = 2; j < COLS; j++) //����
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
	gotoxy(6, 1); textcolor(15); printf("���� ���� : �̸� \"%s\", �ڽŰ� %d (�� : '@')           ������(��) �����(��) ������(��)", pl->name, pl->confidence);
	gotoxy(0, 2);

	for (helper = 0; helper < ROWS; helper++) // �迭�� ���� ���� ǥ��
	{
		for (helper2 = 0; helper2 < COLS; helper2++)
		{
			if (map[helper][helper2] == 1)
			{

				textcolor(8);
				printf("��");
			}
			else if (map[helper][helper2] == 0)
			{
				printf("  ");
			}
		}
		printf("\n");
	}


}

int move_player(struct player* pl, struct monster* mon) // �÷��̾��� ������ ���� �Լ�
{
	int map_re = 0;
	int X = 8, Y = 1; //�÷��̾� �ʱ� ��� ��ġ 
	int startX = 6, startY = 3; //�÷��̾� ������ ���� �� ��ġ (¦���θ�)
	int direction, checker; // ����Ű
	int save_on;

	int map[ROWS][COLS] = { 0, };

	cls;
	map_print(pl, startX, map); // �� ����ϱ� 
	clear_cursor(0); // Ŀ�� �����

	monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);

	while (1) // �÷��̾��� ������
	{
		if (pl->confidence >= 3)
			return 0;
		if (map_re == 1)
		{
			cls;
			gotoxy(50, 15);
			printf("���̺� �Ͻðڽ��ϱ�?");
			save_on = start_option(" ���̺�", "����ϱ�", "", 56, 20, 2, 3);
			cls;
			if (save_on == 1)
				return 1;

			map_print(pl, startX, map);
			map_re = 0;
		}

		fseek(stdin, SEEK_END, 0); // �Է¹��� �����
		direction = getch(); // �÷��̾ ������ ����Ű �Է� ����

		textcolor(14);
		gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
		printf("@");

		textcolor(14);

		switch (direction) // �÷��̾� ����Ű �Է� �޾��� ��
		{
		case UP: // �� ����Ű �Է� �� 
			gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
			printf(" "); // ������ ��µ� ��ǥ�� ���� �����
			Y -= 1; // Y��ǥ�� -1 ��ŭ �̵�
			checker = keeper(map, X, Y, startX - 4); // map�迭 �ּҿ� ��ǥ �Ѱ���

			if (checker == 1) // �̵� ������ ���(map�� ��) 
			{
				gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
				printf("@"); // Y-1 ��ŭ �̵��� ��ǥ�� ���
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
				break;
			}
			else if (checker == 0) // �̵� �Ұ����� ���(map�� ��)
			{
				Y += 1; // �̵��� Y-1 ��ǥ�� +1 �Ͽ� �ٽ� ó�� ��ǥ�� �ٲ�
				gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
				printf("@"); // ���� ��ǥ�� �÷��̾� ���
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
				break;
			}
		case DOWN: // �Ʒ� ����Ű �Է� ��
			gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
			printf(" "); // ������ ��µ� ��ǥ�� ���� �����
			Y += 1; // Y��ǥ�� +1 ��ŭ �̵�
			checker = keeper(map, X, Y, startX - 4); // map�迭 �ּҿ� ��ǥ �Ѱ���

			if (checker == 1) // �̵� ������ ���(map�� ��) 
			{
				gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
				printf("@"); // Y + 1 ��ŭ �̵��� ��ǥ�� ���
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
				break;
			}
			else if (checker == 0) // �̵� �Ұ����� ���(map�� ��)
			{
				Y -= 1; // �̵��� Y+1 ��ǥ�� -1 �Ͽ� �ٽ� ó�� ��ǥ�� �ٲ�
				gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
				printf("@"); // ���� ��ǥ�� �÷��̾� ���
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
				break;
			}

		case LEFT: // ���� ����Ű �Է� ��
			gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
			printf(" "); // ������ ��µ� ��ǥ�� ���� �����
			X -= 2; //  X��ǥ�� -2 ��ŭ �̵� (2����Ʈ�� �����ڵ带 �����)
			checker = keeper(map, X, Y, startX - 4); // map�迭 �ּҿ� ��ǥ �Ѱ���

			if (checker == 1) // �̵� ������ ���(map�� ��) 
			{
				gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
				printf("@"); //  X-2 ��ŭ �̵��� ��ǥ�� ���
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
				break;
			}
			else if (checker == 0) // �̵� �Ұ����� ���(map�� ��)
			{
				X += 2; // �̵��� X-2 ��ǥ�� +2 �Ͽ� �ٽ� ó�� ��ǥ�� �ٲ�
				gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
				printf("@"); // ���� ��ǥ�� �÷��̾� ���
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
				break;
			}

		case RIGHT: // ������ ����Ű �̵� ��
			gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
			printf(" "); // ������ ��µ� ��ǥ�� ���� �����
			X += 2; //  Y��ǥ�� +2 ��ŭ �̵� (2����Ʈ�� �����ڵ带 �����)
			checker = keeper(map, X, Y, startX - 4); // map�迭 �ּҿ� ��ǥ �Ѱ���

			if (checker == 1)
			{
				gotoxy(X, Y + 2); // �÷��̾��� ���� ��ǥ
				printf("@"); //  X+2 ��ŭ �̵��� ��ǥ�� ���
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
				break;
			}
			else if (checker == 0)
			{
				X -= 2; // �̵��� X+2 ��ǥ�� -2 �Ͽ� �ٽ� ó�� ��ǥ�� �ٲ�
				gotoxy(X, Y + 2);
				printf("@");
				monster_move(pl, mon, X, Y + 2, startX, startY, &map_re);//���� ���� �Լ�
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
		printf("��");
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
		printf("��");
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
		printf("��");
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
	printf("�����̽� ��(Space bar)�� ��Ÿ�ؼ� �������� �� �� �ֽ��ϴ�.");
	getch();

	while (strcmp(monster_name, "at") == 0)
	{
		story_square(3, 20, 110, 7);
		gotoxy(8, 22);
		printf("������ ����, ���� �ַ� �������� ����̴�.");
		dot_printf(monster_name);
		gotoxy(20, 24);
		printf("        ");
		gotoxy(8, 24);
		printf("�Ǹ� HP : %d", mon->at.hp);

		Sleep(100);
		fseek(stdin, 0, SEEK_END);
		c1 = getch();
		if (c1 == ' ') // '97'�� ���� 97�� ��Ÿ���� �׳� 97�� �ٲٰų� 'a'�� �����
		{
			mon->at.hp--; //���� hp ���̴� �Լ�

		}
		if (mon->at.hp == -1) //���� hp�� 0�̸� ������ ����
		{
			pl->confidence++;

			break;
		}
	}

	while (strcmp(monster_name, "by") == 0)
	{
		story_square(3, 20, 110, 7);
		gotoxy(8, 22);
		printf("���� ��Ǫ�� ä�� �׳� ���Ѻ��⸸ �ϴ� ������̴�. ");
		dot_printf(monster_name);
		gotoxy(20, 24);
		printf("        ");
		gotoxy(8, 24);
		printf("�Ǹ� HP : %d", mon->by.hp);

		Sleep(100);
		fseek(stdin, 0, SEEK_END);
		c1 = getch();
		if (c1 == ' ') // '97'�� ���� 97�� ��Ÿ���� �׳� 97�� �ٲٰų� 'a'�� �����
		{
			mon->by.hp--; //���� hp ���̴� �Լ�

		}
		if (mon->by.hp == -1) //���� hp�� 0�̸� ������ ����
		{
			pl->confidence++;

			break;
		}
	}

	while (strcmp(monster_name, "sy") == 0)
	{
		story_square(3, 20, 110, 7);
		gotoxy(8, 22);
		printf("������ ����Ե�, ������ �����鼭 ���Ѻ���. ������ �Ϳ� �����Ҹ��� �Ƹ��Ÿ���.");
		dot_printf(monster_name);
		gotoxy(20, 24);
		printf("        ");
		gotoxy(8, 24);
		printf("�Ǹ� HP : %d", mon->sy.hp);

		Sleep(100);
		fseek(stdin, 0, SEEK_END);
		c1 = getch();
		if (c1 == ' ') // '97'�� ���� 97�� ��Ÿ���� �׳� 97�� �ٲٰų� 'a'�� �����
		{
			mon->sy.hp--; //���� hp ���̴� �Լ�

		}
		if (mon->sy.hp == -1) //���� hp�� 0�̸� ������ ����
		{
			pl->confidence++;

			break;
		}
	}
	gotoxy(59, 15);
	printf("�¸�");
	Sleep(1000);
}



void save_data(struct player pl, struct monster mon)
{
	cls;
	int n[2] = { 0, };
	char player_savename[20] = "player_save";

	printf("���� ���� : �̸� \"%s\", �ڽŰ� %d,", pl.name, pl.confidence);
	n[0] = start_option("���̺� 1", "���̺� 2", "���̺� 3", 8, 7, 3, 6) + 48; //���ڿ��� ����� ���ؼ� �ƽ�Ű �ڵ尪 �����ֱ�

	if (pl.name[0] != NULL)
	{
		FILE* player_save = NULL;

		strcat(player_savename, n);

		player_save = fopen(player_savename, "wb");

		if (player_save == NULL)
			printf("�ɰ��� ������ �߻��Ͽ����ϴ�. ");

		fwrite(&pl, sizeof(struct player), 1, player_save);
		fwrite(&mon, sizeof(struct monster), 1, player_save);

		fclose(player_save);
	}
	else
	{
		textcolor(12);
		gotoxy(40, 12);
		printf("�̸��� ������ �ڿ� ���̺갡 �����մϴ�.\n");
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


	n[0] = start_option("�ε� 1", "�ε� 2", "�ε� 3", 8, 7, 3, 6) + 48; //���ڿ��� ����� ���ؼ� �ƽ�Ű �ڵ尪 �����ֱ�

	strcat(player_savename, n);

	if ((access(player_savename, 00) == 0)) //�б� ������ ���Ǵ��� ����
	{
		FILE* player_load = NULL;
		player_load = fopen(player_savename, "rb");

		if (player_load == NULL)
			printf("�ɰ��� ������ �߻��Ͽ����ϴ�. ");

		fread(pl, sizeof(struct player), 1, player_load);
		fread(mon, sizeof(struct monster), 1, player_load);


		Sleep(2000);

		fclose(player_load);
	}
	else
	{
		textcolor(12);
		gotoxy(35, 12);
		printf("�������� �ʴ� ���̺� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
		Sleep(700);
		textcolor(15);
		cls;
	}

}



void prolog(char name[30])
{
	clear_cursor(0);

	gotoxy(46, 4);
	printf("���� �б������� ���ϰ� �ִ�."); //���ڿ� ���� : 28
	Sleep(500);
	gotoxy(17, 6);
	printf("������ 1�г��� ���������� �ٰ��� ����, ����Ȱ�� �ð��� ä��� ���� �����θ� �� ������.");//86
	Sleep(500);
	gotoxy(32, 7);
	printf("���� �������� �濡 ��踦 �ǿ�� ����� ����ġ�� �Ǿ���."); //56
	Sleep(500);
	gotoxy(43, 9);
	printf("\"���� ��, �� �����. ��� ���ݾ�.\""); //34
	Sleep(500);
	gotoxy(45, 11);
	printf("����� ���� ������ �弳�̾���."); //30
	Sleep(500);
	gotoxy(18, 12);
	printf("�������� ������ ������ �츮 �б�������, ���迡�� ����� �弳�� ���� ���� ó���̾���."); //84
	Sleep(500);
	gotoxy(54, 14);
	printf("...������..."); //12
	Sleep(500);
	gotoxy(46, 15);
	printf("���� ����ģ ���谡 ã�ƿԴ�."); //28
	Sleep(500);
	gotoxy(52, 17);
	printf("\"��, %s ����.\"", name);//16
	Sleep(500);
	gotoxy(37, 19);
	printf("���� �״�� ������ �� ��ҷ� �������� �Ǿ���."); //46
	Sleep(500);
	gotoxy(42, 20);
	printf("�������� �𸣴� ������ �����̾���...");//36

	gotoxy(60, 28);
	printf("�Ѿ���� �ƹ� ��ư�̳� ��������....");

	fseek(stdin, 0, SEEK_END);
	getch();
	cls;
}

void story()
{
	fseek(stdin, 0, SEEK_END);

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("���õ� ��ҿ� ���� �Ϸ翴��.");
	Sleep(500);
	gotoxy(8, 24);
	printf("���ϸ��� �⵵�ϰ�� �Ѵ�. ���� ��ȭ�ο� �Ϸ簡 ã�ƿ��⸦...�ϰ�");
	Sleep(500);
	gotoxy(8, 26);
	printf("�� ��Ȳ�� ����� ���� ����� �غô�.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("��� �Ϸ�� �Ҹ�ġ�� ������ ��û�߰�, ��� �Ϸ�� �λ� ó������ ��źθ� �غô�.");
	Sleep(500);
	gotoxy(8, 24);
	printf("�׷��� ����غ��Ƶ� �ٲ�� ���� ������.");
	Sleep(500);
	gotoxy(8, 26);
	printf("���� ���� ��ó�� �þ ���̾���.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("���� �����ϴ� ���� ���������.");
	Sleep(500);
	gotoxy(8, 24);
	printf("�ƹ��� ����غ��Ƶ� �ٲ�� ���� ������.");
	Sleep(500);
	gotoxy(8, 26);
	printf("....");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"��, �ƹ��͵� �ϱ� �ȴ�..\"");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("�Žǿ� ������ ���ϴ� �߾�ŷȴ�. ");
	Sleep(500);
	gotoxy(8, 24);
	printf("������ �Ȱ�̰�, �ƺ��� 3���� ���� �ؿܷ� ���� �����̴�.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("��� �̹� ���� �ް� �ǰ� ���� ���� ��� �ƺ����� �����߾���. ");
	Sleep(500);
	gotoxy(8, 24);
	printf("������ ���� �ʴ� �ƺ��� �����ϸ� ������ ��Ƴ��⵵ �Ͽ���.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"...");
	Sleep(500);
	printf("�ᱹ ������ �� ��������... \"");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("������ ������� ���Ÿ� ���ø��� ���� ���� ���Ҵ�. ");
	getch();

	for (int i = 0; i < 2; i++)
	{
		gotoxy(0, 2);
		printf("                                                                                                                      \n");
		printf("       �������������                                          �������������                     \n");
		printf("         �����������                                              ����������                         \n");
		printf("                     ����              ����������                          ����                           \n");
		printf("                 �����                  ��������                         �����                            \n");
		printf("               �����                          ����                         �����                              \n");
		printf("          ������                          ����                        ������                                \n");
		printf("      �����������                  ����                        �����������                        \n");
		printf("    �������������              ���������              �������������                      \n");
		printf("                                        �����������                                                          \n");

		gotoxy(105, 11);
		for (int j = i; j < 3; j++)
		{
			printf("�� ");
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
	printf("������, �� ������ ���� �����ž�!!!");
	Sleep(500);
	getch();

	cls;

	gotoxy(50, 4);
	printf("����... ��, ���...?"); //20
	Sleep(500);
	gotoxy(55, 6);
	printf("�����...."); //10
	Sleep(500);
	gotoxy(43, 7);
	printf("Ʋ������ ���� �濡 ���� ħ�� ����."); //34
	Sleep(500);
	getch();

	gotoxy(32, 9);
	printf("���� �ᱹ �����ڰ� �޿��� ������ ������ ���濡 �̸�����.");//56
	Sleep(500);
	gotoxy(47, 11);
	printf("������ ����� ������ �ʴ�.");//26
	Sleep(500);
	gotoxy(44, 12);
	printf("���� ������.. ����� ���ٰ� �ұ�"); //32
	Sleep(500);
	gotoxy(51, 14);
	printf("���� �� �ڽŰ���..");//18
	Sleep(500);
	gotoxy(49, 16);
	printf("\"�� ������ ���� �ʾ�!!!\"");//22
	Sleep(500);
	gotoxy(38, 18);
	printf("�̰� �����ڸ� �������� ���� ������ �����̴�."); //44
	Sleep(500);
	gotoxy(39, 20);
	printf("�ӿ������� �������� �ڽŰ��� ��������.");//38
	Sleep(500);
	getch();

	cls;

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("..��������..");
	Sleep(500);
	gotoxy(8, 24);
	printf("\"��������?\"");
	Sleep(500);
	gotoxy(8, 26);
	printf("-�־�, �ƺ��� �� ������?");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"�ƺ�? ��°�� ������ �����Ͻô� �ſ���!!\"");
	Sleep(500);
	gotoxy(8, 24);
	printf("-�̾��ϱ���, ���� ����� �ٶ��� ������ �� �ߴܴ�...");
	Sleep(500);
	gotoxy(8, 26);
	printf(".....");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("-�׷� ���� �� ����?");
	Sleep(500);
	gotoxy(8, 24);
	printf("\"...��\"");
	Sleep(500);
	gotoxy(8, 26);
	printf("-����?");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("\"...��, ������...\"");
	Sleep(500);
	gotoxy(8, 24);
	printf("-......");
	Sleep(500);
	gotoxy(8, 26);
	printf("......");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("-�־� �� ������, �� ȥ�ڰ� �ƴ϶���.");
	Sleep(500);
	gotoxy(8, 24);
	printf(" ��ҿ��� �� �𸣰ڰ� �������� �ʾƵ�");
	Sleep(500);
	gotoxy(8, 26);
	printf(" �� �������� ������ �������� �ִٴ� �� ��������.");
	getch();

	system(cls);

	gotoxy(22, 9);
	printf("�׷�, ���� �ƺ��� ���ɾ ���� �� �ӿ��� ����Ʈ�� ������ ���ø��� �����ߴ�."); //76
	Sleep(500);
	gotoxy(51, 11);
	printf("\"�ƺ�... �����..\""); //18
	Sleep(500);
	gotoxy(41, 14);
	printf("���� ��� ������ ���� �� ���� �� ����."); //38
	Sleep(500);
	getch();


	system(cls);

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("[��ĥ ��]");
	Sleep(500);
	gotoxy(8, 24);
	printf("���� �ҽ� ���� �帳�ϴ�. ���� xx�� ���� �������� �ֵ��ϴ� û�ҳ� 4���� ���ӵǾ����ϴ�.");
	Sleep(500);
	gotoxy(8, 26);
	printf("������ ���� �л��� �Ű�� ������ ���븦 ���� �� �־��ٰ� �������ϴ�.");
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("�б����� �Ű�� 112 Ȥ�� 117�� �Ű��Ͻø� ������ ������ �� �ֽ��ϴ�.");
	Sleep(500);
	gotoxy(8, 24);
	printf("�� �ҽ��� ��� ��� �������� �ֺ����� ������ ������ �ձ��� �ִٴ� �� ���� ���� �ֽñ� �ٶ��ϴ�.");
	Sleep(500);
	getch();

	story_square(3, 20, 110, 7);
	gotoxy(8, 22);
	printf("�̰����� ���� �ҽ��� ������� ���ص帳�ϴ�.");
	Sleep(500);
	gotoxy(8, 24);
	printf("��û���ֽ� ������ �����մϴ�.");
	Sleep(500);

	cls;
}

void dot_printf(char monster_name[5])
{
	if (strcmp(monster_name, "at") == 0)
	{
		gotoxy(0, 5);
		printf("                                         ������                                                           \n");
		printf("                                     ����������          ģ�ϰ� �����ڴ� �ǵ�, �ʹ��ϳ�               \n");
		printf("                                  ����� ��������                                                     \n");
		printf("                                 ����� �� �� �� �����                                                   \n");
		printf("                                 ����� ��    ��  ����                                                    \n");
		printf("                                 �����           ����                                                    \n");
		printf("                                 �����   ������  ����                                                    \n");
		printf("      ���� OOO�̶� ģ�ϴٸ�?    ���  ��ᦡ������������                                                    \n");
		printf("                                ���    ��ᦦ����  ����                                                    \n");
		printf("                               ���     ���       ����                                                     \n");
	}
	else if (strcmp(monster_name, "by") == 0)
	{
		gotoxy(0, 5);
		printf("                                                ������               ���� ���迡�� �ҷ��� ģ����?          \n");
		printf("     �츮 �б� ���� �ҹ��� ����µ� ������  ����������                                                 \n");
		printf("                                           ������������                                              \n");
		printf("                                          �������������                                             \n");
		printf("                                         ��������������                                            \n");
		printf("                                         ��������������                                            \n");
		printf("                                          �������������                                             \n");
		printf("        �Ű��ؾ��ϳ�?                       �����������                                               \n");
		printf("                                              ���������                ������ �ָ����� ��¼��..         \n");
		printf("                                          �������������                                             \n");
		printf("                                        ���������������                                           \n");
	}
	else if (strcmp(monster_name, "sy") == 0)
	{
		gotoxy(0, 5);
		printf("                                            �������                                                        \n");
		printf("                                         ����������                                                     \n");
		printf("                                      �����     ��  ����                                                   \n");
		printf("                                     ����� ��    ��  ����                                                  \n");
		printf("                                     ����� ��    ��  ����                                                  \n");
		printf("                                     �����           ����                                                  \n");
		printf("                                     ������ ����   �����                                                 \n");
		printf("                                    ������ᦨ����������                                                \n");
		printf("                                       ����   ������   ����                                                 \n");
		printf("                                          ��               ��                                                   \n");
	}


}



//�ܼ��� x, y�� ��ǥ�� Ŀ���� �̵��Ѵ�. 
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Ŀ�������
void clear_cursor(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//�ؽ�Ʈ ���� �����ϱ�
void textcolor(int color_number)

{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
