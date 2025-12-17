//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//
//void exe1()
//{
//    int a[6][6] = { 0 };
//    for (int i = 0; i < 6; i++)
//    {
//        a[i][0] = 1;
//        a[i][i] = 1;
//        for (int j = 1; j < i; j++)
//        {
//            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
//        }
//    }
//    for (int i = 0; i < 6; i++)
//    {
//        for (int j = 0; j <= i; j++)
//        {
//            printf("%d\t", a[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}
//
//void exe2()
//{
//    int a[3][3] = { {100, 200, 300}, {400, 500, 600}, {700, 800, 900} };
//    printf("转置前:\n");
//    for (int i = 0; i < 3; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            printf("%d\t", a[i][j]);
//        }
//        printf("\n");
//    }
//    for (int i = 0; i < 3; i++)
//    {
//        for (int j = i + 1; j < 3; j++)
//        {
//            int temp = a[i][j];
//            a[i][j] = a[j][i];
//            a[j][i] = temp;
//        }
//    }
//    printf("转置后:\n");
//    for (int i = 0; i < 3; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            printf("%d\t", a[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}
//
//void exe3()
//{
//    int A[2][3] = { {1, 2, 3}, {4, 5, 6} };
//    int B[2][3] = { {6, 5, 4}, {3, 2, 1} };
//    int C[2][3];
//    printf("矩阵A:\n");
//    for (int i = 0; i < 2; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            printf("%d\t", A[i][j]);
//        }
//        printf("\n");
//    }
//    printf("矩阵B:\n");
//    for (int i = 0; i < 2; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            printf("%d\t", B[i][j]);
//        }
//        printf("\n");
//    }
//    for (int i = 0; i < 2; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            C[i][j] = A[i][j] + B[i][j];
//        }
//    }
//    printf("矩阵C=A+B:\n");
//    for (int i = 0; i < 2; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            printf("%d\t", C[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}
//
//void exe4()
//{
//    int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
//    int sum = 0;
//    printf("矩阵:\n");
//    for (int i = 0; i < 3; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            printf("%d\t", a[i][j]);
//        }
//        printf("\n");
//    }
//    for (int i = 0; i < 3; i++)
//    {
//        sum += a[i][i];
//    }
//    printf("主对角线元素之和: %d\n\n", sum);
//}
//
//void exe5()
//{
//    int a[15] = { 3, 7, 1, 9, 4, 8, 2, 6, 5, 0, 12, 11, 14, 13, 10 };
//    printf("排序前:\n");
//    for (int i = 0; i < 15; i++)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
//    for (int i = 0; i < 14; i++)
//    {
//        for (int j = 0; j < 14 - i; j++)
//        {
//            if (a[j] < a[j + 1])
//            {
//                int temp = a[j];
//                a[j] = a[j + 1];
//                a[j + 1] = temp;
//            }
//        }
//    }
//    printf("排序后(从大到小):\n");
//    for (int i = 0; i < 15; i++)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n\n");
//}
//
//void exe6()
//{
//    int num[20];
//    int pos[20];
//    printf("请输入20个整数:\n");
//    for (int i = 0; i < 20; i++)
//    {
//        scanf("%d", &num[i]);
//        pos[i] = i + 1;
//    }
//    for (int i = 0; i < 19; i++)
//    {
//        for (int j = 0; j < 19 - i; j++)
//        {
//            if (num[j] > num[j + 1])
//            {
//                int temp_num = num[j];
//                num[j] = num[j + 1];
//                num[j + 1] = temp_num;
//                int temp_pos = pos[j];
//                pos[j] = pos[j + 1];
//                pos[j + 1] = temp_pos;
//            }
//        }
//    }
//    printf("排序结果:\n");
//    for (int i = 0; i < 20; i++)
//    {
//        printf("%d\t%d\n", num[i], pos[i]);
//    }
//    printf("\n");
//}
//
//void exe7()
//{
//    int n = 5;
//    int a[1000] = { 8, 6, 5, 4, 1 };
//    printf("原数组:\n");
//    for (int i = 0; i < n; i++)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
//    for (int i = 0; i < n / 2; i++)
//    {
//        int temp = a[i];
//        a[i] = a[n - 1 - i];
//        a[n - 1 - i] = temp;
//    }
//    printf("逆序后:\n");
//    for (int i = 0; i < n; i++)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n\n");
//}
//
//void exe8()
//{
//    int a[1001] = { 1, 2, 4, 4, 5, 10, 12 };
//    int n = 7;
//    int x;
//    printf("原数组:\n");
//    for (int i = 0; i < n; i++)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n请输入要插入的整数: ");
//    scanf("%d", &x);
//    int i = n - 1;
//    while (i >= 0 && a[i] > x)
//    {
//        a[i + 1] = a[i];
//        i--;
//    }
//    a[i + 1] = x;
//    n++;
//    printf("插入后数组:\n");
//    for (int i = 0; i < n; i++)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n\n");
//}
//
//void exe9()
//{
//    float scores[5][3];
//    float sum[5] = { 0 };
//    float avg[5];
//    int count = 0;
//    printf("请输入5个学生的3门成绩:\n");
//    for (int i = 0; i < 5; i++)
//    {
//        for (int j = 0; j < 3; j++)
//        {
//            scanf("%f", &scores[i][j]);
//            sum[i] += scores[i][j];
//        }
//        avg[i] = sum[i] / 3;
//        if (avg[i] < 60) count++;
//    }
//    printf("学生成绩汇总:\n");
//    for (int i = 0; i < 5; i++)
//    {
//        printf("学生%d: 总分=%.2f, 平均分=%.2f\n", i + 1, sum[i], avg[i]);
//    }
//    printf("平均分低于60分的学生人数: %d\n\n", count);
//}
//
//void exe10()
//{
//
//}
//
//void exe11()
//{
//
//}
//
//int main()
//{
//    int choice;
//    do
//    {
//        printf("=== 程序设计基础课后上机练习（六） ===\n");
//        printf("1. 杨辉三角\n");
//        printf("2. 矩阵转置\n");
//        printf("3. 矩阵相加\n");
//        printf("4. 矩阵对角线求和\n");
//        printf("5. 冒泡排序(15个数)\n");
//        printf("6. 排序并记录原始位置(20个数)\n");
//        printf("7. 数组逆序\n");
//        printf("8. 有序数组插入\n");
//        printf("9. 学生成绩统计\n");
//        printf("10. 最高分最低分差值(流程图题)\n");
//        printf("11. 最高分下标(流程图题)\n");
//        printf("0. 退出\n");
//        printf("请选择题目(0-11): ");
//        scanf("%d", &choice);
//
//        switch (choice)
//        {
//        case 1: exe1(); break;
//        case 2: exe2(); break;
//        case 3: exe3(); break;
//        case 4: exe4(); break;
//        case 5: exe5(); break;
//        case 6: exe6(); break;
//        case 7: exe7(); break;
//        case 8: exe8(); break;
//        case 9: exe9(); break;
//        case 10: printf("=== 题目10：最高分最低分差值 ===\n(流程图题，无代码)\n\n"); break;
//        case 11: printf("=== 题目11：最高分下标 ===\n(流程图题，无代码)\n\n"); break;
//        case 0: printf("程序结束\n"); break;
//        default: printf("无效选择\n");
//        }
//    } while (choice != 0);
//
//    return 0;
//}