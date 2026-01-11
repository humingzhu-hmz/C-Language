#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAXN 22  
#define output_pathcount 30
int n;                     
int maze[MAXN][MAXN];       // Maze: -1 = wall, 0 = empty, -2 = start, -3 = exit
int path[MAXN][MAXN];       
bool visited[MAXN][MAXN];   
int path_count = 0;          

int dir[8][2] = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };
int start_x, start_y;

void print_maze_with_coord(int size, int maze[MAXN][MAXN], FILE* fp) {
   
    printf("    ");
	fprintf(fp,"    ");
    for(int j=0;j<size;j++){
        printf("%2d ", j);
		 fprintf(fp,"%2d ", j);
    }
    printf("\n");
    fprintf(fp,"\n");

    
    for(int i=0;i<size;i++){
        printf("%2d |", i);
 		fprintf(fp,"%2d |", i);
        for(int j=0;j<size;j++){
            if(maze[i][j] == -1){
              printf("\033[41m   \033[0m"); if(fp) fprintf(fp,"\033[41m   \033[0m");   // Wall
            }
            else if(maze[i][j] == 0){
                printf("   "); if(fp) fprintf(fp,"   ");   // Empty space
            }
            else if(maze[i][j] == -2){
                printf("  S"); if(fp) fprintf(fp," S ");   // Start
            }
            else if(maze[i][j] == -3){
                printf("  E"); if(fp) fprintf(fp," E ");   // Exit
            }
            else{
                printf("%3d", maze[i][j]); if(fp) fprintf(fp,"%3d", maze[i][j]);  // Step number
            }
        }
        printf("\n");
		fprintf(fp,"\n");
    }
    printf("\n");
	fprintf(fp,"\n");
}


void generate_maze(int size, int maze[MAXN][MAXN]) {
    srand((unsigned int)time(NULL));
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i==0 || i==size-1 || j==0 || j==size-1)
            {	
                maze[i][j] = -1; 
			}
			else
            {   
				maze[i][j] = (rand()%10 < 2) ? -1 : 0;
		  	}  // Random wall
            path[i][j]=maze[i][j];
        }
    }

    maze[size-2][size-2] = -3;
	path[size-2][size-2] = -3;  
}


void dfs(int x,int y,int step,int final_x,int final_y, FILE* fp){
    if(path_count>(final_x*final_y))
	{
		if(path_count==0){
		printf("No solution\n");
		fprintf(fp,"No solution\n");
		} 
		else {
			printf("Total paths: %d\n", path_count);
			fprintf(fp,"Total paths: %d\n", path_count);
		}

		fclose(fp);
        exit(0);
	}
	if(x==final_x && y==final_y){  // Reached exit
        path_count++;
		if(path_count <= output_pathcount)
		{
            path[x][y]=-3;
			printf("Path %d: total steps = %d\n", path_count, step);
			fprintf(fp,"Path %d: total steps = %d\n", path_count, step);
			print_maze_with_coord(n+2, path, fp);  // Print current path
		}  
        return;
    }

    visited[x][y] = true;
    path[x][y] = step;

    for(int i=0;i<8;i++){  
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];

        if(nx>=1 && nx<=n && ny>=1 && ny<=n && maze[nx][ny]!=-1 && !visited[nx][ny]){
            dfs(nx, ny, step+1, final_x, final_y, fp);
        }
    }
	path[x][y] = 0;  // current location has fall into died load ,around all is wall.
}

int main(){
    
    printf("Enter maze size n (<= 20): ");
    scanf("%d", &n);
    if(n<5 || n>20){
        printf("Invalid size\n");
        return 1;
    }

    
    generate_maze(n+2, maze);

    
    const char* filepath = "E:\\desktop\\Program_and_code\\C-Language-Files\\Visual School\\Basical Program Design\\final work (Program design base)\\Text\\Maze_graph.txt";
    FILE* fp = fopen(filepath,"w");
    if(!fp){printf("Cannot open file!\n"); return 1;}
    fprintf(fp,"Generated %dx%d maze:\n", n, n);
    print_maze_with_coord(n+2, maze, fp);
    fclose(fp);
    printf("Maze saved to file.\n");

    
   
    while(1){
        printf("Enter start point (x y, inside maze 1~%d, must be free): ", n);
        scanf("%d %d",&start_x,&start_y);
        if(start_x<1 || start_x>n || start_y<1 || start_y>n){
            printf("Coordinates out of range. Try again.\n");
            continue;
        }
        if(maze[start_x][start_y] != 0){
            printf("Start point cannot be on wall. Try again.\n");
            continue;
        }
        break;
    }

    maze[start_x][start_y] = -2;
    
    for(int i=0;i<n+2;i++)
        {
            for(int j=0;j<n+2;j++)
            {
                visited[i][j] = false;
            }
        }


    
    fp = fopen(filepath,"a"); 
    if(!fp){printf("Cannot open file!\n"); return 1;}

    dfs(start_x, start_y, 0, n, n, fp);

    if(path_count==0){
        printf("No solution\n");
        fprintf(fp,"No solution\n");
    } else {
        printf("Total paths: %d\n", path_count);
        fprintf(fp,"Total paths: %d\n", path_count);
    }

    fclose(fp);
    return 0;
}

 