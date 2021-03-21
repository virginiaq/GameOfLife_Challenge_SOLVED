// Conway's Game of Life
//
#include "stdafx.h"
#include "windows.h"

const int boardXSize = 20;
const int boardYSize = 20;

const int dead = 0;
const int alive = 1;

const char *boardSetup = "flower";

int Board[boardYSize][boardXSize];

// I need a copy of the grid to keep track of the updated grid
int BCopy[boardYSize][boardXSize];

void CopyBoard(int (&board)[boardXSize][boardYSize], int (&bcopy)[boardXSize][boardYSize])
{
	for (int i = 0; i < boardXSize; i++)
	{
		for (int j = 0; j < boardXSize; j++)
		{
			bcopy[i][j] = board[i][j];
		}
	}
}

// Clears the board so all cells are dead
void ClearBoard(int (&dstBoard)[boardXSize][boardYSize])
{
	for (int x = 0; x <= boardXSize; ++x)
	{
		for (int y = 0; y <= boardYSize; ++y)
		{
			dstBoard[x][y] = dead;
		}
	}
}

// Counts the number of neighbours for the specified cell
int Neighbours(int (&board)[boardXSize][boardYSize], int x, int y)
{

	// was it necessary to set dx and dy to 0?
	int dx, dy, ax, ay;
	int n = 0;
	// It's not checking the edges in the right way
	// i.e. if x or y == 0 it needs to count their opposites on the grid

	for (dx = -1; dx <= 1; ++dx)
	{
		for (dy = -1; dy <= 1; ++dy)
		{
			ax = x + dx;
			ay = y + dy;

			// after assigning coords for the cells around it checks for borders
			if (ax < 0)
			{
				ax = boardXSize - 1;
			}
			else if (ax > boardXSize - 1)
			{
				ax = 0;
			}

			if (ay < 0)
			{
				ay = boardYSize - 1;
			}
			else if (ay > boardYSize - 1)
			{
				ay = 0;
			}

			if (board[ax][ay] == alive)
			{
				++n;
			}
		}
	}
	// The neighbouring count was counting itself as neighbour!!!
	// So it subtracts the value of its own coords
	return n - board[x][y];
}

// Draws the board to the console window
void DrawBoard()
{
	COORD coord;

	coord.X = 0;
	coord.Y = 0;

	// Sets the cursor to the top of the console window.
	// If you're not on a Windows platform, feel free to adapt this to ANSI control sequences,
	// or just print out each step sequentially
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	for (int y = 0; y < boardYSize; ++y)
	{
		for (int x = 0; x < boardXSize; ++x)
		{
			printf("%s", Board[x][y] == alive ? "O" : ".");
		}
		printf("\n");
	}
}

// Updates the board based on the rules
void NextStep(int (&board)[boardXSize][boardYSize])
{
	CopyBoard(board, BCopy);

	for (int x = 0; x < boardXSize; ++x)
	{
		for (int y = 0; y < boardYSize; ++y)
		{
			int n = Neighbours(board, x, y);

			// Some conditions were assigning values instead of comparing
			// and weren't covering all rules
			if (board[x][y] == alive && (n < 2 || n > 3))
			{
				BCopy[x][y] = dead;
			}
			else if (n == 3)
			{
				BCopy[x][y] = alive;
			}
			else if (board[x][y] == dead && n != 3)
			{
				BCopy[x][y] = dead;
			}
		}
	}

	// it copies the updated board on the original
	CopyBoard(BCopy, board);
}

// Sets up the initial state of the board
void SetupBoard(int (&board)[boardXSize][boardYSize])
{
	ClearBoard(Board);

	// To find out if the problem was the neighbouring count or the next step func
	// I changed the starting point of blinker and glider so they didn't touch the edges
	// It was in fact the neighbour count. After changing it I put the values back

	// And it works!!
	if (strcmp(boardSetup, "blinker") == 0)
	{
		board[1][0] = alive;
		board[1][1] = alive;
		board[1][2] = alive;
	}
	else if (strcmp(boardSetup, "glider") == 0)
	{
		board[2][0] = 1;
		board[2][1] = 1;
		board[2][2] = 1;
		board[1][2] = 1;
		board[0][1] = 1;
	}
	// I doubled the size of the board so the flower could fit properly with this setup
	else if (strcmp(boardSetup, "flower") == 0)
	{
		board[4][6] = 1;
		board[5][6] = 1;
		board[6][6] = 1;
		board[7][6] = 1;
		board[8][6] = 1;
		board[9][6] = 1;
		board[10][6] = 1;
		board[4][7] = 1;
		board[6][7] = 1;
		board[8][7] = 1;
		board[10][7] = 1;
		board[4][8] = 1;
		board[5][8] = 1;
		board[6][8] = 1;
		board[7][8] = 1;
		board[8][8] = 1;
		board[9][8] = 1;
		board[10][8] = 1;
	}
}

int main()
{
	SetupBoard(Board);

	while (true)
	{
		DrawBoard();
		NextStep(Board);
		//I used this at the beginning to check if the neighbours count was working properly
		//printf("%d", Neighbours(Board));
		Sleep(100);
	}
	return 0;
}
