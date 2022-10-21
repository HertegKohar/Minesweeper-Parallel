#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <omp.h>
// Defining the mine density relative to expert mode
#define MINE_DENSITY 4.85
// Create function to place mines on the board
void placeMines(int mines, int dim, int board[dim][dim], int *seed, int start, int end)
{
    // Set the mine count to 0
    int mineCount = 0;
    int row, col;
    // While the mine count is less than the number of mines keep generating random coordinates to fill mines
    while (mineCount < mines)
    {
        row = start + rand_r(seed) / (RAND_MAX / (end - start + 1) + 1);
        col = rand_r(seed) / (RAND_MAX / (dim) + 1);
        if (board[row][col] != -1)
        {
            board[row][col] = -1;
            mineCount++;
        }
    }
}

// Function to mark the mine counts for the neighbouring tiles on the board
void markMineCounts(int dim, int board[dim][dim], int start, int end)
{
    int row, col;
    int minecount = 0;
    for (row = start; row <= end; row++)
    {
        for (col = 0; col < dim; col++)
        {
            minecount = 0;
            if (board[row][col] != -1)
            {
                if (col > 0)
                {
                    // Left
                    if (board[row][col - 1] == -1)
                    {
                        minecount++;
                    }
                    // Top Left
                    if (row > start)
                    {
                        if (board[row - 1][col - 1] == -1)
                        {
                            minecount++;
                        }
                    }
                }
                if (row > start)
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
                    if (row < end)
                    {
                        if (board[row + 1][col + 1] == -1)
                        {
                            minecount++;
                        }
                    }
                }
                if (row < end)
                {
                    // Down
                    if (board[row + 1][col] == -1)
                    {
                        minecount++;
                    }
                    // Bottom Left
                    if (col > 0)
                    {
                        if (board[row + 1][col - 1] == -1)
                        {
                            minecount++;
                        }
                    }
                }

                board[row][col] = minecount;
            }
        }
    }
}

// Function to update the neighbour borders ot consecutive processes
void updateNeighbourBorders(int dim, int board[dim][dim], int top, int bottom)
{
    int col;
    for (col = 0; col < dim; col++)
    {
        if (board[top][col] != -1)
        {
            if (col < dim - 1)
            {
                if (top < dim - 1)
                {
                    // Bottom Right
                    if (board[top + 1][col + 1] == -1)
                    {
                        board[top][col]++;
                    }
                }
            }
            if (top < dim - 1)
            {
                // Bottom
                if (board[top + 1][col] == -1)
                {
                    board[top][col]++;
                }
                // Bottom Left
                if (col > 0)
                {
                    if (board[top + 1][col - 1] == -1)
                    {
                        board[top][col]++;
                    }
                }
            }
        }
    }
    // If the bottom is equal to the dimension then don't update because of index out of bounds
    if (bottom != dim)
    {
        for (col = 0; col < dim; col++)
        {
            // If tile is not a mine
            if (board[bottom][col] != -1)
            {
                if (col > 0)
                {
                    if (bottom > 0)
                    {
                        // Top Left
                        if (board[bottom - 1][col - 1] == -1)
                        {
                            board[bottom][col]++;
                        }
                    }
                }
                if (bottom > 0)
                {
                    // Top
                    if (board[bottom - 1][col] == -1)
                    {
                        board[bottom][col]++;
                    }
                    // Top Right
                    if (col < dim - 1)
                    {
                        if (board[bottom - 1][col + 1] == -1)
                        {
                            board[bottom][col]++;
                        }
                    }
                }
            }
        }
    }
}

