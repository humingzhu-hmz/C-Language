#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <easyx.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tchar.h>
#include <conio.h>
#include <time.h>

//define constant 

#define BOARD_MARGIN 40
#define BOARD_SIZE 18
#define BOARD_COLOR RGB(222, 184, 135)
#define CHESS_REDIOUS 18
#define LINE_WIDTH 3
#define LINE_COLOR BLACK
#define GRID_SIZE 40
#define STAR_COLOR RGB(255,0,0)
#define MAXCHESS 361
#define MAXBACKCOUNT 3
#define Threat_serious 5
#define Threat_stronger 4
#define Threat_middle 3
#define Threat_weak 2
#define Threat_weaker 1

ExMessage msg;

typedef struct CHESS_BOARD
{
	int x, y;
	int COLOR;
}CHESS_BOARD;

typedef struct Keymessage
{
	bool space;
	bool esc;
	bool shift;
	int elsekey;
}Keymessage;

bool havetarkey = false;
Keymessage Key;
int lastkeytime = 0;
bool exitmode2 = false;
bool beginover = true;
bool maxpriority = true;
int (*Strategy)();
int (*Strategy1)();
int (*Strategy2)();
DWORD mode = 1;
int ComputerPlayer = 1;
int Player = 1;
int prioritymode = 1;
int strategy = 2;
int towardtime = 0;
int currentx = 9;
int currenty = 9;
int backcount = 0;
int chesscount = 0;
int currentplayercolor = 0;
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
	settextcolor(GREEN);
	settextstyle(30, 0, _T("Arial"));

	TCHAR player[50];
	_stprintf_s(player, _T("Player:%s"), Player == 1 ? _T("Humans") : ("Computer"));
	outtextxy(790, 35, player);

	TCHAR cuplayer[50];
	_stprintf_s(cuplayer, _T("Current: % s"), currentplayercolor == 0 ? _T("Black") : _T("White"));
	outtextxy(790, 70, cuplayer);

	settextcolor(BLACK);
	settextstyle(25, 0, _T("Arial"));

	TCHAR chessCountText[50];
	_stprintf_s(chessCountText, _T("ChessCount:%d"), chesscount);
	outtextxy(790, 110, chessCountText);

	TCHAR backcountText[50];
	_stprintf_s(backcountText, _T("BackCount:%d"), backcount);
	outtextxy(790, 140, backcountText);

	TCHAR towardtimeText[50];
	_stprintf_s(towardtimeText, _T("Towardtime:%d"), towardtime);
	outtextxy(790, 170, towardtimeText);
	// Controls
	outtextxy(790, 200, _T("Controls:"));
	outtextxy(790, 230, _T("Arrow Keys: Move"));

	TCHAR SPACETEXT[50];
	_stprintf_s(SPACETEXT, _T("Space: % s"), mode != 2 ? _T("Place") : _T("Suspend"));
	outtextxy(790, 260, SPACETEXT);

	outtextxy(790, 300, _T("ctrl+z/Z:take back"));
	outtextxy(790, 330, _T("ctrl+z/Z:take forward"));
	outtextxy(790, 360, _T("R: Restart"));
	outtextxy(790, 390, _T("ESC: Exit"));
	if (mode == 2)
	{
		outtextxy(790, 430, _T("After press space, "));
		outtextxy(790, 460, _T("After press space, "));
		outtextxy(790, 490, _T("After press space, "));
	}
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
	chessboard[chesscount].COLOR = currentplayercolor;
	chesscount++;
	return true;
}

