/*
=================
Geometry.h
-Geometry header file including imageLoader & textureLoader functions
-could also have directly pasted these functions into main.cpp
-all these functions are self explanatory
=================
*/

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "tga.h"

/* Macro Defines */
#define TOTAL_NUMBER_OF_TEXTURES 11

/* Globals */
int SELECT = 0; //for selected rendering mode
int MODE; //for wireframe drawing

/* internal storage for texture data */
GLuint the_texture[TOTAL_NUMBER_OF_TEXTURES];

/* array storing texture file names */
char* texture_filenames[TOTAL_NUMBER_OF_TEXTURES] = {"texture/floor.tga", 
													 "texture/pool.tga", 
													 "texture/pillars.tga", 
													 "texture/walls.tga", 
													 "texture/windows.tga", 
													 "texture/poolsteps.tga", 
													 "texture/rails.tga", 
													 "texture/support.tga", 
													 "texture/cloth2.tga", 
													 "texture/water.tga", 
													 "texture/default_pool.tga"};

/* Global Vertex Arrays */
/* -------------------- */
GLfloat pedistal_vertices1[][3] = {{-10.0, -0.4, -10.0},
								   {10.0, -0.4, -10.0},
								   {10.0, 0.4, -10.0},
								   {-10.0, 0.4, -10.0},
								   {-10.0, -0.4, 10.0},
								   {10.0, -0.4, 10.0},
								   {10.0, 0.4, 10.0},
								   {-10.0, 0.4, 10.0}};

GLfloat pedistal_vertices2[][3] = {{-5.0, -0.8, -5.0},
								   {5.0, -0.8, -5.0},
								   {5.0, 0.8, -5.0},
								   {-5.0, 0.8, -5.0},
								   {-5.0, -0.8, 5.0},
								   {5.0, -0.8, 5.0},
								   {5.0, 0.8, 5.0},
								   {-5.0, 0.8, 5.0}};

GLfloat terrace_vertices[][3] = {{-30.0, -0.5, -5.7},
								 {30.0, -0.5, -5.7},
								 {30.0, 0.5, -5.7},
								 {-30.0, 0.5, -5.7},
								 {-30.0, -0.5, 5.7},
								 {30.0, -0.5, 5.7},
								 {30.0, 0.5, 5.7},
								 {-30.0, 0.5, 5.7}};

GLfloat support_vertices[][3] = {{-30.0, -0.5, -1.0},
								 {30.0, -0.5, -1.0},
								 {30.0, 0.5, -1.0},
								 {-30.0, 0.5, -1.0},
								 {-30.0, -0.5, 1.0},
								 {30.0, -0.5, 1.0},
								 {30.0, 0.5, 1.0},
								 {-30.0, 0.5, 1.0}};

GLfloat terrace_railing_vertices[][3] = {{-20.0, -1.0, -0.05},
										 {20.0, -1.0, -0.05},
										 {20.0, 1.0, -0.05},
										 {-20.0, 1.0, -0.05},
										 {-20.0, -1.0, 0.05},
										 {20.0, -1.0, 0.05},
										 {20.0, 1.0, 0.05},
										 {-20.0, 1.0, 0.05}};

GLfloat pillar_base[][3] = {{-0.65, -0.65, -0.6},
							{0.65, -0.65, -0.6},
							{0.65, 0.65, -0.6},
							{-0.65, 0.65, -0.6},
							{-0.65, -0.65, 0.6},
							{0.65, -0.65, 0.6},
							{0.65, 0.65, 0.6},
							{-0.65, 0.65, 0.6}};

GLfloat pool_vertices[][3] = {{-4.0, -0.6, -0.3},
							  {4.0, -0.6, -0.3},
							  {4.0, 0.6, -0.3},
							  {-4.0, 0.6, -0.3},
							  {-4.0, -0.6, 0.3},
							  {4.0, -0.6, 0.3},
							  {4.0, 0.6, 0.3},
							  {-4.0, 0.6, 0.3}};

GLfloat poolstep_vertices[][3] = {{-0.3, -0.3, -1.0},
								  {0.3, -0.3, -1.0},
								  {0.3, 0.3, -1.0},
								  {-0.3, 0.3, -1.0},
								  {-0.3, -0.3, 1.0},
								  {0.3, -0.3, 1.0},
								  {0.3, 0.3, 1.0},
								  {-0.3, 0.3, 1.0}};

GLfloat poolstep_vertices2[][3] = {{-0.3, -0.15, -1.0},
								   {0.3, -0.15, -1.0},
								   {0.3, 0.15, -1.0},
								   {-0.3, 0.15, -1.0},
								   {-0.3, -0.15, 1.0},
								   {0.3, -0.15, 1.0},
								   {0.3, 0.15, 1.0},
								   {-0.3, 0.15, 1.0}};
/* -------------------- */


/*
=================
imageLoader
-loads our TGA data
=================
*/
bool imageLoader(char *TexName, int currentTexture) 
{
	/* image loading type */
	TGAImg Img;

	/* loads the texture */
	if(Img.Load(TexName)!=IMG_OK) 
		return false;

	/* the texture handle is set to the current loaded texture */
	glBindTexture(GL_TEXTURE_2D, the_texture[currentTexture]);

	/* setup the texture if it is a standard solid 24bit image (no transparency) */
	if(Img.GetBPP() == 24) 
	{
		/* specifies the solid two-dimensional texture */
		glTexImage2D(GL_TEXTURE_2D, 0, 3, Img.GetWidth(), Img.GetHeight(), 0, GL_RGB,GL_UNSIGNED_BYTE, Img.GetImg());
	} 
	/* else setup the texture if it is a 32bit image with an alpha channel */
	else if(Img.GetBPP()==32) 
	{
		/* specifies the transparent two-dimensional texture */
		glTexImage2D(GL_TEXTURE_2D, 0, 4, Img.GetWidth(),Img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Img.GetImg());
	} 
	else 
	{
		return false;
	}

	/* sets the texture parameters - for reference, consult Prog 8.6's discussion */
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	return true;
}

