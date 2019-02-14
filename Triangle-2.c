/*
	Ryan Bluteau
	Example Program of drawing a Car
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
*	Typical OpenGL Files.
*	Use appropriate files from your
*	system OpenGL installation.
*/

#include <GLUT/glut.h>


/*
*	This is a type definition for the "display" function.
*	This display function will draw all the points on the window
*	and be called on each frame from 'glutMainLoop' in main.
*	'myInit' defines these properties for glutMainLoop.
*/
typedef void (*GLUTdisplayCB) ();



/*
*	Global variable are needed since variables from main() 
*	can't be accessed by the display function when reading inputs.
*/

//triangle coordinates, will be read in on main
float x=0.0;
float rotatex=0.0;
enum{
	MENU_ACCELERATE,
	MENU_SLOW,
	MENU_DIRECTION,
	MENU_EXIT
};
bool SpeedUp = false;
bool SlowDown = false;
bool ChangeDir = false;
bool MouseClick = false;




//function definitions
void myInit(int *, char **, GLUTdisplayCB);
void drawCar();

void myMouseFunc(int button, int state, int x, int y){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			if(MouseClick==true){
				MouseClick=false;
			}
			else{
				MouseClick=true;
			}
		}
}

void SelectMenu(int MenuKey){
	switch(MenuKey){
		case MENU_ACCELERATE:
				SpeedUp = true;
				SlowDown = false;

		break;

		case MENU_SLOW:
				SpeedUp = false;
				SlowDown = true;


		break;

		case MENU_DIRECTION:
			if(ChangeDir==false){
				ChangeDir = true;
			}
			else{
				ChangeDir = false;
			}
		break;

		case MENU_EXIT:
			exit(0);
			break;
	}

}

int BuildMenu(){
	int menu;
	menu = glutCreateMenu(SelectMenu);
	glutAddMenuEntry("increase",MENU_ACCELERATE);
	glutAddMenuEntry("decrease",MENU_SLOW);
	glutAddMenuEntry("Change-direction",MENU_DIRECTION);
	glutAddMenuEntry("Exit",MENU_EXIT);
	return menu;

}


int main(int argc, char **argv){

	/* 
	*	We give myInit the main's arguments and the display function.
	*	This can actually just be done in main, but this makes cleaner code.
	*/
	myInit(&argc, argv, drawCar);

	glutMouseFunc(myMouseFunc);

	BuildMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop(); //infinite frame-drawing loop

	return 0; //will never be reached.
}


	//myInit sets up all of OpenGLs 'settings' for the windows
void myInit(int *argc, char ** argv, GLUTdisplayCB displayFunc) {


	/* Simple C-Style reading in values for pixle colour and Triangle coordinates */


		/** This is some usual window code for OpenGL **/
        glutInit(argc, argv);	                        //Initialization of Window
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);    //Single Buffer window using RGBA
        glutInitWindowSize(640, 480);                   //the size of the window itself
        glutInitWindowPosition(100, 150);               //The position of the window within your computer screen
        glutCreateWindow(argv[0]);                      //Create window with the program name as title

        glutDisplayFunc(displayFunc);                   //Define the function to call at each frame in glutMainLoop
							//This case will be 'drawTriangle' passed in on main


        glClearColor(1.0, 1.0, 1.0, 0.0);               //clear the buffer with white colour (R, G, B, A)

	//set draw colour
	//draw size
        glPointSize(1.0);

}


void drawCar(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Matrix definition, for the window
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //Camera Position is 190% (percent of the window) back from the pyramid,
        //      25% downwards and 50% to the left
        gluLookAt(-1.9f, -0.25f, -.7, 0, 0, 0, 0, 1, 0);
        //gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);


glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      //1.0 represents full red colour - cannot go beyond 1.0 or below 0.
      glColor3f(1.0f, 0.0f, 0.0f);
      //1.0 represents 100% of coordinate view in the height.
      //We make this smaller by moving the camera back (see above)
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);

      // Right
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);

      // Back
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);

      // Left
      glColor3f(0.0f,1.0f,1.0f);
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();   // Done drawing the pyramid

   //draw the black square bottom of the pyramid
   glBegin(GL_QUADS);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f( -1.0f, -1.0f, -1.0f);
      glVertex3f( -1.0f, -1.0f, 1.0f);
   glEnd();

   glFlush();
}

