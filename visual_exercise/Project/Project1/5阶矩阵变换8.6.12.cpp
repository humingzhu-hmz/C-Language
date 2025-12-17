//#include <stdio.h>
//void change1(int* arr)
//{
//	for (int i = 5; i < 10; i++)
//	{
//		int temp = arr[i];
//		arr[i] = arr[i + 15];
//		arr[i + 15] = temp;
//	}
//}
//
//void change2(int arr[])
//{
//	for (int i = 0, j = 0; i < 25; i += 5, j += 6)
//	{
//		for (int k = 0; k < 5; k++)
//		{
//			if (arr[j] != 0)  // ·ÀÖ¹³ýÁã
//				arr[i + k] = arr[i + k] / arr[j];
//		}
//	}
//}
//int main()
//{
//	int i=0, arr[25] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };
//	printf("Ô­¾ØÕó:\n	");
//	while (i< 25)
//	{
//		printf("%-3d ", arr[i]);
//		i++;
//		if (i % 5 == 0 && i != 0)
//			printf("\n	");
//	}
//	printf("\n");
//	change1(arr);
//	i = 0;
//	printf("change1ºó:\n\n	");
//	while (i< 25)
//	{
//		printf("%-3d ", arr[i]);
//		i++;
//		if (i % 5 == 0 && i != 0)
//			printf("\n	");
//	}
//	printf("\n");
//	change2(arr);
//	i = 0;
//	printf("change2ºó:\n\n	");
//	while (i< 25)
//	{
//		printf("%-3d ", arr[i]);
//		i++;
//		if (i % 5 == 0 && i != 0)
//			printf("\n	");
//	}
//}