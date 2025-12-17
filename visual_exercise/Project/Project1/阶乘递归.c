//#include <stdio.h>
//#include <limits.h>
//long long int factorial(int n)
//{
//	if (n < 0) {
//		printf("错误：n不能为负数，阶乘仅定义在非负整数上\n");
//		exit(1);
//	}
//	if (n == 0||n==1)
//		return 1;
//	if (factorial(n-1) > LLONG_MAX / n)
//	{
//		printf("n!数据过大溢出");
//		exit(1);
//	}
//	else
//		return factorial(n-1)*n;
//}
// int main()
// {
//	 int n;
//	 fprintf(stdout, "请输入n计算n!:");
//	 scanf_s("%d", &n);
//	 long long int result = factorial(n);/*n!溢出result会接收随机值，int result = factorial(n);
//	 如果n!溢出不能让printf("n! is :%d",result)执行，exit能终止整段程序,同时避免循环输出该语句 n!数据过大溢出*/
//	 printf("n! is :%lld",result);
// }
