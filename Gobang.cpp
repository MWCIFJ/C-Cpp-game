#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

const int N = 15;//棋盘大小
const char ChessBoardFlag = ' '; //棋盘标志
const char flag1 = 'O'; //1号棋子
const char flag2 = 'X'; //2号棋子

typedef struct Coordinate  //坐标
{
    int x;  //行
    int y;  //列
}ChessCoordi;

class FiveChess
{
public:
    FiveChess()
    {
        InitChessBoard();   //初始化棋盘
    }

    void Play()
    {
        ChessCoordi Pos1;   //1号棋子坐标
        ChessCoordi Pos2;   //2号棋子坐标
        while (TRUE) {
            int mode = ChoseMode();
            while (TRUE) {
                if (mode == 1) {//玩家 VS CPU
                    static size_t count = 1;
                    PalyerGo(Pos1, 1, flag1);//玩家走棋
                    if (count++ >= 9 && GetWiner(Pos1, 1, flag1))
                        break;
                    ComputerGo(Pos2, flag2);//CPU走棋
                    if (count++ >= 10 && GetWiner(Pos2, 0, flag2))
                        break;
                }
                else if (mode == 2) {//玩家 VS 玩家
                    static size_t count = 1;
                    PalyerGo(Pos1, 1, flag1);
                    if (count++ >= 9 && GetWiner(Pos1, 1, flag1))
                        break;
                    PalyerGo(Pos2, 2, flag2);
                    if (count++ >= 10 && GetWiner(Pos2, 2, flag2))
                        break;
                }
            }
            cout << "再来一局 y or no" << endl;
            char chose = 'y';
            cin >> chose;
            if (chose == 'n')
                break;
        }
    }

    void PrintChessBoard()  //构建棋盘框架
    {
        system("cls");
        for (size_t i = 0; i < N + 1; ++i)
        {
            for (size_t j = 0; j < N + 1; ++j)
            {
                if (i == 0) {
                     if (j == 0)
                        printf("   ");
                    else if(j>9)
                        printf("%d  ",j);
                    else
                        printf("%d   ", j);//这是横向的数字标记
                }
                else if (j == 0) {
                    if (i != 0)
                        printf("%2d", i);//这是纵向的数字标记
                }
                else {
                    printf("%c  |", ChessBoard[i][j]);//纵向的框架
                }

            }
            cout << endl;
            cout << "  ";//纵向的数字标记要用“ ”来隔开，以此达到视觉上的对位
            for (size_t i = 1; i < N + 1; ++i) {
                cout << "---+";//横向的框架
            }
            cout << endl;
        }
    }

    void InitChessBoard()//初始化棋盘
    {
        for (size_t i = 0; i < N + 1; ++i) 
            for (size_t j = 0; j < N + 1; ++j) 
                ChessBoard[i][j] = ChessBoardFlag;//棋盘的落子点全部初始化为“ ”
    }

protected:

    int ChoseMode()//选择模式
    {
        system("cls");
        InitChessBoard();
        cout << "请选择 1.玩家VS电脑 2.玩家VS玩家 3.退出" << endl;
        int chose = 0;
        cin >> chose;
        while (TRUE) {
            if (chose == 1)
                return chose;
            else if (chose == 2)
                return chose;
            else if (chose == 3)
                exit(1);
            else
                cout << "对不起，您的输入有误。。" << endl;
        }
    }

    void PalyerGo(ChessCoordi& Pos, int player, char flag)//玩家落子
    {
        PrintChessBoard();
        int x = 0;
        int y = 0;
        while (TRUE) {
            cout << "请玩家" << player << "下一步棋" << endl;
            cin >> Pos.x >> Pos.y;
            if (JudgePos(Pos))//判断下棋时是否符合规则
                break;
            else
                cout << "玩家输入错误! 请重新输入" << endl;
        }
        ChessBoard[Pos.x][Pos.y] = flag;//执行落子
    }

    void ComputerGo(ChessCoordi& Pos, char flag)//CPU落子
    {
        PrintChessBoard();
        int x = 0;
        int y = 0;
        while (TRUE) {
            x = rand() % N + 1;//傻瓜的随机
            srand((unsigned int)time(NULL));
            y = rand() % N + 1;//傻瓜的随机
            srand((unsigned int)time(NULL));//这种方式下生成的x，y一定在棋盘上
            if (ChessBoard[x][y] == ChessBoardFlag)
                break;
        }
        Pos.x = x;
        Pos.y = y;
        ChessBoard[Pos.x][Pos.y] = flag;
    }

