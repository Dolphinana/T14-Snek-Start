#include "Snake.h"

Snake::Snake(const Location & in_loc, const MainWindow& in_wnd)
	:
	wnd( in_wnd ),
	rng( std::random_device()() ),
	xGoalDist(0, 39),
	yGoalDist(0, 29),
	greenColorDist(100,255)
{
	segments[0].InitHead(in_loc);
	for (int i = 1; i < nMaxSegments; ++i)
	{
		
		segments[i].InitBody( greenColorDist(rng) );
	}

	direction = out_delta_loc;
}

void Snake::Update(Goal& goal)
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT) && out_delta_loc.x != 1 && !keyPressed)
	{
		out_delta_loc = { -1,0 };
		keyPressed = true;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) && out_delta_loc.x != -1 && !keyPressed)
	{
		out_delta_loc = { 1,0 };
		keyPressed = true;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP) && out_delta_loc.y != 1 && !keyPressed)
	{
		out_delta_loc = { 0,-1 };
		keyPressed = true;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN) && out_delta_loc.y != -1 && !keyPressed)
	{
		out_delta_loc = { 0,1 };
		keyPressed = true;
	}



	++nTimer;
	if (nTimer >= snakeSpeedRate)
	{
		if (!HitSegment() )
		{
			keyPressed = false;
			nTimer = 0;
			MoveBy(out_delta_loc);
			WrapScreen();
			TouchGoal(goal);
		}
		else { for (int i = 0; i < nSegments; ++i) { segments[i].GameOver(); keyPressed = true;} }
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
		segments[nSegments - 1].SetLoc({ segments[nSegments - 2].GetLoc().x,segments[nSegments - 2].GetLoc().y });
	}
}

void Snake::TouchGoal(Goal& goal)
{
	if (segments[0].GetLoc().x == goal.loc.x && segments[0].GetLoc().y == goal.loc.y )
	{
		Grow();

		goal.loc.x = xGoalDist(rng);
		goal.loc.y = yGoalDist(rng);

		for (int i = 0; i < nSegments; ++i)
		{
			if (segments[i].GetLoc().x == goal.loc.x && segments[i].GetLoc().y == goal.loc.y )
			{
				goal.loc.x = xGoalDist(rng);
				goal.loc.y = yGoalDist(rng);
				i = 0;
			}
		}


	}

}

bool Snake::TouchWall()
{
	if (segments[0].GetLoc().x <= 0 || segments[0].GetLoc().y <= 0 || (segments[0].GetLoc().x + direction.x > 39 ) || (segments[0].GetLoc().y + direction.y > 29   ) )
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
	if (segments[0].GetLoc().x < 0)
	{
		segments[0].SetLoc({Board::boardWidth, segments[0].GetLoc().y });
	}
	if (segments[0].GetLoc().x + direction.x > Board::boardWidth + 1)
	{
		segments[0].SetLoc({0,segments[0].GetLoc().y});
	}
	if (segments[0].GetLoc().y < 0)
	{
		segments[0].SetLoc({segments[0].GetLoc().x, Board::boardHeight});
	}
	if (segments[0].GetLoc().y + direction.y > Board::boardHeight + 1)
	{
		segments[0].SetLoc({segments[0].GetLoc().x, 0 });
	}


}

void Snake::Draw(Board & brd)
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::HitSegment()
{
	for (int i = 1; i < nSegments; ++i)
	{
		if (segments[0].GetLoc().x + out_delta_loc.x == segments[i].GetLoc().x && segments[0].GetLoc().y + out_delta_loc.y == segments[i].GetLoc().y)
		{
			return true;
		}
	}
	return false;

}

void Snake::Segment::InitHead(const Location in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(unsigned char randomGreen)
{
	//const int cg = randomGreen;
	c = {0, randomGreen, 0};
}

void Snake::Segment::GameOver()
{
	c = {255,0,00};
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

Location Snake::Segment::GetLoc()
{
	return loc;
}

void Snake::Segment::MoveBy(Location delta_loc)
{
	//assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}
