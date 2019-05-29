#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>

using namespace std;

int choice,h=0,k=0;
float theta;

GLfloat triangle[3][3]={
    {100,150,200},
    {100,300,100},
    {1,1,1}};

GLfloat rot[3][3]={{0},{0},{0}},res[3][3];

void draw(GLfloat a[3][3])
{
	glBegin(GL_TRIANGLES);
		glVertex2f(a[0][0],a[1][0]);
		glVertex2f(a[0][1],a[1][1]);
		glVertex2f(a[0][2],a[1][2]);
	glEnd();
}

void rotate()
{
	rot[0][0] = cos(theta);
	rot[0][1] = -sin(theta);
	rot[0][2] = -h*(cos(theta)-1)+k*sin(theta);
	rot[1][0] = sin(theta);
	rot[1][1] = cos(theta);
	rot[1][2] = -k*(cos(theta)-1)-h*sin(theta);
	rot[2][0] = 0; 
	rot[2][1] = 0;
	rot[2][2] = 1;
}

void multiply()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			res[i][j] = 0;
			for(int k=0;k<3;k++)
				res[i][j] += rot[i][k]*triangle[k][j];
		}
}

void display()
{
	glColor3f(1,0,0);
	draw(triangle);
	rotate();
	multiply();
	glColor3f(0,1,0);
	draw(res);
	glFlush();
}

void myinit()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500,500,-500,500);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	printf("Enter 1 for rotation about origin, 2 for about pivot:");
	scanf("%d",&choice);
	if(choice==2)
	{
		printf("Enter pivot x and y:");
		scanf("%d%d",&h,&k);
	}
	printf("Enter angle of rotation\n");
	scanf("%f",&theta);
	theta = 3.14*theta/180;

	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);

	glutCreateWindow("triangle rotation");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}