
#include <string.h>
#include <math.h>

#include "PlayerSprite.h"
#include "ScrollText.h"
#include "AISprite.h"
#include "PathFinder.h"
#include "Menu.h"
//======================================




//============================================================================================

volatile int update_frame = 0;
volatile int persecondflag = 0;

#define WALK_EAST		0
#define WALK_NORTH		1
#define WALK_WEST		2
#define WALK_SOUTH		3
#define STAND_EAST		4
#define STAND_NORTH		5
#define STAND_WEST		6
#define STAND_SOUTH		7

//=================================================
//checks to see if a key has been released

bool keyrel(int k)
{
    static bool initialized = false;
    static bool keyp[KEY_MAX];
 
    if(!initialized)
    {
        // Set the keyp (key pressed) flags to false
        for(int i = 0; i < KEY_MAX; i++) keyp[i] = false;
        initialized = true;
    }
 
    // Now for the checking
    // Check if the key was pressed
    if(key[k] && !keyp[k])
    {
        // Set the flag and return
        keyp[k] = true;
        return false;
    }
    else if(!key[k] && keyp[k])
    {
        // The key was released
        keyp[k] = false;
        return true;
    }
    // Nothing happened?
    return false;
}

//=================================================

#define MAX_LEVEL		2

void timer_function() {
	update_frame=1;
} END_OF_FUNCTION(timer_function);

void fps_counter_function() {
	persecondflag=1;
} END_OF_FUNCTION(fps_counter_function);

char maps[MAX_LEVEL][128] = {"NewMap3.txt","NewMap3.txt"};
int startpos_x[MAX_LEVEL] = { 110, 110 }; 
int startpos_y[MAX_LEVEL] = { 110, 110 }; 

