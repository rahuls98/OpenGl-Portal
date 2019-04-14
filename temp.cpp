//Main version. Make NO changes.
/*
-------------------Headers-----------------------
*/

#include<iostream>
#include<unistd.h>
#include<math.h>
#include<string.h>
#include<stdio.h>

#include<OpenGL/gl.h>
#include<GLUT/glut.h>

/*
-------------------Global variables-----------------------
*/

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
using namespace std;
GLdouble cp_eqn[4] = {0.0, 0.0, 1.0, 0.0};
int choice;
float xmin = -8.0;
float xmax = 8.0;

//camera variables
float angle = 0.0, yAngle = 0.0;
int cam = 1;
float roll = 0.0f;

//camera and keyboard
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float lxs = -1.0f, lys = 0.0f, lzs = 0.0f;
//cam1
float x = -5.0f, z = 18.0f;
//cam2
float xside = 9.0f, yside = 2.5f,zside = -7.5f;

//mouse movements
float halfWidth= (float)(WINDOW_WIDTH/2.0);
float halfHeight = (float)(WINDOW_HEIGHT/2.0);
float mouseX = 0.0f, mouseY = 0.0f;

//ball variables
float b1 = 8.0;
float b2 = 18.0;
float b3 = 35.0;
float ang = 0.0;

/*
-------------------Set the cameras-----------------------
*/

//Portal Room 1 front camera
void cam1(){
    gluLookAt(x, 2.5f, z,
              x + lx, 2.5f + ly, z + lz,
              roll + 0.0f, 2.5f, 0.0f);
    glFlush();
}

//Portal Room 1 side camera
void cam2(){
    gluLookAt(xside, 2.5f, zside,
              -4.5,0.3,-7.6,
              roll + 0.0f, 2.5f, 0.0f);
    glFlush();
}

//Portal Room 2 front camera
void cam3(){
    gluLookAt(x, 3.0f, z,
              0, 3.0, -10.0,
              roll + 0.0f, 2.5f, 0.0f);
}

/*
-------------------Render the scene-----------------------
*/

