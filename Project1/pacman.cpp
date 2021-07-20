#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 
#include <conio.h>
#define HIGH 45
#define WIDTH 48 

struct Gamer {
	/*�������*/  //����޷��� 
	int gamer_x;
	int gamer_y;
	int score;//�Ʒ��� 
	int death;//Ѫ�� 
	int monsterDeath;//ɱ���� 
	int flag;//��������Ļ�
	int bullet;//���ַ����ӵ� 1���ӵ� 2���ӵ� 3���ӵ� 4���ӵ� 
	char recordRe;//��¼��ҵķ��� 
};

struct Gamer gamer = {//��ҳ�ʼ״̬ 
	 22, //ע��:һ��ҪΪż�� 
	 20,
	 0,
	 3,
	 0,
	 0,
	 0,
	 0,
};

struct FoodPos {
	/*ʳ��λ��*/
	int food_x;
	int food_y;

};

struct FoodPos food1 = {//ʳ���ʼλ��
	 94,
	 1
};

struct FoodPos food2 = {
	66,
	30
};

struct FoodPos food3 = {
	6,
	36
};

struct FoodPos food4 = {
	66,
	4
};

struct FoodPos food5 = {
	8,
	5
};

struct FoodPos food6 = {
	94,
	28
};

struct Bullet {
	int bullet_x;
	int bullet_y;
	int breaker;
	int flag;
};

struct Bullet bullet[4] = {
	{ 0, 0, 0, 0},
	{ 0, 0, 0, 0},
	{ 0, 0, 0, 0},
	{ 0, 0, 0, 0}
};

struct AppleTree {
	/*ƻ��������*/
	int appletree_x;
	int appletree_y;
	/*ƻ����ǰ����*/
	int appletree_xPre;
	int appletree_yPre;
	int health;//�ظ�Ѫ�� 
	int appletime;//ÿ��һ��ʱ����� 
	int flag;//���Ա�� 
};

struct AppleTree appletree = {
	46,
	28,
	46,
	28,
	1,   //�ָ�Ѫ��Ϊ1 
	5,    //ʱ����Ϊ5 
	0   //δ���� 
};

struct MonsterPos {
	/*��������*/
	int monster_x;
	int monster_y;
};

struct MonsterPos monster1 = {//�����ʼλ�� 
	6,
	4
};

struct MonsterPos monster2 = {//�����ʼλ�� 
	6,
	6
};

struct MonsterPos monster3 = {//�����ʼλ�� 
	6,
	8
};

struct MonsterPos monster4 = {//�����ʼλ�� 
	6,
	10
};

struct Boss {
	/*BOSSλ��*/
	int boss_x;
	int boss_y;
	/*BOSSѪ��*/
	int boss_death;
	/*BOSS������*/
	int boss_ATK;
};

void goto_XY(int x, int y)// //����CMD���ڹ��λ��
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}

void hide_cursor() //����CMD���ڹ��
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);
}

//�������� 
void Show() {

	int i, j;
	for (i = 0; i < 48; i += 1) {
		for (j = 0; j < 120; j += 2) {
			if (i != 0 && i != 47 && (j == 0 || j == 98 || j == 118)) {
				hide_cursor();
				goto_XY(j, i); //����ƶ������տո���ж� 
							   //��һ������ռ���ո� 
				printf("��");
			}
			else if (i == 0 || i == 47) {
				hide_cursor();
				goto_XY(j, i);
				hide_cursor();
				printf("��");
			}
		}
		printf("\n");
	}


	goto_XY(102, 5);
	hide_cursor();
	printf("��Ϸ˵��:");
	goto_XY(107, 6);
	hide_cursor();
	printf("��");
	goto_XY(101, 7);
	hide_cursor();
	printf("ƻ������ �Ժ��");
	goto_XY(101, 8);
	hide_cursor();
	printf("�Ի�Ѫ������Ѫ");
	goto_XY(101, 9);
	hide_cursor();
	printf("����ȷ������");
	goto_XY(101, 10);
	hide_cursor();
	printf("������ǵ�����");
	goto_XY(101, 11);
	hide_cursor();
	printf("�����򣬼�Ѫ��");
	goto_XY(101, 12);
	hide_cursor();
	printf("��С�ݡ����Լ�");
	goto_XY(101, 13);
	hide_cursor();
	printf("�֡�������Ϊ10");
	goto_XY(101, 14);
	hide_cursor();
	printf("ʱ��ͨ�سɹ�!");

	goto_XY(101, 16);
	hide_cursor();
	printf("ע�����");
	goto_XY(101, 18);
	hide_cursor();
	printf("ƻ����ÿ��һ��");
	goto_XY(101, 19);
	hide_cursor();
	printf("ʱ�����ʧ����");
	goto_XY(101, 20);
	hide_cursor();
	printf("���׷ɱ�㣬��");
	goto_XY(101, 21);
	hide_cursor();
	printf("����ӵ����ո�");
	goto_XY(101, 22);
	hide_cursor();
	printf("Ϊ�ٻ�ħ����");
	goto_XY(101, 23);
	hide_cursor();
	printf("ħ��ɿأ�����");
	goto_XY(101, 24);
	hide_cursor();
	printf("��ħ���򲻿ɿ�");

	goto_XY(102, 27);
	hide_cursor();
	printf("������%d", gamer.score);

	goto_XY(102, 29);
	hide_cursor();
	printf("ɱ������%d", gamer.monsterDeath);

	goto_XY(102, 31);
	hide_cursor();
	printf("Ѫ����%d", gamer.death);



	if (gamer.flag == 1) {
		goto_XY(101, 42);
		hide_cursor();
		printf("����˼�����");
		goto_XY(101, 43);
		hide_cursor();
		printf("����Ӯ�ҵģ�����.");
	}
	else if (gamer.flag == 2) {
		goto_XY(101, 42);
		hide_cursor();
		printf("���С���ӣ���");
		goto_XY(101, 43);
		hide_cursor();
		printf("�����ޣ�����.");
	}
	else if (gamer.flag == 3) {
		goto_XY(101, 42);
		hide_cursor();
		printf("�����������");
		goto_XY(101, 43);
		hide_cursor();
		printf("һ���첲������.");
	}
	else if (gamer.flag == 4) {
		goto_XY(101, 42);
		hide_cursor();
		printf("����˯��~~~~����");
		goto_XY(101, 43);
		hide_cursor();
		printf("��ؼ� @&@��");
	}




	//	���ҷ�Χ100~116��Ϊż��//���·�Χ1~46///


}

