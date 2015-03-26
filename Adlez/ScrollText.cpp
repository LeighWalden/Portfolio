#include "ScrollText.h"
#include <string>
#include <fstream>

using namespace std;

CScrollText::CScrollText() {

	m_binitialised = false;
	m_numberofLines = 0;
	m_lineText = NULL;
	m_lineYpos = NULL;
	m_top = 0; 
	m_left = 0; 
	m_right = 0; 
	m_bottom = 0;

}


CScrollText::~CScrollText() {

	m_binitialised = false;
	if (m_lineText!=NULL) {
		for (int i=0;i<m_numberofLines;i++) {
			if (m_lineText[i]!=NULL)
				delete m_lineText[i];
			m_lineText[i]=NULL;
		}
		delete m_lineText;
		m_lineText = NULL;
	}

	if (m_lineYpos!=NULL)
		delete m_lineYpos;
	m_lineYpos = NULL;

	m_top = 0; 
	m_left = 0; 
	m_right = 0; 
	m_bottom = 0;
	m_numberofLines = 0;


}

bool CScrollText::initialise(char filename[], int left, int top, int right, int bottom, int alignment, int colour, int scrollspeed) {

	if (m_binitialised) {

		allegro_message("The scroll text object can not be initialised twice");
		return false;

	}

	if (scrollspeed <= 0) {

		allegro_message("Scroll speed must be greater than zero");
		return false;

	}

	ifstream infile;
	infile.open(filename);
	if (!infile.is_open()) {
		allegro_message("Unable to open scrolling text file");
		return false;
	}

/*	char buf[512];
	int linecount = 0;

	do {
		infile.getline(buf,512,'\n');
		linecount++;
	} while (!infile.eof());

	infile.seekg (0, ios::beg);

	m_numberofLines = linecount-1;*/

	m_top = top;
	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_alignment = alignment;

	if (m_alignment==-1)
		m_textXpos = m_left;
	else if (m_alignment==1)
		m_textXpos = m_right;
	else
		m_textXpos = (m_left+m_right)/2;

	const int MAXLINE = 1024;

	m_lineText = new char* [MAXLINE];
	m_lineYpos = new int[MAXLINE];

	int i =0;

	do {
		m_lineText[i] = new char[512];
		infile.getline(m_lineText[i],512,'\n');
		i++;
	} while((!infile.eof())&&(i<MAXLINE));

	m_numberofLines = i;

	infile.close();

	m_lineYpos[0] = 0;

	int characterHeight = 10+3;

	for (i=1;i<m_numberofLines;i++)
		m_lineYpos[i] = m_lineYpos[i-1] + characterHeight;

	m_colour = colour;
	m_scrollspeed = scrollspeed;

	m_binitialised = true;

	return true;

}


bool CScrollText::scroll(BITMAP* buffer) {

	if (!m_binitialised)
		return false;
	
	set_clip(buffer,m_left, m_top, m_right, m_bottom);

	int characterHeight = 10+3;
	int height = m_bottom-m_top;

	text_mode(-1);

	bool still_scrolling = false;

	for (int i=0;i<m_numberofLines;i++) {

		if ((m_lineYpos[i] <= 0)&&(m_lineYpos[i] > -(height+characterHeight))) {

			switch (m_alignment) {
			case -1:
				textout(buffer,font,m_lineText[i],m_textXpos, m_bottom+m_lineYpos[i], m_colour);
				break;
			case 1:
				textout_right(buffer,font,m_lineText[i],m_textXpos, m_bottom+m_lineYpos[i], m_colour);
				break;
			default:
				textout_centre(buffer,font,m_lineText[i],m_textXpos, m_bottom+m_lineYpos[i], m_colour);
				break;
			}

			still_scrolling = true;

		}

		m_lineYpos[i] -= m_scrollspeed;
		if (m_lineYpos[i]<-2*height)
			m_lineYpos[i] = -2*height;
	}

	set_clip(buffer,0,0,0,0);

	return still_scrolling;

}
