#pragma once
#include "Location.h"
#include "Board.h"

class Goal
{
public:
	Goal( const Location& in_loc );

	void Draw(Board& brd);
	Location loc;
private:
	

};
