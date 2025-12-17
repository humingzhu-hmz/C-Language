//#include <stdio.h>
//#include <string.h>
//#include <ctype.h>
//int main()
//{
//	char documents[3][81];
//	char vocabs[120][13];
//	char word[13];
//	int vocableng = 0;
//	int docfrequence[3][120] = { 0 };
//	int i, m,r, k = 0;
//	printf("please input 3 documents\n");
//	for (i = 0; i <= 2; i++)
//	{
//		printf("ÇëÊäÈë documents%2d:", i+1);
//		printf("\n	");
//		fgets(documents[i], 81, stdin);
//	}
//	for (i = 0; i < 3; i++)
//	{
//		for (m = 0; m < strlen(documents[i]); m++)
//		{
//			if (isalpha(documents[i][m])==0)
//			{
//				word[k] = '\0';
//				for ( r = 0; r < vocableng; r++)
//				{
//					if (strcmp(word, vocabs[r]) == 0)
//					{
//						word[0] = '\0';
//						k = 0;
//						break;
//					}
//				}
//				if (r == vocableng&&k>0)
//				{
//					strcpy_s(vocabs[vocableng], word);
//					vocableng++;
//					word[0] = '\0';
//					k = 0;
//				}
//			}
//			else
//				word[k++] = documents[i][m];
//		}
//
//	}
//	for (i = 0; i < 3; i++)
//	{
//		for (m = 0; m < strlen(documents[i]); m++)
//		{
//			if (isalpha(documents[i][m]) == 0)
//			{
//				word[k] = '\0';
//				for ( r = 0; r < vocableng; r++)
//				{
//					if (strcmp(word, vocabs[r]) == 0)
//						docfrequence[i][r]++;
//					
//				}
//				if(r==vocableng)
//				{
//					word[0] = '\0';
//					k = 0;
//				}
//			}
//			else
//				word[k++] = documents[i][m];
//		}
//	}
//	puts(" ------------------------------------------------------------------------------------------------------------\n");
//	printf(" vocabs:          ");
//	for (int x = 0; x < vocableng; x++)
//	{
//		printf("%8s ", vocabs[x]);
//	}
//	puts("\n ------------------------------------------------------------------------------------------------------------\n");
//	for (i = 0; i <= 2; i++)
//	{
//		printf(" docfrequence %2d:", i);
//		for (int m = 0; m < vocableng; m++)
//		{
//			printf(" %8d", docfrequence[i][m]);
//		}
//		printf("\n");
//	}
//	puts(" ------------------------------------------------------------------------------------------------------------");
//	return 0;
//}
//	
//	
