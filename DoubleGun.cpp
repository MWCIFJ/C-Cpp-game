#include<iostream>
#include<cstdio>
#include<windows.h>
#include<conio.h>
using namespace std;
int SIZ = 20;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
HANDLE hCon;
enum Color { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE };
//枚举

void SetColor(Color c)
{
    if (hCon == NULL)
        hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, c);//color函数
}

SYSTEMTIME sys;
//sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek
struct PLAYER 
{
    int x, y;//坐标
    int hp;//生命
    int gun;//枪
    int direct;//方向
} p1, p2;//player1和player2
int map[1005][1005];

int mabs(int x) //与时间相关的函数，让数值绝对值化
{
    if (x < 0) 
        return -x; 
    return x;
}

void locate(int x, int y) //当前坐标 
{
    coord.X = y - 1;
    coord.Y = x - 1;
    SetConsoleCursorPosition(hout, coord);
}

void print_map() //边界方框以画地图
{
    locate(1, 1);
    SetColor(GRAY);
    for (int i = 1; i <= SIZ; i++) cout << "■ ";//上框
    locate(SIZ, 1);
    for (int i = 1; i <= SIZ; i++) cout << "■ ";//下框
    for (int i = 2; i < SIZ; i++) {
        locate(i, 1);
        cout << "■";//左框
        locate(i, SIZ * 2 - 1);
        cout << "■";//右框
    }
    locate(SIZ + 1, 1);
    SetColor(WHITE);
}

void create_tree(int x, int y) //生成树丛
{
          map[x][y] 
        = map[x + 1][y] 
        = map[x - 1][y] 
        = map[x][y + 1] 
        = map[x][y - 1] = 2;
}

void use_map(int x) //选择地图
{
    if (x == 1)
    {
        SIZ = 20;
        SetColor(DARKGREEN);
              map[16][6]
            = map[15][6] 
            = map[17][6] 
            = map[16][7] 
            = map[16][5] 
            = map[14][13] 
            = map[13][12] 
            = map[13][13] = 2;//树的坐标
        for (int i = 2; i < SIZ; i++) {
            for (int j = 2; j < SIZ; j++) {
                if (map[i][j] == 2) {
                    locate(i, j * 2 - 1);
                    cout << "■";//开始画树
                }
            }
        }
        SetColor(GRAY);
        for (int i = 5; i <= 15; i++) {
            map[i][i] = 1;
            locate(i, i * 2 - 1);
            cout << "■";//地图1的对角线墙
        }
        SetColor(WHITE);
    }
    else if (x == 2) //地图2
    {
        SIZ = 30;
        SetColor(GRAY);
        for (int i = 4; i <= 26; i++) {
            if (i == 13 || i == 14 || i == 15) 
                continue;
                  map[i][4] 
                = map[4][i] 
                = map[26][i]
                = map[i][26] = 1;//内边框的缺口，设置之以不用画
        }
        for (int i = 1; i <= SIZ; i++) {
            for (int j = 1; j <= SIZ; j++) {
                if (map[i][j] == 1) {
                    locate(i, j * 2 - 1);
                    cout << "■";//画内边框
                }
            }
        }
        SetColor(DARKGREEN);
        for (int i = 10; i <= 20; i++) {
            if (i == 13 || i == 17) continue;
                  map[i][10] 
                = map[10][i] 
                = map[20][i] 
                = map[i][20] = 2;//设置树的坐标
        }
        create_tree(5, 5);
        create_tree(18, 18);//生成树丛
        for (int i = 1; i <= SIZ; i++) {
            for (int j = 1; j <= SIZ; j++) {
                if (map[i][j] == 2) 
                {
                    locate(i, j * 2 - 1);
                    cout << "■";//开始画树
                }
            }
        }
        SetColor(WHITE);
    }
}

void cleanbody(int x, int y);
void putbody(int x, int y, int z);
void player_init() //初始化p1和p2
{
    p1.hp = p2.hp = 300;
    p1.gun = p2.gun = 1;//枪
    p1.direct = 4;//方向
    p2.direct = 2;
    p1.x = 2;//x坐标
    p1.y = 2;//y坐标
    p2.x = SIZ - 1;
    p2.y = SIZ - 1;
    putbody(p1.x, p1.y, 1);//放置才能画出身体
    putbody(p2.x, p2.y, 2);
}

void mapinit() //初始化地图
{
    for (int i = 1; i <= SIZ; i++) {
              map[i][1] 
            = map[1][i] 
            = map[SIZ][i] 
            = map[i][SIZ] = 1;//边界设定
    }
}

