#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> 
#include <conio.h>
#define HIGH 45
#define WIDTH 48 

struct Gamer {
	/*玩家坐标*/  //玩家无防御 
	int gamer_x;
	int gamer_y;
	int score;//计分器 
	int death;//血量 
	int monsterDeath;//杀敌数 
	int flag;//引出怪物的话
	int bullet;//区分发射子弹 1号子弹 2号子弹 3号子弹 4号子弹 
	char recordRe;//记录玩家的方向 
};

struct Gamer gamer = {//玩家初始状态 
	 22, //注意:一定要为偶数 
	 20,
	 0,
	 3,
	 0,
	 0,
	 0,
	 0,
};

struct FoodPos {
	/*食物位置*/
	int food_x;
	int food_y;

};

struct FoodPos food1 = {//食物初始位置
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
	/*苹果树坐标*/
	int appletree_x;
	int appletree_y;
	/*苹果树前坐标*/
	int appletree_xPre;
	int appletree_yPre;
	int health;//回复血量 
	int appletime;//每隔一定时间出现 
	int flag;//被吃标记 
};

struct AppleTree appletree = {
	46,
	28,
	46,
	28,
	1,   //恢复血量为1 
	5,    //时间间隔为5 
	0   //未被吃 
};

struct MonsterPos {
	/*怪物坐标*/
	int monster_x;
	int monster_y;
};

struct MonsterPos monster1 = {//怪物初始位置 
	6,
	4
};

struct MonsterPos monster2 = {//怪物初始位置 
	6,
	6
};

struct MonsterPos monster3 = {//怪物初始位置 
	6,
	8
};

struct MonsterPos monster4 = {//怪物初始位置 
	6,
	10
};

struct Boss {
	/*BOSS位置*/
	int boss_x;
	int boss_y;
	/*BOSS血量*/
	int boss_death;
	/*BOSS攻击力*/
	int boss_ATK;
};

void goto_XY(int x, int y)// //设置CMD窗口光标位置
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}

void hide_cursor() //隐藏CMD窗口光标
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);
}

//基本场景 
void Show() {

	int i, j;
	for (i = 0; i < 48; i += 1) {
		for (j = 0; j < 120; j += 2) {
			if (i != 0 && i != 47 && (j == 0 || j == 98 || j == 118)) {
				hide_cursor();
				goto_XY(j, i); //光标移动是依照空格的判断 
							   //但一个方块占俩空格 
				printf("▉");
			}
			else if (i == 0 || i == 47) {
				hide_cursor();
				goto_XY(j, i);
				hide_cursor();
				printf("▉");
			}
		}
		printf("\n");
	}


	goto_XY(102, 5);
	hide_cursor();
	printf("游戏说明:");
	goto_XY(107, 6);
	hide_cursor();
	printf("●");
	goto_XY(101, 7);
	hide_cursor();
	printf("苹果树│ 吃后可");
	goto_XY(101, 8);
	hide_cursor();
	printf("以回血，而回血");
	goto_XY(101, 9);
	hide_cursor();
	printf("量则不确定。遇");
	goto_XY(101, 10);
	hide_cursor();
	printf("到怪物记得逃跑");
	goto_XY(101, 11);
	hide_cursor();
	printf("，否则，减血。");
	goto_XY(101, 12);
	hide_cursor();
	printf("吃小草▲可以加");
	goto_XY(101, 13);
	hide_cursor();
	printf("分。当分数为10");
	goto_XY(101, 14);
	hide_cursor();
	printf("时，通关成功!");

	goto_XY(101, 16);
	hide_cursor();
	printf("注意事项：");
	goto_XY(101, 18);
	hide_cursor();
	printf("苹果树每隔一段");
	goto_XY(101, 19);
	hide_cursor();
	printf("时间会消失。怪");
	goto_XY(101, 20);
	hide_cursor();
	printf("物可追杀你，可");
	goto_XY(101, 21);
	hide_cursor();
	printf("躲避子弹。空格");
	goto_XY(101, 22);
	hide_cursor();
	printf("为召唤魔法球，");
	goto_XY(101, 23);
	hide_cursor();
	printf("魔球可控，但四");
	goto_XY(101, 24);
	hide_cursor();
	printf("个魔法球不可控");

	goto_XY(102, 27);
	hide_cursor();
	printf("分数：%d", gamer.score);

	goto_XY(102, 29);
	hide_cursor();
	printf("杀敌数：%d", gamer.monsterDeath);

	goto_XY(102, 31);
	hide_cursor();
	printf("血量：%d", gamer.death);



	if (gamer.flag == 1) {
		goto_XY(101, 42);
		hide_cursor();
		printf("怪物：菜鸡，你");
		goto_XY(101, 43);
		hide_cursor();
		printf("斗不赢我的，哈哈.");
	}
	else if (gamer.flag == 2) {
		goto_XY(101, 42);
		hide_cursor();
		printf("怪物：小伙子，你");
		goto_XY(101, 43);
		hide_cursor();
		printf("不行噢，哈哈.");
	}
	else if (gamer.flag == 3) {
		goto_XY(101, 42);
		hide_cursor();
		printf("怪物：我想让你");
		goto_XY(101, 43);
		hide_cursor();
		printf("一条胳膊，啧啧.");
	}
	else if (gamer.flag == 4) {
		goto_XY(101, 42);
		hide_cursor();
		printf("我想睡觉~~~~，好");
		goto_XY(101, 43);
		hide_cursor();
		printf("想回家 @&@！");
	}




	//	左右范围100~116且为偶数//上下范围1~46///


}

