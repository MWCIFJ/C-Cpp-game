#define _CRT_SECURE_NO_WARNINGS 1
#include"MineClearance.h"
char show_mine[row][col] = { 0 };
char real_mine[row][col] = { 0 };
double start, finish;

void muen()
{
	printf("************************************************\n");
	printf("*****1.play   2.开启上帝视角后再玩    0.exit****\n");
	printf("************************************************\n");
}


void init_mine()//初始化两个棋盘
{
	int i = 0;
	int j = 0;
	for (int i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			show_mine[i][j] = '*';	//玩家视角，所有坐标都是隐藏
			real_mine[i][j] = '0';	//上帝视角，能看出来雷点（雷1非雷0）
		}
	}
}


void print_player()//打印玩家棋盘
{
	int i = 0;
	int j = 0;
	printf("0  ");
	for (i = 1; i < row - 1; i++)
	{
		printf("%d ", i);//打印横标（0--10）
	}
	printf("\n");
	for (i = 1; i < row - 2; i++)//打印竖标（1--10）
	{
		printf("%d  ", i);
		for (j = 1; j < col - 1; j++)
		{
			printf("%c ", show_mine[i][j]);//玩家棋盘数组,就是玩家视角的地图
			//全*，以“ ”隔开以起到视觉美观的效果
		}
		printf("\n");
	}
	printf("10 ");//开始打印最后一行
	for (i = 1; i < row - 1; i++)
	{
		printf("%c ", show_mine[10][i]); //单独打印最后一行
	}
	printf("\n");
}


void print_mine()//打印设计者棋盘
{
	int i = 0;
	int j = 0;
	printf("0  ");
	for (i = 1; i < row - 1; i++)
	{
		printf("%d ", i);//打印横标（0--10）
	}
	printf("\n");
	for (i = 1; i < row - 2; i++)//打印竖标（1--10）
	{
		printf("%d  ", i);
		for (j = 1; j < col - 1; j++)
		{
			printf("%c ", real_mine[i][j]);
		}
		printf("\n");
	}
	printf("10 ");//开始打印最后一行
	for (i = 1; i < row - 1; i++)
	{
		printf("%c ", real_mine[10][i]);
	}
	printf("\n");
}



void set_mine()//给设计者棋盘布雷
{
	int x = 0;
	int y = 0;
	int count = COUNT;//雷总数
	while (count)	  //雷布完后跳出循环
	{
		int x = rand() % 10 + 1;	//产生1到10的随机数，在数组下标为1到10的范围内布雷
		int y = rand() % 10 + 1;	//产生1到10的随机数，在数组下标为1到10的范围内布雷
		//上两行代码就是随机坐标的指令
		if (real_mine[x][y] == '0') //找不是雷的地方布雷
		{
			real_mine[x][y] = '1';//埋雷（让1覆写0，反复于此，直至雷埋完）
			count--;
		}
	}
}


int count_mine(int x, int y)//检测周围8个区域雷的个数
{
	int count = 0;
	if (  real_mine[x - 1][y - 1] == '1'
		||real_mine[x - 1][y] == '1'
		||real_mine[x - 1][y + 1] == '1'
		||real_mine[x][y - 1] == '1'
		||real_mine[x][y + 1] == '1'
		||real_mine[x + 1][y - 1] == '1'
		||real_mine[x + 1][y] == '1'
		||real_mine[x + 1][y + 1] == '1')
		count++;
	return count;
}

int safe_mine()//避免第一次炸死
{
	int x = 0;
	int y = 0;
	char ch = 0;
	int count = 0;
	int ret = 1;
	printf("输入坐标扫雷\n");
	while (1)
	{
		scanf_s("%d%d", &x, &y);//只能输入1到10，输入错误重新输入
		if ((x >= 1 && x <= 10) && (y >= 1 && y <= 10))//在坐标内
		{
			if (real_mine[x][y] == '1')//第一次踩到雷后补救
			{
				real_mine[x][y] = '0';//覆写为0就会安全
				char ch = count_mine(x, y);//ch为统计周围雷的个数
				show_mine[x][y] = ch + '0';//数字对应的ASCII值和数字字符对应的ASCII值相差48，即'0'的ASCII值
				open_mine(x, y);//坐标周围的展开函数
				while (ret)//在其余有空的地方设置一个雷（让雷的总树保持平衡）
				{
					int x = rand() % 10 + 1;//产生1到10的随机数，在数组下标为1到10的范围内布雷
					int y = rand() % 10 + 1;//产生1到10的随机数，在数组下标为1到10的范围内布雷
					if (real_mine[x][y] == '0')//找不是雷的地方布雷
					{
						real_mine[x][y] = '1';
						ret--;
						break;
					}
				}break;//跳出此函数	
				
			}
			if (real_mine[x][y] == '0')//第一次没踩到雷
			{
				char ch = count_mine(x, y);//ch为统计周围雷的个数
				show_mine[x][y] = ch + '0';//数字对应的ASCII值和数字字符对应的ASCII值相差48，即'0'的ASCII值
				//为之后的open_mine函数直接从0开始
				open_mine(x, y);//坐标周围的展开函数
				break;
			}
		}
		else//坐标错误
		{
			printf("输入错误重新输入\n");
		}
	}
	
}


