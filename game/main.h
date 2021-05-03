#pragma once
#include<stdio.h>
#include<stdlib.h> //rand, strcmp 함수를 사용
#include<time.h> //time 함수를 사용
#include<windows.h> //system 함수를 사용
#include<stdbool.h>//while(true)함수를 사용
#include<conio.h> //getch 함수 사용
#include<string.h> //strcpy 함수 사용

//전역변수 및 매크로
#define cls system("cls")
#define UP 72
#define DOWN 80 
#define LEFT 75
#define RIGHT 77 
#define ROWS 18
#define COLS 114

//구조체
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
	struct attacker at; //가해자
	struct bystander by; //방관자
	struct sympathizer sy;
	char monster_kill[5];
}monster;
#pragma pack(pop) 


//기본적인 기능 제공 함수
void gotoxy(int x, int y); // 커서 위치 이동 함수
void clear_cursor(char show); //커서 숨기기 함수
void textcolor(int color_number); //글자 색 바꾸기 함수


//화면 출력용 함수
//선택지 선택하는 함수(옵션 이름1, 이름2, 이름3, 옵션2의 x위치, y위치, 선택지 개수, 옵션 사이 거리)
int start_option(char option1[30], char option2[30], char option3[30], int x, int y, int n, int enter); 
//사각형 창 띄우기 (시작 x위치, y위치, r가로크기, h세로크기), 기본 : (3, 20, 110, 7))
void story_square(int x, int y, int r, int h); 

//세이브 및 로드 용 함수
void save_data(struct player pl, struct monster mon); //세이브용 함수
void load_data(struct player* pl, struct monster* mon); //로드용 함수

//게임 구현 함수
int keeper(int(*map)[COLS], int X, int Y, int n);
void monster_fight(struct player* pl, struct monster* mon, char monster_name[5]);
void monster_move(struct player* pl, struct monster* mon, int X, int Y, int startX, int startY, int* map_re);
void map_print(struct player* pl, int startX, int map[ROWS][COLS]);
int move_player(struct player* pl, struct monster* mon);

//스토리 구현 함수
void set_name(char name[30]); //이름 설정 함수
void prolog(char name[30]); 
void story();
void ending();
void titleDot();
void dot_printf(char monster_name[5]);
