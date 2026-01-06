//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <ctype.h>
//#include <stdlib.h>
//#include <time.h>
//#define MAXFIGURES 10
//char** generate_nums(int n)
//{
//	srand((unsigned int)time(NULL));
//	
//	char** nums = (char**)malloc(n * sizeof(char*));
//
//	for (int i = 0; i < n; i++)
//	{
//		int numslenth = rand() % MAXFIGURES+ 1;
//		
//		nums[i] = (char*)malloc((numslenth + 1) * sizeof(char));
//		
//		nums[i][0] = rand() % 9 + 1+'0';
//		for (int k = 1; k < numslenth; k++)
//		{
//			nums[i][k] = rand() % 10+'0';
//		}
//		nums[i][numslenth] = '\0';
//	}
//	return nums;
//}
//char* calculate(char* num1, char* num2)
//{
//	int num1lenth = strlen(num1), num2lenth = strlen(num2);
//	int jointlenth = num1lenth > num2lenth ? num1lenth + 1 : num2lenth + 1;
//	
//	char* joint = (char*)malloc((jointlenth+1)*sizeof(char));
//	joint[jointlenth] = '\0';
//
//	memset(joint, '0',jointlenth);//memset 按字节赋值，当给一个整数数组赋值时只能赋值为0或-1，因为int类型0的二进制为都是0，所以给
//									//int每个字节赋值为0没问题，int类型-1是1111111111........,四个字节的-1连接起来就是int类型-1.其他的数
//									//因为单字节每一位不一样所以不行，例如1 00000001（单字节） int类型00000000000000000000.......1
//	int shortnumlenth = (jointlenth - num1lenth == 1) ? num2lenth : num1lenth;
//	int index = 0;
//	for (; index < shortnumlenth; index++)
//	{
//		joint[jointlenth - 1 - (index + 1)] = (num1[num1lenth - 1 - index] +
//			num2[num2lenth - 1 - index] + joint[jointlenth - 1 - index]-3*'0') / 10 + '0';
//		joint[jointlenth - 1 - index] = (num1[num1lenth - 1 - index] +
//			num2[num2lenth - 1 - index] + joint[jointlenth - 1 - index] - 3 * '0') % 10 + '0';
//	}
//	if (num2lenth < num1lenth)
//	{
//		for (; index < jointlenth - 1; index++)
//		{
//			joint[jointlenth - 1 - (index + 1)] = (num1[num1lenth - 1 - index] +
//				joint[jointlenth - 1 - index]- 2 * '0') / 10+'0';
//			joint[jointlenth - 1 - index] = (num1[num1lenth - 1 - index] +
//				joint[jointlenth - 1 - index]- 2 * '0') % 10+'0';
//		}
//	}
//	else
//	{
//		for (; index < jointlenth - 1; index++)
//		{
//			joint[jointlenth - 1 - (index + 1)] = (num2[num2lenth - 1 - index] +
//				joint[jointlenth - 1 - index]- 2 * '0') / 10+'0';
//			joint[jointlenth - 1 - index] = (num2[num2lenth - 1 - index] +
//				joint[jointlenth - 1 - index]- 2 * '0') % 10+'0';
//		}
//	}
//	return joint;
//}
//
//int main()
//{
//	printf("this program will implement that Add multiple long integers,please import thr counts of long integers:");
//	int n;
//	scanf("%d", &n);
//	if (n < 0)
//	{
//		printf("error, n must >0!");
//		return 0;
//	}
//	char** nums = generate_nums(n);
//	printf("they are respectively:\n");
//	for (int i = 0; i < n; i++)
//	{
//		printf("%*s\n",MAXFIGURES, nums[i]);
//	}
//	if (n == 1)
//	{
//		printf("add consequence is:%s\n", nums[0]);
//		free(nums[0]);
//		free(nums);
//		return 0;
//	}
//	char* sum = calculate(nums[0], nums[1]);
//	for (int k = 2; k < n; k++)
//	{
//		char *temp=calculate(sum, nums[k]);
//		free(sum);
//		sum = temp;
//	}
//	char* result = sum;
//	while (*result == '0' && *(result + 1) != '\0') 
//	{
//		result++;
//	}
//
//	printf("add conserquence is :%s\n", result);
//	for (int j = 0; j < n; j++)
//	{
//		free(nums[j]);
//	}
//	free(nums);
//
//	free(sum);
//	return 0;
//}