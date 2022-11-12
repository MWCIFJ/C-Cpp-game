#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define High 100  // 游戏画面尺寸
#define Width 100


// 全局变量
int cells[High][Width]; // 所有位置细胞（生1或死0）

//所有图像类的程序，都要这种死记硬背的代码段 
void gotoxy(int x, int y)//类似于清屏函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()	//数据初始化
{
	int i, j;
	for (i = 0; i < High; i++)
		for (j = 0; j < Width; j++)
			cells[i][j] = 1;
}

void show()	 //显示画面
{
	gotoxy(0, 0);	//清屏
	int i, j;
	for (i = 0; i < High - 1; i++) {
		for (j = 0; j < Width - 1; j++)
			if (cells[i][j] == 1)
				printf("*");	//输出活的细胞
			else	//cells[i][j]==0 (死亡)
				printf(" ");
		printf("\n");
	}
	Sleep(50);	//停顿0.05秒 
}

void updateWithoutInput()
{
	int NeibourNum, NewCells[High][Width], i, j;	//下一帧的细胞情况
	for (i = 1; i < High - 1; i++)
	{
		for (j = 1; j < Width - 1; j++)
		{
			NeibourNum =
				cells[i - 1][j - 1]
				+ cells[i][j - 1]
				+ cells[i + 1][j - 1]
				+ cells[i - 1][j]
				+ cells[i + 1][j]
				+ cells[i - 1][j + 1]
				+ cells[i][j + 1]
				+ cells[i + 1][j + 1];
			if (NeibourNum == 3)
				NewCells[i][j] = 1;
			else if (NeibourNum == 2)
				NewCells[i][j] = cells[i][j];//直接赋值得了
			else	// >3||<2
				NewCells[i][j] = 0;
		}
	}

	for (i = 0; i < High - 1; i++)
	{
		for (j = 0; j < Width - 1; j++)
		{
			cells[i][j] = NewCells[i][j];	//覆写更新 
		}
	}
}

int main()
{
	startup();  //数据初始化	
	while (TRUE) //游戏循环执行
	{
		show();  //显示画面
		updateWithoutInput();
	}
}
