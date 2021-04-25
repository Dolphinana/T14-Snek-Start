/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	rng( std::random_device()() ),
	snake({ 10,10 }),
	goal( { 12,12} )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		delta_loc = { -1,0 };
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		delta_loc = { 1,0 };
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		delta_loc = { 0,-1 };
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		delta_loc = { 0,1 };
	}

	snake.TouchGoal(goal);
	snake.MoveBy(delta_loc);


}

void Game::ComposeFrame()
{
	//std::uniform_int_distribution<int> colorDist(0, 255);
//	for (int x = 0; x < brd.GetWidth(); ++x)
//	{
//		for (int y = 0; y < brd.GetHeight(); ++y)
//		{
//			Location loc = { x,y };
//			Color c( colorDist(rng), colorDist(rng), colorDist(rng) );
//			brd.DrawCell(loc, c);
//		}
//	}

	snake.Draw(brd);
	goal.Draw(brd);

	for (int i = 0; i < 99999999; ++i)
	{

	}
}
