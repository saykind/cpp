#include <iostream>
#include <cstdlib>
#define nl '\n'
using namespace std;

class matrix {
public:
	int m;	// rows
	int n;	// columns
	int size;
	double *data;
	matrix (int rows, int columns);
	matrix (matrix *M);
	matrix (const matrix & M);
	double *operator[] (int i);
	double det(void);
};

matrix::matrix(int rows, int columns) {
	m = rows; n = columns; size = m*n;
	data = (double *) malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) data[i] = .0;
};
matrix::matrix(matrix *M) {		// Copy pointer constructor
	if (M != NULL) {
		m = M->m; n = M->n; size = m*n;
		data = (double *) malloc(size*sizeof(double));
		for (int i = 0; i < size; i++) data[i] = M->data[i]; 
	} else {cout << "Got NULL\n";}
};
matrix::matrix(const matrix &M) {		// Copy constructor
	m = M.m; n = M.n; size = m*n;
	data = (double *) malloc(size*sizeof(double));
	for (int i = 0; i < size; i++) data[i] = M.data[i];
};
ostream &operator << (ostream &stream, matrix &M) {
	int i = 0, j = 0;
	for (i = 0; i < M.m; i++) {
		for (j = 0; j < M.n; j++)
			stream << M.data[i*M.n+j] << ' ';
		cout << nl;
	}
	return stream;
}
matrix operator* (const matrix &M, double k) {
	matrix *A;
	A = (matrix *) malloc(sizeof(matrix));
	A->m = M.m;
	A->n = M.n;
	A->size = A->m*A->n;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->m; i++) {
		for (j = 0; j < A->n; j++)
			A->data[i*A->n+j] = M.data[i*A->n+j]*k;
	}
	return *A;
}
matrix operator/ (const matrix &M, double k) {
	matrix *A;
	A = (matrix *) malloc(sizeof(matrix));
	A->m = M.m;
	A->n = M.n;
	A->size = A->m*A->n;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->m; i++) {
		for (j = 0; j < A->n; j++)
			A->data[i*A->n+j] = M.data[i*A->n+j]/k;
	}
	return *A;
}
/*
void operator= (matrix &A,const matrix &B) {
	if ((B.m > A.m) || (B.n > A.n)) {return;}
	int i, j;
	for (i = 0; i < A.m; i++) {
		for (j = 0; j < A.n; j++)
			A.data[i*A.n+j] = B.data[i*A.n+j];
	}
}*/
matrix *operator* (const matrix &B, const matrix &C) {
	if (B.n != C.m) {return NULL;}
	matrix *A;
	A = (matrix *) malloc(sizeof(matrix));
	A->m = B.m;
	A->n = C.n;
	A->size = A->m*A->n;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j, l, k;
	double s;
	for (i = 0; i < A->m; i++) {
		for (j = 0; j < A->n; j++) {
			s = 0.0;
			for (k = 0; k < C.m; k++) 
				s += B.data[i*B.n+k]*C.data[k*C.n+j];
			A->data[i*A->n+j] = s;
		}
	}
	return A;
}
matrix *operator+ (const matrix &B, const matrix &C) {
	if ((B.n != C.n) || (B.m != C.m)) {return NULL;}
	matrix *A;
	A = (matrix *) malloc(sizeof(matrix));
	A->m = B.m;
	A->n = B.n;
	A->size = A->m*A->n;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->m; i++) {
		for (j = 0; j < A->n; j++) {
			A->data[i*A->n+j] = B.data[i*A->n+j] + C.data[i*A->n+j];
		}
	}
	return A;
}
matrix *operator- (const matrix &B, const matrix &C) {
	if ((B.n != C.n) || (B.m != C.m)) {return NULL;}
	matrix *A;
	A = (matrix *) malloc(sizeof(matrix));
	A->m = B.m;
	A->n = B.n;
	A->size = A->m*A->n;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->m; i++) {
		for (j = 0; j < A->n; j++) {
			A->data[i*A->n+j] = B.data[i*A->n+j] - C.data[i*A->n+j];
		}
	}
	return A;
}
matrix *operator~ (const matrix &B) {
	matrix *A;
	A = (matrix *) malloc(sizeof(matrix));
	A->m = B.n;
	A->n = B.m;
	A->size = A->m*A->n;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->m; i++) {
		for (j = 0; j < A->n; j++) {
			A->data[i*A->n+j] = B.data[j*B.n+i];
		}
	}
	return A;
}
double *matrix::operator[] (int i) {
	return (data+i);
}
double *sub(double *data, int M, int N, int i, int j) {
	double *d =  (double *) malloc((M-1)*(N-1)*sizeof(double));
	int k, l, ii = 0, jj = 0;
	for (k = 0; k < M-1; k++) {
		if (k==i) {ii = 1;}
		for (l = 0; l < N-1; l++) {
			if (l==j) {jj = 1;}
			*(d+k*(N-1)+l) = *(data+(k+ii)*N+(l+jj));
		}
		jj = 0;
	}
	return d;
}
double det(double *data, int M, int N) {
	if (M != N) return -1.0;
	if (M == 1) return *(data+0);
	int i;
	double s= 0.0;
	for (i = 0; i < M; i++) {
		if ((i%2)==0) {s += *(data+i*N)*det(sub(data,M,N,i,0),M-1,N-1);}
		else {s += *(data+i*N)*(-1)*det(sub(data,M,N,i,0),M-1,N-1);}
	}
	return s;
}
double matrix::det(void) {
	if (m != n) return -1.0;
	if (m == 1) return *(data);
	int i;
	double s= 0.0;
	for (i = 0; i < m; i++) {
		if ((i%2)==0) {s += *(data+i*n)*det(sub(data,m,n,i,0),m-1,n-1);}
		else {s += *(data+i*n)*(-1)*det(sub(data,m,n,i,0),m-1,n-1);}
	}
	return s;
}
	


int main(void) {
	int i, j;
	matrix A(3,3);
	for (i = 0; i < A.m; i++) {
		for (j = 0; j < A.n; j++)
			A.data[i*A.n+j] = 1.0+j%3+i%2;
	}
	matrix B(3,2);
	for (i = 0; i < B.m; i++) {
		for (j = 0; j < B.n; j++)
			B.data[i*B.n+j] = i*B.n+j;
	}
	matrix D(A*B);
	matrix G(D+B);
	matrix H(G-B);
	matrix F(~H);
	cout << A << nl << B << nl << D << nl << G << nl << H << nl << F << nl << nl;
	
	*A[2] = 4.0;
	cout << A << "\nDet = " << A.det() << nl;

	
	return 0;
}
