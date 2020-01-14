#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;

#define Snake_max_size 50

/*Create Snake game*/
/* Class:  Map, Snake, Fruits and Player*/
/*Mehods: Setup, Generation Fruits, Draw, Input and Move*/
enum Directon{Top = 1 , Down , Right , Left};
class Map
{
public:
	int Height;
	int width;
	int FruitX;
	int FruitY;
};
class Snake
{
public:
	int HeadX;
	int HeadY;
	int Tail;
	int Tail_X[Snake_max_size];
	int Tail_Y[Snake_max_size];
	Directon Dir;
};
class Player
{
public:
	int score;
	bool lose;
};

Map map1;  Snake snake1;  Player player1;

class play
{
public:
	void Shift_Snake(int arr[], int size)
	{
		for (int i = Snake_max_size - 2; i >= 0; i--)
		{
			arr[i + 1] = arr[i];
		}
	}
	void generate_fruit()
	{
		srand(time(NULL));
		map1.FruitX = rand() % (map1.width - 2) + 1;   //from 1 to 38
		map1.FruitY = rand() % (map1.Height - 2) + 1;
	}
	void Setup()
	{
		map1.Height = 20;
		map1.width = 40;
		generate_fruit();
		//--------------------------------------------------------------
		snake1.HeadX = map1.width / 2;
		snake1.HeadY = map1.Height / 2;
		snake1.Tail = 0;
		//--------------------------------------------------------------
		player1.score = 0;
		player1.lose = false;
	}
	void Draw() 
	{
		system("cls");
		//Draw map, Snake and fruits
		for (int i = 0; i < map1.Height; i++)
		{
			for (int j = 0; j < map1.width; j++)
			{
				if (i == 0 || i == (map1.Height - 1) || j == 0 || j == (map1.width - 1))
				{
					cout << "#";
				}
				else if (i == snake1.HeadY && j == snake1.HeadX)
				{
					cout << "O";
				}
				else if (i == map1.FruitY && j == map1.FruitX)
				{
					cout << "$";
				}
				else
				{
					bool printed = false;
					for (int z = 0; z < snake1.Tail; z++)
					{
						if (snake1.Tail_X[z] == j && snake1.Tail_Y[z] == i)
						{
							cout << "o";
							printed = true;
							break;
						}
					}
					if (!printed)
					{
						cout << " ";
					}
				}
			}
			cout << endl;
		}
		cout << "Player Score : " << player1.score;
	}
	void Input()
	{
		if (_kbhit())
		{
			char c = _getch();
			switch (c)
			{
			case 'w':
				snake1.Dir = Top;
				break;
			case 's':
				snake1.Dir = Down;
				break;
			case 'a':
				snake1.Dir = Left;
				break;
			case 'd':
				snake1.Dir = Right;
				break;
			case 'x':
				exit(0);
			}
		}
	}
	void Move()
	{
		Shift_Snake(snake1.Tail_X, Snake_max_size);
		Shift_Snake(snake1.Tail_Y, Snake_max_size);
		snake1.Tail_X[0] = snake1.HeadX;
		snake1.Tail_Y[0] = snake1.HeadY;
		switch (snake1.Dir)
		{
		case Top:
			snake1.HeadY--;
			break;
		case Down:
			snake1.HeadY++;
			break;
		case Right:
			snake1.HeadX++;
			break;
		case Left:
			snake1.HeadX--;
			break;
		}
		if (snake1.HeadX >= map1.width || snake1.HeadX <= 0 || snake1.HeadY >= map1.Height || snake1.HeadY <= 0)
		{
			player1.lose = true;
		}
		else if (snake1.HeadX == map1.FruitX && snake1.HeadY == map1.FruitY)
		{
			generate_fruit();
			player1.score++;
			snake1.Tail++;
		}
		for (int k = 0; k < snake1.Tail; k++)
		{
			if(snake1.HeadX == snake1.Tail_X[k] && snake1.HeadY == snake1.Tail_Y[k] && snake1.Tail != 0)
				player1.lose = true;
		}

		string m = (!player1.lose) ? "Well, Continue" : "you lose";
		cout << " ==> Status : " << m << endl;
	}
};


int main(void)
{
	play kero;
	kero.Setup();
	while (!player1.lose)
	{
		kero.Draw();
		kero.Input();
		kero.Move();
		Sleep(10);
	}
	system("pause");
	return 0;
}