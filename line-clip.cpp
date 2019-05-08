#include<stdio.h>
#include<GL/glut.h>
#define oc int

const int TOP=8, BOTTOM=4, LEFT=1, RIGHT=2;
int n;
GLfloat x0[4],y0[4],x1[4],y1[4];
GLfloat xmin=50,ymin=50,xmax=150,ymax=150, xvmin=250,yvmin=250,xvmax=400,yvmax=400;

oc outcode(GLfloat x, GLfloat y)
{
	oc res = 0;
	if(x<xmin)
		res |= LEFT;
	else if(x>xmax)
		res |= RIGHT;
	if(y<ymin)
		res |= BOTTOM;
	else if(y>ymax)
		res |= TOP;
	return res;
}

void cohensutherland(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1)
{
	oc oc0,oc1, ocout;
	oc0 = outcode(x0,y0);
	oc1 = outcode(x1,y1);
	bool done=false, accept=false;
	do
	{
		if(!(oc0|oc1))
		{
			done = true;
			accept = true;
		}
		else if(oc0 & oc1)
			done=true;
		else
		{
			ocout = oc0?oc0:oc1;
			GLfloat x,y;
			if(ocout&TOP)
			{
				y = ymax;
				x = (x1-x0)*(ymax-y0)/(y1-y0) + x0;
			}
			else if(ocout&BOTTOM)
			{
				y = ymin;
				x = (x1-x0)*(ymin-y0)/(y1-y0) + x0;
			}
			if(ocout&LEFT)
			{
				x = xmin;
				y = (y1-y0)*(xmin-x0)/(x1-x0) + y0;
			}
			else if(ocout&RIGHT)
			{
				x = xmax;
				y = (y1-y0)*(xmax-x0)/(x1-x0) + y0;
			}

			if(ocout==oc0)
			{
				x0 = x;
				y0 = y;
				oc0 = outcode(x0,y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				oc1 = outcode(x1,y1);
			}
		}
	}while(!done);

	if(accept)
	{
		GLfloat vx0,vy0,vx1,vy1;
		vx0 = xvmin + (xvmax-xvmin)*(x0-xmin)/(xvmax-xvmin);
		vx1 = xvmin + (xvmax-xvmin)*(x1-xmin)/(xvmax-xvmin);
		vy0 = yvmin + (yvmax-yvmin)*(y0-ymin)/(yvmax-yvmin);
		vy1 = yvmin + (yvmax-yvmin)*(y1-ymin)/(yvmax-yvmin);
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin,yvmin);
		glVertex2f(xvmax,yvmin);
		glVertex2f(xvmax,yvmax);
		glVertex2f(xvmin,yvmax);
		glEnd();

		glColor3f(0,0,1);
		glBegin(GL_LINES);
		glVertex2f(vx0,vy0);
		glVertex2f(vx1,vy1);
		glEnd();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin,ymin);
		glVertex2f(xmax,ymin);
		glVertex2f(xmax,ymax);
		glVertex2f(xmin,ymax);
	glEnd();

	glColor3f(0,0,1);
	for(int i=0;i<n;i++)
	{
		glBegin(GL_LINES);
		glVertex2f(x0[i],y0[i]);
		glVertex2f(x1[i],y1[i]);
		glEnd();
	}

	for(int i=0;i<n;i++)
		cohensutherland(x0[i],y0[i],x1[i],y1[i]);
	glFlush();
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
}

void myinit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,1);
}

int main(int argc,char** argv)
{
	printf("enter n\n");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("enter end points\n");
		scanf("%f%f%f%f",&x0[i],&y0[i],&x1[i],&y1[i]);
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("line clipping");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	myinit();

	glutMainLoop();
	return 0;
}
