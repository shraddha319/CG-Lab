#include<stdio.h>
#include<GL/glut.h>

void wall(float thickness)
{
	glPushMatrix();
	glTranslatef(0.5,0.5*thickness,0.5);
	glScalef(1,thickness,1);
	glutSolidCube(1);
	glPopMatrix();
}

void tableleg(float leglen,float legthick)
{
	glPushMatrix();
	glTranslatef(0,leglen/2,0);
	glScalef(legthick,leglen,legthick);
	glutSolidCube(1);
	glPopMatrix();
}

void table(float topwid,float topthick, float leglen, float legthick)
{
	glPushMatrix();
	glTranslatef(0,leglen,0);
	glScalef(topwid,topthick,topwid);
	glutSolidCube(1);
	glPopMatrix();

	double dist = 0.95*topwid/2 - legthick/2;

	glPushMatrix();
	glTranslatef(dist,0,dist);
	tableleg(leglen,legthick);
	glTranslatef(0,0,-2*dist);
	tableleg(leglen,legthick);
	glTranslatef(-2*dist,0,2*dist);
	tableleg(leglen,legthick);
	glTranslatef(0,0,-2*dist);
	tableleg(leglen,legthick);
	glPopMatrix();
}

void display()
{
	float ambient[] = {0.1,0.1,0.1,0.1}, diffuse[]={0.5,0.5,0.5,0.5}, specular[] = {1,1,1,1}, shininess[]={50};
	float lightpos[] = {2,6,3,0}, lightintensity[] = {0.7,0.7,0.7,0.7};

	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightintensity);
	glLightfv(GL_LIGHT0,GL_POSITION,lightpos);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winht = 1;
	glOrtho(-winht*64/48,winht*64/48,-winht,winht,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3,1.3,2.0,0,0.25,0,0,1,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0.6,0.38,0.5);
	glRotatef(30,0,1,0);
	glutSolidTeapot(0.08);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4,0,0.4);
	table(0.6,0.02,0.3,0.02);
	glPopMatrix();

	wall(0.02);
	glPushMatrix();
	glRotatef(90,0,0,1);
	wall(0.02);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90,1,0,0);
	wall(0.02);
	glPopMatrix();
	glFlush();

}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("teapot");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glutMainLoop();
	return 0;
}