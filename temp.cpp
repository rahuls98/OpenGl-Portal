//temp version
/*
-------------------Headers-------------------------------
*/

#include<iostream>
#include<unistd.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#include "imageloader.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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
float posChasm = 1.0f;
float negChasm = -3.0f;
char title[] = "Portal system";
char name1[] = "Rahul Suresh (1PE16CS188)";
char name2[] = "Chinmoy Dutta (1PE16CS189)";
char configurations[] = "Configurations";
char room1[] = "Room 1 : User teleportation";
char room2[] = "Room 2 : Object teleportation";
char esc[] = "Press 'esc' to quit";

//camera variables
float angle = 0.0, yAngle = 0.0;
int cam = 1;
float roll = 0.0f;

//camera and keyboard
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float lxs = -1.0f, lys = 0.0f, lzs = 0.0f;
//cam1
float x = -5.0f, y = 2.5f, z = 18.0f;
//cam2
//float x2 = 9.0f, yside = 2.5f,z2 = -7.5f;
float xside = -9.0f, yside = 2.5f, zside = -7.5f;
//cam3
//float x3 = 0.0f;

//mouse movements
float halfWidth= (float)(WINDOW_WIDTH/2.0);
float halfHeight = (float)(WINDOW_HEIGHT/2.0);
float mouseX = 0.0f, mouseY = 0.0f;

//ball variables
float b1 = 8.0;
float b2 = 18.0;
float b3 = 35.0;
float ang = 0.0;

void reset(){
  lx = 0.0f;
  ly = 0.0f;
  lz = -1.0f;
  lxs = -1.0f;
  lys = 0.0f;
  lzs = 0.0f;
  x = -5.0f;
  y = 2.5f;
  z = 18.0f;
  xside = -9.0f;
  yside = 2.5f;
  zside = -7.5f; 
  b1 = 8.0;
  b2 = 18.0;
  b3 = 35.0;
  ang = 0.0;
}

/*
-------------------Set the cameras-----------------------
*/

//Portal Room 1 front camera
void cam1(){
    gluLookAt(x, y, z,
              x + lx, 2.5f + ly, z + lz,
              roll + 0.0f, 2.5f, 0.0f);
    glFlush();
}

