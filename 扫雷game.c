#define _CRT_SECURE_NO_WARNINGS 1
//#include"MineClearance.c"		//源文件的分文件不需要这行，项目会自动检测到，只需要头文件即可
#include"MineClearance.h"
double start, finish;

int main()
{
	srand((unsigned int)time(NULL));//产生随机数生成器
	int input = 0;
	muen();//菜单
	do
	{
		scanf_s("%d", &input);
		switch (input)
		{
		case 2:game_GOD();//开启上帝视角后再玩
			break;
		case 1:game();
			break;
		case 0:exit(1);//退出游戏
			break;
		default:
			printf("输入错误，重新输入\n");
			break;
		}
		printf("\n是否重来？\n");
		muen();
	} while (1);//循环玩游戏
	system("pause");
	return 0;
}