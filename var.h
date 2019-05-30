#include<OpenGL/gl.h>
#include<GLUT/glut.h>
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
using namespace std;
GLdouble cp_eqn[4] = {0.0, 0.0, 1.0, 0.0};
int choice;
float xmin = -6.0;
float xmax = 6.0;
float posChasm = 1.0f;
float negChasm = -3.0f;
char title[] = "Portal system";
char name1[] = "Rahul Suresh (1PE16CS188)";
char name2[] = "Chinmoy Dutta (1PE16CS189)";
char configurations[] = "Configurations";
char room1[] = "Room 1 : User teleportation";
char room2[] = "Room 2 : Object teleportation";
char esc[] = "Press 'esc' to quit";
int flag=0;

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
