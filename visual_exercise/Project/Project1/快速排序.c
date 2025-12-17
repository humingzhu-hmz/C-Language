//#include <stdio.h>
//#include <stdlib.h>
//int partition(int* data, int pivot, int left, int right )
//{
//	int temp = data[pivot];
//	data[pivot] = data[right];
//	data[right] = temp;
//	pivot = data[right];//基准归右
//	while (left < right)
//	{
//		while (data[left] <= pivot)
//		{
//			left++;
//		}
//		data[right] = data[left];
//		while (data[right] >= pivot)
//		{
//			right--;
//		}
//		data[left] = data[right];
//	}
//	pivot = left;
//	return pivot;
//}
////随即基准
//int randpivot(int left, int right)
//{
//	int pivot = rand() % (right - left + 1) + left;
//	return pivot;
//}
//void qsort(int* data,int left, int right)
//{
//	int pivot = randpivot(left, right);
//	pivot = partition(data, pivot,left, right);
//	if (left < right)
//	{
//		qsort(data, left, pivot - 1);
//		qsort(data, pivot + 1, right);
//	}
//}
//void Qsort(int* data)
//{
//	qsort(data, 0, sizeof(data)/sizeof(int));
//}
//
//// partition ：vt分区 n划分  pivot : n中心，枢纽