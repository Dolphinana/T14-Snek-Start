#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);

	gfx.DrawRectDim( (loc.x * dimension) , loc.y * dimension, dimension,  1,  Colors::Black);
	gfx.DrawRectDim( loc.x * dimension, (loc.y * dimension) + dimension - 1, dimension, 1,  Colors::Black);

	gfx.DrawRectDim( (loc.x * dimension) , loc.y * dimension, 1,  dimension,  Colors::Black);
	gfx.DrawRectDim( (loc.x * dimension) + dimension - 1, loc.y * dimension, 1,  dimension,  Colors::Black);
}

int Board::GetWidth()
{
	return width;
}

int Board::GetHeight()
{
	return height;
}
