#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <tchar.h>  // 添加这个头文件

ExMessage msg = { 0 };

#define BOARD_SIZE 19      // 19x19 board
#define GRID_SIZE 40       // grid size
#define BOARD_MARGIN 40    // board margin
#define CHESS_RADIUS 18    // chess radius
#define BOARD_COLOR RGB(222, 184, 135)  // board color
#define LINE_COLOR RGB(101, 67, 33)     // line color
#define STAR_COLOR RED     // star point color

typedef struct ChessPiece {
    int x, y;           // board coordinates (0-18)
    int color;          // 0:white, 1:black
} ChessPiece;

// Record chess pieces
#define MAXCHESS 361  // 19*19=361
ChessPiece chessboard[MAXCHESS];
int chessCount = 0;    // number of chess pieces
int currentColor = 1;  // current player 1:black first

// Check if position has chess piece
int chessCheck(int x, int y) {
    for (int i = 0; i < chessCount; i++) {
        if (chessboard[i].x == x && chessboard[i].y == y) {
            return chessboard[i].color + 1; // return 1:white, 2:black
        }
    }
    return 0; // no chess piece
}

// Check for five in a row
int checkWin(int x, int y, int color) {
    int directions[4][2] = {
        {1, 0},   // horizontal
        {0, 1},   // vertical
        {1, 1},   // diagonal down-right
        {1, -1}   // diagonal up-right
    };

    for (int d = 0; d < 4; d++) {
        int count = 1; // current position has one piece

        // Forward check
        for (int i = 1; i <= 4; i++) {
            int nx = x + directions[d][0] * i;
            int ny = y + directions[d][1] * i;

            if (nx >= 0 && nx < BOARD_SIZE &&
                ny >= 0 && ny < BOARD_SIZE &&
                chessCheck(nx, ny) == color + 1) {
                count++;
            }
            else {
                break;
            }
        }

        // Backward check
        for (int i = 1; i <= 4; i++) {
            int nx = x - directions[d][0] * i;
            int ny = y - directions[d][1] * i;

            if (nx >= 0 && nx < BOARD_SIZE &&
                ny >= 0 && ny < BOARD_SIZE &&
                chessCheck(nx, ny) == color + 1) {
                count++;
            }
            else {
                break;
            }
        }

        if (count >= 5) {
            return 1; // win
        }
    }

    return 0; // not win
}

// Add chess piece
void addChessPiece(int x, int y, int color) {
    if (chessCheck(x, y) > 0) {
        return; // position already has piece
    }

    if (chessCount < MAXCHESS) {
        chessboard[chessCount].x = x;
        chessboard[chessCount].y = y;
        chessboard[chessCount].color = color;
        chessCount++;
    }
}

// Draw chess board
void drawChessBoard() {
    // Draw board background
    setfillcolor(BOARD_COLOR);
    solidrectangle(BOARD_MARGIN - 10, BOARD_MARGIN - 10,
        BOARD_MARGIN + GRID_SIZE * (BOARD_SIZE - 1) + 10,
        BOARD_MARGIN + GRID_SIZE * (BOARD_SIZE - 1) + 10);

    setlinecolor(LINE_COLOR);
    setlinestyle(PS_SOLID, 3);

    // Draw horizontal and vertical lines
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Horizontal lines
        line(BOARD_MARGIN, BOARD_MARGIN + i * GRID_SIZE,
            BOARD_MARGIN + GRID_SIZE * (BOARD_SIZE - 1), BOARD_MARGIN + i * GRID_SIZE);

        // Vertical lines
        line(BOARD_MARGIN + i * GRID_SIZE, BOARD_MARGIN,
            BOARD_MARGIN + i * GRID_SIZE, BOARD_MARGIN + GRID_SIZE * (BOARD_SIZE - 1));
    }

    // Draw star points (9)
    int starPoints[9][2] = {
        {3, 3}, {3, 9}, {3, 15},
        {9, 3}, {9, 9}, {9, 15},
        {15, 3}, {15, 9}, {15, 15}
    };

    setfillcolor(STAR_COLOR);
    for (int i = 0; i < 9; i++) {
        int x = BOARD_MARGIN + starPoints[i][0] * GRID_SIZE;
        int y = BOARD_MARGIN + starPoints[i][1] * GRID_SIZE;
        solidcircle(x, y, 5);
    }
}

// Draw all chess pieces
void drawAllChessPieces() {
    for (int i = 0; i < chessCount; i++) {
        int pixelX = BOARD_MARGIN + chessboard[i].x * GRID_SIZE;
        int pixelY = BOARD_MARGIN + chessboard[i].y * GRID_SIZE;

        if (chessboard[i].color == 0) { // white
            setfillcolor(WHITE);
            setlinecolor(BLACK);
            fillcircle(pixelX, pixelY, CHESS_RADIUS);
        }
        else { // black
            setfillcolor(BLACK);
			setlinecolor(BLACK);// black border for black pieces（轮廓）
			fillcircle(pixelX, pixelY, CHESS_RADIUS);//circle () only draws outline
        }
    }
}


