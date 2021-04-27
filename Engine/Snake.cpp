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
	segments[nSegments - 1].SetLoc({ 10,10 });
}

void Snake::TouchGoal(Goal & goal, int in_x, int in_y)
{
	if (segments[0].GetX() == goal.loc.x && segments[0].GetY() == goal.loc.y )
	{
		Grow();
		goal.loc.x = in_x;
		goal.loc.y = in_y;
	}

}

bool Snake::TouchWall()
{
	if (segments[0].GetX() <= 0 || segments[0].GetY() <= 0 || segments[0].GetX() >= 39 || segments[0].GetY() >= 29)
	{
		return true;
	}
	else
	{
		return false;
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

void Snake::Segment::SetLoc(const Location & in_loc)
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
