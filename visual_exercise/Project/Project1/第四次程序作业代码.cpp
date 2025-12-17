//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <time.h>
//int exe1(int x)
//{
//	if (x < 1)
//	{
//		return x;
//	}
//	else if (x < 15 && x >= 1)
//	{
//		return 2 * x - 1;
//	}
//	else
//	{
//		return 6 * x + pow(x, 2);
//	}
//}
//float exe2(float x, float y)
//{
//	if (x > 0 && y > 0)
//	{
//		return log(x) + log(y);
//	}
//	if (x < 0 && y>0)
//	{
//		return sin(x) + sin(y);
//	}
//	if (x < 0 && y < 0)
//	{
//		return exp(2 * x) * (1 + exp(x));
//	}
//	if (x > 0 && y < 0)
//	{
//		return (x + y);
//	}
//}
//int exe3(int n)
//{
//	int result = 0, i = 0;
//	do
//	{
//		i++;
//		result = result * 10 + n % 10;
//	} while ((n = (n / 10)) != 0);
//	printf("n是%d位数.\n",i);
//	fprintf(stdout, "逆序输出:%d", result);
//	return 0;
//}
//int exe4(int x, int y)
//{
//	if (y == 0)
//	{
//		printf("除数不能为0");
//		return 0;
//	}
//
//	int* p = (int*)calloc(2, sizeof(int));
//	if (p == NULL)
//	{
//		printf("失败");
//		return 0;
//	}
//	p[0] = x;
//	p[1] = y;
//	*(p + 1) = p[0] % p[1];
//	*(p + 0) = (p[0] - p[1]) / p[0];
//	printf("商为%d,余数为:%d", p[0], p[1]);
//	return 0;
//}
//int  exe5(int year, int month, int day)
//{
//	struct tm targettime = { 0 };
//	targettime.tm_year = 1970 - 1900;
//	targettime.tm_mon = month - 1;
//	targettime.tm_mday = day;
//	time_t times = mktime(&targettime);
//	if (times == (time_t)-1)
//	{
//		return 0;
//	}
//	int x = times / 86400;
//	printf("It's the %dth day of %d", x, year);
//	return 0;
//}
//void exe6(int a, int b, int c)
//{
//	if (a + b > c && a + c > b && b + c > a)
//	{
//		printf("能构成三角形");
//		if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a)
//		{
//			printf("且为直角三角形");
//			if (a == b || a == c || b == c)
//			{
//				printf("且为等腰直角三角形");
//			}
//		}
//
//	}
//	else
//	{
//		printf("不能构成三角形");
//	}
//}
//int exe7(int a, int b)
//{
//	int temp;
//	printf("请选择运算方式:\n1.加法\n2.减法\n3.乘法\n4.除法\n");
//	scanf_s("%d", &temp);
//	switch (temp)
//	{
//	case 1:
//		printf("结果为:%d", a + b);
//		break;
//	case 2:
//		printf("结果为:%d", a - b);
//		break;
//	case 3:
//		printf("结果为:%d", a * b);
//		break;
//	case 4:
//		if (b == 0)
//		{
//			printf("除数不能为0");
//			return 0;
//		}
//		printf("结果为:%d", a / b);
//		break;
//	default:
//		printf("选择错误");
//		break;
//	}
//}
//int exe10()
//{
//	int a[40];
//	for (int i = 0; i < 40; i++)
//	{
//		a[i] = rand() % 100 + 1;
//	}
//	for (size_t i = 0; i < 39; i++)
//	{
//		int max = (a[i] >a[i + 1])?a[i]:a[i+1];
//	}
//	fprintf(stdout, "最大值为:%d", a[0]);
//	return 0;
//}
//void exe11()
//{
//	int abc, a, b, c;
//	printf("满足条件的水仙数为:");
//	for (abc = 100; abc <= 999; abc++)
//	{
//		a = abc / 100;
//		b = (abc / 10) % 10;
//		c = abc % 10;
//		if (a * a * a + b * b * b + c * c * c == abc)
//			printf("	%d", abc);
//	}
//}
//long long int factorial(int n)
//{
//	if (n < 0) {
//		printf("错误：n不能为负数，阶乘仅定义在非负整数上\n");
//		exit(1);
//	}
//	if (n == 0 || n == 1)
//		return 1;
//	if (factorial(n - 1) > LLONG_MAX / n)
//	{
//		printf("n!数据过大溢出");
//		exit(1);
//	}
//	else
//		return factorial(n - 1) * n;
//}
//int exe12(int x)
//{
//	int i = 1;
//	float sinx = 0;
//	while (pow(x, i) / factorial(i) < pow(10, -7))
//	{
//		sinx = sinx + (pow(x, i) * pow(-1, i) / factorial(i));
//		i += 2;
//	}
//	return sinx;
//}
//void exe13()
//{
//	printf("九九乘法表:\n");
//	for (int i = 1; i <= 9; i++)
//	{
//		for (int k = 1; k <= i; k++)
//		{
//			if (k == 3 && i == 3 || k == 3 && i == 4)
//				printf("   %dx%d=%d", k, i, i * k);
//			else printf("  %dx%d=%d", k, i, i * k);
//		}
//		printf("\n");
//	}
//}
//void exe14()
//{
//	float a[10], sum = 0;
//	for (int i = 0; i < 10; i++)
//	{
//		a[i] = rand() % 100 - 50;
//		sum = sum + a[i];
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		printf("a[%d]=%.2f\n", i, a[i]);
//	}
//	printf("%f", sum);
//}
//void exe15()
//{
//	int count1=0, count2=0, count3=0;
//	int a[10];
//	for (int i = 0; i < 10; i++)
//	{
//		scanf_s("%d", &a[i]);
//		if (a[i] > 0)
//		{
//			count1++;
//		}
//		else if (a[i] < 0)
//		{
//			count2++;
//		}
//		else
//		{
//			count3++;
//		}
//	}
//	printf("正数个数为:%d\n负数个数为:%d\n零的个数为:%d", count1, count2, count3);
//}
//void exe16()
//{
//	int i = 0, e = 0;
//	while (1)
//	{
//		if (1 / factorial(i) < pow(10, -6))
//		{
//			break;
//		}
//		e = e + 1 / factorial(i);
//	}
//}
//void exe17()
//{
//	for (int i = 1; i < 26; i++)
//	{
//		printf("%d的阶乘是%lld", i,factorial(i));
//	}
//}
//void exe18(int n)
//{
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = 1; j <= i; j++)
//		{
//			printf("$ ");
//		}
//		printf("\n");
//	}
//}
//int main()
//{
//	printf("1.分段函数计算\n2.条件函数计算\n3.整数逆序输出及位数计算\n4.整数除法商和余数计算\n5.计算某日期是当年的第几天\n6.判断三边能否构成三角形及类型\n7.简单计算器\n10.数组随机数最大值\n11.输出所有水仙花数\n12.计算sinx的值\n13.打印九九乘法表\n14.数组10个元素求和\n15.统计输入10个整数中正数、负数和零的个数\n16.计算e的值\n17.计算1-25的阶乘\n18.打印n行阶梯图案\n");
//	while (1)
//	{
//		printf("\n请选择问题,按回车结束:");
//		int choice,ch;
//		if ((ch=getchar()) == '\n')
//		{
//			exit(1);
//		}
//		ungetc(ch, stdin);
//		scanf_s("%d", &choice);
//		switch (choice)
//		{
//		case 1:
//		{
//			int x;
//			printf("请输入x的值:");
//			scanf_s("%d", &x);
//			printf("结果为:%d", exe1(x));
//			break;
//		}
//		case 2:
//		{
//			float x, y;
//			printf("请输入x和y的值:");
//			scanf_s("%f %f", &x, &y);
//			printf("结果为:%f", exe2(x, y));
//			break;
//		}
//		case 3:
//		{
//			int n;
//			printf("请输入一个整数:");
//			scanf_s("%d", &n);
//			exe3(n);
//			break;
//		}
//		case 4:
//		{
//			int x, y;
//			printf("请输入被除数和除数:");
//			scanf_s("%d %d", &x, &y);
//			exe4(x, y);
//			break;
//		}
//		case 5:
//		{
//			int year, month, day;
//			printf("请输入年月日:");
//			scanf_s("%d %d %d", &year, &month, &day);
//			exe5(year, month, day);
//			break;
//		}
//		case 6:
//		{
//			int a, b, c;
//			printf("请输入三边长:");
//			scanf_s("%d %d %d", &a, &b, &c);
//			exe6(a, b, c);
//			break;
//		}
//		case 7:
//		{
//			int a, b;
//			printf("请输入两个整数:");
//			scanf_s("%d %d", &a, &b);
//			exe7(a, b);
//			break;
//		}
//		case 10:
//		{
//			exe10();
//			break;
//		}
//		case 11:
//		{
//			exe11();
//			break;
//		}
//		case 12:
//		{
//			int x;
//			printf("请输入x的值(弧度制):");
//			scanf_s("%d", &x);
//			printf("sinx的值为:%d", exe12(x));
//			break;
//		}
//		case 13:
//		{
//			exe13();
//			break;
//		}
//		case 14:
//		{
//			exe14();
//			break;
//		}
//		case 15:
//		{
//			exe15();
//			break;
//		}
//		case 16:
//		{
//			exe16();
//			break;
//		}
//		case 17:
//		{
//			exe17();
//			break;
//		}
//		case 18:
//		{
//			int n;
//			printf("请输入n的值:");
//			scanf_s("%d", &n);
//			exe18(n);
//			break;
//		}
//		}
//	}
//}
