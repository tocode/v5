#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "CubeApp.h"
#include "FrameApp.h"

//App* app = new CubeApp;
App* app = new FrameApp;

void initialize()
{
	app->Initialize();
}
void display()
{
	app->Display();
}
void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
		case 27: exit(0); break;
	}
}
void idle()
{
	glutPostRedisplay();
}
void cleanup()
{
	app->Cleanup();
}
int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(480,320);
	glutInitWindowPosition(200,200);
	glutCreateWindow("V5");

	printf("OpenGL Version:\t%s\n", glGetString(GL_VERSION));
	printf("GLEW Version:\t%s\n", glewGetString(GLEW_VERSION));

	if ( GLenum err = glewInit() )
		printf("GLEW Error: %s\n", glewGetErrorString(err));

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	initialize();
	glutMainLoop();
	cleanup();

	return 0;
}