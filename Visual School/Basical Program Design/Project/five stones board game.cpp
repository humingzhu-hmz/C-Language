#include <stdio.h>
#include <string.h>
#include <easyx.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tchar.h>
#include <conio.h>

//define constant 

#define BOARD_MARGIN 40
#define BOARD_SIZE 19
#define BOARD_COLOR RGB(222, 184, 135)
#define CHESS_REDIOUS 18
#define LINE_WIDTH 3
#define LINE_COLOR BLACK
#define GRID_SIZE 40
#define STAR_COLOR RGB(255,0,0)
#define MAXCHESS 361
#define MAXBACKCOUNT 3
ExMessage msg = { 0 };
typedef struct CHESS_BOARD
{
	int x, y;
	int COLOR;
}CHESS_BOARD;

int towardtime = 0;
int currentx = 9;
int currenty = 9;
int backcount = 0;
int chesscount = 0;
int currentplayer = 0;
bool gameover = false;
CHESS_BOARD chessboard[MAXCHESS];
int direction[4][2] = { {0,1},{1,1},{1,0},{1,-1} };

//draw chessboard
void drawchessboard()
{
	setfillcolor(BOARD_COLOR);
	setlinecolor(LINE_COLOR);
	setlinestyle(PS_SOLID, 3);
	settextcolor(BLACK);
	settextstyle(20, 0, _T("Arial"));
	solidrectangle(BOARD_MARGIN - 10, BOARD_MARGIN - 10,
		BOARD_MARGIN + BOARD_SIZE * GRID_SIZE + 10, BOARD_MARGIN + BOARD_SIZE * GRID_SIZE + 10);
	for (int i = 0; i <= BOARD_SIZE; i++)
	{
		//draw horizontal and vertical line
		TCHAR order[3];
		char buf[3];
		_stprintf_s(order, _T("%d"), i);
		outtextxy(10, BOARD_MARGIN + GRID_SIZE * i - 5, order);
		line(BOARD_MARGIN, BOARD_MARGIN + GRID_SIZE * i, BOARD_MARGIN + BOARD_SIZE * GRID_SIZE, BOARD_MARGIN + GRID_SIZE * i);
		outtextxy(BOARD_MARGIN + GRID_SIZE * i - 5, 10, order);
		line(BOARD_MARGIN + GRID_SIZE * i, BOARD_MARGIN, BOARD_MARGIN + GRID_SIZE * i, BOARD_MARGIN + GRID_SIZE * BOARD_SIZE);
	}
	// draw star point
	setfillcolor(STAR_COLOR);
	int starpoint[9][2] = {
		{3,3},{3,9},{3,15},
		{9,3},{9,9},{9,15},
		{15,3},{15,9},{15,15}
	};
	for (int i = 0; i < 9; i++)
	{
		int x = BOARD_MARGIN + starpoint[i][0] * GRID_SIZE;
		int y = BOARD_MARGIN + starpoint[i][1] * GRID_SIZE;
		solidcircle(x, y, 6);
	}
}

//draw all chess
void drawallchess()
{
	for (int i = 0; i < chesscount; i++)
	{
		int chessx = chessboard[i].x * GRID_SIZE + BOARD_MARGIN;
		int chessy = chessboard[i].y * GRID_SIZE + BOARD_MARGIN;
		setfillcolor(chessboard[i].COLOR == 0 ? BLACK : WHITE);
		solidcircle(chessx, chessy, CHESS_REDIOUS);
	}
}

// draw single chess
void drawsinglechess(int newchessx, int newchessy, int color)
{
	int screenX = newchessx * GRID_SIZE + BOARD_MARGIN;
	int screenY = newchessy * GRID_SIZE + BOARD_MARGIN;
	setfillcolor(color == 0 ? BLACK : WHITE);
	for (int i = 3; i <= CHESS_REDIOUS; i += 3)
	{
		solidcircle(screenX, screenY, i);
		Sleep(18);
	}
}