int playlevel(CPlayerSprite* playerSprite, int level, int startx, int starty) {

	// This is the first level of the game =========================
	// The return value is used to pass information on the state of
	// the game to the main function. They are:
	// -1 = Means that there are errors in initialising the level
	// 0  = Means that the user press the 'escape' key and wants to quit
	// 1  = Means that the player has successfully completed the level
	// 2  = Means that the player has run out of life (game over)
	// 
	// It is useful to write similar explanation to each function that
	// you wrote like this to remind you to remind you what the function 
	// is for.

	// Say, in this level the player has to reach are between (0,2665) ->
	// (32,2700) to exit successully


	// *************************************************************************
	// Initialisation phase
	// In this part, we initialise windows, screee, back buffers, load graphics,
	// create objects, and assign timers.
	// *************************************************************************

	// First set the title of the window we would like to create
	set_window_title("Legend of Zelda: Crater of Life. Main Game");

	// Then set the colour depth in bits
	set_color_depth(32);

	// Then initialise the window
	if ( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480 , 0 , 0 ) < 0 )	{
		allegro_message("Unable initialize graphics module\n % s\n", allegro_error );
		return  -1;
	}

	// Optionally you can disable the close window button at the top right corner
	// This is good practice since it will prevent the player to close the window
	// from outside. That action may be harmful if it is not dealt properly.
	set_window_close_button(0);

	// Create the back buffer
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
	if (buffer == NULL) {
		allegro_message("Unable to initialise the back buffer");
		return -1;
	}

	// Now these are som of the parameters used in this level
	// These are the width and height (in pixels) of the window ON THE SCREEN that 
	// shows the background. 
	int visiblescreen_width = 600;
	int visiblescreen_height = 300;

	// These are the top left and bottom right coordinates of the mentioned window
	int visiblescreen_topleft_x = (SCREEN_W-visiblescreen_width)/2;
	int visiblescreen_topleft_y = 20;
	int visiblescreen_bottomright_x = visiblescreen_topleft_x + visiblescreen_width;
	int visiblescreen_bottomright_y = visiblescreen_topleft_y + visiblescreen_height;

	// These are the width and height (in pixels) of the 'cut-out' window to see the
	// background. If you set these values the same as visiblescreen_width and visiblescreen_height
	// then the ratio is 1:1. But if you set these values smaller than the background will be
	// zoomed in and vice versa
	int background_windowwidth = 600;
	int background_windowheight = 300;

	// This is similar to the background but applies to the sky foreground
	// Notice that the ratio in this case would be 2:1 hence this foreground will scroll 2x faster 
	// than the background. Hence, parallax scrolling
	int sky_windowwidth = background_windowwidth/2;
	int sky_windowheight = background_windowheight/2;

	// This variables are useful to store colour values (to avoid re-
	// calculating them everytime
	int colour_white = makecol(255,255,255);
	int colour_black = 0;
	int colour_red = makecol(255,0,0);
	int colour_green = makecol(0,255,0);
	int colour_blue = makecol(0,0,255);


	//-----------------------------------------

	// Display a message on the screen that the graphics are being loaded
	clear_to_color(screen, colour_black);
	text_mode(-1);
	textprintf(screen, font, 10, 150, makecol(255,255,255), "Please wait while the images are being loaded");
	// ===============================================================

	// Initialise the background ======================================
	CBackground* bk = new CBackground();
	if (bk->initialise(maps[level],background_windowwidth,background_windowheight,visiblescreen_topleft_x,visiblescreen_topleft_y,visiblescreen_width,visiblescreen_height)==0) {
		return -1;
	}

	// Find out what is the size in pixels the background is
	int backgroundwidth, backgroundheight;
	bk->getDimension(&backgroundwidth, &backgroundheight);
	// ================================================================

	// Initialise the sky foreground ==================================
	CBackground* sky = new CBackground();
	if (sky->initialise("Sky Foreground.bmp",NULL,sky_windowwidth,sky_windowheight,visiblescreen_topleft_x,visiblescreen_topleft_y,visiblescreen_width,visiblescreen_height)==0) {
		delete bk;
		return -1;
	}
	// ================================================================


	// Set the player initial position (remember this is relative to the world not the screen location)
	int xpos = startx;
	int ypos = starty;
	playerSprite->setpos(xpos,ypos);
	//=======================================
	//sets the start annimation to stand facing east
	playerSprite->setSpriteState(STAND_EAST);
	//==========================================

	// Display name above our character
	playerSprite->setPopupText("Link");

	// For the arrows ----------------------
	int max_arrows = 5;

	CSprite** arrows = new CSprite*[max_arrows];
	int i;
	for (i=0;i<max_arrows;i++) {
		arrows[i] = new CSprite();
		if (!arrows[i]->initialise("Arrow Sprite Data.dat")) {
			return 1;
		}
	}

	int fire_rate = 30;
	int fire_rate_counter = 0;
	int arrow_speed = 10;

	int max_quivers = 1;

	CSprite** quivers = new CSprite*[max_quivers];
	for (i=0;i<max_quivers;i++) {
		quivers[i] = new CSprite();
		if (!quivers[i]->initialise("Quiver Sprite Data.dat")) {
			return 1;
		}
	}
	
	quivers[0]->spawn(0, 999999, 1805, 2930, 0, 0);

	// ================================================================

	// Initialise the AI characters (2 of them) =======================
	int AI_unit_number = 2;
	CAISprite** NPCSprite = new CAISprite* [AI_unit_number];
	for (i=0;i<AI_unit_number;i++) {
		NPCSprite[i] = new CAISprite();
		if (!NPCSprite[i]->initialise("Enemy Robot Data.dat")) {
			for (int j=0;j<i;j++)
				delete NPCSprite[j];
			delete NPCSprite;
			delete bk;
			delete sky;
			return -1;
		}
	}

	// Set each of the NPC character initial position.
	NPCSprite[0]->spawn(WALK_EAST, 999999, 110, 180, 0, 3);
	NPCSprite[1]->spawn(WALK_SOUTH, 999999, 2127, 2765, 0, 3);

	// ================================================================


	// Initialise the path finding object with the background =========
	CPathFinder* pathFinder = new CPathFinder();
	if (!(pathFinder->initialise(bk))) {
		delete bk;
		delete sky;
		for (int j=0;j<AI_unit_number;j++)
			delete NPCSprite[j];
		delete NPCSprite;
		return -1;
	}
	// ================================================================

	// Clear that loading message
	clear_to_color(buffer, makecol(0,0,0));

	// These variables are used as flag if the player still wants to play, alive or success
	bool playing = true;
	bool alive = true;
	bool success = false;

	// This is a contol variable for space key press. It is useful to avoid detecting multiple
	// key presses within a small amount of time period. See its uses in the game loop
	int controlvariable_Space = 0;


	// This is just a debugging variables to calculate frame rate
	int frames_per_second = 0;
	int framecounter = 0;

	// These variables are for storing the collision table between the player sprite and each AI sprites
	int npcid = 0;
	bool* player_with_AI_collision_table = new bool[AI_unit_number];

	// If you look into the file "Player Data.dat" you will see that we assign the first parameter that
	// the player has as health.
	double health;
	playerSprite->getParameterValue(0,&health);
	// This is the cost to the health for colliding with AI units
	double health_cost = 0.5;
	// This is the health replenish value (for getting away) - in this case no health replenishment
	double health_replenish = 0;

	// If you look into the file "Player Data.dat" you will see that we assign the second parameter that
	// the player has as stamina.
	double stamina;
	playerSprite->getParameterValue(1,&stamina);
	// This is the stamina cost for walking
	double stamina_cost = 0.3;
	// This is the stamina replenish value (for standing still)
	double stamina_replenish = 1;

	// In allegro you can assign a function that will be executed at a constant interval of time
	// This function, although is part of your program, is executed by a completely different process
	// which is controlled by external event such as timer. In this case for example, we have a variable
	// named update_frame, which is set to 1 every 50 milliseconds. In the game loop we check if update_frame
	// is greater than 0, if it is then do the input-> calculation -> output sequence and set update_frame
	// to 0. And since at 50 millisecond intervals this variable is set to 1, then the sequence will only
	// be carried out at a maximum of 20 times per second (hence 20 fps).

	// To use this technique you need to lock both function and variable used using LOCK_VARIABLE and
	// LOCK_FUNCTION respectively. Then assign a timer event to execture the function using the
	// install_int_ex() function. See Allegro manual for more information.

	// Just a brief instruction for the player
	allegro_message("You need to get out of this wood without being caught by the leaping frogs");
	allegro_message("And watch out for your stamina too");

	LOCK_VARIABLE(update_frame);
	LOCK_FUNCTION(timer_function);
	install_int_ex(timer_function, MSEC_TO_TIMER(50));

	// This is similar to above but the purpose is to calculate the actual fps of the game.

	LOCK_VARIABLE(persecondflag);
	LOCK_FUNCTION(fps_counter_function);
	install_int_ex(fps_counter_function, MSEC_TO_TIMER(1000));


	// *************************************************************************
	// Game loop phase
	// Keep the game running while 
	//		the player still wants to play and
	//		the player is still alive and
	//		the player has not succeded
	// *************************************************************************

	while (playing && alive && !success) {
		if (update_frame > 0) {

			// Clear the back buffer
			clear_bitmap(buffer);

			// Get the current position of the player with respect to the world
			// We need this because we would like the window that shows the background
			// to 'follow' the player.
			playerSprite->getpos(&xpos,&ypos);

			// Draw the background. Notice that we also supply the player world coordinate
			bk->drawBackground(buffer,xpos,ypos,false);

			// You may want to specify the drawing area on the back buffer (or screen) for all
			// objects. This allows clipping of objects that lay on the edge of the visible
			// background.
			set_clip(buffer,visiblescreen_topleft_x,visiblescreen_topleft_y,visiblescreen_bottomright_x,visiblescreen_bottomright_y);

			// draw quiver objects
			for (i=0;i<max_quivers;i++)
				quivers[i]->drawSprite(buffer,bk);


			// Draw the player character to the back buffer
			playerSprite->drawSprite(buffer,bk);

			// One by one draw the AI units to the back buffer if it is alive
			for (npcid=0;npcid<AI_unit_number;npcid++) {
				for (npcid=0;npcid<AI_unit_number;npcid++) {
					if (NPCSprite[npcid]->isAlive()) {
						NPCSprite[npcid]->drawSprite(buffer,bk);
					}
				}
			}


			// Finally draw the sky foreground
			sky->drawBackground(buffer,xpos,ypos,true);

			// Set the drawing area back to normal again
			set_clip(buffer,0,0,0,0);

			// This are the variables to store the new player location
			int newxpos, newypos;

			if (key[KEY_RIGHT]) {								// If the right arrow key has been pressed

				newxpos = xpos + 5;								// Set the new x-coordinate as the old x-coordinate + 5
				if (newxpos>backgroundwidth)					// If the new x-coordinate exceeds the width of the world then set
					newxpos = backgroundwidth;					// the new coordinate to the width (so that the player can not go over the edge)
				newypos = ypos;									// The new y-coordinate is the same as the old one since we assume that
																// that the up or down key have not been pressed 
				playerSprite->setSpriteState(WALK_EAST);		// Set the player state to 0 (WALK_EAST==0, see definition at the top)

			} 
			
			
			
			
			
			else if (key[KEY_LEFT]) {

				newxpos = xpos - 5;
				if (newxpos<0)
					newxpos = 0;
				newypos = ypos;

				playerSprite->setSpriteState(WALK_WEST);

			} else if (key[KEY_UP]) {
				newxpos = xpos;
				newypos = ypos - 5;
				if (newypos < 0)
					newypos = 0;

				playerSprite->setSpriteState(WALK_NORTH);

			} else if (key[KEY_DOWN]) {
				newxpos = xpos;
				newypos = ypos + 5;
				if (newypos > backgroundheight)
					newypos = backgroundheight;

				playerSprite->setSpriteState(WALK_SOUTH);


			} else {				
				newxpos = xpos;
				newypos = ypos;
			}


				//===========================================================================
			//This code stops the sprite running on the spot by setting it animation state to a bitmap of only 1 frame
			 if(keyrel(KEY_RIGHT)) 
    {
				newxpos = xpos;
				newypos = ypos;

				playerSprite->setSpriteState(STAND_EAST);
    }

			 else if (keyrel(KEY_LEFT)) {

				newxpos = xpos;
				newypos = ypos;
				playerSprite->setSpriteState(STAND_WEST);

			}  else if (keyrel(KEY_UP)) {
				newxpos = xpos;
				newypos = ypos;
				playerSprite->setSpriteState(STAND_NORTH);

			}  else if (keyrel(KEY_DOWN)) {
				newxpos = xpos;
				newypos = ypos;

				playerSprite->setSpriteState(STAND_SOUTH);


			}

			 			//===========================================================================




			// Shooting --------------------
			// -----------------------------

			if (key[KEY_SPACE] && (fire_rate_counter == 0)) { // If the spacebar is pressed and it has been a while since it was pressed

				for (int arrownumber =0 ;arrownumber < max_arrows;arrownumber++) {	// Find any available arrow slot
					if (!arrows[arrownumber]->isAlive()) {

						int state = playerSprite->getSpriteState();

						if (state==WALK_EAST) 
							arrows[arrownumber]->spawn(WALK_EAST, 50, xpos, ypos, arrow_speed, 0);
						else if (state==WALK_NORTH)
							arrows[arrownumber]->spawn(WALK_NORTH, 50, xpos, ypos, 0, -arrow_speed);
						else if (state==WALK_WEST)
							arrows[arrownumber]->spawn(WALK_WEST, 50, xpos, ypos, -arrow_speed, 0);
						else if (state==WALK_SOUTH)
							arrows[arrownumber]->spawn(WALK_SOUTH, 50, xpos, ypos, 0, arrow_speed);
						//==============================================================================
						// add for standing still
						else if (state==STAND_EAST) 
							arrows[arrownumber]->spawn(WALK_EAST, 50, xpos, ypos, arrow_speed, 0);
						else if (state==STAND_NORTH)
							arrows[arrownumber]->spawn(WALK_NORTH, 50, xpos, ypos, 0, -arrow_speed);
						else if (state==STAND_WEST)
							arrows[arrownumber]->spawn(WALK_WEST, 50, xpos, ypos, -arrow_speed, 0);
						else if (state==STAND_SOUTH)
							arrows[arrownumber]->spawn(WALK_SOUTH, 50, xpos, ypos, 0, arrow_speed);

						//==============================================================================

						fire_rate_counter = fire_rate;
						
					
						break;

					}
				}
			}

			if (fire_rate_counter > 0)
				fire_rate_counter --;


			

			// Checking collision with arrows --------------------
			// ---------------------------------------------------


			for (int arrownumber = 0;arrownumber < max_arrows;arrownumber++) {
				if (arrows[arrownumber]->isAlive()) {

					int currentx, currenty;
					arrows[arrownumber]->getpos(&currentx, &currenty);

					if (arrows[arrownumber]->checkCollisionwithBackground(bk, currentx, currenty)) {

						arrows[arrownumber]->despawn();

					} else {
						for (npcid=0;npcid<AI_unit_number;npcid++) {
							if (NPCSprite[npcid]->isAlive()) {
								if (arrows[arrownumber]->checkCollisionwithSprite(NPCSprite[npcid], currentx, currenty)) {
									NPCSprite[npcid]->despawn();
									arrows[arrownumber]->despawn();
									break;
								}
							}
						}
					}
				}

				if (arrows[arrownumber]->isAlive()) {
					arrows[arrownumber]->updatepos();
					arrows[arrownumber]->drawSprite(buffer, bk);
					arrows[arrownumber]->incrementAnimationframe();
				}
			}

			// Checking collision between player and ALL AI units and alter the value of player_with_AI_collision_table
			// accordingly. There are two types of collision checking function:
			// 
			// The first one is checkCollisionwithSprite(spriteA,x,y), which checking collision with spriteA if the
			// the player is to be moved to (x,y) position. In other words, it wants to find out: WILL the player sprite
			// collide with spriteA if it is moved to location (x,y)
			//
			// The second one is hasCollidedwithSprite(spriteA). This basically finds out if the player sprite HAS ALREADY
			// collided with spriteA.

			for (npcid=0;npcid<AI_unit_number;npcid++) {
				if (NPCSprite[npcid]->isAlive()) {
		
					if (playerSprite->checkCollisionwithSprite(NPCSprite[npcid],newxpos,newypos)) {
						health -= health_cost;
						if (health<=0)
							alive = false;

						if (playerSprite->hasCollidedwithSprite(NPCSprite[npcid])) {
							newxpos = xpos;
							newypos = ypos;
						}

						player_with_AI_collision_table[npcid] = true;
					} else
						player_with_AI_collision_table[npcid] = false;
				}
			}

			// Checking collision with background
			if (playerSprite->checkCollisionwithBackground(bk,newxpos,newypos)) {
				// There is collision at the proposed new location
				newxpos = xpos;
				newypos = ypos;
			}

			// Now that all collision checking have been done we need to check if the new position is the same as
			// the last one. If it is not that means the player has moved hence reduce the stamina
			
			if ((newxpos!=xpos)||(newypos!=ypos)) { // If the new position is not the same as previous position
				stamina-=stamina_cost;
				if (stamina<0) {				// If stamina is zero then *pant-pant*. Can't move.
					stamina=0;
					newxpos = xpos;
					newypos = ypos;
				}
			} else {	// else that means Link is stationary, replenish his stamina
				stamina+=stamina_replenish;
				if (stamina>100)
					stamina=100;
			}

			// Replenish lost health every loop. You may want to change this to Replenish lost health when collided with
			// health potion object.
			health+=health_replenish;
			if (health>100)
				health=100;

			// Set the player parameter
			playerSprite->setParameterValue(0,health);
			playerSprite->setParameterValue(1,stamina);

			// draw the avatar (that portrait and infor bar)
			playerSprite->drawAvatar(buffer);


			// Set the player new position
			playerSprite->setpos(newxpos,newypos);	// use the new values

			// Increment the animation frame
			playerSprite->incrementAnimationframe();

			// Check if the new location is the target area
			// Say, in this level the player has to reach are between (0,2665) ->
			// (32,2700) to exit successully
			if ((newxpos>=0)&&(newxpos<=32)&&(newypos>=2665)&&(newypos<=2700))
				success = true;

			// This part of the code tells each AI units to chase the player
			// What it does is like this:
			// For each AI unit do the following:
			//		Get its current position
			//		Calculate its distance to the player new location
			//		If the distance is larger than some value (in this case 3*its movement speed) then
			//			Check if it's has OR almost reached its current destination. If it is, that means you need to update
			//			the target path. If it is not let it try to reach its destination before we do something
			//		If the distance is smaller than that some value then
			//			Check if it's HAS reached its destination. If it has then tell it to move to the player location otherwise
			//			let it try to reach the destination.
			// From the above pseudocode you will notice that eventhough the AI unit has reached the player it is still homing in
			// this is okay since the function findPathto() will be very quick in this case. This function uses the A* path finding
			// technique that has a desirable property of computational complexity directly proportional to the finding the path.
			//
			// But if you are worried about the added complication then you need to amend the code accordingly

			int NPCxpos, NPCypos;

			for (npcid=0;npcid<AI_unit_number;npcid++) {

				if (NPCSprite[npcid]->isAlive()) {

					NPCSprite[npcid]->getpos(&NPCxpos, &NPCypos);
					int dist = abs(NPCxpos-newxpos)+abs(NPCypos-newypos);
					if (dist > NPCSprite[npcid]->getMovementspeed()*3) {
						if (NPCSprite[npcid]->getCurrenttargetpath() < 2)
							NPCSprite[npcid]->findPathto(newxpos, newypos, pathFinder);
						else
							NPCSprite[npcid]->updatePos();
					} else if (!player_with_AI_collision_table[npcid]) {
						if (NPCSprite[npcid]->getCurrenttargetpath()==-1)
							NPCSprite[npcid]->findPathto(newxpos, newypos, pathFinder);
						else
							NPCSprite[npcid]->updatePos();
					}
			
					NPCSprite[npcid]->incrementAnimationframe();
				}

			}

			// ---------------------

			// Draw a minimap at the bottom left corner
			bk->drawMiniMap(buffer,10,370,100,100);


			// This is just some debugging info to the screen
			textout(buffer, font, "System information:", 120, 370, colour_white);
			textprintf(buffer, font, 120, 382, colour_white, "Frame per second: %i", frames_per_second);
			textprintf(buffer, font, 120, 394, colour_white, "Player world coordinate: (%i,%i)", newxpos, newypos);

			// Copy the entire content of the back buffer to the screen
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H );

			// Increment the number of frame drawn in the last one second
			framecounter++;

			// Set the update_frame flag to zero. This flag will be set to 1 again by timer every 50 millisecond 
			update_frame=0;
		}

		// Because variable persecondflag is set to 1 every one second then the following code will copy the total
		// number of frames drawn in the last second to variable frames_per_second
		if (persecondflag > 0) {
			persecondflag = 0;
			frames_per_second = framecounter;
			framecounter = 0;
		}

		// Check if the player has pressed the 'escape' key
		if (key[KEY_ESC]) 
			playing=false;
	}

	// *************************************************************************
	// House keeping phase
	// You will need to clean up and free all memory space used. Notice the order
	// in which NPCSprite objects are deleted. Don't forget to remove those interrupt
	// functions.
	// *************************************************************************

	// Remove the timer interrupts
	remove_int(timer_function);
	remove_int(fps_counter_function);


	// Deleting objects
	delete bk;
	delete sky;

	for (int j=0;j<AI_unit_number;j++)
		delete NPCSprite[j];
	delete NPCSprite;

	for (i=0;i<max_arrows;i++)
		delete arrows[i];
	delete arrows;

	for (i=0;i<max_quivers;i++)
		delete quivers[i];
	delete quivers;

	delete pathFinder;
	destroy_bitmap(buffer);

	// Close graphics window
	set_gfx_mode(GFX_TEXT,0,0,0,0);

	// And finally returning the appropriate value to the main program
	if (!playing)
		return 0;
	else if (!alive)
		return 2;
	else if (success)
		return 1;
	else
		return -1;

}



