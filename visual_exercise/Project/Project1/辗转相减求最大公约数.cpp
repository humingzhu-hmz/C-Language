//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//int gac1(int a, int b)
//{
//	return a - b == 0 ? b : gac1(b > a - b ? b : a - b, b <= a - b ? b : a - b);
//}
//int gac2(int a, int b)
//{
//	while (a - b != 0)
//	{
//		int c = b > a - b ? b : a - b;
//		int d = b <= a - b ? b : a - b;
//		a = c;
//		b = d;
//	}
//	return b;
//}
//int main()
//{
//	int a, b;
//	scanf("%d%d", &a, &b);
//	int max = a > b ? a : b;
//	int min = a <= b ? a : b;
//	printf("%d\n",gac1(max, min));
//	printf("%d", gac2(max, min));
//}