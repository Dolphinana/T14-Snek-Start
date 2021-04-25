#include "Snake.h"

Snake::Snake(const Location & in_loc)
{
	segments[0].InitHead(in_loc);
	for (int i = 1; i <= nMaxSegments; ++i)
	{
		segments[i].InitBody();
	}
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
	Location lol_loc = { 25,25 };
	segments[nSegments - 1].SetLoc(lol_loc);
}

void Snake::TouchGoal(Goal & goal)
{
	if (segments[0].GetX() == goal.loc.x && segments[0].GetY() == goal.loc.y )
	{
		Grow();
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

void Snake::Segment::SetLoc(Location & in_loc)
{
	loc = in_loc;
}

int Snake::Segment::GetX()
{
	return loc.x;
}

int Snake::Segment::GetY()
{
	return loc.y;
}


void Snake::Segment::MoveBy(Location delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}
