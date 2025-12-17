///*
//* 输出杨辉三角
//	written by hu ming zhu
//	 03/11/2025
// */
//#include <stdio.h>
// long int factorial(int n)
//{	
//	long int fn = 1;
//	for (int i = 2; i <= n; i++)
//	{
//		fn *=  i;
//	}
//	return fn;
//}
//	long int C(int a, int b)
//{
//	long int Cnm = factorial(a) / (factorial(b) * factorial(a - b));
//	return Cnm;
//}
//void main()
//{
//	printf("请输入行数（不宜过大）以输出杨辉三角:");
//	int n;
//	scanf_s("%d", &n);
//	printf("\n");
//	for (int i = 0; i <= n; i++)
//	{
//		for (int j = 0; j <= i; j++)
//		{
//			printf("	%ld", C(i, j));
//		}printf("\n\n");
//	}
//}
