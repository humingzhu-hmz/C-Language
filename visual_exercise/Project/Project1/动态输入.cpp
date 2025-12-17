//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
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
//			if(current_len==0)
//			{
//				continue;
//			}
//			char* temp = (char*)realloc(buf, (1+current_len) * sizeof(char));
//			if (temp == NULL)
//			{
//				buf[current_len] = '\0';
//				return buf;
//			}
//			buf = temp;
//			buf[current_len] = '\0';
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
//			char* temp = (char*)realloc(buf,(1+ new_cap) * sizeof(char));
//			if (temp == NULL)
//			{
//				buf[current_len] = '\0';
//				return buf;
//			}
//			current_cap = new_cap;
//			buf = temp;
//		}
//		buf[current_len++] = ch;
//	}
//	char* finalcap = (char*)realloc(buf, (1 + current_len) * sizeof(char));
//	if (finalcap != NULL)
//	{
//		buf = finalcap;
//		return buf;
//	}
//	else
//		return buf;
//}
//int main()
//{
//	size_t i=0,initcap, maxlength;
//	fprintf(stdout, "请输入初始内存大小和最大输入长度(以空格分隔):");
//	scanf_s("%zu %zu", &initcap, &maxlength);
//	fprintf(stdout, "\n请输入内容(以回车结束):");
//	int c;
//	while ((c = getchar()) != '\n' && c != EOF);
//	char* buf = safe_read_input(initcap, maxlength);
//	fprintf(stdout, "您输入的内容为:");
//	while (i < maxlength && buf[i] != '\0')
//	{
//		fprintf(stdout,"%c",buf[i++]);
//	}
//	free(buf);
//	return 0;
//}
//
//
//对上面版本的优化，前者限制了最大输入长度，这个版本不限制最大输入长度，只受内存限制
//
//char* input()
//{
//	char* str = (char*)calloc(50, sizeof(char));
//	size_t current_len=0, current_cap = 50, new_cap;
//	int ch;
//	while((ch=getchar())!=EOF&&ch!='\n')
//	{
//		if ((current_len+1) == current_cap)
//		{
//			new_cap = current_cap + ((current_cap >> 1)>>1);
//			char* temp = (char*)realloc(str, new_cap * sizeof(char));
//			if (temp == NULL)
//			{
//				fprintf(stderr, "内存再分配失败\n");
//				str[current_cap] = '\0';
//				return str;
//			}
//			current_cap = new_cap;
//		}
//		str[current_len++] = ch;
//	}
//	str[current_len] = '\0';
//	char* finalcap = (char*)realloc(str, (current_len + 1) * sizeof(char));
//	if (finalcap != NULL)
//	{
//		str = finalcap;
//		return str;
//	}
//	else
//		free(finalcap);
//	return str;
//}
//int main()
//{
//	fprintf(stdout, "请输入一行文本(以回车结束):");
//	char* str = input();
//	fprintf(stdout, "\n您输入的文本是:");
//	while (*str != '\0')
//	{
//		fprintf(stdout, "%c", *str++);
//	}
//	free(str);
//	return 0;
//}