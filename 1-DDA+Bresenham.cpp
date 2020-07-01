#include <stdio.h>
#include<conio.h>
#include <graphics.h>
void GetPiont();
void Bresenham();
int main()
{
	initgraph(1920, 1080);//初始化,设置分辨率
	MOUSEMSG p; //鼠标结构体
	while (true)
	{
		p = GetMouseMsg();
		if (p.uMsg == WM_LBUTTONDOWN)
			GetPiont();
	}
}

void DDA(int x0, int y0, int x1, int y1) {
	float dx, dy, x, y, len;//变量定义
	int i;
	if (abs(x1 - x0) > abs(y1 - y0))//判断以哪个作增量
		len = abs(x1 - x0);
	else
		len = abs(y1 - y0);
	dx = (x1 - x0) / len;//增量
	dy = (y1 - y0) / len;
	x = x0, y = y0;//起点
	for (i = 1; i <= len; i++) {
		putpixel(int(x + 0.5), int(y + 0.5), YELLOW);//因为没有半个像素点，所以需要强制转换为整型
		x += dx;//x+增量
		y += dy;//y+增量
	}
}

void Bresenham(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int ux = dx > 0 ? 1 : -1;//x伸展方向
	int uy = dy > 0 ? 1 : -1;//y伸展方向
	int dx2 = abs(dx) * 2;
	int dy2 = abs(dy) * 2;

	if (abs(dx) > abs(dy))//x为增量
	{
		int e = -dx; //e = -0.5 * 2 * dx,把e 用2 * dx* e替换
		int x = x0;
		int y = y0;//起点坐标x0,y0
		while (x != x1 + ux)
		{
			putpixel(x, y, WHITE);
			e += dy2;
			if (e > 0)  //e是大于0时 取上面的点 否则取下面的点(y不变)
			{
				if (y != y1)
					y += uy;
				e -= dx2;
			}
			x += ux;
		}
	}
	else//y为增量
	{
		int x = x0;
		int y = y0;//起点坐标x0,y0
		int e = -dy;
		while (y != y1 + uy)
		{
			putpixel(x, y, WHITE);
			e += dx2;
			if (e > 0)  //e是大于0时 取上面的点 否则取下面的点(x不变)
			{
				if (x != x1)
					x += ux;
				e -= dy2;
			}
			y += uy;
		}
	}
}
//获取点 实现两点确定一条直线
void  GetPiont()
{
	int x0, y0, x1, y1;
	MOUSEMSG m;        //定义结构体保存鼠标消息
	while (1)
	{
	t:
		m = GetMouseMsg();//获取一次鼠标坐标信息
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			x0 = m.x; y0 = m.y;    //鼠标第一次按下时，获取鼠标当前坐标（x0,y0）
			circle(x0, y0, 1);
			while (1)
			{
				m = GetMouseMsg();//再次获取一条鼠标坐标消息
				switch (m.uMsg)
				{
				case WM_LBUTTONDOWN:
					x1 = m.x; y1 = m.y;//鼠标第二次按下时,得到坐标（x1,y1）
					circle(x1, y1, 1);
					//Bresenham(x0, y0, x1, y1); //调用Bresenham函数
					DDA(x0, y0, x1, y1); //调用DDA函数
					goto t;//刷新
				}
			}
		}
	}
}
