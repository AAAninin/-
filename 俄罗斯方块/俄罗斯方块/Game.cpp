#include "stdafx.h"
#include "Game.h"
extern Global s;
//extern Other o;
extern Next n;
Game::Game()
{
}

void Game::Draw(HDC &hDC, HDC &hdcmem, PAINTSTRUCT &Ps, HBITMAP &hbmp, BITMAP &bmp, HWND &hWnd)
{
	hDC = BeginPaint(hWnd, &Ps);
	HDC hdcBuffer = CreateCompatibleDC(hDC);//用于缓冲的内存DC  

	hDC = GetDC(hWnd);
	HBITMAP cptBmp = CreateCompatibleBitmap(hDC, 1000, 1000);
	ReleaseDC(hWnd, hDC);
	SelectObject(hdcBuffer, cptBmp);
	HDC hdcBmp = CreateCompatibleDC(hDC);//用于贴位图的内存DC 
	cit = 30;
	hbmp = (HBITMAP)LoadImage(NULL, "myResLib\\01.bmp", IMAGE_BITMAP, cit, cit, LR_LOADFROMFILE);
	GetObject(hbmp, sizeof(bmp), &bmp);
	SelectObject(hdcBmp, hbmp);
	for (int i = 0; i < 22; i++)
	{
		for (int p = 0; p < 22; p++)
		{
			if (s.map[i][p] == 1 || s.other[i][p] == 1)
			{
				TransparentBlt(hdcBuffer, (i - 1) * 30, p * 30, bmp.bmWidth, bmp.bmHeight, hdcBmp, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(0, 0, 0));
			}
		}
	}
	DeleteObject(hbmp);
	cit = 20;
	hbmp = (HBITMAP)LoadImage(NULL, "myResLib\\01.bmp", IMAGE_BITMAP, cit, cit, LR_LOADFROMFILE);
	GetObject(hbmp, sizeof(bmp), &bmp);
	SelectObject(hdcBmp, hbmp);
	for (int i = 0; i < 3; i++)
	{
		for (int p = 0; p < 3;p++)
		{
			if (s.next[i][p] == 1)
			{
				TransparentBlt(hdcBuffer, i * 20 + 615, p * 20 + 70, bmp.bmWidth, bmp.bmHeight, hdcBmp, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));
			}
		}
	}

	DeleteObject(hbmp);
	cit = 5;
	hbmp = (HBITMAP)LoadImage(NULL, "myResLib\\01.bmp", IMAGE_BITMAP, cit, cit, LR_LOADFROMFILE);
	GetObject(hbmp, sizeof(bmp), &bmp);
	SelectObject(hdcBmp, hbmp);
	for (int i = 0; i < 22; i++)
	{
		for (int p = 0; p < 22;p++)
		{
			if (s.rev[i][p] == 1)
			{
				TransparentBlt(hdcBuffer, i * 5 + 615, p * 5 + 300, bmp.bmWidth, bmp.bmHeight, hdcBmp, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));
			}
		}
	}
	BitBlt(hDC, 0, 0, 1000, 1000, hdcBuffer, 0, 0, SRCCOPY);
	DeleteObject(hbmp);
	DeleteDC(hdcBmp);
	DeleteDC(hdcBuffer);
	DeleteObject(cptBmp);
	EndPaint(hWnd, &Ps);
}



void Game::Clear()
{
	HWND Hwnd = FindWindow(NULL, _T("俄罗斯方块"));
	HWND hwnd = FindWindowEx(Hwnd, NULL, TEXT("static"), NULL);
	int together = 0;
	for (int i = 0; i < 22; i++)
	{
		for (int t = 0; t < 22; t++)
		{
			if (s.other[t][i] == 1)
			{
				together++;
				if (together == 20)
				{
					s.soce = s.soce + 10;
					wsprintf(s.szTextBuf, TEXT("分数为：%d"), s.soce);
					SetWindowText(hwnd, s.szTextBuf);

					for (int d = i; d > 0; d--)
					{
						for (int e = 0; e < 22; e++)
						{
							s.other[e][d] = s.other[e][d - 1];
						}
					}
				}
			}
		}
		together = 0;
	}
}

