
#include "MainEngine.h"
#include <iostream.h>  // I/O 
#include <fstream.h>   // file I/O
#include <cstdio>


//=====================================================================================



void Object::Spawn(void)
{
	int xx, yy;
	Object *tile = GameMap[this->tileX][this->tileY][GERM_LAYER];

	// Check Surrounding
		xx = this->tileX + 1;
		yy = this->tileY;

		if (!Exsists(xx, yy, GERM_LAYER) && !Exsists(xx,yy,WALL_LAYER))
		{
			GameMap[xx][yy][GERM_LAYER] = new Object(xx,yy);
			GameMap[xx][yy][GERM_LAYER]->type = GERM;
		}

		//----------------------------------------

		xx = this->tileX - 1;
		yy = this->tileY;

		if (!Exsists(xx, yy, GERM_LAYER) && !Exsists(xx,yy,WALL_LAYER))
		{
			GameMap[xx][yy][GERM_LAYER] = new Object(xx,yy);
			GameMap[xx][yy][GERM_LAYER]->type = GERM;
		}

		//----------------------------------------

		xx = this->tileX;
		yy = this->tileY + 1;

		if (!Exsists(xx, yy, GERM_LAYER) && !Exsists(xx,yy,WALL_LAYER))
		{
			GameMap[xx][yy][GERM_LAYER] = new Object(xx,yy);
			GameMap[xx][yy][GERM_LAYER]->type = GERM;
		}

		//----------------------------------------

		xx = this->tileX;
		yy = this->tileY - 1;

		if (!Exsists(xx, yy, GERM_LAYER) && !Exsists(xx,yy,WALL_LAYER))
		{
			GameMap[xx][yy][GERM_LAYER] = new Object(xx,yy);
			GameMap[xx][yy][GERM_LAYER]->type = GERM;
		}

		//----------------------------------------

	//}

}











void increment_speed_counter()
{
	frameCounter++;
} END_OF_FUNCTION(increment_speed_counter);



