#include <iostream>
#include <ctime>
#include <cstdlib>
/*
INFORMATION:

Battleship Project - Created by Cole Brooks
Embark on a game of battleship with an automated opponent.

*/

using namespace std;

const int ALLOWED_SHIPS = 5; // Max ships allowed.
int arr_size = 8; // size of the game board
char their_arr[8][8]; // contains board status
int ship_arr[8][8]; // contains ship positions
char your_arr[8][8]; // your board
int ship_count = 0; // amount of ships
int sunk_count = 0; // amount of ships sunk
int cpu_sunk = 0; // amount of ships cpu sunk


void mult(int size, char inp)
{
	for (int i = 0; i < size; ++i)
		std::cout << inp; // writes ! to the output 'size' times
}

char numToChar(int i)
{
	return static_cast<char>('A' - 1 + i); // converts a num to a character
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

void makeYourBoard()
{
	// Populates the board array with zeroes.
	for (int i = 0; i < arr_size; i++)
	{
		for (int j = 0; j < arr_size; j++)
		{
			your_arr[i][j] = '0';
		}
	}
}

void buildFleet()
{
	// Populate your board with ships.
	cout << "It is time to build your fleet!" << endl;
	for (int i = 0; i < ALLOWED_SHIPS; i++)
	{
		char x;
		int y;
		cout << "Enter the coordinates (x,y): ";
		cin >> x;
		x = toupper(x) - 'A';
		cin >> y;
		your_arr[y - 1][x] = 'S';
	}
}

void gameOver(int type)
{
	// Game over, can be ended in two ways.
	switch(type)
	{
		case 1: cout << "You've done it! You sunk all the battleships!" << endl; break; // You beat computer.
		case 2: cout << "You've lost, the CPU beat you!" << endl; break; // Computer beats you.
	}
}

void initShips()
{
	// Initializes ship positions.
	srand(time(NULL));
	for (int i = 0; i < ALLOWED_SHIPS; i++)
	{
			int ship = (rand() % 3) + 1; 
			int pos_x = rand() % 8;
			int pos_y = rand() % 8;
			if (ship_arr[pos_x][pos_y] == 0)
			{
				ship_arr[pos_x][pos_y] = ship;
			}
	}
}

void shipCount()
{	// Gets a list of all enemy ships.
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
	cout << "Their board: " << endl;
	cout << "Total Ships: " << ship_count << endl;
	cout << "Total Sunk: " << sunk_count << endl;
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

void drawYourBoard()
{
	// Draws out the current state of the board.
	cout << "-------------------------" << endl;
	cout << "Your Board: " << endl;
	cout << "Your Ships: " << ALLOWED_SHIPS << endl;
	cout << "Ships Sunk: " << cpu_sunk << endl;
	for (int i = 0; i < arr_size; i++)
	{
		cout << i + 1 << "  ";
		for (int j = 0; j < arr_size; j++)
		{
			cout << your_arr[i][j] << " ";
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

void cpu_shoot()
{
	// Computer takes a shot.
	int j = 0;
	char x = numToChar(rand() % 8);
	int y = rand() % 8;
	x = toupper(x) - 'A';
	while (j < 1 && your_arr[x][y] != 'M' && your_arr[x][y] != 'H')
	{
		j++;
		char x = numToChar(rand() % 8);
		int y = rand() % 8;
		x = toupper(x) - 'A';
		if (your_arr[x][y] == 'S')
		{
			cpu_sunk++;
			your_arr[x][y] = 'H';
			cout << "Computer: Ha, I did it! I completely obliterated that ship!" << endl;
		}
		else if (your_arr[x][y] == '0')
		{
			your_arr[x][y] = 'M';
			cout << "Computer: How is this possible! No..." << endl;
		}
	}
}

void shoot(char x, int y)
{
	// Handles shooting on the map.

	if (ship_arr[x][y] != 0 && their_arr[x][y] == '0')
	{
		sunk_count++;
		their_arr[x][y] = 'H';
		cout << "Computer: You were lucky that time..." << endl;
		cpu_shoot();
	}
	else if (their_arr[x][y] == '0')
	{
		their_arr[x][y] = 'M';
		cout << "Computer: Ha! You've missed! Time for me to destroy your ship!" << endl;
		cpu_shoot();
	}
}

void instructions()
{
	// Informs the player on how to play the game.
	cout << "Legend" << endl;
	cout << "0 - Not Seen" << endl;
	cout << "M - Miss" << endl;
	cout << "H - Hit" << endl;
}

int main()
{
	// Main function, calls all the other functions, backbone of the game.
	system("title Battleship - Cole Brooks"); // Title the console
	system("color A"); // Color the console to - Green
	makeYourBoard(); // Population of your board.
	buildFleet(); // Build your fleet.
	drawYourBoard(); // Actual output of your board.
	makeBoard(); // Population of enemy board.
	initShips(); // Initialize enemy ships.
	shipCount(); // Get amount of enemy ships.
	instructions(); // Explains the game
	drawBoard(); // Draws enemy board
	//shipPositions(); // debug purposes, shows ship positions
	while (true)
	{
		// Loop responsible for shooting.
		char x;
		int y;
		cout << "Enter the coordinates (x,y): "; 
		cin >> x;
		x = toupper(x) - 'A';
		cin >> y;
		shoot(y - 1, x);
		instructions();
		drawYourBoard();
		drawBoard();
		if (sunk_count == ship_count)
		{
			gameOver(1);
			break;
		}
		else if (cpu_sunk == ALLOWED_SHIPS)
		{
			gameOver(2);
			break;
		}
	}
	

	system("pause");
	return 0;
}