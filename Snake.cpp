#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>
using namespace std;

/*** 光标定位 ***/
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);  //获取 标准输出句柄
COORD coord;

void locate(int x, int y)
{
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(hout, coord);  //输出光标位置
};

/*** 隐藏光标 ***/
void hide()
{
    return;
}

/*** 生成随机数 ***/
double random(double start, double end)
{
    return start + (end - start) * rand() / (RAND_MAX + 1.0); //生成一个数，大于等于start，小于end；
    //随机数的高级写法
}

/*** 定义地图的长宽 ***/
int m, n;

//蛇的坐标
struct node
{
    int x, y;
}snake[1000];

//长度，方向，食物的位置
int snake_length, dir;
node food;
int direct[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//食物的位置

/*** 输出墙 ***/
void print_wall()
{
    cout << " ";
    for (int i = 1; i <= n; i++)
        cout << "-";//输出第一行 “----------”
    cout << endl;
    for (int j = 0; j <= m - 1; j++)
    {//输出第一列“|”，中间输入空格，最后一列输出“|”
        cout << "|";//左墙
        for (int i = 1; i <= n; i++) cout << " ";
        cout << "|" << endl;//右墙
    }
    cout << " ";
    for (int i = 1; i <= n; i++)
        cout << "-";//输出最后一行“----------”
}

/*** 首次输出蛇，其中snake[0]代表头 ***/
void print_snake()
{   //蛇的外型：“@*****”
    locate(snake[0].x, snake[0].y);
    cout << "@";//头部
    for (int i = 1; i <= snake_length - 1; i++)//length-1是减去头部的长度
    {
        locate(snake[i].x, snake[i].y);
        cout << "*";//身体
    }
}

/*** 判断是否撞墙或者头部是否碰到身体的任意一个部位，碰到则游戏失败 ***/
bool is_correct()
{
    if (snake[0].x == 0      //上墙
        || snake[0].y == 0      //下墙
        || snake[0].x == m + 1  //右墙
        || snake[0].y == n + 1) //左墙
        return false;
    for (int i = 1; i <= snake_length - 1; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) //自撞
            return false;
    }
    return true;
}

/*** 随机生成并输出食物位置 ***/
bool print_food()
{
    srand((unsigned)time(0));//随机种子
    bool e;
    while (TRUE)
    {
        e = true;
        int i = (int)random(0, m) + 1;
        int j = (int)random(0, n) + 1;
        food.x = i; food.y = j;//食物的位置随机
        for (int k = 0; k <= snake_length - 1; k++)
        {//食物不能出现在蛇的身体的任意位置处
            if (snake[k].x == food.x && snake[k].y == food.y)
            {
                e = false;
                break;
            }
        }
        if (e)
            break;
    }
    locate(food.x, food.y);
    cout << "O";
    return true;
}

/*** 蛇的前进 ***/
bool go_ahead()
{
    node temp;
    bool e = false;
    temp = snake[snake_length - 1]; //蛇尾
    for (int i = snake_length - 1; i >= 1; i--)
        snake[i] = snake[i - 1]; //后移一位（相当于数列插入）
    snake[0].x += direct[dir][0];
    snake[0].y += direct[dir][1];
    locate(snake[1].x, snake[1].y);//定位到头部的后一位
    cout << "*";
    //这是以头部后一位来生成身体，并非尾部加上，省去判断位置而加尾方向的问题

    /*** 吃到了食物 ***/
    if (snake[0].x == food.x && snake[0].y == food.y)
    {
        snake_length++;//身长+1
        e = true;
        snake[snake_length - 1] = temp; //要赋值新的蛇尾
    }

    /*** 输出此时蛇状态 ***/
    if (!e)
    {
        locate(temp.x, temp.y);//蛇尾坐标
        cout << " ";//这是蛇尾之后的一位，如果不为“ ”则会记录蛇的路径
    }
    else
        print_food();
    locate(snake[0].x, snake[0].y);
    cout << "@";//吃到就把食物替换成蛇头

    /*** 如果自撞 ***/
    if (!is_correct())
    {
        system("cls");
        cout << "You lose!" << endl << "Length: " << snake_length << endl;
        return false;
    }
    return true;
}


/*** 主函数 ***/
int main()
{
    cout << "------------------S n a c k---------------------" << endl;
    cout << "请注意窗口大小,以免发生错位。建议将窗口调为最大。" << endl;
    cout << "先选择难度.请在1-10中输入1个数,1最简单,10则最难" << endl;
    cout << "然后进入游戏画面,以方向键控制方向。祝你游戏愉快!" << endl;
    cout << "-----------------------------------------------" << endl;
    m = 25;
    n = 40;
    if (m < 10 || n < 10 || m>25 || n>40)
    {
        cout << "ERROR" << endl;
        system("pause");
        return 0;
    }
    int hard;
    //输入难度系数：1-10
    cin >> hard;
    if (hard <= 0 || hard > 100)
    {
        cout << "ERROR" << endl;
        system("pause");
        return 0;
    }
    /*** 数据全部初始化，包括蛇长，位置，方向 ***/
    snake_length = 5;
    clock_t a, b;
    char ch;
    double hard_len;
    for (int i = 0; i <= 4; i++)
    {
        snake[i].x = 1;
        snake[i].y = 5 - i;
    }
    dir = 3;//方向（是direct数组的对应下标）

    /*** 输出初始地图，蛇与食物 ***/
    system("cls");
    hide();
    print_wall();
    print_food();
    print_snake();
    locate(m + 2, 0);
    cout << "Now length: ";

    /*** 开始游戏 ***/
    while (TRUE)
    {
        /*** 难度随长度增加而提高 ***/
        hard_len = (double)snake_length / (double)(m * n);
        /*** 调节时间，单位是ms ***/
        a = clock();
        while (TRUE)
        {
            b = clock();
            if (b - a >= (int)(400 - 30 * hard) * (1 - sqrt(hard_len)))
                //b-a>=(400-30*难度)*{1-sqrt[蛇长/(地图长*地图宽)]}
                break;
        }
        /*** 接受键盘输入的上下左右，并以此改变方向 ***/
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                switch (ch)
                {
                case 72:
                    if (dir == 2 || dir == 3)//上下可以左，右不可以
                        dir = 0;//左
                    break;
                case 80:
                    if (dir == 2 || dir == 3)//上下可以右，左不可以
                        dir = 1;//右
                    break;
                case 75:
                    if (dir == 0 || dir == 1)//左右可以下，上不可以
                        dir = 2;//下
                    break;
                case 77:
                    if (dir == 0 || dir == 1)//左右可以上，下不可以
                        dir = 3;//上
                    break;
                }
            }
        }
        /*** 前进 ***/
        if (!go_ahead())
            break;
        /*** 在最后输出此时长度 ***/
        locate(m + 2, 12);  //定位到窗口坐标
        cout << snake_length;
    }
    system("pause");
    return 0;
}
