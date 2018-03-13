#include <iostream>
#include <ctime>
#include <cstdlib>
/*
INFORMATION:

Instead of using a constant amount of ships, I decided to implement a solution that scaled with the size of the board.


*/

using namespace std;

int arr_size = 8; // size of the game board
char their_arr[8][8]; // contains board status
int ship_arr[8][8]; // contains ship positions
char your_arr[8][8];
int your_ship_arr[8][8];
int ship_count = 0; // amount of ships
int sunk_count = 0; // amount of ships sunk


void mult(int size, char inp)
{
	for (int i = 0; i < size; ++i)
		std::cout << inp; // writes ! to the output 'size' times
}

char numToChar(int i)
{
	return static_cast<char>('A' - 1 + i);
}


void makeBoard()
{
	// Populates the board array with zeroes.
	for (int i = 0; i < arr_size; i++) 
	{
		for (int j = 0; j < arr_size; j++)
		{
			their_arr[i][j] = '0';
		}
	}
}

void gameOver()
{
	// Congratulates the winner of the game.
	cout << "You've done it! You sunk all the battleships!" << endl;
}

void initShips()
{
	// Initializes ship positions.
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
			int ship = (rand() % 3) + 1;
			int pos_x = rand() % 8;
			int pos_y = rand() % 8;
			if (ship_arr[pos_x][pos_y] == 0)
			{
				ship_arr[pos_x][pos_y] = ship;
			}
			else
			{
				i++;
			}
	}
}

void shipCount()
{
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{
			if (ship_arr[i][j] != 0)
			{
				ship_count++;
			}
		}
	}
}

void drawBoard()
{
	// Draws out the current state of the board.
	cout << "-------------------------" << endl;
	for (int i = 0; i < arr_size; i++)
	{
		cout << i + 1 << "  ";
		for (int j = 0; j < arr_size; j++)
		{
			cout << their_arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "  ";
	for (int j = 0; j < arr_size; j++)
	{
		cout << " " << numToChar(j + 1);
	}
	cout << endl;
	cout << "-------------------------" << endl;
}

void shipPositions()
{
	// Shows the positions of the ships (debug purposes)
		cout << "-----------------!-----------------------" << endl;
		for (int i = 0; i < arr_size; i++)
		{
			for (int j = 0; j < arr_size; j++)
			{
				cout << ship_arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << "----------------------------------------" << endl;
}

void shoot(char x, int y)
{
	// Handles shooting on the map.

		if (ship_arr[x][y] != 0 && their_arr[x][y] == '0')
		{
			sunk_count++;
			their_arr[x][y] = 'H';
		}
		else if (their_arr[x][y] == '0')
		{
			their_arr[x][y] = 'M';
		}
}

void instructions()
{
	// Informs the player on how to play the game.
	cout << "Total Ships: " << ship_count << endl;
	cout << "Total Sunk: " << sunk_count << endl;
	cout << "Legend" << endl;
	cout << "0 - Not Seen" << endl;
	cout << "M - Miss" << endl;
	cout << "H - Hit" << endl;
	cout << "3 - Sink" << endl;
}

int main()
{
	system("title Battleship");
	system("color A");
	makeBoard();
	initShips();
	shipCount();
	instructions();
	drawBoard();
	//shipPositions(); // debug purposes
	while (true)
	{
		char x;
		int y;
		cout << "Enter the coordinates (x,y): "; 
		cin >> x;
		if (isupper(x) == false)
		{
			cout << endl << "CRITICAL ERROR: Invalid coordinates!" << endl;
			break;
		}
		x = x - 'A';
		cin >> y;
		shoot(y - 1, x);
		instructions();
		drawBoard();
		if (sunk_count == ship_count)
		{
			gameOver();
			break;
		}
	}
	

	system("pause");
	return 0;
}