/*
=================
textureLoader
-calls imageLoader for every TGA file
=================
*/
void textureLoader() 
{
	/* deals with the generation of texture names  */
	glGenTextures(TOTAL_NUMBER_OF_TEXTURES, the_texture);

	/* calls imageLoader for the current texture */
	for (int k=0; k < TOTAL_NUMBER_OF_TEXTURES; k++) 
	{
		imageLoader(texture_filenames[k], k);
	}
}

/*
=================
drawNormal
-draws red lines to indicate the direction of the normal of a plane
-parameters: coord_x, y & z: the positions if needed to move the drawn normal a bit
			                 for the sake of visibility
			 axis: the axis on which the normal was calculated
=================
*/
void drawNormal(float coord_x, float coord_y, float coord_z, char axis)
{
	if(SELECT == 2)
	{
		glPushMatrix();
			glBegin(GL_LINES);
				glColor3f(1,0,0);
				glVertex3f(coord_x,coord_y,coord_z);
				if(axis == 'z')
				{
					glVertex3f(coord_x,coord_y,coord_z+2);
				}
				else if(axis == 'y')
				{
					glVertex3f(coord_x,coord_y+2,coord_z);
				}
				else
					glVertex3f(coord_x+2,coord_y,coord_z);
			glEnd();
		glPopMatrix();
	}
}

/*
=================
drawMainBottomFloor
-draws the primary floor on which everything is built
=================
*/
void drawMainBottomFloor(void)
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[0]);
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_QUADS;
		glBegin(MODE);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-30.0, 0.0, -30.0);
			glTexCoord2f(0.0,10.0);
			glVertex3f(-30.0, 0.0, 30.0);
			glTexCoord2f(10.0,10.0); //the bigger the higher the resulution
			glVertex3f(30.0, 0.0, 30.0);
			glTexCoord2f(10.0,0.0);
			glVertex3f(30.0, 0.0, -30.0);
		glEnd();
		drawNormal(0,0,0,'y');
	glPopMatrix();
}

/*
=================
drawPoolBottomFog
-draws the pool's volumetric fog
=================
*/
void drawPoolBottomFog(void)
{
	glPushMatrix();
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_QUADS;
		glPushMatrix();
			glEnable(GL_FOG);
			glBindTexture(GL_TEXTURE_2D, the_texture[10]);
			glBegin(MODE);
				glFogCoordfEXT(1.0);
				glTexCoord2f(0.0,0.0);
				glVertex3f(-4.0, 0.9, -4.0);
				glFogCoordfEXT(1.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(-4.0, 0.9, 4.0);
				glFogCoordfEXT(1.0);
				glTexCoord2f(1.0,1.0);
				glVertex3f(4.0, 0.9, 4.0);
				glFogCoordfEXT(1.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(4.0, 0.9, -4.0);
				glDisable(GL_BLEND);
			glEnd();
			glDisable(GL_FOG);
		glPopMatrix();
		drawNormal(1,0,0,'y'); //'1' so that pool floor normal doesn't overlap with main floor normal at (0,0,0)
	glPopMatrix();
}

/*
=================
blendTester
-disables or enables blending based on global 'SELECT'
=================
*/
void blendTester()
{
	if(SELECT == 11)
		glDisable(GL_BLEND);
	if(SELECT == 12)
		glEnable(GL_BLEND);
}

/*
=================
drawPoolWater
-draws the "water" for the pool, basically a textured flat polygon
=================
*/
void drawPoolWater(void)
{
	glPushMatrix();
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_QUADS;
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[9]);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glEnable(GL_BLEND);
		blendTester();
		glBegin(MODE);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-4.0, 1.9, -4.0);
			glTexCoord2f(0.0,3.0);
			glVertex3f(-4.0, 1.9, 4.0);
			glTexCoord2f(3.0,3.0);
			glVertex3f(4.0, 1.9, 4.0);
			glTexCoord2f(3.0,0.0);
			glVertex3f(4.0, 1.9, -4.0);
		glEnd();
		glPopMatrix();
		glDisable(GL_FOG);
		glDisable(GL_BLEND);
		drawNormal(1,0,0,'y');
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, the_texture[8]);
}

