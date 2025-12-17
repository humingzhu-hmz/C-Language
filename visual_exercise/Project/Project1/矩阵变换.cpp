//#include <stdio.h>
//int main()
//{
//	int arr[5][5],temp=0;
//		for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				scanf_s("%d", &arr[i][j]);
//			}
//		}
//		for(int i=0;i<5;i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				if (arr[2][2] < arr[i][j])
//				{
//					temp = arr[2][2];
//					arr[2][2] = arr[i][j];
//					arr[i][j] = temp;
//				}
//				if (arr[0][0] > arr[i][j])
//				{
//					temp = arr[0][0];
//					arr[0][0] = arr[i][j];
//					arr[i][j] = temp;
//				}
//			}
//			
//		}
//		for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				if(i==0&&j==0)
//					continue;
//				if (arr[0][4] > arr[i][j])
//				{
//					temp = arr[0][4];
//					arr[0][4] = arr[i][j];
//					arr[i][j] = temp;
//				}
//			}
//
//		}
//		for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				if (i == 0 && (j == 0||j==4))
//					continue;
//				if (arr[4][4] > arr[i][j])
//				{
//					temp = arr[4][4];
//					arr[4][4] = arr[i][j];
//					arr[i][j] = temp;
//				}
//			}
//
//		}
//		for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				if ((i == 0 && (j == 0 || j == 4)) || (i == 4 && j == 4))
//					continue;
//				if (arr[4][0] > arr[i][j])
//				{
//					temp = arr[4][0];
//					arr[4][0] = arr[i][j];
//					arr[i][j] = temp;
//				}
//			}
//
//		}
//		for(int i =0;i<5;i++)
//		{
//			for(int j=0;j<5;j++)
//			{
//				printf(" %2d ",arr[i][j]);
//			}
//			printf("\n");
//		}
//	return 0;
//}





////written by other
//#include <stdio.h>
//void change__(int(*m)[5])
//{
//	int maax = 0;
//	int maxi;
//	int maxj;
//	int a[4] = { 26, 26, 26, 26 };
//	int pa[4][2] = { 0,0,0,0,0,0,0,0 };
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			int num = *(*(m + i) + j);
//			if (num > maax)
//			{
//				maax = *(*(m + i) + j);
//				maxi = i;
//				maxj = j;
//			}
//			if (num < a[3])
//			{
//				a[3] = num;
//				pa[3][0] = i;
//				pa[3][1] = j;
//				int i1 = 3;
//				while (i1 > 0 && a[i1] < a[i1 - 1])
//				{
//					change(&a[i1], &a[i1 - 1]);
//					change(&pa[i1][0], &pa[i1 - 1][0]);
//					change(&pa[i1][1], &pa[i1 - 1][1]);
//					i1 = i1 - 1;
//				}
//			}
//		}
//	}
//	printf("最小的数值依次为:\n");
//	prinw(a, 4);
//	printf("对应的坐标为:\n");
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 2; j++)
//		{
//			printf("%d\t", pa[i][j]);
//		}
//		printf("\n");
//	}
//	change(*(m + 2) + 2, *(m + maxi) + maxj);
//	for (int i = 0; i < 4; i++)
//	{
//		if (pa[i][0] == 2 && pa[i][1] == 2)
//		{
//			pa[i][0] = maxi;
//			pa[i][1] = maxj;
//		}
//
//	}
//	change(*(m), *(m + pa[0][0]) + pa[0][1]);
//	for (int i = 1; i < 4; i++)
//	{
//		if (pa[i][0] == 0 && pa[i][1] == 0)
//		{
//			pa[i][0] = pa[0][0];
//			pa[i][1] = pa[0][1];
//		}
//
//	}
//	change(*(m)+4, *(m + pa[1][0]) + pa[1][1]);
//	for (int i = 2; i < 4; i++)
//	{
//		if (pa[i][0] == 0 && pa[i][1] == 4)
//		{
//			pa[i][0] = pa[1][0];
//			pa[i][1] = pa[1][1];
//		}
//
//	}
//	change(*(m + 4), *(m + pa[2][0]) + pa[2][1]);
//	for (int i = 3; i < 4; i++)
//	{
//		if (pa[i][0] == 4 && pa[i][1] == 0)
//		{
//			pa[i][0] = pa[2][0];
//			pa[i][1] = pa[2][1];
//		}
//	}
//	change(*(m + 4) + 4, *(m + pa[3][0]) + pa[3][1]);
//
//
//	printf("转换完成后的结果为:\n");
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			printf("%d\t", *(*(m + i) + j));
//		}
//		printf("\n");
//	}
//}










////void change__(int(*m)[5])
////{
////	int maax = 0;
////	int maxi;
////	int maxj;
////	int a[4] = { 26, 26, 26, 26 };
////	int pa[4][2] = { 0,0,0,0,0,0,0,0 };
////	for (int i = 0; i < 5; i++)
////	{
////		for (int j = 0; j < 5; j++)
////		{
////			int num = *(*(m + i) + j);
////			if (num > maax)
////			{
////				maax = *(*(m + i) + j);
////				maxi = i;
////				maxj = j;
////			}
////			if (num < a[3])
////			{
////				a[3] = num;
////				pa[3][0] = i;
////				pa[3][1] = j;
////				int i1 = 3;
////				while (i1 > 0 && a[i1] < a[i1 - 1])
////				{
////					change(&a[i1], &a[i1 - 1]);
////					change(&pa[i1][0], &pa[i1 - 1][0]);
////					change(&pa[i1][1], &pa[i1 - 1][1]);
////					i1 = i1 - 1;
////				}
////			}
////		}
////	}
////	printf("最小的数值依次为:\n");
////	printf(a, 4);
////	printf("对应的坐标为:\n");
////	for (int i = 0; i < 4; i++)
////	{
////		for (int j = 0; j < 2; j++)
////		{
////			printf("%d\t", pa[i][j]);
////		}
////		printf("\n");
////	}
////	change(*(m + 2) + 2, *(m + maxi) + maxj);
////	for (int i = 0; i < 4; i++)
////	{
////		if (pa[i][0] == 2 && pa[i][1] == 2)
////		{
////			pa[i][0] = maxi;
////			pa[i][1] = maxj;
////		}
////
////	}
////	change(*(m), *(m + pa[0][0]) + pa[0][1]);
////	for (int i = 1; i < 4; i++)
////	{
////		if (pa[i][0] == 0 && pa[i][1] == 0)
////		{
////			pa[i][0] = pa[0][0];
////			pa[i][1] = pa[0][1];
////		}
////
////	}
////	change(*(m)+4, *(m + pa[1][0]) + pa[1][1]);
////	for (int i = 2; i < 4; i++)
////	{
////		if (pa[i][0] == 0 && pa[i][1] == 4)
////		{
////			pa[i][0] = pa[1][0];
////			pa[i][1] = pa[1][1];
////		}
////
////	}
////	change(*(m + 4), *(m + pa[2][0]) + pa[2][1]);
////	for (int i = 3; i < 4; i++)
////	{
////		if (pa[i][0] == 4 && pa[i][1] == 0)
////		{
////			pa[i][0] = pa[2][0];
////			pa[i][1] = pa[2][1];
////		}
////	}
////	change(*(m + 4) + 4, *(m + pa[3][0]) + pa[3][1]);
////
////
////	printf("转换完成后的结果为:\n");
////	for (int i = 0; i < 5; i++)
////	{
////		for (int j = 0; j < 5; j++)
////		{
////			printf("%d\t", *(*(m + i) + j));
////		}
////		printf("\n");
////	}
////}