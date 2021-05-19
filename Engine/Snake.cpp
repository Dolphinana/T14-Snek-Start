#include "Snake.h"

Snake::Snake(const Location & in_loc)
	:
	rng( std::random_device()() ),
	xGoalDist(0, 39),
	yGoalDist(0, 29)
{
	segments[0].InitHead(in_loc);
	for (int i = 1; i <= nMaxSegments; ++i)
	{
		segments[i].InitBody();
	}

	direction = { 1,0 };
}

void Snake::Update(const MainWindow & wnd, Goal& goal)
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT) && out_delta_loc.x != 1)
	{
		out_delta_loc = { -1,0 };
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) && out_delta_loc.x != -1)
	{
		out_delta_loc = { 1,0 };
	}
	if (wnd.kbd.KeyIsPressed(VK_UP) && out_delta_loc.y != 1)
	{
		out_delta_loc = { 0,-1 };
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN) && out_delta_loc.y != -1)
	{
		out_delta_loc = { 0,1 };
	}


	++nTimer;
	if (nTimer >= 8)
	{
		nTimer = 0;
		MoveBy(out_delta_loc);
		TouchGoal(goal, xGoalDist(rng), yGoalDist(rng));
		WrapScreen();
	}

}

void Snake::MoveBy(Location & delta_loc)
{
 
	if ( (abs(delta_loc.x) + abs(delta_loc.y) != 0) ) {direction = delta_loc;}
	
	//if (!TouchWall())
	{
		for (int i = nSegments - 1; i > 0; --i)
		{
			segments[i].Follow(segments[ i - 1 ]);
		}
		segments[0].MoveBy(delta_loc);
	}

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
	if (segments[0].GetX() <= 0 || segments[0].GetY() <= 0 || (segments[0].GetX() + direction.x > 39 ) || (segments[0].GetY() + direction.y > 29   ) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Snake::WrapScreen()
{
	if (segments[0].GetX() < 0)
	{
		segments[0].SetLoc({Board::boardWidth, segments[0].GetY() });
	}
	if (segments[0].GetX() + direction.x > Board::boardWidth + 1)
	{
		segments[0].SetLoc({0,segments[0].GetY()});
	}
	if (segments[0].GetY() < 0)
	{
		segments[0].SetLoc({segments[0].GetX(), Board::boardHeight});
	}
	if (segments[0].GetY() + direction.y > Board::boardHeight + 1)
	{
		segments[0].SetLoc({segments[0].GetX(), 0 });
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
	//assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}
