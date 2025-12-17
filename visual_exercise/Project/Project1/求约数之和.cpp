//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <math.h>
//
//int main() {
//    printf("请输入 n: ");
//    int n;
//    scanf("%d", &n);
//
//    int temp = n;
//    long long divisor_count = 1;  // 因子个数
//    long long divisor_sum = 1;    // 因子和
//
//    // 统计因子2的幂
//    int count = 0;
//    while (temp % 2 == 0) {
//        count++;
//        temp /= 2;
//    }
//    if (count > 0) {
//        divisor_count *= (count + 1);
//        divisor_sum *= ((long long)pow(2, count + 1) - 1);
//    }
//
//    // 统计奇素因子的幂
//    for (int i = 3; i * i <= temp; i += 2) {
//        count = 0;
//        while (temp % i == 0) {
//            count++;
//            temp /= i;
//        }
//        if (count > 0) 
//        {
//            divisor_count *= (count + 1);
//            // 计算 1 + p + p^2 + ... + p^count
//            long long geometric_sum = 0;
//            long long power = 1;
//            for (int j = 0; j <= count; j++) {
//                geometric_sum += power;
//                power *= i;
//            }
//            divisor_sum *= geometric_sum;
//        }
//    }
//
//    // 如果剩余的 temp > 1，说明 temp 是一个素因子
//    if (temp > 1) {
//        divisor_count *= 2;
//        divisor_sum *= (1 + temp);
//    }
//
//    printf("\n%lld\n%lld\n", divisor_count, divisor_sum);
//    return 0;
//}