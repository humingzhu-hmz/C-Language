//#include <stdio.h>
//#include <stdlib.h>
//void test()
//{
//	int arr[50][2]={0}, n = 0;
//	for (int i = 0; i <= 19; i++)
//	{
//		scanf_s("%d", &arr[i][0]);
//		n++;
//		arr[i][1] = i + 1;
//		int ch = getchar();
//		if (ch == '\n')
//		{
//			break;
//		}
//		else
//			ungetc(ch, stdin);
//		
//
//	}
//	for (int i = 1; i < n; i++)
//	{
//		int flag = 1;
//		for (int j = n - 1; j >= i; j--)
//		{
//			if (arr[j][0] < arr[j - 1][0])
//			{
//				int temp1 = arr[j][0];
//				arr[j][0] = arr[j - 1][0];
//				arr[j - 1][0] = temp1;
//				int temp2 = arr[j][1];
//				arr[j][1] = arr[j - 1][1];
//				arr[j - 1][1] = temp2;
//				flag = 0;
//			}
//		}
//		if (flag == 1)
//			break;
//	}
//	printf("n=%d\n", n);
//	for (int i = 0; i < n; i++)
//	{
//			printf(" %2d %2d\n", arr[i][0],arr[i][1]);
//	}
//}
//
//
//
//int main()
//{
//	test();
//	return 0;
//}