void GameOver()
{

	if (gamer.score >= 10) {
		system("cls");
		printf("  恭 喜 通 关 ！\n");
		exit(0);
	}
	if (gamer.death <= 0) {
		system("cls");
		printf("  过 关 失 败 ！\n");
		exit(0);
	}

}
//子弹是否消失//撞墙返1 撞怪返2 正常返0 
int IsDeathBullet(int bulletnum)
{
	//首先满足是否处于发射状态 
	if (bullet[bulletnum].breaker == 1) {
		if ((bullet[bulletnum].bullet_y <= 46 && bullet[bulletnum].bullet_y >= 1) && bullet[bulletnum].bullet_x < 2)
		{//碰到左墙 
			bullet[bulletnum].breaker = 0;//开关关闭 
			bullet[bulletnum].flag = 0;//新子弹 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if ((bullet[bulletnum].bullet_y <= 46 && bullet[bulletnum].bullet_y >= 1) && bullet[bulletnum].bullet_x > 96) {
			//碰到右墙 
			bullet[bulletnum].breaker = 0;//开关关闭 
			bullet[bulletnum].flag = 0;//新子弹 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if ((bullet[bulletnum].bullet_x >= 2 && bullet[bulletnum].bullet_x <= 96) && bullet[bulletnum].bullet_y > 46) {
			//碰到下墙	 
			bullet[bulletnum].breaker = 0;//开关关闭 
			bullet[bulletnum].flag = 0;//新子弹 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if ((bullet[bulletnum].bullet_x >= 2 && bullet[bulletnum].bullet_x <= 96) && bullet[bulletnum].bullet_y < 1) {
			//碰到上墙	
			bullet[bulletnum].breaker = 0;//开关关闭 
			bullet[bulletnum].flag = 0;//新子弹 
			bullet[bulletnum].bullet_x = 0;
			bullet[bulletnum].bullet_y = 0;
			return 1;
		}
		else if (bullet[bulletnum].bullet_x == monster1.monster_x && bullet[bulletnum].bullet_y == monster1.monster_y) {
			//如果撞上怪物 1
			bullet[bulletnum].breaker = 0;//开关关闭 
			bullet[bulletnum].flag = 0;   //新子弹 
			bullet[bulletnum].bullet_x = 0;//空位置 
			bullet[bulletnum].bullet_y = 0;
			++gamer.monsterDeath;
			++gamer.score;
			//system("cls")//刷新//随机刷怪 
			monster1.monster_x = rand() % 94 + 2;
			monster1.monster_y = rand() % 45 + 1;
			while (monster1.monster_x % 2 == 0) {
				monster1.monster_x = rand() % 94 + 2;
			}
			goto_XY(monster1.monster_x, monster1.monster_y);
			hide_cursor();
			printf("▉");
			return 2;
		}
		else if (bullet[bulletnum].bullet_x == monster2.monster_x && bullet[bulletnum].bullet_y == monster2.monster_y) {
			//如果撞上怪物 2
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
			printf("▉");
			return 2;
		}
		else if (bullet[bulletnum].bullet_x == monster3.monster_x && bullet[bulletnum].bullet_y == monster3.monster_y) {
			//如果撞上怪物 3
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
			printf("▉");
			return 2;
		}
		else if (bullet[bulletnum].bullet_x == monster4.monster_x && bullet[bulletnum].bullet_y == monster4.monster_y) {
			//如果撞上怪物 4
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
			printf("▉");
			return 2;
		}
		return 0;
	}


}

