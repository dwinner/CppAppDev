/**
 *	Simulating the game of craps
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Status
{
	CONTINUE,
	WON,
	LOST
};

int rollDice(void);

int main(int argc, char* argv[])
{
	// randomize random number generator using current time
	srand(time(NULL));

	int myPoint; // player must make this point to win
	enum Status gameStatus; // can contain CONTINUE, WON, or LOST
	int sum = rollDice(); // first roll of the dice

	// determine game status based on sum of dice
	switch (sum)
	{
		// win on first roll
	case 7: // 7 is a winner
	case 11: // 11 is a winner          
		gameStatus = WON;
		break;

		// lose on first roll
	case 2: // 2 is a loser
	case 3: // 3 is a loser
	case 12: // 12 is a loser
		gameStatus = LOST;
		break;

		// remember point
	default:
		gameStatus = CONTINUE; // player should keep rolling
		myPoint = sum; // remember the point
		printf("Point is %d\n", myPoint);
		break; // optional
	}

	// while game not complete
	while (CONTINUE == gameStatus)
	{
		// player should keep rolling
		sum = rollDice(); // roll dice again

		// determine game status
		if (sum == myPoint)
		{
			// win by making point
			gameStatus = WON;
		}
		else
		{
			if (7 == sum)
			{
				// lose by rolling 7
				gameStatus = LOST;
			}
		}
	}

	// did player win?
	puts(WON == gameStatus ? "Player wins" : "Player loses");

	return 0;
}

int rollDice(void)
{
	const int die1 = 1 + rand() % 6;
	const int die2 = 1 + rand() % 6;

	printf("Player rolled %d + %d = %d\n", die1, die2, die1 + die2);
	return die1 + die2;
}
