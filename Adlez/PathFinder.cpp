#include "PathFinder.h"

CPathFinder::CPathFinder() {

	m_binitialised = false;
	m_grid = NULL;
	m_statusmap = NULL;
	m_gridwidth = 0;
	m_gridheight = 0; 
	m_tilewidth = 0; 
	m_tileheight = 0; 
	m_NodeArray = NULL;
	m_OpenList = NULL;

}

CPathFinder::~CPathFinder() {

	if (m_grid!=NULL)
		delete m_grid;
	m_grid = NULL;

	if (m_statusmap!=NULL)
		delete m_statusmap;
	m_statusmap = NULL;

	if (m_NodeArray!=NULL) {
		for (int i=0;i<m_gridwidth*m_gridheight;i++) {
			if (m_NodeArray[i]!=NULL) {
				delete m_NodeArray[i];
				m_NodeArray[i] = NULL;
			}
		}

		delete m_NodeArray;
		m_NodeArray=NULL;
	}

	if (m_OpenList!=NULL)
		delete m_OpenList;
	m_OpenList = NULL;

	m_gridwidth = 0;
	m_gridheight = 0; 
	m_tilewidth = 0; 
	m_tileheight = 0; 

	m_openlistLength = 0;


	m_binitialised = false;

}

bool CPathFinder::initialise(CBackground* bk) {

	if (m_binitialised) {
		allegro_message("This pathfinder can not be initialised twice");
		return false;
	}

	m_grid = bk->getCollisionGrid(&m_gridwidth, &m_gridheight, &m_tilewidth, &m_tileheight);

	if (m_grid==NULL) {
		allegro_message("Fail to allocate memory for grid");
		return false;
	}

	m_statusmap = new unsigned char[m_gridwidth*m_gridheight];
	if (m_statusmap==NULL) {
		delete m_grid;
		m_grid = NULL;
		allegro_message("Fail to allocate memory for status map");
		return false;
	}

	for (int i=0;i<m_gridwidth*m_gridheight;i++)
		m_statusmap[i]=NODENOTHING;

	m_NodeArray = new CNode*[m_gridwidth*m_gridheight];
	if (m_NodeArray==NULL) {
		delete m_grid;
		m_grid = NULL;
		delete m_statusmap;
		m_statusmap = NULL;
		allegro_message("Fail to allocate memory for status map");
		return false;
	}

	for (int y=0;y<m_gridheight;y++) {
		for (int x=0;x<m_gridwidth;x++) {
			int idx = y*m_gridwidth+x;
			m_NodeArray[idx]=new CNode();
			m_NodeArray[idx]->x=x;
			m_NodeArray[idx]->y=y;
		}
	}

	m_OpenList = new CNode*[m_gridwidth*m_gridheight];

	m_openlistLength = 0;

	m_binitialised = true;

	return true;

}

int CPathFinder::findSmallestFn() {

	if (m_binitialised) {

		unsigned int smallestFn = 100000000;
		int smallestidx;

		for (int i=0;i<m_openlistLength;i++) {
			if (smallestFn > m_OpenList[i]->Fn) {
				smallestidx = i;
				smallestFn = m_OpenList[i]->Fn;
			}
		}

		return smallestidx;

	}

	else return 0;

}

