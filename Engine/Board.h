#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{

public:
	Board(Graphics& gfx);
	void DrawCell(Location& loc, Color c);
	int GetWidth();
	int GetHeight();

	static constexpr int boardWidth = 39;
	static constexpr int boardHeight = 29;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 10;
	static constexpr int height = 10;
	Graphics& gfx;


};
