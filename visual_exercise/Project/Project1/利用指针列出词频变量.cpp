//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
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
//			str = temp;
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
//	return str;
//}
//int findcommenword(char** wordlist, char* word, int len)
//{
//	for (int i = 0; i < len; i++)
//	{
//		if (strcmp(*(wordlist + i), word) == 0)
//		{
//			return 1;
//		}
//	}
//		return 0;
//}
//int freearr(char** wordlist)
//{
//	int i = 0;
//	while (wordlist[i] != NULL)
//	{
//		free(*(wordlist + i));
//		i++;
//	}
//	free(wordlist);
//	return 0;
//}
//char** fetchword(char* input)
//{
//	int wordstart=0, wordend, i = 0, listlen = 0, initcap = 8, currentcap = initcap;
//	char** wordlist;
//	char** temp = (char**)calloc(initcap, sizeof(char*));
//	if (temp == NULL)
//	{
//		fprintf(stderr, "内存分配失败\n");
//		return NULL;
//	}
//	else
//	{
//		wordlist = temp;
//	}
//	char* word;
//	while (input[i]!='\0')
//	{
//		if (!isalpha(input[i++]) && (input[i] != 39))//跳过非字母字符和撇号
//		{
//			wordstart = i;
//		}
//		else
//		{
//			while (isalpha(input[i])||(input[i]==39))
//			{
//				i++;
//			}
//			wordend = i;
//			size_t wordlen = wordend - wordstart+1;
//			word = (char*)calloc(wordlen, sizeof(char));
//			strncpy(word, input + wordstart , wordlen - 1);
//			word[wordlen - 1] = '\0';
//			int a = findcommenword(wordlist, word, listlen);
//			if (a == 1)
//			{
//				free(word);
//				continue;
//			}
//			else
//			{
//				wordlist[listlen] = word;
//				listlen++;
//				if (listlen + 1 == currentcap)
//				{
//					int newcap = currentcap + ((currentcap >> 1) >> 1);
//					char** temp = (char**)realloc(wordlist, newcap * sizeof(char*));
//					if (temp == NULL)
//					{
//						fprintf(stdout, "内存再分配失败\n");
//						free(temp);
//						wordlist[listlen] = NULL;
//						return wordlist;
//					}
//					currentcap = newcap;
//					wordlist = temp;
//				}
//			}
//
//		}
//	}
//	char** finalcap = (char**)realloc(wordlist, (listlen+1) * sizeof(char*));
//	finalcap[listlen] = NULL;
//	if (finalcap != NULL)
//	{
//		wordlist = finalcap;
//		return wordlist;
//	}
//	return wordlist;
//}
//
//	int main()
//	{
//		int i = 0;
//		fprintf(stdout, "请输入一行文本(以回车结束):");
//		char* str = input();
//		fprintf(stdout, "\n -------------------------------------------------------------");
//		fprintf(stdout, "\n您输入的文本是:");
//		while (*(str+i) != '\0')
//		{
//			fprintf(stdout, "%c", *(str+i));
//			i++;
//		}
//		fprintf(stdout, "\n -------------------------------------------------------------");
//		fprintf(stdout, "\n");
//		char**wordlist=fetchword(str);
//		fprintf(stdout, "文本中的不同单词有:");
//		for (int i = 0; wordlist[i] != NULL; i++)
//		{
//			fprintf(stdout, " %s", *(wordlist + i));
//		}
//		fprintf(stdout, "\n -------------------------------------------------------------");
//		freearr(wordlist);
//		free(str);
//		return 0;
//	}
//	