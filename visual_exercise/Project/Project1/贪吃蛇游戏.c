//#include <stdio.h>
//#include <windows.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <stdbool.h>
//
//// 游戏核心配置
//#define WIDTH 40
//#define HEIGHT 20
//#define INITIAL_LENGTH 3
//#define SPEED 150
//#define SCORE_PER_FOOD 10
//
//// 方向枚举
//typedef enum {
//    UP = 1,
//    DOWN = 2,
//    LEFT = 3,
//    RIGHT = 4
//} Direction;
//
//// 坐标结构体
//typedef struct {
//    int x, y;
//} Point;
//
//// 蛇节点（简化为数组模拟，避免链表空指针崩溃）
//#define MAX_SNAKE_LENGTH 100
//typedef struct {
//    Point body[MAX_SNAKE_LENGTH]; // 蛇身数组（下标0为头）
//    int length;                   // 当前长度
//} Snake;
//
//// 游戏状态
//typedef struct {
//    Snake snake;                  // 蛇（数组替代链表，避免内存崩溃）
//    Point food;                   // 食物位置
//    Direction direction;          // 当前方向
//    Direction nextDirection;      // 下一个方向
//    int score;                    // 得分
//    bool gameOver;                // 游戏结束标志
//    HANDLE hConsole;              // 控制台句柄
//} GameState;
//
//// 工具函数：比较两个Point是否相等
//bool point_equals(Point a, Point b) {
//    return (a.x == b.x) && (a.y == b.y);
//}
//
//// 工具函数：设置光标位置（增加句柄有效性检查）
//bool set_cursor_pos(GameState* gs, int x, int y) {
//    if (gs->hConsole == INVALID_HANDLE_VALUE) {
//        return false;
//    }
//    COORD cursorPos = {x, y};
//    SetConsoleCursorPosition(gs->hConsole, cursorPos);
//    return true;
//}
//
//// 工具函数：隐藏控制台光标
//void hide_cursor(GameState* gs) {
//    if (gs->hConsole == INVALID_HANDLE_VALUE) {
//        return;
//    }
//    CONSOLE_CURSOR_INFO cursorInfo = {1, FALSE};
//    SetConsoleCursorInfo(gs->hConsole, &cursorInfo);
//}
//
//// 工具函数：初始化蛇（数组方式，绝对安全）
//void init_snake(GameState* gs) {
//    gs->snake.length = INITIAL_LENGTH;
//    // 居中水平放置蛇（下标0为头）
//    int startX = WIDTH / 2;
//    int startY = HEIGHT / 2;
//    for (int i = 0; i < gs->snake.length; i++) {
//        gs->snake.body[i].x = startX - i;
//        gs->snake.body[i].y = startY;
//    }
//}
//
//// 工具函数：检查点是否在蛇身上
//bool is_point_in_snake(GameState* gs, Point p) {
//    for (int i = 0; i < gs->snake.length; i++) {
//        if (point_equals(gs->snake.body[i], p)) {
//            return true;
//        }
//    }
//    return false;
//}
//
//// 工具函数：生成食物（增加边界检查）
//void generate_food(GameState* gs) {
//    Point food;
//    int retry = 0;
//    do {
//        food.x = rand() % WIDTH + 1;
//        food.y = rand() % HEIGHT + 1;
//        retry++;
//        // 防止死循环（蛇占满区域时退出）
//        if (retry > 1000) {
//            gs->gameOver = true;
//            return;
//        }
//    } while (is_point_in_snake(gs, food));
//
//    gs->food = food;
//    set_cursor_pos(gs, food.x, food.y);
//    printf("$");
//}
//
//// 工具函数：绘制蛇
//void draw_snake(GameState* gs) {
//    // 绘制蛇头
//    set_cursor_pos(gs, gs->snake.body[0].x, gs->snake.body[0].y);
//    printf("@");
//    // 绘制蛇身
//    for (int i = 1; i < gs->snake.length; i++) {
//        set_cursor_pos(gs, gs->snake.body[i].x, gs->snake.body[i].y);
//        printf("*");
//    }
//}
//
//// 工具函数：清除蛇尾
//void clear_snake_tail(GameState* gs) {
//    Point tail = gs->snake.body[gs->snake.length - 1];
//    set_cursor_pos(gs, tail.x, tail.y);
//    printf(" ");
//}
//
//// 工具函数：绘制游戏边框
//void draw_border(GameState* gs) {
//    // 上边框
//    for (int i = 0; i < WIDTH + 2; i++) {
//        set_cursor_pos(gs, i, 0);
//        printf("#");
//    }
//    // 下边框
//    for (int i = 0; i < WIDTH + 2; i++) {
//        set_cursor_pos(gs, i, HEIGHT + 1);
//        printf("#");
//    }
//    // 左边框
//    for (int i = 0; i < HEIGHT + 2; i++) {
//        set_cursor_pos(gs, 0, i);
//        printf("#");
//    }
//    // 右边框
//    for (int i = 0; i < HEIGHT + 2; i++) {
//        set_cursor_pos(gs, WIDTH + 1, i);
//        printf("#");
//    }
//}
//
//// 工具函数：检查碰撞
//bool check_collision(GameState* gs, Point head) {
//    // 墙壁碰撞
//    if (head.x <= 0 || head.x > WIDTH || head.y <= 0 || head.y > HEIGHT) {
//        return true;
//    }
//    // 自身碰撞
//    for (int i = 1; i < gs->snake.length; i++) {
//        if (point_equals(head, gs->snake.body[i])) {
//            return true;
//        }
//    }
//    return false;
//}
//
//// 工具函数：移动蛇（数组方式，无内存泄漏）
//void move_snake(GameState* gs) {
//    gs->direction = gs->nextDirection;
//
//    // 计算新蛇头
//    Point newHead = gs->snake.body[0];
//    switch (gs->direction) {
//        case UP:    newHead.y--; break;
//        case DOWN:  newHead.y++; break;
//        case LEFT:  newHead.x--; break;
//        case RIGHT: newHead.x++; break;
//    }
//
//    // 碰撞检测
//    if (check_collision(gs, newHead)) {
//        gs->gameOver = true;
//        return;
//    }
//
//    // 检查是否吃到食物
//    bool eatFood = point_equals(newHead, gs->food);
//
//    // 没吃到食物则清除尾部
//    if (!eatFood) {
//        clear_snake_tail(gs);
//    } else {
//        // 吃到食物，长度+1（不超过最大值）
//        if (gs->snake.length < MAX_SNAKE_LENGTH) {
//            gs->snake.length++;
//        }
//        gs->score += SCORE_PER_FOOD;
//        generate_food(gs);
//    }
//
//    // 蛇身整体后移（关键：数组方式无指针错误）
//    for (int i = gs->snake.length - 1; i > 0; i--) {
//        gs->snake.body[i] = gs->snake.body[i - 1];
//    }
//    // 设置新蛇头
//    gs->snake.body[0] = newHead;
//}
//
//// 工具函数：处理键盘输入（增加容错）
//void handle_input(GameState* gs) {
//    if (!_kbhit()) {
//        return;
//    }
//    int key = _getch(); // 用int接收，避免EOF错误
//    if (key == EOF) {
//        return;
//    }
//    switch (key) {
//        case 'w': case 'W':
//            if (gs->direction != DOWN) gs->nextDirection = UP;
//            break;
//        case 's': case 'S':
//            if (gs->direction != UP) gs->nextDirection = DOWN;
//            break;
//        case 'a': case 'A':
//            if (gs->direction != RIGHT) gs->nextDirection = LEFT;
//            break;
//        case 'd': case 'D':
//            if (gs->direction != LEFT) gs->nextDirection = RIGHT;
//            break;
//        case 'q': case 'Q':
//            gs->gameOver = true;
//            break;
//    }
//}
//
//// 工具函数：更新得分
//void update_score(GameState* gs) {
//    set_cursor_pos(gs, WIDTH + 5, 2);
//    printf("Score: %d   ", gs->score);
//    set_cursor_pos(gs, WIDTH + 5, 4);
//    printf("Length: %d   ", gs->snake.length);
//}
//
//// 工具函数：游戏结束界面
//void show_game_over(GameState* gs) {
//    system("cls");
//    int centerX = WIDTH / 2 - 8;
//    int centerY = HEIGHT / 2;
//    set_cursor_pos(gs, centerX, centerY);
//    printf("===== GAME OVER =====");
//    set_cursor_pos(gs, centerX, centerY + 1);
//    printf("Final Score: %d", gs->score);
//    set_cursor_pos(gs, centerX, centerY + 2);
//    printf("Snake Length: %d", gs->snake.length);
//    set_cursor_pos(gs, centerX, centerY + 4);
//    printf("Press any key to exit...");
//    _getch();
//}
//
//// 初始化游戏（核心：修复所有崩溃点）
//void game_init(GameState* gs) {
//    // 1. 优先获取控制台句柄，失败则提示
//    gs->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    if (gs->hConsole == INVALID_HANDLE_VALUE) {
//        printf("获取控制台句柄失败！\n");
//        exit(1);
//    }
//
//    // 2. 初始化游戏状态
//    gs->score = 0;
//    gs->gameOver = false;
//    gs->direction = RIGHT;
//    gs->nextDirection = RIGHT;
//
//    // 3. 初始化蛇（数组方式，无空指针）
//    init_snake(gs);
//
//    // 4. 隐藏光标
//    hide_cursor(gs);
//
//    // 5. 初始化随机数
//    srand((unsigned int)time(NULL));
//
//    // 6. 生成初始食物
//    generate_food(gs);
//}
//
//// 游戏主循环
//void game_run(GameState* gs) {
//    // 清屏 + 设置窗口大小（顺序调整，避免窗口大小错误）
//    system("cls");
//    system("mode con cols=60 lines=25");
//    system("title Classic Snake Game (C Version)");
//
//    // 绘制初始界面
//    draw_border(gs);
//    draw_snake(gs);
//    update_score(gs);
//
//    // 主循环（增加防卡死）
//    int loopCount = 0;
//    while (!gs->gameOver && loopCount < 10000) {
//        handle_input(gs);
//        move_snake(gs);
//        if (!gs->gameOver) {
//            draw_snake(gs);
//            update_score(gs);
//        }
//        Sleep(SPEED);
//        loopCount++;
//    }
//
//    show_game_over(gs);
//}
//
//// 主函数（极简，避免参数错误）
//int main() {
//    // 开始界面（简化，避免输入错误）
//    system("cls");
//    printf("==================== CLASSIC SNAKE GAME ====================\n");
//    printf("Controls: WASD to move, Q to quit\n");
//    printf("Press any key to start...\n");
//    
//    // 等待按键（增加容错）
//    while (!_kbhit()); // 等待按键按下
//    _getch(); // 读取按键（清空缓冲区）
//
//    // 初始化并运行游戏
//    GameState game;
//    game_init(&game);
//    game_run(&game);
//
//    return 0;
//}