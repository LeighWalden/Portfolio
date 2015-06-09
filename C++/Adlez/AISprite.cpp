#include "AISprite.h"
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

CAISprite::CAISprite() {

	CSprite::CSprite();

	m_speed = 0;
	m_bmoving = false;
	m_bWALK_PRIMARY = false;
	m_bWALK_DIAGONALLY = false;
	m_bSTAND_PRIMARY = false;
	m_bSTAND_DIAGONALLY = false;
	m_bSWING_PRIMARY = false;
	m_bSWING_DIAGONALLY = false;

	for (int i=0;i<MAXKEYWORD;i++) {
		m_banimationDirection[i] = false;
		m_animationID[i] = 0;
	}

	m_pathPoints = 0; 
	m_currentTargetpath = -1;

}

CAISprite::~CAISprite() {


}

bool CAISprite::initialise(const char filename[]) {

	if (m_binitialised) {
		allegro_message("Sprite object can not be initialised twice");
		return false;
	}


	ifstream infile;

	infile.open(filename);
	if (!infile.is_open()) {
		allegro_message("Unable to open initialisation file");
		return false;
	}

	char buf[1024];

	infile.getline(buf,1024,'\n');
	if (strcmp(buf,"AI Sprite Data File")) {
		allegro_message("The supplied file is not a sprite data file");
		infile.close();
		return false;
	}

	bool keep_reading = true;
	while (keep_reading) {
		infile.getline(buf,1024,'\n');
		if ((buf[0]!='#')&&(buf[0]!=NULL))
			keep_reading = false;
	}

	if (infile.eof()) {
		allegro_message("The file contains no number of states");
		infile.close();
		return false;
	}

	m_numberofState = atoi(buf);
	if (m_numberofState<=0) {
		allegro_message("The file contains negative number of states");
		infile.close();
		return false;
	}

	m_spriteImage = new BITMAP**[m_numberofState];
	if (m_spriteImage==NULL) {

		allegro_message("The program failed to allocate memory to hold sprite images (level 1)");
		infile.close();
		return false;

	}

	m_totalAnimationframes = new int[m_numberofState];
	if (m_totalAnimationframes==NULL) {
		allegro_message("The program failed to allocate memory to hold total animation frames");
		delete m_spriteImage;
		m_spriteImage = NULL;
		infile.close();
		return false;
	}

	m_spriteWidths = new int[m_numberofState];
	if (m_spriteWidths==NULL) {
		allegro_message("The program failed to allocate memory to hold total animation frames");

		delete m_spriteImage;
		m_spriteImage = NULL;

		delete m_totalAnimationframes;
		m_totalAnimationframes = NULL;

		infile.close();
		return false;
	}

	m_spriteHeights = new int[m_numberofState];
	if (m_spriteHeights==NULL) {
		allegro_message("The program failed to allocate memory to hold total animation frames");

		delete m_spriteImage;
		m_spriteImage = NULL;
		
		delete m_totalAnimationframes;
		m_totalAnimationframes = NULL;

		delete m_spriteWidths;
		m_spriteWidths = NULL;

		infile.close();
		return false;
	}

	for (int i=0;i<m_numberofState;i++) {
		keep_reading = true;
		while (keep_reading) {
			infile.getline(buf,1024,'\n');
			if ((buf[0]!='#')&&(buf[0]!=NULL))
				keep_reading = false;
		}

		if (infile.eof()) {
			allegro_message("Unexpected end of files encountered");
				
			delete m_totalAnimationframes;
			m_totalAnimationframes = NULL;

			delete m_spriteWidths;
			m_spriteWidths = NULL;

			int imax=i;

			for (int j=0;j<imax;j++) {
				delete m_spriteImage[j];
				m_spriteImage[j] = NULL;
			}
			
			delete m_spriteImage;
			m_spriteImage = NULL;

			infile.close();
			return false;
		}

		BITMAP *temp = load_bitmap(buf,0);
		if (temp==NULL) {
			allegro_message("Unable to load a sprite image");
				
			delete m_totalAnimationframes;
			m_totalAnimationframes = NULL;

			delete m_spriteWidths;
			m_spriteWidths = NULL;

			int imax=i;

			for (int j=0;j<imax;j++) {
				delete m_spriteImage[j];
				m_spriteImage[j] = NULL;
			}

			delete m_spriteImage;
			m_spriteImage = NULL;

			infile.close();
			return false;
		}

		infile.getline(buf,1024,' ');
		m_spriteWidths[i] = atoi(buf);

		infile.getline(buf,1024,' ');
		m_spriteHeights[i] = atoi(buf);

		infile.getline(buf,1024,'\n');
		m_totalAnimationframes[i] = atoi(buf);

		infile.getline(buf,1024,'\n');
		bool success = false;
		int j = 0;
		for (j=0;j<MAXKEYWORD;j++) {
			if (!strcmp(buf,AnimationKeyword[j])) {
				if (m_banimationDirection[j])
					allegro_message("Warning, this keyword has been used before");
				m_banimationDirection[j] = true;
				m_animationID[j] = i;
				success = true;
				break;
			}
		}

		if (!success)
			m_animationID[i] = 0;

		m_spriteImage[i] = new BITMAP*[m_totalAnimationframes[i]];

		if (m_spriteImage[i] == NULL) {
			allegro_message("The program failed to allocate memory to hold total animation frames");
		
			delete m_totalAnimationframes;
			m_totalAnimationframes = NULL;

			delete m_spriteWidths;
			m_spriteWidths = NULL;

			int imax=i+1;

			for (int j=0;j<imax;j++) {
				delete m_spriteImage[j];
				m_spriteImage[j] = NULL;
			}

			delete m_spriteImage;
			m_spriteImage = NULL;

			destroy_bitmap(temp);

			infile.close();
			return false;
		}

		for (j=0; j<m_totalAnimationframes[i]; j++) {

			m_spriteImage[i][j] = create_bitmap(m_spriteWidths[i], m_spriteHeights[i]);
			blit(temp, m_spriteImage[i][j], j*m_spriteWidths[i], 0, 0, 0, m_spriteWidths[i], m_spriteHeights[i]);

		}

		destroy_bitmap(temp);
	}

	infile.close();

	if (!(m_banimationDirection[0]&&m_banimationDirection[2]&&m_banimationDirection[4]&&m_banimationDirection[6])) {
		allegro_message("You failed to provide at least 4 PRIMARY MOVEMENT ANIMATION");
	
		delete m_totalAnimationframes;
		m_totalAnimationframes = NULL;

		delete m_spriteWidths;
		m_spriteWidths = NULL;

		for (int j=0;j<m_numberofState;j++) {
			delete m_spriteImage[j];
			m_spriteImage[j] = NULL;
		}

		delete m_spriteImage;
		m_spriteImage = NULL;

		infile.close();
		return false;
	}


	m_currentAnimationframe = 0;

	m_currentTargetpath = -1;
	m_pathPoints = 0;

	m_currentState = 0;

	m_xpos = 0;
	m_ypos = 0;

	m_binitialised = true;

	m_speed = 2;

	infile.close();
	
	return true;

}


