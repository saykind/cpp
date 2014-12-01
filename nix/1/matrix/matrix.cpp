#include <iostream>
#include <cstdlib>
#define nl '\n'
using namespace std;


class Matrix {
public:
	int rows;		// m
	int columns;	// n
	int size;
	double *data;
	Matrix (int r, int c);
	Matrix (Matrix *M);
	Matrix (const Matrix & M);
	double *operator[] (int i);
	double D(void);
//	Matrix operator* (const Matrix &M, double k);
};
Matrix::Matrix(int r, int c) {	// Constructor
	rows = r;
	columns = c;
	size = rows*columns;
	data = (double *) malloc(size*sizeof(double));
	int i = 0;
	for (i = 0; i < size; i++) data[i] = .0;
};
Matrix::Matrix(Matrix *M) {		// Copy pointer constructor
	if (M != NULL) {
	rows = M->rows;
	columns = M->columns;
	size = rows*columns;
	data = (double *) malloc(size*sizeof(double));
	int i = 0;
	for (i = 0; i < size; i++) data[i] = M->data[i]; } else {
		cout << "Got NULL\n";}
};
Matrix::Matrix(const Matrix &M) {		// Copy constructor
	rows = M.rows;
	columns = M.columns;
	size = rows*columns;
	data = (double *) malloc(size*sizeof(double));
	int i = 0;
	for (i = 0; i < size; i++) data[i] = M.data[i];
};
ostream &operator << (ostream &stream, Matrix &M) {
	int i = 0, j = 0;
	for (i = 0; i < M.rows; i++) {
		for (j = 0; j < M.columns; j++)
			stream << M.data[i*M.columns+j] << ' ';
		cout << nl;
	}
	return stream;
}
Matrix operator* (const Matrix &M, double k) {
	Matrix *A;
	A = (Matrix *) malloc(sizeof(Matrix));
	A->rows = M.rows;
	A->columns = M.columns;
	A->size = A->rows*A->columns;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->rows; i++) {
		for (j = 0; j < A->columns; j++)
			A->data[i*A->columns+j] = M.data[i*A->columns+j]*k;
	}
	return *A;
}
Matrix operator/ (const Matrix &M, double k) {
	Matrix *A;
	A = (Matrix *) malloc(sizeof(Matrix));
	A->rows = M.rows;
	A->columns = M.columns;
	A->size = A->rows*A->columns;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->rows; i++) {
		for (j = 0; j < A->columns; j++)
			A->data[i*A->columns+j] = M.data[i*A->columns+j]/k;
	}
	return *A;
}
/*
void operator= (Matrix &A,const Matrix &B) {
	if ((B.rows > A.rows) || (B.columns > A.columns)) {return;}
	int i, j;
	for (i = 0; i < A.rows; i++) {
		for (j = 0; j < A.columns; j++)
			A.data[i*A.columns+j] = B.data[i*A.columns+j];
	}
}*/
Matrix *operator* (const Matrix &B, const Matrix &C) {
	if (B.columns != C.rows) {return NULL;}
	Matrix *A;
	A = (Matrix *) malloc(sizeof(Matrix));
	A->rows = B.rows;
	A->columns = C.columns;
	A->size = A->rows*A->columns;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j, l, k;
	double s;
	for (i = 0; i < A->rows; i++) {
		for (j = 0; j < A->columns; j++) {
			s = 0.0;
			for (k = 0; k < C.rows; k++) 
				s += B.data[i*B.columns+k]*C.data[k*C.columns+j];
			A->data[i*A->columns+j] = s;
		}
	}
	return A;
}
Matrix *operator+ (const Matrix &B, const Matrix &C) {
	if ((B.columns != C.columns) || (B.rows != C.rows)) {return NULL;}
	Matrix *A;
	A = (Matrix *) malloc(sizeof(Matrix));
	A->rows = B.rows;
	A->columns = B.columns;
	A->size = A->rows*A->columns;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->rows; i++) {
		for (j = 0; j < A->columns; j++) {
			A->data[i*A->columns+j] = B.data[i*A->columns+j] + C.data[i*A->columns+j];
		}
	}
	return A;
}
Matrix *operator- (const Matrix &B, const Matrix &C) {
	if ((B.columns != C.columns) || (B.rows != C.rows)) {return NULL;}
	Matrix *A;
	A = (Matrix *) malloc(sizeof(Matrix));
	A->rows = B.rows;
	A->columns = B.columns;
	A->size = A->rows*A->columns;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->rows; i++) {
		for (j = 0; j < A->columns; j++) {
			A->data[i*A->columns+j] = B.data[i*A->columns+j] - C.data[i*A->columns+j];
		}
	}
	return A;
}
Matrix *operator~ (const Matrix &B) {
	Matrix *A;
	A = (Matrix *) malloc(sizeof(Matrix));
	A->rows = B.columns;
	A->columns = B.rows;
	A->size = A->rows*A->columns;
	A->data = (double *) malloc(A->size*sizeof(double));
	int i, j;
	for (i = 0; i < A->rows; i++) {
		for (j = 0; j < A->columns; j++) {
			A->data[i*A->columns+j] = B.data[j*A->columns+i];
		}
	}
	return A;
}
double *Matrix::operator[] (int i) {
	return (data+i);
}
double *sub(double *data, int m, int n, int i, int j) {
	double *d =  (double *) malloc((m-1)*(n-1)*sizeof(double));
	int k, l, ii = 0, jj = 0;
	for (k = 0; k < m-1; k++) {
		if (k==i) {ii = 1;}
		for (l = 0; l < n-1; l++) {
			if (l==j) {jj = 1;}
			*(d+k*(n-1)+l) = *(data+(k+ii)*n+(l+jj));
		}
		jj = 0;
	}
	return d;
}
double det(double *data, int m, int n) {
	if (m != n) return -1.0;
	if (m == 1) return *(data+0);
	int i;
	double s= 0.0;
	for (i = 0; i < m; i++) {
		if ((i%2)==0) {s += *(data+i*n)*det(sub(data,m,n,i,0),m-1,n-1);}
		else {s += *(data+i*n)*(-1)*det(sub(data,m,n,i,0),m-1,n-1);}
	}
	return s;
}
double Matrix::D(void) {
	return det(data, rows, columns);
}




