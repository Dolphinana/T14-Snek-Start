#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(Location & loc, Color c)
{
	gfx.DrawRectDim(loc.x, loc.y, loc.x + dimension, loc.y + dimension, c);
}

int Board::GetWidth()
{
	return width;
}

int Board::GetHeight()
{
	return height;
}
