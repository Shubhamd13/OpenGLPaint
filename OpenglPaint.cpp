#include<iostream>
#include <GL/glut.h>
#include <math.h>
#include<vector>

using namespace std;
//global
vector<float> f;
int height=500,width=500;
//prototype
void Draw();
//functions

    float colors=1.0f;
void mouseclick(int button, int state, int x, int y)
{
    float a1,b1;
    static int times=0;
    static float startx,starty;
    if(button==GLUT_LEFT_BUTTON and state==GLUT_DOWN)
    {
        a1=(float)x/height;
        b1=(float)(width-y)/width;
        if(a1>0 and a1<0.04)
        {
            if(b1>0 and b1<0.03)
            {
                colors=1.0f;
                return;
            }else if(b1>0.40 and b1<0.59)
            {
                colors=2.0f;
                return;
            }else if(b1>0.9 and b1<1.0)
            {
                colors=3.0f;
                return;
            }
        }
        f.push_back(a1);
        f.push_back(b1);
        if(times!=0)
        {
            //not start point of polygon(intermediate)
            f.push_back(colors);
            f.push_back(a1);
            f.push_back(b1);
        }else{
            //start point of polygon
            startx=a1;
            starty=b1;
        }
        times++;
    }
    if(button==GLUT_RIGHT_BUTTON and state==GLUT_DOWN)
    {
        //end point of last line
        f.push_back(startx);
        f.push_back(starty);
        f.push_back(colors);
        times=0;
    }
    glutPostRedisplay();
}
void addline(float x1,float Y1,float x2,float y2,float colors)
{
    if(colors==1.0f)
    {
        glColor3f(0.0,0.0,1.0);
    }
    if(colors==2.0f)
    {
        glColor3f(0.0,1.0,0.0);
    }
    if(colors==3.0f)
    {
        glColor3f(1.0,0.0,0.0);
    }
    float dx,dy,steps,xinc,yinc,y=Y1,x=x1;
    dx=x1-x2;
    dy=Y1-y2;
    if(fabs(dx)>fabs(dy)){
        steps=(fabs(dx)*1000.0f);
    }else{
        steps=(fabs(dy)*1000.0f);
    }
    xinc=(float)dx/(float)steps;
    yinc=(float)dy/(float)steps;
    for(float v=0.0;v<=steps;v+=1.0)
    {
		glVertex3f(x,y, 0.0);
        x-=xinc;
        y-=yinc;
    }
}
void Draw() {

    glClear(GL_COLOR_BUFFER_BIT);
	//all lines
	glPointSize(8.0);

    glBegin(GL_POINTS);
    for(int i=0;i<(f.size()/5);i++)
    {
        addline(f[i*5],f[i*5+1],f[i*5+2],f[i*5+3],f[i*5+4]);
    }
    glEnd();
	//blue
	glPointSize(30);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3f(0.02,0.01,0.0);
	glEnd();
	//green
	glPointSize(30.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(0.02,0.5,0.0);
	glEnd();
	//red
	glPointSize(30.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(0.02,0.99,0.0);
    glEnd();
	glFlush();
}

void Initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}
void reshap(int x,int y)
{
    height=x;
    width=y;
    glViewport(0.0,0.0,x,y);
}
void mouse(int x,int y)
{
    int a;
    float a1,b1;
    a=f.size();

    a1=(float)x/height;
    b1=(float)(width-y)/width;
    Draw();
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    if(a%5==2)
    {
        addline(f[a-2],f[a-1],a1,b1,colors);
    }
    glEnd();
    glFlush();
}
int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Shubham");
	Initialize();
	glutReshapeFunc(reshap);
	glutDisplayFunc(Draw);
	glutMouseFunc(mouseclick);
	glutPassiveMotionFunc(mouse);
	glutMainLoop();
	return 0;
}