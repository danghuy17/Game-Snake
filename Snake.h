#include<iostream>

extern const int X_SIZE = 50;
extern const int Y_SIZE = 26;
class Snake 
{
public:
	int size[X_SIZE][Y_SIZE];
	int point;
	int x_head, y_head;
	int x_head1, y_head1;
public:
	Snake()
	{
		point = 3;
		for (int i = 0; i < X_SIZE; ++i)
		{
			for (int j = 0; j < Y_SIZE; ++j)
			{
				size[i][j] = 0;
			}
		}
		x_head = x_head1 = X_SIZE / 2;
		y_head = y_head1 = Y_SIZE / 2;

		for (int i = 0; i < point; ++i)
		{
			size[x_head - i][y_head] = point - i;
		}
		createPoint();
	}
public:
	void move();
	bool moveRight();
	bool moveLeft();
	bool moveUp();
	bool moveDown();
public:
	void createPoint();
	bool eatPoint();
	bool endGame();
};
void Snake::createPoint()
{
	int x, y;
	do
	{
		x = rand() % (X_SIZE - 1 + 1) + 1;
		y = rand() % (Y_SIZE - 1 + 1) + 1;
	} while (size[x][y] != 0);
	size[x][y] = -1;
	size[x - 1][y] = -1;
}
bool Snake::eatPoint()
{
	if (size[x_head][y_head] == -1 || size[x_head1][y_head1] == -1)
	 { 
	 	++point; 
	 	createPoint(); 
	 	if(size[x_head + 1][y_head] == -1) size[x_head + 1][y_head1] = 0;
	 	else if (size[x_head - 1][y_head] == -1) size[x_head - 1][y_head] = 0;
	 	std::cout << char(7); return true; 
	 }
	return false;
}
bool Snake::endGame()
{
	if (eatPoint() == false) move();
	size[x_head][y_head] = point;
	size[x_head1][y_head1] = point;
	if (x_head < 0 || x_head >= X_SIZE || y_head < 0 || y_head >= Y_SIZE) return true;
	return false; 
}
void Snake::move()
{
	for (int i = 0; i < X_SIZE; ++i)
	{
		for (int j = 0; j < Y_SIZE; ++j)
		{
			if (size[i][j] > 0) -- size[i][j];
		}
	}
}
bool Snake::moveRight()
{
	++x_head;
	x_head1 = x_head;
	return endGame();
}
bool Snake::moveLeft()
{
	--x_head;
	x_head1 = x_head;
	return endGame();
}
bool Snake::moveUp()
{
	if (size[x_head - 1][y_head] != 0) x_head1 = x_head - 1;
	else if (size[x_head + 1][y_head] != 0) x_head1 = x_head + 1;
	--y_head;
	y_head1 = y_head;
	return endGame();
}
bool Snake::moveDown()
{
	if (size[x_head - 1][y_head] != 0) x_head1 = x_head - 1;
	else if (size[x_head + 1][y_head] != 0) x_head1 = x_head + 1;
	++y_head;
	y_head1 = y_head;
	return endGame();
}