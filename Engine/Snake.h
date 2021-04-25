#pragma once

#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include "assert.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location in_loc);
		void InitBody();
		void Follow(Segment& next);
		void MoveBy(Location delta_loc);
		void Draw(Board& brd);
	private:
		Location loc;
		Color c;
	};

public:
	Snake(Location& in_loc);
	void MoveBy(Location& delta_loc);
	void Grow();
	void Draw(Board& brd);
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nMaxSegments = 100;
	Segment segments[nMaxSegments];
	int nSegments = 1;
};
