#include<iostream>
#include<windows.h>	//定义控制台应用程序的入口点
#include<conio.h>
#include<time.h>
#include<string>
using namespace std;

/*=============== all the structures ===============*/
//   COORD 是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。
// 其定义为：
// typedef struct _COORD {
//             SHORT X;  
//             SHORT Y;


//定义敌人结构 其中最后面Frame代表结构体类型 若不加typedef代表定义的结构体变量
typedef struct Frame
{
	COORD position[2];
	int flag;
}Frame;

//界面颜色 
void setcolor(string str)	//这里不可以用char str[]，因为后面的if等式右边是const char*型，无法用char*来匹配
{
	if (str == "lightblue")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 1);
	if (str == "lightred")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	if (str == "lightpurple")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	if (str == "lightpink")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	if (str == "blue")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
	if (str == "red")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
	if (str == "green")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	if (str == "purple")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
	if (str == "pink")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
	if (str == "gray")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	if (str == "white")
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	else return;
}

/*=============== all the functions ===============*/

void SetPos(COORD a)// set cursor 
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}

void SetPos(int i, int j)// set cursor
{
	COORD pos = { i, j };
	SetPos(pos);
}

void HideCursor()	//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//第二个值0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//把第y行，[x1, x2]之间的坐标填充为 ch
void drawRow(int y, int x1, int x2, char ch)
{
	SetPos(x1, y);
	for (int i = 0; i <= (x2 - x1); i++)
		cout << ch;
}

/*
//在a, b 纵坐标相同的前提下，把坐标[a, b] 之间填充ch
void drawRow(COORD a, COORD b, char ch)
{
	if (a.Y == b.Y)
		drawRow(a.Y, a.X, b.X, ch);
	else
	{
		SetPos(0, 25);
		cout << "error code 01：无法填充行，因为两个坐标的纵坐标x不相同";
		system("pause");
	}
}
*/

//把第x列，[y1, y2] 之间的坐标填充为 ch
void drawCol(int x, int y1, int y2, char ch)
{
	int y = y1;
	while (y != y2 + 1)
	{
		SetPos(x, y);
		cout << ch;
		y++;
	}
}

/*
//在a, b 横坐标相同的前提下，把坐标[a, b] 之间填充ch
void drawCol(COORD a, COORD b, char ch)
{
	if (a.X == b.X)
		drawCol(a.X, a.Y, b.Y, ch);
	else
	{
		SetPos(0, 25);
		cout << "error code 02：无法填充列，因为两个坐标的横坐标y不相同";
		system("pause");
	}
}
*/

//左上角坐标、右下角坐标，用row填充行、用col填充列
void drawFrame(COORD a, COORD  b, char row, char col)//画出敌机
{//4参之同名函数
	drawRow(a.Y, a.X + 1, b.X - 1, row);
	drawRow(b.Y, a.X + 1, b.X - 1, row);
	drawCol(a.X, a.Y + 1, b.Y - 1, col);
	drawCol(b.X, a.Y + 1, b.Y - 1, col);
}


void drawFrame(int x1, int y1, int x2, int y2, char row, char col)//本质上是画出界面的边框	
{//6参之同名函数
	COORD a = { x1, y1 };
	COORD b = { x2, y2 };
	drawFrame(a, b, row, col);
}


void drawFrame(Frame frame, char row, char col)	//画坠毁后的飞机
{//3参之同名函数 
	COORD a = frame.position[0];
	COORD b = frame.position[1];
	drawFrame(a, b, row, col);
}

// 绘制游戏界面
void drawPlaying()
{									  //下面的drawFrame就是画界面
	drawFrame(0, 0, 48, 24, '=', '|');//	draw map frame主界面
	drawFrame(49, 0, 79, 4, '-', '|');//	draw output frame状态界面
	drawFrame(49, 4, 79, 9, '-', '|');//	draw score frame分数界面
	drawFrame(49, 9, 79, 20, '-', '|');//	draw operate frame操作界面
	drawFrame(49, 20, 79, 24, '-', '|');//	draw other message frame提示界面
	SetPos(52, 6);	//SetPos就是画界面用的
	cout << "得分";
	SetPos(52, 7);
	cout << "称号";

	setcolor("green");
	SetPos(52, 10);
	cout << "操作方式";
	SetPos(52, 12);
	cout << "  a,s,d,w 控制战机移动";
	SetPos(52, 14);
	cout << "  p 暂停游戏";
	SetPos(52, 16);
	cout << "  e 退出游戏";
	SetPos(52, 18);
	cout << "  k 攻击";
	setcolor("white");
}