void CAISprite::spawn(int state, int lifespan, int xpos, int ypos, int speedx, int speedy) {

	CSprite::spawn(state, lifespan, xpos, ypos, speedx, speedy);

	if (abs(m_speedx) > abs(m_speedy))
		m_speed = abs(m_speedx);
	else
		m_speed = abs(m_speedy);

}


void CAISprite::moveTo(int xworld, int yworld) {

	if (!m_binitialised)
		return;

	int dx = xworld-m_xpos;
	int dy = yworld-m_ypos;
	int adx = abs(dx);
	if (adx>m_speed)
		adx=m_speed;
	int ady = abs(dy);
	if (ady>m_speed)
		ady=m_speed;

	double pi = 2*acos(0.0);
	double div8 = pi/4;
	double div4 = pi/2;

	double angle = atan2((float)dy,(float)dx)+pi/2;

	int div = (int)(angle/div8);
	if (div<0)
		div+=8;
	else if (div>=8)
		div-=8;

	if (m_banimationDirection[div]) {
		int state = m_animationID[div];
		setSpriteState(state);
		int newxpos = m_xpos+MoveDirectionx[div]*adx;
		int newypos = m_ypos+MoveDirectiony[div]*ady;
		setpos(newxpos,newypos);
	} else {
		div = (int)(angle/div4);
		if (div<0)
			div+=4;
		else if (div>=4)
			div-=4;
		div=div*2;

		if (m_banimationDirection[div]) {
			int state = m_animationID[div];
			setSpriteState(state);
			int newxpos = m_xpos+MoveDirectionx[div]*adx;
			int newypos = m_ypos+MoveDirectiony[div]*ady;
			setpos(newxpos,newypos);
		}
	}

	return;

}