//============================================================================================

bool initialise_allegro() {

	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();

	if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) {
		allegro_message("Sound Error: %s", allegro_error);
		return false;
	} else
		return true;
}

int intro_sequence() {

	// ========================================================================
	// This is the intro sequence. It displays a Zelda logo and scroll some text

	// First set the title of the window we would like to create
	set_window_title("Legend of Zelda: Crater of Life. Introduction");

	// Then set the colour depth in bits
	set_color_depth(32);

	// Then initialise the window
	if ( set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480 , 0 , 0 ) < 0 )	{
		allegro_message( "Unable initialize graphics module\n % s\n", allegro_error );
		return  false;
	}

	// Optionally you can disable the close window button at the top right corner
	// This is good practice since it will prevent the player to close the window
	// from outside. That action may be harmful if it is not dealt properly.
	set_window_close_button(0);

	// Create the back buffer
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

	// To scroll a text we can use CScrollText object. When initialising this object
	// you need to tell which text file contains the texts that you would like to 
	// display, in this case it is called "Intro Text.txt"
	CScrollText* scroll = new CScrollText();
	scroll->initialise("Intro Text.txt", 100, 100, 540, 380, 0, makecol(255,255,255), 1);

	// Load the logo that we would like to display
	BITMAP* logo = load_bitmap("zelda_logo.bmp",0);

	// Now this coordinate is useful if we would like to centre 
	// the logo in the middle of the screen. This corresponds to
	// the top-left corner of box at which the logo will be drawn
	int tlx = (SCREEN_W-logo->w)/2;
	int tly = (SCREEN_H-logo->h)/2;

	// Clear the back buffer so that we can draw on it fresh
	clear_bitmap(screen);

	// Load the midi music that you would like to play
	MIDI* intro_music = load_midi("Intro Music.mid");

	// And play it maestro!
	play_midi(intro_music,1);

	// We could use a variable to control the speed of which the
	// text will be scrolled. The higher the number the slower the
	// scrolling
	int counter=0;
	int delay = 50000000;

	// This variable will be used to flag the instance the scrolling
	// ends. Set it to true initially since we only just started.
	bool still_scrolling = true;

	// Now the following codes work like this
	// if counter is less or equal to zero (which it initially is) then
	//		1. Clear the back buffer
	//		2. Draw the logo to the back buffer
	//		3. Tell the scrolling text object to scroll the text to the back buffer using 
	//		the scroll() function this function will return a value which is true if it 
	//		is still scrolling or false if it has reached the end
	//		4. Copy the contect of the back buffer to the screen
	//		5. Set the counter to delay
	// else (i.e., if the counter is larger than zero)
	//		This means that it has to do nothing. The number of times the computer has to
	//		do nothing is determined by the delay value.
	//		Make sure every time the computer 'does nothing' you decrement the counter
	//

	// Do the above until the player press the 'escape' key or the scrolling ends

	do {
		if (counter<=0) {
			clear_bitmap(buffer);
			blit(logo,buffer,0,0,tlx,tly,logo->w, logo->h);
			still_scrolling = scroll->scroll(buffer);
			blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			counter = delay;
		} else
			counter--;

	} while ((!key[KEY_ESC])&&(still_scrolling));

	// Stop the music maestro!
	stop_midi();

	// This is house keeping. Keep in mind that for each object you created you are responsible
	// to delete them from the memory. Otherwise, you will use to much memory unnecessarily and
	// may end up with 'Insufficient Memory Error'
	clear_bitmap(screen);
	destroy_bitmap(logo);
	destroy_bitmap(buffer);
	destroy_midi(intro_music);

	// Close graphics window
	set_gfx_mode(GFX_TEXT,0,0,0,0);

	// return true for succesfully running the intro

	return true;
}

