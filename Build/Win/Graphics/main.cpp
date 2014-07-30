#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "DeferredApp.h"
#include "ForwardApp.h"
#include "ShadowMapApp.h"
#include "SSAOApp.h"
#include "HDRApp.h"

//App* app = new SSAOApp;
//App* app = new DeferredApp;
//App* app = new ForwardApp;
//App* app = new ShadowMapApp;
App* app = new HDRApp;

void initialize()
{
	app->Initialize();
}
void display()
{
	app->Display();
}
void keyboard(unsigned char key, int x, int y)
{
	app->KeyDown(key);
}
void passive_motion(int x,int y)
{
	app->MoveTo(x,y);
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
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_STENCIL|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("V5");

	printf("OpenGL Version:\t%s\n", glGetString(GL_VERSION));
	printf("GLEW Version:\t%s\n", glewGetString(GLEW_VERSION));

	if ( GLenum err = glewInit() )
		printf("GLEW Error: %s\n", glewGetErrorString(err));

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passive_motion);
	glutIdleFunc(idle);

	initialize();
	glutMainLoop();
	cleanup();

	return 0;
}