//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include <time.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <stdio.h>
//
//void init_random() {
//    static int initialized = 0;
//    if (!initialized) {
//        srand((unsigned int)time(NULL));
//        initialized = 1;
//    }
//}
//
//char* randstring(int maxlength) {
//    int k = 0, i = 0;
//    char* str = (char*)calloc((maxlength + 1), sizeof(char));
//    char* temp = (char*)calloc((maxlength + 1), sizeof(char));
//    if (!str || !temp) {
//        fprintf(stderr, "�ڴ����ʧ��\n");
//        exit(1);
//    }
//    for (i = 0; i < maxlength; i++) {
//        temp[i] = rand() % 128;
//        if (isalpha((unsigned char)temp[i]) || isdigit((unsigned char)temp[i])) {
//            str[k++] = temp[i];
//        }
//        if (temp[i] == '\0') {
//            break;
//        }
//    }
//    if (k == 0) {
//        str[0] = 'a';
//        str[1] = '\0';
//    }
//    str[maxlength] = '\0';
//    free(temp);
//    return str;
//}
//
//char** stringarr(int n, int maxlength) {
//    init_random();
//    char** str = (char**)calloc(n, sizeof(char*));
//    if (!str) {
//        fprintf(stderr, "�ַ��������ڴ����ʧ��\n");
//        exit(1);
//    }
//    for (int i = 0; i < n; i++) {
//        str[i] = randstring(maxlength);
//        if (!str[i]) {
//            fprintf(stderr, "�ַ����ڴ����ʧ��\n");
//            for (int j = 0; j < i; j++) {
//                free(str[j]);
//            }
//            free(str);
//            exit(1);
//        }
//    }
//    return str;
//}
//
//int randpivot(int left, int right) {
//    if (right <= left)
//        return left;
//    int pivot = rand() % (right - left + 1) + left;
//    return pivot;
//}
//
//void swap(char** str1, char** str2) {
//    char* temp = *str1;
//    *str1 = *str2;
//    *str2 = temp;
//}
//
//int partition(char** stringarr, int pivot, int left, int right) {
//    swap(stringarr + pivot, stringarr + right);
//    char* pivotValue = stringarr[right];
//    int storeIndex = left;
//
//    for (int i = left; i < right; i++) {
//        if (strcmp(stringarr[i], pivotValue) <= 0) {
//            swap(stringarr + i, stringarr + storeIndex);
//            storeIndex++;
//        }
//    }
//    swap(stringarr + storeIndex, stringarr + right);
//    return storeIndex;
//}
//
//void qsort1(char** stringarr, int left, int right) {
//    if (left >= right) return;
//
//    int pivot = randpivot(left, right);
//    pivot = partition(stringarr, pivot, left, right);
//
//    qsort1(stringarr, left, pivot - 1);
//    qsort1(stringarr, pivot + 1, right);
//}
//
//void Qsort(char** string, int n) {
//    init_random();
//    qsort1(string, 0, n - 1);
//}
//
//int main() {
//    int n, maxlength, i;
//    printf("�������ַ��������������󳤶�:");
//    while (scanf("%d %d", &n, &maxlength) != 2 || n <= 0 || maxlength <= 0) {
//        printf("������Ч����������������");
//        while (getchar() != '\n');
//    }
//
//    char** strarr = stringarr(n, maxlength);
//    char** originalstr = (char**)calloc(n, sizeof(char*));
//    if (!originalstr) {
//        fprintf(stderr, "ԭ���鱸���ڴ����ʧ��\n");
//        exit(1);
//    }
//    for (i = 0; i < n; i++) {
//        originalstr[i] = (char*)calloc((maxlength + 1), sizeof(char));
//        strncpy(originalstr[i], strarr[i], maxlength);
//        originalstr[i][maxlength] = '\0';
//    }
//
//    printf("ԭ�ַ�����Ϊ:\n");
//    for (int i = 0; i < n; i++) {
//        printf("    %d :%-*s\n", i, maxlength, strarr[i]);
//    }
//
//    Qsort(strarr, n);
//
//    printf("������ַ�����Ϊ:\n");
//    for (int i = 0; i < n; i++) {
//        printf("    %d :%-*s\n", i, maxlength, strarr[i]);
//    }
//    printf("����������ַ��������±��Բ鿴��Ӧ�ַ���ԭ�±�\n");
//    while (1) {
//        printf("�������±꣨0~%d�����������ֱ�ӽ�����", n - 1);
//        int index;
//        if (scanf("%d", &index) != 1) {
//            int c;
//            while ((c = getchar()) != '\n' && c != EOF);
//            printf("��������������˳�\n");
//            break;
//        }
//        int c;
//        while ((c = getchar()) != '\n' && c != EOF);
//        if (index < 0 || index >= n) {
//            printf("�±���Ч��������0~%d֮�������\n", n - 1);
//            continue;
//        }
//        printf("������±�%d���ַ�����%s����ԭ�±�Ϊ��", index, strarr[index]);
//        for (int i = 0; i < n; i++) {
//            if (strcmp(strarr[index], originalstr[i]) == 0) {
//                printf("%d ", i);
//            }
//        }
//        printf("\n");
//    }
//
//    for (int i = 0; i < n; i++) {
//        free(strarr[i]);
//        free(originalstr[i]);
//    }
//    free(strarr);
//    free(originalstr);
//    return 0;
//}