//#include <stdio.h>
///*计算500被分成 50 20 10 5的接的个数，每个都必须至少有一个*/
//int main()
//{
//	int x = 500-50-10-5;
//	int arr[10000][4];
//	int count=0,k=0;
//	int n1 = x / 50, n2 = x / 20,n3 = x / 10, n4 = x / 5;
//	for (int a = 0; a < n1 + 1; a++)
//	{
//		for (int b = 0; b < n2 + 1; b++)
//		{
//			for (int c = 0; c < n3 + 1; c++)
//			{
//				for(int d =0;d<n4+1;d++)
//					if (x == 50 * a + 20 * b + 10 * c + 5 * d)
//					{
//						count++;
//						arr[k][0] = a+1;
//						arr[k][1] = b+1;
//						arr[k][2] = c+1;
//						arr[k][3] = d+1;
//						k++;
//					}
//			}
//		}
//	}
//	puts("----------------------------------------------------------\n");
//	printf("            50      20      10      5");
//	printf("\n方法数%d", count);
//	for (int m = 0; m < k; m++)
//	{
//		printf("\n解法%3d:", m + 1);
//		for (int n = 0; n <= 3; n++)
//			printf("    %d\t", arr[m][n]);
//	}
//	return 0;
//}