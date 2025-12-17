//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <time.h>
////flush 冲洗 conio : console input output 控制台输入输出
//typedef struct user
//{
//	char *username;
//	char *password;
//}Users;
//void clear_input_buffer() {
//	int ch;
//	while ((ch = getchar()) != '\n' && ch != EOF);
//}
//char* randinput(int maxlength,int flag)
//{
//	
//	char* buf = (char*)malloc(10*sizeof(char));
//	if (buf == NULL)
//	{ // 检查初始分配失败
//		fprintf(stderr, "初始内存分配失败\n");
//		return NULL;
//	}
//	size_t current_len = 0,current_cap=10,new_cap;
//	while (1)
//	{
//		char ch = rand() % 65;
//		if (ch < 26)
//		{
//			ch = 'a' + ch;
//		}
//		else if (ch < 52)
//		{
//			ch = 'A' + ch - 26;
//		}
//		else if (ch < 61&&flag==2)
//		{
//			ch = ch - 52 + '0';
//		}
//		else if(ch>=61)//保证 username/password有相同概率结束写入且保证用户名只有字母，password可以数字ch>=61对flag=2时确实多余，但省去会让username结束写入概率增加
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
//			char* temp = (char*)realloc(buf, (1 + new_cap) * sizeof(char));
//			if (temp == NULL)
//			{
//				buf[current_len] = '\0';
//				return buf;
//			}
//			current_cap = new_cap;
//			buf = temp;
//		}
//		if(flag==1&&ch>51)
//		{
//			buf[current_len++] = ch % 26 + 'a';
//		}
//		else 
//		{
//			buf[current_len++] = ch;
//		}
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
//void input(Users* users, int n, int maxlength, int choice)
//{
//	switch (choice)
//	{
//	case 1:
//		clear_input_buffer();
//		srand((unsigned int)time(NULL)); 
//		for (int i = 0; i < n; i++) 
//		{
//		users[i].username= randinput(maxlength,1);
//		(*(users + i)).password = randinput(maxlength,2);
//		}
//		break;
//	case 2:
//		clear_input_buffer();
//		for (int i = 0; i < n; i++) 
//		{
//		printf("username[%d]:", i + 1);
//		users[i].username = (char*)malloc((maxlength + 1) * sizeof(char));
//		fgets(users[i].username, maxlength + 1, stdin);
//		users[i].username[strcspn(users[i].username, "\n")] = '\0';
//		clear_input_buffer();
//		printf("password[%d]:", i + 1);
//		(users + i)->password = (char*)malloc((maxlength + 1) * sizeof(char));
//		fgets((users + i)->password, maxlength + 1, stdin);
//		(users + i)->password[strcspn((users + i)->password, "\n")] = '\0';
//		clear_input_buffer();
//		}
//	}
//}void freeusers(Users* users, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		free(users[i].username);
//		free((users + i)->password);
//	}
//	free(users);
//}
//void login(Users* users, int n, int maxlength)
//{
//	int count = 0;
//	char* username = (char*)malloc((maxlength + 1) * sizeof(char));
//	char* password = (char*)malloc((maxlength + 1) * sizeof(char));
//	if (username == NULL || password == NULL) {
//		fprintf(stderr, "内存分配失败\n");
//		free(username);
//		free(password);
//		return;
//	}
//	while (count < 3)
//	{
//		printf("\n登录\nusername:");
//		fgets(username, maxlength+1, stdin);
//		username[strcspn(username, "\n")] = '\0';/*string scan complement span(字符串扫描补集长度）
//													strscsp(char*str1,char*str2);计算从字符串str1开始
//													不包含指定字符串str2任何字符的长度
//													strcspn 和 strscpn本质一样但有些编译器支持其中某一个*/
//		printf("\npassword:");
//		fgets(password, maxlength+1, stdin);
//		password[strcspn(password, "\n")] = '\0';
//		for (int i = 0; i < n; i++)
//		{
//			if (strcmp(username, users[i].username) == 0)
//			{
//				if (strcmp(password, users[i].password) == 0)
//				{
//					free(username);
//					free(password);
//					printf("登录成功！");
//					return;
//				}
//			}
//		}
//		count++;
//		if (count < 3)
//		{
//			printf("登陆失败，请重新输入! (剩余尝试次数: %d)\n", 3 - count);
//		}
//		else
//		{
//			printf("end!");
//			return;
//		}
//	}
//}
//int main()
//{
//	printf("请输入user个数，及最大长度:");
//	int n, maxlength,choice;
//	while (scanf("%d %d", &n, &maxlength) != 2)
//	{
//		printf("输入错误，请重新输入:");
//		clear_input_buffer();
//	}
//	printf("请选择输入方式(1、自动随机输入. 2、手动输入.):");
//	start:
//	scanf("%d", &choice);
//	if (choice != 1 && choice != 2)
//	{
//		printf("error choice!input again:");
//		clear_input_buffer();
//		goto start;
//	}
//	Users* users;
//	users = (Users*)calloc(n ,sizeof(Users));
//	input(users, n, maxlength, choice);
//	for (int i = 0; i < n; i++)
//	{
//		printf("\nusername[%d]: %s\npassword[%d]: %s\n", i + 1, (users + i)->username, i + 1, (*(users + i)).password);
//	}
//	login(users, n, maxlength);
//	freeusers(users, n);
//	return 0;
//}
