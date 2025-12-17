//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//void pm1()
//{
//	int num1, num2, num3;
//	printf("请输入三个整数:");
//	scanf("%d %d %d", &num1, &num2, &num3);
//	double average = (num1 + num2 + num3) / 3.0;
//	int product = (num1 * num2 * num3);
//	printf(" 平均数:%f\n        乘  积:%d\n", average, product);
//}
//void pm2()
//{
//	int  a = 70, b = 89, c = 65, d = 100, e = 78;
//	printf("五名学生成绩分别为70，89，65，100，78 。 ");
//	double avg = (a + b + c + d + e) / 5.0;
//	printf("其平均成绩为:%f\n", avg);
//}
//void pm3()
//{
//	int x, y;
//	printf("三问答: 请输入整数X:  ");
//	scanf("%d", &x);
//	y = pow((x - 10), 3);
//	printf("y = %d\n", y);
//}
//void pm4()
//{
//	int x, a, b, c, d, f;
//	printf("四问答:反序输出四位数，请输入一个四位整数:");
//	scanf("%d", &x);
//	a = (x % 10);
//	b = (x / 10) % 10;
//	c = (x / 100) % 10;
//	d = x / 1000;
//	f = a * 1000 + b * 100 + c * 10 + d;
//	printf("       反序输出结果:  % d\n", f);
//}
//void pm5()
//{
//	int num1, num2, num3;
//	printf("五问答:计算三个数平均数及和，请输入三个整数:");
//	scanf("%d %d %d", &num1, &num2, &num3);
//	int sum = (num1 + num2 + num3);
//	double average = sum / 3.0;
//	printf("        平均数:%f    和:%d\n", average, sum);
//}
//void pm6()
//{
//	int x;
//	printf("六问答：ASCLL码值转对应字符，任意输入一个ASCLL码值(如66):");
//	scanf("%d", &x);
//	printf("对应字符:%c\n", x);
//}
//void pm7()
//{
//	int x, y, z;
//	printf("七问答:组合数，请输入三个一位整数:");
//	scanf("%d%d%d", &x, &y, &z);
//	int s = (x * 100 + y * 10 + z);
//	printf("				结果:  %d\n", s);
//}
//void pm8()
//{
//	char a;
//	printf("八问答:大写字母转小写，请输入一个大写字母:");
//	getchar();
//	scanf("%c", &a);
//	char b = a + 32;
//	printf("      转换后的小写字母是:%c\n", b);
//}
//void pm9()
//{
//	float a, b, c;
//	printf("九问答:交换两个数，请输入两个小数:");
//	scanf("%f%f", &a, &b);
//	printf("交换前:		  a=%f,b=%f\n", a, b);
//	c = a;
//	a = b;
//	b = c;
//	printf("交换后:       a=%f,b=%f\n", a, b);
//}
//void pm10()
//{
//	int x, y, z;
//	printf("十问答:输入三个整数，分别表示日期的年，月，日:");
//	scanf("%d%d%d", &x, &y, &z);
//	printf("%d年%d月%d日\n", x, y, z);
//}
//void pm11()
//{
//	float x, y;
//	printf("十一问答:摄氏度转华氏度，请输入任意摄氏温度(精确到小数):");
//	scanf("%f", &x);
//	y = (9 / 5.0) * x + 32;
//	printf("其对应华氏温度为:%f\n", y);
//}
//void pm12()
//{
//	float x, y, z;
//	printf("十二问答::请输入任意直角边长度（精确到小数）:");
//	scanf("%f%f", &x, &y);
//	z = sqrt(pow(x, 2) + pow(y, 2));
//	printf("斜边长为:%f\n", z);
//}
//int main()
//{
//	printf("-----------------\n");
//	printf("1 计算三名学生成绩平均数及乘积\n");
//	printf("2 平均成绩\n");
//	printf("3 计算y=(X-10)^3\n");
//	printf("4 反序输出四位数\n");
//	printf("5 计算三个数平均数及和\n");
//	printf("6 ASCLL码值转对应字符\n");
//	printf("7 组合数，请输入三个一位整数\n");
//	printf("8 大写字母转小写\n");
//	printf("9 交换两个数\n");
//	printf("10 输入三个整数，分别表示日期的年，月，日\n");
//	printf("11 摄氏度转华氏度\n");
//	printf("12 计算三角形斜边\n");
//	printf("0 退出");
//	printf("------------------\n");
//	while (1)
//	{
//		int select;
//		printf("请选择问题:");
//		scanf("%d", &select);
//		if (select == 0)
//			break;
//		switch (select)
//		{
//		case 1:pm1(); break;
//		case 2:pm1(); break;
//		case 3:pm1(); break;
//		case 4:pm1(); break;
//		case 5:pm1(); break;
//		case 6:pm1(); break;
//		case 7:pm1(); break;
//		case 8:pm1(); break;
//		case 9:pm1(); break;
//		case 10:pm1(); break;
//		case 11:pm1(); break;
//		case 12:pm1(); break;
//		}
//	}
//	return 0;
//
//	
//}