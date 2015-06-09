#ifndef INC_SPRITE_H
#define INC_SPRITE_H

#include <allegro.h>
#include "Background.h"

class CSprite {
protected:
	BITMAP*** m_spriteImage;
	int* m_totalAnimationframes;
	int* m_spriteWidths;
	int* m_spriteHeights;
	int m_xpos, m_ypos;
	int m_currentAnimationframe;
	int m_currentState;
	int m_numberofState;
	bool m_binitialised;
	double m_dx, m_dy;
	bool m_bdisplaytext;
	char m_text[256];
	void displayTextPopup(BITMAP* buffer, CBackground *bkground);

	int m_lifespan;
	bool m_alive;
	int m_speedx, m_speedy;


public:
	CSprite();
	~CSprite();
	bool initialise(const char filename[]);
	void drawSprite(BITMAP* buffer,CBackground *bkground);
	int setSpriteState(int state);
	int getSpriteState() { return m_currentState; };
	void incrementAnimationframe();
	void setpos(int xpos, int ypos);
	void getpos(int* xpos, int* ypos);
	bool checkCollisionwithBackground(CBackground *bkground, int xpos, int ypos);
	bool checkCollisionwithSprite(CSprite *sprite, int xpos, int ypos);
	bool hasCollidedwithSprite(CSprite* sprite);
	bool getVertices(int* xvert, int *yvert);

	void setPopupText(const char* text);
	void togglePopupText();

	void spawn(int state, int lifespan, int xpos, int ypos, int speedx, int speedy);
	void updatepos();
	void despawn();
	bool isAlive() { return m_alive; };

	void getspeed(int* xspeed, int* yspeed);
	void setSpeed(int xpseed, int yspeed);

};

#endif /* INC_SPRITE_H */
	