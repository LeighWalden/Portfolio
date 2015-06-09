
#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>
#include <ctime>
#include "allegro.h"


enum ObjectType { WALL, FLOOR, MOVING, GERM, PLAYER };



class Object
{
	public:

		int tileX, tileY;
		int frame;
		ObjectType type;
		int frameDelay;
		int frameLastTime;
		int frameTotal;
		int frameStart;

		// Germ Variables, because inheritance was not working!!!!!
		int spawnDelay;
		int spawnLastTime;

		//-------------------------------------------------------------------

		Object();
		Object(int x, int y);
		void SetAnim(int _frame, int _startFrame, int _totalFrame, int _delay);
		~Object();

		void Animate(void);
		void Update(void);
		void Spawn(void);


		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

};



#endif