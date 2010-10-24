//Author GeekyLink
#include <iostream>
#include <time.h>

#include <PA9.h>  // PAlib include

using namespace std;

// PAGfx Include
#include "gfx/all_gfx.c"
#include "gfx/all_gfx.h"

int iPlayer; //1 = player 1, 2 = player 2
int iPlayers;
int iDifficulty;
bool bTitle;

class Game
{
public:
	Game();
	void drawboard();
	void getmove();
	void randommove();
	void checkwin();
	void checkstale();
	void clearscreen();
	//various difficulties
	void AI1();
	void AI2();
	void AI3();
	void AI4();
	void AI5();
	void movecorner();
	void movecross();
private:
	int iBoard[3][3];
	int iX;
	int iY;
	int iWin; //1 = player one won, 2 = player 2 won
	int iTurn;
	bool bValid;

};

Game::Game()
{
	clearscreen();
}

void Game::clearscreen()
{
	iPlayer = 1;
	iWin = 0;
	iTurn = 0;
	for (iX=0; iX<3; iX++)
	{
		for (iY=0; iY<3; iY++)
		{
			iBoard[iX][iY] = 0;
		}
	}
}

void Game::drawboard()
{
		for (iX=0; iX<3; iX++)
		{
			for (iY=0; iY<3; iY++)
			{
				if (iBoard[iY][iX] == 0)
				{
					PA_SetSpriteAnim(0,(iY)*3 + (iX) + 2,0);
				}
				else if (iBoard[iY][iX] == 1)
				{
					PA_SetSpriteAnim(0,(iY)*3 + (iX) + 2,1);	
				}
				else
				{
					PA_SetSpriteAnim(0,(iY)*3 + (iX) + 2,2);
				}
			}
		}
	if ((iWin == 1) || (iWin == 2))
	{
		PA_OutputText(0,8,23,"Player %d has won!\n", iWin);      
		
		for(int iWait = 0; iWait < 60; iWait++) { PA_WaitForVBL(); }

		clearscreen();
		drawboard();
		
		PA_EasyBgLoad(0, 3, bottom);
		
		PA_SetSpriteXY(0,16,32,100);
		PA_SetSpriteXY(0,17,160,100);	   
		
		int iStatus = 0;
		
		while(iStatus == 0) 
		{ 
			if (Stylus.Newpress)
			{
				if (PA_SpriteTouched(16)) iStatus = 1;
				else if (PA_SpriteTouched(17)) iStatus = 2;
			}			
			
			PA_WaitForVBL(); 
		}

  		PA_SetSpriteXY(0,16,-64,100);
		PA_SetSpriteXY(0,17,-64,100);	
		
		if (iStatus == 1) { PA_EasyBgLoad(0, 3, board);	}
		else if (iStatus == 2) { bTitle = true; }
	}
}

void Game::getmove()
{
   
   bValid = false;
   
   iX = -1; iY = -1;
   
   PA_WaitForVBL();
   
   while(!bValid) 
	{ 
	   if (Stylus.Newpress)
	   {
			if (Stylus.X > 45 && Stylus.X < 98 && Stylus.Y > 17 && Stylus.Y < 68) { iX = 0; iY = 0; }
			else if (Stylus.X > 106 && Stylus.X < 151 && Stylus.Y > 17 && Stylus.Y < 68) { iX = 1; iY = 0;}
			else if (Stylus.X > 155 && Stylus.X < 204 && Stylus.Y > 17 && Stylus.Y < 68) { iX = 2; iY = 0;}
			else if (Stylus.X > 45 && Stylus.X < 98 && Stylus.Y > 75 && Stylus.Y < 119) { iX = 0; iY = 1;}
			else if (Stylus.X > 106 && Stylus.X < 151 && Stylus.Y > 75 && Stylus.Y < 119) { iX = 1; iY = 1;}
			else if (Stylus.X > 155 && Stylus.X < 204 && Stylus.Y > 75 && Stylus.Y < 119) { iX = 2; iY = 1;}
			else if (Stylus.X > 45 && Stylus.X < 98 && Stylus.Y > 127 && Stylus.Y < 170) { iX = 0; iY = 2;}
			else if (Stylus.X > 106 && Stylus.X < 151 && Stylus.Y > 127 && Stylus.Y < 170) { iX = 1; iY = 2;}
			else if (Stylus.X > 155 && Stylus.X < 204 && Stylus.Y > 127 && Stylus.Y < 170) { iX = 2; iY = 2;}
		}		
		
		if (iBoard[iY][iX] == 0 && iX > -1 && iY > -1)
		{
			bValid = true;
		}
		else if (iX > -1 && iY > -1)
		{
		   PA_OutputText(0,2,23,"That Space is already in use!");
		}				
		PA_WaitForVBL(); 	
	}
   
   PA_OutputText(0,2,23,"                              ");
   PA_WaitForVBL();

	//check who's the player
	if (iPlayer == 1)
	{
		iBoard[iY][iX] = 1;
		iPlayer = 2;
	}
	else
	{
		iBoard[iY][iX] = 2;
		iPlayer = 1;
	}
}

