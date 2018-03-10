#pragma once
class Global
{
public:
	Global();
	~Global();
public:
	DWORD dwTimerId = 0;
	int a[22][22] = { 0 };//方块形状数组
	int next[3][3] = { 0 };//下一个方块
	int map[22][22] = { 0 };
	int other[22][22] = { 0 };
	int x;//方块的形状
	int c;
	int soce = 0;//分数
	int f = 17;
	TCHAR szTextBuf[20]; //static 控件文本（缓冲区）
	int n = 5;
	int y = 0;
	int state;//判断是摁上下左右那个键
	int qwe = 0;//开始游戏键的好使和不好使
	int nextone = 0;
	int rev1[22][22];
	int fin[22][22];
	HMENU hRoot;
	int connectstate;
	int rev[22][22];
	RECT rect;
	int test = 0;
};

