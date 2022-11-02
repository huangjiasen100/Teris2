#include<iostream>
#include<string>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<cstdio>
using namespace std;

class Tetris
{
private:
    int rank;        //��Ϸ�Ѷȵȼ�
    int score;        // �÷�
    int id;          //ͼ��ID
    int point[2];      //������
    int top;          //��ߵ�߶�
public:
    Tetris();
    void Welocme();      //�׽���
    void DrawMap();      //��Ϸ����
    void SetColor(int);    //������ɫ
    void Draw(int, int, int);    //��ͼ��
    void Run();        //������Ϸ
    void ReDraw(int, int, int);      //���ͼ��
    bool Judge(int, int, int);
    void Turn(int);        //��ת
    void Updata();        // ���½���
    void Pause();        //��Ϸ��ͣ
    void Input_score();
};

// |0,0|0,1|0,2|0,3|
// |1,0|1,1|1,2|1,3|
// |2,0|2,1|2,2|2,3|
// |3,0|3,1|3,2|3,3|
const int sharp[15][8] =          //���ͼ�εĸ�����ĸ������꣬���ݺ��
{
    {0,0, 1,0, 2,0, 3,0}, // I              1
    {0,0, 0,1, 0,2, 0,3}, // ----           4
    {0,0, 1,0, 0,1, 1,1}, // ��              2
    {0,0, 1,0, 1,1, 1,2}, // ˮƽL       3
    {0,1, 1,1, 2,0, 2,1}, // ��ֱL       2
    {0,0, 0,1, 0,2, 1,2}, //ˮƽL        3                                             
    {0,0, 0,1, 1,0, 2,0}, //��ֱL        2
    {1,0, 1,1, 1,2, 0,2}, //ˮƽL        3
    {0,0, 0,1, 1,1, 2,1}, //��ֱL        2
    {0,0, 0,1, 0,2, 1,0}, //ˮƽL        3
    {0,0, 1,0, 2,0, 2,1}, //��ֱL        2
    {0,0, 0,1, 1,1, 1,2}, //ˮƽZ        3
    {0,1, 1,0, 1,1, 2,0}, //��ֱZ        2
    {0,1, 0,2, 1,0, 1,1}, //ˮƽZ        3
    {0,0, 1,0, 1,1, 2,1}  //��ֱZ        2
};
const int sharp_width[15] = {
    1,  // I              1
    4,  // ----           4
    2,  // ��              2
    3,  // ˮƽL       3
    2,  // ��ֱL       2
    3,  //ˮƽL        3  
    2,  //��ֱL        2
    3,  //ˮƽL        3
    2,  //��ֱL        2
    3,  //ˮƽL        3
    2,  //��ֱL        2
    3,  //ˮƽZ        3
    2,  //��ֱZ        2
    3,  //ˮƽZ        3
    2   //��ֱZ        2
};

//const int sharp[15][8] =          //���ͼ�εĸ�����ĸ������꣬���ݺ��
//{
//{0,0,1,0,2,0,3,0},{0,0,0,1,0,2,0,3},
//{0,0,1,0,0,1,1,1},
//{0,0,1,0,1,1,1,2},{0,1,1,1,2,0,2,1},{0,0,0,1,0,2,1,2},{0,0,0,1,1,0,2,0},
//{1,0,1,1,1,2,0,2},{0,0,0,1,1,1,2,1},{0,0,0,1,0,2,1,0},{0,0,1,0,2,0,2,1},
//{0,0,0,1,1,1,1,2},{0,1,1,0,1,1,2,0},
//{0,1,0,2,1,0,1,1},{0,0,1,0,1,1,2,1}
//};

const int high[15] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3 };
int map[28][16];

#define a1  0      //����
#define a2  1
#define b 2          // ����

#define c1 3          //L��
#define c2 4
#define c3 5
#define c4 6

#define d1 7          //T��
#define d2 8 
#define d3 9
#define d4 10

#define e1 11        //����1��
#define e2 12

#define f1 13        //����2��
#define f2 14

Tetris::Tetris()        //���캯���� ��ʼ������ֵ
{
    point[0] = 0;
    point[1] = 5;
    score = 0;
    top = 25;
}