void GameOver()
{

	if (gamer.score >= 10) {
		system("cls");
		printf("  �� ϲ ͨ �� ��\n");
		exit(0);
	}
	if (gamer.death <= 0) {
		system("cls");
		printf("  �� �� ʧ �� ��\n");
		exit(0);
	}

}
//�ӵ��Ƿ���ʧ//ײǽ��1 ײ�ַ�2 ������0 
int IsDeathBullet(int bulletnum)
{
	//���������Ƿ��ڷ���״̬ 
	if (bullet[bulletnum].breaker == 1) {
		if ((bullet[bulletnum].bullet_y <= 46 && bullet[bulletnum].bullet_y >= 1) && bullet[bulletnum].bullet_x < 2)
		{//������ǽ 
			bullet[bulletnum].breaker = 0;//���عر� 
			bullet[bulletnum].flag = 0;//���ӵ� 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if ((bullet[bulletnum].bullet_y <= 46 && bullet[bulletnum].bullet_y >= 1) && bullet[bulletnum].bullet_x > 96) {
			//������ǽ 
			bullet[bulletnum].breaker = 0;//���عر� 
			bullet[bulletnum].flag = 0;//���ӵ� 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if ((bullet[bulletnum].bullet_x >= 2 && bullet[bulletnum].bullet_x <= 96) && bullet[bulletnum].bullet_y > 46) {
			//������ǽ	 
			bullet[bulletnum].breaker = 0;//���عر� 
			bullet[bulletnum].flag = 0;//���ӵ� 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if ((bullet[bulletnum].bullet_x >= 2 && bullet[bulletnum].bullet_x <= 96) && bullet[bulletnum].bullet_y < 1) {
			//������ǽ	
			bullet[bulletnum].breaker = 0;//���عر� 
			bullet[bulletnum].flag = 0;//���ӵ� 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if (bullet[bulletnum].bullet_x == monster1.monster_x && bullet[bulletnum].bullet_y == monster1.monster_y) {
			//���ײ�Ϲ��� 1
			bullet[bulletnum].breaker = 0;//���عر� 
			bullet[bulletnum].flag = 0;   //���ӵ� 
			bullet[bulletnum].bullet_x = 0;//��λ�� 
			bullet[bulletnum].bullet_y = 0;
			++gamer.monsterDeath;
			++gamer.score;
			//system("cls")//ˢ��//���ˢ�� 
			monster1.monster_x = rand() % 94 + 2;
			monster1.monster_y = rand() % 45 + 1;
			while (monster1.monster_x % 2 == 0) {
				monster1.monster_x = rand() % 94 + 2;
			}
			goto_XY(monster1.monster_x, monster1.monster_y);
			hide_cursor();
			printf("��");
			return 2;
		}
		else if (bullet[bulletnum].bullet_x == monster2.monster_x && bullet[bulletnum].bullet_y == monster2.monster_y) {
			//���ײ�Ϲ��� 2
			bullet[bulletnum].breaker = 0;
			bullet[bulletnum].flag = 0;
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			++gamer.monsterDeath;
			++gamer.score;
			//system("cls");
			monster2.monster_x = rand() % 94 + 2;
			monster2.monster_y = rand() % 45 + 1;
			while (monster2.monster_x % 2 == 0) {
				monster2.monster_x = rand() % 94 + 2;
			}
			goto_XY(monster2.monster_x, monster2.monster_y);
			hide_cursor();
			printf("��");
			return 2;
		}
		else if (bullet[bulletnum].bullet_x == monster3.monster_x && bullet[bulletnum].bullet_y == monster3.monster_y) {
			//���ײ�Ϲ��� 3
			bullet[bulletnum].breaker = 0;
			bullet[bulletnum].flag = 0;
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			++gamer.monsterDeath;
			++gamer.score;
			//system("cls");
			monster3.monster_x = rand() % 94 + 2;
			monster3.monster_y = rand() % 45 + 1;
			while (monster3.monster_x % 2 == 0) {
				monster3.monster_x = rand() % 94 + 2;
			}
			goto_XY(monster3.monster_x, monster3.monster_y);
			hide_cursor();
			printf("��");
			return 2;
		}
		else if (bullet[bulletnum].bullet_x == monster4.monster_x && bullet[bulletnum].bullet_y == monster4.monster_y) {
			//���ײ�Ϲ��� 4
			bullet[bulletnum].breaker = 0;
			bullet[bulletnum].flag = 0;
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			++gamer.monsterDeath;
			++gamer.score;
			//system("cls");
			monster4.monster_x = rand() % 94 + 2;
			monster4.monster_y = rand() % 45 + 1;
			while (monster4.monster_x % 2 == 0) {
				monster4.monster_x = rand() % 94 + 2;
			}
			goto_XY(monster4.monster_x, monster4.monster_y);
			hide_cursor();
			printf("��");
			return 2;
		}
		return 0;
	}


}