/*子弹前进*/
void BulletGo()
{
	//如子弹处于发射状态且子弹状态处于正常情况
	if (bullet[0].breaker == 1 && IsDeathBullet(0) == 0) {
		if (gamer.recordRe == 'w') {//按上键 
			--bullet[0].bullet_y;
			--bullet[0].bullet_y;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 's') {//按下键 
			++bullet[0].bullet_y;
			++bullet[0].bullet_y;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'a') {//按左键 

			--bullet[0].bullet_x;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'd') {//按右键 

			++bullet[0].bullet_x;
			goto_XY(bullet[0].bullet_x, bullet[0].bullet_y);
			hide_cursor();
			printf("◆");
		}
	}


	if (bullet[1].breaker == 1 && IsDeathBullet(1) == 0) {
		if (gamer.recordRe == 'w') {//按上键 
			--bullet[1].bullet_y;
			--bullet[1].bullet_y;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 's') {//按下键 
			++bullet[1].bullet_y;
			++bullet[1].bullet_y;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'a') {//按左键 

			--bullet[1].bullet_x;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'd') {//按右键 

			++bullet[1].bullet_x;
			goto_XY(bullet[1].bullet_x, bullet[1].bullet_y);
			hide_cursor();
			printf("◆");
		}
	}


	if (bullet[2].breaker == 1 && IsDeathBullet(2) == 0) {
		if (gamer.recordRe == 'w') {//按上键 
			--bullet[2].bullet_y;
			--bullet[2].bullet_y;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 's') {//按下键 
			++bullet[2].bullet_y;
			++bullet[2].bullet_y;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'a') {//按左键 

			--bullet[2].bullet_x;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'd') {//按右键 

			++bullet[2].bullet_x;
			goto_XY(bullet[2].bullet_x, bullet[2].bullet_y);
			hide_cursor();
			printf("◆");
		}
	}


	if (bullet[3].breaker == 1 && IsDeathBullet(3) == 0) {
		if (gamer.recordRe == 'w') {//按上键 
			--bullet[3].bullet_y;
			--bullet[3].bullet_y;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 's') {//按下键 
			++bullet[3].bullet_y;
			++bullet[3].bullet_y;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'a') {//按左键 

			--bullet[3].bullet_x;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("◆");
		}
		else if (gamer.recordRe == 'd') {//按右键 

			++bullet[3].bullet_x;
			goto_XY(bullet[3].bullet_x, bullet[3].bullet_y);
			hide_cursor();
			printf("◆");
		}
	}

}


/*发射子弹*/
void Bullet_XY()
{

	if (bullet[gamer.bullet - 1].breaker == 1 && bullet[gamer.bullet - 1].flag == 0) {//子弹发射位置只能记录一次，直到撞上墙壁 
		/*子弹的初始发射方向*/
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
		bullet[gamer.bullet - 1].flag = 1;//保证下次不记录 
	}
	/*子弹前进*/
	BulletGo();
}

