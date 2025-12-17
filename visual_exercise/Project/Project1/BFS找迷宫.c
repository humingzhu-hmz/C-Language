//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <stdbool.h>
//#include <string.h>  // 新增：用于memset初始化数组
//
//#define LENGTH 15   // 迷宫长度（固定15，避免动态越界）
//#define WIDTH 15    // 迷宫宽度
//#define QUEUE_SIZE 4096  // 扩大队列（避免满队列导致越界）
//
//// 坐标结构体（用于队列存储）
//typedef struct {
//    int x, y;       // 当前坐标（严格限制0<=x<LENGTH，0<=y<WIDTH）
//    int step;       // 到达该位置的步数
//    int prevX, prevY;// 前驱坐标（-1表示无）
//} Pos;
//
//// 队列结构体（BFS核心，增加安全校验）
//typedef struct {
//    Pos data[QUEUE_SIZE];
//    int front;      // 队头（0 <= front < QUEUE_SIZE）
//    int rear;       // 队尾（0 <= rear < QUEUE_SIZE）
//} Queue;
//
//// 初始化队列（确保队头队尾为0）
//void initQueue(Queue* q) {
//    q->front = 0;
//    q->rear = 0;
//    // 清空队列内存（避免残留值）
//    memset(q->data, 0, sizeof(Pos) * QUEUE_SIZE);
//}
//
//// 判断队列是否为空
//bool isQueueEmpty(Queue* q) {
//    return q->front == q->rear;
//}
//
//// 判断队列是否已满（安全校验）
//bool isQueueFull(Queue* q) {
//    return (q->rear + 1) % QUEUE_SIZE == q->front;
//}
//
//// 入队（安全版：先判断是否满）
//bool enQueue(Queue* q, Pos pos) {
//    if (isQueueFull(q)) {
//        printf("⚠️ 队列已满，无法入队！\n");
//        return false;
//    }
//    q->data[q->rear] = pos;
//    q->rear = (q->rear + 1) % QUEUE_SIZE;
//    return true;
//}
//
//// 出队（安全版：先判断是否空）
//bool deQueue(Queue* q, Pos* pos) {
//    if (isQueueEmpty(q)) {
//        printf("⚠️ 队列为空，无法出队！\n");
//        return false;
//    }
//    *pos = q->data[q->front];
//    q->front = (q->front + 1) % QUEUE_SIZE;
//    return true;
//}
//
//// 输出迷宫（增加坐标校验，避免越界打印）
//void printMaze(int maze[LENGTH][WIDTH]) {
//    for (int i = 0; i < LENGTH; i++) {
//        // 校验行坐标
//        if (i < 0 || i >= LENGTH) continue;
//        for (int j = 0; j < WIDTH; j++) {
//            // 校验列坐标
//            if (j < 0 || j >= WIDTH) continue;
//            if (maze[i][j] == -1)      printf("###"); // 墙
//            else if (maze[i][j] == -2) printf("SSS"); // 起点
//            else if (maze[i][j] == -3) printf("EEE"); // 终点
//            else if (maze[i][j] == 0)  printf("   "); // 未走通路
//            else                      printf("%3d", maze[i][j]); // 步数
//        }
//        printf("\n");
//    }
//}
//
//// 生成随机迷宫（严格边界校验，避免越界赋值）
//void generateMaze(int maze[LENGTH][WIDTH]) {
//    // 1. 显式初始化全0（避免随机值）
//    memset(maze, 0, sizeof(int) * LENGTH * WIDTH);
//
//    // 2. 边界设为墙（严格校验坐标）
//    for (int k = 0; k < WIDTH; k++) {
//        if (k >= 0 && k < WIDTH) {
//            maze[0][k] = -1;                // 第一行
//            if (LENGTH - 1 >= 0) maze[LENGTH - 1][k] = -1; // 最后一行
//        }
//    }
//    for (int k = 0; k < LENGTH; k++) {
//        if (k >= 0 && k < LENGTH) {
//            maze[k][0] = -1;                // 第一列
//            if (WIDTH - 1 >= 0) maze[k][WIDTH - 1] = -1; // 最后一列
//        }
//    }
//
//    // 3. 内部随机生成墙（20%概率，严格校验坐标）
//    for (int i = 1; i < LENGTH - 1; i++) {
//        for (int j = 1; j < WIDTH - 1; j++) {
//            if (i >= 1 && i < LENGTH - 1 && j >= 1 && j < WIDTH - 1) {
//                maze[i][j] = (rand() % 10 < 2) ? -1 : 0;
//            }
//        }
//    }
//}
//
//// BFS寻路核心（全维度坐标校验，无访问冲突）
//bool bfsFindPath(int maze[LENGTH][WIDTH], int startX, int startY, int endX, int endY) {
//    // 1. 初始化队列和辅助数组（显式清空，避免野值）
//    Queue q;
//    initQueue(&q);
//    bool visited[LENGTH][WIDTH];
//    Pos prev[LENGTH][WIDTH];
//    memset(visited, false, sizeof(visited));  // 全设为未访问
//    memset(prev, -1, sizeof(prev));           // 前驱初始化为-1（无效值）
//
//    // 2. 移动方向：上、下、左、右（4方向）
//    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
//
//    // 3. 校验起点/终点合法性（核心！避免传入非法坐标）
//    if (startX < 0 || startX >= LENGTH || startY < 0 || startY >= WIDTH) {
//        printf("❌ 起点坐标非法！\n");
//        return false;
//    }
//    if (endX < 0 || endX >= LENGTH || endY < 0 || endY >= WIDTH) {
//        printf("❌ 终点坐标非法！\n");
//        return false;
//    }
//
//    // 4. 起点入队（标记已访问）
//    Pos startPos = { startX, startY, 0, -1, -1 };
//    enQueue(&q, startPos);
//    visited[startX][startY] = true;
//
//    // 5. BFS主循环（全程坐标校验）
//    while (!isQueueEmpty(&q)) {
//        Pos curr;
//        if (!deQueue(&q, &curr)) break; // 出队失败则退出
//
//        // 校验当前坐标合法性
//        if (curr.x < 0 || curr.x >= LENGTH || curr.y < 0 || curr.y >= WIDTH) {
//            continue;
//        }
//
//        // 到达终点：回溯路径（增加x/y非负校验）
//        if (curr.x == endX && curr.y == endY) {
//            int step = curr.step;
//            int x = curr.x, y = curr.y;
//            // 回溯时严格校验x/y（避免-1访问数组）
//            while (x >= 0 && x < LENGTH && y >= 0 && y < WIDTH) {
//                // 只标记通路，跳过起点/终点
//                if (maze[x][y] != -2 && maze[x][y] != -3) {
//                    maze[x][y] = step;
//                }
//                // 获取前驱（校验前驱坐标）
//                Pos p = prev[x][y];
//                if (p.prevX == -1 && p.prevY == -1) break; // 无前置则退出
//                x = p.prevX;
//                y = p.prevY;
//                step--;
//            }
//            printf("✅ 找到最短路径！共%d步\n", curr.step);
//            return true;
//        }
//
//        // 遍历4个方向（核心：全维度坐标校验）
//        for (int i = 0; i < 4; i++) {
//            int nx = curr.x + dirs[i][0];
//            int ny = curr.y + dirs[i][1];
//
//            // 合法性校验（5重防护，彻底避免越界）：
//            // 1. nx/ny在迷宫范围内 2. 未访问 3. 不是墙 4. 不是起点 5. 队列未满
//            if (nx >= 0 && nx < LENGTH && ny >= 0 && ny < WIDTH  // 1. 坐标合法
//                && !visited[nx][ny]                             // 2. 未访问
//                && (maze[nx][ny] == 0 || maze[nx][ny] == -3)    // 3. 通路/终点
//                && (maze[nx][ny] != -2)                          // 4. 不是起点
//                && !isQueueFull(&q)) {                           // 5. 队列未满
//
//                visited[nx][ny] = true;
//                Pos nextPos = { nx, ny, curr.step + 1, curr.x, curr.y };
//                enQueue(&q, nextPos);
//                prev[nx][ny] = nextPos; // 记录前驱（坐标已校验）
//            }
//        }
//    }
//
//    // 无通路
//    return false;
//}
//
//int main() {
//    // 1. 初始化迷宫数组（避免栈溢出，显式初始化）
//    int maze[LENGTH][WIDTH];
//    memset(maze, 0, sizeof(maze));
//    srand((unsigned int)time(NULL));
//
//    // 2. 生成迷宫
//    generateMaze(maze);
//
//    // 3. 随机选起点（严格校验非墙）
//    int startX, startY;
//    do {
//        startX = rand() % (LENGTH - 2) + 1;
//        startY = rand() % (WIDTH - 2) + 1;
//        // 校验起点坐标+是否为通路
//    } while (startX < 0 || startX >= LENGTH || startY < 0 || startY >= WIDTH || maze[startX][startY] != 0);
//    maze[startX][startY] = -2; // 标记起点
//
//    // 4. 固定终点（强制设为通路，校验坐标）
//    int endX = LENGTH - 2, endY = WIDTH - 2;
//    if (endX >= 0 && endX < LENGTH && endY >= 0 && endY < WIDTH) {
//        maze[endX][endY] = -3; // 标记终点
//    }
//
//    // 5. 打印初始迷宫
//    printf("🎮 初始迷宫（SSS=起点，EEE=终点，###=墙）：\n");
//    printMaze(maze);
//    printf("----------------------------------------\n");
//
//    // 6. BFS寻路（核心：无访问冲突）
//    bool hasPath = bfsFindPath(maze, startX, startY, endX, endY);
//
//    // 7. 输出结果
//    if (hasPath) {
//        printMaze(maze);
//    }
//    else {
//        printf("❌ 迷宫无通路！\n");
//    }
//
//    system("pause"); // 暂停控制台，避免闪退
//    return 0;
//}