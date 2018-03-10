#include "stdafx.h"
#include "Next.h"
extern Global s;

Next::Next()
{
}

void Next::next(int p)
{
	for (int i = 0; i < 22; i++)
	{
		for (int t = 0; t < 22;t++)
		{
			s.next[i][t] = 0;
		}
	}
	int t = 1;
	switch (p)
	{
	case 0:
		s.next[0][0] = t;
		s.next[1][0] = t;
		s.next[0][1] = t;
		s.next[1][1] = t;
		break;

	case 1:
		s.next[1][1] = t;
		s.next[0][0] = t;
		s.next[1][0] = t;
		s.next[2][1] = t;
		break;
	case 2:
		s.next[2][0] = t;
		s.next[2][1] = t;
		s.next[1][1] = t;
		s.next[1][2] = t;
		break;
	case 3:
		s.next[0][0] = t;
		s.next[0][0 + 1] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 2][0 + 1] = t;
		break;
	case 4:
		s.next[0 + 1][0 + 2] = t;
		s.next[0 + 1][0 + 0] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 2][0 + 0] = t;
		break;
	case 5:
		s.next[0 + 2][0 + 2] = t;
		s.next[0 + 2][0 + 1] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 0][0 + 1] = t;
		break;
	case 6:
		s.next[0 + 0][0 + 2] = t;
		s.next[0 + 1][0 + 0] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 1][0 + 2] = t;
		break;
	case 7:
		s.next[0 + 1][0 + 0] = t;
		s.next[0 + 0][0 + 1] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 2][0 + 1] = t;
		break;
	case 8:
		s.next[0 + 1][0 + 0] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 2][0 + 1] = t;
		s.next[0 + 1][0 + 2] = t;
		break;
	case 9:
		s.next[0 + 0][0 + 1] = t;
		s.next[0 + 2][0 + 1] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 1][0 + 2] = t;
		break;
	case 10:
		s.next[0 + 0][0 + 1] = t;
		s.next[0 + 1][0 + 0] = t;
		s.next[0 + 1][0 + 1] = t;
		s.next[0 + 1][0 + 2] = t;
		break;
	case 11:
		s.next[0 + 0][0 + 0] = t;
		s.next[0 + 1][0 + 0] = t;
		s.next[0 + 0][0 + 1] = t;
		s.next[0 + 1][0 + 1] = t;
		break;
	default:
		break;
	}
}


Next::~Next()
{
}


Next n;