//在[a, b]之间产生一个随机整数
int random(int a, int b)
{
	int c = (rand() % (a - b)) + a;
	return c;
}

//在两个坐标包括的矩形框内随机产生一个坐标
COORD random(COORD a, COORD b)
{
	int x = random(a.X, b.X);
	int y = random(a.Y, b.Y);
	COORD c = { x, y };
	return c;
}

// 该函数用来判断飞机的某一部分是否与敌机有接触
// 如果与敌机有接触在判断为坠毁
bool judgeCoordInFrame(Frame frame, COORD spot)
{
	if (spot.X >= frame.position[0].X
		&& spot.X <= frame.position[1].X
		&& spot.Y >= frame.position[0].Y
		&& spot.Y <= frame.position[0].Y)
		return true;
	return false;
}

/*
void printCoord(COORD a)
{
	cout << "( " << a.X << " , " << a.Y << " )";
}

void printFrameCoord(Frame a)
{
	printCoord(a.position[0]);
	cout << " - ";
	printCoord(a.position[1]);
}
*/

//主菜单绘制
int drawMenu()	//开始界面，开画
{
	SetPos(30, 1);
	cout << "P l a n e  W a r";
	drawRow(3, 0, 79, '-');
	drawRow(5, 0, 79, '-');
	SetPos(28, 4);
	cout << "w、s 或者↑↓选择   回车开始 ";
	SetPos(15, 11);
	cout << "1.简单的敌人";
	SetPos(15, 13);
	cout << "2.冷酷的敌人";
	drawRow(20, 0, 79, '-');
	drawRow(22, 0, 79, '-');
	SetPos(49, 11);
	cout << "简单的敌人：";
	SetPos(49, 13);
	cout << "简单的敌人有着较慢的移动速度";
	SetPos(24, 21);
	int j = 11;
	SetPos(12, j);
	cout << "->";

	drawFrame(45, 8, 79, 16, '=', '|');

	while (1)
	{
		if (_kbhit())  //_kbbit()函数的作用是检查控制台窗口的按键是否被按下
		{
			char x = _getch(); //_getch()函数的作用是从控制台中获取输入的字符
			switch (x)
			{
			case 'w':	//输入w键
			case 72:  //↑：72
			{
				if (j == 13)
				{
					SetPos(12, j);
					cout << "　";
					j = 11;
					SetPos(12, j);
					cout << "->";
					SetPos(51, 13);
					cout << "　　　　　　　　　　　　";
					SetPos(49, 11);
					cout << "简单的敌人：";
					SetPos(49, 13);
					cout << "简单的敌人有着较慢的移动速度";
				}
				break;
			}
			case 's':
			case 80:  //↓：80
			{
				if (j == 11)
				{
					SetPos(12, j);
					cout << "　";
					j = 13;
					SetPos(12, j);
					cout << "->";
					SetPos(51, 13);
					cout << "　　　　　　　　　　　　　　";
					SetPos(49, 11);
					cout << "冷酷的敌人：";
					SetPos(49, 13);
					cout << "冷酷的敌人有着较快的移动速度";
				}
				break;
			}
			case 13:	//开始游戏 回车键：13
			{
				if (j == 8)	return 1;	//源代码为8
				else return 2;
			}
			}
		}
	}
}

/*
DWORD WINAPI MusicFun(LPVOID lpParamte)  //这是调用bgm.wav文件
{
	//DWORD OBJ;
	sndPlaySound(TEXT("bgm.wav"), SND_FILENAME|SND_ASYNC);
	return 0;
}
*/


