#ifndef INC_SCROLLTEXT_H
#define INC_SCROLLTEXT_H

#include <allegro.h>

class CScrollText {
protected:
	bool m_binitialised;
	int m_numberofLines;
	char** m_lineText;
	int* m_lineYpos;
	int m_top, m_left, m_right, m_bottom, m_textXpos, m_alignment, m_colour, m_scrollspeed;
public:
	CScrollText();
	~CScrollText();
	bool isInitialised() { return m_binitialised; };
	bool initialise(char filename[], int left, int top, int right, int bottom, int alignment, int colour, int scrollspeed);
	bool scroll(BITMAP* buffer);
};

#endif /* INC_SCROLLTEXT_H */









	
