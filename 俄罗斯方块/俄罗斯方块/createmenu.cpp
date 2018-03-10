#include "stdafx.h"
#include "createmenu.h"
extern   Global s;

createmenu::createmenu()
{
	s.hRoot = CreateMenu();
	HMENU pop1 = CreatePopupMenu();
	AppendMenu(s.hRoot,
		MF_POPUP,
		(UINT_PTR)pop1,
		"操作");
	// 一种方法是使用AppendMenu函数  
	AppendMenu(pop1,
		MF_STRING,
		IDM_OPT1,
		"创建主机");
	AppendMenu(pop1,
		MF_STRING,
		IDM_OPT2,
		"链接主机");
}


createmenu::~createmenu()
{
}
