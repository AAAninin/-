#include "stdafx.h"
#include "Other.h"

extern Global s;
Other::Other()
{
}


void  Other::recive()
{
	for (int i = 0; i < 22; i++)
	{
		for (int t = 0;t < 22;t++)
		{
			s.fin[i][t] = 0;
		}
	}
	for (int i = 0; i < 22; i++)
	{
		for (int t = 0; t < 22;t++)
		{
			if (s.a[i][t] == 1 || s.other[i][t] == 1)
			{
				s.fin[i][t] = 1;
			}
		}
	}
}

Other::~Other()
{
}

Other o;