void Game::checkstale()
{
	iTurn++;

bool bStalmate = true;
		for (iX=0; iX<3; iX++)
		{
			for (iY=0; iY<3; iY++)
			{
				if (iBoard[iY][iX] == 0)
				{
					bStalmate = false;
				}
			}
		}
	
	
	if (bStalmate)
	{
		PA_OutputText(0,12,23,"Stalemate!");
		
		for(int iWait = 0; iWait < 60; iWait++) { PA_WaitForVBL(); }

		clearscreen();
		drawboard();
		
		PA_EasyBgLoad(0, 3, bottom);
		
		PA_SetSpriteXY(0,16,32,100);
		PA_SetSpriteXY(0,17,160,100);	   
		
		int iStatus = 0;
		
		while(iStatus == 0) 
		{ 
			if (Stylus.Newpress)
			{
				if (PA_SpriteTouched(16)) iStatus = 1;
				else if (PA_SpriteTouched(17)) iStatus = 2;
			}			
			
			PA_WaitForVBL(); 
		}

  		PA_SetSpriteXY(0,16,-64,100);
		PA_SetSpriteXY(0,17,-64,100);	
		
		if (iStatus == 1) { PA_EasyBgLoad(0, 3, board);	}
		else if (iStatus == 2) { bTitle = true; }
	} 
}

void Game::checkwin()
{
	//player 1 verticals	
	if((iBoard[0][0] == 1) && (iBoard[0][1] == 1) && (iBoard[0][2] == 1))
		iWin = 1;
	if((iBoard[1][0] == 1) && (iBoard[1][1] == 1) && (iBoard[1][2] == 1))
		iWin = 1;
	if((iBoard[2][0] == 1) && (iBoard[2][1] == 1) && (iBoard[2][2] == 1))
		iWin = 1;
	//player 1 horizontals
	if((iBoard[0][0] == 1) && (iBoard[1][0] == 1) && (iBoard[2][0] == 1))
		iWin = 1;
	if((iBoard[0][1] == 1) && (iBoard[1][1] == 1) && (iBoard[2][1] == 1))
		iWin = 1;
	if((iBoard[0][2] == 1) && (iBoard[1][2] == 1) && (iBoard[2][2] == 1))
		iWin = 1;
	//player 1 diagonals
	if((iBoard[0][0] == 1) && (iBoard[1][1] == 1) && (iBoard[2][2] == 1))
		iWin = 1;
	if((iBoard[0][2] == 1) && (iBoard[1][1] == 1) && (iBoard[2][0] == 1))
		iWin = 1;

	//player 2 verticals
	if((iBoard[0][0] == 2) && (iBoard[0][1] == 2) && (iBoard[0][2] == 2))
		iWin = 2;
	if((iBoard[1][0] == 2) && (iBoard[1][1] == 2) && (iBoard[1][2] == 2))
		iWin = 2;
	if((iBoard[2][0] == 2) && (iBoard[2][1] == 2) && (iBoard[2][2] == 2))
		iWin = 2;
	//player 2  horizontals
	if((iBoard[0][0] == 2) && (iBoard[1][0] == 2) && (iBoard[2][0] == 2))
		iWin = 2;
	if((iBoard[0][1] == 2) && (iBoard[1][1] == 2) && (iBoard[2][1] == 2))
		iWin = 2;
	if((iBoard[0][2] == 2) && (iBoard[1][2] == 2) && (iBoard[2][2] == 2))
		iWin = 2;
	//player 2 diagonals
	if((iBoard[0][0] == 2) && (iBoard[1][1] == 2) && (iBoard[2][2] == 2))
		iWin = 2;
	if((iBoard[0][2] == 2) && (iBoard[1][1] == 2) && (iBoard[2][0] == 2))
		iWin = 2;

}


