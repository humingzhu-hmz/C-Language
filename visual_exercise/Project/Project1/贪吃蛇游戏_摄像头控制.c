#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// OpenCV头文件 - 需要安装OpenCV库
#ifdef _WIN32
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#endif

// 游戏配置
#define WIDTH 40
#define HEIGHT 20
#define INITIAL_LENGTH 3

// 方向枚举
typedef enum {
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
    NONE = 0
} Direction;

// 坐标结构体
typedef struct {
    int x;
    int y;
} Point;

// 蛇节点结构体
typedef struct SnakeNode {
    Point pos;
    struct SnakeNode* next;
} SnakeNode;

// 游戏状态结构体
typedef struct {
    SnakeNode* head;
    SnakeNode* tail;
    Point food;
    Direction direction;
    Direction nextDirection;
    int score;
    int gameOver;
    HANDLE hOut;
    COORD cursorPos;
    int snakeLength;
} SnakeGame;

// 全局变量用于摄像头控制
#ifdef _WIN32
cv::VideoCapture* cap = NULL;
cv::Mat frame, hsv, mask;
cv::Scalar lowerBound, upperBound;
Point lastHandPos = { -1, -1 };
#endif

// 设置光标位置
void gotoxy(SnakeGame* game, int x, int y) {
    game->cursorPos.X = x;
    game->cursorPos.Y = y;
    SetConsoleCursorPosition(game->hOut, game->cursorPos);
}

// 隐藏光标
void hideCursor(SnakeGame* game) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(game->hOut, &cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(game->hOut, &cursorInfo);
}

// 创建蛇节点
SnakeNode* createNode(int x, int y) {
    SnakeNode* node = (SnakeNode*)malloc(sizeof(SnakeNode));
    if (node == NULL) {
        return NULL;
    }
    node->pos.x = x;
    node->pos.y = y;
    node->next = NULL;
    return node;
}

// 添加节点到蛇头
void addToHead(SnakeGame* game, int x, int y) {
    SnakeNode* newNode = createNode(x, y);
    if (newNode == NULL) {
        return;
    }
    newNode->next = game->head;
    game->head = newNode;
    if (game->tail == NULL) {
        game->tail = newNode;
    }
    game->snakeLength++;
}

// 移除蛇尾
void removeTail(SnakeGame* game) {
    if (game->head == NULL || game->tail == NULL) {
        return;
    }
    if (game->head == game->tail) {
        free(game->tail);
        game->head = NULL;
        game->tail = NULL;
        game->snakeLength = 0;
        return;
    }
    SnakeNode* current = game->head;
    while (current->next != game->tail) {
        current = current->next;
    }
    free(game->tail);
    game->tail = current;
    game->tail->next = NULL;
    game->snakeLength--;
}

