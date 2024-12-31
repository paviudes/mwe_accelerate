#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <Accelerate/Accelerate.h>
#include "clapack.h"
#include "linalg.h"

void ZEigH(double complex **mat, int dim, double complex *eigvals, int iseigvecs, double complex **eigvecs){
	/*
		Compute the eigenvalues and the right-eigenvectors of a complex Hermitian matrix.
		We will use the LAPACK routine zheev to compute the eigenvalues. The LAPACK function is defined as follows.
		There is a C wrapper to the LAPACK routine:
		https://software.intel.com/sites/products/documentation/doclib/mkl_sa/11/mkl_lapack_examples/lapacke_zheev_row.c.htm
		The eigenvalues of a Hermitian matrix are real, however, we will store them in a complex array, for compatibility.
		We need this function for Hermitian matrices because th generic eigensolver has issues.
		See: http://icl.cs.utk.edu/lapack-forum/archives/lapack/msg01352.html.
	*/

	int n = dim, lda = dim, info;
	double w[dim];
	double complex a[dim * dim];
	int i, j;
	for (i = 0; i < dim; i ++){
		for (j = 0; j < dim; j ++){
			a[i * dim + j] = mat[i][j];
		}
	}
	for (i = 0; i < dim; i ++){
		for (j = i + 1; j < dim; j ++){
			a[i * dim + j] = 0 + 0 * I;
		}
	}

	info = LAPACKE_zheev(LAPACK_ROW_MAJOR, 'V', 'L', n, a, lda, w);
	if (info > 0)
		printf("Eigenvalues %d to %d did not converge properly.\n", info, dim);
	else if (info < 0)
		printf("Error in the the %d-th input parameter.\n", -1 * info);
	else{
		for (i = 0; i < dim; i ++){
			eigvals[i] = w[i] + 0 * I;
			if (iseigvecs == 1){
				for (j = 0; j < dim; j ++)
					eigvecs[i][j] = a[i * dim + j];
			}
		}
	}
}