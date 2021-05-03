#include"main.h"


int main()
{

	system("title SCHOOL");

	int result = 0, go = 0, save_on = 0;

	struct player pl = { 0, };
	struct monster* mon = malloc(sizeof(struct monster));
	struct attacker at = { 100, 0, };
	struct bystander by = { 50, 0, };
	struct sympathizer sy = { 30, 0, };
	mon->at = at;
	mon->by = by;
	mon->sy = sy;

	while (1)
	{
		cls;
		titleDot();

		story_square(48, 14, 20, 9);
		go = start_option("게임시작", "계속하기", "게임종료", 56, 16, 3, 3); //(반환값에 따라서 1 게임시작, 2 계속하기, 3 게임종료)
		save_on = 0;

		switch (go)
		{
		case 1:

			if (pl.name[0] == NULL)
			{
				set_name(pl.name);
				cls;

				if (pl.story == 0)
				{
					prolog(pl.name);

					story();
					pl.story = 1;
				}
			}

			save_on = move_player(&pl, mon);

			if (pl.confidence >= 3)
			{
				cls;
				textcolor(15);
				gotoxy(31, 15);
				printf("계속하기를 선택하면 엔딩이 나옵니다. 세이브 하시겠습니까?");
				save_on = start_option(" 세이브", "계속하기", "", 56, 20, 2, 3);

				if (save_on == 1)
					save_data(pl, *mon);

				ending();

			}
			break;
		case 2:
				cls;
				result = start_option(" 세이브", "  로드", "뒤로가기", 57, 16, 3, 3);
				if (result == 1)
					save_data(pl, *mon);
				else if (result == 2)
					load_data(&pl, mon);

			break;
		case 3:
			free(mon);
			return 0;
			
		}

	}
}
