#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include "textfile.h"

#include "Geometry.h"


#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_NUM_PARTICLES 500
#define INITIAL_NUM_PARTICLES 100
#define INITIAL_POINT_SIZE 5.0
#define INITIAL_SPEED 1.0


void myIdle();
void collision(int);
float forces(int, int);
void myinit();


typedef struct particle
{ 
     int color;
     float position[3];
     float velocity[3];
     float mass;
} particle;

particle particles[MAX_NUM_PARTICLES]; /* particle system */

/* initial state of particle system */

int present_time;
int last_time;
int num_particles = INITIAL_NUM_PARTICLES;
float point_size = INITIAL_POINT_SIZE;
float speed = INITIAL_SPEED;
bool gravity = FALSE; /* gravity off */
bool elastic = FALSE; /* restitution off */
bool repulsion = FALSE; /* repulsion off */
float coef = 1.0; /* perfectly elastic collisions */
float d2[MAX_NUM_PARTICLES][MAX_NUM_PARTICLES]; /* array for interparticle distances */

GLsizei wh = 500, ww = 500; /* initial window size */

GLfloat colors[8][3]={{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},{0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0}};

/* rehaping routine called whenever window is resized or moved */



int skybox[6];

GLint loc;
GLuint v,f,f2,p;

//Colour parameters
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat red[] = {1.0, 0.0, 0.0, 0.5};

float lpos[4] = {1.0,0.0,1.0,0.0};

#define checkImageWidth 64
#define checkImageHeight 64  
void makeCheckImage(void); 
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

GLfloat track_height= 0.9f;	// Height of the track
GLfloat track_innerradius=8.0f;// Inner radius of the track
GLfloat track_outerradius=11.0f;// Outer radius of the track////////
int nh = 4; //Number of Hills
GLfloat G = 9.81f; //Gravitational Constant
float rad_to_deg= 57.2957795; // to convert radian on to degree

//Train information
GLfloat train_radius= .4f ;
GLfloat train_radius2= .4f ;
double train1_x;
double train1_y;
double train1_z;
double train2_x;
double train2_y;
double train2_z;
double train3_x;
double train3_y;
double train3_z;

///3 train variables
GLfloat timeStep=.005f;
GLfloat train1_Theta = timeStep;// initial position of train
GLfloat train1_Theta1 = timeStep*400; // initial velocity
GLfloat train1_Theta2 = timeStep*40; // initial acceleration

GLfloat train2_Theta = timeStep*30;// initial position of train
GLfloat train2_Theta1 = timeStep*400; // initial velocity
GLfloat train2_Theta2 = timeStep*40; // initial acceleration

GLfloat train3_Theta = timeStep*100;// initial position of train
GLfloat train3_Theta1 = timeStep*400; // initial velocity
GLfloat train3_Theta2 = timeStep*40; // initial acceleration

//track variables
GLdouble	innerRadius = train_radius/2;
GLdouble	outerRadius = train_radius;
GLint		nsides = 100;
GLint		rings = 100;

//TO BE USED FOR WHEEL ROTATION
double CAR_WHEEL_RADIUS;
float wheelCircumference;
float percentage;
GLfloat	wheel_rotation = 0.0;
float arcLength = 0.0;   // used to calculate the Wheel rotation


//==========================================

