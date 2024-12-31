#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "linalg.h"

int main()
{
	/*
	This function is simply to test all the C functions in the converted/ folder.
	*/
	clock_t begin = clock();
	printf("acc: source last compiled on %s at %s.\n", __DATE__, __TIME__);

	// Initialize memory with a random matrix
	double complex **mat = malloc(sizeof(double complex) * 4);
	double complex **eigvecs = malloc(sizeof(double complex) * 4);
	for (int i = 0; i < 4; i ++){
		mat[i] = malloc(sizeof(double complex) * 4);
		eigvecs[i] = malloc(sizeof(double complex) * 4);
		for (int j = 0; j < 4; j ++)
			mat[i][j] = (double) rand() / RAND_MAX;
	}
	double complex *eigvals = malloc(sizeof(double) * 4);

	// Force the matrix to be Hermitian: A -> A + A^dagger
	for (int i = 0; i < 4; i ++)
		for (int j = 0; j < 4; j ++)
			mat[i][j] = mat[i][j] + conj(mat[i][j]);

	printf("Matrix:\n");
	for (int i = 0; i < 4; i ++){
		printf("(%g + i %g)", creal(mat[i][0]), cimag(mat[i][0]));
		for (int j = 1; i < 4; i ++)
			printf(" (%g + i %g)", creal(mat[i][j]), cimag(mat[i][j]));
		printf("\n");
	}
	printf("=========\n");
	
	ZEigH(mat, 4, eigvals, 1, eigvecs);

	printf("Eigenvalues\n");
	for (int i = 0; i < 4; i ++){
		printf("(%g + i %g) ", creal(eigvals[i]), cimag(eigvals[i]));
	}
	printf("=========\n");
	printf("Eigenvectors\n");
	for (int i = 0; i < 4; i ++){
		printf("v1\n");
		for (int j = 0; j < 4; j ++)
			printf("(%g + i %g) ", creal(eigvecs[i][j]), cimag(eigvecs[i][j]));
		printf("\n");
	}
	printf("=========\n");

	// Free memory
	for (int i = 0; i < 4; i ++){
		free(mat[i]);
		free(eigvecs[i]);
	}
	free(mat);
	free(eigvecs);
	free(eigvals);

	clock_t end = clock();
	double runtime = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("***********\n");
	printf("All testing done in %d seconds.\n", (int) runtime);
	printf("***********\n");
}