//draw cursor
void drawcursor(int currentx, int currenty)
{
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 2);//Pen Style
	int x = BOARD_MARGIN + currentx * GRID_SIZE;
	int y = BOARD_MARGIN + currenty * GRID_SIZE;
	line(x - GRID_SIZE / 2, y - GRID_SIZE / 2, x + GRID_SIZE / 2, y - GRID_SIZE / 2);
	line(x - GRID_SIZE / 2, y + GRID_SIZE / 2, x + GRID_SIZE / 2, y + GRID_SIZE / 2);
	line(x - GRID_SIZE / 2, y - GRID_SIZE / 2, x - GRID_SIZE / 2, y + GRID_SIZE / 2);
	line(x + GRID_SIZE / 2, y - GRID_SIZE / 2, x + GRID_SIZE / 2, y + GRID_SIZE / 2);
}

//display games information
void Gameinfo()
{
	settextcolor(BLACK);
	settextstyle(25, 0, _T("Arial"));

	TCHAR cuplayer[50];
	_stprintf_s(cuplayer, _T("Current: % s"), currentplayer == 0 ? _T("Black") : _T("White"));
	outtextxy(820, 50, cuplayer);

	TCHAR chessCountText[50];
	_stprintf_s(chessCountText, _T("ChessCount:%d"), chesscount);
	outtextxy(820, 90, chessCountText);

	TCHAR backcountText[50];
	_stprintf_s(backcountText, _T("BackCount:%d"), backcount);
	outtextxy(820, 120, backcountText);
	// Controls
	outtextxy(820, 150, _T("Controls:"));
	outtextxy(820, 180, _T("Arrow Keys: Move"));
	outtextxy(820, 210, _T("Space: Place"));
	outtextxy(820, 240, _T("ctrl+z/Z:take back"));
	outtextxy(820, 270, _T("ctrl+z/Z:take forward"));
	outtextxy(820, 300, _T("R: Restart"));
	outtextxy(820, 330, _T("ESC: Exit"));
}

// disapper carton
void discarton(int undox, int undoy)
{
	for (int i = CHESS_REDIOUS; i >= 0; i--)
	{
		BeginBatchDraw();
		cleardevice();
		drawchessboard();
		drawallchess();
		drawcursor(currentx, currenty);
		setfillcolor(chessboard[chesscount].COLOR == 0 ? BLACK : WHITE);
		solidcircle(undox * GRID_SIZE + BOARD_MARGIN, undoy * GRID_SIZE + BOARD_MARGIN, i);
		Gameinfo();
		EndBatchDraw();
		Sleep(18);
	}
}

//check chess
int	 checkchess(int currentx, int currenty)
{
	int chessx = currentx;
	int chessy = currenty;
	for (int i = 0; i < chesscount; i++)
	{
		if (chessboard[i].x == chessx && chessboard[i].y == chessy)
		{
			return chessboard[i].COLOR + 1;
		}
	}
	return 0;
}

// add chess
bool addchess(int currentx, int currenty)
{
	if (checkchess(currentx, currenty) > 0)
	{
		return false;
	}
	chessboard[chesscount].x = currentx;
	chessboard[chesscount].y = currenty;
	chessboard[chesscount].COLOR = currentplayer;
	chesscount++;
	return true;
}

