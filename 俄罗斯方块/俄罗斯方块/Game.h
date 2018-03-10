#pragma once
class Game
{
public:
	Game();
	void Draw(HDC &hDC, HDC &hdcmem, PAINTSTRUCT &Ps, HBITMAP &hbmp, BITMAP &bmp, HWND &hWnd);
	void Clear();
	void Create(int x);
	int decide(int o);
	void Over();
	void ram(int o);
	void loop(int t);
	~Game();
	int cit;
};

