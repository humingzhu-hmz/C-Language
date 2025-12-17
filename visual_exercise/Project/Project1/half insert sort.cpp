//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//void halfinsertsort(int* arr, int arrlenth)
//{
//	for (int i = 0; i < arrlenth; i++)
//	{
//		int left = 0, right = i - 1, mid = (left + right) / 2;
//		while (left <= right)
//		{
//			if (arr[i] < arr[mid])
//			{
//				right = mid - 1;
//				mid = (left + right) / 2;
//			}
//			else
//			{
//				left = mid + 1;
//				mid = (left + right) / 2;
//			}
//		}
//		int temp = arr[i];
//		for (int k = i - 1; k >= left; k--)
//		{
//			arr[k + 1] = arr[k];
//		}
//		arr[left] = temp;
//	}
//}
//int main()
//{
//	int arr[20];
//	srand((unsigned int)time(NULL));
//	for (int i = 0; i < 20; i++)
//	{
//		arr[i] = rand() % 50;
//		printf("%3d", arr[i]);
//	}
//	printf("\n");
//	halfinsertsort(arr, sizeof(arr) / sizeof(int));
//	for (int i = 0; i < 20; i++)
//	{
//		printf("%3d", arr[i]);
//	}
//	return 0;
//}