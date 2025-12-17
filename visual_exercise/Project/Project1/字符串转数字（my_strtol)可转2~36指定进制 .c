//#define _CRT_SRCURE_NO_WATRNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <math.h>
//long long int my_atoi(char* arr)
//{
//	int sign = 1, i = 0;
//	while (!isdigit(*(arr + i))&&(arr[i]!='-'))
//	{
//		i++;
//	}
//	if (arr[i] == '-')
//	{
//		sign = -1;
//		i++;
//	}
//	long long int result = 0;
//	while (arr[i] != '\0')
//	{
//		if (isdigit(arr[i]))
//		{
//			if (result >= (INT_MAX - (arr[i] - '0') / 10))//overflow check
//			{
//				if (sign == 1)
//					return INT_MAX;
//				else
//					return INT_MIN;
//			}
//			result = result * 10 + (arr[i] - '0');
//		}
//		i++;
//	}
//	return sign * result;
//}
//char* safe_read_input(size_t initcap, size_t maxlength)
//{
//	if (initcap > maxlength)
//	{
//		initcap = maxlength;
//	}
//	if (initcap < 1)
//	{ 
//		initcap = 1;
//	}
//	char* buf = (char*)calloc(initcap+1, sizeof(char));
//	if (buf == NULL)
//	{ // 检查初始分配失败
//		fprintf(stderr, "初始内存分配失败\n");
//		return NULL;
//	}
//	size_t current_len = 0,current_cap=initcap,new_cap;
//	while (1)
//	{
//		int ch=getchar();
//		if (ch == '\n' || ch == EOF)
//		{
//			buf[current_len] = '\0';
//			char* temp = (char*)realloc(buf, 1+current_len * sizeof(char));
//			if (temp == NULL)
//			{
//				fprintf(stdout, "内存分配失败");
//				break;
//			}
//			buf = temp;
//			break;
//		}
//		if (current_len == maxlength)
//		{
//			buf[current_len] = '\0';//截断输入流
//			break;
//		}
//		if (current_len + 1 >= current_cap)
//		{
//			new_cap = (current_cap+ (current_cap>>1));
//			if (new_cap > maxlength)
//			{
//				new_cap = maxlength;
//			}
//			char* temp = (char*)realloc(buf,1+ new_cap * sizeof(char));
//			if (temp == NULL)
//			{
//				fprintf(stderr, "内存分配失败");
//				break;
//			}
//			current_cap = new_cap;
//			buf = temp;
//		}
//		buf[current_len++] = ch;
//	}
//	char* finalcap = (char*)realloc(buf, 1 + (current_len * sizeof(char)));
//	if (finalcap != NULL)
//	{
//		buf = finalcap;
//		return buf;
//	}
//	else
//		free(finalcap);
//		return buf;
//}
//
//char* transform(long long int result,int baseline)
//{
//	if (result == 0) {
//		char* value = (char*)malloc(2);
//		value[0] = '0';
//		value[1] = '\0';
//		return value;
//	}
//	if (baseline < 2 || baseline>36)
//	{
//		fprintf(stdout, "进制错误或超出范围,转换失败.");
//		exit(1);
//	}
//	int is_negative = (result < 0),i=0,k=0;
//	unsigned long long int value10 = is_negative ? -result : result;
//	char* value = (char*)calloc(20, sizeof(char));
//	char temp[20];
//	while (value10 > 0)
//	{
//		int digit = value10 % baseline;
//		temp[i++] = (digit < 10) ? (digit + '0') : (digit + 'a' - 10);
//		value10 /= baseline;
//	}
//	temp[i] = '\0';
//	if (is_negative)
//	{
//		value[k++] = '-';
//	}
//	while (i >= 0)
//	{
//		value[k++] = temp[--i];
//	}
//	value[k] = '\0';
//	return value;
//}
//int main()
//{
//	int baseline,ch;
//start:
//	printf("请输入进制(2~36)，直接回车可结束程序：");
//	if ((ch=getchar()) == '\n')
//	{
//		exit(1);
//	}
//	ungetc(ch, stdin);
//	scanf_s("%d", &baseline);
//	printf("\n请输入字符串数字（若有非数字会跳过）:");
//	while ((ch = getchar()) != '\n' && ch != EOF);
//	char* str = safe_read_input(12, 20);
//	printf("\n你输入的字符串是:");
//	fprintf(stdout, "%s", str);
//	long long int result= my_atoi(str);
//	if (baseline == 10)
//	{
//		fprintf(stdout, "\n转换后的 10 进制数为:%lld", result);
//		while ((ch = getchar()) != '\n' && ch != EOF);
//		goto start;
//	}
//	char* value = transform(result, baseline);
//	fprintf(stdout, "\n转换后的 %d 进制数为:%s",baseline,value);
//	while ((ch = getchar()) != '\n' && ch != EOF);
//	goto start;
//	return 0;
//}