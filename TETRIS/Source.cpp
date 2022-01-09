#include <stdint.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <deque>
#include <conio.h>
using namespace std;
const int shape_size = 8;
int endline[36][60] = { 0 };
typedef int color;
typedef int shape;
struct item
{
	int x, y;//起点坐标
	color color_item;//颜色种类
	int position[shape_size];//组成形状的四个方块的坐标
	shape shape_item;//形状，0-3,四个基本形状
};
typedef item *p;
void SetConsoleColor(int x);
void print_item(const int *p, int color_choose);
void gotoxy(int x, int y);//移动鼠标位置到指定位置
class game
{
private:
	deque<p> diamonds;
	int height, length;
	bool is_new,is_end;//产生新的方块和游戏是否结束标志位
	int score;//分数统计
public:
	game(int x,int y);
	void print_map();
	void new_item();
	void run_body();
	void define_position(int *p, int x);
	void judge_direction();//判断左右方向,left or right
	bool IskeyDown(int key);//按键是否按下
	void print_body();
	void print_body_1();
	void judge_new();
	void update_endline();
	void is_gameover();
	void print_gameover();
	~game();
};
game::game(int x = 40, int y = 36) :height(x), length(y), is_new(true), is_end(true), score(0)
{
	print_map();
	while (is_end==true)
	{
		new_item();
		run_body();
		is_gameover();
	}
	print_gameover();
}
void game::run_body()
{
	char c;
	while (is_new==false)
	{
		print_body_1();
		++diamonds.back()->position[1];
		judge_direction();//判断方向
		define_position(diamonds.back()->position, diamonds.back()->shape_item);//重构造图形
		print_body();
		Sleep(150);
		judge_new();
	}
}
void game::print_map()
{
	system("mode con cols=40 lines=36");//高36，宽40的图形界面
}
void game::new_item()
{
	if (is_new)
	{
		p p1 = new item;
		p1->x = rand() % 38;
		if (p1->x % 2 == 1)
			++p1->x;
		p1->y = 0;
		p1->position[0] = p1->x; p1->position[1] = p1->y;
		p1->shape_item = rand()%4; p1->color_item = rand() % 6;
		define_position(p1->position, p1->shape_item);
		diamonds.push_back(p1);
		is_new = false;
		++score;
	}
}
void game::judge_new()
{
	for (int i = 0; i < 4; i++)
	{
		if ((diamonds.back()->position[2 * i + 1]) >= 35||
			endline[diamonds.back()->position[2 * i+1]][diamonds.back()->position[2 * i]] == 1)
		{
			update_endline();
			is_new = true; break;
		}
	}
}
void game::is_gameover()
{
	for (int i = 0; i < 35; i++)
	{
		if (endline[4][i] == 1)
		{
			is_end = false;
			break;
		}
	}
}
void game::print_body()
{
	print_item(diamonds.back()->position, diamonds.back()->color_item);
}
void game::print_body_1()
{
     print_item(diamonds.back()->position, 6);
}
void game::update_endline()
{
	for (int i = 0; i < 4; i++)
	{
		endline[diamonds.back()->position[2 * i+1]-1][diamonds.back()->position[2 * i]] = 1;
	}
}
bool game::IskeyDown(int key)
{
	return(GetAsyncKeyState(key) );
}
void game::judge_direction()
{
	if (IskeyDown(VK_LEFT))
	{
		if (diamonds.back()->position[0] >= 2)
		{
			diamonds.back()->position[0] = diamonds.back()->position[0] - 2;
		}
	}
	if (IskeyDown(VK_RIGHT))
	{
		if (diamonds.back()->position[6] <= 36)
		{
			diamonds.back()->position[0] = diamonds.back()->position[0] + 2;
		}
	}
	if (IskeyDown(VK_SPACE))//将图形旋转
	{
		switch (diamonds.back()->shape_item)
		{
		case 0:
			diamonds.back()->shape_item = 4;
			break;
		case 1:
			diamonds.back()->shape_item = 1;
			break;
		case 2:
			diamonds.back()->shape_item = 6;
			break;
		case 3:
			diamonds.back()->shape_item = 5;
			break;
		case 4:
			diamonds.back()->shape_item = 0;
			break;
		case 5:
			diamonds.back()->shape_item = 3;
			break;
		case 6:
			diamonds.back()->shape_item = 7;
			break;
		case 7:
			diamonds.back()->shape_item = 8;
			break;
		case 8:
			diamonds.back()->shape_item = 2;
			break;;
		default:
			break;
		}
	}
}
void game::print_gameover()
{
	SetConsoleColor(6);
	gotoxy(10, 6);
	cout << "                       " << endl << "                          ";
	gotoxy(10, 6);
	SetConsoleColor(3);
	cout << "游戏结束,你的分数是:"<<score<<"分";
}
game::~game()
{
}
//   颜色系统
//   0 = 黑色      8 = 灰色
//   1 = 蓝色      9 = 淡蓝色
//   2 = 绿色      A = 淡绿色
//   3 = 浅绿色    B = 淡浅绿色
//   4 = 红色      C = 淡红色
//   5 = 紫色      D = 淡紫色
//   6 = 黄色      E = 淡黄色
//   7 = 白色      F = 亮白色

