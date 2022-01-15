#include<iostream>
#include<deque>
#include<algorithm>
#include<Windows.h>
#include<math.h>
#include<conio.h>
using namespace std;
int endtime = 1000;
struct snake
{
	char imagine;
	int x, y;
};
class snakegame{
public:
	snakegame();
	void gotoxy(int x, int y);//�������λ��
	void HideCursor() //���ع��
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
		CursorInfo.bVisible = false; //���ؿ���̨���
		SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
	}
	void printmap();//��ʼ����ͼ
	void init_body();//��ʼ������
	void print_body();//��ӡ����
	void print_food();//�������ʳ���֤���������غ�
	bool ifeat();//�ж��Ƿ�Ե�ʳ��
	void get_direction();//�ж�ǰ�����򣬸ı�ǰ������
	bool IsKeyDown(int x);
	bool gameover();//��Ϸ�����ж�
	void print_gameover();//��ӡ��Ϸ��������
	void begingame();
	void endgame();
private:
	int height, length;
	deque<snake> body;
	deque<snake>::iterator iterator1;
	snake food;
	bool eat;//�ж��Ƿ�Ե�ʳ�1��ʾ�Ե���0��ʾδ�Ե�
	bool trash;//��־λ���ж���Ϸ�Ƿ����
	char dir;
	int score;
};
snakegame::snakegame() :height(40), length(160), score(0), trash(false), dir('d')
{
	while (!trash)
	{
		begingame();
		endgame();
	}
}
void snakegame::begingame()
{
	printmap();
	print_food();
	while (1)
	{
		HideCursor();
		deque<snake>::iterator  head = body.begin();//head��ͷָ��
		snake tail = body.back();//tail��β��������
		head->imagine = '+';
		get_direction();
		if (dir == 'w'){
			body.push_front({ '@', head->x, head->y - 1 });
		}
		else if (dir == 'a'){
			body.push_front({ '@', head->x - 1, head->y });
		}
		else if (dir == 's'){
			body.push_front({ '@', head->x, head->y + 1 });
		}
		else
		{
			body.push_front({ '@', head->x + 1, head->y });
		}
		gotoxy(tail.x, tail.y); cout << ' ';
		body.pop_back();
		if (ifeat())
		{
			print_food();
			body.push_back(tail);
			score += 1;
			endtime -= 100;
		}//����Ե���ʳ������´�ӡʳ��
		//for (int i = 0; i < endtime; i++)//������ʱ��������Ļ��˸,�ٶȹ���
		Sleep(100);
		print_body();
		trash = gameover();
		if (trash){ break; }
	}
}
void snakegame::endgame()
{
	print_gameover();
	char tmp;
	switch (tmp = _getch())
	{
	case 'b':{trash = false; break; }
	default:break;
	}
}
void snakegame::init_body()
{
	if (!body.empty()){ body.clear(); }
	body.push_front({ '@', length / 2, height / 2 });
	for (int i = 0; i < 4; i++)
	{
		body.push_back({ '+', length / 2 - i - 1, height / 2 });
	}
	print_body();
}
void snakegame::print_body()
{
	deque<snake>::iterator s1;
	s1 = body.begin();
	for (; s1 != body.end(); s1++){
		gotoxy(s1->x, s1->y);
		cout << s1->imagine;
	}
}
bool snakegame::ifeat()
{
	if ((food.x == body.front().x) && (food.y == body.front().y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void snakegame::print_food()
{
	bool tag = 1;
	food.imagine = '*';
	while (tag == 1)
	{
		tag = 0;
		food.x = rand() % (length-2 - 2) + 2;
		for (iterator1 = body.begin(); iterator1 != body.end(); ++iterator1)
		{
			if (food.x == iterator1->x){ tag = 1; break; }
		}
	}
	tag = 1;
	while (tag == 1)
	{
		tag = 0;
		food.y = rand() % (height-2 - 2) + 2;
		for (iterator1 = body.begin(); iterator1 != body.end(); ++iterator1)
		{
			if (food.y == iterator1->y){ tag = 1; break; }
		}
	}
	gotoxy(food.x, food.y);
	cout << food.imagine;
}
void snakegame::printmap()
{
	system("mode con cols=160 lines=40");
	gotoxy(0, 0);
	for (int i = 0; i < length/2; i++)
	{
		cout << "��";
	}
	gotoxy(0, height-1);
	for (int i = 0; i < length / 2; i++)
	{
		cout << "��";
	}
	gotoxy(0, 1);
	for (int i = 0; i < height-2; i++)
	{
		cout<< "��"<<endl;
	}
	for (int i = 0; i < height-2; i++)
	{
		gotoxy(length - 2, i+1);
		cout << "��";
	}
	init_body();
}
bool snakegame::IsKeyDown(int x)
{
	return(GetAsyncKeyState(x));
}
void snakegame::get_direction()
{
	if (IsKeyDown(VK_LEFT))
	{
		if (dir!='d')
		{
			dir='a';
		}
	}
	if (IsKeyDown(VK_RIGHT))
	{
		if (dir!='a')
		{
			dir='d';
		}
	}
	if (IsKeyDown(VK_DOWN))
	{
		if (dir != 'w')
		{
			dir = 's';
		}
	}
	if (IsKeyDown(VK_UP))
	{
		if (dir != 's')
		{
			dir = 'w';
		}
	}
}
void snakegame::gotoxy(int x, int y)
{
	HANDLE hout;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}
bool snakegame::gameover()
{
	if ((body.front().x > length - 6) || (body.front().x < 6) || (body.front().y > height - 2) || (body.front().y < 2))
	{
		return true;
	}
	snake tmp = body.front();
	for (iterator1 = body.begin()+1; iterator1 != body.end(); ++iterator1)
	{
		if (iterator1->x == tmp.x&&iterator1->y == tmp.y){ return true; }
	}
	return false;
}
void snakegame::print_gameover()
{
	gotoxy(length / 2-10, height / 2-4);
	cout << "��Ϸ����" << endl;
	gotoxy(length / 2-10, height / 2-2);
	cout << "��ķ����ǣ�" << score;
	gotoxy(length / 2 - 10, height / 2);
	cout << "��b�����¿�ʼ������������˳���Ϸ";
	system("pause");
}
int main()
{
	snakegame game1;
	return 0;
}