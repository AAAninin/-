// 俄罗斯方块.cpp: 定义控制台应用程序的入口点。
//
#pragma comment(lib, "Ws2_32.lib")  
#include<winsock2.h>  
#include<process.h>  
#include<ws2tcpip.h>  

#include<windows.h>  
#include<windowsx.h>  
#include<tchar.h> 
#include "stdafx.h"
extern Global s;
extern Game g;
extern Other o;
extern Next n;
int i;
WNDCLASSEX winclass, winclass1;
WORD wVersionRequested;
TCHAR tempBuf[255];
WSADATA wsaData;
SOCKET sockConn, sockSrv, sockClient;
SOCKADDR_IN addrSrv;
int err;
char *_char;
WORD lEvent, lError;
bool isAccepted = false;
bool isConnected = false;
char *szpSendBuf = (char*)&s.fin[0][0];
hostent *pHost;
HINSTANCE hinstances;
HWND hwndchlidren;
HWND hwndtrue;
HWND hwndout;
HWND hwndip;
HWND hwnd1;
HWND editwnd;
TCHAR szText1[512];
HWND main;
void CALLBACK TimeProc(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime)//settiomout定时器的回调函数
{
	HWND hWnd = FindWindow(NULL, _T("俄罗斯方块"));
	if (s.dwTimerId == idEvent)
	{
		s.state = 5;
		InvalidateRgn(hWnd, NULL, FALSE);
	}

}
LRESULT CALLBACK winproc(HWND hwnd,
	UINT msg,
	WPARAM wparam,
	LPARAM lparam)//子窗口的回调函数
{
	HDC hdc;
	HDC hdcmem;
	PAINTSTRUCT ps;
	HBITMAP hbmp;
	BITMAP bmp;
	HWND hWnd = FindWindow(NULL, _T("俄罗斯方块"));
	HWND hwnd1 = FindWindowEx(hWnd, NULL, TEXT("static"), TEXT("等待连接"));
	switch (msg)
	{
	case WM_COMMAND:
	{

		switch (LOWORD(wparam))
		{
		case IDB_BUTTON_TRUE://建立socket链接

			GetDlgItemText(hwndchlidren, IDB_BUTTON_IP, (LPTSTR)szText1, 512);
			wVersionRequested = MAKEWORD(2, 2);
			err = WSAStartup(wVersionRequested, &wsaData);
			if (err != 0)
			{
				return 0;
			}
			if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
			{
				WSACleanup();
				return 0;
			}
			sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (SOCKET_ERROR == WSAAsyncSelect(sockClient, main,
				WM_CLIENT_SOCKET, FD_CONNECT | FD_READ))
			{
				MessageBox(main, TEXT("WSAAsyncSelect Error!"), TEXT("Server"), MB_OK);
				closesocket(sockClient);
				WSACleanup();
			}

			addrSrv.sin_addr.S_un.S_addr = inet_addr(szText1);
			addrSrv.sin_family = AF_INET;
			addrSrv.sin_port = htons(8000);

			i = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
			SendMessage(hwndchlidren, WM_CLOSE, wparam, lparam);
			break;
		case IDB_BUTTON_OUT:
			//MessageBox(hwndchlidren, TEXT("1111"), TEXT("Client"), MB_OK);
			SendMessage(hwndchlidren, WM_CLOSE, wparam, lparam);
			break;
		}
	case WM_CLIENT_SOCKET://自定义的网络消息  

		lEvent = WSAGETSELECTEVENT(lparam);
		lError = WSAGETSELECTERROR(lparam);

		switch (lEvent)
		{
		case FD_CONNECT:
		{
			if (lError)
			{
				MessageBox(hwnd, TEXT("Connect Timeout!"), TEXT("Client"), MB_OK);
			}
			else
			{
				isConnected = true;
				InvalidateRect(hwnd1, NULL, FALSE);
			}
		}
		break;

		case FD_READ:
		{
			if (lError)
			{
				MessageBox(hwnd, TEXT("Receive Error!"), TEXT("Client"), MB_OK);
			}

			memset(s.rev1, 0, sizeof(s.rev1));
			char *szpRevcBuf = (char*)&s.rev1[0][0];
			int re = recv(sockClient, szpRevcBuf, sizeof(int) * 484, 0);
			if (re > 0)
			{
				wsprintf(tempBuf, _T("已经连接"), szpRevcBuf);
				SetWindowText(hwnd1, tempBuf);
				g.Draw(hdc, hdcmem, ps, hbmp, bmp, hWnd);
			}

		}
		break;

		case FD_CLOSE:
		{
			closesocket(sockClient);
			isConnected = false;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;

		default:
			break;
		}
	}
	break;
	case WM_DESTROY://可以正常关闭窗口
	{
		//PostQuitMessage(0);
		return 0;
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//从消息通道里拿出消息进行处理
}


LRESULT CALLBACK WinProc(HWND hwnd,
	UINT msg,
	WPARAM wparam,
	LPARAM lparam)//主窗口的回调函数
{
	main = hwnd;
	HDC hdc;
	HDC hdcmem;
	PAINTSTRUCT ps;
	HBITMAP hbmp;
	BITMAP bmp;
	HWND hWnd = FindWindow(NULL, _T("俄罗斯方块"));
	HWND hwnd1 = FindWindowEx(hWnd, NULL, TEXT("static"), TEXT("等待连接"));

	switch (msg)
	{
	case WM_PAINT:
		if (s.qwe == 0)
		{

		}
		else
		{
			if (s.state == 1)
			{
				s.x++;
				if (s.x == 7)
				{
					s.x = 3;
				}
				else if (s.x == 3)
				{
					s.x = 1;
				}
				else if (s.x == 11)
				{
					s.x = 7;
				}
				else if (s.x == 1)
				{
					s.x = 0;
				}
				n.next(s.c);
				g.Create(s.x);
				//nextone(c);
			}
			else if (s.state == 2)
			{
				g.loop(3);
			}
			else if (s.state == 3)
			{
				g.loop(2);
			}
			else if (s.state == 4)
			{
				g.loop(1);
			}
			else if (s.state == 5)
			{
				g.loop(3);
			}
		}
		o.recive();
		if (s.connectstate == 1)
		{

			send(sockConn, szpSendBuf, sizeof(int) * 484, 0);
		}
		else
		{
			send(sockClient, szpSendBuf, sizeof(int) * 484, 0);
		}
		g.Draw(hdc, hdcmem, ps, hbmp, bmp, hWnd);
		break;
	case WM_KEYDOWN:
		switch (wparam)
		{
			
		case VK_UP:
			s.state = 1;
			
			InvalidateRect(hWnd, &s.rect, FALSE);
			break;
		case VK_DOWN:
			s.state = 2;
			InvalidateRect(hWnd, &s.rect, FALSE);
			break;
		case VK_LEFT:
			s.state = 3;
			InvalidateRect(hWnd, &s.rect, FALSE);
			break;
		case VK_RIGHT:
			s.state = 4;
			InvalidateRect(hWnd, &s.rect, FALSE);
			break;
		default:
			break;
		}
		return 0;
	case WM_COMMAND:
	{

		switch (LOWORD(wparam))
		{
		case IDM_OPT1:
			//创建主机
			//初始化socket

			s.connectstate = 1;
			wVersionRequested = MAKEWORD(2, 2);
			err = WSAStartup(wVersionRequested, &wsaData);
			if (err != 0)
			{
				return 0;
			}
			if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
			{
				WSACleanup();
				return 0;
			}
			sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (SOCKET_ERROR == WSAAsyncSelect(sockSrv, hwnd,
				WM_SERVER_SOCKET, FD_ACCEPT | FD_READ))
			{
				MessageBox(hwnd, TEXT("WSAAsyncSelect Error!"), TEXT("Server"), MB_OK);
				closesocket(sockSrv);
				WSACleanup();
			}
			addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
			addrSrv.sin_family = AF_INET;
			addrSrv.sin_port = htons(8000);
			bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
			listen(sockSrv, 5);
			char szHost[256];
			gethostname(szHost, 256);
			pHost = gethostbyname(szHost);
			in_addr addr;
			for (int i = 0;; i++)
			{
				char *p = pHost->h_addr_list[i];
				if (p == NULL)
					break;
				memcpy(&addr.S_un.S_addr, p, pHost->h_length);
				const char *slzp = inet_ntoa(addr);
				MessageBox(hWnd, slzp, TEXT("IP"), MB_OK);

			}

			break;
		case IDM_OPT2:
			//链接主机
			s.connectstate = 2;
			winclass1.cbSize = sizeof(WNDCLASSEX);
			winclass1.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
			winclass1.lpfnWndProc = winproc;
			winclass1.hInstance = hinstances;
			winclass1.cbClsExtra = 0;
			winclass1.cbWndExtra = 0;
			winclass1.hCursor = LoadCursor(NULL, IDC_ARROW);
			winclass1.hIcon = LoadIcon(NULL, IDC_APPSTARTING);

			winclass1.hIconSm = LoadIcon(hinstances, _T("IDI_MYICON"));
			winclass1.lpszMenuName = NULL;
			winclass1.hbrBackground = NULL;
			winclass1.lpszClassName = _T("WINCLASS");
			RegisterClassEx(&winclass1);
			hwndchlidren = CreateWindowEx(NULL,
				_T("WINCLASS"),
				_T("寻找主机"),
				WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD | WS_POPUP,
				500,
				300,
				300,
				200,
				hWnd,
				NULL,
				hinstances,
				NULL);
			hwndtrue = CreateWindow(TEXT("button"), TEXT("确定"), WS_CHILD | WS_VISIBLE, 80, 120, 40, 25, hwndchlidren, (HMENU)IDB_BUTTON_TRUE, hinstances, NULL);
			hwndout = CreateWindow(TEXT("button"), TEXT("退出"), WS_CHILD | WS_VISIBLE, 180, 120, 40, 25, hwndchlidren, (HMENU)IDB_BUTTON_OUT, hinstances, NULL);
			hwndip = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 90, 60, 110, 25, hwndchlidren, (HMENU)IDB_BUTTON_IP, hinstances, NULL);
			break;
		case IDB_BUTTON_CONNECT:
			if (s.qwe == 1)
			{
				s.dwTimerId = SetTimer(hWnd, 1, 900, TimeProc);
				SetFocus(hWnd);
			}
			break;
		case IDB_BUTTON_STOP:
			KillTimer(hWnd, 1);
			break;
		case IDB_BUTTON_START:
			if (s.qwe == 0)
			{
				g.ram(0);
				s.dwTimerId = SetTimer(hWnd, 1, 900, TimeProc);
				SetFocus(hWnd);
				s.qwe = 1;
			}
		}
		break;
	case WM_CLIENT_SOCKET://自定义的网络消息  

		lEvent = WSAGETSELECTEVENT(lparam);
		lError = WSAGETSELECTERROR(lparam);

		switch (lEvent)
		{
		case FD_CONNECT:
		{
			if (lError)
			{
				MessageBox(hwnd, TEXT("Connect Timeout!"), TEXT("Client"), MB_OK);
			}
			else
			{
				isConnected = true;
				InvalidateRect(hwnd1, NULL, FALSE);
			}
			//sockConn = accept(sockClient, NULL, NULL);
		}
		break;

		case FD_READ:
		{
			if (lError)
			{
				MessageBox(hwnd, TEXT("Receive Error!"), TEXT("Client"), MB_OK);
			}

			memset(s.rev1, 0, sizeof(s.rev1));
			char *szpRevcBuf = (char*)&s.rev1[0][0];
			int re = recv(sockClient, szpRevcBuf, sizeof(int) * 484, 0);
			if (re > 0)
			{
				wsprintf(tempBuf, _T("已经连接"), szpRevcBuf);
				SetWindowText(hwnd1, tempBuf);
				g.Draw(hdc, hdcmem, ps, hbmp, bmp, hWnd);
			}

		}
		break;

		case FD_CLOSE:
		{
			closesocket(sockClient);
			isConnected = false;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;

		default:
			break;
		}
	case WM_SERVER_SOCKET:
		lEvent = WSAGETSELECTEVENT(lparam);
		lError = WSAGETSELECTERROR(lparam);
		switch (lEvent)
		{
		case FD_ACCEPT:
		{
			if (lError)
			{
				MessageBox(hwnd, _T("Accept Error!"), _T("Server"), 0);
			}
			else
			{
				isAccepted = true;
			}
			sockConn = accept(sockSrv, NULL, NULL);
		}
		break;
		case FD_READ:
		{
			if (lError)
			{
				MessageBox(hwnd, _T("Read Error!"), _T("Server"), 0);
			}
			//char szpRevcBuf[20];
			//tempBuf = new TCHAR[MAX_LEN];
			memset(s.rev, 0, sizeof(s.rev));
			char *szpRevcBuf = (char*)&s.rev[0][0];
			int re = recv(sockConn, szpRevcBuf, sizeof(int) * 484, 0);
			if (re > 0)
			{
				wsprintf(tempBuf, _T("已经连接"), szpRevcBuf);
				SetWindowText(hwnd1, tempBuf);
				g.Draw(hdc, hdcmem, ps, hbmp, bmp, hWnd);
			}

		}
		break;
		case FD_CLOSE:
		{
			closesocket(sockSrv);
			closesocket(sockConn);
			isAccepted = false;
			InvalidateRect(hwnd1, NULL, FALSE);
		}
		break;

		default:
			break;
		}
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}



int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hprevinstance,
	LPSTR lpcmdline,
	int ncmdshow)//主函数
{
	s.rect.bottom = 725;
	s.rect.top = 0;
	s.rect.left = 0;
	s.rect.right = 600;
	MSG msg;
	createmenu();
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	winclass.lpfnWndProc = WinProc;
	winclass.hInstance = hinstance;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hIcon = LoadIcon(NULL, IDC_APPSTARTING);

	winclass.hIconSm = LoadIcon(hinstance, _T("IDI_MYICON"));
	winclass.lpszMenuName = NULL;
	winclass.hbrBackground = NULL;
	winclass.lpszClassName = _T("WINCLASS1");
	if (!RegisterClassEx(&winclass))
	{
		return 0;
	}
	hinstances = hinstance;
	hwnd1 = CreateWindowEx(NULL,
		_T("WINCLASS1"),
		_T("俄罗斯方块"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		300,
		100,
		725,
		625,
		NULL,
		s.hRoot,
		hinstance,
		NULL);
	
	HWND hstatic = CreateWindow(TEXT("static"), TEXT("分数 0"), WS_CHILD | WS_VISIBLE, 605, 0, 113, 50, hwnd1, (HMENU)2, hinstance, NULL);
	HWND hstatic1 = CreateWindow(TEXT("static"), TEXT(""), WS_CHILD | WS_VISIBLE, 600, 0, 5, 615, hwnd1, (HMENU)2, hinstance, NULL);
	HWND hstatic2 = CreateWindow(TEXT("static"), TEXT(""), WS_CHILD | WS_VISIBLE, 600, 500, 113, 150, hwnd1, (HMENU)2, hinstance, NULL);
	HWND hstatic3 = CreateWindow(TEXT("static"), TEXT("等待连接"), WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE, 600, 150, 113, 150, hwnd1, (HMENU)2, hinstance, NULL);
	HWND hwnd4 = CreateWindow(TEXT("button"), TEXT("暂停"), WS_CHILD | WS_VISIBLE, 605, 500, 113, 50, hwnd1, (HMENU)IDB_BUTTON_STOP, hinstance, NULL);
	HWND hwnd2 = CreateWindow(TEXT("button"), TEXT("开始游戏"), WS_CHILD | WS_VISIBLE, 605, 400, 113, 50, hwnd1, (HMENU)IDB_BUTTON_START, hinstance, NULL);
	HWND hwnd3 = CreateWindow(TEXT("button"), TEXT("继续"), WS_CHILD | WS_VISIBLE, 605, 450, 113, 50, hwnd1, (HMENU)IDB_BUTTON_CONNECT, hinstance, NULL);
	if (!hwnd1)
		return 0;
	ShowWindow(hwnd1, ncmdshow);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

