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
		go = start_option("���ӽ���", "����ϱ�", "��������", 56, 16, 3, 3); //(��ȯ���� ���� 1 ���ӽ���, 2 ����ϱ�, 3 ��������)
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
				printf("����ϱ⸦ �����ϸ� ������ ���ɴϴ�. ���̺� �Ͻðڽ��ϱ�?");
				save_on = start_option(" ���̺�", "����ϱ�", "", 56, 20, 2, 3);

				if (save_on == 1)
					save_data(pl, *mon);

				ending();

			}
			break;
		case 2:
				cls;
				result = start_option(" ���̺�", "  �ε�", "�ڷΰ���", 57, 16, 3, 3);
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