/*================== the Game Class ==================*/

class Game
{
public:
	COORD position[10];
	COORD bullet[10];	//一屏最多同时存在10发子弹
	Frame enemy[8];		//一屏最多同时存在8个敌人
	int score;
	int rank;	//级别,难度
	int rankf;	//等级标志
	string title;
	int flag_rank;	//等级标志

	Game(); //构造函数

	//初始化所有	(设定位置)
	void initPlane();
	void initBullet();
	void initEnemy();

	//初始化(剩下未使用之物)
	//void initThisBullet( COORD );
	//void initThisEnemy( Frame );


	//执行某一个操作
	void planeMove(char);//飞机移动
	void bulletMove();	//子弹移动
	void enemyMove();	//敌机移动

	//填充所有	画出形状和消失的形状
	void drawPlane();
	void drawPlaneToNull();
	void drawBullet();
	void drawBulletToNull();
	void drawEnemy();
	void drawEnemyToNull();


	//填充其中一
	void drawThisBulletToNull(COORD);//画出失效子弹
	void drawThisEnemyToNull(Frame);

	void Pause();//该成员函数用来使游戏暂停
	void Playing();//游戏主循环
	void judgePlane();//判断飞机是否与敌机重叠
	void judgeEnemy();//判断子弹是否击中敌机

	void Shoot();//发射子弹

	void GameOver();//游戏失败
	void printScore();//输出分数
};

Game::Game()	//开始游戏的初始化
{
	initPlane();
	initBullet();
	initEnemy();
	// 初始化四个int型数据成员，采用赋值的方式进行初始化
	// string类型的数据成员title没有进行初始化，因为：
	// string本身就是一个标准库类类型，它的类定义中设置了默认构造函数，
	// 这些默认构造函数会将对象初始化为合理的默认状态，
	// string的默认构造函数会产生空字符串，相当于"" 。
	score = 0;
	rank = 25;
	rankf = 0;
	flag_rank = 0;
}

// 这个函数体类的代码其实就是为了初始化战机的十个部分的位置，战机的组成如下所示：   
//                     |       5 
//                     |       9    
//                   *****   12034
//                    ***     678
// 第一排5个0的坐标依次对应了position[1]position[2]position[0]position[3]position[4]
// 第二排三个0的坐标依次对应了position[6]position[7]position[8]
// 两排0上面的两|的坐标从上往下依次对应了position[5]position[9]
void Game::initPlane()	//初始化飞机
{
	COORD center = { 39, 22 };
	position[0].X = position[5].X = position[7].X = position[9].X = center.X;
	position[1].X = center.X - 2;
	position[2].X = position[6].X = center.X - 1;
	position[3].X = position[8].X = center.X + 1;
	position[4].X = center.X + 2;
	for (int i = 0; i <= 4; i++)
		position[i].Y = center.Y; //都在y那一行
	for (int i = 6; i <= 8; i++)
		position[i].Y = center.Y + 1; //都在y+1那一行
	position[5].Y = center.Y - 1;
	position[9].Y = center.Y - 2;
}

void Game::drawPlane()	//画飞机
{
	for (int i = 0; i < 9; i++)
	{
		SetPos(position[i]);
		if (i != 5)
			cout << "@";	//飞机身体
		else if (i == 5)
			cout << "|";	//飞机头
	}
}

void Game::drawPlaneToNull()	//碰到敌机后的飞机图像
{
	for (int i = 0; i < 9; i++)
	{
		SetPos(position[i]);
		cout << " ";
	}
}

void Game::initBullet()	//初始化子弹
{
	for (int i = 0; i < 10; i++)
		bullet[i].Y = 30;	//子弹开始的位置
}

void Game::drawBullet()	//画子弹
{
	for (int i = 0; i < 10; i++)
	{
		if (bullet[i].Y != 30)//子弹的动画
		{
			SetPos(bullet[i]);
			setcolor("blue");
			cout << "*";	//子弹输出
			setcolor("white");
		}
	}
}

