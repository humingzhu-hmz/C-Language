//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//void auto_generatenums(int* arr, int n)
//{
//	for(int i=0;i<n;i++)
//	{
//		arr[i]= i+1;
//	}
//}
//void auto_generate_randnums1(int arr[],int n, int range)
//{
//	srand((unsigned int)time(NULL));
//	for (int i = 0; i < n; i++)
//	{
//		arr[i] = rand() %range +1;
//	}
//}
//void auto_generate_randnums2(int arr[],int n,int range)
//{
//	auto_generate_randnums1( arr,  n,range);
//	srand((unsigned int)time(NULL));
//	int hashtable[100000];
//	memset(hashtable, -1, sizeof(hashtable));
//	for (int i = 0; i < n; i++)
//	{start:
//		if (hashtable[arr[i]] == -1)
//		{
//			hashtable[arr[i]] = 0;
//		}
//		else 
//		{
//			arr[i] = rand() % range + 1;
//			goto start;
//		}
//	}
//	/*for(int i=n-1;i>0;i--)
//	{
//		int j=rand()%(i+1);
//		int temp = arr[i];
//		arr[i] = arr[j];
//		arr[j] = temp;
//	}*/
//}
//int shuru(int arr[],int range)
//{
//	int i;
//	for (i = 0; i < range; i++)
//	{
//	int ch = getchar();
//	if (ch == '\n')
//	{
//		break;
//	}
//	else
//	{
//		ungetc(ch, stdin);
//	}
//	scanf_s("%d", &arr[i]);
//	}
//	return i;
//}
//void ordering(int *arr,int n)
//{
//	for (int j = 0; j < n - 1; j++)
//	{
//		int flag = 0;
//		for (int m = 0; m < n - 1-j; m++)
//		{
//			if (arr[m] > arr[m + 1])
//			{
//				int temp = arr[m];
//				arr[m] = arr[m + 1];
//				arr[m + 1] = temp;
//				flag = 1;
//			}
//		}
//		if(flag==0)
//			break;
//	}
//}
//void insertion_sort(int x,int n,int arr[])
//{
//	/*int mini = 0, maxi = n, i=(int)((mini+maxi)/2);
//	while (1)
//	{
//		if ((arr[i] < x) && (arr[i + 1] < x)&&(i<=n-2))
//		{
//			mini=i;
//			i = (int)((mini + maxi) / 2);
//			if(i==n-1)
//			{
//				goto start;
//			}
//			continue;
//		}
//		if ((arr[i] > x) && (arr[i + 1] > x))
//		{
//			 maxi =i;
//			 if (i == 0)
//			 {
//				 i = -1;
//				 goto start;
//			 }
//			i = (int)((mini + maxi) / 2);
//			continue;
//		}
//		else
//		{
//		start:
//			int m = n-1;
//			while (m > i)
//			{
//				arr[m + 1] = arr[m];
//				m--;
//
//			}
//		}
//		arr[i + 1] = x;
//		break;
//	}*/
//	int pos = n;
//	for(int i=n-1;i>=0;i--)
//	{
//		if(arr[i]<=x)
//		{
//			pos = i + 1;
//			break;
//		}
//		pos = 0;
//	}
//	for (int m = n - 1; m >= pos; m--)
//	{
//		arr[m + 1] = arr[m];
//	}
//	arr[pos] = x;
//}
//int main()
//{
//	int arr[1001], n,y,range;
//	printf("请输入数组的长度和数的最大值:");
//start:
//	scanf_s("%d%d", &n,&range);
//	if (n <= 0)
//	{
//		printf("数组长度必须大于0，请重新输入:");
//		goto start;
//	}
//	if (range <= 0)
//	{
//		printf("数的最大值必须大于0，请重新输入:");
//		goto start;
//	}
//	if (n > range)
//	{
//		printf("数组长度不能大于数的最大值，请重新输入:");
//		goto start;
//	}
//	printf("请选择生成数组的方式:\n");
//start3:
//	printf("1.手动输入\n2.自动生成有序数组\n3.自动生成随机数组\n4.自动生成随机乱序数组(不重复）\n");
//	if (scanf_s("%d", &y) != 1)
//	{
//		printf("输入有误，请重新选择:\n");
//		while (getchar() != '\n');
//		goto start3;
//	}
//	if(y<1||y>4)
//	{
//		printf("输入有误，请重新选择:\n");
//		goto start3;
//	}
//	switch (y)
//	{
//		case 1:shuru(arr,range); break;
//		case 2:auto_generatenums(arr, n); break;
//		case 3:auto_generate_randnums1(arr, n, range); break;
//		case 4:auto_generate_randnums2(arr, n, range); break;
//	
//	}
//	printf("生成的数组为:\n	");
//	for (int m = 0; m < n; m++)
//	{
//		printf(" %d", arr[m]);
//	}
//	ordering(arr,n);
//	printf("\n输入的数组初始排序为:\n	");
//	for (int m = 0; m < n; m++)
//	{
//		printf(" %d", arr[m]);
//	}
//	printf("\n请输入一个数:");
//	start2:
//	int x;
//	if (scanf_s("%d", &x) != 1)
//	{
//		printf("输入有误，请重新输入一个数:");
//		while (getchar() != '\n');
//		goto start2;
//	}
//	insertion_sort(x,n,arr);
//	printf("插入%d后的数组为:\n	", x);
//	for (int m = 0; m < n + 1; m++)
//	{
//		printf(" %d", arr[m]);
//	}
//	printf("\n");
//	printf("回车结束程序，否则输入continue并按回车继续：");
//	getchar();
//	int ch = getchar();
//	if (ch == '\n')
//		return 0;
//	else
//	{
//		while (getchar() != '\n');
//		main();
//	}
//	
//}
