#include<stdio.h>
#include<GL/glut.h>
#include<math.h> 
#define PI 3.14

float theta=0;
int choice=0;

typedef struct wcPt3D
{
	float x,y,z;
}wcPt3D;

void bino(int n, int *C)
{
	int k,i;
	for(k=0;k<=n;k++)
	{
		C[k] = 1;
		for(i=n;i>=(k+1);i--)
			C[k]*=i;
		for(i=n-k;i>=1;i--)
			C[k]/=i;
	}
}

void ComputeBezier(float u, wcPt3D *BezPt, int nCtrlPts, wcPt3D *CtrlPts, int *C)
{
	float blendfunc;
	int n = nCtrlPts-1;
	BezPt->x = BezPt->y = BezPt->z = 0;
	for(int k=0;k<nCtrlPts;k++)
	{
		blendfunc = C[k] * pow(u,k) * pow((1-u),(n-k));
		BezPt->x += (CtrlPts[k].x)*blendfunc;
		BezPt->y += (CtrlPts[k].y)*blendfunc;
		BezPt->z += (CtrlPts[k].z)*blendfunc;
	}
}

void bezier(wcPt3D *CtrlPts, int nCtrlPts, int nBezPts)
{
	wcPt3D BezPt;
	float u;
	int *C =new GLint[nCtrlPts];
	bino(nCtrlPts-1,C);
	glBegin(GL_LINE_STRIP);
	for(int i=0;i<=nBezPts;i++)
	{
		u = float(i)/float(nBezPts);
		ComputeBezier(u, &BezPt, nCtrlPts, CtrlPts, C);
		glVertex2f(BezPt.x, BezPt.y);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int nCtrlPts=4, nBezPts=20;

	if(choice==1||choice==2){
	wcPt3D CtrlPts[4] =
	{ {20,100,0},
	  {30,110,0},
 	  {50,90,0},
	  {60,100,0}
	};

	CtrlPts[1].x += 10*sin(theta*PI/180);
	CtrlPts[1].y += 10*sin(theta*PI/180);

	CtrlPts[2].x -= 10*sin((theta+30)*PI/180);
	CtrlPts[2].y -= 10*sin((theta+30)*PI/180);

	CtrlPts[3].x -= sin(theta*PI/180);
	CtrlPts[3].y += sin((theta-30)*PI/180);

	if(choice==2) theta += 2;

	glPushMatrix();
	glPointSize(5);
	glLineWidth(10);

	glColor3f(255/255,153/255.0,51/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(CtrlPts,nCtrlPts,nBezPts);
	}

	glColor3f(1,1,1);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(CtrlPts,nCtrlPts,nBezPts);
	}

	glColor3f(19/255.0,136/255.0,8/255.0);
	for(int i=0;i<8;i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(CtrlPts,nCtrlPts,nBezPts);
	}
	glPopMatrix();

	glColor3f(0.7,0.5,0.3);
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(20,100);
		glVertex2f(20,40);
	glEnd();
}
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,130,0,130);
	glMatrixMode(GL_MODELVIEW);
}

void menu(int id)
{
	switch(id)
	{
		case 1:choice=1; break;
		case 2:choice=2; break;
		case 3:exit(0);
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Bezier curve - flag");
	glutCreateMenu(menu);
	glutAddMenuEntry("Draw",1);
	glutAddMenuEntry("Animation",2);
	glutAddMenuEntry("Exit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}