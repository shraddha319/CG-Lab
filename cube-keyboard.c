#include<stdio.h>
#include<GL/glut.h>

float vertices[8][3]={{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1},{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1}};
float color[8][3] = {{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
float theta[3] = {0,0,0}, viewer[3]={0,0,5};
int axis=2;

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
	polygon(7,6,5,4);
	polygon(4,5,1,0);
	polygon(2,6,7,3);
	polygon(7,4,0,3);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);
	glRotatef(theta[0],1,0,0);
	glRotatef(theta[1],0,1,0);
	glRotatef(theta[2],0,0,1);
	colorcube();
	glFlush();
	glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'x':viewer[0] -= 1; break;
		case 'X':viewer[0] += 1; break;
		case 'y':viewer[1] -= 1; break;
		case 'Y':viewer[1] += 1; break;
		case 'z':viewer[2] -= 1; break;
		case 'Z':viewer[2] += 1; break;
		case 'r': theta[axis]+= 1; if(theta[axis]>360) theta[axis]-=360; break;
	}
	glutPostRedisplay();
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glFrustum(-2,2,-2*(float)h/(float)w,2*(float)h/(float)w,2,20);
	else
		glFrustum(-2*(float)w/(float)h,2*(float)w/(float)h,-2,2,2,20);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}