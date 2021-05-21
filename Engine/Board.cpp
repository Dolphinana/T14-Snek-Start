#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);

	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension,  (loc.y * dimension) + 1, Colors::Blue);
	//gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, loc.x + 1,  dimension, Colors::Blue);
	//gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension,  dimension, Colors::Blue);
	//gfx.DrawRectDim(loc.x, dimension, loc.y, loc.y + 1, Colors::Blue);
}

int Board::GetWidth()
{
	return width;
}

int Board::GetHeight()
{
	return height;
}