void MainGameEngine()
{
	char filename[10];
	int t;

	offsetX = (320 - (340.0/2.0));
	offsetY = (240 - (340.0/2.0));

	LOCK_VARIABLE(frameCounter);
	LOCK_FUNCTION(increment_speed_counter);

	install_int_ex(increment_speed_counter, BPS_TO_TIMER(100));
//	install_int_ex(increment_speed_counter, SECS_TO_TIMER(1));


	//-----------------------------------------

	//=Load Main Graphics

		LoadImage(levelBack, "media\\gameBackground.bmp");
		LoadImageStrip(wall, "media\\wall.bmp", 20, 30, 0, 16);
		LoadImageStrip(virus, "media\\virus.bmp", 20, 20, 0, 12);
		LoadImageStrip(floor, "media\\floor.bmp", 20, 20, 0, 1);
		LoadImageStrip(ship, "media\\ship.bmp", 20, 20, 0, 4);
		LoadImage(readyImage, "media\\ready.bmp");

	//=End Loading of main graphics


	for (int m=1; m<11; m++)
	{

		sprintf(filename, "map%i.txt",m);
		LoadMap(filename);
	

		//------------------------------------------
		clear_to_color(buffer, makecol(0,0,0));
		DrawImage(levelBack, offsetX, offsetY);
		DrawMap();
		//textprintf_centre(buffer, font, offsetX + 170, offsetY + 170, makecol(255,255,255), "GET READY!!");

		DrawImage(readyImage, offsetX + 100, offsetY + 150);

		blit( buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

		t = clock();
		while (clock() < t + 2000) { }

		ResetGermTimes();

		//------------------------------------------

		timeTakenLevel = 0;
		scoreLevel = 0;

		t=clock();

		germInPlay =true;


		while (germInPlay == true)
		{
			while (frameCounter > 0)
			{
				UpdateShip();
				UpdateMap();
				frameCounter--;
				timeTakenLevel = int(clock() - t)/1000;
			}

			clear_to_color(buffer, makecol(0,0,0));
			DrawImage(levelBack, offsetX, offsetY);
			DrawMap();

			textprintf_centre(buffer, font, offsetX + 170, offsetY + 4, makecol(255,255,255), "Level %i", m);

			textprintf(buffer, font, offsetX + 10, offsetY + 327, makecol(255,255,255), "Score: %i", scoreLevel);
			textprintf(buffer, font, offsetX + 220, offsetY + 327, makecol(255,255,255), "Time: %i", timeTakenLevel);


			blit( buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

			if (key[KEY_ESC]) germInPlay = false;
			if (key[KEY_F1]) { germInPlay = false; m = 10;}
		
		}

	}

}

//============================================================================================

void LoadImageStrip(BITMAP **_images, char *_filename, int _width, int _height, int _start, int _count)
{
	//BITMAP *image[20];
	BITMAP *temp = load_bitmap(_filename,0);

	for (int i=0; i<_count; i++)
	{
		_images[i] = create_bitmap(_width, _height);
		blit(temp, _images[i], (i+_start)*_width, 0, 0, 0, _width, _height);
	}

	destroy_bitmap(temp);

}

//------------------------------------------------------------------------------

void LoadImage(BITMAP *&_image, char *_filename)
{
	_image = load_bitmap(_filename,0);
}

//------------------------------------------------------------------------------

void DrawImage(BITMAP *_image, int _x, int _y)
{
	masked_blit(_image, buffer, 0, 0, _x, _y, _image->w, _image->h);
}

//------------------------------------------------------------------------------

void LoadMap(char *_filename)
{
	ifstream fileIn;
	int x, y, k;
	char next;

	// Set Array pointers to null just incase
	 for (x=0; x<14; x++)
		for (y=0; y<14; y++)
			for (k=1; k<4; k++)
			{
				delete GameMap[x][y][k];
				GameMap[x][y][k] = NULL;
			}

	fileIn.open(_filename);


	//x=0; y=0;
	for (y=0; y<15; y++)
		for (x=0; x<15; x++)
		{
			fileIn >> next;

		//	switch(next)
		//	{
			//	case "1": 
			if (next == '1')
			{
					GameMap[x][y][WALL_LAYER] = new Object();
					GameMap[x][y][WALL_LAYER]->type = WALL;
					
			} else if (next == '2') {

					GameMap[x][y][GERM_LAYER] = new Object(x,y);
					GameMap[x][y][GERM_LAYER]->type = GERM;
					
			} else if (next == '3') {
					shipObject = new Object(x, y);
					shipTileX = x; shipTileY = y;
					shipObject->type = PLAYER;
					GameMap[x][y][SHIP_LAYER] = shipObject;

			} else {

			}


			//GameMap[i][j][k] = NULL;
		}
		

	fileIn.close();

	FormatWalls();

	//CreateWalls();
	//CreateGerms();

}

//------------------------------------------------------------------------------

void CreateWalls(void)
{
	int i, x, y;

	// Setup the 4 bounding walls
	for (i=0; i<15; i++)
	{
		if (GameMap[i][0][WALL_LAYER] == NULL)  GameMap[i][0][WALL_LAYER] = new Object();
		if (GameMap[i][14][WALL_LAYER] == NULL) GameMap[i][14][WALL_LAYER] = new Object();
		if (GameMap[0][i][WALL_LAYER] == NULL)  GameMap[0][i][WALL_LAYER] = new Object();
		if (GameMap[14][i][WALL_LAYER] == NULL) GameMap[14][i][WALL_LAYER] = new Object();
	}


	for (i=0; i<50; i++)
	{
		x = rand() % 13;
		y = rand() % 13;

		if (GameMap[x][y][WALL_LAYER] == NULL)
		{
			GameMap[x][y][WALL_LAYER] = new Object();
			GameMap[x][y][WALL_LAYER]->type = WALL;
		}

	}

	FormatWalls();


}

//------------------------------------------------------------------------------

void FormatWalls(void)
{
	int frame = 0;
	
	for (int i=0; i<15; i++)
		for (int j=0; j<15; j++)
		{
			if (GameMap[i][j][1] != NULL)
			{
				if (j > 0)  if (GameMap[i][j-1][WALL_LAYER] != NULL) frame+=1;
				if (i < 14) if (GameMap[i+1][j][WALL_LAYER] != NULL) frame+=2;
				if (j < 14) if (GameMap[i][j+1][WALL_LAYER] != NULL) frame+=4;
				if (i > 0)  if (GameMap[i-1][j][WALL_LAYER] != NULL) frame+=8;

				GameMap[i][j][WALL_LAYER]->frame = frame;
				GameMap[i][j][WALL_LAYER]->type = WALL;

				frame = 0;
			}
		}


}

//------------------------------------------------------------------------------

void DrawMap(void)
{
	int tileX, tileY;
	
	for (int k=3; k>0; k--)
		for (int i=0; i<15; i++)
		{
			for (int j=0; j<15; j++)
			{
				tileX = offsetX + 20 + i*20;
				tileY = offsetY + 20 + j*20;			
				
				if (GameMap[i][j][k] != NULL) // tile exsists here
				{
					Object *tile = GameMap[i][j][k];

					switch (tile->type)
					{
						case WALL:
							DrawImage(wall[ tile->frame ], tileX, tileY-10);
						break;

						case GERM:
							//tile->Animate();

							DrawImage(virus[ tile->frame ], tileX, tileY);
						break;

						case PLAYER:
							DrawImage(ship[shipDir], tileX + shipX, tileY + shipY);
						break;

					}

				}

			}

		}
	

}

//------------------------------------------------------------------------------

void CreateGerms(void)
{
	int i, x, y;

	for (i=0; i<7; i++)
	{
		x = rand() % 13;
		y = rand() % 13;

		if ((GameMap[x][y][WALL_LAYER] == NULL) && (GameMap[x][y][GERM_LAYER] == NULL))
		{
			GameMap[x][y][GERM_LAYER] = new Object(x, y);
			GameMap[x][y][GERM_LAYER]->type = GERM;
			//GameMap[x][y][GERM_LAYER]->SetAnim(0, 8, 11, 300);
		} else {
			i--;
		}

	}


}

//------------------------------------------------------------------------------

void UpdateMap(void)
{
	int x,y,z;

	germInPlay = false;

	for (x=0; x<14; x++)
		for (y=0; y<15; y++)
			for (z=1; z<4; z++)
			{
				Object *tile = GameMap[x][y][z];
				if (tile != NULL) // tile exsists
				{
					switch(tile->type)
					{
						case GERM:
							
							tile->Animate();
							tile->Update();
							germInPlay = true;

						break;

					}

				}

			}


}

//------------------------------------------------------------------------------

bool Exsists(int x, int y, int l)
{
	if (GameMap[x][y][l] != NULL) return true;
	return false;
}

//------------------------------------------------------------------------------

void UpdateShip(void)
{

	if (shipMoving == false) // ship can now pick a new direction
	{

		if (key[KEY_DOWN])
		{
			if (!Exsists(shipTileX, shipTileY + 1, WALL_LAYER)) // down is clear
			{
				shipDir = 0;
				shipTravel = 20;
				shipMoving = true;
				shipY = -20;
				GameMap[shipTileX][shipTileY][SHIP_LAYER] = NULL;
				GameMap[shipTileX][shipTileY+1][SHIP_LAYER] = shipObject;
			}
		} else if (key[KEY_UP]) {

			if (!Exsists(shipTileX, shipTileY - 1, WALL_LAYER)) // up is clear
			{
				shipDir = 2;
				shipTravel = 20;
				shipMoving = true;
				shipY = 20;
				GameMap[shipTileX][shipTileY][SHIP_LAYER] = NULL;
				GameMap[shipTileX][shipTileY-1][SHIP_LAYER] = shipObject;
			}
		} else if (key[KEY_LEFT]) {

			if (!Exsists(shipTileX - 1, shipTileY, WALL_LAYER)) // left is clear
			{
				shipDir = 3;
				shipTravel = 20;
				shipMoving = true;
				shipX = 20;
				GameMap[shipTileX][shipTileY][SHIP_LAYER] = NULL;
				GameMap[shipTileX-1][shipTileY][SHIP_LAYER] = shipObject;
			}
		} else if (key[KEY_RIGHT]) {
			if (!Exsists(shipTileX + 1, shipTileY, WALL_LAYER)) // right is clear
			{
				shipDir = 1;
				shipTravel = 20;
				shipMoving = true;
				shipX = -20;
				GameMap[shipTileX][shipTileY][SHIP_LAYER] = NULL;
				GameMap[shipTileX+1][shipTileY][SHIP_LAYER] = shipObject;
			}
		}

		//--------------------------------------

	}
	
	if (shipMoving == true)
	{ // is moving

		if (shipTravel > 0)
		{
			switch(shipDir)
			{
				case 0: shipY++; break;
				case 1: shipX++; break;
				case 2: shipY--; break;
				case 3: shipX--; break;
			}

			shipTravel--;

			if (shipTravel == 0) // movement ended
			{
				shipX = 0;
				shipY = 0;

				switch(shipDir)
				{
					case 0: shipTileY++; break;
					case 1: shipTileX++; break;
					case 2: shipTileY--; break;
					case 3: shipTileX--; break;
				}

				shipObject->tileX = shipTileX;
				shipObject->tileY = shipTileY;

				CheckForVirus(shipTileX, shipTileY);

				shipMoving = false;
			}

		}

	}


}

//------------------------------------------------------------------------------

void ResetGermTimes(void)
{
	for (int i=0; i<15; i++)
		for (int j=0; j<15; j++)
			if (Exsists(i,j,GERM_LAYER)) 
				GameMap[i][j][GERM_LAYER]->spawnLastTime = clock() + (rand() % 1000);

}

//------------------------------------------------------------------------------

void CheckForVirus(int x, int y)
{
	if (Exsists(x,y,GERM_LAYER))
	{
		delete GameMap[x][y][GERM_LAYER];
		GameMap[x][y][GERM_LAYER] = NULL;
		scoreLevel += 10;
	}

}

//------------------------------------------------------------------------------