    int GetVictory(ChessCoordi Pos, char flag)//判断是否有赢家
    {
        int begin = 0;//在检查对角线时 作为【行】坐标的开始 结束
        int end = 0;
        //检查【行】是否连续5个子
        int beginl = 0;//在检查对角线时 作为【列】坐标的开始 结束
        int endl = 0;
        (Pos.y - 4) > 0 ? begin = Pos.y - 4 : begin = 1;//上边框的begin与end判断
        (Pos.y + 4) < N ? end = Pos.y + 4 : end = N;    //下边框的begin与end判断
        for (size_t i = Pos.x, j = begin; j + 4 <= end; ++j)//j管行
        {
            if (   flag == ChessBoard[i][j] 
                && flag == ChessBoard[i][j + 1] 
                && flag == ChessBoard[i][j + 2] 
                && flag == ChessBoard[i][j + 3] 
                && flag == ChessBoard[i][j + 4])//连续五个排成一行
                return 1;
        }
        //检查【列】是否连续5个子
        (Pos.x - 4) > 0 ? begin = Pos.x - 4 : begin = 1;//左边框的begin与end判断
        (Pos.x + 4) > N ? end = Pos.x + 4 : end = N;    //右边框的begin与end判断
        for (size_t j = Pos.y, i = begin; i + 4 <= end; ++i)//i管列
        {
            if (flag == ChessBoard[i][j]
                && flag == ChessBoard[i + 1][j]
                && flag == ChessBoard[i + 2][j] 
                && flag == ChessBoard[i + 3][j] 
                && flag == ChessBoard[i + 4][j])//连续五个排成一列
                return 1;
        }

        int len = 0;
        //检查主对角线是否满五个子（左上-右下）
        (Pos.x > Pos.y) ? len = Pos.y - 1 : len = Pos.x - 1;
        if (len > 4)//找落子点到上 左两边的垂直距离较短的地方 如果其大于4 取4 不大于4 取其本身
            len = 4;//因为[i+4]-[i]才是五个棋子，[j]同理
        begin = Pos.x - len;    //向上移动适当距离找可能的五连子的起始位置
        beginl = Pos.y - len;   //向左移动适当距离找可能的五连子的起始位置
        (Pos.x > Pos.y) ? len = N - Pos.x : len = N - Pos.y;
        if (len > 4)
            len = 4;
        end = Pos.x + len;      //向下移动适当距离找可能的五连子的起始位置
        endl = Pos.y + len;     //向右移动适当距离找可能的五连子的起始位置
        for (size_t i = begin, j = beginl; i + 4 <= end && j + 4 <= endl; ++i, ++j)
        {
            if (   flag == ChessBoard[i][j] 
                && flag == ChessBoard[i + 1][j + 1] 
                && flag == ChessBoard[i + 2][j + 2] 
                && flag == ChessBoard[i + 3][j + 3] 
                && flag == ChessBoard[i + 4][j + 4])
                return 1;
        }
        //检查副对角线是否满五个子（右上-左下）
        (Pos.x - 1 > N - Pos.y) ? len = N - Pos.y : Pos.x - 1;
        if (len > 4)//找落子点到右 下两边的垂直距离较短的地方 如果其大于4 取4 不大于4 取其本身
            len = 4;
        begin = Pos.x - len;//向上 右移动适当距离找可能的五连子的起始位置
        beginl = Pos.y + len;
        (N - Pos.x > Pos.y - 1) ? len = Pos.y - 1 : len = N - Pos.x;
        end = Pos.x + len;//向下 左移动适当距离找可能的五连子的最终位置
        endl = Pos.y - len;
        for (size_t i = begin, j = beginl; i + 4 <= end && j - 4 >= endl; ++i, ++j)
        {
            if (   flag == ChessBoard[i][j] 
                && flag == ChessBoard[i + 1][j - 1] 
                && flag == ChessBoard[i + 2][j - 2] 
                && flag == ChessBoard[i + 3][j - 3] 
                && flag == ChessBoard[i + 4][j - 4])
                return 1;
        }
        //检查棋盘是否已满
        for (size_t i = 1; i < N + 1; ++i) 
            for (size_t j = 1; j < N + 1; ++j) 
                if (ChessBoard[i][j] == ChessBoardFlag)
                    return 0;//表示棋盘没满
        //和棋
        return -1;
    }

    bool GetWiner(ChessCoordi& Pos, int player, char flag)//判断是谁赢了
    {
        int n = 0;
        n = GetVictory(Pos, flag);
        PrintChessBoard();
        if (1 == n) {
            if (0 == player)
                cout << "玩家1获胜" << endl;
            else if (1 == player)
                cout << "玩家2获胜" << endl;
            else
                cout << "电脑获胜" << endl;
            return true;
        }
        else if (-1 == n) {
            cout << "和棋" << endl;
            return true;
        }
        else  //还未分出胜负
            return false;
    }

    bool JudgePos(const ChessCoordi& Pos)//判断是否落子正确
    {
        if (   Pos.x < N + 1 //在右边框内
            && Pos.x > 0     //在左边框内
            && Pos.y < N + 1 //在下边框内
            && Pos.y > 0
            && ChessBoard[Pos.x][Pos.y] == ChessBoardFlag)//这里还是" ",没被下过
            return true;

        return false;
    }

private:
    char ChessBoard[N + 1][N + 1];
};

//#include"FiveChess.cpp"
int main()
{
    //char a[] = "exit";
    //for (size_t i = 0; i < sizeof(a) / sizeof(char);++i)
    //printf(":%d", a[i]);
    FiveChess a;
    a.InitChessBoard();
    a.PrintChessBoard();
    a.Play();
    system("pause");
    return 0;
}