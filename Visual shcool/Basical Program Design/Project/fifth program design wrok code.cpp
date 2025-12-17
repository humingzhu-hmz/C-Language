//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//float exe1(int n)//pi 前n项
//{
//	if (n == 0)
//		return 1;
//	return pow((2 * n), 2) / ((2 * n - 1) * (2 * n + 1)) * exe1(n - 1);
//}
//int exe2(int n)
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
//int exe3()
//{
//	int count = 0,x,sum=0;
//	while (1)
//	{
//		if (scanf("%d",&x) != 1)
//		{
//			printf("输入有误，重新输入！\n");
//			continue;
//		}
//		if (x == -1)
//		{
//			printf("偶数个数%d，偶数平均数%f", count,sum/count);
//			return 0;
//		}
//		if (x % 2 == 0)
//		{
//			count++;
//			sum += x;
//		}
//	}
//}
//int exe4(char a)
//{
//	if (!isupper(a))
//	{
//		printf("非大写字母！");
//		return 0;
//	}
//	for (char i = 'A'; i <= a; i++)
//	{
//		printf("%*c", (int)(a - 'A'), ' ');
//		for (char j = 'A'; j < i; j++)
//		{
//			printf("%2c", j);
//		}
//		printf("%2c", i);
//		for (char j = i - 1; j >= 'A'; j--)
//		{
//			printf("%2c", j);
//		}
//	}
//	return 0;
//}
//int divisorsum(int n)
//{
//	int temp = n;
//	long long divisor_count = 1;  
//	long long divisor_sum = 1;    
//	int count = 0;
//	while (temp % 2 == 0) {
//		count++;
//		temp /= 2;
//	}
//	if (count > 0) {
//		divisor_count *= (count + 1);
//		divisor_sum *= ((long long)pow(2, count + 1) - 1);
//	}
//	for (int i = 3; i * i <= temp; i += 2) {
//		count = 0;
//		while (temp % i == 0) {
//			count++;
//			temp /= i;
//		}
//		if (count > 0)
//		{
//			divisor_count *= (count + 1);
//			long long tempsum = (pow(i,count+1)-1)/(i-1);
//			long long power = 1;
//			divisor_sum *= tempsum;
//		}
//	}
//
//	if (temp > 1) {
//		divisor_count *= 2;
//		divisor_sum *= (1 + temp);
//	}
//	return divisor_sum - temp;
//}
//int exe5(int n)
//{
//	int count=0;
//	for (int i = 1; i <= n; i++)
//	{
//		if (divisorsum(i) == 1)
//		{
//			continue;
//		}
//		else if(divisorsum(i)==i)
//		{
//			printf(" %3d", i);
//			count++;
//		}
//	}
//	if (count == 0)
//	{
//		printf("n内无完全数.");
//	}
//	return 0;
//}
//int sumofproperdivisions(int x)
//{
//
//	int k = (int)sqrt(x); 
//	int sum = 1;
//	for (int m = 2; m <= k; m++)
//	{
//		if (x % m == 0)
//		{
//			if (m != x / m)
//				sum += m + x / m;
//			else sum += m;
//		}
//	}return sum;
//}
//int exe6(int range)
//{
//	printf("2-range的亲和数对为:");
//	for ( int x = 2; x <= range; x++)
//	{
//		int y = sumofproperdivisions(x);
//		if (x < y && sumofproperdivisions(y) == x)
//		{
//			printf("	(%d,%d)", x, y);
//		}
//	}
//	return 0;
//}
//int exe7()
//{
//	int count=0;
//	printf("方案如下:\n");
//	for (int z = 0; z <= 75; z=z+3)
//	{
//		count++;
//		printf(" %d %d \n", z / 3, 100 - 4*(z / 3));
//	}
//	printf("总方案数:%d", count);
//	return 0;
//}
//int exe8()
//{
//	int large, middle, small; 
//	int solutions = 0;
//
//	printf("百马百担的方案如下：\n");
//
//	for (large = 0; large <= 33; large++) {  
//		for (middle = 0; middle <= 50; middle++) {  
//			small = 100 - large - middle; 
//
//			
//			if (6 * large + 4 * middle + small == 200) {
//				solutions++;
//				printf("方案%d: 大马%d匹，中马%d匹，小马%d匹\n",
//					solutions, large, middle, small);
//			}
//		}
//	}
//
//	printf("\n总共有 %d 种方案\n", solutions);
//
//	return 0;
//}
//int exe9()
//{
//	int sequence[100]; 
//	int i;
//	
//	sequence[0] = 0;
//	sequence[1] = 1;
//
//	
//	for (i = 2; i < 100; i++) {
//		if (i % 2 == 1) {  
//			sequence[i] = sequence[i - 1] + sequence[i - 2];
//		}
//		else {
//			sequence[i] = sequence[i - 2] - sequence[i - 1];
//		}
//	}
//
//	printf("序列前100项如下：\n");
//	for (i = 0; i < 100; i++) {
//		printf("%4d", sequence[i]);
//		if ((i + 1) % 10 == 0) {  
//			printf("\n");
//		}
//	}
//
//	return 0;
//}
//int exe10()
//{
//	
//		int i;
//		int is_true = 1;  
//
//		for (i = 1; i <= 100; i += 2) {  
//			if ((i * i) % 8 != 1) {  
//				is_true = 0;  
//				printf("反例：%d^2 = %d, 除以8余%d\n", i, i * i, (i * i) % 8);
//				break;
//			}
//		}
//		if (is_true) {
//			printf("YES\n");  
//		}
//		else {
//			printf("NO\n");   
//		}
//
//		return 0;
//}
//int exe14()
//{
//	int n;
//	scanf("%d", &n);
//	float arr[1000];
//
//	for (int i = 0; i < n; i++) {
//		scanf("%f", &arr[i]);
//	}
//
//	int max_index = 0;
//	for (int i = 1; i < n; i++) {
//		if (arr[i] > arr[max_index]) {
//			max_index = i;
//		}
//	}
//
//	printf("%d\n", max_index);
//	return 0;
//}
//int exe15()
//{
//	int n;
//	scanf("%d", &n);
//	int arr[1000];
//
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &arr[i]);
//	}
//
//	int max = arr[0];
//	int min = arr[0];
//
//	for (int i = 1; i < n; i++) {
//		if (arr[i] > max) max = arr[i];
//		if (arr[i] < min) min = arr[i];
//	}
//
//	printf("%d\n", max - min);
//	return 0;
//}
//int exe16()
//{
//	int n;
//	scanf("%d", &n);
//	int A[1000], B[1000], C[1000];
//
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &A[i]);
//	}
//
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &B[i]);
//	}
//
//	for (int i = 0; i < n; i++) {
//		C[i] = A[i] + B[i];
//		printf("%d ", C[i]);
//	}
//
//	return 0;
//}
//int is_prime(int num) {
//	if (num < 2) return 0;
//	for (int i = 2; i * i <= num; i++) {
//		if (num % i == 0) return 0;
//	}
//	return 1;
//}
//int exe17()
//{
//	int arr[20];
//	int count = 0;
//
//	for (int i = 0; i < 20; i++) {
//		scanf("%d", &arr[i]);
//	}
//
//	for (int i = 0; i < 20; i++) {
//		if (is_prime(arr[i])) {
//			count++;
//		}
//	}
//
//	printf("%d\n", count);
//	return 0;
//}
//int exe18()
//{
//	int arr[20];
//	int sum = 0;
//	float average;
//
//	for (int i = 0; i < 20; i++) {
//		scanf("%d", &arr[i]);
//		sum += arr[i];
//	}
//
//	average = sum / 20.0;
//	printf("%.2f\n", average);
//
//	for (int i = 0; i < 20; i++) {
//		printf("%.2f ", arr[i] - average);
//	}
//
//	return 0;
//}
//int main()
//{
//	
//}
