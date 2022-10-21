#!/bin/bash
#SBATCH --time=00:05:00
#SBATCH --account=mcs
gcc -o minesweeper_parallel -fopenmp minesweeper_parallel.c -O2
gcc minesweeper.c -o minesweeper -O2
./minesweeper -d 10 -f
./minesweeper_parallel -nt 5 -d 10 -f
./minesweeper -d 50 -f
./minesweeper_parallel -nt 10 -d 50 -f
./minesweeper -d 100 -f
./minesweeper_parallel -nt 20 -d 100 -f
./minesweeper -d 200 -f
./minesweeper_parallel -nt 25 -d 200 -f
./minesweeper -d 500 -f
./minesweeper_parallel -nt 25 -d 500 -f
./minesweeper -d 600 -f
./minesweeper_parallel -nt 30 -d 600 -f
./minesweeper -d 700 -f
./minesweeper_parallel -nt 35 -d 700 -f
./minesweeper -d 800 -f
./minesweeper_parallel -nt 40 -d 800 -f
./minesweeper -d 900 -f
./minesweeper_parallel -nt 45 -d 900 -f
./minesweeper -d 1000 -f
./minesweeper_parallel -nt 50 -d 1000 -f
./minesweeper -d 1100 -f
./minesweeper_parallel -nt 55 -d 1100 -f
./minesweeper -d 1200 -f
./minesweeper_parallel -nt 60 -d 1200 -f
./minesweeper -d 1300 -f
./minesweeper_parallel -nt 65 -d 1300 -f
./minesweeper -d 1400 -f
./minesweeper_parallel -nt 70 -d 1400 -f
./minesweeper -d 1500 -f
./minesweeper_parallel -nt 75 -d 1500 -f
./minesweeper -d 1600 -f
./minesweeper_parallel -nt 80 -d 1600 -f