// Draw current cursor position
void drawCursor(int x, int y) {
    int pixelX = BOARD_MARGIN + x * GRID_SIZE;
    int pixelY = BOARD_MARGIN + y * GRID_SIZE;

    setlinecolor(RED);
    setlinestyle(PS_SOLID, 2);
    rectangle(pixelX - CHESS_RADIUS, pixelY - CHESS_RADIUS,
        pixelX + CHESS_RADIUS, pixelY + CHESS_RADIUS);
}

// Draw game info
void drawGameInfo() {
    settextcolor(BLACK);
    settextstyle(20, 0, _T("Arial"));// height ,width, ipszface

    // Current player info
    TCHAR currentPlayer[50];
    _stprintf_s(currentPlayer, _T("Current: %s"), currentColor == 1 ? _T("Black") : _T("White"));
	outtextxy(650, 50, currentPlayer);// x,y, text

    // Chess piece count
    TCHAR chessCountText[50];
    _stprintf_s(chessCountText, _T("Chess: %d"), chessCount);
    outtextxy(650, 70, chessCountText);
    

    // Controls
    outtextxy(650, 150, _T("Controls:"));
    outtextxy(650, 180, _T("Arrow Keys: Move"));
    outtextxy(650, 210, _T("Space: Place"));
    outtextxy(650, 240, _T("R: Restart"));
    outtextxy(650, 270, _T("ESC: Exit"));
}

// Restart game
void restartGame() {
    chessCount = 0;
    currentColor = 1;
}

int main() {
    initgraph(850, 800, EX_SHOWCONSOLE);

    // Set background color
    setbkcolor(RGB(240, 240, 240));
    cleardevice();

    // Initial cursor position (center)
    int cursorX = 9;
    int cursorY = 9;

    DWORD lastSpaceTime = 0;
    DWORD lastRTime = 0;

    int gameOver = 0;
    TCHAR winMessage[100] = _T("");

    while (true) {
        // Process messages
        if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
            switch (msg.message) {
            case WM_KEYDOWN:
                if (gameOver && msg.vkcode != 'R' && msg.vkcode != VK_ESCAPE) {
                    break;
                }

               switch (msg.vkcode) {
                case VK_UP:
                    if (cursorY > 0) cursorY--;
                    break;
                case VK_DOWN:
                    if (cursorY < BOARD_SIZE - 1) cursorY++;
                    break;
                case VK_LEFT:
                    if (cursorX > 0) cursorX--;
                    break;
                case VK_RIGHT:
                    if (cursorX < BOARD_SIZE - 1) cursorX++;
                    break;
                case VK_SPACE:
                    if (GetTickCount() - lastSpaceTime > 200 && !gameOver) {
                        if (chessCheck(cursorX, cursorY) == 0) {
                            addChessPiece(cursorX, cursorY, currentColor);
                            printf("%s at: (%d, %d)\n",
                                currentColor == 1 ? "Black" : "White",
                                cursorX, cursorY);

                            // Check win
                            if (checkWin(cursorX, cursorY, currentColor)) {
                                gameOver = 1;
                                _stprintf_s(winMessage, _T("%s Wins!"),
                                    currentColor == 1 ? _T("Black") : _T("White"));
                                printf("%s\n", winMessage);
                            }
                            else {
                                // Switch player
                                currentColor = 1 - currentColor;
                            }

                            lastSpaceTime = GetTickCount();
                        }
                    }
                    break;
                case 'R':
                    if (GetTickCount() - lastRTime > 500) {
                        restartGame();
                        gameOver = 0;
                        winMessage[0] = '\0';
                        lastRTime = GetTickCount();
                    }
                    break;
                case VK_ESCAPE:
                    closegraph();
                    return 0;
                }
                break;
            }
        }

        // Start batch drawing
        BeginBatchDraw();//applying for cache space to draw,
                        //after end of draw,will display all at once
        cleardevice();

        // Draw board
        drawChessBoard();

        // Draw all pieces
        drawAllChessPieces();

        // Draw cursor
        if (!gameOver) {
            drawCursor(cursorX, cursorY);
        }

        // Draw game info
        drawGameInfo();

        // If game over, show win message
        if (gameOver) {
            settextcolor(RED);
            settextstyle(30, 0, _T("Arial"));
            outtextxy(650, 350, winMessage);

            settextcolor(BLUE);
            settextstyle(20, 0, _T("Arial"));
            outtextxy(650, 400, _T("Press R to restart"));
        }

        EndBatchDraw();
        Sleep(50); // Control frame rate
    }

    closegraph();
    return 0;
}