#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

int choice=0;
float x1=200,y1=200,x2=100,y2=300,x3=200,y3=400,x4=300,y4=300;

void draw_pixel(int x,int y)
{
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void edgedetect(float x1, float y1, float x2, float y2, int *le, int *re)
{
	float temp,mx;
	if((y2-y1)<0)
	{
		temp = y2;
		y2 = y1;
		y1 = temp;

		temp = x2;
		x2= x1;
		x1 = temp;
	}
	if((y2-y1)!=0)
		mx = (x2-x1)/(y2-y1);
	else mx = x2-x1;
	float x=x1;
	for(int i=y1;i<=y2;i++)
	{
		if(x<(float)le[i])
			le[i] = (int)x;
		if(x>(float)re[i])
			re[i] = (int)x;
		x += mx;
	}
}

void scanfill()
{
	int le[500],re[500];
	for(int i=0;i<500;i++)
	{
		le[i]=500;
		re[i]=0;
	}
	edgedetect(x1,y1,x2,y2,le,re);
	edgedetect(x2,y2,x3,y3,le,re);
	edgedetect(x3,y3,x4,y4,le,re);
	edgedetect(x4,y4,x1,y1,le,re);
	for(int y=0;y<500;y++)
	{
		if(le[y]<=re[y])
			for(int x=(int)le[y];x<=(int)re[y];x++)
				draw_pixel(x,y);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(choice==1)
	{
		glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
			glVertex2f(x4,y4);
		glEnd();
	}
	if(choice==2)
		scanfill();
	glFlush();
}

void menu(int id)
{
		glClear(GL_COLOR_BUFFER_BIT);
	switch(id)
	{
		case 1:choice=1; break;
		case 2:choice=2; break;
		case 3:exit(0);
	}
	glutPostRedisplay();
}

void init()
{
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("scanf fill");
	glutCreateMenu(menu);
	glutAddMenuEntry("draw",1);
	glutAddMenuEntry("fill",2);
	glutAddMenuEntry("exit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}