void init() 
{
    printf("Use Which Map?\n");
    int x;
    cin >> x;
    system("cls");
    use_map(x); //有3种地图，1、2、除了1，2的所有其他输入
    mapinit();//初始化地图
    print_map();//显示出地图
    player_init();//初始化p1和p2
}

void putbody(int x, int y, int z) //绘制玩家身体
{
    if (z == 1) SetColor(BLUE);//p1蓝色
    else if (z == 2) SetColor(RED);//p2红色
    locate(x, y * 2 - 1);
    cout << "■";
    SetColor(WHITE);
}

void cleanbody(int x, int y) //清除在这个坐标的身体
{
    locate(x, y * 2 - 1);
    cout << " ";
}
/*
LIST
direct:
    w 1
    a 2
    s 3
    d 4
gun:
    usp 1
    mimigun 2
    awp 3
block:
    void 0
    stone 1
    tree 2
    player 3
    clip 4
*/

bool judge(int x, int y) //判断是否出界（边框）
{
    if (map[x][y] == 1) return false;
    if (map[x][y] == 2) return false;
    if (map[x][y] == 3) return false;
    return true;
}

bool judge_gun(int x, int y) //关于枪击的判断
{
    if (map[x][y] == 1) return 0;
    if (map[x][y] == 2) return 0;
    if (map[x][y] == 3) {
        if (p1.x == x && p1.y == y) //枪打中了
            p1.hp -= 100;//3发就死
        else 
            p2.hp -= 100;
        return 0;
    }
    return 1;
}

int cnt;
struct Clip //子弹
{
    int x, y;//子弹坐标
    int derect;//子弹方向
    int force;//威力
    int start;
    bool flag;
}clip[1000000];//范弗里特当量

void create_clip(int y, int x, int a, int b) //绘制子弹
{
    int X, Y;
    if (y == 1) {
        if (!judge_gun(a - 1, b)) return;//只有枪击判断成功才能继续执行
        X = a - 1;  //子弹射出的位置
        Y = b;      //子弹射出的位置
    }
    else if (y == 2) {
        if (!judge_gun(a, b - 1)) return;
        X = a;
        Y = b - 1;
    }
    else if (y == 3) {
        if (!judge_gun(a + 1, b)) return;
        X = a + 1;
        Y = b;
    }
    else if (y == 4) {
        if (!judge_gun(a, b + 1)) return;
        X = a;
        Y = b + 1;
    }
    cnt++;
    GetLocalTime(&sys);//获得本地时间
    clip[cnt].start = sys.wMilliseconds + sys.wSecond * 60 + sys.wHour * 3600;//子弹的数组开始数值
    clip[cnt].x = X;//坐标x
    clip[cnt].y = Y;//坐标y
    if (x == 1) {//p1
        clip[cnt].derect = p1.direct;//与持枪者同方向
    }
    else if (x == 2) {
        clip[cnt].derect = p2.direct;
    }
}

void shoot(int x) //开枪函数
{
    if (x == 1) {
        create_clip(p1.direct, 1, p1.x, p1.y);//p1开枪
    }
    else if (x == 2) {
        create_clip(p2.direct, 2, p2.x, p2.y);//p2开枪
    }
}

void clean_clip(int x, int y) //子弹轨迹清除
{
    locate(x, y * 2 - 1);
    cout << "  ";
    locate(1, 1);
}

void print_clip(int x, int y, int i) //绘制子弹
{ 
    if (clip[i].flag) {
        clean_clip(x, y);//碰到边框就清除子弹
        return;
    }
    locate(x, y * 2 - 1);
    SetColor(YELLOW);
    cout << "*";
    locate(1, 1);
    //  system("pause");
}