/*
=================
drawPillarBase
-draws a square block used for the block at the bottom of the pillars
=================
*/
void drawPillarBase(int a, int b, int c, int d)
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[2]);
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_POLYGON;
		glBegin(MODE);
		glBegin(GL_POLYGON);
			glColor3f(1,0,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(pillar_base[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(pillar_base[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(pillar_base[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(pillar_base[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
constructPillarBase
-calls 'drawPillarBase' for each of the pillars
=================
*/
void constructPillarBase()
{
	/* bottom */
	glPushMatrix();
		glRotatef(-180.0, 0.0, 0.0, 1.0);
		glTranslatef(0,0,0.6);
		glNormal3f(1,0,0);
		drawNormal(0,0,0,'x');
        drawPillarBase(5,4,0,1);
		drawPillarBase(1,0,3,2);

		glNormal3f(0,1,0);
		drawNormal(0,0,0,'y');
		drawPillarBase(3,7,6,2);
		
		glNormal3f(1,0,0);
		drawNormal(0,0,0,'x');
		drawPillarBase(7,3,0,4);
		
		glNormal3f(1,0,0);
		drawNormal(-1,0,0,'x'); //-1 else it points into the wrong direction
		drawPillarBase(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawNormal(0.6,0,0,'z');
		drawPillarBase(4,5,6,7);
	glPopMatrix();

	/* top */
	glPushMatrix();
		glRotatef(-180.0, 0.0, 0.0, 1.0);
		glTranslatef(0,0,6.2);
		glNormal3f(1,0,0);
		drawNormal(0,0,0,'x');
        drawPillarBase(5,4,0,1);
		drawPillarBase(1,0,3,2);

		glNormal3f(0,1,0);
		drawNormal(0,0,0,'y');
		drawPillarBase(3,7,6,2);
		
		glNormal3f(1,0,0);
		drawNormal(0,0,0,'x');
		drawPillarBase(7,3,0,4);
		
		glNormal3f(1,0,0);
		drawNormal(-1,0,0,'x');
		drawPillarBase(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawNormal(0.6,0,0,'z'); //x component = 0.6 else normal drawn in middle of cylinder
		drawPillarBase(4,5,6,7);
	glPopMatrix();
}

/*
=================
drawPillars
-calls 'constructPillarBase' and creates 1 pillar
=================
*/
void drawPillars()
{
	/* wireframe view */
	if(SELECT == 2 || SELECT == 1)
	{	
		glPushMatrix();
			constructPillarBase(); //draw the bases
			GLUquadricObj* obj;
			glColor3f(1.0,1.0,0.0);
			glBindTexture(GL_TEXTURE_2D, the_texture[1]);
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_LINE);
			gluQuadricNormals(obj, GLU_SMOOTH);
			gluQuadricTexture(obj, GLU_TRUE);
			gluCylinder(obj, 0.5, 0.5, 7.0, 24, 24);
			gluDeleteQuadric(obj);
		glPopMatrix();
	}
	/* solid view */
	else
	{
		glPushMatrix();
			constructPillarBase(); //draw the bases
			GLUquadricObj* obj;
			glColor3f(1.0,1.0,0.0);
			glBindTexture(GL_TEXTURE_2D, the_texture[1]);
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_FILL);
			gluQuadricNormals(obj, GLU_SMOOTH);
			gluQuadricTexture(obj, GLU_TRUE);
			gluCylinder(obj, 0.5, 0.5, 7.0, 24, 24);
			gluDeleteQuadric(obj);
		glPopMatrix();
	}
}

/*
=================
constructPillarArchitecture
-setups the pillars throughout the scene
=================
*/
void constructPillarArchitecture()
{
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,-20,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,-15,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,-10,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,-5,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,0,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,5,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,10,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,15,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,20,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,25,0);
		drawPillars();
	glPopMatrix();

	////////////////////////////////////////

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-20,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-15,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-10,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-5,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(5,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(10,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(15,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(20,-25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,-25,0);
		drawPillars();
	glPopMatrix();

	////////////////////////////////////////

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(20,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(15,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(10,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(5,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-5,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-10,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-15,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-20,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-25,25,0);
		drawPillars();
	glPopMatrix();

	////////////////////////////////////////

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,25,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,20,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,15,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,10,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,5,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,0,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,-5,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,-10,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,-15,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,-20,0);
		drawPillars();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(25,-25,0);
		drawPillars();
	glPopMatrix();

}

/*
=================
drawWall
-draws a single wall
=================
*/
void drawWall()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[3]);
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_QUADS;
		glColor3f(0.0,1.0,0.0);
		glBegin(MODE);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-30.0, 0.0, -6.0);
			glTexCoord2f(0.0,5.0);
			glVertex3f(-30.0, 0.0, 6.0);
			glTexCoord2f(5.0,5.0);
			glVertex3f(30.0, 0.0, 6.0);
			glTexCoord2f(5.0,0.0);
			glVertex3f(30.0, 0.0, -6.0);
		glEnd();
		drawNormal(0,0,0,'y');
	glPopMatrix();
}

/*
=================
constructOuterWalls
-setups the outer walls of the scene
=================
*/
void constructOuterWalls()
{
	//NORTH
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0,-30,6);
		drawWall();
	glPopMatrix();

	//SOUTH
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0,30,6);
		glRotatef(-180.0,1.0,0.0,0.0);
		drawWall();
	glPopMatrix();

	//EAST
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(30,0,6);
		glRotatef(-90.0,0.0,0.0,1.0);
		glRotatef(-180.0,1.0,0.0,0.0);
		drawWall();
	glPopMatrix();

	//WEST
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(-30,0,6);
		glRotatef(-90.0,0.0,0.0,1.0);
		drawWall();
	glPopMatrix();
}

/*
=================
drawRoofWalls
-draws a single wall used at the roof
=================
*/
void drawRoofWalls()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[3]);
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_QUADS;
		glColor3f(1.0,1.0,0.0);
		glBegin(MODE);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-30.0, 0.0, -10.0);
			glTexCoord2f(0.0,10.0);
			glVertex3f(-30.0, 0.0, 10.0);
			glTexCoord2f(10.0,10.0);
			glVertex3f(30.0, 0.0, 10.0);
			glTexCoord2f(10.0,0.0);
			glVertex3f(30.0, 0.0, -10.0);
		glEnd();
		drawNormal(0,0,0,'y');
	glPopMatrix();
}

/*
=================
constructRoofWalls
-setups the roof walls of the scene
=================
*/
void constructRoofWalls()
{
	//SOUTH
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0,-33,17);
		drawRoofWalls();
	glPopMatrix();

	//NORTH
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0,33,17);
		glRotatef(-180.0,1.0,0.0,0.0);
		drawRoofWalls();
	glPopMatrix();
}

/*
=================
drawRoofWallWindow
-draws a single polygon used to represent a window
=================
*/
void drawRoofWallWindow()
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[4]);
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_QUADS;
		glColor3f(0.0,1.0,1.0);
		glBegin(MODE);
			glNormal3f(0,1,0);
			glTexCoord2f(0.0,0.0);
			glVertex3f(-3.0, 0.0, -3.0);
			glTexCoord2f(0.0,1.0);
			glVertex3f(-3.0, 0.0, 3.0);
			glTexCoord2f(1.0,1.0);
			glVertex3f(3.0, 0.0, 3.0);
			glTexCoord2f(1.0,0.0);
			glVertex3f(3.0, 0.0, -3.0);
		glEnd();
		drawNormal(0,0,0,'y');
	glPopMatrix();
}

/*
=================
constructRoofWalls
-setups the roof wall window used in the scene
=================
*/
void constructRoofWallWindow()
{
	//NORTH
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0,31,17);
		glRotatef(-180.0,1.0,0.0,0.0);
		drawRoofWallWindow();
	glPopMatrix();
}