// 检查点是否在蛇身上
int isSnakeBody(SnakeGame* game, Point p) {
    SnakeNode* current = game->head;
    while (current != NULL) {
        if (current->pos.x == p.x && current->pos.y == p.y) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// 绘制边框
void drawBorder(SnakeGame* game) {
    int i;
    // 上边框
    for (i = 0; i < WIDTH + 2; i++) {
        gotoxy(game, i, 0);
        printf("#");
    }
    // 下边框
    for (i = 0; i < WIDTH + 2; i++) {
        gotoxy(game, i, HEIGHT + 1);
        printf("#");
    }
    // 左边框
    for (i = 0; i < HEIGHT + 2; i++) {
        gotoxy(game, 0, i);
        printf("#");
    }
    // 右边框
    for (i = 0; i < HEIGHT + 2; i++) {
        gotoxy(game, WIDTH + 1, i);
        printf("#");
    }
}

// 生成食物
void generateFood(SnakeGame* game) {
    srand((unsigned int)time(NULL));
    do {
        game->food.x = rand() % WIDTH + 1;
        game->food.y = rand() % HEIGHT + 1;
    } while (isSnakeBody(game, game->food));
}

// 绘制蛇
void drawSnake(SnakeGame* game) {
    SnakeNode* current = game->head;
    int index = 0;
    while (current != NULL) {
        gotoxy(game, current->pos.x, current->pos.y);
        if (index == 0) {
            printf("@"); // 蛇头
        }
        else {
            printf("*"); // 蛇身
        }
        current = current->next;
        index++;
    }
}

// 绘制食物
void drawFood(SnakeGame* game) {
    gotoxy(game, game->food.x, game->food.y);
    printf("$");
}

// 清除蛇尾
void clearTail(SnakeGame* game) {
    if (game->tail != NULL) {
        gotoxy(game, game->tail->pos.x, game->tail->pos.y);
        printf(" ");
    }
}

// 检查碰撞
int checkCollision(SnakeGame* game, Point head) {
    // 检查墙壁碰撞
    if (head.x <= 0 || head.x > WIDTH || head.y <= 0 || head.y > HEIGHT) {
        return 1;
    }
    // 检查自身碰撞（跳过头部）
    SnakeNode* current = game->head->next;
    while (current != NULL) {
        if (head.x == current->pos.x && head.y == current->pos.y) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// 移动蛇
void moveSnake(SnakeGame* game) {
    // 更新方向
    game->direction = game->nextDirection;
    if (game->direction == NONE) {
        return;
    }

    // 计算新头部位置
    Point newHead;
    if (game->head != NULL) {
        newHead.x = game->head->pos.x;
        newHead.y = game->head->pos.y;
    }
    else {
        return;
    }

    switch (game->direction) {
    case UP:
        newHead.y--;
        break;
    case DOWN:
        newHead.y++;
        break;
    case LEFT:
        newHead.x--;
        break;
    case RIGHT:
        newHead.x++;
        break;
    }

    // 检查碰撞
    if (checkCollision(game, newHead)) {
        game->gameOver = 1;
        return;
    }

    // 添加新头部
    addToHead(game, newHead.x, newHead.y);

    // 检查是否吃到食物
    if (newHead.x == game->food.x && newHead.y == game->food.y) {
        game->score += 10;
        generateFood(game);
        drawFood(game);
    }
    else {
        // 如果没有吃到食物，移除尾部
        clearTail(game);
        removeTail(game);
    }
}

// 显示得分
void displayScore(SnakeGame* game) {
    gotoxy(game, WIDTH + 5, 2);
    printf("Score: %d", game->score);
    gotoxy(game, WIDTH + 5, 4);
    printf("Length: %d", game->snakeLength);
}

// 显示游戏结束信息
void displayGameOver(SnakeGame* game) {
    system("cls");
    gotoxy(game, WIDTH / 2 - 5, HEIGHT / 2);
    printf("Game Over!");
    gotoxy(game, WIDTH / 2 - 5, HEIGHT / 2 + 1);
    printf("Final Score: %d", game->score);
    gotoxy(game, WIDTH / 2 - 5, HEIGHT / 2 + 2);
    printf("Press any key to exit...");
    _getch();
}

// 初始化摄像头（使用颜色追踪）
#ifdef _WIN32
int initCamera() {
    cap = new cv::VideoCapture(0);
    if (!cap->isOpened()) {
        printf("Error: Cannot open camera!\n");
        return 0;
    }
    
    // 设置HSV颜色范围（用于追踪特定颜色，例如红色）
    // 可以根据需要调整这些值来追踪不同颜色的物体
    lowerBound = cv::Scalar(0, 50, 50);   // 红色下限
    upperBound = cv::Scalar(10, 255, 255); // 红色上限
    
    return 1;
}

// 从摄像头获取手势方向
Direction getDirectionFromCamera() {
    if (cap == NULL || !cap->isOpened()) {
        return NONE;
    }
    
    *cap >> frame;
    if (frame.empty()) {
        return NONE;
    }
    
    // 翻转图像（镜像效果）
    cv::flip(frame, frame, 1);
    
    // 转换为HSV颜色空间
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
    
    // 创建颜色掩码
    cv::inRange(hsv, lowerBound, upperBound, mask);
    
    // 形态学操作，去除噪声
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);
    
    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    if (contours.empty()) {
        return NONE;
    }
    
    // 找到最大的轮廓（假设是手）
    int maxArea = 0;
    int maxIdx = -1;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxIdx = i;
        }
    }
    
    if (maxIdx == -1 || maxArea < 1000) { // 面积太小，忽略
        return NONE;
    }
    
    // 计算质心
    cv::Moments moments = cv::moments(contours[maxIdx]);
    if (moments.m00 == 0) {
        return NONE;
    }
    
    int cx = (int)(moments.m10 / moments.m00);
    int cy = (int)(moments.m01 / moments.m00);
    
    Point currentHandPos = { cx, cy };
    
    // 在图像上绘制追踪点
    cv::circle(frame, cv::Point(cx, cy), 10, cv::Scalar(0, 255, 0), -1);
    cv::imshow("Hand Tracking", frame);
    cv::waitKey(1);
    
    // 如果这是第一次检测，只记录位置
    if (lastHandPos.x == -1) {
        lastHandPos = currentHandPos;
        return NONE;
    }
    
    // 计算移动方向
    int dx = currentHandPos.x - lastHandPos.x;
    int dy = currentHandPos.y - lastHandPos.y;
    
    // 设置阈值，避免微小移动
    int threshold = 30;
    
    Direction dir = NONE;
    
    if (abs(dx) > abs(dy)) {
        // 水平移动
        if (dx > threshold) {
            dir = RIGHT;
        }
        else if (dx < -threshold) {
            dir = LEFT;
        }
    }
    else {
        // 垂直移动
        if (dy > threshold) {
            dir = DOWN;
        }
        else if (dy < -threshold) {
            dir = UP;
        }
    }
    
    lastHandPos = currentHandPos;
    return dir;
}

// 释放摄像头资源
void releaseCamera() {
    if (cap != NULL) {
        cap->release();
        delete cap;
        cap = NULL;
    }
    cv::destroyAllWindows();
}
#else
int initCamera() {
    printf("OpenCV not available on this platform.\n");
    return 0;
}

Direction getDirectionFromCamera() {
    return NONE;
}

void releaseCamera() {
    // 空实现
}
#endif

// 处理输入（键盘或摄像头）
void handleInput(SnakeGame* game, int useCamera) {
    if (useCamera) {
        // 使用摄像头控制
        Direction camDir = getDirectionFromCamera();
        if (camDir != NONE) {
            // 防止反向移动
            if ((camDir == UP && game->direction != DOWN) ||
                (camDir == DOWN && game->direction != UP) ||
                (camDir == LEFT && game->direction != RIGHT) ||
                (camDir == RIGHT && game->direction != LEFT)) {
                game->nextDirection = camDir;
            }
        }
    }
    else {
        // 使用键盘控制
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'w':
            case 'W':
                if (game->direction != DOWN) {
                    game->nextDirection = UP;
                }
                break;
            case 's':
            case 'S':
                if (game->direction != UP) {
                    game->nextDirection = DOWN;
                }
                break;
            case 'a':
            case 'A':
                if (game->direction != RIGHT) {
                    game->nextDirection = LEFT;
                }
                break;
            case 'd':
            case 'D':
                if (game->direction != LEFT) {
                    game->nextDirection = RIGHT;
                }
                break;
            case 'q':
            case 'Q':
                game->gameOver = 1;
                break;
            }
        }
    }
}

