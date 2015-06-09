#ifndef INC_AISPRITE_H
#define INC_AISPRITE_H

#include "Sprite.h"
#include "PathFinder.h"

#define MAXKEYWORD 32
const char AnimationKeyword[MAXKEYWORD][64] = {	"WALK_NORTH", "WALK_NORTHEAST", "WALK_EAST", "WALK_SOUTHEAST",  
												"WALK_SOUTH", "WALK_SOUTHWEST", "WALK_WEST", "WALK_NORTWEST",
												"STAND_EAST", "STAND_NORTHEAST", "STAND_NORTH", "STAND_NORTWEST", 
												"STAND_WEST", "STAND_SOUTHWEST", "STAND_SOUTH", "STAND_SOUTHEAST",
												"SWING_EAST", "SWING_NORTHEAST", "SWING_NORTH", "SWING_NORTWEST", 
												"SWING_WEST", "SWING_SOUTHWEST", "SWING_SOUTH", "SWING_SOUTHEAST"};

const int MoveDirectionx[8] = {0,1,1,1,0,-1,-1,-1};
const int MoveDirectiony[8] = {-1,-1,0,1,1,1,0,-1};

class CAISprite : public CSprite {
protected:
	int m_speed;
	bool m_bmoving;
	bool m_bWALK_PRIMARY;
	bool m_bWALK_DIAGONALLY;
	bool m_bSTAND_PRIMARY;
	bool m_bSTAND_DIAGONALLY;
	bool m_bSWING_PRIMARY;
	bool m_bSWING_DIAGONALLY;
	int m_pathx[MAXPATHLENGTH], m_pathy[MAXPATHLENGTH];
	int m_pathPoints, m_currentTargetpath;
	bool m_banimationDirection[MAXKEYWORD];
	int m_animationID[MAXKEYWORD];
	void movePath(int* xworld, int* yworld, int numberofpoints);
	int followPath();

public:
	CAISprite();
	~CAISprite();
	bool initialise(const char filename[]);
	void moveTo(int xworld, int yworld);
	bool isMoving();
	int updatePos(); // return true if is moving and not yet reached target and false if it stopped (either for reaching the target or stuck in background)
	void stopMoving();
	bool getTargetpos(int* xworld, int* yworld);
	bool findPathto(int xworld, int yworld, CPathFinder* pathfinder);
	int getCurrenttargetpath() { return m_currentTargetpath; };
	int getMovementspeed() { return m_speed; };
	void spawn(int state, int lifespan, int xpos, int ypos, int speedx, int speedy);
};

#endif /* INC_AISPRITE_H */