void myIdle()
{
    int i, j, k;
    float dt;
    present_time = glutGet(GLUT_ELAPSED_TIME);
    dt = 0.001*(present_time -  last_time);
    for(i=0; i<num_particles; i++) 
    {
       for(j=0; j<3; j++)
       {
           particles[i].position[j]+=dt*particles[i].velocity[j];    
           particles[i].velocity[j]+=dt*forces(i,j)/particles[i].mass;
       }
        collision(i);
    }
    if(repulsion) for(i=0;i<num_particles;i++) for(k=0;k<i;k++) 
    {
            d2[i][k] = 0.0;
            for(j=0;j<3;j++) d2[i][k]+= (particles[i].position[j]-
              particles[k].position[j])*(particles[i].position[j]-
              particles[k].position[j]);
            d2[k][i]=d2[i][k];
    }
    last_time = present_time;
    glutPostRedisplay();
}
//Train Model
void display_cart(void)
{
       glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.5, 0.8, -0.70);
    glVertex3f(0.5, 0.8, 0.70);
    glVertex3f(-2.0, 0.8, 0.70);
    glVertex3f(-2.0, 0.8, -0.70);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-2.0, 0.8, -0.70);
    glVertex3f(-2.0, 0.8, 0.70);
    glVertex3f(-2.0, 2.3, 0.70);
    glVertex3f(-2.0, 2.3, -0.70);

    glNormal3f(0.71, 0.71, 0.0);
    glVertex3f(-2.0, 2.3, -0.70);
    glVertex3f(-2.0, 2.3, 0.70);
    glVertex3f(-1.7, 2.0, 0.70);
    glVertex3f(-1.7, 2.0, -0.70);

    glNormal3f(0.12, 0.03, 0.0);
    glVertex3f(-1.7, 2.0, -0.70);
    glVertex3f(-1.7, 2.0, 0.70);
    glVertex3f(-1.4, 0.8, 0.70);
    glVertex3f(-1.4, 0.8, -0.70);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-1.4, 0.8, -0.70);
    glVertex3f(-1.4, 0.8, 0.70);
    glVertex3f(0.0, 0.8, 0.70);
    glVertex3f(0.0, 0.8, -0.70);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.8, -0.70);
    glVertex3f(0.0, 0.8, 0.70);
    glVertex3f(0.0, 1.5, 0.70);
    glVertex3f(0.0, 1.5, -0.70);

    glNormal3f(0.5, 0.3, 0.0);
    glVertex3f(0.0, 1.5, -0.70);
    glVertex3f(0.0, 1.5, 0.70);
    glVertex3f(-0.5, 1.8, 0.70);
    glVertex3f(-0.5, 1.8, -0.70);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, 1.8, -0.70);
    glVertex3f(-0.5, 1.8, 0.70);
    glVertex3f(-0.5, 0.8, 0.70);
    glVertex3f(-0.5, 0.8, -0.70);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-1.8, 0.8, 0.70);
    glVertex3f(-1.8, 1.3, 0.70);
    glVertex3f(0.0, 1.3, 0.70);
    glVertex3f(0.0, 0.8, 0.70);

    glVertex3f(-1.8, 0.8, -0.70);
    glVertex3f(-1.8, 1.6, -0.70);
    glVertex3f(0.0, 1.4, -0.70);
    glVertex3f(0.0, 0.8, -0.70);

    glVertex3f(-2.0, 0.8, 0.70);
    glVertex3f(-2.0, 2.3, 0.70);
    glVertex3f(-1.7, 2.0, 0.70);
    glVertex3f(-1.4, 0.8, 0.70);

    glVertex3f(-2.0, 0.8, -0.70);
    glVertex3f(-2.0, 2.3, -0.70);
    glVertex3f(-1.7, 2.0, -0.70);
    glVertex3f(-1.4, 0.8, -0.70);

    glVertex3f(0.0, 0.8, -0.70);
    glVertex3f(0.0, 1.5, -0.70);
    glVertex3f(-0.5, 1.8, -0.70);
    glVertex3f(-0.5, 0.8, -0.70);

    glVertex3f(0.0, 0.8, 0.70);
    glVertex3f(0.0, 1.5, 0.70);
    glVertex3f(-0.5, 1.8, 0.70);
    glVertex3f(-0.5, 0.8, 0.70);
    glEnd();
}

//=========================================

void trainInit()
{
   train1_x = ((track_outerradius+track_innerradius)/2)*cos(train1_Theta); // initial x position
   train1_y = track_height*sin(nh*train1_Theta)+train_radius;              // initial y position
   train1_z = ((track_outerradius+track_innerradius)/2)*sin(train1_Theta); // initial z position

   train2_x = ((track_outerradius+track_innerradius)/2)*cos(train2_Theta); // initial x position
   train2_y = track_height*sin(nh*train2_Theta)+train_radius;              // initial y position
   train2_z = ((track_outerradius+track_innerradius)/2)*sin(train2_Theta); // initial z position

   train3_x = ((track_outerradius+track_innerradius)/2)*cos(train3_Theta); // initial x position
   train3_y = track_height*sin(nh*train3_Theta)+train_radius;              // initial y position
   train3_z = ((track_outerradius+track_innerradius)/2)*sin(train3_Theta); // initial z position
}

