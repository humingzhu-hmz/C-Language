//#include <iostream>
//#include <vector>
//#include <string>
//#include <stack>
//#include <utility>
//#include <conio.h>
//#include <windows.h>
//using namespace std;
//
////棋盘大小
//const int BOARD_SIZE = 15;
//
//// 棋子类型
//enum PieceType { EMPTY, BLACK, WHITE };
//
//// 棋盘类
//class Board {
//private:
//    vector<vector<PieceType>> grid;
//    PieceType currentPlayer;
//    stack<pair<int, int>> history;      // 落子历史
//    stack<pair<int, int>> redoStack;    // 重做栈
//    stack<PieceType> playerHistory;     // 玩家历史
//
//public:
//    Board()
//    {
//        // 初始化棋盘
//        grid.resize(BOARD_SIZE, vector<PieceType>(BOARD_SIZE, EMPTY));
//        currentPlayer = BLACK;
//    }
//
//    //打印棋盘
//    void print()
//    {
//        system("cls");
//        cout << "   ";
//        // 打印列号
//        for (int i = 0; i < BOARD_SIZE; i++)
//            printf("%2d ", i);
//        cout << endl;
//
//        for (int i = 0; i < BOARD_SIZE; i++)
//        {
//            printf("%2d ", i); // 打印行号
//            for (int j = 0; j < BOARD_SIZE; j++)
//            {
//                switch (grid[i][j])
//                {
//                case EMPTY: cout << " . "; break;
//                case BLACK: cout << " X "; break;
//                case WHITE: cout << " O "; break;
//                }
//            }
//            cout << endl;
//        }
//        //显示当前玩家
//        cout << "当前玩家: " << (currentPlayer == BLACK ? "黑棋 (X)" : "白棋 (O)") << endl;
//    }
//
//    //落子
//    bool placePiece(int row, int col)
//    {
//        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
//        {
//            cout << "坐标超出范围，请重新输入！" << endl;
//            return false;
//        }
//        if (grid[row][col] != EMPTY)
//        {
//            cout << "该位置已有棋子，请重新输入！" << endl;
//            return false;
//        }
//        //放置棋子
//        grid[row][col] = currentPlayer;
//
//        // 记录历史
//        history.push(make_pair(row, col));
//        playerHistory.push(currentPlayer);
//
//        // 清空重做栈（新的落子后重做栈无效）
//        while (!redoStack.empty()) {
//            redoStack.pop();
//        }
//
//        return true;
//    }
//
//    //切换玩家
//    void switchPlayer()
//    {
//        currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
//    }
//
//    //检查胜利
//    bool checkWin(int row, int col)
//    {
//        PieceType piece = grid[row][col];
//        // 检查四个方向
//        const int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };
//        for (auto& dir : directions)
//        {
//            int count = 1;
//            // 向一个方向检查
//            for (int step = 1; step < 5; step++)
//            {
//                int r = row + dir[0] * step;
//                int c = col + dir[1] * step;
//                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && grid[r][c] == piece)
//                    count++;
//                else
//                    break;
//            }
//            // 向相反方向检查
//            for (int step = 1; step < 5; step++)
//            {
//                int r = row - dir[0] * step;
//                int c = col - dir[1] * step;
//                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && grid[r][c] == piece)
//                    count++;
//                else
//                    break;
//            }
//            // 检查是否有五子连珠
//            if (count >= 5)
//                return true;
//        }
//        return false;
//    }
//
//    //检查棋盘是否已满
//    bool isFull()
//    {
//        for (int i = 0; i < BOARD_SIZE; i++)
//        {
//            for (int j = 0; j < BOARD_SIZE; j++)
//            {
//                if (grid[i][j] == EMPTY)
//                    return false;
//            }
//        }
//        return true;
//    }
//
//    //获取当前玩家
//    PieceType getCurrentPlayer()
//    {
//        return currentPlayer;
//    }
//
//    // 悔棋
//    bool undo()
//    {
//        if (history.empty())
//        {
//            cout << "无法悔棋，历史记录为空！" << endl;
//            return false;
//        }
//
//        // 获取最后一步
//        pair<int, int> lastMove = history.top();
//        PieceType lastPlayer = playerHistory.top();
//
//        history.pop();
//        playerHistory.pop();
//
//        // 保存到重做栈
//        redoStack.push(lastMove);
//
//        // 清空该位置
//        grid[lastMove.first][lastMove.second] = EMPTY;
//
//        // 切换回上一个玩家
//        currentPlayer = lastPlayer;
//
//        return true;
//    }
//
//    // 重做
//    bool redo()
//    {
//        if (redoStack.empty())
//        {
//            cout << "无法重做，没有可恢复的步骤！" << endl;
//            return false;
//        }
//
//        // 获取重做步骤
//        pair<int, int> redoMove = redoStack.top();
//        redoStack.pop();
//
//        // 重新放置棋子
//        grid[redoMove.first][redoMove.second] = currentPlayer;
//
//        // 记录到历史
//        history.push(redoMove);
//        playerHistory.push(currentPlayer);
//
//        // 切换到下一个玩家
//        switchPlayer();
//
//        return true;
//    }
//
//    // 检查是否有重做步骤
//    bool canRedo()
//    {
//        return !redoStack.empty();
//    }
//
//    // 检查是否有悔棋步骤
//    bool canUndo()
//    {
//        return !history.empty();
//    }
//
//    // 清空历史记录（新游戏时使用）
//    void clearHistory()
//    {
//        while (!history.empty()) history.pop();
//        while (!redoStack.empty()) redoStack.pop();
//        while (!playerHistory.empty()) playerHistory.pop();
//    }
//};
//
////游戏类
//class Game
//{
//private:
//    Board board;
//
//    // 检测Ctrl组合键
//    bool isCtrlKeyPressed(int key)
//    {
//        return (GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(key) & 0x8000);
//    }
//
//public:
//    void start()
//    {
//        bool gameOver = false;
//        int row, col;
//
//        cout << "欢迎来到五子棋游戏！" << endl;
//        cout << "规则：两名玩家轮流在15x15的棋盘上放置黑白棋子，先连成五子者获胜。" << endl;
//        cout << "输入格式：请输入行号和列号，以空格分隔（例如：7 7）。" << endl;
//        cout << "快捷键：" << endl;
//        cout << "  - Ctrl+Z: 悔棋" << endl;
//        cout << "  - Ctrl+Y: 恢复" << endl;
//        cout << "  - 回车键: 结束游戏" << endl;
//        cout << "按任意键开始游戏..." << endl;
//        cin.get();
//
//        while (!gameOver)
//        {
//            board.print();
//
//            // 显示快捷键提示
//            cout << "快捷键: Ctrl+Z(悔棋) Ctrl+Y(恢复) 回车(结束游戏)" << endl;
//            if (board.canUndo()) {
//                cout << "提示：可以按 Ctrl+Z 悔棋" << endl;
//            }
//            if (board.canRedo()) {
//                cout << "提示：可以按 Ctrl+Y 恢复" << endl;
//            }
//            cout << "请输入落子位置（行 列）：";
//
//            // 检测键盘输入
//            if (_kbhit()) {
//                int ch = _getch();
//
//                // 检测Ctrl组合键
//                if (ch == 0 || ch == 0xE0) {
//                    ch = _getch();
//
//                    // Ctrl+Z (悔棋)
//                    if (ch == 26) {
//                        if (board.undo()) {
//                            cout << "悔棋成功！" << endl;
//                            continue;
//                        }
//                    }
//                    // Ctrl+Y (恢复)
//                    else if (ch == 25) {
//                        if (board.redo()) {
//                            cout << "恢复成功！" << endl;
//                            continue;
//                        }
//                    }
//                }
//                // 回车键 (结束游戏)
//                else if (ch == 13) {
//                    cout << endl << "确定要结束游戏吗？(y/n): ";
//                    char confirm = _getch();
//                    cout << confirm << endl;
//                    if (confirm == 'y' || confirm == 'Y') {
//                        cout << "游戏结束！" << endl;
//                        break;
//                    }
//                    else {
//                        cout << "继续游戏..." << endl;
//                        continue;
//                    }
//                }
//                else {
//                    // 如果不是特殊键，将字符放回输入缓冲区
//                    _ungetch(ch);
//                }
//            }
//
//            // 正常的输入处理
//            if (!(cin >> row >> col))
//            {
//                cout << "\n输入无效，请输入数字！" << endl;
//                cin.clear();
//                cin.ignore(10000, '\n');
//                continue;
//            }
//
//            //验证输入并落子
//            if (!board.placePiece(row, col))
//            {
//                cin.ignore(10000, '\n');
//                continue;
//            }
//
//            //检查胜利
//            if (board.checkWin(row, col))
//            {
//                board.print();
//                cout << (board.getCurrentPlayer() == BLACK ? "黑棋 (X)" : "白棋 (O)") << " 获胜！" << endl;
//                gameOver = true;
//
//                // 询问是否重新开始
//                cout << "是否重新开始游戏？(y/n): ";
//                char restart;
//                cin >> restart;
//                if (restart == 'y' || restart == 'Y') {
//                    // 重置游戏
//                    Board newBoard;
//                    board = newBoard;
//                    gameOver = false;
//                    cout << "新游戏开始！" << endl;
//                }
//            }
//            //检查平局
//            else if (board.isFull())
//            {
//                board.print();
//                cout << "平局！棋盘已满。" << endl;
//                gameOver = true;
//
//                // 询问是否重新开始
//                cout << "是否重新开始游戏？(y/n): ";
//                char restart;
//                cin >> restart;
//                if (restart == 'y' || restart == 'Y') {
//                    // 重置游戏
//                    Board newBoard;
//                    board = newBoard;
//                    gameOver = false;
//                    cout << "新游戏开始！" << endl;
//                }
//            }
//            //切换玩家
//            else
//            {
//                board.switchPlayer();
//            }
//        }
//        cout << "感谢游玩！" << endl;
//    }
//
//    // 新游戏
//    void newGame()
//    {
//        Board newBoard;
//        board = newBoard;
//        start();
//    }
//};
//
//int main()
//{
//    Game game;
//    game.start();
//    return 0;
//}