/*判断苹果是否被吃*/
int AppleEated()
{
	if (gamer.gamer_x == appletree.appletree_xPre && gamer.gamer_y == appletree.appletree_yPre) {
		gamer.death += appletree.health;//回血 
		appletree.flag = 1;//被吃 
		return 1;
	}
	else {
		return 0;
	}

}

/*苹果树*/
void Appletree()
{
	srand((unsigned)time(NULL));//提供种子    
	if (appletree.appletime >= 0 && appletree.appletime <= 75) {
		//苹果树出现时间段
		if (appletree.flag == 1) {
			appletree.appletree_x = rand() % 94 + 2;
			appletree.appletree_y = rand() % 45 + 1;
			appletree.appletime = 76;
			appletree.flag = 0;
		}
		else {
			goto_XY(appletree.appletree_xPre, appletree.appletree_yPre);
			hide_cursor();
			printf("●");
			goto_XY(appletree.appletree_xPre, appletree.appletree_yPre + 1);
			printf("│");
			//保证食物出现的位置为偶数
			while (appletree.appletree_xPre % 2 != 0) {
				appletree.appletree_xPre = rand() % 94 + 2;
				appletree.appletree_yPre = rand() % 45 + 1;
				goto_XY(appletree.appletree_xPre, appletree.appletree_yPre);
				hide_cursor();
				printf("●");
				goto_XY(appletree.appletree_xPre, appletree.appletree_yPre + 1);
				printf("│");
			}
		}

	}
	else if (appletree.appletime > 75 && appletree.appletime <= 100) {
		//苹果树消失时间段 
		if (appletree.appletree_x != 0 && appletree.appletree_y != 0) {
			//如果苹果树坐标为0，则不保存 
			appletree.appletree_xPre = appletree.appletree_x;
			appletree.appletree_yPre = appletree.appletree_y;
		}

		appletree.appletree_x = 0;
		appletree.appletree_y = 0;
		goto_XY(appletree.appletree_x, appletree.appletree_y);
	}
	else {//其他时间段 
		appletree.appletime = 0;
	}

}


/*食物*/
void Food()
{


	srand((unsigned)time(NULL));//提供种子

	goto_XY(food1.food_x, food1.food_y);//对应食物位置 
	hide_cursor();
	//保证食物出现的位置为偶数
	while (food1.food_x % 2 != 0) {
		food1.food_x = rand() % 94 + 2;
		food1.food_y = rand() % 45 + 1;
		goto_XY(food1.food_x, food1.food_y);//对应食物位置 
	}
	printf("▲");

	//保证食物出现的位置为偶数
	goto_XY(food2.food_x, food2.food_y);//对应食物位置 
	hide_cursor();
	while (food2.food_x % 2 != 0) {
		food2.food_x = rand() % 94 + 2;
		food2.food_y = rand() % 45 + 1;
		goto_XY(food2.food_x, food2.food_y);//对应食物位置 
	}
	printf("▲");

	//保证食物出现的位置为偶数
	goto_XY(food3.food_x, food3.food_y);//对应食物位置
	hide_cursor();
	while (food3.food_x % 2 != 0) {
		food3.food_x = rand() % 94 + 2;
		food3.food_y = rand() % 45 + 1;
		goto_XY(food3.food_x, food3.food_y);//对应食物位置 
	}
	printf("▲");

	goto_XY(food4.food_x, food4.food_y);//对应食物位置
	hide_cursor();
	//保证食物出现的位置为偶数
	while (food4.food_x % 2 != 0) {
		food4.food_x = rand() % 94 + 2;
		food4.food_y = rand() % 45 + 1;
		goto_XY(food4.food_x, food4.food_y);//对应食物位置 
	}
	printf("▲");

	goto_XY(food5.food_x, food5.food_y);//对应食物位置
	hide_cursor();
	//保证食物出现的位置为偶数
	while (food5.food_x % 2 != 0) {
		food5.food_x = rand() % 94 + 2;
		food5.food_y = rand() % 45 + 1;
		goto_XY(food5.food_x, food5.food_y);//对应食物位置 
	}
	printf("▲");

	goto_XY(food6.food_x, food6.food_y);//对应食物位置
	hide_cursor();
	//保证食物出现的位置为偶数
	while (food6.food_x % 2 != 0) {
		food6.food_x = rand() % 94 + 2;
		food6.food_y = rand() % 45 + 1;
		goto_XY(food6.food_x, food6.food_y);//对应食物位置 
	}
	printf("▲");

}
/*判断食物是否被吃 */
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