void Game::drawBulletToNull()	//碰到敌人or出界为NULL  让子弹消失
{
	for (int i = 0; i < 10; i++)
		if (bullet[i].Y != 30)
		{
			COORD pos = { bullet[i].X, bullet[i].Y + 1 };
			SetPos(pos);
			cout << " ";
		}
}

/*
void Game::drawBulletToNull_EXTRA()  //作弊码：bullet
{
	for (int i = 0; i < 10; i++)
		if (bullet[i].Y != 30)
		{
			COORD pos = { bullet[i].X, bullet[i].Y - 1 };
			SetPos(pos);
			cout << " ";
		}
}
*/

void Game::initEnemy()	//初始化敌机
{
	COORD a = { 1, 1 };
	COORD b = { 45, 15 };
	for (int i = 0; i < 8; i++)	//一个界面恒定同时存在8个敌人
	{
		enemy[i].position[0] = random(a, b);//随机出现最后一行的某个位置
		// random(a, b)是调用了一个重载的函数，它表示在坐标a、b之间的矩形框
		// 内随机生成一个坐标值，并将该坐标值作为敌机的左上角的坐标。
		// enemy[i].position[0]中是一个Frame结构体类型的变量，存放了敌机i的左上角的坐标。
		enemy[i].position[1].X = enemy[i].position[0].X + 3; //敌机左右长
		enemy[i].position[1].Y = enemy[i].position[0].Y + 2; //敌机前后长
		// enemy[i].position[1]也中是一个Frame结构体类型的变量，存放了敌机i的右下角的坐标。
	}
}

// 接下来要根据敌机的左上角坐标和右下角坐标画出敌机，
// 显然，敌机的外形如下所示：
//   --
//  |  |
//   --
void Game::drawEnemy()	//画敌机
{
	for (int i = 0; i < 8; i++)
		drawFrame(enemy[i].position[0], enemy[i].position[1], '-', '|');
	//8个敌机都是一个体型，并且在此画出体型
}

void Game::drawEnemyToNull()  //触发某种情况后敌机消失
{
	for (int i = 0; i < 8; i++)
	{
		drawFrame(enemy[i].position[0], enemy[i].position[1], ' ', ' ');
	}
	//8个敌机的某个直接消失
}


// 当出现"暂停中"的提示以后，程序会接收按下的按键，
// 当按下'p'键以后，说明要退出暂停状态，此时需要清除"暂停中"的提示
// 通过输出空白 "         "来将其覆盖，达到效果
void Game::Pause()	//暂停
{
	SetPos(61, 2);
	cout << "               ";
	SetPos(61, 2);
	cout << "暂停中";
	char c = _getch();
	while (c != 'p')
		c = _getch();
	SetPos(61, 2);
	cout << "         ";
}

void Game::planeMove(char x)	//asdw移动
{
	if (x == 'a')
		if (position[1].X != 1)//左界
			for (int i = 0; i <= 9; i++) //9是因为我方飞机由10个字符而画成
				position[i].X -= 2;

	if (x == 's')
		if (position[7].Y != 23)//下界
			for (int i = 0; i <= 9; i++)
				position[i].Y += 1;

	if (x == 'd')
		if (position[4].X != 47)//右界
			for (int i = 0; i <= 9; i++)
				position[i].X += 2;

	if (x == 'w')
		if (position[5].Y != 3)//上界
			for (int i = 0; i <= 9; i++)
				position[i].Y -= 1;
}

// 此成员函数用来响应一次子弹的运动
// 每次子弹运动，屏幕子弹的坐标都会出现变化，即
// 先判断子弹是否有效（即判断语句if (bullet[i].Y != 30)），
// 若子弹有效，将该子弹的Y坐标减少1，X坐标不变，
// 检测子弹坐标更改之后是否达到上边界，如果达到上边界，则将该子弹从屏幕上擦除，
// 同时，将该子弹置为失效状态，即 bullet[i].Y = 30。
void Game::bulletMove()	//子弹移动
{
	for (int i = 0; i < 10; i++)	//子弹最多同时存在10颗
	{
		if (bullet[i].Y != 30)	//不是下界
		{
			bullet[i].Y -= 1;	//发出子弹，起到子弹移动的效果
			if (bullet[i].Y == 1)	//到达上界时or碰到敌机时
			{
				COORD pos = { bullet[i].X, bullet[i].Y + 1 };
				//获取这个子弹到消失的临界状态

				drawThisBulletToNull(pos);	//让子弹消失
				bullet[i].Y = 30;	//一发子弹出界，就有一发可以发出来
			}

		}
	}
}

