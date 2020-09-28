
# include <iostream>
#include <ctime>
#include <cstdlib>                                        // inclusion of libraries
#include <time.h>
#include <stdlib.h>
using namespace std;
int score;
int count;
char user[40];
void replay();
// functions

int random(int boardsize)
{

	int random_number;
	random_number = rand() % boardsize;                      // GENERATES RANDOM NUMBER WITH BOARD SIZE AS LIMIT
	return random_number;


}

void openbox(int x)
{                                            // gets input mineboard[i][j] as x and display its value at these coordinates
	if (x == 0)
	{
		system("color F8");
		cout << "o|";
	}
	else if (x == 9)                           //9 is for mine
	{
		system("color F4");
		cout << "x|";
	}
	else
	{
		system("color F1");
		cout << x << "|";
	}
}
void File_write(char *user, int scores)
{
	FILE * p;
	p = fopen("score.txt", "a");
	fprintf(p, "%s %d\n", user, scores);                     // writing score and user name in file

	fclose(p);
}
void File_display()
{
	int score = 0;
	FILE * a;
	a = fopen("score.txt", "r");
	while (fscanf(a, "%s %d\n", user, &score) != EOF)            // reading from file and displaying it.
	{
		cout << "user = " << user << "  " << "score = " << score << endl;
	}
	fclose(a);
}