/*�ӵ�ǰ��*/
void BulletGo()
{
	//���ӵ����ڷ���״̬���ӵ�״̬�����������
	if (bullet[0].breaker == 1 && IsDeathBullet(0) == 0) {
		if (gamer.recordRe == 'w') {//���ϼ� 
			--bullet[0].bullet_y;
			--bullet[0].bullet_y;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 's') {//���¼� 
			++bullet[0].bullet_y;
			++bullet[0].bullet_y;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'a') {//����� 

			--bullet[0].bullet_x;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'd') {//���Ҽ� 

			++bullet[0].bullet_x;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("��");
		}
	}


	if (bullet[1].breaker == 1 && IsDeathBullet(1) == 0) {
		if (gamer.recordRe == 'w') {//���ϼ� 
			--bullet[1].bullet_y;
			--bullet[1].bullet_y;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 's') {//���¼� 
			++bullet[1].bullet_y;
			++bullet[1].bullet_y;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'a') {//����� 

			--bullet[1].bullet_x;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'd') {//���Ҽ� 

			++bullet[1].bullet_x;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("��");
		}
	}


	if (bullet[2].breaker == 1 && IsDeathBullet(2) == 0) {
		if (gamer.recordRe == 'w') {//���ϼ� 
			--bullet[2].bullet_y;
			--bullet[2].bullet_y;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 's') {//���¼� 
			++bullet[2].bullet_y;
			++bullet[2].bullet_y;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'a') {//����� 

			--bullet[2].bullet_x;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'd') {//���Ҽ� 

			++bullet[2].bullet_x;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("��");
		}
	}


	if (bullet[3].breaker == 1 && IsDeathBullet(3) == 0) {
		if (gamer.recordRe == 'w') {//���ϼ� 
			--bullet[3].bullet_y;
			--bullet[3].bullet_y;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 's') {//���¼� 
			++bullet[3].bullet_y;
			++bullet[3].bullet_y;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'a') {//����� 

			--bullet[3].bullet_x;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("��");
		}
		else if (gamer.recordRe == 'd') {//���Ҽ� 

			++bullet[3].bullet_x;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("��");
		}
	}

}


/*�����ӵ�*/
void Bullet_XY()
{

	if (bullet[gamer.bullet - 1].breaker == 1 && bullet[gamer.bullet - 1].flag == 0) {//�ӵ�����λ��ֻ�ܼ�¼һ�Σ�ֱ��ײ��ǽ�� 
		/*�ӵ��ĳ�ʼ���䷽��*/
		if (gamer.recordRe == 'w') {
			bullet[gamer.bullet - 1].bullet_x = gamer.gamer_x;
			bullet[gamer.bullet - 1].bullet_y = gamer.gamer_y - 1;
		}
		else if (gamer.recordRe == 's') {
			bullet[gamer.bullet - 1].bullet_x = gamer.gamer_x;
			bullet[gamer.bullet - 1].bullet_y = gamer.gamer_y + 1;
		}
		else if (gamer.recordRe == 'a') {
			bullet[gamer.bullet - 1].bullet_y = gamer.gamer_y;
			bullet[gamer.bullet - 1].bullet_x = gamer.gamer_x - 1;
		}
		else if (gamer.recordRe == 'd') {
			bullet[gamer.bullet - 1].bullet_y = gamer.gamer_y;
			bullet[gamer.bullet - 1].bullet_x = gamer.gamer_x + 1;
		}
		bullet[gamer.bullet - 1].flag = 1;//��֤�´β���¼ 
	}
	/*�ӵ�ǰ��*/
	BulletGo();
}

