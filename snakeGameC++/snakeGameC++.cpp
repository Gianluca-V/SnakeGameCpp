#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime> 
using namespace std;

bool GameOver;
const int WIDTH = 85;
const int HEIGHT = 20;
int PlayerX, PlayerY, PlayerZ, FruitX, FruitY, Score;
int TailX[100], TailY[100];
int NTails;
enum EDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
EDirection Dir;



void Setup()
{
	system("color 7");
	system("cls");
	srand(time(NULL));
	GameOver = false;
	Dir = STOP;
	PlayerX = 45;
	PlayerY = (HEIGHT / 2);
	FruitX = rand() % WIDTH;
	FruitY = rand() % HEIGHT;
	Score = 0;
	NTails = 0;
}

void Draw()
{
	system("color 7");
	system("cls");                 //reset screen
	system("color 7");

	cout << "SCORE: " << Score << endl;
	for (int i = 0; i < WIDTH + 2; i++)                 //print the top border
	{
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < HEIGHT; i++)                //print the left and right borders
	{
		for (int j = 0; j <= WIDTH; j++)
		{
			if (j == 0 || j == WIDTH)
			{
				cout << "#";
			}
			if (j == PlayerX && i == PlayerY)
			{
				cout << "@";
			}
			else if (j == FruitX && i == FruitY)
			{
				cout << "F";
			}
			else
			{
				bool printed = false;
				for (int t = 0; t < NTails; t++)
				{
					if (j == TailX[t] && i == TailY[t])
					{
						cout << "o";
						printed = true;
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

	for (int i = 0; i < WIDTH + 2; i++)                 //print the botom border
	{
		cout << "#";
	}

	cout << endl;

}

void Input()
{
	cout << endl;
	if (_kbhit())		//get the player input and change direction
	{
		switch (_getch())
		{
		case 'w':
			Dir = UP;
			break;

		case 'a':
			Dir = LEFT;
			break;

		case 's':
			Dir = DOWN;
			break;

		case 'd':
			Dir = RIGHT;
			break;

		case 'x':
			GameOver = true;
			Dir = STOP;
			break;

		default:
			break;
		}
	}


}
void Logic()
{

	int PlayerPreX = TailX[0];
	int PlayerPreY = TailY[0];
	int PlayerPreX2, PlayerPreY2;
	TailX[0] = PlayerX;
	TailY[0] = PlayerY;
	for (int i = 1; i < NTails; i++)		//update the snake coords
	{
		PlayerPreX2 = TailX[i];
		PlayerPreY2 = TailY[i];
		TailX[i] = PlayerPreX;
		TailY[i] = PlayerPreY;
		PlayerPreX = PlayerPreX2;
		PlayerPreY = PlayerPreY2;
	}

	switch (Dir)				//change snake coords
	{
	case LEFT:
		PlayerX--;
		break;
	case RIGHT:
		PlayerX++;
		break;
	case UP:
		PlayerY--;
		break;
	case DOWN:
		PlayerY++;
		break;

	default:
		break;
	}


	if (PlayerX < 0 || PlayerX > WIDTH)			//constrols gameover logic
	{
		GameOver = true;
		Dir = STOP;
	}
	if (PlayerY < 0 || PlayerY > HEIGHT - 1)
	{
		GameOver = true;
		Dir = STOP;
	}
	for (int i = 0; i < NTails; i++)
	{
		if (PlayerX == TailX[i] && PlayerY == TailY[i])
		{
			GameOver = true;
			Dir = STOP;
		}
	}
	if (PlayerY == FruitY && PlayerX == FruitX)
	{
		Score += 100;
		FruitX = rand() % WIDTH;
		FruitY = rand() % HEIGHT;
		NTails++;
	}


}

void play() {
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(16.6);	//change this number to change fps
	}

	system("color 4");
	system("cls");
	Draw();
	Sleep(2000);
	system("color 2");
	system("cls");

	cout << "Score: " << Score << endl;
	cout << "Play again? Y/N    ";
	string answer;
	cin >> answer;
	system("color 7");
	system("cls");
	if (answer == "Y" || answer == "y") play();
}

void main()
{
	play();
}



