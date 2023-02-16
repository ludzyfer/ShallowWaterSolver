#include "glut.h"

void Init(void)
{
    glClearColor(1, 1, 1, 0);
    InitSurface();
    //std::cout << "init"<<std::endl;
}

void Idle(void)
{
    CalculateSurface();

    glutPostRedisplay();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawFluidSurface();

    glutSwapBuffers();
}


void Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}


void SpecialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        break;
    case GLUT_KEY_DOWN:
        break;
    case GLUT_KEY_LEFT:
        break;
    case GLUT_KEY_RIGHT:
        break;
    }
    glutPostRedisplay();
}
