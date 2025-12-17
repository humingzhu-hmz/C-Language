//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <string.h>
//#include <time.h>
//#include <ctype.h>
//#include <math.h>
//
//
//	char* generate_rand_string()
//{
//	srand((unsigned int)time(NULL));
//	char* string = (char*)malloc(1025 * sizeof(char));
//	if (string == NULL)
//	{
//		printf("内存分配失败！\n");
//		exit(1);
//	}
//	int i = 0;
//	do
//	{
//		string[i++] = (char)(rand() % 95 + 32);
//	} while (i < 1024);
//	string[i] = '\0';
//	return string;
//}
//
//void exe1()
//{
//	char* string = generate_rand_string();
//	fprintf(stdout, "生成的随机字符串string为:%s\n", string);
//	int i = 0, upper = 0, lower = 0;
//	while (*(string + i) != '\0')
//	{
//		if (isupper(string[i]))
//		{
//			upper++;
//		}
//		else if (islower(string[i]))
//		{
//			lower++;
//		}
//		i++;
//	}
//	printf("upper = %d ,lower = %d \n", upper, lower);
//	free(string);
//}
//
//void exe2()
//{
//	char* string = generate_rand_string();
//	fprintf(stdout, "生成的随机字符串 string 为:%s\n", string);
//	if (string[0] == '\0')
//	{
//		printf("字符串为空！\n");
//		free(string);
//		return;
//	}
//	int max = (int)string[0], i = 1;
//	do
//	{
//		if ((int)string[i] > max)
//		{
//			max = (int)string[i];
//		}
//		i++;
//	} while (string[i] != '\0');
//	printf("The char of max Acall is :%c\n", (char)(max));
//	free(string);
//}
//
//void exe3()
//{
//	int i = 0;
//	char* string1 = generate_rand_string();
//	char string2[1025] = { 0 };
//	fprintf(stdout, "生成的随机字符串 string1 为:%s\n", string1);
//	while (string1[i] != '\0')
//	{
//		string2[i] = string1[i];
//		i++;
//	}
//	string2[i] = '\0';
//	printf("Copy string1 to string2 ,string2 is:%s\n", string2);
//	free(string1);
//}
//
//void halfinsertsort(char* arr, int step, int arrlenth)
//{
//	for (int start = 0; start < step; start++)
//	{
//		for (int j = start + step; j < arrlenth; j += step)
//		{
//			int left = start, right = j - step, mid = left + (right - left) / (2 * step) * step;
//			char piont = arr[j];
//			while (left <= right)
//			{
//				if (piont < arr[mid])
//				{
//					right = mid - step;
//					mid = left + (right - left) / (2 * step) * step;
//				}
//				else
//				{
//					left = mid + step;
//					mid = left + (right - left) / (2 * step) * step;
//				}
//			}
//			for (int k = j - step; k >= left; k -= step)
//			{
//				arr[k + step] = arr[k];
//			}
//			arr[left] = piont;
//		}
//	}
//}
//
//void shellsort(char* arr, int arrlenth)
//{
//	int d = (arrlenth) / 2;
//	while (d > 0)
//	{
//		halfinsertsort(arr, d, arrlenth);
//		d = d / 2;
//	}
//}
//
//void exe4()
//{
//	char* string = generate_rand_string();
//	fprintf(stdout, "生成的随机字符串 string 为:%s\n", string);
//	int stringlenth = strlen(string);
//	shellsort(string, stringlenth);
//	printf("排序后:%s\n", string);
//	free(string);
//}
//
//typedef struct statistic
//{
//	int count;
//	char ch;
//}statistic;
//
//int comparing(const void* a, const void* b)
//{
//	statistic* S1 = (statistic*)a;
//	statistic* S2 = (statistic*)b;
//	if (S2->count != S1->count)
//	{
//		return S2->count - S1->count;
//	}
//	else
//	{
//		return S1->ch - S2->ch;
//	}
//}
//
//void exe5()
//{
//	char* string = generate_rand_string();
//	fprintf(stdout, "生成的随机字符串 string 为:%s\n", string);
//	int stringlenth = strlen(string);
//	statistic loweralpha[26];
//	for (int k = 0; k < 26; k++)
//	{
//		loweralpha[k].count = 0;
//		loweralpha[k].ch = 'a' + k;
//	}
//	for (int i = 0; i < stringlenth; i++)
//	{
//		if (islower(string[i]))
//		{
//			int idx = string[i] - 'a';
//			loweralpha[idx].count++;
//		}
//	}
//	qsort(loweralpha, 26, sizeof(statistic), comparing);
//	for (int i = 0; i < 26; i++)
//	{
//		if (loweralpha[i].count > 0)
//		{
//			printf(" %c  %d\n", loweralpha[i].ch, loweralpha[i].count);
//		}
//	}
//	free(string);
//}
//
//char* generate_article(char* string, int strlenth)
//{
//	srand((unsigned int)time(NULL));
//	for (int i = 0; i < strlenth - 1; i++)
//	{
//		int type = rand() % 5;
//		switch (type)
//		{
//		case 0: string[i] = 'A' + rand() % 26; break;
//		case 1: string[i] = 'a' + rand() % 26; break;
//		case 2: string[i] = '0' + rand() % 10; break;
//		case 3: string[i] = ' '; break;
//		default: string[i] = '!' + rand() % 15; break;
//		}
//	}
//	string[strlenth - 1] = '\0';
//	return string;
//}
//
//void exe6()
//{
//	char* string = (char*)malloc(240 * sizeof(char));
//	generate_article(string, 240);
//	int upalpha = 0, loalpha = 0, digit = 0, space = 0, elsechar = 0;
//	for (int i = 0; i < 240; i++)
//	{
//		if (isdigit(string[i]))
//		{
//			digit++;
//		}
//		else if (isupper(string[i]))
//		{
//			upalpha++;
//		}
//		else if (islower(string[i]))
//		{
//			loalpha++;
//		}
//		else if (string[i] == ' ')
//		{
//			space++;
//		}
//		else
//		{
//			elsechar++;
//		}
//	}
//	printf("upperalpha :%d\n loweralpha :%d \n digit :%d \n space :%d \n elsechar :%d \n", upalpha, loalpha, digit, space, elsechar);
//	free(string);
//}
//
//bool existword(char** vocalubary, char* word, int vocalenth)
//{
//	for (int i = 0; i < vocalenth; i++)
//	{
//		if (strcmp(vocalubary[i], word) == 0)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//
//void exe7()
//{
//	char* passage;
//	printf("import a passage:");
//	gets(passage);
//	int lenth = strlen(passage);
//	char** vocalubary = (char**)malloc(lenth / 2, sizeof(char*));
//	int vocalenth = 0;
//	for (int point = 0; point < lenth; point++)
//	{
//		if (isalpha(passage[point]))
//		{
//			int temp = point;
//			point++;
//			while (isalpha(passage[point]) || passage[point] == 39)
//				//passage real lenth (intclude \0) is lenth +1;
//				// so even if point = lenth ,also don't over range
//				// then the circle (while and for)will end .
//			{
//				point++;
//			}
//			int wordlenth = (point - temp);
//			char* word = (char*)malloc((wordlenth + 1) * sizeof(char));
//			for (int i = 0; i < wordlenth; i++)
//			{
//				word[i] = passage[temp++];
//			}
//			if (existword(vocalubary, word, vocalenth))
//			{
//				continue;
//			}
//			else
//
//			{
//				vocalubary[vocalenth] = (char*)malloc((wordlenth + 1) * sizeof(char));
//				strcpy(vocalubary[vocalenth], word);
//				vocalenth++;
//			}
//		}
//	}
//	for (int i = 0; i < vocalenth; i++)
//	{
//		printf("%s\n", vocalubary[i]);
//	}
//}
//
//
//void exe8()
//{
//	int digit, figures = 0, i = 1;
//	printf("import:");
//	scanf("%d", &digit);
//	int temp = digit;
//	do {
//		figures++;
//		temp /= 10;
//	} while (temp != 0);
//	long long squares = (long long)digit * digit;
//	long long mod = 1;
//	for (int j = 0; j < figures; j++) mod *= 10;
//	printf("%s\n", (squares % mod == digit) ? "YES" : "NO");
//}
//
//void exe9()
//{
//	int digit;
//	printf("please import value:");
//	scanf("%d", &digit);
//	if (digit <= 0 || digit > 65535)
//	{
//		printf("input error!\n");
//		return;
//	}
//	char string[17] = { 0 };
//	int i = 15;
//	while (digit != 0)
//	{
//		string[i--] = (digit % 2) + '0';
//		digit /= 2;
//	}
//	printf("%s\n", string + i + 1);
//}
//
//void exe10()
//{
//	for (int i = 1; i <= 100; i++)
//	{
//		if ((i & 1) == 1)
//		{
//			if (((long long)i * i) % 8 != 1)
//			{
//				printf("NO\n");
//				return;
//			}
//		}
//	}
//	printf("YES\n");
//}
//
//double calculate_pi(int total_points)
//{
//	int inside_circle = 0;
//	double x, y;
//	srand((unsigned int)time(NULL));
//	for (int i = 0; i < total_points; i++)
//	{
//		x = (double)rand() / RAND_MAX * 2 - 1;
//		y = (double)rand() / RAND_MAX * 2 - 1;
//		if (x * x + y * y <= 1)
//		{
//			inside_circle++;
//		}
//	}
//	double pi = 4 * ((double)inside_circle / total_points);
//	return pi;
//}
//
//double circea(double r, double pi)
//{
//	return pi * r * r;
//}
//
//void exe12()
//{
//	int total_points;
//	double radius;
//	printf("import total_points and r:");
//	scanf("%d %lf", &total_points, &radius);
//	double pi = calculate_pi(total_points);
//	double areas = circea(radius, pi);
//	printf("%lf\n", areas);
//}
//
//int gcd(int num1, int num2)
//{
//	return (num2 == 0) ? num1 : (gcd(num2, num1 % num2));
//}
//
//void exe13()
//{
//	int num1, num2;
//	printf(" please import two integers:");
//	scanf("%d %d", &num1, &num2);
//	printf("%d\n", gcd(num1, num2));
//}
//
//void exe14()
//{
//	int x1, y1, x2, y2;
//	printf("pleae import two location(x1,y1) (x2,y2):");
//	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
//	double instance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
//	printf("the instance between a and b is :%lf\n", instance);
//}
//
//double changeCF(double temp, char ctype) {
//	char type = toupper(ctype);
//	double result = 0.0;
//
//	switch (type) {
//	case 'C':
//		result = (temp - 32) * 5.0 / 9.0;
//		break;
//	case 'F':
//		result = temp * 9.0 / 5.0 + 32;
//		break;
//	default:
//		printf("错误：无效的温度类型！仅支持 'C' 或 'F'\n");
//		result = -9999.0;
//		break;
//	}
//	return result;
//}
//
//void exe15()
//{
//	double temp_input, temp_output;
//	char type;
//
//	temp_input = 0.0;
//	type = 'F';
//	temp_output = changeCF(temp_input, type);
//	printf("%.2f℃ 转换为华氏温度：%.2f℉\n", temp_input, temp_output);
//
//	temp_input = 32.0;
//	type = 'C';
//	temp_output = changeCF(temp_input, type);
//	printf("%.2f℉ 转换为摄氏温度：%.2f℃\n", temp_input, temp_output);
//
//	printf("\n请输入待转换的温度值：");
//	scanf("%lf", &temp_input);
//	printf("请输入转换类型（C：华氏转摄氏 / F：摄氏转华氏）：");
//	scanf(" %c", &type);
//
//	temp_output = changeCF(temp_input, type);
//	if (temp_output != -9999.0) {
//		if (toupper(type) == 'C') {
//			printf("%.2f℉ 转换为摄氏温度：%.2f℃\n", temp_input, temp_output);
//		}
//		else if (toupper(type) == 'F') {
//			printf("%.2f℃ 转换为华氏温度：%.2f℉\n", temp_input, temp_output);
//		}
//	}
//}
//
//int isOE(int number)
//{
//	return ((number & 1) == 0) ? -1 : 1;
//}
//
//void exe16()
//{
//	int number;
//	scanf("%d", &number);
//	printf("%d\n", isOE(number));
//}
//
//void exchange(int* n1, int* n2)
//{
//	int temp = *n1;
//	*n1 = *n2;
//	*n2 = temp;
//}
//
//void exe17()
//{
//	int n1, n2;
//	scanf("%d %d", &n1, &n2);
//	exchange(&n1, &n2);
//	printf("%d %d\n", n1, n2);
//}
//
//int main()
//{
//	int N;
//	setbuf(stdin, NULL);
//	printf("===== 程序设计基础课后上机练习（七）=====\n");
//	printf("请选择要运行的题目编号（1-10,12-17）：\n");
//	printf("1:统计大小写字母  2:找ASCII最大字符  3:字符串复制  4:字符串排序  5:统计小写字母次数\n");
//	printf("6:统计文章字符类型  7:提取单词分行  8:判断自守数  9:十进制转二进制  10:验证奇数平方命题\n");
//	printf("12:计算圆面积  13:最大公约数  14:两点间距离  15:温度转换  16:判断奇偶  17:交换整数\n");
//	printf("selected problem: ");
//	scanf("%d", &N);
//	getchar();
//	switch (N)
//	{
//	case 1: exe1(); break;
//	case 2: exe2(); break;
//	case 3: exe3(); break;
//	case 4: exe4(); break;
//	case 5: exe5(); break;
//	case 6: exe6(); break;
//	case 7: exe7(); break;
//	case 8: exe8(); break;
//	case 9: exe9(); break;
//	case 10: exe10(); break;
//	case 12: exe12(); break;
//	case 13: exe13(); break;
//	case 14: exe14(); break;
//	case 15: exe15(); break;
//	case 16: exe16(); break;
//	case 17: exe17(); break;
//	default: printf("无效的题目编号！\n"); break;
//	}
//	return 0;
//}