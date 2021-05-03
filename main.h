#pragma once
#include<stdio.h>
#include<stdlib.h> //rand, strcmp �Լ��� ���
#include<time.h> //time �Լ��� ���
#include<windows.h> //system �Լ��� ���
#include<stdbool.h>//while(true)�Լ��� ���
#include<conio.h> //getch �Լ� ���
#include<string.h> //strcpy �Լ� ���

//�������� �� ��ũ��
#define cls system("cls")
#define UP 72
#define DOWN 80 
#define LEFT 75
#define RIGHT 77 
#define ROWS 18
#define COLS 114

//����ü
#pragma pack(push, 1) 
typedef struct player
{
	char name[10];
	char confidence;
	char story;
	char monster_kill_at;
	char monster_kill_by;
	char monster_kill_sy;

}player;

typedef struct attacker {

	int hp;
	int monsterX;
	int monsterY;
	int monster_die;

}attacker;

typedef struct bystander {

	int hp;
	int monsterX;
	int monsterY;
	int monster_die;

}bystander;

typedef struct sympathizer {
	int hp;
	int monsterX;
	int monsterY;
	int monster_die;
}sympathizer;

typedef struct monster {
	struct attacker at; //������
	struct bystander by; //�����
	struct sympathizer sy;
	char monster_kill[5];
}monster;
#pragma pack(pop) 


//�⺻���� ��� ���� �Լ�
void gotoxy(int x, int y); // Ŀ�� ��ġ �̵� �Լ�
void clear_cursor(char show); //Ŀ�� ����� �Լ�
void textcolor(int color_number); //���� �� �ٲٱ� �Լ�


//ȭ�� ��¿� �Լ�
//������ �����ϴ� �Լ�(�ɼ� �̸�1, �̸�2, �̸�3, �ɼ�2�� x��ġ, y��ġ, ������ ����, �ɼ� ���� �Ÿ�)
int start_option(char option1[30], char option2[30], char option3[30], int x, int y, int n, int enter); 
//�簢�� â ���� (���� x��ġ, y��ġ, r����ũ��, h����ũ��), �⺻ : (3, 20, 110, 7))
void story_square(int x, int y, int r, int h); 

//���̺� �� �ε� �� �Լ�
void save_data(struct player pl, struct monster mon); //���̺�� �Լ�
void load_data(struct player* pl, struct monster* mon); //�ε�� �Լ�

//���� ���� �Լ�
int keeper(int(*map)[COLS], int X, int Y, int n);
void monster_fight(struct player* pl, struct monster* mon, char monster_name[5]);
void monster_move(struct player* pl, struct monster* mon, int X, int Y, int startX, int startY, int* map_re);
void map_print(struct player* pl, int startX, int map[ROWS][COLS]);
int move_player(struct player* pl, struct monster* mon);

//���丮 ���� �Լ�
void set_name(char name[30]); //�̸� ���� �Լ�
void prolog(char name[30]); 
void story();
void ending();
void titleDot();
void dot_printf(char monster_name[5]);