#pragma once

struct Location
{
	void Add( Location& val )
	{
		x += val.x;
		y += val.y;
	}
	int x;
	int y;
};
