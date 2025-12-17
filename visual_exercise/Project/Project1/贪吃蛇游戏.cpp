//#include <iostream>
//#include <windows.h>
//#include <conio.h>
//#include <cstdlib>
//#include <ctime>
//#include <deque>
//
//using namespace std;
//
//// 游戏核心配置（全英文符号，避免编译错误）
//const int WIDTH = 40;          // 游戏区域宽度
//const int HEIGHT = 20;         // 游戏区域高度
//const int INITIAL_LENGTH = 3;  // 蛇初始长度
//const int SPEED = 150;         // 移动间隔（毫秒）
//const int SCORE_PER_FOOD = 10; // 每个食物得分
//
//// 方向枚举（避免魔法数字）
//enum Direction {
//    UP = 1,
//    DOWN = 2,
//    LEFT = 3,
//    RIGHT = 4
//};
//
//// 坐标结构体（重载==方便比较）
//struct Point {
//    int x, y;
//    Point(int x = 0, int y = 0) : x(x), y(y) {}
//    bool operator==(const Point& other) const {
//        return x == other.x && y == other.y;
//    }
//};
//
//class SnakeGame {
//private:
//    deque<Point> snake;           // 蛇身（双端队列）
//    Point food;                   // 食物坐标
//    Direction direction;          // 当前方向
//    Direction nextDirection;      // 下一个方向（输入缓冲）
//    int score;                    // 得分
//    bool gameOver;                // 游戏结束标志
//    HANDLE hConsole;              // 控制台句柄
//    COORD cursorPos;              // 光标位置缓存
//
//    // 设置光标位置（封装Windows API）
//    void setCursorPos(int x, int y) {
//        cursorPos.X = x;
//        cursorPos.Y = y;
//        SetConsoleCursorPosition(hConsole, cursorPos);
//    }
//
//    // 隐藏控制台光标（消除闪烁）
//    void hideCursor() {
//        CONSOLE_CURSOR_INFO cursorInfo;
//        GetConsoleCursorInfo(hConsole, &cursorInfo);
//        cursorInfo.bVisible = false;
//        SetConsoleCursorInfo(hConsole, &cursorInfo);
//    }
//
//    // 绘制游戏边框
//    void drawBorder() {
//        // 上边框
//        for (int i = 0; i < WIDTH + 2; i++) {
//            setCursorPos(i, 0);
//            cout << "#";
//        }
//        // 下边框
//        for (int i = 0; i < WIDTH + 2; i++) {
//            setCursorPos(i, HEIGHT + 1);
//            cout << "#";
//        }
//        // 左边框
//        for (int i = 0; i < HEIGHT + 2; i++) {
//            setCursorPos(0, i);
//            cout << "#";
//        }
//        // 右边框
//        for (int i = 0; i < HEIGHT + 2; i++) {
//            setCursorPos(WIDTH + 1, i);
//            cout << "#";
//        }
//    }
//
//    // 生成食物（确保不在蛇身上）
//    void generateFood() {
//        do {
//            food.x = rand() % WIDTH + 1;
//            food.y = rand() % HEIGHT + 1;
//        } while (isPointInSnake(food));
//
//        // 绘制食物
//        setCursorPos(food.x, food.y);
//        cout << "$";
//    }
//
//    // 检查坐标是否在蛇身上
//    bool isPointInSnake(const Point& p) {
//        for (const auto& segment : snake) {
//            if (segment == p) {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    // 绘制蛇（只更新变化部分）
//    void drawSnake() {
//        // 绘制蛇头
//        setCursorPos(snake.front().x, snake.front().y);
//        cout << "@";
//
//        // 绘制蛇身
//        for (size_t i = 1; i < snake.size(); i++) {
//            setCursorPos(snake[i].x, snake[i].y);
//            cout << "*";
//        }
//    }
//
//    // 清除蛇尾（移动时覆盖）
//    void clearSnakeTail() {
//        if (!snake.empty()) {
//            setCursorPos(snake.back().x, snake.back().y);
//            cout << " ";
//        }
//    }
//
//    // 移动蛇（核心逻辑）
//    void moveSnake() {
//        // 更新方向
//        direction = nextDirection;
//
//        // 计算新蛇头
//        Point newHead = snake.front();
//        switch (direction) {
//        case UP:
//            newHead.y--;
//            break;
//        case DOWN:
//            newHead.y++;
//            break;
//        case LEFT:
//            newHead.x--;
//            break;
//        case RIGHT:
//            newHead.x++;
//            break;
//        }
//
//        // 碰撞检测
//        if (checkCollision(newHead)) {
//            gameOver = true;
//            return;
//        }
//
//        // 添加新蛇头
//        snake.push_front(newHead);
//
//        // 检查是否吃到食物
//        if (newHead == food) {
//            score += SCORE_PER_FOOD;
//            generateFood();
//        }
//        else {
//            // 未吃到食物则删除尾部
//            clearSnakeTail();
//            snake.pop_back();
//        }
//    }
//
//    // 碰撞检测（墙壁/自身）
//    bool checkCollision(const Point& head) {
//        // 墙壁碰撞
//        if (head.x <= 0 || head.x > WIDTH || head.y <= 0 || head.y > HEIGHT) {
//            return true;
//        }
//
//        // 自身碰撞
//        for (size_t i = 1; i < snake.size(); i++) {
//            if (head == snake[i]) {
//                return true;
//            }
//        }
//
//        return false;
//    }
//
//    // 处理键盘输入（无阻塞）
//    void handleInput() {
//        if (_kbhit()) {
//            char key = _getch();
//            switch (key) {
//                // 上（W/w）- 禁止直接反向
//            case 'w':
//            case 'W':
//                if (direction != DOWN) {
//                    nextDirection = UP;
//                }
//                break;
//                // 下（S/s）
//            case 's':
//            case 'S':
//                if (direction != UP) {
//                    nextDirection = DOWN;
//                }
//                break;
//                // 左（A/a）
//            case 'a':
//            case 'A':
//                if (direction != RIGHT) {
//                    nextDirection = LEFT;
//                }
//                break;
//                // 右（D/d）
//            case 'd':
//            case 'D':
//                if (direction != LEFT) {
//                    nextDirection = RIGHT;
//                }
//                break;
//                // 退出（Q/q）
//            case 'q':
//            case 'Q':
//                gameOver = true;
//                break;
//            }
//        }
//    }
//
//    // 更新并显示得分
//    void updateScore() {
//        setCursorPos(WIDTH + 5, 2);
//        cout << "Score: " << score << "   ";
//        setCursorPos(WIDTH + 5, 4);
//        cout << "Length: " << snake.size() << "   ";
//    }
//
//    // 游戏结束界面
//    void showGameOver() {
//        system("cls");
//        int centerX = WIDTH / 2 - 8;
//        int centerY = HEIGHT / 2;
//
//        setCursorPos(centerX, centerY);
//        cout << "===== GAME OVER =====";
//        setCursorPos(centerX, centerY + 1);
//        cout << "Final Score: " << score;
//        setCursorPos(centerX, centerY + 2);
//        cout << "Snake Length: " << snake.size();
//        setCursorPos(centerX, centerY + 4);
//        cout << "Press any key to exit...";
//        _getch();
//    }
//
//public:
//    // 构造函数：初始化游戏
//    SnakeGame() {
//        // 初始化控制台
//        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        hideCursor();
//
//        // 初始化游戏状态
//        score = 0;
//        gameOver = false;
//        direction = RIGHT;
//        nextDirection = RIGHT;
//
//        // 初始化蛇身（居中）
//        for (int i = 0; i < INITIAL_LENGTH; i++) {
//            snake.push_back(Point(WIDTH / 2 - i, HEIGHT / 2));
//        }
//
//        // 初始化随机数（仅一次）
//        srand((unsigned int)time(NULL));
//        generateFood();
//    }
//
//    // 游戏主循环
//    void run() {
//        system("cls");
//        drawBorder();
//        drawSnake();
//        updateScore();
//
//        // 主循环
//        while (!gameOver) {
//            handleInput();
//            moveSnake();
//            if (!gameOver) {
//                drawSnake();
//                updateScore();
//            }
//            Sleep(SPEED);
//        }
//
//        // 显示结束界面
//        showGameOver();
//    }
//};
//
//// 主函数（程序入口）
//int main() {
//    // 设置控制台窗口
//    system("mode con cols=60 lines=25");
//    system("title Classic Snake Game");
//
//    // 开始界面
//    cout << "==================== CLASSIC SNAKE GAME ====================" << endl;
//    cout << "Controls:" << endl;
//    cout << "  W / ↑ - Move Up" << endl;
//    cout << "  S / ↓ - Move Down" << endl;
//    cout << "  A / ← - Move Left" << endl;
//    cout << "  D / → - Move Right" << endl;
//    cout << "  Q     - Quit Game" << endl;
//    cout << "============================================================" << endl;
//    cout << "Press any key to start..." << endl;
//    _getch();
//
//    // 启动游戏
//    SnakeGame game;
//    game.run();
//
//    return 0;
//}