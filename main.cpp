#include "fluid.h"
#include "glut.h"

extern double DT;
extern double g;

int main(int argc, char* argv[])
{
	printf("%f < %f\n", DT, 1.0f / sqrt(g));

	glutInit(&argc, argv);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutCreateWindow("Shallow water");

	Init();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	glutMainLoop();

	return 0;
}