//Make Checker image to use as Texture
void makeCheckImage(void) 
{
   int i, j, c;
     
   for (i = 0; i < checkImageHeight; i++) 
   {
      for (j = 0; j < checkImageWidth; j++) 
	  {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

///////////////////////////////////////////////////////////
//Draw the floor
void room_floor(const float *colour, int width, int height)
{
	glEnable(GL_TEXTURE_2D);
       glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
        glBindTexture(GL_TEXTURE_2D, texName);

	glPushMatrix();
	glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT, GL_AMBIENT, colour);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colour);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-width, -1.0, width);
		glTexCoord2f(0.0, 3.0); glVertex3f(width,  -1.0, width);
		glTexCoord2f(3.0, 3.0); glVertex3f(width, -1.0, -width);
		glTexCoord2f(3.0, 0.0); glVertex3f(-width, -1.0, -width);

	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


static void Init() {                                 // Initialization routine

 
	double x=-3.14;
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};     // Define highlight properties
  GLfloat mat_shininess[]= {50.0};                   // Define shininess of surface
  GLfloat light_position[] = {10.0, 40.0, 1.0, 0.0}; // Define light source position
  glClearColor(0.0, 0.0, 1.0, 1.0);						// Set background to bleu
  glShadeModel(GL_SMOOTH);                           // Smooth transitions between edges
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);   // Set material properties
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // Set material properties
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);   // Set light properties
  glColorMaterial(GL_FRONT,GL_DIFFUSE);                // Set Color Capability

  glEnable(GL_COLOR_MATERIAL);		       // Enable color
  glEnable(GL_LIGHTING);		       // Enable lighting for surfaces
  glEnable(GL_LIGHT0);			       // Enable light source
  glEnable(GL_DEPTH_TEST); 		       // Enable depth buffering

  glNewList(1, GL_COMPILE);  /* create sphere display list for Object 1*/
  glColor3f(1.0,0.0, 0.0);  //red sphere
  glutSolidSphere(0.10,20,10); 
  glEndList();
  
  glNewList(2, GL_COMPILE);
    // Texture
    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

   glNewList(2, GL_COMPILE);
  //Texture
    for (x; x<3.14;x= x+.005) //This is done in radian, but can be achieved in degree
    {

		////// Build inner track
         glPushMatrix();
		 //Translate to the next position in the track
		 glTranslatef(track_innerradius*cos(x),track_height*sin(nh*x),track_innerradius*sin(x));
         glCallList(1);
         glPopMatrix();

		 ///////// Buid outer track
		 glPushMatrix();
		 //Translate to the next position in the track
         glTranslatef(track_outerradius*cos(x),track_height*sin(nh*x), track_outerradius*sin(x));
         glCallList(1);
         glPopMatrix();


		 //////// Add Quad between inner and outer track
		 //Texture
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
        glBindTexture(GL_TEXTURE_2D, texName);

		 glBegin(GL_QUADS);	 
		glPushMatrix();
		glTexCoord2f(0.0f, 0.0f);  // to assign a texture point to a quad point
		glVertex3f(track_innerradius*cos(x),track_height*sin(nh*x),track_innerradius*sin(x));
		glTexCoord2f(1.0f, 0.0f); // to assign a texture point to a quad point
		glVertex3f(track_outerradius*cos(x),track_height*sin(nh*x), track_outerradius*sin(x));
		glTexCoord2f(0.0f, 0.0f); // to assign a texture point to a quad point
		glVertex3f(track_innerradius*cos((x-0.05)),track_height*sin(nh*(x-0.05)),track_innerradius*sin((x-0.05)));
		glTexCoord2f(1.0f, 0.0f); // to assign a texture point to a quad point
		glVertex3f(track_outerradius*cos((x-0.05)),track_height*sin(nh*(x-0.05)), track_outerradius*sin((x-0.05)));
		glPopMatrix();
		glEnd();

      glDisable(GL_TEXTURE_2D);
    }
 glEndList();

 trainInit();

 

 	
}

