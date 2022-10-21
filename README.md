**Generating the minesweeper board in parallel using OpenMP. Comparing the time to generate the board in parallel compared to serial progamming.**

**Compilation of Serial Program**  
gcc minesweeper.c -o minesweeper -O2  

**Command Line Execution for Serial Program**  
./minesweeper -d <dimension (int)> -f (Optional argument for file output of board)  

**Compilation of Parallel Program**  
gcc -o minesweeper_parallel -fopenmp minesweeper_parallel.c -O2  

**Command Line Execution for Parallel Program**
./minesweeper_parallel -nt <threads (int)> -d <dimension (int)> -f (Optional argument for file
output of board)  