//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <stdbool.h>
//#define MAX_SET_SIZE 200
//#define MAX_SUBSET_SIZE 25
//#define MAXvalue 1000
//#define MAX_SUBSET_COUNT 25
//typedef struct Set
//{
//	int elements[MAX_SET_SIZE];
//	int size;
//}Set;
//typedef struct Subset
//{
//	int elements[MAX_SUBSET_SIZE];
//	int size;
//}Subset;
//void init_Subset(Subset* S)
//{
//	S = (Subset*)malloc(sizeof(Subset));
//	S->size = 0;
//}
//void init_Set(Set* S)
//{
//	S->size = 0;
//}
//bool is_Subset_empty(Subset* S)
//{
//	if (S->size == 0)
//	{
//		return true;
//	}
//	return false;
//}
//bool is_Set_empty(Set* set)
//{
//	if (set->size == 0)
//	{
//		return true;
//	}
//	return false;
//}
//bool add_to_set(Set* chosen_set,Subset subset1)
//{
//	for (int i = 0; i < subset1.size; i++)
//	{
//		chosen_set->elements[chosen_set->size++] =subset1.elements[i] ;
//	}
//	return true;
//}
//bool set_contain(Set *S,int element)
//{
//	if (is_Set_empty(S))
//	{
//		return false;
//	}
//	for (int i = 0; i < S->size; i++)
//	{
//		if (S->elements[i] == element)
//			return true;
//	}
//	return false;
//}
//bool are_disjoint(Subset* subset1, Subset* subset2)
//{
//	Subset* outer = subset1->size < subset2->size ? subset1 : subset2;
//	Subset* inner = subset1->size >= subset2->size ? subset1: subset2;
//	for (int i = 0; i < outer->size; i++)
//	{
//		for (int j = 0; j < inner->size; j++)
//		{
//			if (outer->elements[i] == inner->elements[j])
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//void generate_rand_Set(Set* U)
//{
//	for (int i = 0; i < U->size; i++)
//	{
//		U->elements[i] = rand() % MAXvalue + 1;
//		for (int j = 0; j <i; j++)
//		{
//			if (U->elements[j] == U->elements[i])
//			{
//				i--;
//				break;
//			}
//		}
//	}
//}
//void generate_rand_Subset(Set* U, Subset* subset,int subsetcount)
//{
//	for (int i = 0; i < subsetcount; i++)
//	{
//		init_Subset(&subset[i]);
//		subset[i].size = rand() % (MAX_SUBSET_SIZE/2) + 1;
//		int* flag = (int*)calloc(U->size, sizeof(int));
//		for (int j = 0; j < subset[i].size; j++)
//		{
//			int index = rand() % U->size;
//			if (flag[index] == 1)
//			{
//				j--;
//				continue;
//			}
//			flag[index] = 1;
//			subset[i].elements[j] = U->elements[index];
//		}
//		free(flag);
//	}
//
//}
//int comparing_subset(const void*subset1, const void*subset2)
//{
//	const Subset* sa = (const Subset*)subset1;
//	const Subset* sb = (const Subset*)subset2;
//	return sa->size - sb->size;
//}
//void greedy_find_max_disjoint(Subset *chosen_set[], int* chosen_set_count,
//	int Subsetcount, Subset subset[], Set* chosen_elements,int arr[])
//{
//	int k = 0;
//	qsort(subset, Subsetcount, sizeof(Subset), comparing_subset);
//	init_Set(chosen_elements);
//	*(chosen_set_count) = 0;
//	for (int i = 0; i < Subsetcount; i++)
//	{
//		bool not_contain = true;
//		for (int j = 0; j < subset[i].size; j++)
//		{
//			if (set_contain(chosen_elements, subset[i].elements[j]))
//			{
//				not_contain = false;
//				break;
//			}
//		}
//		if (not_contain)
//		{
//			chosen_set[*(chosen_set_count)] = &subset[i];
//			(*chosen_set_count)++;
//			arr[k++] = i+1;
//			add_to_set(chosen_elements, subset[i]);
//		}
//		if (*chosen_set_count >= MAX_SUBSET_COUNT)
//		{
//			break;
//		}
//	}
//}
//void printSubset(Subset subset)
//{
//	if (is_Subset_empty(&subset))
//	{
//		printf("{ }");
//		return;
//	}
//	printf("{");
//	for (int i = 0; i < subset.size-1; i++)
//	{
//		printf(" %d ,", subset.elements[i]);
//	}
//	printf(" %d }\n", subset.elements[subset.size - 1]);
//}
//void printSet(Set set)
//{
//	if (is_Set_empty(&set))
//	{
//		printf("\n{ }\n");
//		return;
//	}
//	printf("\n{");
//		for (int i = 0; i < set.size - 1; i++)
//		{
//			printf(" %d ,", set.elements[i]);
//		}
//		printf(" %d }\n", set.elements[set.size - 1]);
//}
//int main()
//{
//	srand((unsigned int)time(NULL));
//	Set* U,*chosen_elements,*Newjoint;
//	U = (Set*)malloc(sizeof(Set));
//	if (!U)
//	{
//		fprintf(stderr," U reserve allocate fail!\n");
//		fprintf(stdout, "program end!");
//		exit(1);
//	}
//	chosen_elements = (Set*)malloc(sizeof(Set));
//	if (!chosen_elements)
//	{
//		fprintf(stderr, " chosen_elements reserve allocate fail!\n");
//		fprintf(stdout, "program end!");
//		free(U);
//		exit(1);
//	}
//	int chosen_set_count = 0;
//	U->size = rand() % (MAX_SET_SIZE / 2) + (MAX_SET_SIZE / 2);
//	int subset_count = rand() % (MAX_SUBSET_COUNT / 2) + (MAX_SUBSET_COUNT / 2);
//	Subset*subset = (Subset*)malloc(subset_count *sizeof(Subset));
//	if (!subset)
//	{
//		fprintf(stderr, " subset reserve allocate fail!\n");
//		fprintf(stdout, "program end!");
//		free(U);
//		free(chosen_elements);
//		exit(1);
//	}
//	Subset**chosen_set = (Subset**)malloc(MAX_SUBSET_COUNT * sizeof(Subset*));
//	if (!chosen_set)
//	{
//		fprintf(stderr, " chosen_set reserve allocate fail!\n");
//		fprintf(stdout, "program end!");
//		free(U);
//		free(chosen_elements);
//		free(chosen_set);
//		exit(1);
//	}
//	printf("Start generating random subsets and using greedy algorithm to find disjoint subsets...\n");
//	printf("U value range: 1 to 1000 (total %d elements)\n", U->size);
//	printf("Will generate %d random subsets...\n\n", subset_count);
//
//	printf("---------------------------------------------------------\n");
//	printf("generate rand Set is:\n");
//	generate_rand_Set(U);
//	printSet(*U);
//	printf("---------------------------------------------------------\n");
//	printf("generate random Subset:\n");
//	generate_rand_Subset(U, subset, subset_count);
//
//	int  total_elements = 0;
//	int empty_subsets = 0;
//	int* arr = (int*)malloc(subset_count * sizeof(int));
//	for (int i = 0; i < subset_count;i++)
//	{
//
//		printf("Subset %-2d: size = %-2d, elements=:", i + 1, subset[i].size);
//		printSubset(subset[i]);
//		total_elements += subset[i].size;
//		if (is_Subset_empty(&subset[i]))
//		{
//			empty_subsets++;
//		}
//	}
//
//	printf("---------------------------------------------------------\n");
//	printf("\nStatistics:\n");
//	printf("Average subset size: %.2f\n", (float)total_elements /subset_count );
//	printf("Total elements in all subsets: %d\n", total_elements);
//	printf("Empty subsets count: %d\n", empty_subsets);
//	printf("---------------------------------------------------------\n");
//	printf("starting use greedy to find max disjoint set:\n");
//
//	greedy_find_max_disjoint(chosen_set, &chosen_set_count,
//		subset_count, subset, chosen_elements,arr);
//
//	Newjoint = chosen_elements;
//	printf("slected result is:\n");
//	printf("Number of disjiont subsets selected :%d\n", chosen_set_count);
//	printf("Number of disjiont elements in N:%d\n", chosen_elements->size);
//	printf("Elements in N:");
//	printSet(*Newjoint);
//	printf("---------------------------------------------------------\n");
//
//
//	printf("chosen Subset:\n");
//
//	for (int i = 0; i < chosen_set_count; i++)
//	{
//		printf("subset %-3d:", arr[i]);
//		printSubset(*chosen_set[i]);
//	}
//
//	printf("---------------------------------------------------------\n");
//	printf("Coverage detection");
//	
//	
//	Set all_covered;
//	init_Set(&all_covered);
//	for (int i = 0; i < subset_count; i++) {
//		for (int j = 0; j < subset[i].size; j++) 
//		{
//			for (int k = 0; k < all_covered.size; k++)
//			{
//				if (all_covered.elements[k] == subset[i].elements[j]);
//				break;
//			}
//			all_covered.elements[all_covered.size++] = subset[i].elements[j];
//		}
//	}
//	printf("Number of distinct elements covered by all subsets: %d\n", all_covered.size);
//	printf("Size of U: %3d\n", U->size);
//	printf("Whether all U is covered: %s\n", all_covered.size == U->size ? "Yes" : "No");
//
//	free(arr);
//	free(U);
//	free(subset);
//	free(chosen_set);
//	free(chosen_elements);
//	return 0;
//}