#include<stdio.h>
#include<GL/glut.h>
int x1,x2,y1,y2;
void init(){
glClear(GL_COLOR_BUFFER_BIT);
glClearColor(0.0,0.0,0.0,1.0);
gluOrtho2D(0,500,0,500);
}
void drawp(int x,int y){
glBegin(GL_POINTS);
glColor3f(1.0,1.0,0.0);
glVertex2i(x,y);
glEnd();
sleep(1);
glFlush();
}
void display(){
int dx,dy,e,incx,incy,x,y,i;
dx=x2-x1;
dy=y2-y1;
if(dx<0)   dx=-dx;
if(dy<0)   dy=-dy;
incx=1;
if(x1>x2)   incx=-1;
incy=1;
if(y1>y2)   incy=-1;
x=x1;y=y1;
if(dx>dy){
    e=2*dy-dx;
    drawp(x,y);
    for(i=0;i<dx;i++){
    if(e>=0){
        y+=incy;
        e+=2*dy-2*dx;
    }
    else{
        e+=2*dy;
    }
    x+=incx;
    drawp(x,y);
    }
}
else{
e=2*dx-dy;
    drawp(x,y);
    for(i=0;i<dy;i++){
    if(e>=0){
        x+=incx;
        e+=2*dx-2*dy;
    }
    else{
        e+=2*dx;
    }
    y+=incy;
    drawp(x,y);
    }
}
}
int main(int argc,char* argv){
    printf("Enter x1,y1,x2,y2\n");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Line draw");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