void clipmove() //子弹移动函数
{
    GetLocalTime(&sys);
    int t = sys.wMilliseconds + sys.wSecond * 60 + sys.wHour * 3600;
    for (int i = 1; i <= cnt; i++) {//在范弗里特当量下
        if (clip[i].flag) //开枪就能让子弹执行移动函数
            continue;
        if (mabs(clip[i].start - t) > 50) {//这行其实可以省略
            clip[i].start = t;
            int x = clip[i].x;
            int y = clip[i].y;

            if (clip[i].derect == 1) {//子弹方向为1（上）
                if (!judge_gun(clip[i].x - 1, clip[i].y)) {//能成立开枪的条件
                    clip[i].flag = 1;//让flag成真
                    clean_clip(x, y);//才能好清除子弹
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);//清除子弹
                clip[i].x--;//子弹坐标移动
                print_clip(clip[i].x, clip[i].y, i);//画出子弹，配合sleep()起到动画效果
            }
            else if (clip[i].derect == 2) {
                if (!judge_gun(clip[i].x, clip[i].y - 1)) {
                    clip[i].flag = 1;
                    clean_clip(x, y);
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);
                clip[i].y--;
                print_clip(clip[i].x, clip[i].y, i);
            }
            else if (clip[i].derect == 3) {
                if (!judge_gun(clip[i].x + 1, clip[i].y)) {
                    clip[i].flag = 1;
                    clean_clip(x, y);
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);
                clip[i].x++;
                print_clip(clip[i].x, clip[i].y, i);
            }
            else if (clip[i].derect == 4) {
                if (!judge_gun(clip[i].x, clip[i].y + 1)) {
                    clip[i].flag = 1;
                    clean_clip(x, y);
                    continue;
                }
                clean_clip(clip[i].x, clip[i].y);
                clip[i].y++;
                print_clip(clip[i].x, clip[i].y, i);
            }
        }
    }
}

void judge_hp() //判断某方hp为0就判定游戏结束
{
    int x = p1.hp;
    int y = p2.hp;
    if (x < 0 && y < 0 && x > y) 
        swap(x, y);//交换最小值
    if (x <= 0) {//p1生命<=0
        locate(1, 1);
        system("cls");
        printf("GAME OVER!\nTHE WINNER IS P2!");//p2胜利
        Sleep(5000);
        printf("\n-MADE BY MWVIFJ-");
        exit(0);
    }
    else if (y <= 0) {//p2生命<=0
        locate(1, 1);
        system("cls");
        printf("GAME OVER!\nTHE WINNER IS P1!");//p1胜利
        Sleep(5000);
        printf("\n-MADE BY MWVIFJ-");
        exit(0);
    }
}

void prog() //按键移动
{  
    char ch;
    while (TRUE) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'w' && judge(p1.x - 1, p1.y)) {//未到上边界
                p1.direct = 1;  //向上
                cleanbody(p1.x, p1.y);//清除身体
                map[p1.x][p1.y] = 0;//移动时不能射出
                putbody(--p1.x, p1.y, 1);//在新的坐标画出身体
                map[p1.x][p1.y] = 3;//移动后可以射出
            }
            else if (ch == '8' && judge(p2.x - 1, p2.y)) {
                p2.direct = 1;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(--p2.x, p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == 'a' && judge(p1.x, p1.y - 1)) {
                p1.direct = 2;
                cleanbody(p1.x, p1.y);
                map[p1.x][p1.y] = 0;
                putbody(p1.x, --p1.y, 1);
                map[p1.x][p1.y] = 3;
            }
            else if (ch == '4' && judge(p2.x, p2.y - 1)) {
                p2.direct = 2;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(p2.x, --p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == 's' && judge(p1.x + 1, p1.y)) {
                p1.direct = 3;
                cleanbody(p1.x, p1.y);
                map[p1.x][p1.y] = 0;
                putbody(++p1.x, p1.y, 1);
                map[p1.x][p1.y] = 3;
            }
            else if (ch == '5' && judge(p2.x + 1, p2.y)) {
                p2.direct = 3;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(++p2.x, p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == 'd' && judge(p1.x, p1.y + 1)) {
                p1.direct = 4;
                cleanbody(p1.x, p1.y);
                map[p1.x][p1.y] = 0;
                putbody(p1.x, ++p1.y, 1);
                map[p1.x][p1.y] = 3;
            }
            else if (ch == '6' && judge(p2.x, p2.y + 1)) {
                p2.direct = 4;
                cleanbody(p2.x, p2.y);
                map[p2.x][p2.y] = 0;
                putbody(p2.x, ++p2.y, 2);
                map[p2.x][p2.y] = 3;
            }
            else if (ch == '0') {//开枪
                shoot(2);
            }
            else if (ch == ' ') {
                shoot(1);
            }
            Sleep(20);//CD为0.02s
        }
        clipmove();//子弹移动判断
        judge_hp();
    }
}

void welcome() //主界面说明书
{
    printf("操作方法：\n玩家1 wasd控制移动，空格攻击 只能往右侧打子弹\n玩家2 数字小键盘4568控制移动，0攻击 只能往左侧打子弹\n");
    Sleep(1000);
}

int main() {
    welcome();
    GetLocalTime(&sys);
    init();
    prog();
    return 0;
}