//#include <stdio.h>
//int main()
//{
//	int bridge[4][4] = { {0,2,1,0},{2,0,2,1},{1,2,0,2},{0,1,2,0} }, degrees[4] = { 0,0,0,0 };
//	printf("birdge[i][j]表示第i块陆地与第j块陆地之间的桥数.\n");
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			printf("bridge[%d][%d]=%d\n", i+1, j+1, bridge[i][j]);
//			degrees[i] += bridge[i][j];
//		}
//	}
//	printf("各陆地桥数:");
//	for (int i = 0; i < 4; i++)
//	{
//		printf("%d ", degrees[i]);
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		if (degrees[i] % 2 != 0)
//		{
//			printf("\n存在桥数为奇数的陆地，无欧拉回路.");
//				return 0;
//		}
//	}
//}