static void Reshape(int width, int height) //  Determines Projection type
{         
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(80.0, (GLfloat)width / (GLfloat)height, 1.00, 50.0);
  gluLookAt(0.0, 0.0, 15,  0.0, 0.0, 0,  0.0, 1.0, 0); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



//Function Theta2 ODE for angular acceleration
GLfloat Theta2_ODE (float speed, float pos) {

	GLfloat n = track_height;
	int H = nh;
	GLfloat R = track_innerradius+track_outerradius/2;
	GLfloat g = G;

	// equate primary numerator and denominator of Lagrangian separately
	GLfloat numerator = (float)(((n*n*n)*(H*H)*(speed*speed)*sin(n*pos) - n*g*H)*cos(n*pos));
	GLfloat denominator = (float)((R*R) + (n*n)*(H*H)*((cos(n*pos))*(cos(n*pos))));

	// return the calculated result
	return(numerator/denominator);
}

GLfloat RK4 (float speed, float pos) 
{ 
	float k1;
	float k2;
	float k3;
	float k4;

	float j1;
	float j2;
	float j3;
	

	float accel;
    
	k1 = Theta2_ODE(speed, pos);
	j1 = speed+k1;

	k2 = Theta2_ODE(speed+k1/2, pos+j1/2);
	j2 = speed+k2;

	k3 = Theta2_ODE(speed+k2/2, pos+j2/2);
	j3 = speed+k3;

	k4 = Theta2_ODE(speed+k3/2, pos+j3/2);
		 
	accel = (1/6) * (k1 + (2*k2) + (2*k3) + k4);
	
	return (accel);
}

//Euler Solver
GLfloat Euler(float speed, float pos) {

	float k1;
	float accel;
	
	k1 = Theta2_ODE(speed, pos);

	accel = k1;

	return(accel);
}

void Calculate_Position(float &Theta, float &Theta1, float &Theta2)
{
	float speed, pos;
	if (Theta2 <= timeStep) {Theta1=timeStep*400; Theta2= timeStep*40;}
			// derive the car acceleration value using RK ODE integration
	Theta2 = RK4(Theta1, Theta);  // will replace Euler call below
	//Theta2 = Euler(Theta1, Theta);
			// calculate new speed and position values
	speed = Theta1 + timeStep*(Theta2);
	pos = Theta + timeStep*(Theta1);

			// store the new values for car model rendering
	Theta = pos;
	Theta1 = speed;
}







void Wheel()
{
	CAR_WHEEL_RADIUS=train_radius;  //WILL HAVE TO BE CHANGE WHEN YOU USE YOUR OWN TRAIN AND WHEELS
	 // Calculate the arclength distance covered for the change in theta
	 arcLength = ((track_height * nh * cos(nh * train1_Theta)) * (track_height * nh * cos(nh * train1_Theta))) + 1.0f;
	 	// The arclength calculation is an integration, therefore we must
	// sum this bit with all the previous arcLengths
	 arcLength += sqrt (arcLength); //DISTANCE TRAVELLED ON CURVE BETWEEN TO FRAME
	 // We must now divide by the wheel circumference
	 wheelCircumference = 2.0f * M_PI * CAR_WHEEL_RADIUS; //WHEEL CIRCUMFERENCE
	 percentage = arcLength / wheelCircumference; //PERCENTAGE OF DISTANCE TRAVELLED BETWEEN FRAMES
	 // Multiplying the percentage by 360.0 gives us the amount to
	// turn the wheels by
	wheel_rotation = -percentage * 360.0f;  //WHEEL ROTATION ANGLE
	glRotatef(wheel_rotation, 0.0, 0.0, 1.0); //Apply wheel rotation
   glutWireTorus (train_radius/2, train_radius, 50, 100);
}


void myinit()
{
        int  i, j;

 /* set up particles with random locations and velocities */

        for(i=0; i<num_particles; i++) 
        {
            particles[i].mass = 1.0;
            particles[i].color = i%8;
            for(j=0; j<3; j++)
            {
                particles[i].position[j] = 2.0*((float) rand()/RAND_MAX)-1.0;
                particles[i].velocity[j] = speed*2.0*((float) rand()/RAND_MAX)-1.0;
            }
        }
        glPointSize(point_size);


/* set clear color to grey */

        glClearColor(0.5, 0.5, 0.5, 1.0);
}


float forces(int i, int j)
{
   int k;
   float force = 0.0;
   if(gravity&&j==1) force = -1.0; /* simple gravity */
   if(repulsion) for(k=0; k<num_particles; k++)  /* repulsive force */
   {
      if(k!=i) force+= 0.001*(particles[i].position[j]-particles[k].position[j])/(0.001+d2[i][k]);
   }
   return(force);
}

void collision(int n)

/* tests for collisions against cube and reflect particles if necessary */

{
     int i;
     for (i=0; i<3; i++) 
     {
           if(particles[n].position[i]>=1.0) 
           {
                particles[n].velocity[i] = -coef*particles[n].velocity[i];
                particles[n].position[i] = 1.0-coef*(particles[n].position[i]-1.0);
           }
           if(particles[n].position[i]<=-1.0) 
           {
                particles[n].velocity[i] = -coef*particles[n].velocity[i];
                particles[n].position[i] = -1.0-coef*(particles[n].position[i]+1.0);
           }
     }
}


static void display()
{
	// Set the size of the room
	float room_width = 10.0;
	float room_height = 2.0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  // Clear Color and Depth
 room_floor(white, room_width, room_height);

 skyBox();
  glCallList(2);

   //first train
   Calculate_Position(train1_Theta, train1_Theta1, train1_Theta2);
   train1_x = ((track_outerradius+track_innerradius)/2)*cos(train1_Theta); // initial x position
   train1_y = track_height*sin(nh*train1_Theta)+train_radius;              // initial y position
   train1_z = ((track_outerradius+track_innerradius)/2)*sin(train1_Theta); // initial z position
   glPushMatrix();
   glTranslatef(train1_x,train1_y,train1_z);
   glColor3f(1.0,1.0, 0.0);  //yellow sphere
   glRotatef((-train1_Theta*rad_to_deg)-90,0,1,0);
   glRotatef((cos(nh*train1_Theta)*10.0f), 0.0, 0.0, 1.0);  // rotation around z to check - yaw

  /* CAR_WHEEL_RADIUS=train_radius;  //WILL HAVE TO BE CHANGE WHEN YOU USE YOUR OWN TRAIN AND WHEELS
	 // Calculate the arclength distance covered for the change in theta
	 arcLength = ((track_height * nh * cos(nh * train1_Theta)) * (track_height * nh * cos(nh * train1_Theta))) + 1.0f;
	 	// The arclength calculation is an integration, therefore we must
	// sum this bit with all the previous arcLengths
	 arcLength += sqrt (arcLength); //DISTANCE TRAVELLED ON CURVE BETWEEN TO FRAME
	 // We must now divide by the wheel circumference
	 wheelCircumference = 2.0f * M_PI * CAR_WHEEL_RADIUS; //WHEEL CIRCUMFERENCE
	 percentage = arcLength / wheelCircumference; //PERCENTAGE OF DISTANCE TRAVELLED BETWEEN FRAMES
	 // Multiplying the percentage by 360.0 gives us the amount to
	// turn the wheels by
	wheel_rotation = -percentage * 360.0f;  //WHEEL ROTATION ANGLE
	glRotatef(wheel_rotation, 0.0, 0.0, 1.0); //Apply wheel rotation
   glutWireTorus (train_radius/2, train_radius, 50, 100);*/
   display_cart();
   Wheel();
   glPopMatrix();

	//second train
   Calculate_Position(train2_Theta, train2_Theta1, train2_Theta2);
  // train2_x = ((track_outerradius+track_innerradius)/2)*cos(train2_Theta); // initial x position
   train2_x = (((track_outerradius+ (track_outerradius+track_innerradius)/2))/2)*cos(train2_Theta); // initial x position
   train2_y = track_height*sin(nh*train2_Theta)+train_radius;              // initial y position
  // train2_z = ((track_outerradius+track_innerradius)/2)*sin(train2_Theta); // initial z position
   train2_z = (((track_outerradius+ (track_outerradius+track_innerradius)/2))/2)*sin(train2_Theta); // initial z position
   glPushMatrix();
   glTranslatef(train2_x,train2_y, train2_z);
   glColor3f(1.0,1.0, 0.0);  //yellow sphere
   glRotatef((-train2_Theta*rad_to_deg)-90,0,1,0);
   glRotatef((cos(nh*train2_Theta)*10.0f), 0.0, 0.0, 1.0);  // rotation around z to check - yaw

   /*
   CAR_WHEEL_RADIUS=train_radius;  //WILL HAVE TO BE CHANGE WHEN YOU USE YOUR OWN TRAIN AND WHEELS
	 // Calculate the arclength distance covered for the change in theta
	 arcLength = ((track_height * nh * cos(nh * train2_Theta)) * (track_height * nh * cos(nh * train2_Theta))) + 1.0f;
	 	// The arclength calculation is an integration, therefore we must
	// sum this bit with all the previous arcLengths
	 arcLength += sqrt (arcLength); //DISTANCE TRAVELLED ON CURVE BETWEEN TO FRAME
	 // We must now divide by the wheel circumference
	 wheelCircumference = 2.0f * M_PI * CAR_WHEEL_RADIUS; //WHEEL CIRCUMFERENCE
	 percentage = arcLength / wheelCircumference; //PERCENTAGE OF DISTANCE TRAVELLED BETWEEN FRAMES
	 // Multiplying the percentage by 360.0 gives us the amount to
	// turn the wheels by
	wheel_rotation = -percentage * 360.0f;  //WHEEL ROTATION ANGLE
	glRotatef(wheel_rotation, 0.0, 0.0, 1.0); //Apply wheel rotation
   glutWireTorus (train_radius/2, train_radius, 50, 100);*/
   display_cart();
   Wheel();
   glPopMatrix();

   //third train
   Calculate_Position(train3_Theta, train3_Theta1, train3_Theta2);
// train3_x = ((track_outerradius+track_innerradius)/2)*cos(train3_Theta); // initial x position
   train3_x = (((track_innerradius+ (track_outerradius+track_innerradius)/2))/2)*cos(train3_Theta); // initial x position
   train3_y = track_height*sin(nh*train3_Theta)+train_radius;              // initial y position
  // train3_z = ((track_outerradius+track_innerradius)/2)*sin(train3_Theta); // initial z position
   train3_z = (((track_innerradius+ (track_outerradius+track_innerradius)/2))/2)*sin(train3_Theta); // initial z position   glPushMatrix();
   glPushMatrix();
   glTranslatef(train3_x,train3_y, train3_z);
   glColor3f(1.0,1.0, 0.0);  //yellow sphere
   glRotatef((-train3_Theta*rad_to_deg)-90,0,1,0);
   glRotatef((cos(nh*train3_Theta)*10.0f), 0.0, 0.0, 1.0);  // rotation around z to check - yaw
   /*
   CAR_WHEEL_RADIUS=train_radius;  //WILL HAVE TO BE CHANGE WHEN YOU USE YOUR OWN TRAIN AND WHEELS
	 // Calculate the arclength distance covered for the change in theta
	 arcLength = ((track_height * nh * cos(nh * train3_Theta)) * (track_height * nh * cos(nh * train3_Theta))) + 1.0f;
	 	// The arclength calculation is an integration, therefore we must
	// sum this bit with all the previous arcLengths
	 arcLength += sqrt (arcLength); //DISTANCE TRAVELLED ON CURVE BETWEEN TO FRAME
	 // We must now divide by the wheel circumference
	 wheelCircumference = 2.0f * M_PI * CAR_WHEEL_RADIUS; //WHEEL CIRCUMFERENCE
	 percentage = arcLength / wheelCircumference; //PERCENTAGE OF DISTANCE TRAVELLED BETWEEN FRAMES
	 // Multiplying the percentage by 360.0 gives us the amount to
	// turn the wheels by
	wheel_rotation = -percentage * 360.0f;  //WHEEL ROTATION ANGLE
	glRotatef(wheel_rotation, 0.0, 0.0, 1.0); //Apply wheel rotation
   glutWireTorus (train_radius/2, train_radius, 50, 100);*/
   	display_cart();
	Wheel();
   glPopMatrix();
	
  glColor3f(1.0,1.0, 1.0);  
  glFlush();			      // Flush drawing routines
  glutSwapBuffers();		      // Swap buffers
 glutPostRedisplay();		      // Display results
}


/* Rotate about x-axis when "x" typed; rotate about y-axis
   when "y" typed; "i" returns torus to original view */
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   
   case 'a':			// Move forward slowly
		glTranslated(0.0,0.0, 0.05);
		glutPostRedisplay();
		break;
	case 'A':			// Move forward more quickly
		glTranslated(0.0,0.0, 0.1);
		glutPostRedisplay();
		break;
	case 'z':			// Move backward slowly
		glTranslated(0.0,0.0, -0.05);
		glutPostRedisplay();
		break;
	case 'Z':			// Move backward more quickly
		glTranslated(0.0,0.0, -0.1);
		glutPostRedisplay();
		break;
	case '.':	// Rotate scene around origin clockwise
		glRotated(5.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case ',': // Rotate scene around origin anticlockwise
		glRotated(5.0, 0.0, -1.0, 0.0);
		glutPostRedisplay();
		break;
   case 'r':
   case 'R':
      glLoadIdentity();
      gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
      glutPostRedisplay();
      break;
   case 'x':
   case 'X':
      glRotatef(5.0,1.0,0.0,0.0);
      glutPostRedisplay();
      break;
   case 's':
   case 'S':
      glRotatef(-5.0,1.0,0.0,0.0);
      glutPostRedisplay();
	  break;
   case 'y':
   case 'Y':
      glRotatef(5.0,0.0,0.0,1.0);
      glutPostRedisplay();
	  break;
   case 'h':
   case 'H':
      glRotatef(-5.0,0.0,0.0,1.0);
      glutPostRedisplay();
      break;

      break;
   case 27:
   case 'q':
   case 'Q':
      exit(0);
      break;
   }
}