void Tetris::Turn(int num)        //��ת����
{
    switch (num)
    {
    case a1: id = a2; break;          //���λ���
    case a2: id = a1; break;

    case b: id = b; break;          //�����޷���ת

    case c1: id = c2; break;          //����L�λ���
    case c2: id = c3; break;
    case c3: id = c4; break;
    case c4: id = c1; break;

    case d1: id = d2; break;          //����T�λ���
    case d2: id = d3; break;
    case d3: id = d4; break;
    case d4: id = d1; break;

    case e1: id = e2; break;          //���������λ���
    case e2: id = e1; break;

    case f1: id = f2; break;
    case f2: id = f1; break;
    }
}

void SetPos(int i, int j)      //���ƹ��λ�ã� �У� ��
{
    COORD pos = { i,j };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Tetris::Pause()        // ��ͣ����
{
    SetPos(32, 10);
    cout << "��Ϸ��ͣ!" << endl;
    SetPos(30, 11);
    cout << "��ķ���Ϊ " << score;
    char temp;
    while (1)
    {
        while (1)
        {
            if (_kbhit())
            {
                temp = _getch();
                break;
            }
        }
        if (temp == 32)
            break;
    }
    SetPos(32, 10);          // �����ͣʱ��ʾ����Ϣ
    cout << "         ";
    SetPos(30, 11);
    cout << "              ";
}

void Tetris::Updata()          //���º���
{
    int i, flag;
    int nx, ny;
    for (i = 0; i < 4; i++)
    {
        nx = point[0] + sharp[id][i * 2];
        ny = point[1] + sharp[id][i * 2 + 1];
        SetPos((ny + 1) * 2, nx + 1);
        SetColor(0);
        cout << "��";
        map[nx][ny] = 1;          //����������Ƿ�Ϊ�յĸ���
    }

    if (point[0] < top)
        top = point[0];          //��ߵ�ĸ���

    for (i = point[0]; i < point[0] + high[id]; i++)      //������
    {
        flag = 1;
        for (int j = 0; j < 13; j++)          //�ж�ĳһ���Ƿ����� ��flag�����
            if (map[i][j] == 0)
                flag = 0;
        if (flag == 1)
        {
            for (int k = i; k >= top; k--)
            {
                for (int p = 0; p < 13; p++)
                {
                    map[k][p] = map[k - 1][p];
                    SetPos((p + 1) * 2, k + 1);
                    if (map[k][p] == 1)
                        cout << "��";
                    else cout << " ";

                }
            }
            score += 10;
            Input_score();
        }
    }
}

void Tetris::Input_score()
{
    SetColor(3);
    SetPos(30, 19);
    cout << "�÷�: " << score;
}

void Tetris::Welocme()      //��ӭ����
{
    SetColor(1);
    char x;
    while (1)
    {
        system("cls");
        cout << "������������������������������������������" << endl;
        cout << "    ����˹����    " << endl;
        cout << "������������������������������������������" << endl;
        cout << "    ������ʽ��" << endl;
        cout << "    �� - ��ת" << endl;
        cout << "    �� - ��������" << endl;
        cout << "    �� - ����" << endl;
        cout << "    �� - ����" << endl;
        cout << "    �ո� - ��ͣ" << endl;
        cout << "������������������������������������������" << endl;
        cout << "�� ��1��3ѡ���Ѷȡ�" << endl;
        SetPos(20, 10);
        x = getchar();
        if (x <= '9' && x >= '0')
        {
            rank = x - '0';
            break;
        }
    }
}

void Tetris::SetColor(int color_num)      //������ɫ
{
    int n;
    switch (color_num)
    {
    case 0: n = 0x08; break;
    case 1: n = 0x0C; break;
    case 2: n = 0x0D; break;
    case 3: n = 0x0E; break;
    case 4: n = 0x0A; break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}

void Tetris::DrawMap()        //����Ϸʱ����
{
    int i;
    SetColor(0);

    for (i = 0; i < 24; i++)    //��24��
    {
        SetPos(i * 2, 0);
        cout << "��";
        SetPos(i * 2, 26);
        cout << "��";
    }

    for (i = 0; i < 26; i++)    //��26��
    {
        SetPos(0, i);
        cout << "��";
        SetPos(28, i);
        cout << "��";
        SetPos(46, i);
        cout << "��";
    }

    for (i = 14; i < 24; i++)
    {
        SetPos(i * 2, 16);
        cout << "��";
    }

    SetColor(3);
    Input_score();
    SetPos(30, 21); // 30: �к�
    cout << "�Ѷȵȼ�: " << rank;
    SetPos(32, 2);
    cout << "��һͼ��";
}

void Tetris::Draw(int x, int y, int num)        //��ͼ��
{
    int nx, ny;

    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        SetPos((ny + 1) * 2, nx + 1);
        SetColor(i + 1);
        cout << "��";
    }
}

void Tetris::ReDraw(int x, int y, int num)        //Ϊ����ͼ�ε�λ�����ͼ��
{
    int nx, ny;

    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        SetPos((ny + 1) * 2, nx + 1);

        //cout << " ";
        // [BugFix] HJS
        cout << "  ";
    }
}

