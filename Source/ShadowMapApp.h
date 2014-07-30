#ifndef SHADOWMAPAPP_H
#define SHADOWMAPAPP_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "App.h"
#include "GL.h"
#include "Mathematics.h"
#include "Mesh.h"
#include "Pass.h"
#include "Camera.h"
#include "MeshFactory.h"
#include "TextureFactory.h"
#include "SkyBox.h"
#include "Shadowmap.h"
#include "Timer.h"

class ShadowMapApp: public App
{
public:
	void Initialize()
	{
		width = glutGet(GLUT_WINDOW_WIDTH);
		height = glutGet(GLUT_WINDOW_HEIGHT);

		timer.Start();
		render_count = 0;

		gl = MakeGL();

		shadowmap = MakeShadowMap();
		shadowmap->Init(gl,width,height);
		shadowmap->SetMesh(LoadMesh(gl,"phoenix_ugv.md2"));
		shadowmap->SetTexture(LoadTexture(gl,"phoenix.pcx"));
		shadowmap->SetLightPos(Vector3(0,100,-151));
		camera = MakeCamera(Vector3(0,0,0),Vector3(0,0,-1),Vector3(0,1,0),60,width/height,1,300);
	}
	void Display()
	{
		static float angle = 0;
		angle += PI/256;
		if (angle>2*PI) angle = 0;
		Matrix4 world = Translate(Vector3(0.0, -30.0, -150)) * Rotate(Vector3(0,1,0),angle) * Scale(Vector3(0.6,0.6,0.6));
		Matrix4 wvp = camera->VPMatrix() * world;
		Vector3 eye = camera->Position();

		shadowmap->SetWVP(wvp);
		shadowmap->SetVP(camera->VPMatrix());
		shadowmap->SetW(world);
		shadowmap->Render();

		glutSwapBuffers();
		render_count++;
	}
	void KeyDown(int key)
	{
		switch (key)
		{
		case 'w':
			camera->Forward(10);
			break;
		case 's':
			camera->Backward(10);
			break;
		case 'a':
			camera->StrafeLeft(8);
			break;
		case 'd':
			camera->StrafeRight(8);
			break;
		case 'j':
			camera->Yaw(20/width*(60.0/360)*2*PI);
			break;
		case 'l':
			camera->Yaw(-20/width*(60.0/360)*2*PI);
			break;
		case 'i':
			camera->Pitch(20/height*(60.0/360)*2*PI);
			break;
		case 'k':
			camera->Pitch(-20/height*(60.0/360)*2*PI);
			break;
		case 't':
			timer.Finish();
			printf("FPS = %f \n",render_count/timer.Duration());
			break;
		case 27: 
			exit(0); 
			break;
		}
	}
private:
	GLPtr						gl;
	MeshPtr						mesh;
	CameraPtr					camera;
	float						width;
	float						height;

	SkyBoxPtr					skybox;
	ShadowMapPtr				shadowmap;
	Timer						timer;
	long						render_count;
};

#endif