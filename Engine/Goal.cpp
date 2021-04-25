#include "Goal.h"

Goal::Goal(Location & in_loc)
{
	loc = in_loc;
}

void Goal::Draw(Board & brd)
{
	brd.DrawCell(loc, Colors::Red);
}
