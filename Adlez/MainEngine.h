
#ifndef MAINENGINE_H
#define MAINENGINE_H

#define WALL_LAYER		1
#define SHIP_LAYER		2
#define GERM_LAYER		3


//---------------------------------------------


#include "Object.h"

//---------------------------------------------
// Variables
//---------------------------------------------


extern BITMAP *buffer;

Object *GameMap[15][15][5];
BITMAP *wall[16];
BITMAP *levelBack;
BITMAP *virus[12];
BITMAP *floor[2];
BITMAP *ship[4];
Object *shipObject;
BITMAP *readyImage;

int offsetX = 20;
int offsetY = 20;
bool shipMoving = false;
int shipDir = 0;
int shipX = 0;
int shipY = 0;
int shipTileX = 1;
int shipTileY = 1;
int shipTravel = 0;

int timeTakenLevel = 0;
int scoreLevel = 0;
int scoreOverall = 0;
int timeTakenOverall = 0;

bool germInPlay = true;


volatile int frameCounter = 0;

//---------------------------------------------

void LoadImage(BITMAP *&_image, char *_filename);
void LoadImageStrip(BITMAP **_images, char *_filename, int _width, int _height, int _start, int _count);
void DrawImage(BITMAP *_image, int _x, int _y);
void MainGameEngine(void);
void LoadMap(char *_filename);
void DrawMap(void);
void FormatWalls(void);

void CreateWalls(void);
void CreateGerms(void);

void UpdateMap(void);
void increment_speed_counter(void);
bool Exsists(int x, int y, int l);

void UpdateShip(void);
void CheckForVirus(int x, int y);
void ResetGermTimes(void);


//---------------------------------------------

#endif