//#include <stdio.h>
//#include <stdlib.h>
//void init(int* data, int len)
//{
//	for (int i = 0; i < len; i++)
//	{
//		scanf("%d", data + i);
//	}
//}
//void prv(int* data, int len)
//{
//	for (int i = 0; i < len; i++)
//	{
//		printf("%d ", data[i]);
//	}
//}
//int search(int* data, int len, int key)
//{
//	for (int i = 0; i < len; i++)
//	{
//		if (*(data + i) == key)
//		{
//			return 1;
//		}
//	}
//	return 0;
//}
//int main()
//{
//	int len,key;
//	scanf("%d%d", &len, &key);
//	int* data = (int*)malloc(len * sizeof(int));
//	init(data, len);
//	prv(data, len);
//	if (search(data, len, key))
//	{
//		printf("found success");
//	}
//	else
//	{
//		printf("no found");
//	}
//	return 0;
//}