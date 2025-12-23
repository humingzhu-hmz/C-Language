//#include<stdio.h>
//#include<easyx.h>
//#include<time.h>
//#include<conio.h>
//#include<windows.h>
//ExMessage msg = { 0 };
//
//typedef struct ChessPiece 
//{
//	int x, y;
//	int color; // 0:白色, 1:黑色
//}chesspiece;
//
////记录棋子
//#define MAXCHESS 400
//chesspiece chessboard[MAXCHESS];
//int chessCount = 0;//qizi数
//
//int chesscheek(int x, int y)
//{
//	for (int i = 0; i < chessCount; i++)
//	{
//		if (chessboard[i].x == x && chessboard[i].y == y)
//		{
//			return chessboard[i].color + 1; // 返回1:白子，2:黑子
//		}
//	}
//	return 0; // 没有棋子
//}
//
//void drawAllChessPieces() 
//{
//	for (int i = 0; i < chessCount; i++) 
//	{
//		if (chessboard[i].color == 0) 
//		{ // 白色
//			setfillcolor(WHITE);
//			setlinecolor(BLACK);
//			fillcircle(chessboard[i].x, chessboard[i].y, 18);
//		}
//		else 
//		{ // 黑色
//			setfillcolor(BLACK);
//			setlinecolor(BLACK);
//			fillcircle(chessboard[i].x, chessboard[i].y, 18);
//		}
//	}
//}
//void addChessPiece(int x, int y, int color) 
//{
//	int existingChess = chesscheek(x, y);
//	if (existingChess > 0)
//	{
//		printf("该位置已有%s子，不能重复下子！\n", existingChess == 1 ? "白" : "黑");
//		return;
//	}
//	if (chessCount < MAXCHESS) 
//	{
//		chessboard[chessCount].x = x;
//		chessboard[chessCount].y = y;
//		chessboard[chessCount].color = color;
//		chessCount++;
//	}
//}
//
//
//
//void creatcirle(int x,int y,int r)
//{
//	//cleardevice();
//	setfillcolor(RGB(149, 219, 125));
//	solidcircle(x, y, r);
//	
//}
//void mouseMessage()
//{
//	//定义消息结构体变量
//	ExMessage msg = { 0 };
//	while (true)
//	{
//		//获取消息
//		if (peekmessage(&msg, EX_MOUSE))
//		{
//			switch (msg.message)
//			{
//			case WM_LBUTTONDOWN:printf("鼠标左键按下 pos(%d,%d)\n", msg.x, msg.y); break;
//			case WM_RBUTTONDOWN:printf("鼠标右键按下\n"); break;
//			case WM_MBUTTONDOWN:printf("鼠标中键按下\n"); break;
//			case WM_MOUSEWHEEL:printf("鼠标滚轮滚动 direct(%d)\n", msg.wheel); break;
//			case WM_LBUTTONDBLCLK:printf("鼠标左键双击\n"); break;
//				//case WM_MOUSEMOVE:printf("鼠标移动\n"); break;
//			}
//		}
//	}
//}
//int main()
//{
//	initgraph(800,800, EX_SHOWCONSOLE | 8);
//	cleardevice();
//	IMAGE img_nilu;
//	//setbkcolor(RGB(85, 177, 85));
//	/*putimage(0, 0, &img_nilu);
//	mouseMessage();*///测量棋盘间隔为40像素；天元是(400,400)
//	int x = 400, y = 400, r = 18, speed = 40;
//	DWORD lastSpaceTime = 0;
//	DWORD lastATime = 0;
//	while (true)
//	{
//		
//		BeginBatchDraw();
//		/*cleardevice();*///不知道为什么去掉这个函数反而更流畅
//		putimage(0, 0, &img_nilu);
//		//绘制棋子
//		drawAllChessPieces();
//		creatcirle(x, y, r);
//		EndBatchDraw();
//		Sleep(50);
//		if (peekmessage(&msg, EX_MOUSE | EX_KEY))
//		{
//			switch (msg.message)
//			{
//			case WM_KEYDOWN:
//				switch (msg.vkcode)
//				{
//				case VK_UP:y -= speed; break;
//				case VK_DOWN:y += speed; break;
//				case VK_LEFT:x -= speed; break;
//				case VK_RIGHT:x += speed; break;
//				case VK_SPACE:if (GetTickCount() - lastSpaceTime > 200) 
//				{
//					addChessPiece(x, y, 0); // 白子
//					lastSpaceTime = GetTickCount();
//					printf("白子下在: (%d, %d)\n", x, y);
//				} break;
//				case 'A':if (GetTickCount() - lastATime > 200) 
//				{
//					addChessPiece(x, y, 1); // 黑子
//					lastATime = GetTickCount();
//					printf("黑子下在: (%d, %d)\n", x, y);
//				} break;
//				}
//				break;
//				
//			case WM_KEYUP:
//				switch (msg.vkcode)
//				{
//				case VK_UP:; break;
//				case VK_DOWN:; break;
//				case VK_LEFT:; break;
//				case VK_RIGHT:; break;
//				case VK_SPACE:; break;
//				case 'A':; break;
//				}
//				break;
//				break;
//			}
//		}
//		msg.message = 0;
//	}
//	closegraph();
//	return 0;
//}