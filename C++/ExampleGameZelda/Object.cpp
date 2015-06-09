
#include "Object.h"
extern Object *GameMap[15][15][5];

//===================================================================

Object::Object()
{
	frame = 0;
	frameLastTime = clock();
	frameDelay = 1000;
	frameTotal = 1;

	spawnLastTime = clock();
	spawnDelay = 2000 + (rand() % 1000); 
}

//===================================================================

Object::Object(int x, int y)
{
	tileX = x;
	tileY = y;

	frame = 0;
	frameStart = 4;
	frameTotal = 8;
	frameDelay = 200 + (rand() % 100);
	spawnLastTime = clock();
	spawnDelay = 3000 + (rand() % 1000); 
}

//===================================================================

void Object::SetAnim(int _frame, int _startFrame, int _totalFrame, int _delay)
{
	frame = _frame;
	frameLastTime = clock();
	frameStart = _startFrame;
	frameDelay = _delay;
	frameTotal = _totalFrame;
}

//===================================================================

Object::~Object()
{

}

//===================================================================

void Object::Animate(void)
{
	if (frameTotal > 1)
	{
		if (clock() > (frameLastTime + frameDelay))
		{
			frame++;
			frameLastTime = clock();
		}

		if (frame == frameTotal) frame = frameStart;
	}

}

//===================================================================

void Object::Update(void)
{
	if (clock() > (spawnLastTime + spawnDelay))
	{
		Spawn();
		spawnLastTime = clock();
	}

}

//===================================================================