//check win
bool appearwin(int currentx, int currenty)
{
	for (int d = 0; d < 4; d++)
	{
		int count = 1;
		for (int j = 1; j <= 4; j++)
		{
			int x = currentx + j * direction[d][0];
			int y = currenty + j * direction[d][1];
			if (x <= BOARD_SIZE && y <= BOARD_SIZE && checkchess(x, y) == currentplayer + 1)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		for (int k = 1; k <= 4; k++)
		{
			int x = currentx - k * direction[d][0];
			int y = currenty - k * direction[d][1];
			if (x >= 0 && y >= 0 && checkchess(x, y) == currentplayer + 1)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		if (count >= 5)
		{
			return true;
		}
	}
	return false;
}

// take back 
void undo()
{
	if (backcount < MAXBACKCOUNT)
	{
		chesscount--;
		backcount++;
		towardtime++;
		int undox = chessboard[chesscount].x;
		int undoy = chessboard[chesscount].y;
		currentplayer = 1 - currentplayer;
		discarton(undox, undoy);
	}
}

// take forward
void redo()
{
	if (backcount > 0 && towardtime)
	{
		drawsinglechess(chessboard[chesscount].x, chessboard[chesscount].y, chessboard[chesscount].COLOR);
		chesscount++;
		backcount--;
		towardtime--;
		currentplayer = 1 - currentplayer;
	}
}

void restartgame()
{
	gameover = false;
	chesscount = 0;
	backcount = 0;
}
int main()
{
	initgraph(1010, 850, EX_SHOWCONSOLE);
	setbkcolor(RGB(240, 240, 240));
	cleardevice();


	DWORD lastspacetime = 0;
	DWORD lastrtime = 0;
	TCHAR WINMESSAGE[100];
	while (true)
	{
		bool freechess = false;
		if (peekmessage(&msg, EX_KEY))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (gameover && (msg.vkcode != 'R' || msg.vkcode != 'r') && msg.vkcode == VK_ESCAPE)
				{
					break;
				}
				short ctrlstate = GetKeyState(VK_CONTROL);
				bool ctrlpressed = (ctrlstate & 0x8000 == 0) ? false : true;
				switch (msg.vkcode)
				{
				case 'z':
				case 'Z':if (ctrlpressed) {
					undo();
					break;
				}
						break;
				case 'y':
				case 'Y':if (ctrlpressed) {
					redo();
					freechess = true;
					break;
				}
						break;
				case 'w':
				case 'W':
				case VK_UP:
					if (currenty > 0)currenty--; break;
				case 's':
				case 'S':
				case VK_DOWN:
					if (currenty < BOARD_SIZE)currenty++; break;
				case 'a':
				case 'A':
				case VK_LEFT:
					if (currentx > 0)currentx--; break;
				case 'd':
				case 'D':
				case VK_RIGHT:
					if (currentx < BOARD_SIZE)currentx++; break;
				case 'r':
				case 'R':
					restartgame();
					currentx = 9;
					currenty = 9;
					system("cls");
					break;
				case VK_SPACE:
					if (GetTickCount() - lastspacetime > 20 && !gameover)
					{
						if (checkchess(currentx, currenty) == 0)
						{
							addchess(currentx, currenty);
							if (backcount > 0) backcount--;
							towardtime = 0;
							freechess = true;
							printf("%s at (%d,%d)\n", currentplayer == 0 ? "black" : "white", currentx, currenty);
							drawsinglechess(currentx, currenty, currentplayer);

							if (appearwin(currentx, currenty))
							{
								_stprintf_s(WINMESSAGE, _T("WIN:%s"), currentplayer == 0 ? _T("black") : _T("white"));
								gameover = true;
								system("cls");
								break;
							}
							currentplayer = 1 - currentplayer;
						}
					}
					lastspacetime = GetTickCount();
					break;
				case VK_ESCAPE:
					return 0;
				}
			}
		}
		if (!freechess)
		{
			BeginBatchDraw();
			cleardevice();
			drawchessboard();
			drawallchess();
			drawcursor(currentx, currenty);
			Gameinfo();
		}
		if (gameover)
		{
			settextcolor(RED);
			settextstyle(35, 0, _T("Arial"));
			outtextxy(700, 360, WINMESSAGE);
			settextcolor(BLUE);
			outtextxy(700, 400, _T("Press R to Restart!"));
		}
		EndBatchDraw();
	}
	closegraph();
	return 0;
}