bool CPathFinder::findPath(int startxpos, int startypos, int finishxpos, int finishypos, int* pathx, int* pathy, int* length) {

	int xleft = 0;
	int yleft = 0;

	if (!m_binitialised) {
		*length = 0;
		return false;
	}

	int i;
	
	for (i=0;i<m_gridwidth*m_gridheight;i++)
		m_statusmap[i]=NODENOTHING;

	int startpointx = (startxpos-xleft)/m_tilewidth;
	int startpointy = (startypos-yleft)/m_tileheight;

	int finishpointx = (finishxpos-xleft)/m_tilewidth;
	int finishpointy = (finishypos-yleft)/m_tileheight;

	int startidx = startpointy*m_gridwidth+startpointx;
	int finishidx = finishpointy*m_gridwidth+finishpointx;

	m_statusmap[startidx] = NODESTART;
	m_statusmap[finishidx] = NODEFINISH;

	m_NodeArray[startidx]->Gn=0;

	int currentidx = startidx;
	int currentx = startpointx;
	int currenty = startpointy;

	m_openlistLength = 0;

	bool iterate = true;
	bool foundtarget = false;


	while (iterate&&!foundtarget) {

		m_statusmap[currentidx] = NODECLOSE;

		for (i=-1;i<=1;i++) {
			int y = currenty+i;
			if ((y>=0)&&(y<m_gridheight)) {
				for (int j=-1;j<=1;j++) {
					int x = currentx+j;
					if ((x>=0)&&(x<m_gridwidth)) {
						int checkidx1 = y*m_gridwidth+currentx;
						int checkidx2 = currenty*m_gridwidth+x;
						int idx = y*m_gridwidth+x;
						if ((m_statusmap[idx] != NODECLOSE)&&(m_statusmap[idx] != NODEOPEN)&&(m_grid[idx] != NODEWALL)&&(m_grid[checkidx1] != NODEWALL)&&(m_grid[checkidx2] != NODEWALL)) {
							m_NodeArray[idx]->Gn = m_NodeArray[idx]->calculateGn(m_NodeArray[currentidx]);
							m_NodeArray[idx]->Hn = m_NodeArray[idx]->calculateHn(m_NodeArray[finishidx]);
							m_NodeArray[idx]->Fn = m_NodeArray[idx]->calculateFn();
							m_NodeArray[idx]->m_parentNode = m_NodeArray[currentidx];
							if (m_statusmap[idx]!=NODEFINISH) {
								m_OpenList[m_openlistLength] = m_NodeArray[idx];
								m_statusmap[idx] = NODEOPEN;
								m_openlistLength++;
							} else
								foundtarget = true;
						} else if (m_statusmap[idx] == NODEOPEN) {
							if (m_NodeArray[idx]->calculateGn(m_NodeArray[currentidx]) < m_NodeArray[idx]->Gn) {
								m_NodeArray[idx]->Gn = m_NodeArray[idx]->calculateGn(m_NodeArray[currentidx]);
								m_NodeArray[idx]->m_parentNode = m_NodeArray[currentidx];
							}
						}
					}
				}
			}
		}

		if (!foundtarget) {

			if (m_openlistLength>0) {

				currentidx = findSmallestFn();
				currentx = m_OpenList[currentidx]->x;
				currenty = m_OpenList[currentidx]->y;

				for (i=currentidx;i<m_openlistLength;i++)
					m_OpenList[i] = m_OpenList[i+1];

				currentidx = currenty*m_gridwidth+currentx;

				m_openlistLength--;

			} else

				iterate = false;
		}

	}

	if (foundtarget) {

		iterate = true;

		currentidx = finishidx;
		currentx = finishpointx;
		currenty = finishpointy;

		int pathlength = 0;

		while (iterate) {

			m_pathx[pathlength] = currentx*m_tilewidth+xleft+m_tilewidth/2;
			m_pathy[pathlength] = currenty*m_tileheight+yleft+m_tileheight/2;

			pathlength++;
		
			if (currentidx==startidx)
				iterate = false;
			else {
				currentx = m_NodeArray[currentidx]->m_parentNode->x;
				currenty = m_NodeArray[currentidx]->m_parentNode->y;
				currentidx = currenty*m_gridwidth+currentx;
			}

		}

		for (int i=0;i<pathlength-1;i++) {
			pathx[i] = m_pathx[i];
			pathy[i] = m_pathy[i];
		}

		pathx[0] = finishxpos;
		pathy[0] = finishypos;
/*		pathx[pathlength-1] = startxpos;
		pathy[pathlength-1] = startypos;*/

		*length = pathlength-1;

		if (*length>0)
			return true;
		else
			return false;

	} else

		*length = 0;

	return true;
}
