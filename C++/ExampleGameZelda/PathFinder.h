#ifndef INC_PATHFINDER_H
#define INC_PATHFINDER_H

#include "Background.h"
#include "Node.h"

#define MAXPATHLENGTH 1024

class CPathFinder {
protected:
	bool m_binitialised;
	unsigned char* m_grid;
	unsigned char* m_statusmap;
	int m_gridwidth, m_gridheight, m_tilewidth, m_tileheight;
	CNode** m_NodeArray;
	CNode** m_OpenList;
	int findSmallestFn();
	int m_openlistLength;
	int m_pathx[MAXPATHLENGTH];
	int m_pathy[MAXPATHLENGTH];

public:
	CPathFinder();
	~CPathFinder();
	bool initialise(CBackground* bk);
	bool findPath(int startx, int starty, int targetx, int targety, int* pathx, int* pathy, int* length);

};

#endif /* INC_PATHFINDER_H */