void Game::AI1()
{
	randommove();
}
void Game::AI2()
{
//checks to see if it can win
	//column one
	if((iBoard[0][0] == 2) && (iBoard[0][1] == 2) && (iBoard[0][2] != 1))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[0][1] != 1) && (iBoard[0][2] == 2))
		iBoard[0][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[0][1] == 2) && (iBoard[0][2] == 2))
		iBoard[0][0] = 2;
	//column two
	else if((iBoard[1][0] == 2) && (iBoard[1][1] == 2) && (iBoard[1][2] != 1))
		iBoard[1][2] = 2;
	else if((iBoard[1][0] == 2) && (iBoard[1][1] != 1) && (iBoard[1][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] != 1) && (iBoard[1][1] == 2) && (iBoard[1][2] == 2))
		iBoard[1][0] = 2;
	//column three
	else if((iBoard[2][0] == 2) && (iBoard[2][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[2][0] == 2) && (iBoard[2][1] != 1) && (iBoard[2][2] == 2))
		iBoard[2][1] = 2;
	else if((iBoard[2][0] != 1) && (iBoard[2][1] == 2) && (iBoard[2][2] == 2))
		iBoard[2][0] = 2;
	//row one
	else if((iBoard[0][0] == 2) && (iBoard[1][0] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][0] != 1) && (iBoard[2][0] == 2))
		iBoard[1][0] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][0] == 2) && (iBoard[2][0] == 2))
		iBoard[0][0] = 2;
	//row two
	else if((iBoard[0][1] == 2) && (iBoard[1][1] == 2) && (iBoard[2][1] != 1))
		iBoard[2][1] = 2;
	else if((iBoard[0][1] == 2) && (iBoard[1][1] != 1) && (iBoard[2][1] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][1] != 1) && (iBoard[1][1] == 2) && (iBoard[2][1] == 2))
		iBoard[0][1] = 2;
	//row three
	else if((iBoard[0][2] == 2) && (iBoard[1][2] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][2] != 1) && (iBoard[2][2] == 2))
		iBoard[1][2] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][2] == 2) && (iBoard[2][2] == 2))
		iBoard[0][2] = 2;
	//diagonal top left to bottom right
	else if((iBoard[0][0] == 2) && (iBoard[1][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][1] != 1) && (iBoard[2][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][1] == 2) && (iBoard[2][2] == 2))
		iBoard[0][0] = 2;
	//diagonal top right to bottom left
	else if((iBoard[0][2] == 2) && (iBoard[1][1] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][1] != 1) && (iBoard[2][0] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][1] == 2) && (iBoard[2][0] == 2))
		iBoard[0][2] = 2;
	else
		randommove();
}
void Game::AI3()
{
	//checks to see if it can win
	//column one
	if((iBoard[0][0] == 2) && (iBoard[0][1] == 2) && (iBoard[0][2] != 1))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[0][1] != 1) && (iBoard[0][2] == 2))
		iBoard[0][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[0][1] == 2) && (iBoard[0][2] == 2))
		iBoard[0][0] = 2;
	//column two
	else if((iBoard[1][0] == 2) && (iBoard[1][1] == 2) && (iBoard[1][2] != 1))
		iBoard[1][2] = 2;
	else if((iBoard[1][0] == 2) && (iBoard[1][1] != 1) && (iBoard[1][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] != 1) && (iBoard[1][1] == 2) && (iBoard[1][2] == 2))
		iBoard[1][0] = 2;
	//column three
	else if((iBoard[2][0] == 2) && (iBoard[2][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[2][0] == 2) && (iBoard[2][1] != 1) && (iBoard[2][2] == 2))
		iBoard[2][1] = 2;
	else if((iBoard[2][0] != 1) && (iBoard[2][1] == 2) && (iBoard[2][2] == 2))
		iBoard[2][0] = 2;
	//row one
	else if((iBoard[0][0] == 2) && (iBoard[1][0] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][0] != 1) && (iBoard[2][0] == 2))
		iBoard[1][0] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][0] == 2) && (iBoard[2][0] == 2))
		iBoard[0][0] = 2;
	//row two
	else if((iBoard[0][1] == 2) && (iBoard[1][1] == 2) && (iBoard[2][1] != 1))
		iBoard[2][1] = 2;
	else if((iBoard[0][1] == 2) && (iBoard[1][1] != 1) && (iBoard[2][1] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][1] != 1) && (iBoard[1][1] == 2) && (iBoard[2][1] == 2))
		iBoard[0][1] = 2;
	//row three
	else if((iBoard[0][2] == 2) && (iBoard[1][2] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][2] != 1) && (iBoard[2][2] == 2))
		iBoard[1][2] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][2] == 2) && (iBoard[2][2] == 2))
		iBoard[0][2] = 2;
	//diagonal top left to bottom right
	else if((iBoard[0][0] == 2) && (iBoard[1][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][1] != 1) && (iBoard[2][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][1] == 2) && (iBoard[2][2] == 2))
		iBoard[0][0] = 2;
	//diagonal top right to bottom left
	else if((iBoard[0][2] == 2) && (iBoard[1][1] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][1] != 1) && (iBoard[2][0] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][1] == 2) && (iBoard[2][0] == 2))
		iBoard[0][2] = 2;

	//block column one
	else if((iBoard[0][0] == 1) && (iBoard[0][1] == 1) && (iBoard[0][2] == 0))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[0][1] == 0) && (iBoard[0][2] == 1))
		iBoard[0][1] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[0][1] == 1) && (iBoard[0][2] == 1))
		iBoard[0][0] = 2;
	//block column two
	else if((iBoard[1][0] == 1) && (iBoard[1][1] == 1) && (iBoard[1][2] == 0))
		iBoard[1][2] = 2;
	else if((iBoard[1][0] == 1) && (iBoard[1][1] == 0) && (iBoard[1][2] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] == 0) && (iBoard[1][1] == 1) && (iBoard[1][2] == 1))
		iBoard[1][0] = 2;
	//block column three
	else if((iBoard[2][0] == 1) && (iBoard[2][1] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[2][0] == 1) && (iBoard[2][1] == 0) && (iBoard[2][2] == 1))
		iBoard[2][1] = 2;
	else if((iBoard[2][0] == 0) && (iBoard[2][1] == 1) && (iBoard[2][2] == 1))
		iBoard[2][0] = 2;
	//block row one
	else if((iBoard[0][0] == 1) && (iBoard[1][0] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[1][0] == 0) && (iBoard[2][0] == 1))
		iBoard[1][0] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[1][0] == 1) && (iBoard[2][0] == 1))
		iBoard[0][0] = 2;
	//block row two
	else if((iBoard[0][1] == 1) && (iBoard[1][1] == 1) && (iBoard[2][1] == 0))
		iBoard[2][1] = 2;
	else if((iBoard[0][1] == 1) && (iBoard[1][1] == 0) && (iBoard[2][1] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][1] == 0) && (iBoard[1][1] == 1) && (iBoard[2][1] == 1))
		iBoard[0][1] = 2;
	//block row three
	else if((iBoard[0][2] == 1) && (iBoard[1][2] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[0][2] == 1) && (iBoard[1][2] == 0) && (iBoard[2][2] == 1))
		iBoard[1][2] = 2;
	else if((iBoard[0][2] == 0) && (iBoard[1][2] == 1) && (iBoard[2][2] == 1))
		iBoard[0][2] = 2;
	//block diagonal top left to bottom right
	else if((iBoard[0][0] == 1) && (iBoard[1][1] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[1][1] == 0) && (iBoard[2][2] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[1][1] == 1) && (iBoard[2][2] == 1))
		iBoard[0][0] = 2;
	//block diagonal top right to bottom left
	else if((iBoard[0][2] == 1) && (iBoard[1][1] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;
	else if((iBoard[0][2] == 1) && (iBoard[1][1] == 0) && (iBoard[2][0] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][2] == 0) && (iBoard[1][1] == 1) && (iBoard[2][0] == 1))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 0) || (iBoard[2][2] == 0) || (iBoard[2][0] == 0) || (iBoard[0][2] == 0) || (iBoard[1][1] == 0))
		movecorner();
	else
		randommove();
}
void Game::AI4()
{
//checks to see if it can win
	//column one
	if((iBoard[0][0] == 2) && (iBoard[0][1] == 2) && (iBoard[0][2] != 1))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[0][1] != 1) && (iBoard[0][2] == 2))
		iBoard[0][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[0][1] == 2) && (iBoard[0][2] == 2))
		iBoard[0][0] = 2;
	//column two
	else if((iBoard[1][0] == 2) && (iBoard[1][1] == 2) && (iBoard[1][2] != 1))
		iBoard[1][2] = 2;
	else if((iBoard[1][0] == 2) && (iBoard[1][1] != 1) && (iBoard[1][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] != 1) && (iBoard[1][1] == 2) && (iBoard[1][2] == 2))
		iBoard[1][0] = 2;
	//column three
	else if((iBoard[2][0] == 2) && (iBoard[2][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[2][0] == 2) && (iBoard[2][1] != 1) && (iBoard[2][2] == 2))
		iBoard[2][1] = 2;
	else if((iBoard[2][0] != 1) && (iBoard[2][1] == 2) && (iBoard[2][2] == 2))
		iBoard[2][0] = 2;
	//row one
	else if((iBoard[0][0] == 2) && (iBoard[1][0] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][0] != 1) && (iBoard[2][0] == 2))
		iBoard[1][0] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][0] == 2) && (iBoard[2][0] == 2))
		iBoard[0][0] = 2;
	//row two
	else if((iBoard[0][1] == 2) && (iBoard[1][1] == 2) && (iBoard[2][1] != 1))
		iBoard[2][1] = 2;
	else if((iBoard[0][1] == 2) && (iBoard[1][1] != 1) && (iBoard[2][1] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][1] != 1) && (iBoard[1][1] == 2) && (iBoard[2][1] == 2))
		iBoard[0][1] = 2;
	//row three
	else if((iBoard[0][2] == 2) && (iBoard[1][2] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][2] != 1) && (iBoard[2][2] == 2))
		iBoard[1][2] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][2] == 2) && (iBoard[2][2] == 2))
		iBoard[0][2] = 2;
	//diagonal top left to bottom right
	else if((iBoard[0][0] == 2) && (iBoard[1][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][1] != 1) && (iBoard[2][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][1] == 2) && (iBoard[2][2] == 2))
		iBoard[0][0] = 2;
	//diagonal top right to bottom left
	else if((iBoard[0][2] == 2) && (iBoard[1][1] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][1] != 1) && (iBoard[2][0] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][1] == 2) && (iBoard[2][0] == 2))
		iBoard[0][2] = 2;

	//block column one
	else if((iBoard[0][0] == 1) && (iBoard[0][1] == 1) && (iBoard[0][2] == 0))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[0][1] == 0) && (iBoard[0][2] == 1))
		iBoard[0][1] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[0][1] == 1) && (iBoard[0][2] == 1))
		iBoard[0][0] = 2;
	//block column two
	else if((iBoard[1][0] == 1) && (iBoard[1][1] == 1) && (iBoard[1][2] == 0))
		iBoard[1][2] = 2;
	else if((iBoard[1][0] == 1) && (iBoard[1][1] == 0) && (iBoard[1][2] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] == 0) && (iBoard[1][1] == 1) && (iBoard[1][2] == 1))
		iBoard[1][0] = 2;
	//block column three
	else if((iBoard[2][0] == 1) && (iBoard[2][1] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[2][0] == 1) && (iBoard[2][1] == 0) && (iBoard[2][2] == 1))
		iBoard[2][1] = 2;
	else if((iBoard[2][0] == 0) && (iBoard[2][1] == 1) && (iBoard[2][2] == 1))
		iBoard[2][0] = 2;
	//block row one
	else if((iBoard[0][0] == 1) && (iBoard[1][0] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[1][0] == 0) && (iBoard[2][0] == 1))
		iBoard[1][0] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[1][0] == 1) && (iBoard[2][0] == 1))
		iBoard[0][0] = 2;
	//block row two
	else if((iBoard[0][1] == 1) && (iBoard[1][1] == 1) && (iBoard[2][1] == 0))
		iBoard[2][1] = 2;
	else if((iBoard[0][1] == 1) && (iBoard[1][1] == 0) && (iBoard[2][1] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][1] == 0) && (iBoard[1][1] == 1) && (iBoard[2][1] == 1))
		iBoard[0][1] = 2;
	//block row three
	else if((iBoard[0][2] == 1) && (iBoard[1][2] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[0][2] == 1) && (iBoard[1][2] == 0) && (iBoard[2][2] == 1))
		iBoard[1][2] = 2;
	else if((iBoard[0][2] == 0) && (iBoard[1][2] == 1) && (iBoard[2][2] == 1))
		iBoard[0][2] = 2;
	//block diagonal top left to bottom right
	else if((iBoard[0][0] == 1) && (iBoard[1][1] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[1][1] == 0) && (iBoard[2][2] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[1][1] == 1) && (iBoard[2][2] == 1))
		iBoard[0][0] = 2;
	//block diagonal top right to bottom left
	else if((iBoard[0][2] == 1) && (iBoard[1][1] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;
	else if((iBoard[0][2] == 1) && (iBoard[1][1] == 0) && (iBoard[2][0] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][2] == 0) && (iBoard[1][1] == 1) && (iBoard[2][0] == 1))
		iBoard[0][2] = 2;
	//checks if the player is trying to trap the computer
	else if((iBoard[0][0] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[2][2] == 1) && (iBoard[0][0] == 0))
		iBoard[0][0] = 2;	
	else if((iBoard[0][2] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;	
	else if((iBoard[2][0] == 1) && (iBoard[0][2] == 0))
		iBoard[0][2] = 2;
	//moves to a random corner or the middle
	else if((iBoard[0][0] == 0) || (iBoard[2][2] == 0) || (iBoard[2][0] == 0) || (iBoard[0][2] == 0) || (iBoard[1][1] == 0))
		movecorner();
	//moves to some other random spot
	else
	{
		randommove();
	}
}
void Game::AI5()
{
     
     //moves to middle if possible
     if (iBoard[1][1] == 0)
        iBoard[1][1] = 2;
	//checks to see if it can win
	//column one	
	else if((iBoard[0][0] == 2) && (iBoard[0][1] == 2) && (iBoard[0][2] != 1))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[0][1] != 1) && (iBoard[0][2] == 2))
		iBoard[0][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[0][1] == 2) && (iBoard[0][2] == 2))
		iBoard[0][0] = 2;
	//column two
	else if((iBoard[1][0] == 2) && (iBoard[1][1] == 2) && (iBoard[1][2] != 1))
		iBoard[1][2] = 2;
	else if((iBoard[1][0] == 2) && (iBoard[1][1] != 1) && (iBoard[1][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] != 1) && (iBoard[1][1] == 2) && (iBoard[1][2] == 2))
		iBoard[1][0] = 2;
	//column three
	else if((iBoard[2][0] == 2) && (iBoard[2][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[2][0] == 2) && (iBoard[2][1] != 1) && (iBoard[2][2] == 2))
		iBoard[2][1] = 2;
	else if((iBoard[2][0] != 1) && (iBoard[2][1] == 2) && (iBoard[2][2] == 2))
		iBoard[2][0] = 2;
	//row one
	else if((iBoard[0][0] == 2) && (iBoard[1][0] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][0] != 1) && (iBoard[2][0] == 2))
		iBoard[1][0] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][0] == 2) && (iBoard[2][0] == 2))
		iBoard[0][0] = 2;
	//row two
	else if((iBoard[0][1] == 2) && (iBoard[1][1] == 2) && (iBoard[2][1] != 1))
		iBoard[2][1] = 2;
	else if((iBoard[0][1] == 2) && (iBoard[1][1] != 1) && (iBoard[2][1] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][1] != 1) && (iBoard[1][1] == 2) && (iBoard[2][1] == 2))
		iBoard[0][1] = 2;
	//row three
	else if((iBoard[0][2] == 2) && (iBoard[1][2] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][2] != 1) && (iBoard[2][2] == 2))
		iBoard[1][2] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][2] == 2) && (iBoard[2][2] == 2))
		iBoard[0][2] = 2;
	//diagonal top left to bottom right
	else if((iBoard[0][0] == 2) && (iBoard[1][1] == 2) && (iBoard[2][2] != 1))
		iBoard[2][2] = 2;
	else if((iBoard[0][0] == 2) && (iBoard[1][1] != 1) && (iBoard[2][2] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][0] != 1) && (iBoard[1][1] == 2) && (iBoard[2][2] == 2))
		iBoard[0][0] = 2;
	//diagonal top right to bottom left
	else if((iBoard[0][2] == 2) && (iBoard[1][1] == 2) && (iBoard[2][0] != 1))
		iBoard[2][0] = 2;
	else if((iBoard[0][2] == 2) && (iBoard[1][1] != 1) && (iBoard[2][0] == 2))
		iBoard[1][1] = 2;
	else if((iBoard[0][2] != 1) && (iBoard[1][1] == 2) && (iBoard[2][0] == 2))
		iBoard[0][2] = 2;

	//block column one
	else if((iBoard[0][0] == 1) && (iBoard[0][1] == 1) && (iBoard[0][2] == 0))
		iBoard[0][2] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[0][1] == 0) && (iBoard[0][2] == 1))
		iBoard[0][1] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[0][1] == 1) && (iBoard[0][2] == 1))
		iBoard[0][0] = 2;
	//block column two
	else if((iBoard[1][0] == 1) && (iBoard[1][1] == 1) && (iBoard[1][2] == 0))
		iBoard[1][2] = 2;
	else if((iBoard[1][0] == 1) && (iBoard[1][1] == 0) && (iBoard[1][2] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] == 0) && (iBoard[1][1] == 1) && (iBoard[1][2] == 1))
		iBoard[1][0] = 2;
	//block column three
	else if((iBoard[2][0] == 1) && (iBoard[2][1] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[2][0] == 1) && (iBoard[2][1] == 0) && (iBoard[2][2] == 1))
		iBoard[2][1] = 2;
	else if((iBoard[2][0] == 0) && (iBoard[2][1] == 1) && (iBoard[2][2] == 1))
		iBoard[2][0] = 2;
	//block row one
	else if((iBoard[0][0] == 1) && (iBoard[1][0] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[1][0] == 0) && (iBoard[2][0] == 1))
		iBoard[1][0] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[1][0] == 1) && (iBoard[2][0] == 1))
		iBoard[0][0] = 2;
	//block row two
	else if((iBoard[0][1] == 1) && (iBoard[1][1] == 1) && (iBoard[2][1] == 0))
		iBoard[2][1] = 2;
	else if((iBoard[0][1] == 1) && (iBoard[1][1] == 0) && (iBoard[2][1] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][1] == 0) && (iBoard[1][1] == 1) && (iBoard[2][1] == 1))
		iBoard[0][1] = 2;
	//block row three
	else if((iBoard[0][2] == 1) && (iBoard[1][2] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[0][2] == 1) && (iBoard[1][2] == 0) && (iBoard[2][2] == 1))
		iBoard[1][2] = 2;
	else if((iBoard[0][2] == 0) && (iBoard[1][2] == 1) && (iBoard[2][2] == 1))
		iBoard[0][2] = 2;
	//block diagonal top left to bottom right
	else if((iBoard[0][0] == 1) && (iBoard[1][1] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[0][0] == 1) && (iBoard[1][1] == 0) && (iBoard[2][2] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][0] == 0) && (iBoard[1][1] == 1) && (iBoard[2][2] == 1))
		iBoard[0][0] = 2;
	//block diagonal top right to bottom left
	else if((iBoard[0][2] == 1) && (iBoard[1][1] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;
	else if((iBoard[0][2] == 1) && (iBoard[1][1] == 0) && (iBoard[2][0] == 1))
		iBoard[1][1] = 2;
	else if((iBoard[0][2] == 0) && (iBoard[1][1] == 1) && (iBoard[2][0] == 1))
		iBoard[0][2] = 2;
	//checks if the player is trying to trap the computer
	else if((iBoard[0][0] == 1) && (iBoard[2][2] == 0))
		iBoard[2][2] = 2;
	else if((iBoard[2][2] == 1) && (iBoard[0][0] == 0))
		iBoard[0][0] = 2;	
	else if((iBoard[0][2] == 1) && (iBoard[2][0] == 0))
		iBoard[2][0] = 2;	
	else if((iBoard[2][0] == 1) && (iBoard[0][2] == 0))
		iBoard[0][2] = 2;
	//checks some more possiblities
	else if((iBoard[0][1] == 1) && (iBoard[1][0] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;
	else if((iBoard[1][0] == 1) && (iBoard[2][1] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;	
	else if((iBoard[2][1] == 1) && (iBoard[1][2] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;	
	else if((iBoard[1][2] == 1) && (iBoard[0][1] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;
	//checks even more
	else if((iBoard[0][0] == 1) && (iBoard[2][1] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;
	else if((iBoard[2][0] == 1) && (iBoard[0][1] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;	
	else if((iBoard[2][2] == 1) && (iBoard[0][1] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;	
	else if((iBoard[0][2] == 1) && (iBoard[2][1] == 1) && (iBoard[1][1] == 0))
		iBoard[1][1] = 2;
	//checks more :o
	else if((iBoard[0][0] == 1) && (iBoard[2][2] == 1) && (iBoard[1][1] == 2))
	     movecross();
 	else if((iBoard[2][0] == 1) && (iBoard[0][2] == 1) && (iBoard[1][1] == 2))
	     movecross();
    //ZOMG what's this?! more?!?!?
    else if((iBoard[2][1] == 1) && (iBoard[1][0] == 1) && (iBoard[2][0] == 0))
	     iBoard[2][0] = 2;
    else if((iBoard[2][1] == 1) && (iBoard[1][2] == 1) && (iBoard[2][2] == 0))
	     iBoard[2][2] = 2;
    else if((iBoard[1][2] == 1) && (iBoard[0][1] == 1) && (iBoard[0][2] == 0))
	     iBoard[0][2] = 2;
    else if((iBoard[0][1] == 1) && (iBoard[1][0] == 1) && (iBoard[0][0] == 0))
	     iBoard[0][0] = 2;
	//moves to a random corner or the middle
	else if((iBoard[0][0] == 0) || (iBoard[2][2] == 0) || (iBoard[2][0] == 0) || (iBoard[0][2] == 0) || (iBoard[1][1] == 0))
		movecorner();
	//moves to some other random spot
	else
	{
		randommove();
	}
}

void Game::movecross()
{
	bValid = false;
	while (bValid != true)
	{
		iX = PA_RandMinMax(1,4);;
		if ((iBoard[2][1] == 0) && (iX == 1))
		{
			iBoard[2][1] = 2;
			bValid = true;
		}
		else if ((iBoard[0][1] == 0) && (iX == 2))
		{	
			iBoard[0][1] = 2;
			bValid = true;
		}
		else if ((iBoard[1][0] == 0) && (iX == 3))
		{
			iBoard[1][0] = 2;
			bValid = true;
		}
		else if ((iBoard[1][2] == 0) && (iX == 4))
		{	
			iBoard[1][2] = 2;
			bValid = true;
		}
	}
}


void Game::randommove()
{
	bValid = false;
	while (bValid != true)
	{
		iX = PA_RandMinMax(0,2);
		iY = PA_RandMinMax(0,2);
		if ((iX > 2) || (iY > 2) || (iX < 0) || (iY < 0))
		{
			bValid = false;
		}
		else if (iBoard[iX][iY] == 0)
		{
			bValid = true;
		}
		else
		{
			bValid = false;
		}
	}
		iBoard[iX][iY] = 2;
}
void Game::movecorner()
{
	bValid = false;
	while (bValid != true)
	{
		iX = PA_RandMinMax(1,5);;
		if ((iBoard[0][0] == 0) && (iX == 1))
		{
			iBoard[0][0] = 2;
			bValid = true;
		}
		else if ((iBoard[2][0] == 0) && (iX == 2))
		{	
			iBoard[2][0] = 2;
			bValid = true;
		}
		else if ((iBoard[0][2] == 0) && (iX == 3))
		{
			iBoard[0][2] = 2;
			bValid = true;
		}
		else if ((iBoard[2][2] == 0) && (iX == 4))
		{	
			iBoard[2][2] = 2;
			bValid = true;
		}
		else if ((iBoard[1][1] == 0) && (iX == 5))
		{	
			iBoard[1][1] = 2;
			bValid = true;
		}
	}
}


int main(void)	{

	// PAlib Inits
	PA_Init();
	PA_InitVBL();
	PA_InitText(1,1);
	PA_InitText(0,1);
	Game g;
	
	PA_LoadSpritePal(0, 0, (void*)oneplayer_Pal);
	PA_LoadSpritePal(0, 1, (void*)twoplayer_Pal);
	PA_LoadSpritePal(0, 2, (void*)spot_Pal);
	
	PA_LoadSpritePal(0, 3, (void*)veryeasy_Pal);
	PA_LoadSpritePal(0, 4, (void*)easy_Pal);
	PA_LoadSpritePal(0, 5, (void*)normal_Pal);
	PA_LoadSpritePal(0, 6, (void*)hard_Pal);
	PA_LoadSpritePal(0, 7, (void*)impossible_Pal);
	
	PA_LoadSpritePal(0, 8, (void*)again_Pal);
	PA_LoadSpritePal(0, 9, (void*)titlescreen_Pal);
	
	PA_CreateSprite(0, 0,(void*)oneplayer_Sprite, OBJ_SIZE_64X32,1, 0, 32, 100);
	PA_CreateSprite(0, 1,(void*)twoplayer_Sprite, OBJ_SIZE_64X32,1, 1, 160, 100);
	
	PA_CreateSprite(0, 2,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 45, 17);
	PA_CreateSprite(0, 3,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 98, 17);
	PA_CreateSprite(0, 4,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 151, 17);
	
	PA_CreateSprite(0, 5,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 45, 68);
	PA_CreateSprite(0, 6,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 98, 68);
	PA_CreateSprite(0, 7,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 151, 68);
	
	PA_CreateSprite(0, 8,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 45, 119);
	PA_CreateSprite(0, 9,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 98, 119);
	PA_CreateSprite(0, 10,(void*)spot_Sprite, OBJ_SIZE_64X64,1, 2, 151, 119);
	
	PA_CreateSprite(0, 11,(void*)veryeasy_Sprite, OBJ_SIZE_64X32,1, 3, -64, 70);
	PA_CreateSprite(0, 12,(void*)easy_Sprite, OBJ_SIZE_64X32,1, 4, -64, 69);
	PA_CreateSprite(0, 13,(void*)normal_Sprite, OBJ_SIZE_64X32,1, 5, -64, 150);
	PA_CreateSprite(0, 14,(void*)hard_Sprite, OBJ_SIZE_64X32,1, 6, -64, 149);
	PA_CreateSprite(0, 15,(void*)impossible_Sprite, OBJ_SIZE_64X32,1, 7, -64, 110);
	
	PA_CreateSprite(0, 16,(void*)again_Sprite, OBJ_SIZE_64X32,1, 8, -64, 149);
	PA_CreateSprite(0, 17,(void*)titlescreen_Sprite, OBJ_SIZE_64X32,1, 9, -64, 110);
	
	//for (int i = 2; i < 11; i++)
	//PA_SetSpriteAnim(0,i,2);
	
	PA_SetTextTileCol(0, 9);
	
	PA_EasyBgLoad(1, 3, top);

	PA_InitRand();
	while (1)
	{
	   
   	PA_EasyBgLoad(0, 3, bottom);
   	
//		PA_OutputText(0,5,1,"*****Tic Tac Toe*****\n");
		PA_OutputText(0,5,2,"Programmed by GeekyLink\n");
		PA_OutputText(0,6,3,"Beta tested by Kori\n");
		PA_OutputText(0,7,4,"Graphics by Kori\n");
		PA_OutputText(0,8,8,"Select game mode:\n");
		
		PA_OutputText(0,5,23,"http://gekinzuku.com               ");
		
		PA_SetSpriteXY(0,0,32,100);
		PA_SetSpriteXY(0,1,160,100);
		
		//Player Select
	
		int iTemp = 0;
		
		PA_WaitForVBL();
		
		while(iTemp == 0)
		{
		   if (Stylus.Newpress)
		   {
			   if (PA_SpriteTouched(0))iTemp = 1;
			   else if (PA_SpriteTouched(1))iTemp = 2;
			}			
			   
			   PA_WaitForVBL();
		}		

		bTitle = false;
				
		iPlayers = iTemp;
		
		PA_ClearTextBg(0);
		PA_SetSpriteY(0,0,-64);
		PA_SetSpriteY(0,1,-64);
		
		// If one player game mode, then pick difficulty
		
		if (iPlayers == 1)
		{
			PA_OutputText(0,1,1,"Select Difficulty:");

			PA_SetSpriteX(0,11,32);
			PA_SetSpriteX(0,12,156);
			PA_SetSpriteX(0,13,32);
			PA_SetSpriteX(0,14,156);
			PA_SetSpriteX(0,15,94);
			
			PA_WaitForVBL();
			
			iDifficulty = 0;
			while(iDifficulty == 0) 
			{ 
			   if (Stylus.Newpress)
			   {
					if (PA_SpriteTouched(11)) iDifficulty = 1;
					if (PA_SpriteTouched(12)) iDifficulty = 2;
					if (PA_SpriteTouched(13)) iDifficulty = 3;
					if (PA_SpriteTouched(14)) iDifficulty = 4;
					if (PA_SpriteTouched(15)) iDifficulty = 5;
				}			
				PA_WaitForVBL();
			}
			
			for (int iR = 11; iR < 16; iR++)PA_SetSpriteX(0,iR,-64);
			
			PA_OutputText(0,1,1,"                   ");
			iPlayer = 1;
		}

		//goes to gameplay
		PA_EasyBgLoad(0, 3, board);

		if (iPlayers == 2)
		{
			while (!bTitle)
			{
				g.checkwin();				
				g.drawboard();
				g.checkstale();
				
				if(bTitle) break;
				
				g.getmove();
			}
		}
		else if (iPlayers == 1)
		{
			while (!bTitle)
			{
				g.checkwin();				
				g.drawboard();
				g.checkstale();
				
				if(bTitle) break;

				if (iPlayer == 1)
				{
					g.getmove();
					iPlayer = 2;
				}
				else
				{
					if (iDifficulty == 1)
						g.AI1();
					else if (iDifficulty == 2)
						g.AI2();
					else if (iDifficulty == 3)
						g.AI3();
					else if (iDifficulty == 4)
						g.AI4();
					else if (iDifficulty == 5)
						g.AI5();
					iPlayer = 1;
				}
			}
		}
	}
	return 0;
}