/*打印怪物*/
void PrintMonster()
{

	if ((monster1.monster_y <= 46 && monster1.monster_y >= 1) && monster1.monster_x < 2)
	{//碰到左墙 
		monster1.monster_x = 96;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("▉");
	}
	else if ((monster1.monster_y <= 46 && monster1.monster_y >= 1) && monster1.monster_x > 96) {
		//碰到右墙 
		monster1.monster_x = 2;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("▉");
	}
	else if ((monster1.monster_x >= 2 && monster1.monster_x <= 96) && monster1.monster_y > 46) {
		//碰到下墙	    
		monster1.monster_y = 1;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("▉");
	}
	else if ((monster1.monster_x >= 2 && monster1.monster_x <= 96) && monster1.monster_y < 1) {
		//碰到上墙	    
		monster1.monster_y = 46;
		goto_XY(monster1.monster_x, monster1.monster_y);
		hide_cursor();
		printf("▉");
	}


	if ((monster2.monster_y <= 46 && monster2.monster_y >= 1) && monster2.monster_x < 2)
	{//碰到左墙 
		monster2.monster_x = 96;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("▉");
	}
	else if ((monster2.monster_y <= 46 && monster2.monster_y >= 1) && monster2.monster_x > 96) {
		//碰到右墙 
		monster2.monster_x = 2;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("▉");
	}
	else if ((monster2.monster_x >= 2 && monster2.monster_x <= 96) && monster2.monster_y > 46) {
		//碰到下墙	    
		monster2.monster_y = 1;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("▉");
	}
	else if ((monster2.monster_x >= 2 && monster2.monster_x <= 96) && monster2.monster_y < 1) {
		//碰到上墙	    
		monster2.monster_y = 46;
		goto_XY(monster2.monster_x, monster2.monster_y);
		hide_cursor();
		printf("▉");
	}


	if ((monster3.monster_y <= 46 && monster3.monster_y >= 1) && monster3.monster_x < 2)
	{//碰到左墙 
		monster3.monster_x = 96;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("▉");
	}
	else if ((monster3.monster_y <= 46 && monster3.monster_y >= 1) && monster3.monster_x > 96) {
		//碰到右墙 
		monster3.monster_x = 2;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("▉");
	}
	else if ((monster3.monster_x >= 2 && monster3.monster_x <= 96) && monster3.monster_y > 46) {
		//碰到下墙	    
		monster3.monster_y = 1;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("▉");
	}
	else if ((monster3.monster_x >= 2 && monster3.monster_x <= 96) && monster3.monster_y < 1) {
		//碰到上墙	    
		monster3.monster_y = 46;
		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("▉");
	}


	if ((monster4.monster_y <= 46 && monster4.monster_y >= 1) && monster4.monster_x < 2)
	{//碰到左墙 
		monster4.monster_x = 96;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("▉");
	}
	else if ((monster4.monster_y <= 46 && monster4.monster_y >= 1) && monster4.monster_x > 96) {
		//碰到右墙 
		monster4.monster_x = 2;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("▉");
	}
	else if ((monster4.monster_x >= 2 && monster4.monster_x <= 96) && monster4.monster_y > 46) {
		//碰到下墙	    
		monster4.monster_y = 1;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("▉");
	}
	else if ((monster4.monster_x >= 2 && monster4.monster_x <= 96) && monster4.monster_y < 1) {
		//碰到上墙	    
		monster4.monster_y = 46;
		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("▉");
	}

	if ((gamer.gamer_x == monster1.monster_x) && (gamer.gamer_y == monster1.monster_y)) {
		//碰到怪物1
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
		printf("▉");
	}
	else if ((gamer.gamer_x == monster2.monster_x) && (gamer.gamer_y == monster2.monster_y)) {
		//碰到怪物2
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
		printf("▉");
	}
	else if ((gamer.gamer_x == monster3.monster_x) && (gamer.gamer_y == monster3.monster_y)) {
		//碰到怪物3
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
		printf("▉");
	}
	else if ((gamer.gamer_x == monster4.monster_x) && (gamer.gamer_y == monster4.monster_y)) {
		//碰到怪物4
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
		printf("▉");
	}
	else {
		//正常情况
		hide_cursor();
		goto_XY(monster1.monster_x, monster1.monster_y);
		printf("▉");

		hide_cursor();
		goto_XY(monster2.monster_x, monster2.monster_y);
		printf("▉");

		hide_cursor();
		goto_XY(monster3.monster_x, monster3.monster_y);
		printf("▉");

		hide_cursor();
		goto_XY(monster4.monster_x, monster4.monster_y);
		printf("▉");
	}

}
/*怪物搜索玩家*/
int MonsterIndex()
{
	int flag = 0;
	//怪物1 
	if (monster1.monster_x == gamer.gamer_x && monster1.monster_y > gamer.gamer_y) {
		//怪物位置在我方正下方 
		--monster1.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster1.monster_x == gamer.gamer_x && monster1.monster_y < gamer.gamer_y) {
		//怪物位置在我方正上方 
		++monster1.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster1.monster_y == gamer.gamer_y && monster1.monster_x > gamer.gamer_x) {
		//怪物位置在我方正右方 
		monster1.monster_x -= -2;
		PrintMonster();
		flag = 1;
	}
	else if (monster1.monster_y == gamer.gamer_y && monster1.monster_x < gamer.gamer_x) {
		//怪物位置在我方正左方 
		monster1.monster_x += 2;
		PrintMonster();
		flag = 1;
	}
	//怪物2		
	if (monster2.monster_x == gamer.gamer_x && monster2.monster_y > gamer.gamer_y) {
		//怪物位置在我方正下方 
		--monster2.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster2.monster_x == gamer.gamer_x && monster2.monster_y < gamer.gamer_y) {
		//怪物位置在我方正上方 
		++monster2.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster2.monster_y == gamer.gamer_y && monster2.monster_x > gamer.gamer_x) {
		//怪物位置在我方正右方 
		monster2.monster_x -= 2;
		PrintMonster();
		flag = 1;
	}
	else if (monster2.monster_y == gamer.gamer_y && monster2.monster_x < gamer.gamer_x) {
		//怪物位置在我方正左方 
		monster2.monster_x += 2;
		PrintMonster();
		flag = 1;
	}
	//怪物3	
	if (monster3.monster_x == gamer.gamer_x && monster3.monster_y > gamer.gamer_y) {
		//怪物位置在我方正下方 
		--monster3.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster3.monster_x == gamer.gamer_x && monster3.monster_y < gamer.gamer_y) {
		//怪物位置在我方正上方 
		++monster3.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster3.monster_y == gamer.gamer_y && monster3.monster_x > gamer.gamer_x) {
		//怪物位置在我方正右方 
		monster3.monster_x -= 2;
		PrintMonster();
		flag = 1;
	}
	else if (monster3.monster_y == gamer.gamer_y && monster3.monster_x < gamer.gamer_x) {
		//怪物位置在我方正左方 
		monster3.monster_x += 2;
		PrintMonster();
		flag = 1;
	}
	//怪物4	
	if (monster4.monster_x == gamer.gamer_x && monster4.monster_y > gamer.gamer_y) {
		//怪物位置在我方正下方 
		--monster4.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster4.monster_x == gamer.gamer_x && monster4.monster_y < gamer.gamer_y) {
		//怪物位置在我方正上方 
		++monster4.monster_y;
		PrintMonster();
		flag = 1;
	}
	else if (monster4.monster_y == gamer.gamer_y && monster4.monster_x > gamer.gamer_x) {
		//怪物位置在我方正右方 
		monster4.monster_x -= 2;
		PrintMonster();
		flag = 1;
	}
	else if (monster4.monster_y == gamer.gamer_y && monster4.monster_x < gamer.gamer_x) {
		//怪物位置在我方正左方 
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


/*移动怪物*/
void MonsterMovement()
{

	srand((unsigned)time(NULL));


	if (MonsterIndex()) {

		int direction1 = rand() % 7;//四个方向 0表示左 1表示右 2表示上 3表示下 其余不动 		
		if (direction1 == 0) {      //向左移动 
			monster1.monster_x -= 2;
		}
		else if (direction1 == 1) {//向右移动 
			monster1.monster_x += 2;
		}
		else if (direction1 == 2) {//向上移动 
			monster1.monster_y -= 1;
		}
		else if (direction1 == 3) {//向下移动 
			monster1.monster_y += 1;
		}
		PrintMonster();

		int direction2 = rand() % 7;//四个方向 0表示左 1表示右 2表示上 3表示下 
		if (direction2 == 0) { //向左移动 
			monster2.monster_x -= 2;
		}
		else if (direction2 == 1) {//向右移动 
			monster2.monster_x += 2;
		}
		else if (direction2 == 2) {//向上移动 
			monster2.monster_y -= 1;
		}
		else if (direction2 == 3) {//向下移动 
			monster2.monster_y += 1;
		}
		PrintMonster();

		int direction3 = rand() % 7;//四个方向 0表示左 1表示右 2表示上 3表示下 
		if (direction3 == 0) { //向左移动 
			monster3.monster_x -= 2;
		}
		else if (direction3 == 1) {//向右移动 
			monster3.monster_x += 2;
		}
		else if (direction3 == 2) {//向上移动 
			monster3.monster_y -= 1;
		}
		else if (direction3 == 3) {//向下移动 
			monster3.monster_y += 1;
		}
		PrintMonster();


		int direction4 = rand() % 7;//四个方向 0表示左 1表示右 2表示上 3表示下 
		if (direction4 == 0) { //向左移动 
			monster4.monster_x -= 2;
		}
		else if (direction4 == 1) {//向右移动 
			monster4.monster_x += 2;
		}
		else if (direction4 == 2) {//向上移动 
			monster4.monster_y -= 1;
		}
		else if (direction4 == 3) {//向下移动 
			monster4.monster_y += 1;
		}
		PrintMonster();

	}

}

/*怪物初始位置*/
void Monster()
{

	srand((unsigned)time(NULL));//提供种子
	monster1.monster_x = rand() % 94 + 2;
	monster1.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster1.monster_x, monster1.monster_y);//对应怪物位置 
	 //保证怪物出现的位置为偶数
	while (monster1.monster_x % 2 != 0) {
		monster1.monster_x = rand() % 94 + 2;
		monster1.monster_y = rand() % 45 + 1;
		goto_XY(monster1.monster_x, monster1.monster_y);//对应怪物位置 
	}
	printf("▉");

	srand((unsigned)time(NULL));//提供种子
	monster2.monster_x = rand() % 94 + 2;
	monster2.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster2.monster_x, monster2.monster_y);//对应怪物位置 
	 //保证怪物出现的位置为偶数
	while (monster2.monster_x % 2 != 0) {
		monster2.monster_x = rand() % 94 + 2;
		monster2.monster_y = rand() % 45 + 1;
		goto_XY(monster2.monster_x, monster2.monster_y);//对应怪物位置 
	}
	printf("▉");

	srand((unsigned)time(NULL));//提供种子
	monster3.monster_x = rand() % 94 + 2;
	monster3.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster3.monster_x, monster3.monster_y);//对应怪物位置 
	 //保证怪物出现的位置为偶数
	while (monster3.monster_x % 2 != 0) {
		monster3.monster_x = rand() % 94 + 2;
		monster3.monster_y = rand() % 45 + 1;
		goto_XY(monster3.monster_x, monster3.monster_y);//对应怪物位置 
	}
	printf("▉");

	srand((unsigned)time(NULL));//提供种子
	monster4.monster_x = rand() % 94 + 2;
	monster4.monster_y = rand() % 45 + 1;
	hide_cursor();
	goto_XY(monster4.monster_x, monster4.monster_y);//对应怪物位置 
	 //保证怪物出现的位置为偶数
	while (monster4.monster_x % 2 != 0) {
		monster4.monster_x = rand() % 94 + 2;
		monster4.monster_y = rand() % 45 + 1;
		goto_XY(monster4.monster_x, monster4.monster_y);//对应怪物位置 
	}
	printf("▉");

}


