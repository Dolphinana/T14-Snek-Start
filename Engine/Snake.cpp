#include "Snake.h"

Snake::Snake(const Location & in_loc)
{
	segments[0].InitHead(in_loc);
}

void Snake::MoveBy(Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[ i - 1 ]);
	}
 
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nMaxSegments)
	{
		++nSegments;
	}
}

void Snake::Draw(Board & brd)
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

void Snake::Segment::InitHead(const Location in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::MoveBy(Location delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}