int startNewGame() {

	if (!intro_sequence())
		return 1;

	// Initialise the player character ================================
	CPlayerSprite* playerSprite = new CPlayerSprite();
	if (!playerSprite->initialise("Player Data.dat")) {
		return 1;
	}

	int level = 0;
	int game_state;
	bool game_over = false;

	do {

		game_state = playlevel(playerSprite,level, startpos_x[level], startpos_y[level]);

		switch (game_state) {
		case -1:
			allegro_message("There was an error");
			game_over = true;
			break;
		case 0:
			allegro_message("You have decided to have enough");
			game_over = true;
			break;
		case 1:
			level++;
			if (level>=MAX_LEVEL) {
				game_over = true;
				allegro_message("You have completed the game");
			} else
				allegro_message("You have completed the level. You proceed to the next level");
			break;
		case 2:
			allegro_message("You are dead");
			game_over = true;
			break;
		default:
			allegro_message("This value is not supposed to be returned");
			game_over = true;
			break;
		}
	} while (!game_over);

	delete playerSprite;

	return game_state;

}

int main(void) {

	if (!initialise_allegro())
		return 1;

	CMenu mainMenu;

	set_color_depth(32);
	int col = makecol(255,255,255);

	mainMenu.Initialise("Main Menu", 4, col);

	mainMenu.AddMenuItem("Main Menu Button 01.bmp", NULL, 1);
	mainMenu.AddMenuItem("Main Menu Button 02.bmp", NULL, 2);
	mainMenu.AddMenuItem("Main Menu Button 03.bmp", NULL, 3);
	mainMenu.AddMenuItem("Main Menu Button 04.bmp", NULL, 4);
	int returnvalue;
	bool inthegame = true;
	
	do {
		returnvalue = mainMenu.DoModal();
		int game_state;
		switch (returnvalue) {
		case 1:
			game_state = startNewGame();
			if (game_state==-1)
				inthegame = false;
			break;
		case 2:
			allegro_message("This feature has not yet been implemented");
			break;
		case 3:
			allegro_message("This feature has not yet been implemented");
			break;
		case 4:
			inthegame = false;
			break;
		}
	} while (inthegame);

	return 0;

} END_OF_MAIN();

