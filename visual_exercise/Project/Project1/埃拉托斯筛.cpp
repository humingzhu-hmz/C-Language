//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
////É¸Ñ¡1-nµÄËØÊý
//int primeCount(int n)
//{
//	int count = 1;
//	int* prime = (int*)calloc(n, sizeof(int));
//	for (int i = 2; i * i <= n; i++)
//	{
//		if (!prime[i])
//		{
//			for (int j = i * i; j <= n; j += i)
//			{
//				prime[j] = 1;
//				count++;
//			}
//		}
//	}
//	return count;
//}
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	printf("%d", primeCount(n));
//	return 0;
//}