//Portal Room 1 side camera
void cam2(){
    gluLookAt(xside, 2.5f, zside,
              4.5,0.8,-7.0,
              //-4.5f, 0.3f, -2.0f,
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
-------------------Textures-----------------------
*/

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
//GLuint _textureId2;

void texPortal(){
  Image* image = loadBMP("portal.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void texWall(){
  Image* image = loadBMP("greymarble_brick.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void texLava(){
  Image* image = loadBMP("lava.bmp");
	_textureId = loadTexture(image);
	delete image;
}

/*
-------------------Doors----------------------------
*/

void door(float widthStart, float heightStart, int axis, float axisVal){
  float width = 3.0;
  float height = 5.0;
  switch(axis){
    case 1: //perp to x axis
            texPortal();
            glEnable(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
	          glTexCoord2f(0.0f, 0.0f);
            glVertex3f(axisVal, heightStart,        widthStart);
            glTexCoord2f(2.0f, 0.0f);          
            glVertex3f(axisVal, heightStart+height, widthStart);
            glTexCoord2f(2.0f, 1.0f);
            glVertex3f(axisVal, heightStart+height, widthStart-width);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(axisVal, heightStart,        widthStart-width);  
            glEnd();
            glDisable(GL_TEXTURE_2D);
            break;

    case 2: //perp to y axis
            texPortal();
            glEnable(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
	          glTexCoord2f(0.0f, 0.0f);
            glVertex3f(heightStart+height, axisVal, widthStart);
            glTexCoord2f(2.0f, 0.0f);          
            glVertex3f(heightStart,        axisVal, widthStart);
            glTexCoord2f(2.0f, 1.0f);
            glVertex3f(heightStart,        axisVal, widthStart-width);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(heightStart+height, axisVal, widthStart-width);   
            glEnd();
            glDisable(GL_TEXTURE_2D);
            break;

    case 3: //perp to z axis
            texPortal();
            glEnable(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 0.0f, 1.0f);
	          glTexCoord2f(0.0f, 0.0f);
            glVertex3f(widthStart-width, heightStart,        axisVal);
            glTexCoord2f(2.0f, 0.0f);          
            glVertex3f(widthStart-width, heightStart+height, axisVal);
            glTexCoord2f(2.0f, 1.0f);
            glVertex3f(widthStart,       heightStart+height, axisVal);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(widthStart,       heightStart,        axisVal); 
            glEnd(); 
            glDisable(GL_TEXTURE_2D);   
            break;
  }
}

void drawRoom1Doors(){
  door(-3.0f ,0.0f ,3 ,3.0f);
  door(-6.0f ,0.0f ,1 ,-9.9f);

  //chasm top layer
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(-9.0f, 0.1f, 1.0f);
  glVertex3f(-9.0f, 0.1f, -3.0f);
  glVertex3f(9.0f, 0.1f, -3.0f);
  glVertex3f(9.0f, 0.1f, 1.0f);
  glEnd();

  //chasm bottom layer
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(-9.0f, -0.1f, 1.0f);
  glVertex3f(-9.0f, -0.1f, -3.0f);
  glVertex3f(9.0f, -0.1f, -3.0f);
  glVertex3f(9.0f, -0.1f, 1.0f);
  glEnd();
}

void drawRoom2Doors(){
  door(-3.0f, 0.0f, 3, 0.0f);
  door(-6.0f, 0.0f, 1, 9.9f);
  door(-6.0f, 0.0f, 1, -9.9f);
  door(1.5f, 2.5f, 2, 6.9f);
}

/*
-------------------Objects-----------------------
*/

//draw ball
void drawBall(float ballx, float bally, float ballz){
    glColor3f(0.556863, 0.137255, 0.137255);
    glLineWidth(1);
    glTranslatef(ballx,bally,ballz);
    glutWireSphere(1.0,40,40);
    usleep(5000);
}

//draw teatpot
void drawTeaPot(){
  glPushMatrix();
  glColor3f(0.556863, 0.137255, 0.137255);
  //glTranslated(-4.5,0.3,-7.6);
  //glTranslated(-4.5,0.3,-2.0);
  glTranslated(4.5,0.5,-7.0);
  glutSolidTeapot(0.6);
  glPopMatrix();
}

/*
-------------------Render scene-----------------------
*/

void fall(){
  y -= 0.08;
}

//main animation function
void renderScene(void){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, _textureId);

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
    texWall();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-10.0f, 7.0f, -10.0f);
    glTexCoord2f(5.0f, 2.0f);
    glVertex3f(10.0f, 7.0f, -10.0f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //left wall
    texWall();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-10.0f, 7.0f, -10.0f);
    glTexCoord2f(5.0f, 2.0f);
    glVertex3f(-10.0f, 7.0f, 10.0f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //right wall
    texWall();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(10.0f, 7.0f, -10.0f);
    glTexCoord2f(5.0f, 2.0f);
    glVertex3f(10.0f, 7.0f, 10.0f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

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
      
      if(z<posChasm){
        if(y>-30.0)
          fall();
      }
    }

    //object teleportation room
    else if(choice==2){
      drawRoom2Doors();

      //ball : portal2 -> portal3
      glPushMatrix();
      drawBall(b2,0.95,-7.5);
      b2 -= 0.1;
      if(ang>=360.0)
        ang = 0.0;
      ang+=30;
      glPopMatrix();

      //ball : portal4 -> ground
      glPushMatrix();
      drawBall(5.0,b3,0.0);
      if(b3>1.0){
        b3 -=0.1;
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
      b1 -= 0.1;
      if(ang>=360.0)
        ang = 0.0;
      ang+=30;
      glDisable(GL_CLIP_PLANE0);
    }

    glFlush();
    glutSwapBuffers();
  }
}

void scene1(void){
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);  
  glLineWidth(2.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 2500, 0, 2500);

  //title
  glPushMatrix();  
  glTranslatef(50,2000,0);
  for (int i = 0; i < strlen(title); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, title[i]);
  }
  glPopMatrix();

  //Name1
  glPushMatrix();  
  glTranslatef(50,1600,0);
  for (int i = 0; i < strlen(name1); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, name1[i]);
  }
  glPopMatrix();

  ///Name2
  glPushMatrix();  
  glTranslatef(50,1400,0);
  for (int i = 0; i < strlen(name2); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, name2[i]);
  }
  glPopMatrix();

  //Configurations
  glPushMatrix();  
  glTranslatef(50,1000,0);
  for (int i = 0; i < strlen(configurations); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, configurations[i]);
  }
  glPopMatrix();

  //Room1 desc
  glPushMatrix();  
  glTranslatef(50,800,0);
  for (int i = 0; i < strlen(room1); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, room1[i]);
  }
  glPopMatrix();

  //Room2 desc
  glPushMatrix();  
  glTranslatef(50,600,0);
  for (int i = 0; i < strlen(room2); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, room2[i]);
  }
  glPopMatrix();

  //Quit
  glPushMatrix();  
  glTranslatef(50,400,0);
  for (int i = 0; i < strlen(esc); i++) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, esc[i]);
  }
  glPopMatrix();
  glutSwapBuffers();
}

/*
-------------------Rest-----------------------
*/

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
          xside -= sin(angle - M_PI/2.0) * fraction;
          zside -= -cos(angle - M_PI/2.0) * fraction;
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
          xside -= sin(M_PI/2.0 + angle) * fraction;
          zside -= -cos(M_PI/2.0 + angle) * fraction;
      }
      break;

    //top arrow key event

    case GLUT_KEY_UP:
      if(choice==1){
        if(x<-3 && x>-6 && z<3.5){
          cam = 2;
        }
        if(cam==1){
            x += lx * fraction;
            z += lz * fraction;
        }
        if(cam==2){
            xside -= lxs * fraction;
            zside -= lzs * fraction;
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
            xside += lxs * fraction;
            zside += lzs * fraction;
        }
      }
      break;

    
    case 'c':
      if(choice==1)
        choice = 2;
      else if(choice==2){
        choice = 1;
        cam = 1;
      }
      reset();
      break;

    
    case 'r':
      reset();
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

void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//refresh screen
void animate () {
    glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
  //description window
  glutInitWindowPosition(0, 200);
  glutInitWindowSize(430,500);
  glutCreateWindow("Project description");
  glutDisplayFunc(scene1);
  //portal window
  glutInitWindowPosition(435,150);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Portal");
  initRendering();
  //menu
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
