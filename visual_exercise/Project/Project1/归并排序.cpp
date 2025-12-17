//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//void merge(int* nums, int left, int right, int* temp)
//{
//	int i = left,k=left,mid=left+(right-left)/2,j=mid+1;
//	while (i <= mid && j <= right)
//	{
//		if (nums[i] <= nums[j])
//		{
//			temp[k++] = nums[i++];
//		}
//		else
//			temp[k++] = nums[j++];
//	}
//	while (i <= mid)
//	{
//		temp[k++] = nums[i++];
//	}
//	while (j <= right)
//	{
//		temp[k++] = nums[j++];
//	}
//	for (int i = left; i <= right; i++)
//	{
//		nums[i] = temp[i];
//	}
//}
//void mergesort(int* nums, int left, int right,int*temp)
//{
//	if (left < right)
//	{
//		int mid = left + (right - left) / 2;
//		mergesort(nums, left, mid,temp);
//		mergesort(nums, mid + 1, right,temp);
//		merge(nums, left, right, temp);
//	}
//}
//void Mergesort(int* nums, int numsSize)
//{
//	int* temp = (int*)malloc(numsSize * sizeof(int));
//	if (!temp)
//	{
//		fprintf(stderr, "ÄÚ´æ·ÖÅäÊ§°Ü£¬³ÌÐò½áÊø£¡");
//		exit(1);
//	}
//	mergesort(nums, 0, numsSize-1,temp);
//	free(temp);
//}
//int main()
//{
//	srand((unsigned int)time(NULL));
//	int numsSize = rand() % 200 + 10;
//	int* nums = (int*)malloc(numsSize * sizeof(int));
//	printf("ÅÅÐòÇ°.\n");
//	for (int i = 0; i < numsSize; i++)
//	{
//		*(nums + i) = rand() % 10000000;
//		printf("nums[%d]= %-7d\n", i, nums[i]);
//	}
//	Mergesort(nums, numsSize);
//	printf("ÅÅÐòºó.\n");
//	for (int i = 0; i < numsSize; i++)
//	{
//		printf("nums[%d]= %-7d\n", i, nums[i]);
//	}
//	return 0;
//}