//该成员函数用来响应一次敌机的移动
//界面上必须同时出现八架敌机，因此
//如果有某架敌机运动到下边界处，则重置该敌机的坐标
void Game::enemyMove()	//敌机移动
{
	for (int i = 0; i < 8; i++)	//8个敌机
	{
		for (int j = 0; j < 2; j++) //移动
			enemy[i].position[j].Y++;
		// 我们将每架敌机的左上角和右下角坐标的Y值增加1，
		// 表示该敌机向下走了一个距离

		// 检测向下走一个距离后的敌机的右下角坐标的Y值是否达到24，
		// 如果达到，代表敌机已经运动到下边界了，
		// 此时需要随机重置该敌机的坐标（新的敌机诞生）
		if (24 == enemy[i].position[1].Y)
		{
			COORD a = { 1, 1 };
			COORD b = { 45, 3 };
			enemy[i].position[0] = random(a, b);
			enemy[i].position[1].X = enemy[i].position[0].X + 3;	//敌机宽
			enemy[i].position[1].Y = enemy[i].position[0].Y + 2;	//敌机长
		}
	}
}

// 该成员函数用来判断战机是否坠毁，
// 依次判断每架障碍物与战机的每个部分是否有接触，
// 如果有接触，则表示战机坠毁
void Game::judgePlane()	 //判断飞机是否与障碍物重叠
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 9; j++)
			// 此处的实参position[j]是指战机的10个部分的COORD坐标，
			// 类中的成员函数可以访问数据成员变量。
			// 此处也可以写成this->position[j]，因为
			// 成员函数具有一个附加的隐含形参，即指向该类对象的一个指针，
			// 这个隐含形参命名为this，与调用成员函数的对象绑定在一起。
			// 成员函数不能定义this形参，而是由编译器隐含地定义。
			// 成员函数的函数体可以显式使用this指针，但不是必须这么做。
			if (judgeCoordInFrame(enemy[i], position[j]))
			{
				SetPos(62, 1);
				cout << "坠毁";
				setcolor("red");
				drawFrame(enemy[i], '+', '+');
				setcolor("white");
				// 将与战机相撞的障碍物的形状绘制为:
				//    ++
				//   +  +
				//    ++
				Sleep(1000);
				GameOver();
				break;
			}
}

void Game::drawThisBulletToNull(COORD c)  //子弹消失的形状
{
	SetPos(c);
	cout << " ";
}

void Game::drawThisEnemyToNull(Frame f)	//敌机消失的形状
{
	drawFrame(f, ' ', ' ');
}

// 该成员函数依次遍历每一架敌机，
// 将每一架敌机依次与每一颗子弹进行检测（双重遍历）
// 判断敌机是否与子弹有接触，如果有接触，则表示击中敌机，
// 此时将敌机和子弹擦除，然后在界面顶部的位置处随机生成一架敌机
void Game::judgeEnemy()		//判断子弹是否击中敌机
{
	for (int i = 0; i < 8; i++)//遍历敌机
		for (int j = 0; j < 10; j++)//遍历子弹
			if (judgeCoordInFrame(enemy[i], bullet[j]))
				//如果当前存在用子弹打死敌机的情况的话，就执行下列代码
			{
				score += 5;//加分
				drawThisEnemyToNull(enemy[i]);//敌机消失
				COORD a = { 1, 1 };
				COORD b = { 45, 3 };
				enemy[i].position[0] = random(a, b);
				enemy[i].position[1].X = enemy[i].position[0].X + 3;//敌机宽
				enemy[i].position[1].Y = enemy[i].position[0].Y + 2;//敌机长
				drawThisBulletToNull(bullet[j]);//子弹消失
				bullet[j].Y = 30;//新子弹坐标
			}
}


