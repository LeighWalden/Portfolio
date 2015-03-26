#include <string>
#include <fstream>
#include "Sprite.h"

using namespace std;

CSprite::CSprite() {

	m_spriteImage = NULL;
	m_totalAnimationframes = NULL;
	m_spriteWidths = NULL;
	m_spriteHeights = NULL;
	m_numberofState = 0;
	m_binitialised = false;
	m_bdisplaytext = false;
	m_alive = false;

}

CSprite::~CSprite() {

	if (m_binitialised) {
		if ((m_spriteImage!=NULL)&&(m_totalAnimationframes!=NULL)) {
			for (int i=0;i<m_numberofState;i++) {
				if (m_spriteImage[i]!=NULL) {
					for (int j=0;j<m_totalAnimationframes[i];j++) {
						if (m_spriteImage[i][j]!=NULL) {
							destroy_bitmap(m_spriteImage[i][j]);
							m_spriteImage[i][j] = NULL;
						}
					}

					delete m_spriteImage[i];
					m_spriteImage[i] = NULL;

				}
			}

			delete m_spriteImage;
			m_spriteImage = NULL;

			delete m_totalAnimationframes;

		}

		if (m_spriteWidths != NULL) {
			delete m_spriteWidths;
			m_spriteWidths = NULL;
		}

		if (m_spriteHeights != NULL) {
			delete m_spriteHeights;
			m_spriteHeights = NULL;
		}
	}

	m_totalAnimationframes = 0;

	m_binitialised = false;


}

void CSprite::drawSprite(BITMAP* buffer, CBackground *bkground) {

	if (!m_binitialised) {

		return;

	}

	int topborder, leftborder, bottomborder, rightborder;

	bkground->getVisibleborder(&topborder, &leftborder, &bottomborder, &rightborder);

	if ((m_xpos+m_spriteWidths[m_currentState]/2<leftborder)||(m_xpos-m_spriteWidths[m_currentState]/2>rightborder)||(m_ypos+m_spriteHeights[m_currentState]/2<topborder)||(m_ypos-m_spriteHeights[m_currentState]/2>bottomborder))
		return;

	int xscreenpos, yscreenpos;
	double dx, dy;

	bkground->getScreencoordinate(m_xpos, m_ypos, &xscreenpos, &yscreenpos);
	bkground->getScreentoWindowRatio(&dx, &dy);

	masked_stretch_blit(m_spriteImage[m_currentState][m_currentAnimationframe], buffer, 0, 0, m_spriteWidths[m_currentState], m_spriteHeights[m_currentState], xscreenpos-m_spriteWidths[m_currentState]/2*dx, yscreenpos-m_spriteHeights[m_currentState]/2*dy, m_spriteWidths[m_currentState]*dx, m_spriteHeights[m_currentState]*dy);

	if (m_bdisplaytext)
		textout_centre(buffer,font,m_text,xscreenpos, yscreenpos-m_spriteHeights[m_currentState]/2-10, makecol(255,255,255));

}


int CSprite::setSpriteState(int state) {

	if (!m_binitialised) {

		return 0;

	}

	if ((state >= m_numberofState)||(state < 0)) {

		allegro_message("The supplied state is out of range");

		return 0;

	}

	if (state!=m_currentState) {
		m_currentState = state;
		m_currentAnimationframe = 0;
	}

	return 1;

}


void CSprite::incrementAnimationframe() {

	if (!m_binitialised) {

		return;

	}

	m_currentAnimationframe++;

	if (m_currentAnimationframe>=m_totalAnimationframes[m_currentState])
		m_currentAnimationframe = 0;

}

void CSprite::setpos(int xpos, int ypos) {

	m_xpos = xpos;
	m_ypos = ypos;

}

void CSprite::getpos(int* xpos, int* ypos){

	*xpos = m_xpos;
	*ypos = m_ypos;

}

bool CSprite::checkCollisionwithBackground(CBackground *bkground, int xpos, int ypos) {

	if (!m_binitialised)
		return true;

	int xcoord[4];
	int ycoord[4];

	xcoord[0] = xpos-m_spriteWidths[m_currentState]/2;
	xcoord[1] = xpos+m_spriteWidths[m_currentState]/2;
	xcoord[2] = xcoord[1];
	xcoord[3] = xcoord[0];

	ycoord[0] = ypos-m_spriteWidths[m_currentState]/2;
	ycoord[1] = ycoord[0];
	ycoord[2] = ypos+m_spriteWidths[m_currentState]/2;
	ycoord[3] = ycoord[2];

	return bkground->checkCollision(xcoord, ycoord, 4);

	/*

	(0) ----- (1)
	 |         |
	 |         |
	 |         |
	 |         |
	(3) ----- (2)

	*/

}

bool CSprite::getVertices(int* xvert, int *yvert) {

	if (!m_binitialised)
		return false;

	if (m_bdisplaytext)
		return false;

	*(xvert+0) = m_xpos-m_spriteWidths[m_currentState]/2;
	*(xvert+1) = m_xpos+m_spriteWidths[m_currentState]/2;

	*(yvert+0) = m_ypos-m_spriteWidths[m_currentState]/2;
	*(yvert+1) = m_ypos+m_spriteWidths[m_currentState]/2;

	return true;

}