/*�ж�ƻ���Ƿ񱻳�*/
int AppleEated()
{
	if (gamer.gamer_x == appletree.appletree_xPre && gamer.gamer_y == appletree.appletree_yPre) {
		gamer.death += appletree.health;//��Ѫ 
		appletree.flag = 1;//���� 
		return 1;
	}
	else {
		return 0;
	}

}

/*ƻ����*/
void Appletree()
{
	srand((unsigned)time(NULL));//�ṩ����    
	if (appletree.appletime >= 0 && appletree.appletime <= 75) {
		//ƻ��������ʱ���
		if (appletree.flag == 1) {
			appletree.appletree_x = rand() % 94 + 2;
			appletree.appletree_y = rand() % 45 + 1;
			appletree.appletime = 76;
			appletree.flag = 0;
		}
		else {
			goto_XY(appletree.appletree_xPre, appletree.appletree_yPre);
			hide_cursor();
			printf("��");
			goto_XY(appletree.appletree_xPre, appletree.appletree_yPre + 1);
			printf("��");
			//��֤ʳ����ֵ�λ��Ϊż��
			while (appletree.appletree_xPre % 2 != 0) {
				appletree.appletree_xPre = rand() % 94 + 2;
				appletree.appletree_yPre = rand() % 45 + 1;
				goto_XY(appletree.appletree_xPre, appletree.appletree_yPre);
				hide_cursor();
				printf("��");
				goto_XY(appletree.appletree_xPre, appletree.appletree_yPre + 1);
				printf("��");
			}
		}

	}
	else if (appletree.appletime > 75 && appletree.appletime <= 100) {
		//ƻ������ʧʱ��� 
		if (appletree.appletree_x != 0 && appletree.appletree_y != 0) {
			//���ƻ��������Ϊ0���򲻱��� 
			appletree.appletree_xPre = appletree.appletree_x;
			appletree.appletree_yPre = appletree.appletree_y;
		}

		appletree.appletree_x = 0;
		appletree.appletree_y = 0;
		goto_XY(appletree.appletree_x, appletree.appletree_y);
	}
	else {//����ʱ��� 
		appletree.appletime = 0;
	}

}


/*ʳ��*/
void Food()
{


	srand((unsigned)time(NULL));//�ṩ����

	goto_XY(food1.food_x, food1.food_y);//��Ӧʳ��λ�� 
	hide_cursor();
	//��֤ʳ����ֵ�λ��Ϊż��
	while (food1.food_x % 2 != 0) {
		food1.food_x = rand() % 94 + 2;
		food1.food_y = rand() % 45 + 1;
		goto_XY(food1.food_x, food1.food_y);//��Ӧʳ��λ�� 
	}
	printf("��");

	//��֤ʳ����ֵ�λ��Ϊż��
	goto_XY(food2.food_x, food2.food_y);//��Ӧʳ��λ�� 
	hide_cursor();
	while (food2.food_x % 2 != 0) {
		food2.food_x = rand() % 94 + 2;
		food2.food_y = rand() % 45 + 1;
		goto_XY(food2.food_x, food2.food_y);//��Ӧʳ��λ�� 
	}
	printf("��");

	//��֤ʳ����ֵ�λ��Ϊż��
	goto_XY(food3.food_x, food3.food_y);//��Ӧʳ��λ��
	hide_cursor();
	while (food3.food_x % 2 != 0) {
		food3.food_x = rand() % 94 + 2;
		food3.food_y = rand() % 45 + 1;
		goto_XY(food3.food_x, food3.food_y);//��Ӧʳ��λ�� 
	}
	printf("��");

	goto_XY(food4.food_x, food4.food_y);//��Ӧʳ��λ��
	hide_cursor();
	//��֤ʳ����ֵ�λ��Ϊż��
	while (food4.food_x % 2 != 0) {
		food4.food_x = rand() % 94 + 2;
		food4.food_y = rand() % 45 + 1;
		goto_XY(food4.food_x, food4.food_y);//��Ӧʳ��λ�� 
	}
	printf("��");

	goto_XY(food5.food_x, food5.food_y);//��Ӧʳ��λ��
	hide_cursor();
	//��֤ʳ����ֵ�λ��Ϊż��
	while (food5.food_x % 2 != 0) {
		food5.food_x = rand() % 94 + 2;
		food5.food_y = rand() % 45 + 1;
		goto_XY(food5.food_x, food5.food_y);//��Ӧʳ��λ�� 
	}
	printf("��");

	goto_XY(food6.food_x, food6.food_y);//��Ӧʳ��λ��
	hide_cursor();
	//��֤ʳ����ֵ�λ��Ϊż��
	while (food6.food_x % 2 != 0) {
		food6.food_x = rand() % 94 + 2;
		food6.food_y = rand() % 45 + 1;
		goto_XY(food6.food_x, food6.food_y);//��Ӧʳ��λ�� 
	}
	printf("��");

}
/*�ж�ʳ���Ƿ񱻳� */
int FoodEated()
{
	if (gamer.gamer_x == food1.food_x && gamer.gamer_y == food1.food_y) {
		food1.food_x = rand() % 94 + 2;
		food1.food_y = rand() % 45 + 1;
		Food();
		return 1;
	}
	else if (gamer.gamer_x == food2.food_x && gamer.gamer_y == food2.food_y) {
		food2.food_x = rand() % 94 + 2;
		food2.food_y = rand() % 45 + 1;
		Food();
		return 1;
	}
	else if (gamer.gamer_x == food3.food_x && gamer.gamer_y == food3.food_y) {
		food3.food_x = rand() % 94 + 2;
		food3.food_y = rand() % 45 + 1;
		Food();
		return 1;
	}
	else if (gamer.gamer_x == food4.food_x && gamer.gamer_y == food4.food_y) {
		food4.food_x = rand() % 94 + 2;
		food4.food_y = rand() % 45 + 1;
		Food();
		return 1;
	}
	else if (gamer.gamer_x == food5.food_x && gamer.gamer_y == food5.food_y) {
		food5.food_x = rand() % 94 + 2;
		food5.food_y = rand() % 45 + 1;
		Food();
		return 1;
	}
	else if (gamer.gamer_x == food6.food_x && gamer.gamer_y == food6.food_y) {
		food6.food_x = rand() % 94 + 2;
		food6.food_y = rand() % 45 + 1;
		Food();
		return 1;
	}
	else {
		return 0;
	}

}

