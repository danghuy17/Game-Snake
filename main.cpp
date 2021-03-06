#include<iostream>
#include<conio.h>
#include<Windows.h>
#include "Snake.h"


#define X0		1
#define Y0		1

enum MOVE { LEFT = 'a', UP = 'w', RIGHT = 'd', DOWN = 's' };
enum SPEED { ONE = 10, TWO = 20, THREE = 30, FOUR = 50, FIVE = 100 };
void disableResizeWindow()
{
	HWND hWnd  = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void setConsoleWindowSize(SHORT width, SHORT height)
{
	SMALL_RECT windowSize;
	windowSize.Top = 0;
	windowSize.Left = 0;
	windowSize.Right = width;
	windowSize.Bottom = height;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
}
void setCursor(int x = X0, int y = Y0)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void showCursor(bool show = false)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = show;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void setColor(int background, int text)
{
	int color = background * 16 + text;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void print(const Snake& s)
{
	setColor(7, 1);
	setCursor(X_SIZE + 4, Y_SIZE / 2);
	std::cout << "POINTS: " << s.point;
	for (int i = 0; i < Y_SIZE; ++i)
	{
		setCursor(X0, Y0 + i);
		for (int j = 0; j < X_SIZE; ++j)
		{
			if (s.size[j][i] > 0) 
			{
				setColor(1, 0);
				std::cout << ' ';
			}
			else if (s.size[j][i] == 0) 
			{
				setColor(15, 0);
				std::cout << ' ';
			}
			else 
			{
				setColor(4, 0);
				std::cout << ' ';
			}
		}
	}
}

void startGame(int speed = 50)
{
	Snake s;
	bool b = false;
	int m = RIGHT;
	int c;
	while (true)
	{
		print(s);
		Sleep(speed);
		if (m == RIGHT)
		{
			b = s.moveRight();
		}
		else if (m == LEFT)
		{
			b = s.moveLeft();
		}
		else if (m == UP)
		{
			b = s.moveUp();
		}
		else if (m == DOWN)
		{
			b = s.moveDown();
		}
		if (b == true) break;
		if (_kbhit())
		{
			c = getch();
			m = c;
		}
	}
}
void printInline(int left, int middle, int right)
{
	setColor(6, 0);
	std::cout << char(left);
	for (int i = 0; i < X_SIZE; ++i)
	{
		std::cout << char(middle);
	}
	std::cout << char(right);
}
void showScreen()
{
	setCursor(X0 - 1, Y0 - 1); printInline(201, 205, 187);
	for (int i = 0; i < Y_SIZE; ++i)
	{
		setCursor(X0 - 1, Y0 + i); printInline(186, ' ', 186);
	}
	setCursor(X0 - 1, Y0 + Y_SIZE); printInline(200, 205, 188);
}
int main()
{
	int n = 10, speed = 50;
	setConsoleWindowSize(X_SIZE + 20, Y_SIZE + 1);
	disableResizeWindow();
	while (n < 1 ||n > 5)
	{
		std::cout << "ENTER SPEED(1-2-3-4-5): "; std::cin >> n;
	}
	if (n == 1) speed = ONE;
	else if (n == 2) speed = TWO;
	else if (n == 3) speed = THREE;
	else if (n == 4) speed = FOUR;
	else if (n == 5) speed = FIVE;
	setConsoleWindowSize(X_SIZE + 20, Y_SIZE + 1);
	disableResizeWindow();
	showCursor();
	showScreen();
	startGame(speed);
	getch();
}