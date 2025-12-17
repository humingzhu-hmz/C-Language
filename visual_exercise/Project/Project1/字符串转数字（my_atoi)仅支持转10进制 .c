//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <limits.h>
//#include <stddef.h>
//long long int my_atoi(char* arr)
//{
//	int sign = 1, i = 0;
//	while (isspace((unsigned char)*(arr+i)))
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
//		if  (isdigit(arr[i]))
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
//int main()
//{	//调用了之前写的文件（动态输入.cpp)
//	size_t i=0,maxlength;
//	fprintf(stdout, "请输入最大输入长度:");
//	scanf_s("%zu", &maxlength);
//	fprintf(stdout, "\n请输入内容(以回车结束):");
//	int ch;
//	while ((ch = getchar()) != '\n' && ch != EOF);
//	char* buf = safe_read_input(10, maxlength);
//	fprintf(stdout, "您输入的内容为:");
//	while (i < maxlength && buf[i] != '\0')
//	{
//		fprintf(stdout,"%c",buf[i++]);
//	}
//	long long int result = my_atoi(buf);
//	fprintf(stdout, "\n");
//	fprintf(stdout, "字符串转换为数字后：%lld", result);
//	free(buf);
//	return 0;
//}
