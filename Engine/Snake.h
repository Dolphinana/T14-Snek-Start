#pragma once

#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include "assert.h"
#include "Goal.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location in_loc);
		void InitBody();
		void Follow(const Segment& next);
		void MoveBy(Location delta_loc);
		void Draw(Board& brd);
		int GetX();
		int GetY();
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Location& in_loc);
	void MoveBy(Location& delta_loc);
	void Grow();
	void TouchGoal(Goal& goal);
	void Draw(Board& brd);
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nMaxSegments = 100;
	Segment segments[nMaxSegments];
	int nSegments = 1;
};
