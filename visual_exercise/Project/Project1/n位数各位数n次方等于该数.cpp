//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//void main()
//{
//	long int n, i, n = 0 ;
//	printf("请输入一个整数(可负）:");
//	scanf_s("%ld", &n);
//	for (i = 10; i <= 1e9; i *= 10)
//	{
//		n++;
//		if (llabs(n)/i==0)
//		{
//			break;
//		}
//	}
//	int arr[11];
//	  long int sum = 0;
//	  for (i = 0; i <= n - 1; i++)
//	  {
//		  arr[i] = (int)(llabs(n) / pow(10, i)) % 10;
//		  int a = pow(arr[i], n);
//		  sum += a;
//	  }
//	  printf("各位数的%d次方之和为	%ld\n",n, sum);
//	  if (llabs(n) == sum)
//	  {
//		  printf("%ld是armstrong数\n", n);
//	  }
//	  else printf("%ld不是armstrong数\n", n);
//	  printf("与n同位数的armstrong还有:");
//	  for ( i = pow(10, n - 1); i <= pow(10, n) - 1; i++)
//	  {
//		  for (int m = 0; m <= n - 1; m++)
//		  {
//			  arr[m] = (int)(llabs(i) / pow(10, m)) % 10;
//		  }
//		  int sum = 0;
//		  for (int m = 0; m <= n - 1; m++)
//		  {
//			  int a = pow(arr[m], n);
//			  sum += a;
//		  }
//		  if (llabs (i) == sum)
//		  {
//			  printf("	%ld", i);
//		  }
//	  }
//
//}