//check win
bool appearwin(int currentx, int currenty, int color)// check win
{
	if (chesscount < 8)return false;
	for (int d = 0; d < 4; d++)
	{
		int count = 1;
		for (int j = 1; j <= 4; j++)
		{
			int x = currentx + j * direction[d][0];
			int y = currenty + j * direction[d][1];
			if (x <= BOARD_SIZE && y <= BOARD_SIZE && checkchess(x, y) == color + 1)
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
			if (x >= 0 && y >= 0 && checkchess(x, y) == color + 1)
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

// strategy functions
int strategy1()
{
	if (chesscount == 0)
	{
		currentx = 9;
		currenty = 9;
	}
	if (chesscount == MAXCHESS) return false;
	int x, y;
	do
	{
		x = rand() % (BOARD_SIZE + 1);
		y = rand() % (BOARD_SIZE + 1);
	} while (checkchess(x, y) != 0);

	currentx = x;
	currenty = y;
	return 0;
}

int threat_degree(int x, int y, int humancolor)
{
	if (chesscount < 5) return Threat_weaker;
	int threat_state = Threat_weaker;
	int threat_temp = Threat_weaker;
	if (appearwin(x, y, humancolor))// check human (priority defend)
	{
		threat_state = Threat_serious;
		return threat_state;
	}
	for (int d = 0; d < 4; d++)
	{
		int count = 1, block = 0;
		for (int j = 1; j <= 4; j++)
		{
			int nx = x + j * direction[d][0];
			int ny = y + j * direction[d][1];
			if (nx > BOARD_SIZE || ny > BOARD_SIZE || checkchess(nx, ny) == currentplayercolor + 1)
			{
				block++;
				break;
			}
			else if (checkchess(nx, ny) == humancolor + 1)
			{
				count++;
			}
			else
				break;
		}
		for (int k = 1; k <= 4; k++)
		{
			int nx = x - k * direction[d][0];
			int ny = y - k * direction[d][1];
			if (nx < 0 || ny < 0 || checkchess(nx, ny) == currentplayercolor + 1)
			{
				block++;
				break;
			}
			else if (checkchess(nx, ny) == humancolor + 1)
			{
				count++;
			}
			else
				break;

		}
		if (count >= 4)
		{
			switch (block)
			{
			case 0: threat_temp = Threat_stronger;
				break;// _xxx( )_
			case 1: threat_temp = Threat_middle;
				break;// |xxx( )_
			case 2: threat_temp = Threat_weaker;
				break;// 
			}
		}
		else
		{
			threat_temp = Threat_weak;
		}
		if (threat_state < threat_temp)
		{
			threat_state = threat_temp;
		}
	}
	if (threat_state >= Threat_middle)
	{
		return threat_state;
	}
	return threat_state;
}

int maxscore(int testx, int testy)
{
	if (chesscount == 1)return 0;
	int temp = 0;

	for (int d = 0; d < 4; d++)
	{
		int count = 1;
		for (int j = 1; j <= 4; j++)
		{
			int x = testx + j * direction[d][0];
			int y = testy + j * direction[d][1];
			if (x <= BOARD_SIZE && y <= BOARD_SIZE && checkchess(x, y) == currentplayercolor + 1)
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
			int x = testx - k * direction[d][0];
			int y = testy - k * direction[d][1];
			if (x >= 0 && y >= 0 && checkchess(x, y) == currentplayercolor + 1)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		temp += (int)(pow(10, count));
	}
	return temp;
}
int strategy2()
{
	int score = -1;/*真正的问题是score < maxscore(x,
	y)在只有一个棋子的时候永远会不成立,因为score=0,
	而且maxscore永远等于0导致currentx一直没有更换,而此时我的
	currentx和我下的棋子的坐标是一致的就导致了结果返回来了,但是又
	由于该位置最开始是被占用的,所以添加失败,但是在case0里面由于strategy仍然返回了
	所以会继续走完case0,之后又切换到了human了,所以改成-1,让他有路可走,或者条件改成
	<=maxscore,但等于情况占多数,不断地写入有点浪费*/
	int center = (BOARD_SIZE) / 2;
	for (int i = 0; i <= BOARD_SIZE; i++)
	{
		int x = (center + i) % (BOARD_SIZE + 1);
		for (int j = 0; j <= BOARD_SIZE; j++)
		{
			int y = (center + j) % (BOARD_SIZE + 1);
			if (checkchess(x, y) == 0)
			{
				if (score < maxscore(x, y))
				{
					score = maxscore(x, y);
					currentx = x;
					currenty = y;
				}
			}
		}
	}

	return 0;
}
int strategy3()
{

	int score = -1;
	int center = (BOARD_SIZE) / 2;
	int threat_state = Threat_weaker;
	int humancolor = 1 - currentplayercolor;

	for (int i = 0; i <= BOARD_SIZE; i++)//check myself whether able to win.
	{
		int x = (center + i) % (BOARD_SIZE + 1);
		for (int j = 0; j <= BOARD_SIZE; j++)
		{
			int y = (center + j) % (BOARD_SIZE + 1);
			y = (center + y) % (BOARD_SIZE + 1);
			if (checkchess(x, y) == 0)
			{
				if (appearwin(x, y, currentplayercolor))
				{
					currentx = x;
					currenty = y;
					return 0;
				}
			}
		}
	}


	for (int i = 0; i <= BOARD_SIZE; i++)//check human
	{
		int x = (center + i) % (BOARD_SIZE + 1);
		for (int j = 0; j <= BOARD_SIZE; j++)
		{
			int y = (center + j) % (BOARD_SIZE + 1);
			if (checkchess(x, y) == 0)
			{
				int T = threat_degree(x, y, humancolor);
				if (threat_state < T)
				{
					threat_state = T;
					currentx = x;
					currenty = y;

				}
			}
		}
	}
	if (threat_state >= Threat_middle)
	{
		return threat_state;
	}


	for (int i = 0; i <= BOARD_SIZE; i++)
	{
		int x = (center + i) % (BOARD_SIZE + 1);
		for (int j = 0; j <= BOARD_SIZE; j++)
		{
			int y = (center + j) % (BOARD_SIZE + 1);
			if (checkchess(x, y) == 0)
			{
				if (score < maxscore(x, y))
				{
					score = maxscore(x, y);
					currentx = x;
					currenty = y;
				}
			}
		}
	}

	return 0;
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
		currentplayercolor = 1 - currentplayercolor;
		Player = 2 - mode - Player;
		discarton(undox, undoy);
	}
}

// take forward
void redo()
{
	if (backcount > 0 && towardtime > 0)
	{
		drawsinglechess(chessboard[chesscount].x, chessboard[chesscount].y, chessboard[chesscount].COLOR);
		chesscount++;
		backcount--;
		towardtime--;
		currentplayercolor = 1 - currentplayercolor;
	}
}

void restartgame()
{
	gameover = false;
	chesscount = 0;
	backcount = 0;
	currentx = 9;
	currenty = 9;
	Player = prioritymode;
	system("cls");
}

void Peekspecific(Keymessage* Key)
{
	Key->esc = false;
	Key->space = false;
	Key->shift = false;
	printf("\033[31m");
	while (peekmessage(&msg))
	{
		if (msg.message == WM_KEYDOWN)
		{
			if (msg.vkcode == VK_ESCAPE)
			{
				Key->esc = true;
				fprintf(stdout, "press %s(Ascll %d)\n", "ESC", VK_ESCAPE);
			}
			else if (msg.vkcode == VK_SPACE)
			{
				Key->space = true;
				fprintf(stdout, "press %s(Ascll %d)\n", "SPACE", VK_SPACE);
			}
			else if (msg.vkcode == VK_SHIFT)
			{
				Key->shift = true;
				fprintf(stdout, "press %s(Ascll %d)\n", "SHIFT", VK_SHIFT);
			}
			else {
				Key->elsekey = msg.vkcode;
				fprintf(stdout, "press %c(Ascll %d)\n", Key->elsekey, int(Key->elsekey));
			}
		}
	}
	printf("\033[0m");
}
int main()
{
	srand((unsigned int)time(NULL));
Start:
	ExMessage msg = { 0 };
	fprintf(stdout, "\033[31;43m please enjoy the game!\033[0m\n");
	fprintf(stdout, "please use arrow keys to move the cursor\n");
	fprintf(stdout, "press space to place chess\n");
	fprintf(stdout, "press \033[36mctrl+z/Z\033[0m to take back chess\n");
	fprintf(stdout, "press \033[36mctrl+y/Y\033[0m to take forward chess\n");
	fprintf(stdout, "press \033[36mR/r\033[0m to restart the game\n");
	fprintf(stdout, "press \033[36mESC\033[0m to exit the game\n");
	fprintf(stdout, "please chose game mode((\033[32mhuman vs human\033[0m )or(\033[32mhuman vs Computer\033[0m)or(\033[32mcomputer vs computer\033[0m),0 is former,1 is later,2 is last):\n");
	if (scanf("%d", &mode) != 1 || (mode != 0 && mode != 1 && mode != 2))
	{
		fprintf(stderr, "invalid input,default human vs computer mode\n\n");
		while (getchar() != '\n');
		mode = 1;
	}
	if (!mode)
	{
		fprintf(stdout, "you chose \033[32mhuman vs human mode\033[0m\n");
	}
	else if (mode == 1)
	{
		fprintf(stdout, "you chose \033[32mhuman vs Computer mode\033[0m\n");
		fprintf(stdout, "\nplease chose computer startegy(1,2,3):\n\n");
		fprintf(stdout, "\033[34mstrategy1,intellgence degree:*\nstrategy2,intellgence degree:**\nstrategy3,intellgence degree:***\033[0m\n");
		if (scanf("%d", &strategy) != 1 || strategy < 1 || strategy>3)
		{
			fprintf(stderr, "invalid input,default startegy 2\n");
			while (getchar() != '\n');
			strategy = 2;
		}
		else
		{

			fprintf(stdout, "Computer chose startegy %d\n", strategy);
			while (getchar() != '\n');
		}
		fprintf(stdout, "\nplease chose priority mode(1 is you first,else 0 is computer first):\n");
		if (scanf("%d", &prioritymode) != 1 || (prioritymode != 0 && prioritymode != 1))
		{
			fprintf(stderr, "invalid input,default you first\n");
			while (getchar() != '\n');
			prioritymode = 1;
		}
		else
		{
			fprintf(stdout, "you chose %s first\n", prioritymode ? "you" : "computer");
		}
		Player = prioritymode;
		switch (strategy)
		{
		case 1:Strategy = strategy1; break;
		case 2:Strategy = strategy2; break;
		case 3:Strategy = strategy3; break;
		}
	}
	else
	{
		fprintf(stdout, "you chose \033[32mComputer vs Computer mode\033[0m\n");
		for (int i = 1; i < 3; i++)
		{
			fprintf(stdout, "\nplease chose computer%d startegy(1,2,3):\n", i);
			fprintf(stdout, "\033[34mstrategy1,intellgence degree:*\nstrategy2,intellgence degree:**\nstrategy3,intellgence degree:***\033[0m\n");
			if (scanf("%d", &strategy) != 1 || strategy < 1 || strategy>3)
			{
				fprintf(stderr, "invalid input,default startegy 3\n");
				while (getchar() != '\n');
				strategy = 3;
			}
			else
			{

				fprintf(stdout, "Computer%d chose startegy %d\n", i, strategy);
				while (getchar() != '\n');
			}
			if (i == 1)
			{
				switch (strategy)
				{
				case 1:Strategy1 = strategy1; break;
				case 2:Strategy1 = strategy2; break;
				case 3:Strategy1 = strategy3; break;
				}
			}
			else
			{
				switch (strategy)
				{
				case 1:Strategy2 = strategy1; break;
				case 2:Strategy2 = strategy2; break;
				case 3:Strategy2 = strategy3; break;
				}
			}
		}
		Player = 0;
		exitmode2 = false;// restart mode2 need set exitmode2,otherwise will suspend on if (exitmode2 == true) break,then agian into case 0,leads to no chess free,because 
		// strategy no implecoment,then turns to leads to no (x,y)generate.
	}


	fprintf(stdout, "\033[31;43mgame start,have a good fun!\033[0m\n");
	while (getchar() != '\n');
	getchar();

	if (beginover)
	{
		initgraph(1010, 750, EX_SHOWCONSOLE);
		setbkcolor(RGB(240, 240, 240));
		cleardevice();
		beginover = false;
	}
	bool running = true;
	DWORD lastspacetime = 0;
	DWORD lastrtime = 0;
	TCHAR WINMESSAGE[100];
	while (running)
	{
		bool freechess = false;
		switch (Player)
		{
		case 1:

			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode == VK_ESCAPE)
				{
					restartgame();
					running = false;
					break;
				}
				short ctrlstate = GetKeyState(VK_CONTROL);
				bool ctrlpressed = (ctrlstate & 0x8000) == 0 ? false : true;
				switch (msg.vkcode)
				{
				case 'z':
				case 'Z':if (ctrlpressed && !gameover) {
					if (mode == 1 && chesscount >= 2 && backcount < MAXCHESS)
					{
						undo();
						backcount--;
						towardtime--;
						undo();
					}
					else if (mode == 0)
						undo();
					break;

				}
						break;
				case 'y':
				case 'Y':if (ctrlpressed && !gameover) {
					if (mode == 1 && towardtime > 0)
					{
						redo();
						backcount++;
						towardtime++;
						redo();
						freechess = true;
					}
					else if (mode == 0)
					{
						redo();
						freechess = true;
					}
					break;
				}
						break;
				case 'w':
				case 'W':
				case VK_UP:
					if (currenty > 0 && !gameover)currenty--; break;
				case 's':
				case 'S':
				case VK_DOWN:
					if (currenty < BOARD_SIZE && !gameover)currenty++; break;
				case 'a':
				case 'A':
				case VK_LEFT:
					if (currentx > 0 && !gameover)currentx--; break;
				case 'd':
				case 'D':
				case VK_RIGHT:
					if (currentx < BOARD_SIZE && !gameover)currentx++; break;
				case 'r':
				case 'R':
					restartgame();
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
							printf("%s(%s) at (%d,%d)\n", "Humans", currentplayercolor == 0 ? "black" : "white", currentx, currenty);
							drawsinglechess(currentx, currenty, currentplayercolor);

							if (appearwin(currentx, currenty, currentplayercolor))
							{
								_stprintf_s(WINMESSAGE, _T("WIN:%s(%s)"), _T("Humans"), currentplayercolor == 0 ? _T("black") : _T("white"));
								gameover = true;
								break;
							}
							Player = 2 - Player - mode;
							currentplayercolor = 1 - currentplayercolor;
						}
					}
					lastspacetime = GetTickCount();
					break;
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
				outtextxy(300, 0, WINMESSAGE);
				settextcolor(BLUE);
				outtextxy(300, 40, _T("Press R to Restart!"));
			}
			EndBatchDraw();
			getmessage(&msg, EX_KEY);// It eliminates the high-speed empty loops while caused
			// by using peekmessage(in non-blocking mode) when there is 
			// no message input,which in turn leads to high-speed CPU idling.
			// Additionally,it can load graphics at very start and normal
			// key response functioning 
			break;

		case 0:
			BeginBatchDraw();
			cleardevice();
			drawchessboard();
			drawallchess();
			drawcursor(currentx, currenty);
			Gameinfo();
			EndBatchDraw();

			/*
			prioritymode = 1; if the game has restart(no mode change, only press r),
			 this action can make next time game 's priority brcome human. or use
			 prioritymode=1-prioritymode(only once) to alterate(take turns to exchange) prioritymode
			*/

			//only just generate currentx,currenty.
			if (mode == 1)Strategy();
			if (mode == 2)
			{
				while (GetTickCount() - lastkeytime < 1000)//have time give to make chioce,
					//when the distance of time more than set value.incomplment strategy.
				{
					havetarkey = false;
					Peekspecific(&Key);
					if (Key.esc)
					{
						restartgame();
						running = false;
						havetarkey = true;
						exitmode2 = true;// actually ,this change is not necessary,because next senstence(break) can break switch ,
						//then running is false,can end mode2.
						break;// break switch and end while(running)
					}
					if (Key.space)
					{
						settextcolor(RED);
						settextstyle(38, 0, _T("Arial"));
						outtextxy(350, 0, _T("Already Suspend!"));
						while (true)
						{
							//getmessage(&msg);这里是个大错误,我想等待我按键然后检测是否有消息,我后面又用
							//peekspecific,但此时消息已经取出来了,所以key->space等我按下的键都是false,进入死循环了
							//或者使用peek和get不能混在一起用.还可以这样getmessage 判断msg.vkcode也可以,这样更好还可以避免cpu空转
							Peekspecific(&Key);
							if (Key.esc)
							{
								restartgame();
								running = false;
								havetarkey = true;
								exitmode2 = true;// this change is necessary,because break only end the nearst switch or while.
								//break while(msg.vk.....),then this execution still incomplement the remaining code,so we need
								// define avariable (exitmode2) to help exit.
								break;
							}
							if (Key.shift)
							{
								Player = 1;
								mode = 1;
								havetarkey = true;
								mode = 1;
								switch (ComputerPlayer)// new computer take over current computer player strategy; 
								{
								case 1:Strategy = Strategy1; break;
								case 2:Strategy = Strategy2; break;
								}
								exitmode2 = true;
								break;
							}
							if (Key.space)
							{
								havetarkey = true;
								break;// press SPACE again,on brhalf of continue game in mode2.
							}
						}
						// msg.vkcode = VK_SPACE;  getmessage() will flush msg.message,if the message  is not SPACE or ESCAPE or shift,which from getmessage(no break while loops) ,it represent 
						// the press is invalid, we must reset vkcode and into loops again until we input correct.
						/*OR way2 (not
						if (msg.vkcode==VK_SPACE)
						{
							while(true)
							{
								getmessage();
								if (msg.message == WM_KEYDOWN)
									{
										if (msg.vkcode == VK_ESCAPE){...........}
										if (msg.vkcode == VK_SPACE) {...........}
										if (msg.vkcode == VK_SHIFT) {...........}
									}
							}
						}
						*/
					}
					if (havetarkey)break;//break while(.....<2000)
				}
				lastkeytime = GetTickCount();
				if (exitmode2 == true) break;
				if (mode == 2 && chesscount < 2)// avoid mode =2,only one chesss situation
				{
					do {
						currentx = rand() % 5 + 7;
						currenty = rand() % 5 + 7;// currentx and currenty all belong to 7~11}
					} while (checkchess(currentx, currenty));
				}
				else
				{
					switch (ComputerPlayer)
					{
					case 1:Strategy1(); ComputerPlayer = 3 - ComputerPlayer; break;
					case 2:Strategy2(); ComputerPlayer = 3 - ComputerPlayer; break;
					}
				}
			}
			addchess(currentx, currenty);//add the x and y of computer.
			int sleeptime = rand() % 150;
			Sleep(sleeptime);
			drawsinglechess(currentx, currenty, currentplayercolor);
			printf("%s(%s) at (%d,%d)\n", "Computer", currentplayercolor == 0 ? "black" : "white", currentx, currenty);

			// human vs computer ,only decrese once for backcount.
			towardtime = 0;
			Player = 2 - Player - mode;

			if (appearwin(currentx, currenty, currentplayercolor))
			{
				_stprintf_s(WINMESSAGE, _T("WIN:%s(%s)"), _T("Computer"), currentplayercolor == 0 ? _T("black") : _T("white"));
				gameover = true;
				if (mode == 1) break;
			}
			currentplayercolor = 1 - currentplayercolor;

			if (gameover)
			{
				settextcolor(RED);
				settextstyle(35, 0, _T("Arial"));
				outtextxy(300, 0, WINMESSAGE);
				settextcolor(BLUE);
				outtextxy(300, 40, _T("Press R to Restart!"));
				outtextxy(300, 80, _T("please press exit or r:"));
				if (mode == 2)
				{
					Player = 1;//turn to humans to make choice ,continue of exit?
				}
			}
		}


	}
	int ch;
	char readline[5];
	fprintf(stdout, "do you want try again(y/n)?\n");
	if (!fgets(readline, sizeof(readline), stdin))
	{
		fprintf(stdout, "Gameover,Bye!");
		closegraph();
	}
	else if (readline[0] == 'y' || readline[0] == 'Y')
	{
		system("cls");
		goto Start;
	}
	return 0;
}