/*��ӡ����*/
void PrintMonster()
{

	if ((monster1.monster_y <= 46 && monster1.monster_y >= 1) && monster1.monster_x < 2)
	{//������ǽ 
		monster1.monster_x = 96;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("��");
	}
	else if ((monster1.monster_y <= 46 && monster1.monster_y >= 1) && monster1.monster_x > 96) {
		//������ǽ 
		monster1.monster_x = 2;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("��");
	}
	else if ((monster1.monster_x >= 2 && monster1.monster_x <= 96) && monster1.monster_y > 46) {
		//������ǽ	    
		monster1.monster_y = 1;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("��");
	}
	else if ((monster1.monster_x >= 2 && monster1.monster_x <= 96) && monster1.monster_y < 1) {
		//������ǽ	    
		monster1.monster_y = 46;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("��");
	}


	if ((monster2.monster_y <= 46 && monster2.monster_y >= 1) && monster2.monster_x < 2)
	{//������ǽ 
		monster2.monster_x = 96;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("��");
	}
	else if ((monster2.monster_y <= 46 && monster2.monster_y >= 1) && monster2.monster_x > 96) {
		//������ǽ 
		monster2.monster_x = 2;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("��");
	}
	else if ((monster2.monster_x >= 2 && monster2.monster_x <= 96) && monster2.monster_y > 46) {
		//������ǽ	    
		monster2.monster_y = 1;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("��");
	}
	else if ((monster2.monster_x >= 2 && monster2.monster_x <= 96) && monster2.monster_y < 1) {
		//������ǽ	    
		monster2.monster_y = 46;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("��");
	}


	if ((monster3.monster_y <= 46 && monster3.monster_y >= 1) && monster3.monster_x < 2)
	{//������ǽ 
		monster3.monster_x = 96;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("��");
	}
	else if ((monster3.monster_y <= 46 && monster3.monster_y >= 1) && monster3.monster_x > 96) {
		//������ǽ 
		monster3.monster_x = 2;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("��");
	}
	else if ((monster3.monster_x >= 2 && monster3.monster_x <= 96) && monster3.monster_y > 46) {
		//������ǽ	    
		monster3.monster_y = 1;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("��");
	}
	else if ((monster3.monster_x >= 2 && monster3.monster_x <= 96) && monster3.monster_y < 1) {
		//������ǽ	    
		monster3.monster_y = 46;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("��");
	}


	if ((monster4.monster_y <= 46 && monster4.monster_y >= 1) && monster4.monster_x < 2)
	{//������ǽ 
		monster4.monster_x = 96;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("��");
	}
	else if ((monster4.monster_y <= 46 && monster4.monster_y >= 1) && monster4.monster_x > 96) {
		//������ǽ 
		monster4.monster_x = 2;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("��");
	}
	else if ((monster4.monster_x >= 2 && monster4.monster_x <= 96) && monster4.monster_y > 46) {
		//������ǽ	    
		monster4.monster_y = 1;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("��");
	}
	else if ((monster4.monster_x >= 2 && monster4.monster_x <= 96) && monster4.monster_y < 1) {
		//������ǽ	    
		monster4.monster_y = 46;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("��");
	}

	if ((gamer.gamer_x == monster1.monster_x) && (gamer.gamer_y == monster1.monster_y)) {
		//��������1
		gamer.gamer_x = 22;
		gamer.gamer_y = 20;
		--gamer.score;
		--gamer.death;
		gamer.flag = 1;
		if (gamer.score <= 0)
			gamer.score = 0;
		GameOver();
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else if ((gamer.gamer_x == monster2.monster_x) && (gamer.gamer_y == monster2.monster_y)) {
		//��������2
		gamer.gamer_x = 22;
		gamer.gamer_y = 20;
		--gamer.score;
		--gamer.death;
		gamer.flag = 2;
		if (gamer.score <= 0)
			gamer.score = 0;
		GameOver();
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else if ((gamer.gamer_x == monster3.monster_x) && (gamer.gamer_y == monster3.monster_y)) {
		//��������3
		gamer.gamer_x = 22;
		gamer.gamer_y = 20;
		--gamer.score;
		--gamer.death;
		gamer.flag = 3;
		if (gamer.score <= 0)
			gamer.score = 0;
		GameOver();
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else if ((gamer.gamer_x == monster4.monster_x) && (gamer.gamer_y == monster4.monster_y)) {
		//��������4
		gamer.gamer_x = 22;
		gamer.gamer_y = 20;
		--gamer.score;
		--gamer.death;
		gamer.flag = 4;
		if (gamer.score <= 0)
			gamer.score = 0;
		GameOver();
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else {
		//�������
		hide_cursor();
		goto_XY(monster1.monster_x, monster1.monster_y);
		printf("��");

		hide_cursor();
		goto_XY(monster2.monster_x, monster2.monster_y);
		printf("��");

		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("��");

		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("��");
	}

}
/*�����������*/
int MonsterIndex()
{
	int flag = 0;
	//����1 
	if (monster1.monster_x == gamer.gamer_x && monster1.monster_y > gamer.gamer_y) {
		//����λ�����ҷ����·� 
		--monster1.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster1.monster_x == gamer.gamer_x && monster1.monster_y < gamer.gamer_y) {
		//����λ�����ҷ����Ϸ� 
		++monster1.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster1.monster_y == gamer.gamer_y && monster1.monster_x > gamer.gamer_x) {
		//����λ�����ҷ����ҷ� 
		monster1.monster_x -= -2;
		PrintMonster();
		flag = 1;
	}
	else if (monster1.monster_y == gamer.gamer_y && monster1.monster_x < gamer.gamer_x) {
		//����λ�����ҷ����� 
		monster1.monster_x += 2;
		PrintMonster();
		flag = 1;
	}
	//����2		
	if (monster2.monster_x == gamer.gamer_x && monster2.monster_y > gamer.gamer_y) {
		//����λ�����ҷ����·� 
		--monster2.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster2.monster_x == gamer.gamer_x && monster2.monster_y < gamer.gamer_y) {
		//����λ�����ҷ����Ϸ� 
		++monster2.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster2.monster_y == gamer.gamer_y && monster2.monster_x > gamer.gamer_x) {
		//����λ�����ҷ����ҷ� 
		monster2.monster_x -= 2;
		PrintMonster();
		flag = 1;
	}
	else if (monster2.monster_y == gamer.gamer_y && monster2.monster_x < gamer.gamer_x) {
		//����λ�����ҷ����� 
		monster2.monster_x += 2;
		PrintMonster();
		flag = 1;
	}
	//����3	
	if (monster3.monster_x == gamer.gamer_x && monster3.monster_y > gamer.gamer_y) {
		//����λ�����ҷ����·� 
		--monster3.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster3.monster_x == gamer.gamer_x && monster3.monster_y < gamer.gamer_y) {
		//����λ�����ҷ����Ϸ� 
		++monster3.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster3.monster_y == gamer.gamer_y && monster3.monster_x > gamer.gamer_x) {
		//����λ�����ҷ����ҷ� 
		monster3.monster_x -= 2;
		PrintMonster();
		flag = 1;
	}
	else if (monster3.monster_y == gamer.gamer_y && monster3.monster_x < gamer.gamer_x) {
		//����λ�����ҷ����� 
		monster3.monster_x += 2;
		PrintMonster();
		flag = 1;
	}
	//����4	
	if (monster4.monster_x == gamer.gamer_x && monster4.monster_y > gamer.gamer_y) {
		//����λ�����ҷ����·� 
		--monster4.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster4.monster_x == gamer.gamer_x && monster4.monster_y < gamer.gamer_y) {
		//����λ�����ҷ����Ϸ� 
		++monster4.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster4.monster_y == gamer.gamer_y && monster4.monster_x > gamer.gamer_x) {
		//����λ�����ҷ����ҷ� 
		monster4.monster_x -= 2;
		PrintMonster();
		flag = 1;
	}
	else if (monster4.monster_y == gamer.gamer_y && monster4.monster_x < gamer.gamer_x) {
		//����λ�����ҷ����� 
		monster4.monster_x += 2;
		PrintMonster();
		flag = 1;
	}

	if (flag == 0) {
		return 1;
	}
	else {
		return 0;
	}

}


/*�ƶ�����*/
void MonsterMovement()
{

	srand((unsigned)time(NULL));


	if (MonsterIndex()) {

		int direction1 = rand() % 7;//�ĸ����� 0��ʾ�� 1��ʾ�� 2��ʾ�� 3��ʾ�� ���಻�� 		
		if (direction1 == 0) {      //�����ƶ� 
			monster1.monster_x -= 2;
		}
		else if (direction1 == 1) {//�����ƶ� 
			monster1.monster_x += 2;
		}
		else if (direction1 == 2) {//�����ƶ� 
			monster1.monster_y -= 1;
		}
		else if (direction1 == 3) {//�����ƶ� 
			monster1.monster_y += 1;
		}
		PrintMonster();

		int direction2 = rand() % 7;//�ĸ����� 0��ʾ�� 1��ʾ�� 2��ʾ�� 3��ʾ�� 
		if (direction2 == 0) { //�����ƶ� 
			monster2.monster_x -= 2;
		}
		else if (direction2 == 1) {//�����ƶ� 
			monster2.monster_x += 2;
		}
		else if (direction2 == 2) {//�����ƶ� 
			monster2.monster_y -= 1;
		}
		else if (direction2 == 3) {//�����ƶ� 
			monster2.monster_y += 1;
		}
		PrintMonster();

		int direction3 = rand() % 7;//�ĸ����� 0��ʾ�� 1��ʾ�� 2��ʾ�� 3��ʾ�� 
		if (direction3 == 0) { //�����ƶ� 
			monster3.monster_x -= 2;
		}
		else if (direction3 == 1) {//�����ƶ� 
			monster3.monster_x += 2;
		}
		else if (direction3 == 2) {//�����ƶ� 
			monster3.monster_y -= 1;
		}
		else if (direction3 == 3) {//�����ƶ� 
			monster3.monster_y += 1;
		}
		PrintMonster();


		int direction4 = rand() % 7;//�ĸ����� 0��ʾ�� 1��ʾ�� 2��ʾ�� 3��ʾ�� 
		if (direction4 == 0) { //�����ƶ� 
			monster4.monster_x -= 2;
		}
		else if (direction4 == 1) {//�����ƶ� 
			monster4.monster_x += 2;
		}
		else if (direction4 == 2) {//�����ƶ� 
			monster4.monster_y -= 1;
		}
		else if (direction4 == 3) {//�����ƶ� 
			monster4.monster_y += 1;
		}
		PrintMonster();

	}

}

/*�����ʼλ��*/
void Monster()
{

	srand((unsigned)time(NULL));//�ṩ����
	monster1.monster_x = rand() % 94 + 2;
	monster1.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster1.monster_x, monster1.monster_y);//��Ӧ����λ�� 
	 //��֤������ֵ�λ��Ϊż��
	while (monster1.monster_x % 2 != 0) {
		monster1.monster_x = rand() % 94 + 2;
		monster1.monster_y = rand() % 45 + 1;
		goto_XY(monster1.monster_x, monster1.monster_y);//��Ӧ����λ�� 
	}
	printf("��");

	srand((unsigned)time(NULL));//�ṩ����
	monster2.monster_x = rand() % 94 + 2;
	monster2.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster2.monster_x, monster2.monster_y);//��Ӧ����λ�� 
	 //��֤������ֵ�λ��Ϊż��
	while (monster2.monster_x % 2 != 0) {
		monster2.monster_x = rand() % 94 + 2;
		monster2.monster_y = rand() % 45 + 1;
		goto_XY(monster2.monster_x, monster2.monster_y);//��Ӧ����λ�� 
	}
	printf("��");

	srand((unsigned)time(NULL));//�ṩ����
	monster3.monster_x = rand() % 94 + 2;
	monster3.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster3.monster_x, monster3.monster_y);//��Ӧ����λ�� 
	 //��֤������ֵ�λ��Ϊż��
	while (monster3.monster_x % 2 != 0) {
		monster3.monster_x = rand() % 94 + 2;
		monster3.monster_y = rand() % 45 + 1;
		goto_XY(monster3.monster_x, monster3.monster_y);//��Ӧ����λ�� 
	}
	printf("��");

	srand((unsigned)time(NULL));//�ṩ����
	monster4.monster_x = rand() % 94 + 2;
	monster4.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster4.monster_x, monster4.monster_y);//��Ӧ����λ�� 
	 //��֤������ֵ�λ��Ϊż��
	while (monster4.monster_x % 2 != 0) {
		monster4.monster_x = rand() % 94 + 2;
		monster4.monster_y = rand() % 45 + 1;
		goto_XY(monster4.monster_x, monster4.monster_y);//��Ӧ����λ�� 
	}
	printf("��");

}