/*打印玩家*/
void PrintGamer()
{

	if ((gamer.gamer_y <= 46 && gamer.gamer_y >= 1) && gamer.gamer_x < 2)
	{//碰到左墙 
		gamer.gamer_x = 96;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("▉");
	}
	else if ((gamer.gamer_y <= 46 && gamer.gamer_y >= 1) && gamer.gamer_x > 96) {
		//碰到右墙 
		gamer.gamer_x = 2;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("▉");
	}
	else if ((gamer.gamer_x >= 2 && gamer.gamer_x <= 96) && gamer.gamer_y > 46) {
		//碰到下墙	    
		gamer.gamer_y = 1;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("▉");
	}
	else if ((gamer.gamer_x >= 2 && gamer.gamer_x <= 96) && gamer.gamer_y < 1) {
		//碰到上墙	    
		gamer.gamer_y = 46;
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("▉");
	}
	else {
		//正常情况	
		hide_cursor();
		goto_XY(gamer.gamer_x, gamer.gamer_y);
		printf("▉");
	}

}

void Judgement(char ch)
{
	int bulletnum = gamer.bullet; //1~4号子弹 
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
//根据不同情况，打开发射不同子弹的开关 
void BulletState()
{
	if (gamer.bullet >= 5) {
		gamer.bullet = 1;
	}
	bullet[gamer.bullet - 1].breaker = 1;
}

void Move()
{

	//左右范围在2~96且为偶数,上下范围在1~46

				//无按键的处理
	if (_kbhit())
	{
		//有按键接受
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
	/*重新显示刷新后的对象*/
	PrintGamer();//打印玩家

	goto_XY(food1.food_x, food1.food_y);//对应食物位置 
	printf("▲");
	goto_XY(food2.food_x, food2.food_y);//对应食物位置
	printf("▲");
	goto_XY(food3.food_x, food3.food_y);//对应食物位置
	printf("▲");
	goto_XY(food4.food_x, food4.food_y);//对应食物位置
	printf("▲");
	goto_XY(food5.food_x, food5.food_y);//对应食物位置
	printf("▲");
	goto_XY(food6.food_x, food6.food_y);//对应食物位置
	printf("▲");

}

int main()
{
	int g, i, ch;

	//显示场景 
	Show();
	//显示玩家初始位置 
	goto_XY(gamer.gamer_x, gamer.gamer_y);
	printf("▉");
	//显示怪物初始位置 
	Monster();

	while (1) {

		system("cls");//清屏 

		Show();//打印场景 

		PrintGamer();//打印玩家 

		Food();//打印食物 

		Appletree(); //打印苹果树

		MonsterMovement();//打印怪物 

		BulletGo();

		Move();

		ch = IsDeathBullet(0);
		ch = IsDeathBullet(1);
		ch = IsDeathBullet(2);
		ch = IsDeathBullet(3);

		if (FoodEated())//判断是否吃到食物
			++gamer.score;  //分数增加 
		if (AppleEated())
			appletree.appletime = 76;//时间重置至消失时 

		GameOver();//判断是否结束游戏 

		appletree.appletime++;

		Sleep(100);
	}

}