int difficulty()
{
	int mines = 0;
	int check = 0;
	do
	{
		int difficulty;
		cout << "ENTER  1 FOR BEGINNER" << endl;
		cout << "ENTER  2 FOR MEDUIM" << endl;             // reads  difficulty level from user to decide no of mines accordingly
		cout << "ENTER  3 FOR HARD" << endl;               // returns no of mines
		cin >> difficulty;
		if (difficulty == 1)
		{
			mines = 10;
			check = 1;
		}
		else if (difficulty == 2)
		{
			mines = 20;
			check = 1;
		}
		else if (difficulty == 3)
		{
			mines = 30;
			check = 1;
		}
	} while (check != 1);

	return  mines;
}
void initialize(int board[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = 0;
		}
	}


}
void plant_mines(int mineboard[10][10], int boardsize, int mines)
{

	do
	{

		int x = random(boardsize);
		int y = random(boardsize);                   //generating random number 
		if (mineboard[y][x] != 9)
		{
			mineboard[y][x] = 9;
			mines--;

			if ((y - 1) >= 0)
			{
				if (mineboard[y - 1][x] != 9)
					mineboard[y - 1][x]++;                                    // this if conditions after the mine is planted 
			}                                                                  // scan around that mine and update their number
			// the ones which in direct contact
			if ((y - 1) >= 0 && (x - 1) >= 0)
			{
				if (mineboard[y - 1][x - 1] != 9)
					mineboard[y - 1][x - 1]++;
			}
			if ((x - 1) >= 0)
			{
				if (mineboard[y][x - 1] != 9)
					mineboard[y][x - 1]++;
			}
			if ((y + 1) < boardsize)
			{
				if (mineboard[y + 1][x] != 9)
					mineboard[y + 1][x]++;
			}
			if ((y + 1) < boardsize && (x + 1) < boardsize)
			{
				if (mineboard[y + 1][x + 1] != 9)
					mineboard[y + 1][x + 1]++;
			}
			if ((x + 1) < boardsize)
			{
				if (mineboard[y][x + 1] != 9)
					mineboard[y][x + 1]++;
			}
			if ((y - 1) >= 0 && (x + 1) < boardsize)
			{
				if (mineboard[y - 1][x + 1] != 9)
					mineboard[y - 1][x + 1]++;
			}
			if ((y + 1) < boardsize && (x - 1) >= 0)
			{
				if (mineboard[y + 1][x - 1] != 9)
					mineboard[y + 1][x - 1]++;
			}
		}
	} while (mines>0);                      // this loop will keep repeating itself until all mines have been planted

}
int check_ifwon(int obox, int mines)
{                                                              //obox means opened boxes
	if (obox >= ((100) - mines))
	{
		cout << "You win!" << endl;
		return 1;                                                  //if no of opened box get equal to total no of boxes other than mines
	}


}
int check_iflost(int y, int x, int mineboard[10][10], int userboard[10][10], int boardsize)
{

	if (mineboard[y][x] == 9)
	{
		int d = 0;
		cout << "OOPS  You hit a mine!" << endl;                 // if a mine has been hit finish equals 1 and display board with all mines 
		cout << "   ";
		for (int i = 0; i<boardsize; i++)
			cout << i << " ";
		cout << endl;
		d = 1;
		for (int i = 0; i<boardsize; i++)
		{
			for (int j = 0; j<boardsize; j++)
			{
				if (j == 0)
					cout << i << " |";
				if (mineboard[i][j] == 9)
					userboard[i][j] = 1;
				if (userboard[i][j] == 1)
					openbox(mineboard[i][j]);
				else
					cout << "_|";
				if (j == (boardsize - 1))
					cout << endl;
			}
		}
		return d;


	}

}
void game(char * user)
{/*
 system("color F2");*/
	int boardsize = 10;
	//do
	//{
	//	cout << "Enter boardsize (2 - 10)" << endl;            // read's size of board from user until valid INPUT IS GIVEN (2-10)
	//	cin >> boardsize;
	//}
	//while ( boardsize < 1 && boardsize >= 10);


	int mineboard[10][10];                                        // declaring characterrarray for mineboard
	int userboard[10][10];                                          // declaring characterarray for userboard
	int i = 0;                                                                                        //speacial comments
	int j = 0;                                                                                        // using "tb"for 1
	int x = 0;                                                                                        // "x" for mine instead of 9
	int y = 0;                                                                                        // no_mines instead of z and openendbox for q
	int no_mines;                                                                                     // finish for dead
	int opened_box;
	int score = 0;
	int win = 0;
	int lost = 0;
	int end = 0;

	no_mines = difficulty();            //calling difficulty functionfor no of mines

	initialize(mineboard);
	initialize(userboard);    // calling  function of initialize to initialize user and mineboard


	cout << "Generating board...please wait" << endl;

	plant_mines(mineboard, 10, no_mines);                 // calling function to plant bombs randomly


	do
	{

		no_mines = 0;
		opened_box = 0;

		cout << "   ";

		for (i = 0; i < boardsize; i++)
		{
			cout << i << " ";                     //displays no of rows
		}
		cout << endl;

		for (i = 0; i < boardsize; i++)
		{
			for (j = 0; j < boardsize; j++)
			{
				if (j == 0)
				{                               //if col is zero which is j in this case than print |
					cout << i << " |";
				}

				if (userboard[i][j] == 1)
				{                                  //if there is  a box to be displayed (tb) in user board than  open corresponding box in mineboard
					openbox(mineboard[i][j]);
				}
				else
				{
					cout << "_|";
				}

				if (j == (boardsize - 1))
				{                                      // if last col is reached move to next line
					cout << endl;
				}

				if (mineboard[i][j] != 9 && userboard[i][j] == 1)
				{
					opened_box++;
					score = score + 5;                     //if a box is not a mine and has been opened cout it as an openbox
				}

				if (mineboard[i][j] == 9)
				{
					no_mines++;
				}
			}
		}
		win = check_ifwon(opened_box, no_mines);

		if (win == 1)
		{
			end = 1;

		}

		if (end == 0)

		{
			cout << " please enter row ";
			cin >> y;
			cout << " please enter col ";
			cin >> x;
		}

		lost = check_iflost(y, x, mineboard, userboard, boardsize);
		{
			if (lost == 1)
			{

				end = 1;
			}
		}


		if (mineboard[y][x] == 0)
		{
			userboard[y][x] = 1;
			for (i = 0; i < boardsize; i++)
			{
				for (j = 0; j<boardsize; j++)
				{                                                  // if there is is a zero on mineboard selected than open random 
					if (i>(y - 2) && i<(y + 2))                    //  boxes via through  formula
					{
						if (j>(x - 2) && j < (x + 2))
						{
							if (mineboard[i][j] != 9)
							{
								userboard[i][j] = 1;
							}
						}
					}

				}
			}
		}


		if (mineboard[y][x] > 0 && mineboard[y][x] < 9)
		{
			userboard[y][x] = 1;
		}
	}

	while (end == 0);                                    // this loop continues to repeat until game is either won or lost so finish equals 1 
	cout << "score  = " << score << endl;
	File_write(user, score);
	// and loop breaks
	if (end == 1)
	{

		replay();
	}
}

void main()
{
	//system("color xy");
	system("color F2");
	int choice;
	cout << "1-NEW GAME" << endl;
	cout << "2-SCORE LIST" << endl;
	cout << "3-EXIT" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
			  cout << "Enter Player's Name" << endl;
			  fflush(stdin);
			  gets(user);
			  game(user);
			  break;
	}
	case 2:
	{
			  File_display();
			  main();
			  break;
	}
	case 3:
	{
			  break;
	}
	}


}
void replay()
{
	char choice;
	cout << "ENTER (1) TO PLAY AGAIN  " << endl;
	cout << "ENTER (2) TO PLAY QUIT " << endl;
	cin >> choice;
	switch (choice)
	{
	case '1':                                          // IF CHOICE IS 1 CALL GAME FUNCTION
		game(user);
		break;
	case '2':

		main();                                           // IF CHOICE IS 2 CALL MAIN FUNCTION 
		break;
	default:
		cout << "Invalid input" << endl;           //IF CHOICE IS INVALID REPEAT THIS PROCESS BY AGAIN CALLING REPLAY FUNCTION
		replay();
		break;
	}
}