// 这个成员函数用来响应一次射击操作，
// 也就是，当游戏中的时候，玩家按下"k"键，就执行该函数。
// 由于子弹是由COORD bullet[10]定义的，因此同一时刻，界面内只能有10颗子弹同时出现。
// 如果界面内不够10颗子弹，按下"k"键后战机应该发射出一颗子弹，
// 于是，依次遍历10颗子弹，当遇到第一颗失效的子弹后，
// 立即将该子弹赋予新的坐标（飞机的炮口，也就是（position[5].X，position[5].Y - 1）），
// 让其激活。然后退出for循环，函数执行完毕。
void Game::Shoot()
{
	for (int i = 0; i < 10; i++)
		if (bullet[i].Y == 30)
		{
			bullet[i].X = position[5].X;//飞机的炮口就是新生成的子弹的初始位置
			bullet[i].Y = position[5].Y - 1;
			break;
		}
}

void Game::printScore()
{
	if (score == 120 && flag_rank == 0)	//分数到120就升级，并且画面速度加快（画面刷新时间变短）
	{
		rank -= 5;
		flag_rank = 1;
	}

	else if (score == 240 && flag_rank == 1) //240
	{
		rank -= 5;
		flag_rank = 2;
	}
	else if (score == 360 && flag_rank == 2) //360
	{
		rank -= 5;
		flag_rank = 3;
	}
	int x = rank / 5;
	SetPos(60, 6);
	cout << score;

	if (rank != rankf)
	{
		SetPos(60, 7);
		if (x == 4)	//初始为4
			title = "初级飞行员";
		else if (x == 3) //升级后x-1
			title = "中级飞行员";
		else if (x == 2)
			title = "高级飞行员";
		else if (x == 1)
			title = "王牌飞行员";
		cout << title;
	}
	rankf = rank;
}


// 这个成员函数是游戏的主循环函数，
// 定义了整个游戏过程。
void Game::Playing()
{
	//HANDLE MFUN;
	//MFUN = CreateThread(NULL, 0, MusicFun, NULL, 0, NULL); 

	drawEnemy();
	drawPlane();

	int flag_bullet = 0;
	int flag_enemy = 0;

	while (1)
	{
		Sleep(8);
		if (_kbhit())
		{
			char x = _getch();
			if ('a' == x || 's' == x || 'd' == x || 'w' == x)
			{
				drawPlaneToNull();//先让飞机的图像消失
				planeMove(x);//飞机移动
				drawPlane();//访问类中的数据成员（飞机）的坐标，在新的坐标处【重新绘制飞机】
				judgePlane();//判断飞机是否与敌机重叠（坠毁）
			}

			// 在某一循环当中，如果检测到有'p'键按下，
			// 首先在右侧游戏界面输出"暂停中..."，然后陷入while()循环一直等待'p'键再次按下，
			// 如果'p'键没有按下，就一直处在while()循环内，因此不能执行后面的程序，起到暂停的效果。
			else if ('p' == x)
				Pause();

			// 如果是检测到'k'键按下，则运行Shoot()函数
			else if ('k' == x)
				Shoot();

			// 如果是检测到'e'键按下，则运行GameOver()函数，
			// GameOver()函数执行完毕后，执行break;语句跳出while循环（注意不是if (_kbhit())）。
			// break语句用于结束最近的while、do while、for或switch语句，并将程序的执行权传递给紧接在
			// 被终止语句之后的语句。
			else if ('e' == x)
			{
				//CloseHandle(MFUN);
				GameOver();
				break;
			}

		}
		/* 处理子弹 */
		// 判断子弹状态的程序一直在运行
		if (0 == flag_bullet)
		{
			bulletMove();           // 更新界面上有效子弹的坐标
			drawBulletToNull();     // 将处于旧坐标的子弹擦除
			drawBullet();           // 绘制出新坐标上的子弹
			judgeEnemy();           // 判断障碍物是否被子弹击中
		}
		flag_bullet++;
		if (5 == flag_bullet)	//子弹CD，5个sleep(8)后可以重新再按一发
			flag_bullet = 0;

		/* 处理敌人 */
		if (0 == flag_enemy)
		{
			drawEnemyToNull();     // 将所有的障碍物都擦除
			enemyMove();           // 更新障碍物的坐标
			drawEnemy();           // 绘制出处于新坐标上的障碍物
			judgePlane();          // 判断障碍物是否与战机接触
		}
		flag_enemy++;	//通过缩短画面刷新的时长，从而达到视觉上的加速效果
		if (flag_enemy >= rank)	   //难度一提升就增速
			flag_enemy = 0;		//实际上，如果眼尖的话，可以看出是逐渐加速后跳回原来速度，再逐渐加速的循环

		/* 输出得分 */
		printScore();
	}
}

