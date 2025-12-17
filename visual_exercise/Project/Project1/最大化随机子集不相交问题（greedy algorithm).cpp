//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <stdbool.h>
//
//#ifdef _WIN32
//#include <windows.h>
//#endif
//
//#define U_SIZE 100
//#define SUBSET_COUNT 20
//#define MAX_SUBSET_SIZE 15
//
//typedef struct {
//    int elements[MAX_SUBSET_SIZE];
//    int size;
//} Subset;
//
//typedef struct {
//    int elements[U_SIZE];
//    int size;
//} Set;
//
//void init_set(Set* set) {
//    set->size = 0;
//}
//
//bool is_set_empty(const Set* set) {
//    return set->size == 0;
//}
//bool add_to_set(Set* set, int element) {
//    for (int i = 0; i < set->size; i++) {
//        if (set->elements[i] == element) {
//            return false;  
//        }
//    }
//    if (set->size < U_SIZE) {
//        set->elements[set->size] = element;
//        set->size++;
//        return true;
//    }
//    return false;
//}
//
//bool set_contains(const Set* set, int element) {
//    for (int i = 0; i < set->size; i++) {
//        if (set->elements[i] == element) {
//            return true;
//        }
//    }
//    return false;
//}
//
//bool is_subset_empty(const Subset* subset) {
//    return subset->size == 0;
//}
//
//bool are_disjoint(const Subset* a, const Subset* b) {
//    if (is_subset_empty(a) || is_subset_empty(b)) {
//        return true;
//    }
//
//    const Subset* outer = (a->size <= b->size) ? a : b;
//    const Subset* inner = (a->size <= b->size) ? b : a;
//
//    for (int i = 0; i < outer->size; i++) {
//        for (int j = 0; j < inner->size; j++) {
//            if (outer->elements[i] == inner->elements[j]) {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//bool is_disjoint_with_selected(const Subset* subset, const Set* used_elements) {
//    if (is_subset_empty(subset)) {
//        return true;
//    }
//
//    if (is_set_empty(used_elements)) {
//        return true;
//    }
//
//    for (int i = 0; i < subset->size; i++) {
//        if (set_contains(used_elements, subset->elements[i])) {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool generate_random_subset(Subset* subset, int* available_elements, int available_count) {
//    if (available_count <= 0) {
//        subset->size = 0;
//        return false;
//    }
//
//    subset->size = rand() % MAX_SUBSET_SIZE + 1;
//    if (subset->size > available_count) {
//        subset->size = available_count;
//    }
//
//    for (int i = 0; i < subset->size; i++) {
//        int random_index = rand() % available_count;
//        subset->elements[i] = available_elements[random_index];
//
//        for (int j = 0; j < i; j++) {
//            if (subset->elements[j] == subset->elements[i]) {
//                i--;
//                break;
//            }
//        }
//    }
//
//    return true;
//}
//
//int compare_subsets(const void* a, const void* b) {
//    const Subset* sa = (const Subset*)a;
//    const Subset* sb = (const Subset*)b;
//    return sa->size - sb->size;
//}
//
//void greedy_max_disjoint_subsets(Subset subsets[], int subset_count,
//    Subset chosen_subsets[], int* chosen_count,
//    Set* n) {
//    qsort(subsets, subset_count, sizeof(Subset), compare_subsets);
//
//    Set used_elements;
//    init_set(&used_elements);
//    *chosen_count = 0;
//    init_set(n);
//
//    for (int i = 0; i < subset_count; i++) {
//        if (is_subset_empty(&subsets[i])) {
//            continue;
//        }
//
//        if (is_disjoint_with_selected(&subsets[i], &used_elements)) {
//            chosen_subsets[*chosen_count] = subsets[i];
//            (*chosen_count)++;
//
//            for (int j = 0; j < subsets[i].size; j++) {
//                add_to_set(&used_elements, subsets[i].elements[j]);
//                add_to_set(n, subsets[i].elements[j]);
//            }
//        }
//    }
//}
//
//void print_subset(const Subset* subset) {
//    if (is_subset_empty(subset)) {
//        printf("{}");
//        return;
//    }
//
//    printf("{");
//    for (int i = 0; i < subset->size; i++) {
//        printf("%d", subset->elements[i]);
//        if (i < subset->size - 1) {
//            printf(", ");
//        }
//    }
//    printf("}");
//}
//
//void print_set(const Set* set) {
//    if (is_set_empty(set)) {
//        printf("{}");
//        return;
//    }
//
//    printf("{");
//    for (int i = 0; i < set->size; i++) {
//        printf("%d", set->elements[i]);
//        if (i < set->size - 1) {
//            printf(", ");
//        }
//    }
//    printf("}");
//}
////虽然在初始生成子集中保证了有效性以及不重复性，validate起防御性检测，代码复用性（检测来自其他的子集），开发检测.
//bool validate_subset(const Subset* subset, int max_element) {
//    if (is_subset_empty(subset)) {
//        return false;
//    }
//
//    for (int i = 0; i < subset->size; i++) {
//        if (subset->elements[i] < 1 || subset->elements[i] > max_element) {
//            return false;
//        }
//
//        for (int j = i + 1; j < subset->size; j++) {
//            if (subset->elements[i] == subset->elements[j]) {
//                return false;
//            }
//        }
//    }
//
//    return true;
//}
//
//int main() {
//#ifdef _WIN32
//    SetConsoleOutputCP(CP_UTF8);
//    SetConsoleCP(CP_UTF8);
//#endif
//
//    srand((unsigned int)time(0));
//
//    printf("Start generating random subsets and using greedy algorithm to find disjoint subsets...\n");
//    printf("U value range: 1 to 100 (total %d elements)\n", U_SIZE);
//    printf("Will generate %d random subsets...\n\n", SUBSET_COUNT);
//
//    int u[U_SIZE];
//    for (int i = 0; i < U_SIZE; i++) {
//        u[i] = i + 1;
//    }
//
//    Subset subsets[SUBSET_COUNT];
//    int valid_subsets = 0;
//
//    for (int i = 0; i < SUBSET_COUNT; i++) {
//        if (generate_random_subset(&subsets[i], u, U_SIZE) &&
//            validate_subset(&subsets[i], U_SIZE)) {
//            valid_subsets++;
//        }
//        else {
//            subsets[i].size = 1;
//            subsets[i].elements[0] = u[(i % U_SIZE) + 1];
//            valid_subsets++;
//        }
//    }
//
//    printf("Generated subsets:\n");
//    int total_elements = 0;
//    int empty_subsets = 0;
//
//    for (int i = 0; i < SUBSET_COUNT; i++) {
//        printf("Subset %d: size=%d, elements=", i + 1, subsets[i].size);
//        print_subset(&subsets[i]);
//        printf("\n");
//        total_elements += subsets[i].size;
//
//        if (is_subset_empty(&subsets[i])) {
//            empty_subsets++;
//        }
//    }
//
//    printf("\nStatistics:\n");
//    printf("Average subset size: %.2f\n", (float)total_elements / SUBSET_COUNT);
//    printf("Total elements in all subsets: %d\n", total_elements);
//    printf("Valid subsets: %d/%d\n", valid_subsets, SUBSET_COUNT);
//    printf("Empty subsets count: %d\n", empty_subsets);
//
//    printf("\n============================================================\n");
//    printf("Start greedy selection of disjoint subsets...\n");
//
//    Subset chosen_subsets[SUBSET_COUNT];
//    int chosen_count;
//    Set n;
//
//    Subset subsets_copy[SUBSET_COUNT];
//    for (int i = 0; i < SUBSET_COUNT; i++) {
//        subsets_copy[i] = subsets[i];
//    }
//
//    greedy_max_disjoint_subsets(subsets_copy, SUBSET_COUNT, chosen_subsets, &chosen_count, &n);
//
//    printf("Selection results:\n");
//    printf("Number of disjoint subsets selected: %d\n", chosen_count);
//    printf("Number of distinct elements in N: %d\n", n.size);
//    printf("Elements in N: ");
//    print_set(&n);
//    printf("\n");
//
//    printf("\nSelected subsets:\n");
//    for (int i = 0; i < chosen_count; i++) {
//        printf("Subset%2d: ", i + 1);
//        print_subset(&chosen_subsets[i]);
//        printf("\n");
//    }
//
//    printf("\n============================================================\n");
//    printf("Coverage detection:\n");
//
//    Set all_covered;
//    init_set(&all_covered);
//    for (int i = 0; i < SUBSET_COUNT; i++) {
//        for (int j = 0; j < subsets[i].size; j++) {
//            add_to_set(&all_covered, subsets[i].elements[j]);
//        }
//    }
//
//    printf("Number of distinct elements covered by all subsets: %d\n", all_covered.size);
//    printf("Size of U: %d\n", U_SIZE);
//    printf("Whether all U is covered: %s\n", all_covered.size == U_SIZE ? "Yes" : "No");
//
//    printf("\n============================================================\n");
//    printf("Verify whether selected subsets are pairwise disjoint:\n");
//
//    bool all_disjoint = true;
//    Set verification_set;
//    init_set(&verification_set);
//
//    for (int i = 0; i < chosen_count; i++) {
//        for (int j = 0; j < chosen_subsets[i].size; j++) {
//            int element = chosen_subsets[i].elements[j];
//            if (set_contains(&verification_set, element)) {
//                printf("Error: Element %d appears in multiple selected subsets!\n", element);
//                all_disjoint = false;
//            }
//            else {
//                add_to_set(&verification_set, element);
//            }
//        }
//    }
//
//    if (all_disjoint) {
//        printf("Verification passed: Selected subsets are disjoint.\n");
//    }
//    else {
//        printf("Verification failed: There are intersections.\n");
//    }
//
//    return 0;
//}