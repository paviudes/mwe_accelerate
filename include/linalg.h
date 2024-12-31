#ifndef LINALG_H
#define LINALG_H

#include <complex.h>

/*
	Compute the eigenvalues and the right-eigenvectors of a complex Hermitian matrix.
	We will use the LAPACK routine zheev to compute the eigenvalues. The LAPACK function is defined as follows.
	There is a C wrapper to the LAPACK routine:
	https://software.intel.com/sites/products/documentation/doclib/mkl_sa/11/mkl_lapack_examples/lapacke_zheev_row.c.htm
*/
extern void ZEigH(double complex **mat, int dim, double complex *eigvals, int iseigvecs, double complex **eigvecs);

#endif /* LINALG_H */