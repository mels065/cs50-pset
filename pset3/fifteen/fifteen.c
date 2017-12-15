/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// empty space
int emptySpace[2];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int coord1[2], int coord2[2]);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    emptySpace[0] = d - 1;
    emptySpace[1] = d - 1;
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    int val = (d * d) - 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = val;
            val--;
        }
    }

    if (d % 2 == 0)
    {
        int pos1[2] = {d - 1, d - 2};
        int pos2[2] = {d - 1, d - 3};
        swap(pos1, pos2);
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0) printf(" _");
            else printf("%2i ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // Above
    int possible = emptySpace[0] - 1;
    if (possible >= 0 && board[possible][emptySpace[1]] == tile)
    {
        int newPos[2] = {possible, emptySpace[1]};
        swap(emptySpace, newPos);
        emptySpace[0] = possible;
        return true;
    }
    // Left
    possible = emptySpace[1] - 1;
    if (possible >= 0 && board[emptySpace[0]][possible] == tile)
    {
        int newPos[2] = {emptySpace[0], possible};
        swap(emptySpace, newPos);
        emptySpace[1] = possible;
        return true;
    }
    // Bottom
    possible = emptySpace[0] + 1;
    if (possible < d && board[possible][emptySpace[1]] == tile)
    {
        int newPos[2] = {possible, emptySpace[1]};
        swap(emptySpace, newPos);
        emptySpace[0] = possible;
        return true;
    }
    // Right
    possible = emptySpace[1] + 1;
    if (possible < d && board[emptySpace[0]][possible] == tile)
    {
        int newPos[2] = {emptySpace[0], possible};
        swap(emptySpace, newPos);
        emptySpace[1] = possible;
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int val = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (i == d - 1 && j == d - 1) break;
            if (board[i][j] != val) return false;
            val++;
        }
    }
    return true;
}

void swap(int coord1[2], int coord2[2])
{
    int temp = board[coord1[0]][coord1[1]];
    board[coord1[0]][coord1[1]] = board[coord2[0]][coord2[1]];
    board[coord2[0]][coord2[1]] = temp;
}
