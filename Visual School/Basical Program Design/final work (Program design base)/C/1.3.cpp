//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <windows.h>
//#include <stdbool.h>
//#define MAXLENGTH 20
////use virtul terminal accomplish diversity color exhibit (ANSL)
//
//int flag = 1;// deal with negative;
//void enable_ansi()
//{
//	HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);
//	DWORD mode = 0;
//	GetConsoleMode(HOUT, &mode);
//	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//	SetConsoleMode(HOUT, mode);
//}
//
//bool is_valid_char(char ch, int src_base)
//{
//	if ('0' <= ch && ch <= '9')
//	{
//		return ch - '0' < src_base;
//	}
//	else if ('A' <= ch && ch <= 'Z')
//	{
//		return ch - 'A' + 10 < src_base;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//int find_last_invalid_char(char* string, int stringlength, int src_base)
//{
//	int flag = -1;
//	for (int i = stringlength - 1; i >= 0; i--)
//	{
//		if (!is_valid_char(string[i], src_base))
//		{
//			flag = i;
//			break;
//		}
//	}
//	return flag;
//}
//
//bool is_valid_string(char* string, int stringlength, int src_base)
//{
//	return find_last_invalid_char(string, stringlength, src_base) == -1;
//}
//int char_to_num(char ch)
//{
//	if ('0' <= ch && ch <= '9')
//	{
//		return ch - '0';
//	}
//	else
//	{
//		return ch - 'A' + 10;
//	}
//}
//
//char num_to_char(int num)
//{
//	return num < 10 ? num + '0' : num - 10 + 'A';
//}
//
//void redraw(char* string, int stringlength, int src_base, int tar_base)
//{
//	system("cls");
//	printf("please imput %d base number(0-%c) and shoule make sure length <%d),it will be transfermed to %d base:\n", src_base, num_to_char(src_base - 1), MAXLENGTH, tar_base);
//	printf("imput comtent:");
//	if (flag == -1)
//	{
//		printf("-");
//	}
//	for (int i = 0; i < stringlength; i++)
//	{
//		if (is_valid_char(string[i], src_base))
//		{
//			printf("%c", string[i]);
//		}
//		else
//		{
//			printf("\033[31m%c\033[0m", string[i]);
//		}
//	}
//	printf("|");
//	printf("\nhint:");
//	if (stringlength == 0)
//	{
//		printf("nothing");
//		return;
//	}
//	int invalid_index = find_last_invalid_char(string, stringlength, src_base);
//	if (invalid_index == -1)
//	{
//		printf("\033[33mLegal imput,enter at most is:%d\033[0m", MAXLENGTH - 1 - stringlength);
//	}
//	else
//	{
//		printf("\033[31m illegal char【%c】(the index is %d)，only support %d base(0-%c)!enter at most is:%d\033[0m",
//			string[invalid_index], invalid_index + 1, src_base, num_to_char(src_base - 1), MAXLENGTH - 1 - stringlength);
//	}
//}
//
//int main()
//{
//	enable_ansi();
//	int src_base, tar_base, num = 0;
//	do
//	{
//		printf("please imput initial base:");
//		if (scanf("%d", &src_base) != 1 || (src_base < 2 || src_base>36))
//		{
//			printf("\033[31munlegal base,beyond range(2-36)\033[0m\n");
//		}
//		while (getchar() != '\n');
//	} while (src_base < 2 || src_base>36);
//	do
//	{
//		printf("please imput target base:");
//		if (scanf("%d", &tar_base) != 1 || (tar_base < 2 || tar_base>36))
//		{
//			printf("\033[31munlegal base,beyond range(2-36)\033[0m\n");
//		}
//		while (getchar() != '\n');
//	} while (tar_base < 2 || tar_base>36);
//	char string[MAXLENGTH] = { 0 };// 显示初始化string全部为\0
//	int stringlength = 0;
//	redraw(string, stringlength, src_base, tar_base);
//	while (1)
//	{
//		int ch = _getch();
//		if (ch == '\r' && is_valid_string(string, stringlength, src_base))// \n居然不能退出，why,看来enter键存在ch里是\r \n是换行\r是回车，说明
//			// 系统一般情况将enter键解释为\n+\r
//		{
//			break;
//		}
//		else if (ch == 8 && stringlength > 0)
//		{
//			stringlength--;
//			string[stringlength] = '\0';
//		}
//		else if (ch == 8 && flag == -1)//首位为-号，将flag重新变为1
//		{
//			flag = 1;
//		}
//		else if (ch >= 32 && ch <= 126 && stringlength < MAXLENGTH - 1)
//		{
//			if ('a' <= ch && ch <= 'z')
//			{
//				string[stringlength++] = ch - 'a' + 'A';
//			}
//			else if (ch == '-' && flag != -1)//flag!=-1,确保是首次输入-，对于所有非 首次输入的-号都标红
//			{
//				if (string[0] == '\0')flag = -1;//只要首次输入的时候第一个不是\0，都看作非法-号
//				else string[stringlength++] = ch;
//			}
//			else
//			{
//				string[stringlength++] = ch;
//			}
//		}
//		redraw(string, stringlength, src_base, tar_base);
//	}
//
//	unsigned long long int dec_num = 0;
//	for (int i = 0; i < stringlength; i++)
//	{
//		dec_num = dec_num * src_base + char_to_num(string[i]);
//	}
//	int index = 0;
//	char tar_string[64] = { 0 };
//	while (dec_num)
//	{
//		tar_string[index++] = num_to_char(dec_num % tar_base);
//		dec_num /= tar_base;
//	}
//	for (int i = 0; i < index / 2; i++)
//	{
//		char temp = tar_string[i];
//		tar_string[i] = tar_string[index - 1 - i];
//		tar_string[index - 1 - i] = temp;
//	}
//
//	system("cls");
//	printf("\033[31mtransfering:\033[0m\n");
//	printf("initial %d base num :%c%s\n", src_base, flag == -1 ? '-' : ' ', string);
//	printf("target %d base num:%c%s", tar_base, flag == -1 ? '-' : ' ', tar_string);
//	return 0;
//}