// 初始化游戏
void initGame(SnakeGame* game) {
    game->hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor(game);
    game->score = 0;
    game->gameOver = 0;
    game->direction = RIGHT;
    game->nextDirection = RIGHT;
    game->head = NULL;
    game->tail = NULL;
    game->snakeLength = 0;

    // 初始化蛇（水平放置）
    int i;
    for (i = 0; i < INITIAL_LENGTH; i++) {
        addToHead(game, WIDTH / 2 - i, HEIGHT / 2);
    }

    generateFood(game);
}

// 释放游戏资源
void freeGame(SnakeGame* game) {
    SnakeNode* current = game->head;
    while (current != NULL) {
        SnakeNode* next = current->next;
        free(current);
        current = next;
    }
    game->head = NULL;
    game->tail = NULL;
}

// 游戏主循环
void runGame(SnakeGame* game, int useCamera) {
    system("cls");
    drawBorder(game);
    drawSnake(game);
    drawFood(game);
    displayScore(game);

    while (!game->gameOver) {
        handleInput(game, useCamera);
        moveSnake(game);
        if (!game->gameOver) {
            drawSnake(game);
            displayScore(game);
        }
        Sleep(150); // 控制游戏速度（毫秒）
    }

    displayGameOver(game);
}

int main() {
    // 设置控制台窗口大小
    system("mode con cols=60 lines=25");
    system("title Snake Game - Camera Control");

    printf("========== Snake Game ==========\n");
    printf("Control Mode:\n");
    printf("1 - Keyboard (W/A/S/D)\n");
    printf("2 - Camera Hand Tracking\n");
    printf("Enter choice (1 or 2): ");
    
    int choice;
    scanf("%d", &choice);
    
    int useCamera = 0;
    if (choice == 2) {
        useCamera = 1;
        printf("Initializing camera...\n");
        if (!initCamera()) {
            printf("Camera initialization failed! Using keyboard control instead.\n");
            useCamera = 0;
        }
        else {
            printf("Camera initialized! Show a colored object (red recommended) to the camera.\n");
            printf("Move it up/down/left/right to control the snake.\n");
            printf("Press any key to start...\n");
            _getch();
        }
    }
    else {
        printf("Controls:\n");
        printf("W/A/S/D - Move Up/Left/Down/Right\n");
        printf("Q - Quit Game\n");
        printf("Press any key to start...\n");
        _getch();
    }

    SnakeGame game;
    initGame(&game);
    runGame(&game, useCamera);
    freeGame(&game);
    
    if (useCamera) {
        releaseCamera();
    }

    return 0;
}

