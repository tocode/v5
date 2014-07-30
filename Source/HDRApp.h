#ifndef HDRAPP_H
#define HDRAPP_H

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
#include "SSAO.h"
#include "Timer.h"
#include "DownSampler.h"

class HDRApp: public App
{
public:
	void Initialize()
	{
		width = glutGet(GLUT_WINDOW_WIDTH);
		height = glutGet(GLUT_WINDOW_HEIGHT);

		timer.Start();
		render_count = 0;

		gl = MakeGL();

		TexturePtr texture = LoadTexture(gl,"phoenix.pcx");
		mesh = LoadMesh(gl,"phoenix_ugv.md2",true);
		camera = MakeCamera(Vector3(0,0,0),Vector3(0,0,-1),Vector3(0,1,0),60,width/height);

		//skybox = MakeSkyBox();
		//skybox->Init(gl);

		deferred = MakeDeferredShading();
		deferred->Init(gl,width,height);
		deferred->SetTexture(texture);
		deferred->SetMesh(mesh);

		downsampler0 = MakeDownSampler();
		downsampler0->Init(gl,width,height);

		downsampler1 = MakeDownSampler();
		downsampler1->Init(gl,width/4,height/4);

		tank_z=-150;
	}
	void Display()
	{
		//glClearColor(0.1, 0.3, 0.6, 0.0);
		//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//skybox->SetLocation(camera->Position());
		//skybox->SetVP(camera->VPMatrix());
		//skybox->render();

		static float angle = 0;
		angle += PI/256;
		if (angle>2*PI) angle = 0;
		Matrix4 world = Translate(Vector3(0.0, -50.0, tank_z)) * Rotate(Vector3(0,1,0),angle);
		Matrix4 vp = camera->VPMatrix();
		Matrix4 wvp = vp * world;
		Vector3 eye = camera->Position();

		deferred->SetWVP(wvp);
		deferred->SetVP(vp);
		deferred->SetW(world);
		deferred->Render();

		downsampler0->SetInput(deferred->shaded_tx);
		downsampler0->Render();
		downsampler0->ShowOutput();

		//downsampler1->SetInput(downsampler0->output_tx);
		//downsampler1->Render();
		//downsampler1->ShowOutput();

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
		case 'z':
			tank_z+=30;
			break;
		case 'x':
			tank_z-=30;
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
	DeferredShadingPtr			deferred;
	Timer						timer;
	long						render_count;
	float						tank_z;

	DownSamplerPtr				downsampler0;
	DownSamplerPtr				downsampler1;
};

#endif