// Display to showcase the board based on each processe's subgrid
void debugDisplayBoard(int dim, int board[dim][dim], int subGridSize)
{
    int row, col;
    printf("Displaying Board\n");
    printf("%3s", " ");
    for (col = 0; col < dim; col++)
    {
        printf("%3d", col);
    }
    for (row = 0; row < dim; row++)
    {
        if (row % subGridSize == 0)
        {
            printf("\n");
        }
        printf("%3d", row);
        for (col = 0; col < dim; col++)
        {
            if (board[row][col] == -1)
            {
                printf("%3s", "X");
            }
            else
            {
                printf("%3d", board[row][col]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
// Display board normally for the user
void displayBoard(int dim, int board[dim][dim])
{
    printf("Displaying Board\n");
    int row, col;
    printf("%3s", " ");
    for (col = 0; col < dim; col++)
    {
        printf("%3d", col);
    }
    printf("\n");
    for (row = 0; row < dim; row++)
    {
        printf("%3d", row);
        for (col = 0; col < dim; col++)
        {
            if (board[row][col] == -1)
            {
                printf("%3s", "X");
            }
            else
            {
                printf("%3d", board[row][col]);
            }
        }
        printf("\n");
    }
}
// Function to check if the board is correctly marked
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

/*
Command Line Program Execution
./minesweeper_parallel -nt <threads (int)> -d <dimension (int)>
*/
int main(int argc, char *argv[])
{
    printf("-----------------------------------------------------\n");
    // Seed random number generator
    srand(time(NULL));
    // Seed the random number generator
    int seed = time(NULL);

    printf("Parallelized Generation of Board\n");
    // Get specified number of threads
    int nthreads = atoi(argv[2]);
    // Set specified number of threads
    omp_set_num_threads(nthreads);
    printf("Number of threads: %d\n", nthreads);
    // Get specified dimensions
    int dim = atoi(argv[4]);
    // Check if dimensions are divisible by the number of threads
    if (dim % nthreads != 0)
    {
        printf("Dimension must be divisible by number of threads\n");
        return 0;
    }
    // Initialize board
    int board[dim][dim];
    int i, j;
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            board[i][j] = 0;
        }
    }
    // Determine the amount of mines with same density of expert board
    int totalMines = dim * dim / MINE_DENSITY;
    // int minesPerThread = totalMines / nthreads;
    int minesPerThread[nthreads];
    int remainder = totalMines % nthreads;
    printf("Board Size: %d x %d\n", dim, dim);
    printf("Total number of mines %d\n", totalMines);
    printf("Mines per thread %d\n", totalMines / nthreads);
    printf("Remainder Distributed Among Threads %d\n", remainder);
    for (i = 0; i < nthreads; i++)
    {
        minesPerThread[i] = totalMines / nthreads;
        minesPerThread[i] += (remainder > 0) ? 1 : 0;
        remainder--;
    }

    int tid;
    double startTime = omp_get_wtime();
    // Start parallel region to fill in board subgrids
#pragma omp parallel shared(board, minesPerThread) firstprivate(nthreads, dim, seed) private(tid)
    {
        // Get thread number
        tid = omp_get_thread_num();
        // Increment the seed
        seed += tid;
        int start, end;
        // Calculate start and end points for each thread
        start = dim / nthreads * tid;
        end = dim / nthreads * (tid + 1) - 1;
        // printf("Thread %d Start: %d, End: %d, Seed: %d\n", tid, start, end, seed);
        // Place mines with specified seed and start and end points
        placeMines(minesPerThread[tid], dim, board, &seed, start, end);
#pragma omp barrier
        // Mark the minecounts on each respective subgrid
        markMineCounts(dim, board, start, end);
// Have barrier to wait until all threads are done creating their subgrids
#pragma omp barrier
        //  Update the neighbour borders
        updateNeighbourBorders(dim, board, end, end + 1);
    }
    double endTime = omp_get_wtime();
    printf("Elapsed Time: %lf seconds\n", endTime - startTime);
    // Check board
    checkBoard(dim, board, totalMines);
    // Write board to a file
    if (argc > 5)
    {
        FILE *fp;
        char filename[100];
        snprintf(filename, sizeof(filename), "board_parallel -nt %d -d %d.txt", nthreads, dim);
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

    printf("-----------------------------------------------------\n");
    return 0;
}