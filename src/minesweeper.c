#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
// Defining the mine density relative to expert mode
#define MINE_DENSITY 4.85
// Function to place the mines on the board
void placeMines(int mines, int dim, int board[dim][dim])
{
    // Set the mine count to 0
    int mineCount = 0;
    // While the mine count does not equal the amount of mines keep generating random coordinates to place mines
    while (mineCount < mines)
    {
        int x = rand() / (RAND_MAX / (dim) + 1);
        int y = rand() / (RAND_MAX / (dim) + 1);
        if (board[x][y] != -1)
        {
            board[x][y] = -1;
            mineCount++;
        }
    }
}
// Function to mark the mine counts on the board
void markMineCounts(int dim, int board[dim][dim])
{
    int row, col;
    int minecount = 0;
    for (row = 0; row < dim; row++)
    {
        for (col = 0; col < dim; col++)
        {
            minecount = 0;
            if (col > 0)
            {
                // Left
                if (board[row][col - 1] == -1)
                {
                    minecount++;
                }
                // Top Left
                if (row > 0)
                {
                    if (board[row - 1][col - 1] == -1)
                    {
                        minecount++;
                    }
                }
            }
            if (row > 0)
            {
                // Up
                if (board[row - 1][col] == -1)
                {
                    minecount++;
                }
                // Top Right
                if (col < dim - 1)
                {
                    if (board[row - 1][col + 1] == -1)
                    {
                        minecount++;
                    }
                }
            }
            if (col < dim - 1)
            {
                // Right
                if (board[row][col + 1] == -1)
                {
                    minecount++;
                }
                // Bottom Right
                if (row < dim - 1)
                {
                    if (board[row + 1][col + 1] == -1)
                    {
                        minecount++;
                    }
                }
            }
            if (row < dim - 1)
            {
                // Down
                if (board[row + 1][col] == -1)
                {
                    minecount++;
                }
                // Botom Left
                if (col > 0)
                {
                    if (board[row + 1][col - 1] == -1)
                    {
                        minecount++;
                    }
                }
            }
            if (board[row][col] != -1)
            {
                board[row][col] = minecount;
            }
        }
    }
}
// Function to check the validity of the board
void checkBoard(int dim, int board[dim][dim], int totalMines)
{
    int row, col, mineCount, totalMineCount = 0;
    bool wrong = false;
    for (row = 0; row < dim; row++)
    {
        for (col = 0; col < dim; col++)
        {
            if (board[row][col] != -1)
            {
                mineCount = 0;
                if (col > 0)
                {
                    // Left
                    if (board[row][col - 1] == -1)
                    {
                        mineCount++;
                    }
                    // Top Left
                    if (row > 0)
                    {
                        if (board[row - 1][col - 1] == -1)
                        {
                            mineCount++;
                        }
                    }
                }
                if (row > 0)
                {
                    // Top
                    if (board[row - 1][col] == -1)
                    {
                        mineCount++;
                    }

                    if (col < dim - 1)
                    {
                        // Top Right
                        if (board[row - 1][col + 1] == -1)
                        {
                            mineCount++;
                        }
                    }
                }
                if (col < dim - 1)
                {
                    // Right
                    if (board[row][col + 1] == -1)
                    {
                        mineCount++;
                    }
                    // Bottom Right
                    if (row < dim - 1)
                    {
                        if (board[row + 1][col + 1] == -1)
                        {
                            mineCount++;
                        }
                    }
                }
                if (row < dim - 1)
                {
                    // Bottom
                    if (board[row + 1][col] == -1)
                    {
                        mineCount++;
                    }
                    // Bottom Left
                    if (col > 0)
                    {
                        if (board[row + 1][col - 1] == -1)
                        {
                            mineCount++;
                        }
                    }
                }
                if (board[row][col] != mineCount)
                {
                    printf("Wrong at %d, %d\n", row, col);
                    printf("Minecount %d does not match %d from board\n", mineCount, board[row][col]);
                    wrong = true;
                }
            }
            else
            {
                totalMineCount++;
            }
        }
    }
    if (wrong || totalMineCount != totalMines)
    {
        printf("Board is wrong\n");
    }
    else
    {
        printf("Board is correct\n");
    }
}
// Function to display the board in the console
void displayBoard(int dim, int board[dim][dim])
{
    int i, j;
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (board[i][j] == -1)
            {
                printf("X ");
            }
            else
            {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
}
// Timing function
int timeval_subtract(double *result, struct timeval *x, struct timeval *y)
{
    struct timeval result0;

    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec)
    {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000)
    {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait.
       tv_usec is certainly positive. */
    result0.tv_sec = x->tv_sec - y->tv_sec;
    result0.tv_usec = x->tv_usec - y->tv_usec;
    *result = ((double)result0.tv_usec) / 1e6 + (double)result0.tv_sec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}
/*
Command Line Program Execution
./minesweeper -d <dimension (int)>
*/
int main(int argc, char *argv[])
{
    printf("-----------------------------------------------------\n");
    // Seed random number generator
    srand(time(NULL));
    printf("Serial Generation of Board\n");
    // Get dimension
    int dim = atoi(argv[2]);
    int board[dim][dim];
    int i, j;
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            board[i][j] = 0;
        }
    }

    // Get amount of mines with same density as expert board
    int mines = dim * dim / MINE_DENSITY;
    printf("Board Size: %d x %d\n", dim, dim);
    printf("Number of mines %d\n", mines);
    double restime;
    struct timeval tdr0, tdr1, tdr;
    // Start time
    gettimeofday(&tdr0, NULL);
    // Place mines
    placeMines(mines, dim, board);
    // Mark mine counts
    markMineCounts(dim, board);
    // End time
    gettimeofday(&tdr1, NULL);
    tdr = tdr0;
    timeval_subtract(&restime, &tdr1, &tdr);
    printf("Elapsed Time: %lf seconds\n", restime);
    // Check board
    checkBoard(dim, board, mines);
    if (argc > 3)
    {
        // Write board to a file
        char filename[50];
        snprintf(filename, sizeof(filename), "board_serial -d %d.txt", dim);
        FILE *fp;
        fp = fopen(filename, "w");
        for (i = 0; i < dim; i++)
        {
            for (j = 0; j < dim; j++)
            {
                if (board[i][j] == -1)
                {
                    fprintf(fp, "X ");
                }
                else
                {
                    fprintf(fp, "%d ", board[i][j]);
                }
            }
            fprintf(fp, "\n");
        }
        printf("Board written to \"%s\"\n", filename);
        fclose(fp);
    }

    // displayBoard(dim, board);
    printf("-----------------------------------------------------\n");
    return 0;
}