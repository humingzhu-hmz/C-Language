//#define _crt_secure_no_warnings
//#include <stdio.h>
//#include <math.h>
//#define pi 3.1415926
//void exe4_2_3_1()
//{
//	int a = 5, b = 10, h = 6;
//	float s = (a + b) * h / 2;
//	printf("计算梯形面积，其中a=5,b=10,h=6.");
//	fflush(stdout);
//	printf("	请按回车键继续:\n");
//	char ch;
//	while (ch = getchar() != '\n');
//	{
//
//	}
//	printf("梯形面积为：%f", s);
//}
//void exe4_2_3_2()
//{
//	float a, b, c, x1, x2, m;
//	printf("计算并输出方程的两个实根,请输入三个实数作为一元二次方程（ax^2+bx+c)的系数：");
//	scanf("%f%f%f", &a, &b, &c);
//	while (pow(b, 2) - 4 * a * c < 0)
//	{
//		printf("您输入的方程为：%.2fx^2+%.2fx+%.2f	因b^2-4a*c<0 故其无实数根\n 请重新输入：", a, b, c);
//		scanf("%f%f%f", &a, &b, &c);
//	}
//	m = sqrt(b * b - 4 * a * c);
//	x1 = (-b + m) / 2 * a;
//	x2 = (-b - m) / 2 * a;
//	printf("您输入的方程为：%.2fx^2+%.2fx+%.2f	其两根分别为：x1=%f x2=%f", a, b, c, x1, x2);
//}
//void exe4_2_3_3()
//{
//	printf("输入任意三个数字字符构成一个整数，请输入:");
//	int a, b, c;
//	scanf("%d%d%d", &a, &b, &c);
//	int x = (a * 100 + b * 10 + c);
//	printf("	\n输出整数:%d", x);
//}
//void exe4_2_3_4()
//{
//	float x;
//	printf("计算x^5,请输入任意一个浮点数x（1.00<=x<=100.00):");
//	scanf("%f", &x);
//	while (0==(x >= 1 && x <= 100));
//	{
//		printf("\n	您输入的x值不在取值范围内，请重新输入：");
//		scanf("%f", &x);
//	}
//	printf("\n	x^5值为:%f", pow(x, 5));
//}
//void exe4_2_3_5()
//{
//	int v = 10, a = 2,vt, s, t;
//	printf("请输入时间以计算末速度（t>=20):");
//	scanf("%d", &t);
//	vt = v + a * t;
//	s = v * t + (a * t * t) / 2;
//	float vx = s / 20.0;
//	printf("%d秒后速度为%d,20秒内运动路程为%d,平均速度为:%.2f", t, vt, s, vx);
//}
//void exe4_2_3_6()
//{
//	float lqt;
//	printf("输入水的夸脱数（数字）以计算其所包含的水分子数:");
//	scanf("%f", &lqt);
//	printf("\n		水分子数为:%e", lqt * 3e-23);
//}
//void exe4_2_3_7()
//{
//	float a, b, c, s, p;
//printf("输入三个正数表示三角形三边:");
//scanf("%f%f%f", &a, &b, &c);
//while (0== a + b > c && a + c > b && b + c > a);
//{
//	printf("\n	输入的三边不能构成一个三角形，请重新输入:");
//	scanf("%f%f%f", &a, &b, &c);
//}
//	p = (a + b + c) / 2;
//	s = sqrt(p*(p - a)*(p - b)*(p - c));
//	printf("\n	该三角形面积为:%f", s);
//}
//void exe4_2_3_8()
//{
//	float r, h, c, s, v;
//printf("计算圆柱的底面周长、表面积、体积，请输入底面半径r、高h：");
//scanf("%f%f", &r, &h);
//c = 2 * pi * r;
//s = pi * r * r;
//v = s * h;
//printf("c=%f,s=%f,v=%f", c, s, v);
//}
//void exe4_2_3_9()
//{
//	printf("已知u=220，r1=r2=10k欧姆，r3=r4=20k欧姆	 并联电路求各路电流i及总电阻：\n");
//float r1=1e4, r2=1e4, r3=2e4, r4=2e4, r, i1, i2, i3, i4;
//int u = 220;
//r = (1.0 / r1 + 1.0 / r2 + 1.0 / r3 + 1.0 / r4  );
//i1 = u / r1;
//i2 = u / r2;
//i3 = u / r3;
//i4 = u / r4;
//printf("r总 = %f \n i1 = %f \n i2 = %f \n i3 = %f \n i4 = %f\n", r, i1, i2, i3, i4);
//}
//void exe4_2_3_10()
//{
//	int a ;
//	printf("该程序会把输入天数转为对应周数及天数,请输入:");
//	scanf("%d", &a);
//	printf("输出%d周%d天\n", a / 7, a % 7);
//}
//void exe4_2_3_11()
//{
//	printf("字母加密,请输入字母:");
//	char str[15];
//	scanf("%s", str);
//	printf("\n		");
//	int count = strlen(str);
//	for (int i = 0; i <= count; i++)
//	{
//		if (str[i] <= 90 && str[i] >= 65)
//			printf("%c", 'a' + (str[i] - 'a' + 4) % 26);
//		else if (str[i] <= 123 && str[i] >= 97)
//			printf("%c", 'a' + (str[i] - 'a' + 4) % 26);
//		else printf(" ");
//	}
//}
//void exe4_2_3_12()
//{
//	int n;
//	printf("请输入一个两位整数:");
//	scanf("%d", &n);
//	int nn = n * n;
//	int a = nn % 10, b = (nn / 10) % 10;
//	printf("%d", b * 10 + a);
//
//}
//int main()
//{
//	printf("-----------------\n");
//	printf("1 计算梯形面积\n");
//	printf("2 计算并输出方程的两个实根\n");
//	printf("3 输入任意三个数字字符构成一个整数\n");
//	printf("4 计算x^5\n");
//	printf("5 请输入时间以计算末速度（t>=20)\n");
//	printf("6 输入水的夸脱数（数字）以计算其所包含的水分子数\n");
//	printf("7 计算三角形面积\n");
//	printf("8 计算圆柱的底面周长、表面积、体积\n");
//	printf("9 并联电路求各路电流i及总电阻\n");
//	printf("10 输入天数转为对应周数及天数\n");
//	printf("11 字母加密\n");
//	printf("12 两位整数平方取其十位个位组合新数\n");
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
//		case 1:exe_4_2_3_1(); break;
//		case 2:exe_4_2_3_2(); break;
//		case 3:exe_4_2_3_3(); break;
//		case 4:exe_4_2_3_4(); break;
//		case 5:exe_4_2_3_5(); break;
//		case 6:exe_4_2_3_6(); break;
//		case 7:exe_4_2_3_7(); break;
//		case 8:exe_4_2_3_8(); break;
//		case 9:exe_4_2_3_9(); break;
//		case 10:exe_4_2_310(); break;
//		case 11:exe_4_2_3_11(); break;
//		case 12:exe_4_2_3_12(); break;
//		}
//	}
//	return 0;
//}