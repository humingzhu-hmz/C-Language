//#include <stdio.h>
//#include <math.h>
//#define _CRT_SECURE_NO_WARNINGS
//int sumofproperdivisions(int x)
//{
//
//	int k = (int)sqrt(x); 
//	int sum = 1;
//	for (int m = 2; m <= k; m++)
//	{
//		if (x % m == 0)
//		{
//			if (m != x / m)
//				sum += m + x / m;
//			else sum += m;
//		}
//	}return sum;
//}
//void main( )
//{
//	printf("2-range的亲和数对为:");
//	for ( int x = 2; x <= range; x++)
//	{
//		int y = sumofproperdivisions(x);
//		if (x < y && sumofproperdivisions(y) == x)
//		{
//			printf("	(%d,%d)", x, y);
//		}
//	}
//}