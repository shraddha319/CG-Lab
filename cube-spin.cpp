#include<stdio.h>
#include<GL/glut.h>

GLfloat vertices[8][3] = {{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1},{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1}}, theta[3] ={0,0,0};
GLfloat color[8][3] = {{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
int axis = 2;

void polygon(int a,int b,int c,int d)
{
	glBegin(GL_POLYGON);
		glColor3fv(color[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(color[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(color[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(color[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube()
{
	polygon(0,1,2,3);
	polygon(5,6,2,1);
	polygon(4,7,6,5);
	polygon(0,4,5,1);
	polygon(2,6,7,3);
	polygon(3,7,4,0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0],1,0,0);
	glRotatef(theta[1],0,1,0);
	glRotatef(theta[2],0,0,1);
	colorcube();
	glFlush();
	glutSwapBuffers();
}

void spincube()
{
	theta[axis] += 2;
	if(theta[axis]>360) theta[axis]-=360;
	glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) axis=0;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) axis=1;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) axis=2;
	spincube();
}


void myinit(){
	glClearColor(0,0,0,0);
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2,2,-2*(GLfloat)h/(GLfloat)w,2*(GLfloat)h/(GLfloat)w,-10,10);
	else
		glOrtho(-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("cube spin");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutIdleFunc(spincube);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}