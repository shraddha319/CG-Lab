#include<stdio.h>
#include<GL/glut.h>

int n;
GLfloat v[4][3] = {{0,0,1},{0.8164,-0.4714,-0.333},{-0.8164,-0.4714,-0.333},{0,0.9428,-0.333}};

void triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
	glBegin(GL_POLYGON);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}

void DivideTriange(GLfloat *a, GLfloat *b , GLfloat *c, int m)
{
	GLfloat v1[3],v2[3],v3[3];
	if(m>0)
	{
		for(int j=0;j<3;j++) v1[j]=(a[j]+b[j])/2;
		for(int j=0;j<2;j++) v2[j]=(a[j]+c[j])/2;
		for(int j=0;j<2;j++) v3[j]=(b[j]+c[j])/2;
		DivideTriange(a,v1,v2,m-1);
		DivideTriange(b,v1,v3,m-1);
		DivideTriange(c,v2,v3,m-1);
	}
	else triangle(a,b,c);
}

void tetrahedron(int m)
{
	glColor3f(1,0,0);
	DivideTriange(v[0],v[1],v[2],m);
	glColor3f(0,1,0);
	DivideTriange(v[0],v[1],v[3],m);
	glColor3f(0,0,1);
	DivideTriange(v[0],v[2],v[3],m);
	glColor3f(1,1,0);
	DivideTriange(v[1],v[2],v[3],m);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	tetrahedron(n);
	glFlush();
}

void init()
{
	glOrtho(-2,2,-2,2,-10,10);
	glClearColor(1,1,1,1);

}

int main(int argc, char **argv)
{
	printf("Enter n:");
	scanf("%d",&n);

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("3D Sierpinski gasket");
	init();
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}