//draw the portals in room 1 (User teleportation room)
void drawRoom1Doors(){
  //door1
  glColor3f(0.4f, 0.2f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(-6.0f, 0.0f, 0.0f);
  glVertex3f(-6.0f, 5.0f, 0.0f);
  glVertex3f(-3.0f, 5.0f, 0.0f);
  glVertex3f(-3.0f, 0.0f, 0.0f);
  glEnd();

  //door2
  glColor3f(0.4f, 0.2f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(9.9f, 0.0f, -9.0f);
  glVertex3f(9.9f, 5.0f, -9.0f);
  glVertex3f(9.9f, 5.0f, -6.0f);
  glVertex3f(9.9f, 0.0f, -6.0f);
  glEnd();
}

//draw the portals in room 2 (Object teleportation room)
void drawRoom2Doors(){
  //door1
  glColor3f(0.4f, 0.2f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(-6.0f, 0.0f, 0.0f);
  glVertex3f(-6.0f, 5.0f, 0.0f);
  glVertex3f(-3.0f, 5.0f, 0.0f);
  glVertex3f(-3.0f, 0.0f, 0.0f);
  glEnd();

  //door2
  glColor3f(0.4f, 0.2f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(9.9f, 0.0f, -9.0f);
  glVertex3f(9.9f, 5.0f, -9.0f);
  glVertex3f(9.9f, 5.0f, -6.0f);
  glVertex3f(9.9f, 0.0f, -6.0f);
  glEnd();

  //door3
  glColor3f(0.4f, 0.2f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(-9.9f, 0.0f, -9.0f);
  glVertex3f(-9.9f, 5.0f, -9.0f);
  glVertex3f(-9.9f, 5.0f, -6.0f);
  glVertex3f(-9.9f, 0.0f, -6.0f);
  glEnd();

  //door4
  glColor3f(0.4f, 0.2f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(7.5f, 6.9f, 1.5f);
  glVertex3f(2.5f, 6.9f, 1.5f);
  glVertex3f(2.5f, 6.9f, -1.5f);
  glVertex3f(7.5f, 6.9f, -1.5f);
  glEnd();
}

//draw ball
void drawBall(float ballx, float bally, float ballz){
    glColor3f(0.5,0.75,0.25);
    glLineWidth(1);
    glTranslatef(ballx,bally,ballz);
    glutSolidSphere(1.0,30,30);
    usleep(5000);
}

//draw teatpot
void drawTeaPot(){
  glPushMatrix();
  glColor3f(0.0f, 0.0f, 0.0f);
  glTranslated(-4.5,0.3,-7.6);
  glutSolidTeapot(0.6);
  glPopMatrix();
}

//main animation function
void renderScene(void){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  if(choice==1 || choice==2){
    glLoadIdentity();

    //toggle camera
    if(choice==1){
      if(cam==1)
        cam1();
      else if(cam==2)
        cam2();
    }
    else if(choice==2){
      cam = 3;
      cam3();
    }

    //Draw Floor
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();

    //back wall
    glColor3f(0.9294f, 0.9216f, 0.8353f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 7.0f, -10.0f);
    glVertex3f(10.0f, 7.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();

    //left wall
    glColor3f(1.0f, 0.851f, 0.702f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 7.0f, -10.0f);
    glVertex3f(-10.0f, 7.0f, 10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();

    //right wall
    glColor3f(1.0f, 0.851f, 0.702f);
    glBegin(GL_QUADS);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 7.0f, -10.0f);
    glVertex3f(10.0f, 7.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();

    //ceiling
    glColor3f(0.95f, 0.95f, 0.95f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 7.0f, -10.0f);
    glVertex3f(10.0f, 7.0f, -10.0f);
    glVertex3f(10.0f, 7.0f, 10.0f);
    glVertex3f(-10.0f, 7.0f, 10.0f);
    glEnd();

    //User teleportation room
    if(choice==1){
      drawRoom1Doors();
      drawTeaPot();
    }

    //object teleportation room
    else if(choice==2){
      drawRoom2Doors();

      //ball : portal2 -> portal3
      glPushMatrix();
      drawBall(b2,0.95,-7.5);
      b2 -= 0.05;
      if(ang>=360.0)
        ang = 0.0;
      ang+=30;
      glPopMatrix();

      //ball : portal4 -> ground
      glPushMatrix();
      drawBall(5.0,b3,0.0);
      if(b3>1.0){
        b3 -=0.05;
        if(ang>=360.0)
          ang = 0.0;
        ang+=30;
      }
      else
        b3 = 1.0;
      glPopMatrix();

      //ball : user -> portal1
      glClipPlane(GL_CLIP_PLANE0, cp_eqn);
      glEnable(GL_CLIP_PLANE0);
      drawBall(-4.5,0.95,b1);
      b1 -= 0.05;
      if(ang>=360.0)
        ang = 0.0;
      ang+=30;
      glDisable(GL_CLIP_PLANE0);
    }

    glFlush();
    glutSwapBuffers();
  }
}

//keyboard keys
void processSpecialKeys(int key, int xx, int yy){
  float fraction = 0.3f;
  switch(key){
    //left arrow key event
    case GLUT_KEY_LEFT:
      if(cam==1){
          x += sin(angle - M_PI/2.0) * fraction;
          z += -cos(angle - M_PI/2.0) * fraction;
      }
      else if(cam==3){
        if(x>xmin){
          //printf("\n%f",x);
          x += sin(angle - M_PI/2.0) * fraction;
          z += -cos(angle - M_PI/2.0) * fraction;
        }
      }
      else if(cam==2){
          zside -= sin(angle - M_PI/2.0) * fraction;
          xside -= -cos(angle - M_PI/2.0) * fraction;
      }
      break;

    //right arrow key event
    case GLUT_KEY_RIGHT:
      if(cam==1){
          x += sin(M_PI/2.0 + angle) * fraction;
          z += -cos(M_PI/2.0 + angle) * fraction;
      }
      else if(cam==3){
        if(x<xmax){
          x += sin(M_PI/2.0 + angle) * fraction;
          z += -cos(M_PI/2.0 + angle) * fraction;
        }
      }
      else if(cam==2){
          zside -= sin(M_PI/2.0 + angle) * fraction;
          xside -= -cos(M_PI/2.0 + angle) * fraction;
      }
      break;

    //top arrow key event
    case GLUT_KEY_UP:
      if(choice==1){
        if(x<-3 && x>-6 && z<0.5){
          cam = 2;
        }
        if(cam==1){
            x += lx * fraction;
            z += lz * fraction;
        }
        if(cam==2){
            xside += lxs * fraction;
            zside += lzs * fraction;
        }
      }
      break;

    //bottom arrow key event
    case GLUT_KEY_DOWN:
      if(choice==1){
        if(cam==1){
            x -= lx * fraction;
            z -= lz * fraction;
        }
        if(cam==2){
            xside -= lxs * fraction;
            zside -= lzs * fraction;
        }
      }
      break;

    //Exit
    case 27:
        exit(0);
  }
}

//mouse movement
void processMouseMovement(int xx, int yy){
    mouseX = (float)(halfWidth - xx)/halfWidth;
    mouseY = (float)(halfHeight - yy)/halfHeight;
    angle -= (0.003f * mouseX);
    lx = sin(angle);
    lz = -cos(angle);

    if(abs(yAngle) < (M_PI/2)){
        yAngle += (0.003f * mouseY);
    }
    ly = sin(yAngle);
}

//menu selection function
void demo_menu(int id){
  switch(id){
    case 0:exit(0);
           break;
    case 1:choice=1;
           break;
    case 2:choice=2;
           break;
  }
  glutPostRedisplay();
}

//window size and viewport
void changeSize(int w, int h){
  if(h==0)
    h=1;
  float ratio = w * 1.0 / h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0,0,w,h);
  halfWidth = (float)(w/2.0);
  halfHeight = (float)(h/2.0);
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

//refresh screen
void animate () {
    glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Portal");

  int config = glutCreateMenu(demo_menu);
  glutAddMenuEntry("Enter Portal Room 1",1);
  glutAddMenuEntry("Enter Portal Room 2",2);
  glutAddMenuEntry("Exit",0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(animate);
  glutSpecialFunc(processSpecialKeys);
  glutPassiveMotionFunc(processMouseMovement);

  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 1;
}
