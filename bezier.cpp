#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.1416

GLfloat theta = 0;

typedef struct point
{
	GLfloat x,y,z;
}point;

void bino(GLint *C,int n)
{
	for(int k=0;k<=n;k++)
	{
		C[k]=1;
		for(int i=n;i>=k+1;i--)
			C[k] *= i;
		for (int j=n-k;j>=2;j--)
			C[k] /= j;
	}
}

void bezier(point *ctrlpts, int nctrlpts, int nbezcurvept)
{
	GLint *C = new GLint[nctrlpts];
	bino(C,nctrlpts-1);
	point bezpoint;
	GLfloat u;

	glBegin(GL_LINE_STRIP);
	for(int i=0;i<=nbezcurvept;i++)
	{
		GLfloat blendfunct = 0;
		u = GLfloat(i)/GLfloat(nbezcurvept);
		bezpoint.x = bezpoint.y = bezpoint.z = 0;
		for(int k=0;k<nctrlpts;k++)
		{	
			blendfunct = C[k] * pow(u,k) *pow(1-u,nctrlpts-k);
			bezpoint.x += ctrlpts[k].x *blendfunct;			
			bezpoint.y += ctrlpts[k].y *blendfunct;
			bezpoint.z += ctrlpts[k].z *blendfunct;
		}
		glVertex2f(bezpoint.x,bezpoint.y);
	}
	glEnd();
	delete[]C;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	point ctrlpts[4] = {
		{20,100,0},
		{30,110,0},
		{50,90,0},
		{60,100,0}
	};
	float theta=0;
	int nctrlpts = 4, nbezcurvept = 20;
	ctrlpts[1].x += 10*sin(theta*PI/180);
	ctrlpts[1].y += 10*sin(theta*PI/180);
	ctrlpts[2].x -= 10*sin((theta+30)*PI/180);
	ctrlpts[2].y -= 10*sin((theta+30)*PI/180);
	ctrlpts[3].x -= 4*sin(theta*PI/180);
	ctrlpts[3].y += sin((theta-30)*PI/180);

	theta += 1;
		glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1.0, 1.0, 1.0);

			glPointSize(5);
	glPushMatrix();
	glLineWidth(5);
		

	glColor3f(255/255,153/255.0,51/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(ctrlpts,nctrlpts,nbezcurvept);
	}
	glColor3f(1,1,1);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(ctrlpts,nctrlpts,nbezcurvept);
	}
	glColor3f(19/255,136/255,8/255);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(ctrlpts,nctrlpts,nbezcurvept);
	}
	glPopMatrix();
	glColor3f(0.7,0.5,0.3);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(20,100);
	glVertex2f(20,40);
	glEnd();
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}



void reshape(int w,int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 130, 0, 130);
	//glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc,char ** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("flag");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}