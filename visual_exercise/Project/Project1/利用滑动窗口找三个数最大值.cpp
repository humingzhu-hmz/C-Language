//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//int movewindow( long int arr[], int windowlong, int arrlong)
//{
//	long int summax = 0;
//	if (windowlong >arrlong)
//		return 0;
//	for (int i = 0; i < windowlong; i++)
//		summax += arr[i];
//	long int nsum = summax;
//		for (int i = 0; i <= arrlong-windowlong-1; i++)
//		{
//			 nsum += arr[windowlong + i] - arr[i];
//			summax = summax > nsum ? summax : nsum;
//		}
//		return summax;
//}
//void main()
//	{
//	long int  arr[5];
//	printf("请输入几个整数:");
//	for (int i = 0; i <= 4; i++)
//		scanf("%ld", &arr[i]);
//	int arrlong = sizeof(arr) / sizeof(arr[0]);
//	long int summax = movewindow(arr, 3, arrlong);
//	printf("%ld", summax);
//
//	}