#include <stdio.h>
int main()
{
	printf("?????:\n");
	for (int i = 1; i <= 9; i++)
	{
		for (int k = 1; k <= i; k ++ )
		{if(k==3&&i==3||k==3&&i==4)
			printf("   %dx%d=%d", k, i, i * k);
			else printf("  %dx%d=%d", k,i , i * k);
		}
		printf("\n");
	}
	return 0;
}