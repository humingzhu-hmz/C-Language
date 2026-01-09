#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define longth 15
#define width 15
void prn(int arr[longth][width])
{
	for (int i = 0; i<longth; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (arr[i][j] == -1) {
				printf("###");
			}
			else if (arr[i][j] == 0) {
				printf("   ");
			}
			else if (arr[i][j] == -2) {
				printf("SSS");
			}
			else if (arr[i][j] == -3) {
				printf("EEE");
			}
			else {
				printf("%3d", arr[i][j]);
			}
		}
		printf("\n");
	}
}
bool isExit(int posx, int posy,int finalposx,int finalposy)
{
	return (posx == finalposx && posy == finalposy);
}
typedef struct Move
{
	int posx, posy;
}Move;
Move move[4] = { {0,1},{1,0},{0,-1},{-1,0} };
void Maze(int arr[longth][width], int currentposx, int currentposy, int *step,int finalposx,int finalposy,int *flag)
{
	for (int i = 0; i < 4; i++)
	{
		if (arr[currentposx + move[i].posx][currentposy + move[i].posy] == 0)
		{
			if (*flag >= ((longth - 1) * (width - 1)*0.8))
			{
				printf("");
				exit(1);
			}
			int newposx = currentposx + move[i].posx;
			int newposy = currentposy + move[i].posy;
			arr[newposx][newposy] = ++(*step);
			*flag = *flag + 1;
			if (!isExit(newposx, newposy, finalposx, finalposy))
			{
				Maze(arr, newposx, newposy, step, finalposx, finalposy,flag);
			}
			else
			{
				printf(":\n", (*step));
				arr[longth - 2][width - 2] = -3;
				prn(arr);
				exit(0);
			}
			arr[newposx][newposy] = 0;
			(*step)--;
		}
	}
}
void generate_rand_maze(int arr[longth][width])
{
	srand((unsigned int)time(NULL));
	for (int k = 0; k<width; k++)
	{
		arr[0][k] = -1;
		arr[longth - 1][k] = -1;
	}
	for (int k = 0; k<longth; k++)
	{
		arr[k][0] = -1;
		arr[k][width - 1] = -1;
	}
	for (int i = 1; i<longth - 1; i++)
	{
		for (int j = 1; j < width-1; j++)
		{
			arr[i][j] = (rand() % 10<2)? - 1:0;
		}
	}
}
int main()
{
	int arr[longth][width];
	srand((unsigned int)time(NULL));

	//generate initial maze and print maze
	generate_rand_maze(arr);
	int startposx, startposy;
	while (1)
	{
		startposx = rand() % (longth - 2) + 1;
		startposy = rand() % (width - 2) + 1;
		if (arr[startposx][startposy] == 0)
		{
			break;
		}
	}
	arr[startposx][startposy] = -2;
	arr[longth - 2][width - 2] = -3;
	prn(arr);

	// generate begin pos
	
	int step = 0;
	
	//find exit
	int flag = 0;
	arr[longth - 2][width - 2] = 0;
	Maze(arr, startposx, startposy, &step, longth - 2, width - 2,&flag);
	return 0;
}