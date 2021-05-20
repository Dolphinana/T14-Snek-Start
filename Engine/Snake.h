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
		void GameOver();
		void Follow(const Segment& next);
		void MoveBy(Location delta_loc);
		void Draw(Board& brd);
		void SetLoc( const Location& in_loc);
		Location GetLoc();
	private:
		Location loc;
		Color c;
	};

public:
	std::mt19937 rng;
	std::uniform_int_distribution<int> xGoalDist;
	std::uniform_int_distribution<int> yGoalDist;
	Snake(const Location& in_loc, const MainWindow& in_wnd);
	void Update(Goal& goal);
	void MoveBy(Location& delta_loc);
	void Grow();
	void TouchGoal(Goal& goal, int in_x, int in_y);
	bool TouchWall();
	void WrapScreen();
	void Draw(Board& brd);
	bool HitSegment();
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nMaxSegments = 400;
	Segment segments[nMaxSegments];
	int nSegments = 1;
	Location out_delta_loc = {1,0};
	Location direction;
	const MainWindow& wnd;
	int nTimer = 0;
	bool gameOver = false;
	bool keyPressed = false;
};