int sweep_mine()//扫雷函数，踩到雷返回1，没有踩到雷返回0
{
	int x = 0;
	int y = 0;
	int count = 0;
	printf("输入坐标扫雷\n");
	scanf_s("%d%d", &x, &y);//只能输入1到10
	if ((x >= 1 && x <= 10) && (y >= 1 && y <= 10))//判断输入坐标是否有误，输入错误重新输入
	{
		if (real_mine[x][y] == '0')//没踩到雷
		{
			char ch = count_mine(x, y);
			show_mine[x][y] = ch + '0';//数字对应的ASCII值和数字字符对应的ASCII值相差48，即'0'的ASCII值
			open_mine(x, y);
			if (count_show_mine() == COUNT)//判断剩余未知区域的个数，个数为雷数时玩家赢
			{
				print_mine();
				printf("玩家赢！\n\n");
				return 0;
			}
		}
		else if (real_mine[x][y] == '1')//踩到雷
		{
			return 1;
		}

	}
	else
	{
		printf("输入错误重新输入\n");
	}
	return 0;//没踩到雷
}



void open_mine(int x, int y)//坐标周围展开函数
{
	if (real_mine[x - 1][y - 1] == '0')
	{
		show_mine[x - 1][y - 1] = count_mine(x - 1, y - 1) + '0';//显示该坐标周围雷数
	}
	if (real_mine[x - 1][y] == '0')
	{
		show_mine[x - 1][y] = count_mine(x - 1, y) + '0';//显示该坐标周围雷数
	}
	if (real_mine[x - 1][y + 1] == '0')
	{
		show_mine[x - 1][y + 1] = count_mine(x - 1, y + 1) + '0';//显示该坐标周围雷数
	}
	if (real_mine[x][y - 1] == '0')
	{
		show_mine[x][y - 1] = count_mine(x, y - 1) + '0';//显示该坐标周围雷数
	}
	if (real_mine[x][y + 1] == '0')
	{
		show_mine[x][y + 1] = count_mine(x, y + 1) + '0';//显示该坐标周围雷数
	}
	if (real_mine[x + 1][y - 1] == '0')
	{
		show_mine[x + 1][y - 1] = count_mine(x + 1, y - 1) + '0';//显示该坐标周围雷数
	}
	if (real_mine[x + 1][y] == '0')
	{
		show_mine[x + 1][y] = count_mine(x + 1, y) + '0';//显示该坐标周围雷数
	}
	if (real_mine[x + 1][y + 1] == '0')
	{
		show_mine[x + 1][y + 1] = count_mine(x + 1, y + 1) + '0';//显示该坐标周围雷数
	}
}


int count_show_mine()//判断剩余未知区域的个数，个数为雷数时玩家赢（扫雷排干净，留下来的全都是雷）
{
	int count = 0;
	int i = 0;
	int j = 0;
	for (i = 1; i <= row - 2; i++)
	{
		for (j = 1; j <= col - 2; j++)
		{
			if (show_mine[i][j] == '*')
			{
				count++;
			}
		}

	}
	return count;
}

void game_GOD()
{

	int ret = 0;
	init_mine();//初始化玩家棋盘和设计者棋盘
	set_mine();//给设计者棋盘布雷
	printf("开启上帝视角\n");
	print_mine();//打印设计者棋盘（可不打印）
	printf("\n");
	print_player();//打印玩家棋盘
	start = clock();
	safe_mine();//避免第一次被炸死
		printf("为避免故意输入一次雷，触发“第一次绝对安全”的措施后雷变随机的情况，现在再给你看一遍\n");
		print_mine();
		printf("\n");
	

	if (count_show_mine() == COUNT)//赢的情况
	{
		print_mine();
		printf("玩家赢！\n\n");
		return;
	}print_player(); //打印玩家棋盘

	while (1)//循环扫雷
	{
		int ret = sweep_mine();//扫雷,踩到雷返回1，没有踩到雷返回0
		if (count_show_mine() == COUNT)//若玩家棋盘的'*'个数为雷数时，扫雷完成，游戏胜利
		{
			print_mine();//打印设计者棋盘
			printf("玩家赢！\n\n");
			finish = clock();//取结束时间
			printf("用时 %d 秒\n", (int)(finish - start) / CLOCKS_PER_SEC);//取时间的框死指令
			break;
		}
		if (ret)//判断是否踩到雷
		{
			printf("被雷炸死\t");
			finish = clock();//取结束时间
			printf("用时 %d 秒\n", (int)(finish - start) / CLOCKS_PER_SEC);
			printf("\n这是雷阵\n");
			print_mine();//打印设计者雷阵，以查看雷的分布
			break;
		}
		print_player();//打印玩家棋盘
	}
}


void game()
{

	int ret = 0;
	init_mine();//初始化玩家棋盘和设计者棋盘
	set_mine();//给设计者棋盘布雷
	//printf("开启上帝视角\n");
	//print_mine();//打印设计者棋盘（可不打印）
	printf("\n");
	print_player();//打印玩家棋盘
	start = clock();
	safe_mine();//避免第一次被炸死

	if (count_show_mine() == COUNT)//赢的情况
	{
		print_mine();
		printf("玩家赢！\n\n");
		return;
	}print_player(); //打印玩家棋盘

	while (1)//循环扫雷
	{
		int ret = sweep_mine();//扫雷,踩到雷返回1，没有踩到雷返回0
		if (count_show_mine() == COUNT)//若玩家棋盘的'*'个数为雷数时，扫雷完成，游戏胜利
		{
			print_mine();//打印设计者棋盘
			printf("玩家赢！\n\n");
			finish = clock();//取结束时间
			printf("用时 %d 秒\n", (int)(finish - start) / CLOCKS_PER_SEC);//取时间的框死指令
			break;
		}
		if (ret)//判断是否踩到雷
		{
			printf("被雷炸死\t");
			finish = clock();//取结束时间
			printf("用时 %d 秒\n", (int)(finish - start) / CLOCKS_PER_SEC);
			printf("\n这是雷阵\n");
			print_mine();//打印设计者雷阵，以查看雷的分布
			break;
		}print_player();//打印玩家棋盘
	}
}

