//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//void halfinsertsort(int* arr, int step,int arrlenth)
//{
//	for (int start = 0; start < step; start++)
//	{
//		for (int j = start+step; j < arrlenth; j += step)
//		{
//			int left = start, right = j - step, mid = left+(right-left)/(2*step)*step, piont = arr[j];
//			while (left <= right)
//			{
//				if (piont < arr[mid])
//				{
//					right = mid - step;
//					mid = left + (right - left) / (2 * step) * step;
//				}
//				else
//				{
//					left = mid + step;
//					mid = left + (right - left) / (2 * step) * step;
//				}
//			}
//			for (int k = j - step; k >= left; k -= step)
//			{
//				arr[k + step] = arr[k];
//			}
//			arr[left] = piont;
//		}
//	}
//}
//void shellsort(int* arr,int arrlenth)
//{
//	int d = (arrlenth) / 2;
//	while (d > 0)
//	{
//		halfinsertsort(arr, d,arrlenth);
//		d = d / 2;
//	}
//}
//
//int main()
//{
//	srand((unsigned int)time(NULL));
//	int arr[20];
//	int arrlenth = sizeof(arr) / sizeof(int);
//	for (int k = 0; k < arrlenth; k++)
//	{
//		arr[k] = rand() % 20;
//		printf("%-2d ", arr[k]);
//	}
//	printf("\n");
//	shellsort(arr, arrlenth);
//	for (int k = 0; k < arrlenth; k++)
//	{
//		printf("%-2d ", arr[k]);
//	}
//}