#ifndef PROGRAM_H
#define PROGRAM_H

#include "GL.h"

class Program
{
public:
	Program(GLPtr gl,string vs_str,string fs_str)
	{
		this->gl = gl;
		vs = gl->CreateShader(VertexShader,vs_str);
		fs = gl->CreateShader(FragmentShader,fs_str);
		pl = gl->CreateProgram(vs,fs);
	}
	void DeclareAttribute(string semantic,string attribute)
	{
		gl->DeclareAttribute(semantic,attribute,pl);
	}
	void DeclareTexture(string semantic,string texture)
	{
		gl->DeclareTexture(semantic,texture,pl);
	}
	void DeclareUniform(string semantic,string uniform)
	{
		gl->DeclareUniform(semantic,uniform,pl);
	}
	void Bind()
	{
		gl->BindProgram(pl);
	}
private:
	GLPtr gl;
	ShaderID vs;
	ShaderID fs;
	ProgramID pl;

};

DECLARE_POINTER_OF(Program);

static ProgramPtr MakePipeline(GLPtr gl,string vs_str,string fs_str)
{
	return ProgramPtr(new Program(gl,vs_str,fs_str));
}

#endif