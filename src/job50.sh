#!/bin/bash
#SBATCH --time=00:05:00
#SBATCH --account=mcs
gcc -o minesweeper_parallel -fopenmp minesweeper_parallel.c -O2
gcc minesweeper.c -o minesweeper -O2
./minesweeper -d 500
./minesweeper_parallel -nt 50 -d 500
./minesweeper -d 1000
./minesweeper_parallel -nt 50 -d 1000
./minesweeper -d 1500
./minesweeper_parallel -nt 50 -d 1500
./minesweeper -d 2000
./minesweeper_parallel -nt 50 -d 2000
./minesweeper -d 2500
./minesweeper_parallel -nt 50 -d 2500
./minesweeper -d 3000
./minesweeper_parallel -nt 50 -d 3000
./minesweeper -d 3500
./minesweeper_parallel -nt 50 -d 3500
./minesweeper -d 4000
./minesweeper_parallel -nt 50 -d 4000
./minesweeper -d 4500
./minesweeper_parallel -nt 50 -d 4500
./minesweeper -d 5000
./minesweeper_parallel -nt 50 -d 5000
./minesweeper -d 5500
./minesweeper_parallel -nt 50 -d 5500
./minesweeper -d 6000
./minesweeper_parallel -nt 50 -d 6000
./minesweeper -d 7000
./minesweeper_parallel -nt 50 -d 7000
./minesweeper -d 8000
./minesweeper_parallel -nt 50 -d 8000
./minesweeper -d 9000
./minesweeper_parallel -nt 50 -d 9000
./minesweeper -d 10000
./minesweeper_parallel -nt 50 -d 10000
./minesweeper -d 11000
./minesweeper_parallel -nt 50 -d 11000
./minesweeper -d 12000
./minesweeper_parallel -nt 50 -d 12000