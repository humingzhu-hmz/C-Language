///*第三次程序设计作业代码
//2025/11/5
//源自程序设计指导4.3*/
//#include <stdio.h>
//#include <stdio.h>
//#include <ctype.h>
//void  pm1()
//{
//	int a, b, c;
//	scanf_s("%d%d%d", &a, &b, &c);
//	int max = a > b ? a : b;
//	max = max > c ? max : c;
//	printf("最大值:%d\n", max);
//	
//}
//void pm2()
//{
//	char a, b, c;
//	scanf_s("%c%c%c", &a, &b, &c);
//	int max = a > b ? a : b;
//	max = max > c ? max : c;
//	printf("最大:%c\n", max);
//}
//void pm3()
//{
//	int a, b, c;
//	char inputline[10];
//	printf("请输入一元二次方程的系数(a b c，a≠0)，双击回车结束程序：");
//	while (1)
//	{
//		int ch;
//		while (( ch =getchar()) != '\n' && ch != EOF);
//		int ch1 = getchar(), ch2 = getchar();
//		if (ch1 == '\n'&&ch2 =='\n')
//		{
//			printf("程序已结束！\n");
//			break;
//		}
//		ungetc(ch2, stdin);
//		ungetc(ch1, stdin);
//		fgets(inputline, 10, stdin);
//		int len = strlen(inputline);
//		inputline[len - 1] = '\0';
//		int ret = sscanf(inputline, " %d %d %d", &a, &b, &c);
//		if (ret != 3 || a == 0)
//		{
//			printf("输入格式有误或无二次项系数,请重新输入或三击回车结束该段程序:");
//			continue;
//		}
//		printf("输入的方程:%dx^2+%dx+%d=0\n",a,b,c);
//		float delta_val = (float)b * b - 4 * a * c;
//		const float EPS = 1e-6; 
//
//		if (delta_val < -EPS) 
//		{  
//			printf("方程无实数根，请重新输入或双击回车结束：");
//			continue;
//		}
//
//		
//		float derta = sqrt(fabs(delta_val));
//		float x1, x2;
//		if (fabs(delta_val) < EPS) 
//		{ 
//			x1 = x2 = -b / (2.0 * a);
//			printf("X1=X2=%.4f\n", x1);
//		}
//		else
//		{  
//			x1 = (-b + derta) / (2.0 * a);
//			x2 = (-b - derta) / (2.0 * a);
//			printf("X1=%.4f  X2=%.4f\n", x1, x2);
//		}
//
//		break;
//	}
//}
//void pm4()
//{
//	int score;
//	scanf_s("%d", &score);
//	switch (score / 10)
//	{
//	case 9:printf("'A'\n"); break;
//	case 8:printf("'B'\n"); break;
//	case 7:printf("'C'\n"); break;
//	case 6:printf("'D'\n"); break;
//	default: printf("'E'\n");break;
//	}
//}
//void pm5()
//{
//	int arr[3];
//	for (int i = 0; i < 3; i++)
//	{
//		scanf_s("%d", &arr[i]);
//	}
//	for (int i = 1; i < 3; i++)
//	{
//		for(int m =3-i;m>=1;m--)
//			if (arr[m] < arr[m - 1])
//			{
//				int temp = arr[m];
//				arr[m] = arr[m - 1];
//				arr[m - 1] = temp;
//			}
//	}for (int i = 0; i < 3; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	printf("\n");
//}
//void pm6()
//{
//	int x;
//	scanf_s("%d", &x);
//	if (x % 2 == 0 && x % 3 == 0 && x % 5 == 0)
//	{
//		printf("YES\n");
//	}
//	else
//		printf("NO\n");
//}
//void pm7()
//{
//	char ch;
//	scanf_s("%c", &ch);
//	if (isalpha(ch) == 0)
//	{
//		printf("The character needn't to changed\n");
//		return 0;
//	}
//	if (isupper(ch))
//	{
//		printf("%c\n", tolower(ch));
//	}
//	else
//		printf("%c\n", toupper(ch));
//}
//void pm8()
//{
//	int m;
//	scanf_s("%d", &m);
//	if (m <= 0)
//	{	printf("输入了非正数|n");
//	return 0;
//	}
//	if (m % 2 == 0)
//		printf("%d是偶数\n",m);
//	else
//		printf("%d是奇数\n",m);
//}
//void pm9()
//{
//	int x, tax;
//	scanf_s("%d", &x);
//	if (x >= 10000)
//	{
//		printf("税金 %d", x * 5 / 100);
//		return ;
//	}
//	if (x >= 5000&&x<10000)
//	{
//		printf("税金 %d", x * 3 / 100);
//		return;
//	}
//	if (x >=1000&&x<5000 )
//	{
//		printf("税金 %d", x * 2 / 100);
//		return;
//	}
//	if (x <1000 )
//	{
//		printf("税金 %d", x * 0 / 100);
//		return;
//	}
//}
//void pm10()
//{
//	int x;
//	scanf_s("%d", &x);
//	switch (x)
//	{
//	case 91:printf("30\n"); break;
//	case 92:printf("32\n"); break;
//	case 93:printf("30\n"); break;
//	case 94:printf("30\n"); break;
//	case 95:printf("32\n"); break;
//	default:printf("班级号输入错误");
//	}
//}
//int main()
//{
//	printf("-----------------\n");
//	printf("1 任意输入三个整数，找出其最大值，并输出该最大值\n");
//	printf("2 任意输入三个字符，找出其中（ASCII码）最大的字符，并输出该字符\n");
//	printf("3 任意输入一元二次方程的三个实系数a、b和c，计算并输出该方程所有可能的解\n");
//	printf("4 反序输出四位数\n");
//	printf("5 输入一个学生的百分制分数，计算该学生的成绩等级，并输出学生的成绩等级\n");
//	printf("6 任意输入一个整数，判断该数是否能同时被2、3和5整除，输出“YES”或“NO\n");
//	printf("7 输入一个字符，如果它是小写字母，\n则将其转换为大写字母，若是大写字母，\n则转换为小写字母，输出转换后的这个字符。\n如果该字符不是字母，则输出：\nThe character needn’t to be changed\n");
//	printf("8 判断任意输入的一个整数是奇数还是偶数，输出判断的结果\n");
//	printf("9 货物征收税金\n");
//	printf("10 输入班级号，输出该班的学生人数n");
//	printf("0 退出");
//	printf("------------------\n");
//	while (1)
//	{
//		int select;
//		printf("\n请选择问题:");
//		scanf_s("%d", &select);
//		if (select == 0)
//			break;
//		switch (select)
//		{
//		case 1:pm1(); break;
//		case 2:pm2(); break;
//		case 3:pm3(); break;
//		case 4:pm4(); break;
//		case 5:pm5(); break;
//		case 6:pm6(); break;
//		case 7:pm7(); break;
//		case 8:pm8(); break;
//		case 9:pm9(); break;
//		case 10:pm10(); break;
//		}
//	}
//	return 0;
//}