/*��ӡ���*/
void PrintGamer()
{

	if ((gamer.gamer_y <= 46 && gamer.gamer_y >= 1) && gamer.gamer_x < 2)
	{//������ǽ 
		gamer.gamer_x = 96;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else if ((gamer.gamer_y <= 46 && gamer.gamer_y >= 1) && gamer.gamer_x > 96) {
		//������ǽ 
		gamer.gamer_x = 2;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else if ((gamer.gamer_x >= 2 && gamer.gamer_x <= 96) && gamer.gamer_y > 46) {
		//������ǽ	    
		gamer.gamer_y = 1;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else if ((gamer.gamer_x >= 2 && gamer.gamer_x <= 96) && gamer.gamer_y < 1) {
		//������ǽ	    
		gamer.gamer_y = 46;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}
	else {
		//�������	
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("��");
	}

}

void Judgement(char ch)
{
	int bulletnum = gamer.bullet; //1~4���ӵ� 
	if (bulletnum >= 4) {
		bulletnum = 0;
	}
	if (ch == 'w' && bullet[bulletnum].flag == 0) {
		gamer.recordRe = 'w';
	}
	else if (ch == 's' && bullet[bulletnum].flag == 0) {
		gamer.recordRe = 's';
	}
	else if (ch == 'a' && bullet[bulletnum].flag == 0) {
		gamer.recordRe = 'a';
	}
	else if (ch == 'd' && bullet[bulletnum].flag == 0) {
		gamer.recordRe = 'd';
	}

}
//���ݲ�ͬ������򿪷��䲻ͬ�ӵ��Ŀ��� 
void BulletState()
{
	if (gamer.bullet >= 5) {
		gamer.bullet = 1;
	}
	bullet[gamer.bullet - 1].breaker = 1;
}

void Move()
{

	//���ҷ�Χ��2~96��Ϊż��,���·�Χ��1~46

				//�ް����Ĵ���
	if (_kbhit())
	{
		//�а�������
		fflush(stdin);
		char key = _getch();
		switch (key)
		{
		case 'd':gamer.gamer_x += 2; Judgement('d'); break;
		case 's':++gamer.gamer_y;  Judgement('s'); break;
		case 'a':gamer.gamer_x -= 2; Judgement('a'); break;
		case 'w':--gamer.gamer_y;  Judgement('w'); break;
		case ' ':++gamer.bullet; BulletState(); Bullet_XY();  break;
		}
	}
	/*������ʾˢ�º�Ķ���*/
	PrintGamer();//��ӡ���

	goto_XY(food1.food_x, food1.food_y);//��Ӧʳ��λ�� 
	printf("��");
	goto_XY(food2.food_x, food2.food_y);//��Ӧʳ��λ��
	printf("��");
	goto_XY(food3.food_x, food3.food_y);//��Ӧʳ��λ��
	printf("��");
	goto_XY(food4.food_x, food4.food_y);//��Ӧʳ��λ��
	printf("��");
	goto_XY(food5.food_x, food5.food_y);//��Ӧʳ��λ��
	printf("��");
	goto_XY(food6.food_x, food6.food_y);//��Ӧʳ��λ��
	printf("��");

}

int main()
{
	int g, i, ch;

	//��ʾ���� 
	Show();
	//��ʾ��ҳ�ʼλ�� 
	goto_XY(gamer.gamer_x, gamer.gamer_y);
	printf("��");
	//��ʾ�����ʼλ�� 
	Monster();

	while (1) {

		system("cls");//���� 

		Show();//��ӡ���� 

		PrintGamer();//��ӡ��� 

		Food();//��ӡʳ�� 

		Appletree(); //��ӡƻ����

		MonsterMovement();//��ӡ���� 

		BulletGo();

		Move();

		ch = IsDeathBullet(0);
		ch = IsDeathBullet(1);
		ch = IsDeathBullet(2);
		ch = IsDeathBullet(3);

		if (FoodEated())//�ж��Ƿ�Ե�ʳ��
			++gamer.score;  //�������� 
		if (AppleEated())
			appletree.appletime = 76;//ʱ����������ʧʱ 

		GameOver();//�ж��Ƿ������Ϸ 

		appletree.appletime++;

		Sleep(100);
	}

}


