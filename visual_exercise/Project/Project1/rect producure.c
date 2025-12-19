//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <string.h>
//int **imput(int row, int col)
//{
//	int **x = (int **)malloc(row*sizeof(int *));
//	int i = 0, j = 0;
//	for (; i < row; i++)
//	{
//		x[i] = (int *)malloc(col*sizeof(int));
//		for (; j < col; j++)
//		{
//			scanf("%d", &x[i][j]);
//		}
//	}
//	return x;
//}
//int ** calculate(int **A, int **B, int Araw, int Acol, int Braw, int Bcol)
//{
//	 
//	int Craw = Araw, Ccol = Bcol;
//	int **C = (int **)malloc(Craw*sizeof(int*));
//	int i = 0;
//	for (; i < Craw; i++)
//	{
//		int j = 0;
//		C[i] = (int *)calloc(Ccol, sizeof(int));
//		for (; j < Ccol; j++)
//		{
//			int k = 0;
//			for (; k < Acol; k++)
//			{
//				C[i][j] += A[i][k] * B[k][j];
//			}
//		}
//	}
//	return C;
//}
//void freearr(int **X, int Xraw)
//{
//	int i = 0;
//	for (; i < Xraw; i++)
//	{
//		free(X[i]);
//	}
//	free(X);
//}
//int main()
//{
//	int Araw, Acol, Braw, Bcol;
//	scanf("%d %d %d %d", &Araw, &Acol, &Braw, &Bcol);
//	if (Acol != Braw)
//	{
//		printf("Error: Matrix dimensions do not match!");
//		return 0;
//	}
//	int **A = imput(Araw, Acol);
//	int **B = imput(Braw, Bcol);
//	int **C = calculate(A, B, Araw, Acol, Braw, Bcol);
//	int Craw = Araw, Ccol = Bcol;
//	int i = 0, j = 0;
//	for (; i < Craw; i++)
//	{
//		for (; j < Ccol; j++)
//		{
//			printf("%d ", C[i][j]);
//		}
//		printf("\n");
//	}
//	freearr(A, Araw);
//	freearr(B, Braw);
//	freearr(C, Craw);
//	return 0;
//}
//
//