bool CAISprite::findPathto(int xworld, int yworld, CPathFinder* pathfinder) {

	if (!m_binitialised)
		return false;

	if (pathfinder->findPath(m_xpos, m_ypos, xworld, yworld, m_pathx, m_pathy, &m_pathPoints)) {

		m_currentTargetpath = m_pathPoints-1;

		followPath();

		return true;

	} else

		return false;

}


int CAISprite::updatePos() {

	if (!m_binitialised)
		return 0;

	if (m_currentTargetpath==-1)
		return -1;

	if (m_pathPoints<=0)
		return -1;

	// return -1 for no target

	return followPath(); // 1 for target reached or 2 otherwise

}

		
int CAISprite::followPath() {

	if (!m_binitialised)
		return 0;

	bool reachedtarget = false;

	if (m_pathPoints>0) {
		if (m_currentTargetpath>=0) {

			int dx = m_pathx[m_currentTargetpath]-m_xpos;
			int dy = m_pathy[m_currentTargetpath]-m_ypos;

			int adx = abs(dx);
			int ady = abs(dy);

			if ((adx<m_speed)&&(ady<m_speed)) {
				if (m_currentTargetpath>0) {
					// Move to the next target
					m_currentTargetpath--;
					dx = m_pathx[m_currentTargetpath]-m_xpos;
					dy = m_pathy[m_currentTargetpath]-m_ypos;

					adx = abs(dx);
					ady = abs(dy);
				} else {
					// reached target
					reachedtarget = true;
					m_currentTargetpath = -1;
					m_pathPoints = 0;
				}

			}

			if (adx>m_speed)
				adx=m_speed;
			if (ady>m_speed)
				ady=m_speed;

			double pi = 2*acos(0.0);
			double div8 = pi/4;
			double div4 = pi/2;

			double angle = atan2((float)dy,(float)dx)+pi/2;

			int div = (int)(angle/div8);
			if (div<0)
				div+=8;
			else if (div>=8)
				div-=8;

			if (m_banimationDirection[div]) {
				int state = m_animationID[div];
				setSpriteState(state);
				int newxpos = m_xpos+MoveDirectionx[div]*adx;
				int newypos = m_ypos+MoveDirectiony[div]*ady;
				setpos(newxpos,newypos);
			} else {
				div = (int)(angle/div4);
				if (div<0)
					div+=4;
				else if (div>=4)
					div-=4;
				div=div*2;

				if (m_banimationDirection[div]) {
					int state = m_animationID[div];
					setSpriteState(state);
					int newxpos = m_xpos+MoveDirectionx[div]*adx;
					int newypos = m_ypos+MoveDirectiony[div]*ady;
					setpos(newxpos,newypos);
				}
			}

		}
	}

	if (reachedtarget)
		return 1;
	else
		return 2;

}




