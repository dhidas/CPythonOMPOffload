#!/bin/bash -e

#SBATCH -A m2810
#SBATCH -N 1
#SBATCH -C gpu
#SBATCH --gres=gpu:1
#SBATCH -t 00:01:00
#SBATCH -p debug
#SBATCH --job-name=nvtest

srun -n 1 nvprof ./mymain3
