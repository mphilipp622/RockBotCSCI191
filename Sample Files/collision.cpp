/*
    To demo this file, run it as a new and separate GLUT project.
*/

#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159

using namespace std;

bool WireFrame= false;
float i =0;

GLint m_viewport[4];
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

    float xpos =1;
    float ypos =5;
    float xdes =4.0;
    float ydes =4.0;
    float t =0.0;
    float xcurr =0.0;
    float ycurr =0.0;

    float  mlocX =0;
    float  mlocY =0;
    float gravity = -9.8;
    float Wwidth,Wheight;

static void withTimer(int);
/* GLUT callback Handlers */

void square(){


  glBegin(GL_QUADS);
      glVertex3f(4.3,4.3,0.0);
      glVertex3f(-4.3,4.3,0.0);
      glVertex3f(-4.3,-4.3,0.0);
      glVertex3f(4.3,-4.3,0.0);
  glEnd();

}

static void resize(int width, int height)
{
     double Ratio;

     Wwidth = (float)width;
     Wheight = (float)height;

     Ratio= (double)width /(double)height;

    glViewport(0,0,(GLsizei) width,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective (45.0f,Ratio,0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glGetIntegerv( GL_VIEWPORT, m_viewport );
    cout<<m_viewport[0]<<"  "<<m_viewport[2]<<" "<<m_viewport[3]<<endl;
 }

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,100.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    glPushMatrix();
    glColor3f(0.1,1.3,0.4);
        square();
    glPopMatrix();

    // your code here
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslated(xpos,ypos,0);
    glutSolidSphere(0.2,24,24);
    glPopMatrix();

    glPushMatrix();
    glPointSize(	8);
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_POINTS);
         glVertex3f(mlocX,mlocY,2);
    glEnd();
    glPopMatrix();

    glutTimerFunc(20,withTimer,0);
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

	  case 'w':
		WireFrame =!WireFrame;
	       break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
    break;
   }
  glutPostRedisplay();
}

/*
    Checks where the boundaries for collisions to occur.
*/
 int check_Collision(float x,float y)
{
    if((x > 4)||(x < -4))
    {
        (x < -4)? xpos = -4:xpos = 4;

        return 1;
    }
    if((y > 4)|| (y <-4))
    {
         (y< -4)? ypos = -4:ypos = 4;

        return 2;
    }
    else return 0;
}

static void withTimer(int val)
{
   int result=0;
    t += 0.03;

     result = check_Collision(xpos,ypos);

    if(result == 1)
      {
        ydes = 2*ypos - ycurr;
        xdes = xcurr;

        xcurr = xpos;
        ycurr = ypos;
        t = 0;
      }

     if(result == 2)
     {
        xdes = 2*xpos - xcurr;
        ydes = ycurr;

        xcurr = xpos;
        ycurr = ypos;

        t = 0;
      }

      if(abs(xdes - xcurr)<0.3)
        {
        xpos = xcurr + t*(xdes-xcurr)*10;
        ypos = ycurr + t*(ydes-ycurr)*10;
      }
      else{
        xpos = xcurr + t*(xdes-xcurr);
        ypos = ycurr + t*(ydes-ycurr);
      }

    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
    /*
    "70" is an arbitrary value due to user screen size,
     might scale differently on bigger or smaller screens.
     Affects where the little dot is placed based on mouse clicks to the screen
    */
    float scale = 70*(Wwidth/Wheight);

    float mx = (float) (x-Wwidth/2)/scale;
    float my = (float) (Wheight/2-y)/scale;

    switch(btn){
        case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
            {

                  mlocX = mx;
                  mlocY = my;

                  xcurr = xpos;
                  ycurr = ypos;

                  xdes = mx;
                  ydes = my;

                  t = 0;
               // get new mouse coordinates for x,y
               // use scale to match right
            }
            break;
    }
     glutPostRedisplay();
};



static void init(void)
{
    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);                 // assign a color you like

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Collision Example");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);
    //glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