bool Tetris::Judge(int x, int y, int num)        //�ж���x, y ��ָλ���Ƿ�ɻ����Ϊ
{                          //num ��ͼ�Σ� �����ɻ��򷴻�true
    int nx, ny;
    for (int i = 0; i < 4; i++)
    {
        nx = x + sharp[num][2 * i];
        ny = y + sharp[num][2 * i + 1];
        if (!(nx < 25 && nx >= 0 && ny < 13 && ny >= 0 && !map[nx][ny]))
            return true;
    }
    return false;
}

void Tetris::Run()          //������Ϸ
{
    int next_id;
    srand((int)time(0));

    id = rand() % 15;
    next_id = rand() % 15;

    Draw(point[0], point[1], id);
    Draw(5, 16, next_id);

    int count;
    if (rank == 1)
        count = 150;
    else if (rank == 2)
        count = 100;
    else if (rank == 3)
        count = 50;
    else
        count = 5;
    int i = 0;  //��ͬ�ȼ���Ӧ��ͬcount

    while (1)
    {
        if (!(i < count))        //i �� count ���ڿ���ʱ��
        {
            i = 0;
            if (Judge(point[0] + 1, point[1], id))      //��ĳһλ�ò�������Ļ�
            {
                Updata();
                id = next_id;

                ReDraw(5, 16, next_id);
                next_id = rand() % 15;

                point[0] = 0; point[1] = 5;
                Draw(point[0], point[1], id);
                Draw(5, 16, next_id);

                if (Judge(point[0], point[1], id))
                {
                    system("cls");
                    SetPos(20, 10);
                    cout << "��Ϸ������" << endl;
                    SetPos(20, 11);
                    cout << "��ķ���Ϊ " << score << endl;
                    system("pause");
                    exit(1);
                }
            }
            else          //��������
            {
                ReDraw(point[0], point[1], id);
                point[0]++;
                Draw(point[0], point[1], id);
            }
        }

        if (_kbhit())        //��������ֵʱ 
        {
            int key, key2;
            key = _getch();
            if (key == 224)
            {
                key2 = _getch();

                if (key2 == 72)      //�����Ϸ����ʱ
                {
                    int temp = id;
                    Turn(id);
                    if (Judge(point[0], point[1], id))
                        id = temp;
                    ReDraw(point[0], point[1], temp);
                    Draw(point[0], point[1], id);
                }
                if (key2 == 80)        //�����·����ʱ
                {
                    if (!Judge(point[0] + 2, point[1], id))
                    {
                        ReDraw(point[0], point[1], id);
                        point[0] += 2;
                        Draw(point[0], point[1], id);
                    }
                }
                else if (key2 == 75)        //���������ʱ
                {
                    if (!Judge(point[0], point[1] - 1, id))
                    {
                        ReDraw(point[0], point[1], id);
                        point[1]--;
                        Draw(point[0], point[1], id);
                    }
                }
                else if (key2 == 77)          //�����ҷ����ʱ
                {
                    if (!Judge(point[0], point[1] + 1, id))
                    {
                        ReDraw(point[0], point[1], id);
                        point[1]++;
                        Draw(point[0], point[1], id);
                    }
                }
            }
            else if (key == 32)          // ���¿ո���ͣ
                Pause();
        }

        Sleep(1);    //�ȴ�1����
        i++;        //����������
    }
}

int main()
{
    Tetris game;
    game.Welocme();
    system("cls");        //�����ӭ����
    game.DrawMap();

    game.Run();
}