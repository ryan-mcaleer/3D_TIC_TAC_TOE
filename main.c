#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int directions[10][3] = {
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {0,1,1},
    {1,0,1},
    {1,1,0},
    {1,1,1},
    {-1,1,-1},
    {-1,1,1},
    {1,1,-1}
};

int AtBounds(int x, int y, int z, int dx, int dy, int dz) {
    // Check if at bounds in X direction
    if (dx > 0) {
        if((x + (2 * dx)) > 2)
            return 1;
    } else if (dx < 0 ) {
        if((x + (2 * dx)) < 0)
            return 1;
    }
    // Check if at bounds in Y direction
    if (dy > 0) {
        if((y + (2 * dy)) > 2)
            return 1;
    } else if (dy < 0 ) {
        if((y + (2 * dy)) < 0)
            return 1;
    }
    // Check if at bounds in Z direction
    if (dz > 0) {
        if((z + (2 * dz)) > 2)
            return 1;
    } else if (dz < 0 ) {
        if((z + (2 * dz)) < 0)
            return 1;
    }
    return 0;
}

int PlayerWinningAtPos(char grid[3][3][3], char player, int x, int y, int z) {
    int *direction;
    for (size_t di = 0; di <10; di++) {
        direction = directions[di];
        int dx = direction[0];
        int dy = direction[1];
        int dz = direction[2];
        int NumConsecutiveOnes = 0;
        int xi = x, yi = y, zi = z;
        if (AtBounds(x, y, z, dx, dy, dz) == 1)
            break;
        else {
            for (int i = 0; i < 3; i++) {
                if (grid[xi][yi][zi] == player) {
                    NumConsecutiveOnes += 1;
                    xi += dx;
                    yi += dy;
                    zi += dz;
                }
            }
        }
        if (NumConsecutiveOnes == 3) {
            return 1;
        }
    }
    return 0;
}

void display_board(char array[3][3][3]) {
	int x,y,z;

	/* display */
	puts("\n\nTic Tac Toe");
	for(x=0;x<3;x++)
	{
		printf("%*c",x+1,' ');		/* The * is a placeholder for the width */
		for(y=0;y<3;y++)
		{
			for(z=0;z<3;z++)
				printf(" %c ", array[x][y][z]);
			printf("     ");	/* 5 spaces */
		}
		putchar('\n');
	}
}

char CheckWinner(char grid[3][3][3]) {
    for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
    for (int z = 0; z < 3; z++) {
        if (PlayerWinningAtPos(grid, 'X', x, y, z) == 1) {
            return 'X';
        } else if (PlayerWinningAtPos(grid, 'O', x, y, z) == 1){
            return 'O';
        }
    }
    }
    }
}

void one_turn(char array[3][3][3], int player) {

    int x,y,z;

    printf("Player %d's turn", player);
    printf("\nplease enter the X index of the square you would like to fill (0 - 2 index, separated by spaces): ");
    scanf("%i", &x);
    printf("\nplease enter the Y index of the square you would like to fill (0 - 2 index, separated by spaces): ");
    scanf("%i", &y);
    printf("\nplease enter the Z index of the square you would like to fill (0 - 2 index, separated by spaces): ");
    scanf("%i", &z);

    if (player == 1) {
        array[x][y][z] = 'X';
    }
    else if (player == 2) {
        array[x][y][z] = 'O';
    }
}

int main()
{
	char tictactoe[3][3][3];
	char win_value;
	int x,y,z, player;

	player = 1;

	/* initialize */
	for(x=0;x<3;x++)
		for(y=0;y<3;y++)
			for(z=0;z<3;z++)
				tictactoe[x][y][z] = '.';

    while (1) {
        if(player == 1) {
            one_turn(tictactoe, player);
            win_value = CheckWinner(tictactoe);
            if (win_value == 'X') {
                printf("\n\nWin Value: %c", win_value);
                printf("\nPlayer %i has won!\n", player);
                break;
            }
            player += 1;
        } else if (player == 2) {
            one_turn(tictactoe, player);
            win_value = CheckWinner(tictactoe);
            if (win_value == 'O') {
                printf("\n\nWin Value: %c", win_value);
                printf("\nPlayer %i has won!\n", player);
                break;
            }
            player -= 1;
        }
        display_board(tictactoe);
    }
	return 0;
}