void Game::GameOver()//游戏结束
{
	system("cls");
	COORD p1 = { 28,9 };	//标记字符要填充的部分
	COORD p2 = { 53,15 };
	drawFrame(p1, p2, '=', '|');//字符填充
	SetPos(36, 12);
	setcolor("lightpurple");
	string str = "Game Over";
	for (int i = 0; i < str.size(); i++)
	{
		Sleep(80);//Game Over每输出一个字符，要休息0.08秒
		cout << str[i];
	}
	setcolor("white");
	Sleep(1000);	//休息1秒后跳转下一个界面
	system("cls");
	drawFrame(p1, p2, '=', '|');  //还是原来的预设定位置，只需要重新画上就行
	SetPos(31, 11);
	cout << "击落敌机: " << score / 5;
	SetPos(31, 12);
	cout << "得　　分：" << score;
	SetPos(31, 13);
	cout << "获得称号: " << title;
	SetPos(30, 16);
	Sleep(1000);
	setcolor("green");
	cout << "继续 是（y）| 否（n）";
	setcolor("white");
as:
	char x = _getch();
	if (x == 'n')
		exit(0);//整个程序退出
	else if (x == 'y')
	{
		system("cls");
		Game game;
		int a = drawMenu();// 绘制游戏开始界面主菜单
		if (a == 2)
			game.rank = 20;	//一开始是20，方便/5分四个阶段
		system("cls");
		drawPlaying();// 绘制游戏界面框架
		game.Playing();
	}
	else goto as;//你输入了其他的键，是无效的，重新给你一次输入机会
}

/*================== the main function ==================*/
int main()
{
	//游戏准备
	cout << "\t\t****飞机大战游戏正在准备****\n";
	cout << "\n已加载 0%";
	for (int i = 0; i < 9; i++) {
		SetPos((i + 1) * 2 - 1, 1); cout << "■ ";
		SetPos(7 - 1, 3 - 1); cout << i + 1;
		Sleep(30);
	}
	Sleep(30);
	SetPos(19, 1); cout << "■ \n已加载100%";
	Sleep(50);
	system("cls");
	srand((int)time(0));	//随机种子
	HideCursor();	//隐藏光标

	Game game;
	int a = drawMenu();
	if (a == 2)
		game.rank = 20;
	system("cls");
	drawPlaying();
	game.Playing();
}


// 函数名：kbhit()（VC++6.0下为_kbhit()）
// 功能及返回值：检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
// 用法：int kbhit(void);
// 包含头文件： include <conio.h>
// kbhit()在执行时,检测是否有按键按下,有按下返回非0值，没有按下则返回0，是非阻塞函数；
// 不同于getch()的在执行时, 检测按下什么键, 如果不按键该函数不返回，也就不进行下一步操作，是阻塞函数。


// getch()是编程中所用的函数，这个函数是一个不回显函数，
// 当用户按下某个字符时，函数自动读取，无需按回车
// getch()并非标准C中的函数，不存在C语言中。
// 所在头文件是conio.h，而不是stdio.h。
// 用ch = getch(); 会等待你按下任意键之后，把该键字符所对应的ASCII码赋给ch, 再执行下面的语句。