/*
=================
drawPedestal
-draws the pedestals at the pool
=================
*/
void drawPedestal(int a, int b, int c, int d)
{
	glBindTexture(GL_TEXTURE_2D, the_texture[1]);
	if(SELECT == 2 || SELECT == 1)
		MODE = GL_LINE_LOOP;
	else
		MODE = GL_POLYGON;
	glPushMatrix();
		glBegin(MODE);
			glColor3f(1,0,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(pedistal_vertices1[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(pedistal_vertices1[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(pedistal_vertices1[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(pedistal_vertices1[d]);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(MODE);
			glColor3f(1,0,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(pedistal_vertices2[a]);
			glTexCoord2f(0.0,2.0);
			glVertex3fv(pedistal_vertices2[b]);
			glTexCoord2f(2.0,2.0);
			glVertex3fv(pedistal_vertices2[c]);
			glTexCoord2f(2.0,0.0);
			glVertex3fv(pedistal_vertices2[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
constructInnerPedestal
-setups the inner pedestal at the pool
=================
*/
void constructInnerPedestal()
{
	glPushMatrix();
		glNormal3f(1,0,0);
        drawPedestal(5,4,0,1);
		drawPedestal(1,0,3,2);

		glNormal3f(0,1,0);
		drawPedestal(3,7,6,2);
		
		glNormal3f(1,0,0);
		drawPedestal(7,3,0,4);
		
		glNormal3f(1,0,0);
		drawPedestal(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawPedestal(4,5,6,7);
	glPopMatrix();
}

/*
=================
drawPool
-draws the pool walls with volumetric fog
=================
*/
void drawPool(int a, int b, int c, int d)
{
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[1]);
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_POLYGON;
		glBegin(MODE);
			glDisable(GL_BLEND);
			glColor3f(1,0,1);
			glFogCoordfEXT(1.0f); glTexCoord2f(1.0f, 0.0f);
			glVertex3fv(pool_vertices[a]);
			glFogCoordfEXT(1.0f); glTexCoord2f(1.0f, 1.0f);
			glVertex3fv(pool_vertices[b]);
			glFogCoordfEXT(0.0f); glTexCoord2f(0.0f, 1.0f);
			glVertex3fv(pool_vertices[c]);
			glFogCoordfEXT(0.0f); glTexCoord2f(0.0f, 0.0f);
			glVertex3fv(pool_vertices[d]);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, the_texture[1]);
		glBegin(MODE);
			glDisable(GL_BLEND);
			glColor3f(1,0,1);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3fv(pool_vertices[a]);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3fv(pool_vertices[b]);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3fv(pool_vertices[c]);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3fv(pool_vertices[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
constructPool
-setups the pool in the middle of the scene
=================
*/
void constructPool()
{
	//light side
	glPushMatrix();
		glDisable(GL_BLEND);
		glTranslatef(0,1.5,4);
		glNormal3f(1,0,0);
		drawNormal(-3.5,0,-4,'x');
        	glEnable(GL_FOG);
		drawPool(5,0,0,1);
		drawPool(1,0,3,2);
		glDisable(GL_FOG);

		glNormal3f(0,1,0);
		drawPool(3,7,6,2);
		drawNormal(4,0.5,-4,'y');
		
		glNormal3f(1,0,0);
		drawPool(7,3,0,4);
		drawNormal(4,0,-4,'x');
		
		glNormal3f(1,0,0);
		drawPool(2,6,5,1);
		drawNormal(-6,0,-4,'x');
	
		glNormal3f(0,0,1);
		drawPool(4,5,6,7);
	glPopMatrix();

	//dark side opposite light
	glPushMatrix();
		glDisable(GL_BLEND);
		glRotatef(180.0,0.0,1.0,0.0);
		glTranslatef(0,1.5,4);
		drawNormal(-3.5,0,-4,'x');
		glEnable(GL_FOG);
		glNormal3f(0,1,0);
        drawPool(5,4,0,1);
		drawPool(1,0,3,2);
		glDisable(GL_FOG);

		glNormal3f(0,1,0);
		drawPool(3,7,6,2);
		drawNormal(4,0.5,-4,'y');
		
		glNormal3f(1,0,0);
		drawPool(7,3,0,4);
		drawNormal(4,0,-4,'x');
		
		glNormal3f(1,0,0);
		drawPool(2,6,5,1);
		drawNormal(-6,0,-4,'x');
	
		glNormal3f(0,0,1);
		drawPool(4,5,6,7);
	glPopMatrix();

	//left side from light
	glPushMatrix();
		glDisable(GL_BLEND);
		glRotatef(270.0,0.0,1.0,0.0);
		glTranslatef(0,1.5,3.7);
		drawNormal(-3.5,0,-4,'x');
		glEnable(GL_FOG);
		glNormal3f(0,0,1);
        drawPool(5,4,0,1);
		drawPool(1,0,3,2);
		glDisable(GL_FOG);

		glNormal3f(0,1,0);
		drawPool(3,7,6,2);
		drawNormal(4,0.5,-4,'y');
		
		glNormal3f(1,0,0);
		drawPool(7,3,0,4);
		drawNormal(4,0,-3.4,'x');
		
		glNormal3f(1,0,0);
		drawPool(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawPool(4,5,6,7);
	glPopMatrix();

	//right side from light
	glPushMatrix();
		glDisable(GL_BLEND);
		glRotatef(90.0,0.0,1.0,0.0);
		glTranslatef(0,1.5,3.7);
		drawNormal(-3.5,0,-4,'x');
		glEnable(GL_FOG);
		glNormal3f(1,0,0);
        drawPool(5,4,0,1);
		drawPool(1,0,3,2);
		glDisable(GL_FOG);

		glNormal3f(0,1,0);
		drawPool(3,7,6,2);
		drawNormal(4,0.5,-4,'y');
		
		glNormal3f(1,0,0);
		drawPool(7,3,0,4);
		drawNormal(4,0,-3.4,'x');
		
		glNormal3f(1,0,0);
		drawPool(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawPool(4,5,6,7);
	glPopMatrix();
}

/*
=================
drawPoolSteps
-draws the higher set of steps at the pool
=================
*/
void drawPoolSteps(int a, int b, int c, int d)
{
	glBindTexture(GL_TEXTURE_2D, the_texture[5]);
	if(SELECT == 2 || SELECT == 1)
		MODE = GL_LINE_LOOP;
	else
		MODE = GL_POLYGON;
	glPushMatrix();
		glBegin(MODE);
			glColor3f(1,1,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(poolstep_vertices[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(poolstep_vertices[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(poolstep_vertices[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(poolstep_vertices[d]);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(MODE);
			glColor3f(1,1,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(poolstep_vertices[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(poolstep_vertices[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(poolstep_vertices[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(poolstep_vertices[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
drawPoolSteps2
-draws the lower set of steps at the pool
=================
*/
void drawPoolSteps2(int a, int b, int c, int d)
{
	glBindTexture(GL_TEXTURE_2D, the_texture[5]);
	if(SELECT == 2 || SELECT == 1)
		MODE = GL_LINE_LOOP;
	else
		MODE = GL_POLYGON;
	glPushMatrix();
		glBegin(MODE);
			glColor3f(1,1,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(poolstep_vertices2[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(poolstep_vertices2[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(poolstep_vertices2[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(poolstep_vertices2[d]);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glBegin(MODE);
			glColor3f(1,1,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(poolstep_vertices2[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(poolstep_vertices2[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(poolstep_vertices2[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(poolstep_vertices2[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
constructPoolSteps
-setups the pool steps in the scene
=================
*/
void constructPoolSteps()
{
	glPushMatrix();
		glTranslatef(-4,1,0);
		glNormal3f(1,0,0);
        drawPoolSteps(5,4,0,1);
		drawPoolSteps(1,0,3,2);
		drawNormal(-2,0.1,0,'x');

		glNormal3f(0,1,0);
		drawPoolSteps(3,7,6,2);
		drawNormal(0.2,0.1,0,'y');
		
		glNormal3f(1,0,0);
		drawPoolSteps(7,3,0,4);
		drawNormal(0.2,0.1,0,'x');
		
		glNormal3f(1,0,0);
		drawPoolSteps(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawPoolSteps(4,5,6,7);
		drawNormal(-0.2,-0.1,0,'z');
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.5,0.9,0);
		glNormal3f(1,0,0);
        drawPoolSteps2(5,4,0,1);
		drawPoolSteps2(1,0,3,2);
		drawNormal(-2,0,0,'x');

		glNormal3f(0,1,0);
		drawPoolSteps2(3,7,6,2);
		drawNormal(0.2,0.1,0,'y');
		
		glNormal3f(1,0,0);
		drawPoolSteps2(7,3,0,4);
		drawNormal(0.2,0.1,0,'x');
		
		glNormal3f(1,0,0);
		drawPoolSteps2(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawPoolSteps2(4,5,6,7);
		drawNormal(-0.2,-0.1,0,'z');
	glPopMatrix();
}

/*
=================
drawTerrace
-draws the top terrace slab
=================
*/
void drawTerrace(int a, int b, int c, int d)
{
	glBindTexture(GL_TEXTURE_2D, the_texture[1]);
	glPushMatrix();
	if(SELECT == 2 || SELECT == 1)
		MODE = GL_LINE_LOOP;
	else
		MODE = GL_POLYGON;
		glBegin(MODE);
			glColor3f(1,0,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(terrace_vertices[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(terrace_vertices[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(terrace_vertices[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(terrace_vertices[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
constructTerraces
-setups the top terrace slabs
=================
*/
void constructTerraces()
{
	//NORTH
	glPushMatrix();
		glTranslatef(0,7.3,-25);
		drawNormal(0,0,0,'x');
		glNormal3f(1,0,0);
        drawTerrace(5,4,0,1);
		drawTerrace(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerrace(3,7,6,2);
		drawNormal(0,0,0,'y');
		
		glNormal3f(1,0,0);
		drawTerrace(7,3,0,4);
		drawNormal(-0.1,0,0,'x');
		
		glNormal3f(1,0,0);
		drawTerrace(2,6,5,1);
		drawNormal(0,0,0,'x');
	
		glNormal3f(0,0,1);
		drawTerrace(4,5,6,7);
		drawNormal(0,0,0,'z');
	glPopMatrix();

	//SOUTH
	glPushMatrix();
		glTranslatef(0,7.3,25);
		//glRotatef(90.0,0.0,1.0,0.0);
		drawNormal(0,0,0,'x');
		glNormal3f(1,0,0);
        drawTerrace(5,4,0,1);
		drawTerrace(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerrace(3,7,6,2);
		drawNormal(0,0,0,'y');
		
		glNormal3f(1,0,0);
		drawTerrace(7,3,0,4);
		drawNormal(-0.1,0,0,'x');
		
		glNormal3f(1,0,0);
		drawTerrace(2,6,5,1);
		drawNormal(0,0,0,'x');
	
		glNormal3f(0,0,1);
		drawTerrace(4,5,6,7);
		drawNormal(0,0,0,'z');
	glPopMatrix();

	//EAST
	glPushMatrix();
		glTranslatef(-25,7.3,0);
		glRotatef(90.0,0.0,1.0,0.0);
		drawNormal(0,0,0,'x');
		glNormal3f(1,0,0);
        drawTerrace(5,4,0,1);
		drawTerrace(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerrace(3,7,6,2);
		drawNormal(0,0,0,'y');
		
		glNormal3f(1,0,0);
		drawTerrace(7,3,0,4);
		drawNormal(-0.1,0,0,'x');
		
		glNormal3f(1,0,0);
		drawTerrace(2,6,5,1);
		drawNormal(0,0,0,'x');
	
		glNormal3f(0,0,1);
		drawTerrace(4,5,6,7);
		drawNormal(0,0,0,'z');
	glPopMatrix();

	//WEST
	glPushMatrix();
		glTranslatef(25,7.3,0);
		glRotatef(90.0,0.0,1.0,0.0);
		drawNormal(0,0,0,'x');
		glNormal3f(1,0,0);
        drawTerrace(5,4,0,1);
		drawTerrace(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerrace(3,7,6,2);
		drawNormal(0,0,0,'y');
		
		glNormal3f(1,0,0);
		drawTerrace(7,3,0,4);
		drawNormal(0,0,0,'x');
		
		glNormal3f(1,0,0);
		drawTerrace(2,6,5,1);
		drawNormal(-0.1,0,0,'x');
	
		glNormal3f(0,0,1);
		drawTerrace(4,5,6,7);
		drawNormal(0,0,0,'z');
	glPopMatrix();
}

/*
=================
drawTerraceRailing
-draws a single terrace railing
=================
*/
void drawTerraceRailing(int a, int b, int c, int d)
{
	glPushMatrix();
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.45);
	glBindTexture(GL_TEXTURE_2D, the_texture[6]);
	if(SELECT == 2 || SELECT == 1)
		MODE = GL_LINE_LOOP;
	else
		MODE = GL_POLYGON;
		glBegin(MODE);
			glColor3f(0,1,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(terrace_railing_vertices[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(terrace_railing_vertices[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(terrace_railing_vertices[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(terrace_railing_vertices[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
constructTerraceRailing
-setups the top terrace railings
=================
*/
void constructTerraceRailing()
{
	//NORTH
	glPushMatrix();
		glTranslatef(0,8.8,-20);
		glNormal3f(1,0,0);
        drawTerraceRailing(5,4,0,1);
		drawTerraceRailing(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerraceRailing(3,7,6,2);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(7,3,0,4);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawTerraceRailing(4,5,6,7);
		drawNormal(1,0,0,'z');
	glPopMatrix();

	//SOUTH
	glPushMatrix();
		glTranslatef(0,8.8,20);
		//glRotatef(90.0,0.0,1.0,0.0);
	
		glNormal3f(1,0,0);
        drawTerraceRailing(5,4,0,1);
		drawTerraceRailing(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerraceRailing(3,7,6,2);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(7,3,0,4);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawTerraceRailing(4,5,6,7);
		drawNormal(1,0,0,'z');
	glPopMatrix();

	//EAST
	glPushMatrix();
		glTranslatef(-20,8.8,0);	
		glRotatef(90.0,0.0,1.0,0.0);
	
		glNormal3f(1,0,0);
        drawTerraceRailing(5,4,0,1);
		drawTerraceRailing(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerraceRailing(3,7,6,2);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(7,3,0,4);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawTerraceRailing(4,5,6,7);
		drawNormal(1,0,0,'z');
	glPopMatrix();

	//WEST
	glPushMatrix();
		glTranslatef(20,8.8,0);	
		glRotatef(90.0,0.0,1.0,0.0);
	
		glNormal3f(1,0,0);
        drawTerraceRailing(5,4,0,1);
		drawTerraceRailing(1,0,3,2);

		glNormal3f(0,1,0);
		drawTerraceRailing(3,7,6,2);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(7,3,0,4);
		
		glNormal3f(1,0,0);
		drawTerraceRailing(2,6,5,1);
	
		glNormal3f(0,0,1);
		drawTerraceRailing(4,5,6,7);
		drawNormal(1,0,0,'z');
	glPopMatrix();
}

/*
=================
drawSupportBeam
-draws a support beam above the cloths
=================
*/
void drawSupportBeam(int a, int b, int c, int d)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, the_texture[7]);
	if(SELECT == 2 || SELECT == 1)
		MODE = GL_LINE_LOOP;
	else
		MODE = GL_POLYGON;
		glBegin(MODE);
			glColor3f(1,0,1);
			glTexCoord2f(0.0,0.0);
			glVertex3fv(support_vertices[a]);
			glTexCoord2f(0.0,1.0);
			glVertex3fv(support_vertices[b]);
			glTexCoord2f(1.0,1.0);
			glVertex3fv(support_vertices[c]);
			glTexCoord2f(1.0,0.0);
			glVertex3fv(support_vertices[d]);
		glEnd();
	glPopMatrix();
}

/*
=================
constructSupportBeam
-setups the support beam
=================
*/
void constructSupportBeam()
{
	//NORTH
	glPushMatrix();
		glTranslatef(0,7.3,0);
		drawNormal(0,0,0,'x');
		glNormal3f(1,0,0);
        drawSupportBeam(5,4,0,1);
		drawSupportBeam(1,0,3,2);

		glNormal3f(0,1,0);
		drawSupportBeam(3,7,6,2);
		drawNormal(0,0,0,'y');
		
		glNormal3f(1,0,0);
		drawSupportBeam(7,3,0,4);
		drawNormal(-0.1,0,0,'x');
		
		glNormal3f(1,0,0);
		drawSupportBeam(2,6,5,1);
		drawNormal(0,0,0,'x');
	
		glNormal3f(0,0,1);
		drawSupportBeam(4,5,6,7);
		drawNormal(0,0,0,'z');
	glPopMatrix();
}

/*
=================
drawPersianRoof
-draws the persian looking roof
=================
*/
void drawPersianRoof(int a, int b, int c)
{
		glBindTexture(GL_TEXTURE_2D, the_texture[3]);
		if(SELECT == 2 || SELECT == 1)
			MODE = GL_LINE_LOOP;
		else
			MODE = GL_TRIANGLE_STRIP;
		glBegin(MODE);
			glColor3f(1,1,1);
			glTexCoord2f(0.0,0.0);
			//LEFT
			glVertex3f(0,0,0);glTexCoord2f(0.0,0.0);
						glVertex3f(0,0,0);glTexCoord2f(0.0,0.0);
			glVertex3f(0,0,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(0.10*a,-0.26*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(0.10*a,-0.26*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(0.27*a,-0.62*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(0.27*a,-0.62*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(0.52*a,-1.02*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(0.52*a,-1.02*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(0.58*a,-1.06*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(0.58*a,-1.06*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(0.71*a,-1.22*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(0.71*a,-1.22*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(0.89*a,-1.37*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(0.89*a,-1.37*b,5*c);;glTexCoord2f(0.0,1.0);
						glVertex3f(1.13*a,-1.52*b,0);;glTexCoord2f(1.0,1.0);
			glVertex3f(1.13*a,-1.52*b,5*c);;glTexCoord2f(1.0,0.0);
						glVertex3f(1.19*a,-1.54*b,0);;glTexCoord2f(0.0,0.0);
			glVertex3f(1.19*a,-1.54*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(1.42*a,-1.64*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(1.42*a,-1.64*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(1.58*a,-1.71*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(1.58*a,-1.71*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(1.77*a,-1.77*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(1.77*a,-1.77*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(1.95*a,-1.87*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(1.95*a,-1.87*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(2.03*a,-1.91*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(2.03*a,-1.91*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(2.17*a,-1.97*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(2.17*a,-1.97*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(2.25*a,-2.04*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(2.25*a,-2.04*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(2.35*a,-2.12*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(2.35*a,-2.12*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(2.43*a,-2.17*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(2.43*a,-2.17*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(2.49*a,-2.24*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(2.49*a,-2.24*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(2.57*a,-2.33*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(2.57*a,-2.33*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(2.76*a,-2.56*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(2.76*a,-2.56*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(2.85*a,-2.71*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(2.85*a,-2.71*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(2.89*a,-2.81*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(2.89*a,-2.81*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(2.95*a,-2.92*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(2.95*a,-2.92*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(3.00*a,-2.99*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(3.00*a,-2.99*b,5);glTexCoord2f(0.0,1.0);
						glVertex3f(3.05*a,-3.09*b,0);glTexCoord2f(1.0,1.0);
			glVertex3f(3.05*a,-3.09*b,5*c);glTexCoord2f(1.0,0.0);
						glVertex3f(3.08*a,-3.20*b,0);glTexCoord2f(0.0,0.0);
			glVertex3f(3.08*a,-3.20*b,5*c);glTexCoord2f(0.0,1.0);
						glVertex3f(3.11*a,-3.29*b,0);glTexCoord2f(1.0,1.0);
		glEnd();

		glBegin(MODE);
			glTexCoord2f(0.0,0.0);
			glColor3f(1,1,1);
			//RIGHT
						glVertex3f(0,0,0);glTexCoord2f(0.0,1.0);
			glVertex3f(0,0,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-0.10*a,-0.26*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-0.10*a,-0.26*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-0.27*a,-0.62*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-0.27*a,-0.62*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-0.52*a,-1.02*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-0.52*a,-1.02*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-0.58*a,-1.06*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-0.58*a,-1.06*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-0.71*a,-1.22*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-0.71*a,-1.22*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-0.89*a,-1.37*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-0.89*a,-1.37*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-1.13*a,-1.52*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-1.13*a,-1.52*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-1.19*a,-1.54*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-1.19*a,-1.54*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-1.42*a,-1.64*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-1.42*a,-1.64*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-1.58*a,-1.71*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-1.58*a,-1.71*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-1.77*a,-1.77*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-1.77*a,-1.77*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-1.95*a,-1.87*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-1.95*a,-1.87*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-2.03*a,-1.91*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-2.03*a,-1.91*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-2.17*a,-1.97*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-2.17*a,-1.97*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-2.25*a,-2.04*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-2.25*a,-2.04*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-2.35*a,-2.12*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-2.35*a,-2.12*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-2.43*a,-2.17*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-2.43*a,-2.17*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-2.49*a,-2.24*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-2.49*a,-2.24*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-2.57*a,-2.33*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-2.57*a,-2.33*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-2.76*a,-2.56*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-2.76*a,-2.56*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-2.85*a,-2.71*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-2.85*a,-2.71*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-2.89*a,-2.81*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-2.89*a,-2.81*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-2.95*a,-2.92*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-2.95*a,-2.92*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-3.00*a,-2.99*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-3.00*a,-2.99*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-3.05*a,-3.09*b,0);glTexCoord2f(1.0,0.0);
			glVertex3f(-3.05*a,-3.09*b,5*c);glTexCoord2f(0.0,0.0);
						glVertex3f(-3.08*a,-3.20*b,0);glTexCoord2f(0.0,1.0);
			glVertex3f(-3.08*a,-3.20*b,5*c);glTexCoord2f(1.0,1.0);
						glVertex3f(-3.11*a,-3.29,0);glTexCoord2f(1.0,0.0);
		glEnd();
}

/*
=================
constructPersianRoof
-setups the persian roof
=================
*/
void constructPersianRoof()
{
	glPushMatrix();
		glNormal3f(1,1,0);
		glTranslatef(0,26,-32);
		drawPersianRoof(10,5,13);
		drawNormal(0,0,3,'y');
		drawNormal(0,0,3,'x');
	glPopMatrix();
}


void skyBox()
{
	glEnable(GL_TEXTURE_2D);
	
	// Render the front quad
   glBindTexture(GL_TEXTURE_2D, the_texture[0]);
   glBegin(GL_QUADS);
       glTexCoord2f(0, 0); glVertex3f(  15.0, -15.0, -15.0 );
       glTexCoord2f(1, 0); glVertex3f( -15.0, -15.0, -15.0 );
       glTexCoord2f(1, 1); glVertex3f( -15.0,  15.0, -15.0 );
       glTexCoord2f(0, 1); glVertex3f(  15.0,  15.0, -15.0 );
   glEnd();

   // Render the left quad
   glBindTexture(GL_TEXTURE_2D, the_texture[0]);
   glBegin(GL_QUADS);
       glTexCoord2f(0, 0); glVertex3f(  15.0, -15.0,  15.0 );
       glTexCoord2f(1, 0); glVertex3f(  15.0, -15.0, -15.0);
       glTexCoord2f(1, 1); glVertex3f(  15.0, 15.0, -15.0 );
       glTexCoord2f(0, 1); glVertex3f(  15.0, 15.0, 15.0);
   glEnd();

    // Render the back quad
   glBindTexture(GL_TEXTURE_2D, the_texture[0]);
   glBegin(GL_QUADS);
       glTexCoord2f(0, 0); glVertex3f( -15.0, -15.0, 15.0);
       glTexCoord2f(1, 0); glVertex3f(  15.0, -15.0, 15.0 );
       glTexCoord2f(1, 1); glVertex3f(  15.0, 15.0, 15.0 );
       glTexCoord2f(0, 1); glVertex3f( -15.0, 15.0, 15.0 );
   glEnd();

   // Render the right quad
   glBindTexture(GL_TEXTURE_2D, the_texture[0]);
   glBegin(GL_QUADS);
       glTexCoord2f(0, 0); glVertex3f( -15.0, -15.0, -15.0 );
       glTexCoord2f(1, 0); glVertex3f( -15.0, -15.0,  15.0 );
       glTexCoord2f(1, 1); glVertex3f( -15.0,  15.0,  15.0 );
       glTexCoord2f(0, 1); glVertex3f( -15.0,  15.0, -15.0 );
   glEnd();

   // Render the top quad
   glBindTexture(GL_TEXTURE_2D, the_texture[0]);
   glBegin(GL_QUADS);
       glTexCoord2f(0, 1); glVertex3f( -15.0,  15.0f, -15.0 );
       glTexCoord2f(0, 0); glVertex3f( -15.0,  15.0,  15.0 );
       glTexCoord2f(1, 0); glVertex3f(  15.0,  15.0,  15.0 );
       glTexCoord2f(1, 1); glVertex3f(  15.0,  15.0, -15.0 );
   glEnd();

   // Render the bottom quad
   glBindTexture(GL_TEXTURE_2D, the_texture[0]);
   glBegin(GL_QUADS);

       glTexCoord2f(0, 0); glVertex3f( -15.0, -15.0, -15.0 );
       glTexCoord2f(0, 1); glVertex3f( -15.0, -15.0,  15.0 );
       glTexCoord2f(1, 1); glVertex3f(  15.0, -15.0,  15.0 );
       glTexCoord2f(1, 0); glVertex3f(  15.0, -15.0, -15.0 );
   glEnd();

   // Restore enable bits and matrix
   glPopAttrib();
   glPopMatrix();

   glDisable(GL_TEXTURE_2D);
		
}

//Draw the floor
/*void room_floor(void)
{
	glEnable(GL_TEXTURE_2D);
 
	glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, the_texture[0]);

	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10., -10., 10.);
		glTexCoord2f(0.0, 3.0); glVertex3f(10.,  -10., 10.);
		glTexCoord2f(3.0, 3.0); glVertex3f(10., -10., -10.);
		glTexCoord2f(3.0, 0.0); glVertex3f(-10., -10., -10.);

	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
*/
#endif
//EOF