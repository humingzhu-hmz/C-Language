//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//int primeCount(int n)
//{
//	if (n < 2)
//	{
//		return 0;
//	}
//	if (n == 2)
//	{
//		printf("2\n");
//		return 1;
//	}
//	int* prime = (int*)calloc(n, sizeof(int));
//	typedef struct Prime
//	{
//		int prime;
//		struct Prime* next;
//	}Prime;
//	int count = 1;
//	Prime *headp=(Prime*)malloc(sizeof(Prime));
//	Prime* current = headp;
//	headp->prime = 2;
//	headp->next = NULL;
//	for (int i = 3; i <= n; i++)
//	{
//		if (!prime[i - 1])
//		{
//			Prime* temp = headp;
//			while (i % temp->prime && temp->prime * temp->prime < n)//不可能有质因数均大于sqrt(n)
//			{
//				if (i * temp->prime <= n)
//				{
//					prime[i * temp->prime - 1] = 1;
//				}
//				if (temp->next)
//				{
//					temp = temp->next;
//				}
//				else
//				{
//					break;
//				}
//			}
//			if ((temp->next == NULL && i % temp->prime) || temp->prime * temp->prime > n)//排除极端情况，最后一个质数恰好时I的最小质因数
//			{
//				while (temp->next != NULL)
//				{
//					temp = temp->next;//将临时指针置于末尾，保证素数从到到校添加.因为可能终止是因为检查
//										//到了temp->prime大于根号n,
//										// 此时添加会让大素数被添加至中间
//				}
//				Prime* newp = (Prime*)malloc(sizeof(Prime));
//				newp->prime = i;
//				newp->next = temp->next;
//				temp->next = newp;
//				count++;
//			}
//			else
//			{
//				prime[i - 1] = 1;
//			}
//			if (i == n)
//			{
//				temp = NULL;
//			}
//		}
//	}
//	if (n == 3)
//	{
//		count++;
//	}
//	if (current)
//	{
//		printf("1-n的素数有:\n");
//	}
//	while (current)
//	{
//		printf(" %3d\t", current->prime);
//		Prime* temp = current;
//		current = current->next;
//		free(temp);
//	}
//	free(prime);
//	return count;
//}
//int main()
//{
//	int n;
//	fprintf(stdout, "线性筛，请输入n:");
//	fscanf_s(stdin, "%d", &n);
//	fprintf(stdout, "\n1-n的素数个数:%d", primeCount(n));
//}