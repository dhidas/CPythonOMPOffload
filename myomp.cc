#include "myomp.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 100

int const n = N;
int const m = N;

float A[N][N];
float Anew[N][N];
float error = 1;
float tol = 1e-5;
float this_error;

int iter_max = int(1e19);
int iter = 0;

int Offload ()
{

  printf("There are %d devices\n", omp_get_num_devices());

  for (int j = 1; j < n - 1; ++j) {
    for (int i = 1; i < m - 1; ++i) {
      A[j][i] = 0;
    }
  }

  for (int j = 0; j < n; ++j) {
    A[j][0] = 1;
    A[j][N-1] = 0;
  }
  for (int i = 0; i < n; ++i) {
    A[0][i] = 1;
    A[N-1][i] = 2;
  }


  while (error > tol && iter < iter_max) {
    error = 0.0;

#pragma omp target teams distribute parallel for map(error)
      for (int j = 1; j < n - 1; ++j) {
        for (int i = 1; i < m - 1; ++i) {
          Anew[j][i] = 0.25 * (A[j][i+1] + A[j][i-1] + A[j-1][i] + A[j+1][i]);
          this_error = Anew[j][i] - A[j][i];
          if (this_error < 0) {
            this_error *= -1;
          }
          if (this_error > error) {
            error = this_error;
          }
        }
      }


#pragma omp target teams distribute parallel for
      for (int j = 1; j < n - 1; ++j) {
        for (int i = 1; i < m - 1; ++i) {
          A[j][i] = Anew[j][i];
        }
      }
    if (iter++ % 100 == 0) {
      printf("iter: %5d, error: %f\n", iter, error);
    }

  }

  return 123;
}
