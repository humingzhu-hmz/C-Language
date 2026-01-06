//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <limits.h>
//
//#define LINEBUF 128
//#define MAX_N 999   /* 上限，防止内存/打印过大；可按需调整 */
//
//static char *readline(char *buf, size_t sz) {
//    if (!fgets(buf, (int)sz, stdin)) return NULL;
//    size_t L = strlen(buf);
//    if (L && buf[L-1] == '\n') buf[L-1] = '\0';
//    return buf;
//}
//
//static int parse_positive_odd(const char *s) {
//    if (!s || !*s) return -1;
//    /* 拒绝非数字开头（允许前后空格） */
//    const char *p = s;
//    while (isspace((unsigned char)*p)) ++p;
//    if (*p == '\0') return -1;
//    if (*p == 'q' || *p == 'Q') return -2; /* 信号：退出 */
//    char *end;
//    long v = strtol(p, &end, 10);
//    if (p == end) return -1;
//    while (isspace((unsigned char)*end)) ++end;
//    if (*end != '\0') return -1;
//    if (v <= 0 || v > MAX_N) return -1;
//    if (v % 2 == 0) return -1;
//    return (int)v;
//}
//
//static int **alloc_square(int n) {
//    int **a = (int**)malloc(n * sizeof(int*));
//    if (!a) return NULL;
//    for (int i = 0; i < n; ++i) {
//        a[i] = (int*)calloc(n, sizeof(int));
//        if (!a[i]) {
//            for (int j = 0; j < i; ++j) free(a[j]);
//            free(a);
//            return NULL;
//        }
//    }
//    return a;
//}
//
//static void free_square(int **a, int n) {
//    if (!a) return;
//    for (int i = 0; i < n; ++i) free(a[i]);
//    free(a);
//}
//
//static int **generate_magic(int n) {
//    int **sq = alloc_square(n);
//    if (!sq) return NULL;
//    int row = 0, col = n/2;
//    for (int num = 1; num <= n * n; ++num) {
//        sq[row][col] = num;
//        int next_row = (row - 1 + n) % n;
//        int next_col = (col + 1) % n;
//        if (sq[next_row][next_col] != 0) {
//            row = (row + 1) % n;
//        } else {
//            row = next_row;
//            col = next_col;
//        }
//    }
//    return sq;
//}
//
//static int digits_of_int(int x) {
//    if (x == 0) return 1;
//    int d = 0;
//    if (x < 0) { x = -x; d = 1; } /* sign */
//    while (x) { ++d; x /= 10; }
//    return d;
//}
//
//static void print_square(int **sq, int n, FILE *out) {
//    int maxval = n * n;
//    int w = digits_of_int(maxval) + 1; /* some padding */
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            fprintf(out, "%*d", w, sq[i][j]);
//        }
//        fprintf(out, "\n");
//    }
//}
//
//static long long magic_constant(int n) {
//    return (long long)n * ( (long long)n * n + 1 ) / 2;
//}
//
//static int verify_magic(int **sq, int n, long long target, FILE *out) {
//    int ok = 1;
//    /* rows */
//    for (int i = 0; i < n; ++i) {
//        long long s = 0;
//        for (int j = 0; j < n; ++j) s += sq[i][j];
//        if (s != target) {
//            fprintf(out, "Row %d sum = %lld != %lld\n", i, s, target);
//            ok = 0;
//        }
//    }
//    /* cols */
//    for (int j = 0; j < n; ++j) {
//        long long s = 0;
//        for (int i = 0; i < n; ++i) s += sq[i][j];
//        if (s != target) {
//            fprintf(out, "Col %d sum = %lld != %lld\n", j, s, target);
//            ok = 0;
//        }
//    }
//    /* main diag */
//    long long s1 = 0;
//    for (int i = 0; i < n; ++i) s1 += sq[i][i];
//    if (s1 != target) {
//        fprintf(out, "Main diagonal sum = %lld != %lld\n", s1, target);
//        ok = 0;
//    }
//    /* anti diag */
//    long long s2 = 0;
//    for (int i = 0; i < n; ++i) s2 += sq[i][n-1-i];
//    if (s2 != target) {
//        fprintf(out, "Anti diagonal sum = %lld != %lld\n", s2, target);
//        ok = 0;
//    }
//    return ok;
//}
//
//int main(void) {
//    char line[LINEBUF];
//    printf("Magic Square (odd order). Enter 'q' to quit.\n");
//    printf("Allowed range: odd n, 1..%d\n\n", MAX_N);
//
//    while (1) {
//        printf("Input n (odd positive integer) > ");
//        if (!readline(line, sizeof line)) break;
//        int n = parse_positive_odd(line);
//        if (n == -2) break;    /* q */
//        if (n <= 0) {
//            printf("Invalid input. Please enter an odd positive integer between 1 and %d.\n\n", MAX_N);
//            continue;
//        }
//
//        int **sq = generate_magic(n);
//        if (!sq) {
//            fprintf(stderr, "Memory allocation failed for n=%d\n", n);
//            continue;
//        }
//
//        long long M = magic_constant(n);
//        printf("\nGenerated %d x %d magic square (magic constant = %lld):\n\n", n, n, M);
//        print_square(sq, n, stdout);
//
//        printf("\nVerifying sums... ");
//        if (verify_magic(sq, n, M, stdout)) {
//            printf("OK. All sums equal %lld.\n", M);
//        } else {
//            printf("Verification failed (see above).\n");
//        }
//
//        /* ask to save */
//        printf("\nSave output to file? (y/N) > ");
//        if (!readline(line, sizeof line)) { free_square(sq, n); break; }
//        if (line[0] == 'y' || line[0] == 'Y') {
//            printf("Filename > ");
//            if (!readline(line, sizeof line)) { free_square(sq, n); break; }
//            FILE *fp = fopen(line, "w");
//            if (!fp) {
//                perror("fopen");
//            } else {
//                fprintf(fp, "Magic square n=%d (magic constant=%lld)\n\n", n, M);
//                print_square(sq, n, fp);
//                fprintf(fp, "\nVerification:\n");
//                verify_magic(sq, n, M, fp);
//                fclose(fp);
//                printf("Saved to '%s'\n", line);
//            }
//        }
//
//        free_square(sq, n);
//        printf("\nDone. You may input another n or 'q' to quit.\n\n");
//    }
//
//    printf("Bye.\n");
//    return 0;
//}
