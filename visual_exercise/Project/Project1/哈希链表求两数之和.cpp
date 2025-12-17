//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <time.h>
//typedef struct hashnode {
//	int key;
//	int value;
//	struct hashnode* next;
//}hashnode;
//typedef struct hashtable
//{
//	int capasity;
//	hashnode** table;
//}hashtable;
//void hashfree(hashtable* ht)
//{
//	if (ht == NULL)
//	{
//		return;
//	}
//	for (int i = 0; i < ht->capasity; i++)
//	{
//		hashnode* current = ht->table[i];
//		while (current != NULL)
//		{
//			hashnode* temp = current;
//			current = current->next;
//			free(temp);
//			temp = NULL;
//		}
//		ht->table[i] = NULL;
//	}
//	free(ht->table);
//	free(ht);
//}
//int* twoSum(int* nums, int numSize, int target, int* returnSize)
//{
//
//	hashtable* ht = (hashtable*)malloc(sizeof(hashtable));
//	ht->capasity = numSize;
//	ht->table = (hashnode**)calloc(ht->capasity, sizeof(hashnode*));
//
//	for (int i = 0; i < numSize; i++)
//	{
//		int complement = (abs(target - nums[i])) % ht->capasity;
//		int index = (abs(nums[i])) % ht->capasity;
//		hashnode* newnode = (hashnode*)malloc(sizeof(hashnode));
//		newnode->key = nums[i];
//		newnode->value = i;
//		if (ht->table[complement] == NULL)
//		{
//			newnode->next = ht->table[index];
//			ht->table[index] = newnode;
//		}
//		else
//		{
//			hashnode* temp = ht->table[complement];
//			while (temp != NULL)
//			{
//				if (temp->key == target - nums[i])
//				{
//					int* result = (int*)malloc(2 * sizeof(int));
//					result[0] = temp->value;
//					result[1] = i;
//					*returnSize = 2;
//					hashfree(ht);
//					return result;
//				}
//				temp = temp->next;
//			}
//			newnode->next = ht->table[index];
//			ht->table[index] = newnode;
//		}
//	}
//	hashfree(ht);
//	return NULL;
//}
//int main()
//{
//	srand((unsigned int)time(NULL));
//	int n,target;
//	printf("请输入数组个数:");
//	scanf_s("%d", &n);
//	printf("生成数组为;");
//	int* nums = (int*)malloc(n * sizeof(int));
//  srand((unsigned int)time(NULL));
//	for (int i = 0; i < n; i++)
//	{
//		nums[i] = rand() % 201 - 100;
//		printf(" %d ", nums[i]);
//	}
//	printf("\ntarget:");
//	scanf_s("%d", &target);
//	int*returnSize=(int *)malloc(2*sizeof(int));
//	int *result =twoSum(nums, n, target, returnSize);
//	if (result == NULL)
//	{
//		printf("未找到匹配数对！");
//		free(nums);
//		return 0;
//	}
//	printf("索引：%d %d\n", result[0],result[1]);
//	free(nums);
//	return 0;
//}