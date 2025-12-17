//#include <stdio.h>
//void way1(int a, int b)
//{
//	while (1)
//	{
//		if(a>b)
//		{
//			a = a - b;
//		}
//		else if (b==a)
//		{
//			printf("%d", a);
//			break;
//		}
//		if (a < b)
//		{
//			b = b - a;
//		}
//		else if (a == b)
//		{
//			printf("%d", b);
//			break;
//		}
//	}
//}
//void way2(int a, int b)
//{
//	if (a < b)
//	{
//		int t = b;
//		b = a;
//		a = t;
//	}
//	while (1)
//	{
//		if (a % b == 0)
//		{
//			printf("%d", b);
//			break;
//		}
//		int k = a % b;
//		a = b;
//		b = k;
//		
//	}
//}
//void way3(int a, int b)
//{
//	int maxfosterofpublic=1;
//	for (int i = 1; i <= (a <= b ? a : b); i++)
//	{
//		if (a % i == 0 && b % i == 0)
//			maxfosterofpublic = i;
//	}
//	printf("%d", maxfosterofpublic);
//}
//void main()
//{
//	int a, b;
//	printf("请输入两个正整数以求其最大公约数:");
//	scanf_s("%d %d", &a, &b);
//	if (a <= 0 || b <= 0)
//	{
//		printf("输入有误");
//	}
//	way3(a, b);
//}