void SetupRC()
    {
    // Light values
    // Bright white light
	 GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

    // Lighting stuff
    glEnable(GL_LIGHTING);			// Enable lighting	

    // Set light model to use ambient light specified by ambientLight
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);

    glEnable(GL_COLOR_MATERIAL);	// Enable Material color tracking

    // Front material ambient and diffuse colors track glColor
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

    // Nice light blue
   //glClearColor(0.0f, 0.0f, 05.f,1.0f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


//======================== SET SHADERS


#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}


void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}



void setShaders() {

	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	f2 = glCreateShader(GL_FRAGMENT_SHADER);


//	  vs = textFileRead("shaders/flat.vert");
//   	fs = textFileRead("shaders/flat.frag");

 //vs = textFileRead("shaders/Light.vert");
 //	fs = textFileRead("shaders/Light.frag");

//      vs = textFileRead("shaders/specular.vert");
//  	fs = textFileRead("shaders/specular.frag");

 	//vs = textFileRead("shaders/toyball.vert");
 	//fs = textFileRead("shaders/toyball.frag");

  	//vs = textFileRead("shaders/beachball.vert");
  //	fs = textFileRead("shaders/beachball.frag");

 // 	vs = textFileRead("shaders/checkerboard.vert");
 // 	fs = textFileRead("shaders/checkerboard.frag");

   vs = textFileRead("shaders/3lights.vert");
 	fs = textFileRead("shaders/3lights.frag");

	//vs = textFileRead("shaders/toon.vert");
	//fs = textFileRead("shaders/toon.frag");

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	printShaderInfoLog(v);
	printShaderInfoLog(f);
	printShaderInfoLog(f2);

	p = glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);

	glLinkProgram(p);
	printProgramInfoLog(p);

	glUseProgram(p);
	loc = glGetUniformLocation(p,"time");

}

int main(int argc, char** argv)// Run program with possible parameters
{	
	
// "glut" Initialization Functions rather than "aux" versions
  glutInit(&argc,argv);  
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); // Initialize modes
  glutInitWindowSize( 1100, 800);
  glutInitWindowPosition( 20, 20);
  glutCreateWindow( argv[0]); // Note that arg[0] is name of program (Window name)
  Init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(Reshape);
  glutIdleFunc(myIdle);

  	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
		printf("Ready for OpenGL 3.0 and above\n");
	else {
		printf("OpenGL 3.0 not supported\n");
		exit(1);
	}

	//This function set the shaders
  setShaders();
  //SetupRC();
  glutMainLoop();
  return 0;
}