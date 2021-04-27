#pragma once

#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include "assert.h"
#include "Goal.h"
#include "MainWindow.h"
#include <random>

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
		void SetLoc( const Location& in_loc);
		int GetX();
		int GetY();
	private:
		Location loc;
		Color c;
	};

public:
	std::mt19937 rng;
	std::uniform_int_distribution<int> xGoalDist;
	std::uniform_int_distribution<int> yGoalDist;
	Snake(const Location& in_loc);
	void Update(const MainWindow& wnd, Goal& goal);
	void MoveBy(Location& delta_loc);
	void Grow();
	void TouchGoal(Goal& goal, int in_x, int in_y);
	bool TouchWall();
	void Draw(Board& brd);
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nMaxSegments = 100;
	Segment segments[nMaxSegments];
	int nSegments = 1;

	Location out_delta_loc;
	Location direction;
	
	int nTimer = 0;
};
