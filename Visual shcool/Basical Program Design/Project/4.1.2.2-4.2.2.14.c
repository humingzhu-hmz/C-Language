//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
//#include <math.h>
//void exe4_1_2_2 ( )
//{
//	printf("**************\n");
//		printf("\n");
//	printf("	very Good!\n");
//	printf("\n");
//	printf("**************\n");
//}
//
//void exe4_1_2_3( )
//{
//	int a = 10, b = 20, c = 30, d, sum;
//	sum = a + b * c;
//	a = c; d = a + c;
//	printf("sum=%d, d=%d",sum,d);
//}
//void exe4_1_2_4( )
//{
//	int num1, num2, num3;
//	printf("计算三个整数平均数及乘积，请输入三个整数:");
//	scanf_s("%d %d %d", &num1, &num2, &num3);
//	double average = (num1 + num2 + num3) / 3.0;
//	int product = (num1 * num2 * num3);
//	printf(" 平均数:%f\n        乘  积:%d\n", average, product);
//}
//void exe4_1_2_5( )
//{
//	int  a = 70, b = 89, c = 65, d = 100, e = 78;
//	printf("五名学生成绩分别为70，89，65，100，78 。 ");
//	double avg = (a + b + c + d + e) / 5.0;
//	printf("其平均成绩为:%f\n", avg);
//}
//void exe4_1_3_1( )
//{
//	int x, y;
//	printf("计算y=（x-10）^3,请输入一个整数:");
//	scanf("%d", &x);
//	y = pow(x - 10, 3);
//	printf("	y=%d\n", y);
//}
//void exe4_1_3_2( )
//{
//	int i1, i2=1000;
//	{
//		i2 = 100;
//		printf("i2=%d", i2);
//	}
//	i1 = i2;
//	printf("	i1=%d\n", i1);
//}
//void exe4_1_3_3( )
//{
//	int x, y, z;
//	scanf("%d%d", &y, &z);
//	x = 0;
//	z = x + y;
//	printf("z=%d\n", z);
//}
//void exe4_1_3_4( )
//{	float y, z, x=3.5, a=5.5;
//	scanf("%f", &z);
//	y = x + z;
//	printf("a=%f,x=%f,y=%f\n", a, x, y);
//}
//void exe4_1_3_5( )
//{
//	char ch;
//	while ((ch = getchar()) != '\n');
//	{
//
//	}
//	printf("For hr's a jolly good fellow!\n");
//	printf("which nobody can deny\n");
//	printf("For hr's a jolly good fellow!\n");
//}
//void exe4_2_2_2( )
//{
//	char ch1, ch2;
//	ch1 = 97; ch2 = 98;
//	printf("ch1=%c,ch2=%c\n", ch1, ch2);
//	printf("ch1=%d,ch2=%d\n", ch1, ch2);
//	ch1 = ch1 - 32; ch2 = ch2 - 32;
//	printf("ch1=%c,ch2=%c\n", ch1, ch2);
//	printf("ch1=%d,ch2=%d\n", ch1, ch2);
//}
//void exe4_2_2_3( )
//{
//	int i, m, n;
//	i = 5;
//	printf("brfore i++ i=%d\n", i);
//	m = i++;
//	printf("after i++ i=%d\n", i);
//	n = ++i;
//	printf("after++i i=%d m=%d n=%d\n", i, m, n);
//}
//void exe4_2_2_4( )
//{
//	int a = 3;
//	printf("%d\n", a + (a -= a * a));
//}
//void exe4_2_2_5( )
//{
//	int n, d1, d2, d3, d4;
//	printf("反序输出四位数:");
//	scanf("%d\n", &n);
//	d1 = n % 10;
//	d2 = (n % 100) / 10;
//	d3 = (n / 100) / 10;
//	d4 = (n / 1000);
//	int x = (d1 * 1000 + d2 * 100 + d3 * 10 + d4);
//	printf("	%d\n", x);
//}
//void exe4_2_2_6( )
//{
//	int a = 12, n = 5;
//	a += a;
//	printf("%d\n", a);
//	a -= 2;
//	printf("%d\n", a);
//	a *= 2 + 3;
//	printf("%d\n",a );
//	a %= (n % 2);
//	printf("%d\n", a);
//	a /= a + a;
//	printf("%d\n", a);
//	a += a -= a *= a;
//	printf("%d\n", a);
//}
//
//void exe4_2_2_7( )
//{
//	int a = 2, b = 3, x = 3.5, y = 2.5;
//	printf("%f\n", (float)(a + b) / 2 + (int)x % (int)y);
//	printf("%f\n", (float)a + b / 2 + (int)x % (int)y );
//	printf("%f\n", (float)(a + b / 2) + (int)x % (int)y);
//}
//void exe4_2_2_8( )
//{
//	int x;
//	printf("ASCLL码值转对应字符，任意输入一个ASCLL码值(如66):");
//	scanf("%d", &x);
//	printf("对应字符:%c\n", x);
//}
//void exe4_2_2_9( )
//{
//	int x, y, z;
//	printf("组合数，请输入三个一位整数:");
//	scanf("%d%d%d", &x, &y, &z);
//	int s = (x * 100 + y * 10 + z);
//	printf("				结果:  %d\n", s);
//}
//void exe4_2_2_10( )
//{
//	char a;
//	printf("大写字母转小写，请输入一个大写字母:");
//	getchar();
//	scanf("%c", &a);
//	char b = a + 32;
//	printf("      转换后的小写字母是:%c\n", b);
//}
//void exe4_2_2_11( )
//{
//	float a, b, c;
//	printf("交换两个数，请输入两个小数:");
//	scanf("%f%f", &a, &b);
//	printf("交换前:		  a=%f,b=%f\n", a, b);
//	c = a;
//	a = b;
//	b = c;
//	printf("交换后:       a=%f,b=%f\n", a, b);
//}
//void exe4_2_2_12( )
//{
//	int x, y, z;
//	printf("输入三个整数，分别表示日期的年，月，日:");
//	scanf("%d%d%d", &x, &y, &z);
//	printf("%d年%d月%d日\n", x, y, z);
//}
//void exe4_2_2_13( )
//{
//	float x, y;
//	printf("摄氏度转华氏度，请输入任意摄氏温度(精确到小数):");
//	scanf("%f", &x);
//	y = (9 / 5.0) * x + 32;
//	printf("其对应华氏温度为:%f\n", y);
//}
//void exe4_2_2_14( )
//{
//	float x, y, z;
//	printf("计算三角形斜边:请输入任意直角边长度（精确到小数）:");
//	scanf("%f%f", &x, &y);
//	z = sqrt(pow(x, 2) + pow(y, 2));
//	printf("斜边长为:%f\n", z);
//}