void Game::Create(int x)
{
	for (int i = 0; i < 22; i++)
	{
		for (int t = 0; t < 22;t++)
		{
			s.a[i][t] = 0;
		}
	}
	int t = 1;
	switch (x)
	{
	case 0:
		s.a[s.n + 0][s.y + 0] = t;
		s.a[s.n + 1][s.y + 0] = t;
		s.a[s.n + 0][s.y + 1] = t;
		s.a[s.n + 1][s.y + 1] = t;
		break;

	case 1:
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n][s.y] = t;
		s.a[s.n + 1][s.y] = t;
		s.a[s.n + 2][s.y + 1] = t;
		break;
	case 2:
		s.a[s.n + 2][s.y] = t;
		s.a[s.n + 2][s.y + 1] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 1][s.y + 2] = t;
		break;
	case 3:
		s.a[s.n][s.y] = t;
		s.a[s.n][s.y + 1] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 2][s.y + 1] = t;
		break;
	case 4:
		s.a[s.n + 1][s.y + 2] = t;
		s.a[s.n + 1][s.y + 0] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 2][s.y + 0] = t;
		break;
	case 5:
		s.a[s.n + 2][s.y + 2] = t;
		s.a[s.n + 2][s.y + 1] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 0][s.y + 1] = t;
		break;
	case 6:
		s.a[s.n + 0][s.y + 2] = t;
		s.a[s.n + 1][s.y + 0] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 1][s.y + 2] = t;
		break;
	case 7:
		s.a[s.n + 1][s.y + 0] = t;
		s.a[s.n + 0][s.y + 1] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 2][s.y + 1] = t;
		break;
	case 8:
		s.a[s.n + 1][s.y + 0] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 2][s.y + 1] = t;
		s.a[s.n + 1][s.y + 2] = t;
		break;
	case 9:
		s.a[s.n + 0][s.y + 1] = t;
		s.a[s.n + 2][s.y + 1] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 1][s.y + 2] = t;
		break;
	case 10:
		s.a[s.n + 0][s.y + 1] = t;
		s.a[s.n + 1][s.y + 0] = t;
		s.a[s.n + 1][s.y + 1] = t;
		s.a[s.n + 1][s.y + 2] = t;
		break;
	case 11:
		s.a[s.n + 0][s.y + 0] = t;
		s.a[s.n + 1][s.y + 0] = t;
		s.a[s.n + 0][s.y + 1] = t;
		s.a[s.n + 1][s.y + 1] = t;
		break;
	default:
		break;
	}
	for (int i = 0; i < 22; i++)
	{
		for (int f = 0; f < 22; f++)
		{
			s.map[i][f] = s.a[i][f];
		}
	}
}

int Game::decide(int o)
{
	if (o == 1)
	{
		for (int i = s.n; i < s.n + 4; i++)
		{
			for (int t = s.y; t < s.y + 4; t++)
			{
				if ((s.n == 1 && s.a[s.n][t] == 1) || (s.a[i][t] == 1 && s.other[i - 1][t] == 1) || (s.n - 1 < 0))
					return 0;
			}
		}
	}
	else if (o == 2)
	{
		for (int i = s.n; i < s.n + 4; i++)
		{
			for (int t = s.y; t < s.y + 4; t++)
			{
				if ((s.a[i][t] == 1 && s.other[i + 1][t] == 1) || (s.a[19][t] == 1 && s.a[20][t] == 1) || (s.n > 21))
					return 0;
			}
		}
	}
	else if (o == 3)
	{
		for (int i = s.n; i < s.n + 4; i++) {
			if ((s.y >= 16 && s.other[i][s.y + 3] == 0 && s.a[i][s.y + 2] == 1) || (s.a[i][s.y + 2] == 1 && s.other[i][s.y + 3] == 1) || (s.a[i][s.y + 1] == 1 && s.other[i][s.y + 2] == 1) || (s.y >= 17))
				return 0;
		}
	}
}


 void Game::Over()
{
	s.qwe = 0;
	HWND Hwnd = FindWindow(NULL, _T("俄罗斯方块"));

	HWND hwnd = FindWindowEx(Hwnd, NULL, TEXT("static"), NULL);
	s.state = 0;
	KillTimer(Hwnd, 1);
	s.soce = 0;

	wsprintf(s.szTextBuf, TEXT("分数为：%d"), s.soce);
	SetWindowText(hwnd, s.szTextBuf);
	MessageBox(Hwnd, TEXT("GAME OVER!!"), TEXT("OVER"), MB_OK);
	InvalidateRgn(Hwnd, NULL, true);
	for (int i = 0; i < 22; i++)
	{
		for (int t = 0; t < 22;t++)
		{
			s.a[i][t] = 0;
			s.map[i][t] = 0;
			s.other[i][t] = 0;
		}
	}
}


 void Game::ram(int o)
 {
	 srand((unsigned)time(NULL)); //用时间做种，每次产生随机数不一样
	 if (o == 0)
	 {
		 s.x = rand() % 11; //产生0-10的随机数
		 s.c = rand() % 11;
	 }
	 else
	 {
		 s.x = s.c;
		 s.c = rand() % 11;
	 }
 }

 void Game::loop(int t)
 {
	 if (t == 1)
	 {
		 if (decide(2) != 0)
		 {
			 s.n++;
			 Create(s.x);
		 }
	 }
	 else if (t == 2)
	 {
		 if (decide(1) != 0)
		 {
			 s.n--;
			 Create(s.x);
		 }
	 }
	 else if (t == 3)
	 {
		 if (decide(3) != 0)
		 {
			 s.y++;
			 Create(s.x);
			 if (s.nextone == 0)
			 {
				 n.next(s.c);
				 s.nextone = 1;
			 }
		 }
		 else
		 {
			 for (int i = 0; i < 22; i++)
			 {
				 for (int t = 0; t < 22;t++)
				 {
					 if (s.a[i][t] == 1)
					 {
						 s.other[i][t] = 1;
					 }
				 }
			 }
			 Clear();
			 s.n = 5;
			 s.y = 0;
			 ram(1);
			 Create(s.x);
			 n.next(s.c);
			 if (decide(3) == 0)
			 {
				 Over();
			 }
		 }
	 }
 }

Game::~Game()
{
}
Game g;