bool CSprite::checkCollisionwithSprite(CSprite* sprite, int xpos, int ypos) {

	if (!m_binitialised)
		return false;

	if (m_bdisplaytext)
		return false;

	int xcoord[2];
	int ycoord[2];

	xcoord[0] = xpos-m_spriteWidths[m_currentState]/2;
	xcoord[1] = xpos+m_spriteWidths[m_currentState]/2;

	ycoord[0] = ypos-m_spriteWidths[m_currentState]/2;
	ycoord[1] = ypos+m_spriteWidths[m_currentState]/2;

	int xvert[2];
	int yvert[2];

	sprite->getVertices(xvert,yvert);

	int i;
	for (i=0;i<2;i++) {
		for (int j=0;j<2;j++) {
			if ((xvert[i]>=xcoord[0])&&(xvert[i]<=xcoord[1])&&(yvert[j]>=ycoord[0])&&(yvert[j]<=ycoord[1]))
				return true;
		}
	}

	for (i=0;i<2;i++) {
		for (int j=0;j<2;j++) {
			if ((xcoord[i]>=xvert[0])&&(xcoord[i]<=xvert[1])&&(ycoord[j]>=yvert[0])&&(ycoord[j]<=yvert[1]))
				return true;
		}
	}


	return false;



	/*

	(0) ----- (1)
	 |         |
	 |         |
	 |         |
	 |         |
	(3) ----- (2)

	*/

}

bool CSprite::hasCollidedwithSprite(CSprite* sprite) {

	if (!m_binitialised)
		return false;

	if (m_bdisplaytext)
		return false;

	int xcoord[2];
	int ycoord[2];

	xcoord[0] = m_xpos-m_spriteWidths[m_currentState]/2;
	xcoord[1] = m_xpos+m_spriteWidths[m_currentState]/2;

	ycoord[0] = m_ypos-m_spriteWidths[m_currentState]/2;
	ycoord[1] = m_ypos+m_spriteWidths[m_currentState]/2;

	int xvert[2];
	int yvert[2];

	sprite->getVertices(xvert,yvert);

	for (int i=0;i<2;i++) {
		for (int j=0;j<2;j++) {
			if ((xvert[i]>=xcoord[0])&&(xvert[i]<=xcoord[1])&&(yvert[j]>=ycoord[0])&&(yvert[j]<=ycoord[1]))
				return true;
		}
	}

	return false;



	/*

	(0) ----- (1)
	 |         |
	 |         |
	 |         |
	 |         |
	(3) ----- (2)

	*/

}


void CSprite::setPopupText(const char* text) {

	if (!m_binitialised) {

		return;

	}

	strncpy(m_text,text,256);


}



void CSprite::togglePopupText() {

	if (!m_binitialised) {

		return;

	}

	m_bdisplaytext = !m_bdisplaytext;

}
void CSprite::displayTextPopup(BITMAP* buffer, CBackground *bkground) {

	if (!m_binitialised) {

		return;

	}

	int xscreenpos, yscreenpos;

	bkground->getScreencoordinate(m_xpos, m_ypos, &xscreenpos, &yscreenpos);

	textout_centre(buffer,font,m_text,xscreenpos, yscreenpos, 0);

}

bool CSprite::initialise(const char filename[]) {

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
	if (strcmp(buf,"Sprite Data File")) {
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

		for (int j=0; j<m_totalAnimationframes[i]; j++) {

			m_spriteImage[i][j] = create_bitmap(m_spriteWidths[i], m_spriteHeights[i]);
			blit(temp, m_spriteImage[i][j], j*m_spriteWidths[i], 0, 0, 0, m_spriteWidths[i], m_spriteHeights[i]);

		}

		destroy_bitmap(temp);
	}

	infile.close();

	m_currentAnimationframe = 0;

	m_currentState = 0;

	m_xpos = 0;
	m_ypos = 0;

	m_binitialised = true;
	infile.close();
	
	return true;

}


void CSprite::spawn(int state, int lifespan, int xpos, int ypos, int speedx, int speedy) {

	setSpriteState(state);
	m_lifespan = lifespan;
	m_speedx = speedx;
	m_speedy = speedy;

	m_xpos = xpos;
	m_ypos = ypos;

	m_alive = true;

}


void CSprite::updatepos() {

	m_xpos += m_speedx;
	m_ypos += m_speedy;

	if (m_lifespan!=999999)
		m_lifespan--;

	if (m_lifespan < 0)
		m_alive = false;


}


void CSprite::despawn() {

	m_lifespan = 0;
	m_alive = false;


}

void CSprite::getspeed(int* xspeed, int* yspeed) {

	*xspeed = m_speedx;
	*yspeed = m_speedy;

}


void CSprite::setSpeed(int xspeed, int yspeed) {

	m_speedx = xspeed;
	m_speedy = yspeed;

}
