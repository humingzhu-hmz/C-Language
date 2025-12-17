//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>
//#include <string.h>
//
//int** w;
//int** maxpathsum;
//
//// 生成随机金字塔
//int** rand_distribute(int n) {
//    w = (int**)calloc(n, sizeof(int*));
//    maxpathsum = (int**)calloc(n, sizeof(int*));
//    if (!w || !maxpathsum) {
//        printf("Memory allocation failed\n");
//        exit(1);
//    }
//
//    for (int i = 0; i < n; i++) {
//        w[i] = (int*)calloc(i + 1, sizeof(int));
//        maxpathsum[i] = (int*)calloc(i + 1, sizeof(int));
//
//        // 修正：简化内存分配失败处理
//        if (!w[i] || !maxpathsum[i]) {
//            printf("Memory allocation failed for row %d\n", i);
//            // 统一释放所有已分配内存
//            for (int k = 0; k < i; k++) {
//                if (w[k]) 
//                    free(w[k]);
//                if (maxpathsum[k])
//                    free(maxpathsum[k]);
//            }
//            free(w);
//            free(maxpathsum);
//            exit(1);
//        }
//
//        for (int j = 0; j <= i; j++) {
//            w[i][j] = rand() % 20 + 1;
//        }
//    }
//    return w;
//}
//
//int max(int a, int b) {
//    return a > b ? a : b;
//}
//
//// 动态规划求解 - 修正边界检查
//int f(int i, int j, int n) {
//    if (i < 0 || i >= n || j < 0 || j > i) {
//        return -1;
//    }
//
//    if (maxpathsum[i][j] != 0) {
//        return maxpathsum[i][j];
//    }
//
//    if (i == 0 && j == 0) {
//        maxpathsum[i][j] = w[i][j];
//    }
//    else if (j == 0) {
//        int parent = f(i - 1, j, n);
//        if (parent == -1) return -1;
//        maxpathsum[i][j] = parent + w[i][j];
//    }
//    else if (j == i) {
//        int parent = f(i - 1, j - 1, n);
//        if (parent == -1) return -1;
//        maxpathsum[i][j] = parent + w[i][j];
//    }
//    else {
//        int left_parent = f(i - 1, j - 1, n);
//        int right_parent = f(i - 1, j, n);
//        if (left_parent == -1 || right_parent == -1) return -1;
//        maxpathsum[i][j] = max(left_parent, right_parent) + w[i][j];
//    }
//    return maxpathsum[i][j];
//}
//
//void clear_input_buffer() {
//    while (getchar() != '\n');
//}
//
//int main() {
//    int n, i, j;
//    srand((unsigned)time(NULL));
//
//    printf("请输入层数n: ");
//    while (scanf_s("%d", &n) != 1 || n <= 0) {
//        printf("输入错误！请输入正整数n: ");
//        clear_input_buffer();
//    }
//
//    rand_distribute(n);
//
//    // 打印金字塔
//    printf("\n随机生成的数值金字塔为:\n");
//    for (i = 0; i < n; i++) {
//        printf("%*s", (n - i - 1) * 2, "");
//        for (j = 0; j <= i; j++) {
//            printf("%4d", w[i][j]);
//        }
//        printf("\n");
//    }
//
//    // 输入终点位置查询
//    while (1) {
//        printf("\n请输入终点位置i,j(从0开始，输入非数字结束测试): ");
//        if (scanf_s("%d", &i) != 1) {
//            clear_input_buffer();
//            break;
//        }
//        if (scanf_s("%d", &j) != 1) {
//            clear_input_buffer();
//            printf("输入错误！请重新输入\n");
//            continue;
//        }
//
//        if (i < 0 || i >= n || j < 0 || j > i) {
//            printf("位置(%d,%d)超出范围！有效范围: i[0-%d], j[0-%d]\n", i, j, n - 1, i);
//            continue;
//        }
//
//        int val = w[i][j];
//        int max_sum = f(i, j, n);
//        printf("终点(%d,%d)的值为: %d\n", i, j, val);
//        printf("从起点到终点(%d,%d)的最大路径和为: %d\n", i, j, max_sum);
//    }
//
//    // 打印所有点的最大路径和
//    printf("\n各点的起点至该点路径之和最大值为:\n");
//    for (i = 0; i < n; i++) {
//        printf("%*s", (n - i - 1) * 2, "");
//        for (j = 0; j <= i; j++) {
//            int sum = f(i, j, n);
//            printf("%4d", sum);
//        }
//        printf("\n");
//    }
//
//    // 释放内存
//    for (i = 0; i < n; i++) {
//        free(w[i]);
//        free(maxpathsum[i]);
//    }
//    free(w);
//    free(maxpathsum);
//
//    return 0;
//}