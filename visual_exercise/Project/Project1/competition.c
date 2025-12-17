//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//
//typedef struct RNG
//{
//	unsigned long long seed;
//}RNG;
//static const long long A = 151;
//static const long long C = 1ULL << 2;
//static const long long range = 1e9;
//static const long long M = 759225;
//void init_SEED(RNG* rng, unsigned long long s)
//{
//	rng->seed = s;
//	if (rng->seed == 0)
//		rng->seed = time(NULL);
//}
//int next_INT(RNG* rng)
//{
//	rng->seed = (A * rng->seed + C) % M;
//	return (int)(rng->seed % range) + 1;
//}
//long int maxnum(long int i, long int j)
//{
//	return i > j ? i : j;
//}
//long int F(int i,int j,int **f,int **w)
//{
//	if (f[i][j])
//	{
//		return f[i][j];
//	}
// else if(i==0&&j==0)
// {
//	return f[i][j];
// }
//	else if (i == 0)
//	{
//		f[i][j] = F(i,j-1,f,w) + w[i][j];
//		return f[i][j];
//	}
//	else if (j == 0)
//	{
//		f[i][j] = F(i-1,j,f,w) + w[i][j];
//		return f[i][j];
//	}
//	else
//	{
//		f[i][j] = maxnum(F(i - 1, j, f, w), F(i, j - 1, f, w)) + w[i][j];
//		return f[i][j];
//	}
//}
//int main( )
//{
//	int a;
//	int n, m;
//	RNG* rng=(RNG*)malloc(sizeof(RNG));
//	unsigned long long seed;
//	scanf("%d %d %lld", &n, &m, &seed);
//	init_SEED(rng, seed);
//	int** w = (int**)malloc(n * sizeof(int*));
//	int** f = (int**)malloc(n * sizeof(int*));
//	for (int i = 0; i < n; i++)
//	{
//		w[i] = (int*)malloc(m * sizeof(int));
//		f[i] = (int*)calloc(m ,sizeof(long int));
//	}
//	for (int k = 1; k <= (n * m); k++)
//	{
//		w[(k - 1) / m][(k - 1) % m] = next_INT(rng);
//	}
//	f[0][0] = w[0][0];
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < m; j++)
//		{
//			printf("%5d ", w[i][j]);
//		}
//		printf("\n");
//	}
//	printf("--------------------------------------");
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < m; j++)
//		{
//			printf("%5ld ",F(i,j,f,w));
//		}
//		printf("\n");
//	}
//	printf("--------------------------------------");
//	long int result = F(n-1, m-1, f, w);
//	printf("%ld ", result);
//	for (int i = 0; i < n; i++)
//	{
//		free(w[i]);
//		free(f[i]);
//	}
//	free(w);
//	free(f);
//	free(rng);
//	return 0;
//}