enum ConsoleBackGroundColor
{
	enmCBC_Red = BACKGROUND_INTENSITY | BACKGROUND_RED,
	enmCBC_Green = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	enmCBC_Blue = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	enmCBC_Yellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	enmCBC_Purple = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	enmCBC_Cyan = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
	enmCBC_White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	enmCBC_HighWhite = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	enmCBC_Black = 0,
	//enmCBC_Black=BACKGROUND_INTENSITY | 0,
};
int main()
{
	game game1;
	getchar();
	return 0;
}
void SetConsoleColor(int x)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (x)
	{
	case 0:
		SetConsoleTextAttribute(handle, (ConsoleBackGroundColor)enmCBC_Red);
		break;
	case 1:
		SetConsoleTextAttribute(handle, (ConsoleBackGroundColor)enmCBC_Green);
		break;
	case 2:
		SetConsoleTextAttribute(handle, (ConsoleBackGroundColor)enmCBC_Blue);
		break;
	case 3:
		SetConsoleTextAttribute(handle, (ConsoleBackGroundColor)enmCBC_Yellow);
		break;
	case 4:
		SetConsoleTextAttribute(handle, (ConsoleBackGroundColor)enmCBC_Purple);
		break;
	case 5:
		SetConsoleTextAttribute(handle, (ConsoleBackGroundColor)enmCBC_Cyan);
		break;
	case 6:
		SetConsoleTextAttribute(handle, (ConsoleBackGroundColor)enmCBC_Black);
		break;
	}
}
void game::define_position(int *p,int x)
{
	switch (x)
	{
	case 0://横一
		p[3] = p[5] = p[7] = p[1];
		p[2] = p[0] + 2; p[4] = p[2] + 2; p[6] = p[4] + 2;
		break;
	case 1://田字格
		p[2] = p[0] + 2; p[3] = p[1]; p[4] = p[0]; p[5] = p[1] + 1; p[6] = p[2]; p[7] = p[5];
		break;
	case 2://L1
		p[4] = p[2] = p[0]; p[3] = p[1] + 1; p[5] = p[3] + 1; p[7] = p[5];
		p[6] = p[4] + 2;
		break;
	case 3://闪电形
		p[2] = p[0]; p[3] = p[1] + 1; p[4] = p[2]+2; p[5] = p[3]; p[6] =p[4]; p[7] =p[5]+1;
		break;
	case 4://竖1
		p[2] = p[4] = p[6] = p[0];
		p[3] = p[1] + 1; p[5] = p[3] + 1; p[7] = p[5] + 1;
		break;
	case 5://横闪电
		p[2] = p[0] + 2; p[3] = p[1]; p[4] = p[2]; p[5] = p[3] + 1; p[6] = p[4] + 2; p[7] = p[5];
		break;
	case 6:
		p[5] = p[3] = p[1]; p[7] = p[1] + 1; p[2] = p[0] - 2; p[4] = p[2] - 2; p[6] = p[4];
		break;
	case 7:
		p[2] = p[4] = p[0]; p[6] = p[4] - 2; p[3] = p[1] - 1; p[5] = p[3] - 1; p[7] = p[5];
		break;
	case 8:
		p[3] = p[5] = p[1]; p[7] = p[5] - 1; p[2] = p[0] + 2; p[4] = p[2] + 2; p[6] = p[4];
		break;
	default:
		break;
	}
	
}
void gotoxy(int x, int y)
{
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}
void print_item(const int *p, int color_choose)
{
	SetConsoleColor(color_choose);
	for (int i = 0; i < shape_size/2; i++)
	{
		gotoxy(p[2*i], p[2*i+1]);
		cout << "  ";
	}
}