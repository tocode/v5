#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include "CanvasApp.h"
#include "UIApp.h"

//App* app = new CanvasApp;
App* app = new UIApp;

void initialize()
{
	app->Initialize();
}
void display()
{
	app->Display();
	glutSwapBuffers();
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
void mouse_click(int button,int state,int x,int y)
{
	if (button==GLUT_LEFT_BUTTON)
		if (state==GLUT_DOWN)
		{
			UITouch touch = { TOUCH_DOWN, x, y };
			app->Touch(&touch);
		}
		else if (state==GLUT_UP)
		{
			UITouch touch = { TOUCH_UP, x, y };
			app->Touch(&touch);
		}
}
void mouse_drag(int x,int y)
{
	UITouch touch = { TOUCH_MOVE, x, y };
	app->Touch(&touch);
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
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse_drag);
	glutIdleFunc(idle);

	initialize();
	glutMainLoop();
	cleanup();

	return 0;
}