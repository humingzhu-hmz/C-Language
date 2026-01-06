//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <stdbool.h>
//
//#define EPS 1e-6
//#define MAXN 8
//#define MAXSTATE 100000
//
//int recursecount = 0;
///* ----------------- structure data ----------------- */
//
//typedef struct {
//    double value;
//    char expr[128];
//} Node;
//
///* the table be used to memorey*/
//char visited[MAXSTATE][256];
//int visited_cnt = 0;
//
///* ----------------- tool function ----------------- */
//
//int cmp_double(const void* a, const void* b) {
//    double x = *(double*)a;
//    double y = *(double*)b;
//    if (fabs(x - y) < EPS) return 0;
//    return x < y ? -1 : 1;
//}
//
///* according to the siae of num to sort */
//void build_state_key(Node nums[], int n, char key[]) {
//    double tmp[MAXN];
//    for (int i = 0; i < n; i++) tmp[i] = nums[i].value;
//
//    qsort(tmp, n, sizeof(double), cmp_double);
//
//    key[0] = '\0';
//    for (int i = 0; i < n; i++) {
//        char buf[32];
//        sprintf(buf, "%.4f,", tmp[i]);
//        strcat(key, buf);
//    }
//}
//
///* check whether visited */
//bool is_visited(const char* key) {
//    for (int i = 0; i < visited_cnt; i++) {
//        if (strcmp(visited[i], key) == 0)
//            return true;
//    }
//    return false;
//}
//
//void mark_visited(const char* key) {
//    if (visited_cnt < MAXSTATE) {
//        strcpy(visited[visited_cnt++], key);
//    }
//}
//
//bool is_samevalue(Node node[], int index, double n)
//{
//    for (int i = 0; i < index; i++)
//    {
//        if (n == node[i].value)
//        {
//            return true;
//        }
//    }
//    return false;
//}
///* ----------------- DFS  ----------------- */
//bool dfs(Node nums[], int n, double target, char result[]) {
//    recursecount++;
//    /* ===== memoized pruning===== */
//    char state_key[256];
//    build_state_key(nums, n, state_key);
//    if (is_visited(state_key))
//        return false;
//    mark_visited(state_key);
//
//    /* ===== the suspend condition of recurse ===== */
//    if (n == 1) {
//        if (fabs(nums[0].value - target) < EPS) {
//            strcpy(result, nums[0].expr);
//            return true;
//        }
//        return false;
//    }
//
//    /* ===== chosen a and b ===== */
//    for (int i = 0; i < n; i++) {
//        for (int j = i + 1; j < n; j++) {
//
//            Node a = nums[i];
//            Node b = nums[j];
//
//            Node restring[MAXN];
//            int r = 0;
//            for (int k = 0; k < n; k++) {
//                if (k != i && k != j)
//                    restring[r++] = nums[k];
//            }
//
//            Node candidate[6];
//            double x = a.value;
//            double y = b.value;
//            int index = 0;
//
//            candidate[index].value = x + y;
//            snprintf(candidate[index].expr, sizeof(candidate[index].expr), "(%s+%s)", a.expr, b.expr);
//            index++;
//
//            if (!is_samevalue(candidate, index, x * y))
//            {
//                candidate[index].value = x * y;
//                snprintf(candidate[index].expr, sizeof(candidate[index].expr), "(%s*%s)", a.expr, b.expr);
//                index++;
//            }
//            if (!is_samevalue(candidate, index, x - y))
//            {
//                candidate[index].value = x - y;
//                snprintf(candidate[index].expr, sizeof(candidate[index].expr), "(%s-%s)", a.expr, b.expr);
//                index++;
//            }
//            if (!is_samevalue(candidate, index, y - x))
//            {
//                candidate[index].value = y - x;
//                snprintf(candidate[index].expr, sizeof(candidate[index].expr), "(%s-%s)", b.expr, a.expr);
//                index++;
//            }
//
//            if (fabs(x) > EPS && !is_samevalue(candidate, index, y / x))
//            {
//                candidate[index].value = y / x;
//                snprintf(candidate[index].expr, sizeof(candidate[index].expr), "(%s / %s)", b.expr, a.expr);
//                index++;
//            }
//            if (fabs(y) > EPS && !is_samevalue(candidate, index, x / y))
//            {
//                candidate[index].value = x / y;
//                snprintf(candidate[index].expr, sizeof(candidate[index].expr), "(%s / %s)", a.expr, b.expr);
//                index++;
//            }
//            for (int i = 0; i < index; i++)
//            {
//                restring[r] = candidate[i];
//                if (dfs(restring, r+1, target, result))
//                {
//                    return true;
//                }
//            }
//        }
//    }
//     return false;
//}
//
//int main() 
//{
//
//    int n;
//    double target = 24.0;
//    while (true)
//    {
//        do
//        {
//            printf("Enter number count (<= %d): ", MAXN);
//            if (scanf("%d", &n) != 1) {
//                printf("Invalid input\n");
//                while (getchar() != '\n');
//            }
//            if (n < 2 || n > MAXN) {
//                printf("Invalid n\n");
//            }
//            else {
//                break;
//            }
//        } while (true);
//
//        Node nums[MAXN];
//        printf("Enter %d numbers:\n", n);
//        for (int i = 0; i < n; i++) {
//            scanf("%lf", &nums[i].value);
//            snprintf(nums[i].expr, sizeof(nums[i].expr),
//                "%.0f", nums[i].value);
//        }
//
//        visited_cnt = 0;
//
//        char result[512];
//        if (dfs(nums, n, target, result)) {
//            printf("\nSolution found:\n%s = %.0f\n", result, target);
//        }
//        else {
//            printf("\nNo solution.\n");
//        }
//        printf("recurse times:%d\nvisited array quantity=%d\n", recursecount,visited_cnt);
//        printf("do you want to try again(y/N)?");
//        char readline[5];
//        while (getchar() != '\n');
//        if (!fgets(readline, sizeof(readline),stdin))
//        {
//            break;
//        }
//        if (readline[0] == 'y' || readline[0]=='Y')
//        {
//            system("cls");
//        }
//        else
//        {
//            break;
//        }
//    }
//    return 0;
//}