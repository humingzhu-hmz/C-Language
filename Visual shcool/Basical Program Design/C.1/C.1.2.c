//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//int figures(int n)
//{
//	int i = 1;
//	for (; pow(10, i) <= n; i++);
//	return i;
//}
//
//bool selfnums(int n)
//{
//	int nlenth = figures(n), power = 1;
//	for (int i = 1; i <= nlenth; i++)
//	{
//		power *= 10;
//	}
//	return (n * n) % power==n;
//}
//
//int main()
//{
//	int n;
//	printf("please iuput a number:");
//	scanf("%d", &n);
//	if (n == 0)
//	{
//		printf("This number is Self-locking number.");
//		return 0;
//	}
//	if (selfnums(n))
//	{
//		printf("the number's square is:%d\n",n*n);
//		printf("This number is Self-locking number.");//lock :Ëø
//	}
//	else
//	{
//		printf("the number's square is:%d\n", n*n);
//		printf("This number isn't Self-locking number.");
//	}
//	return 0;
//}