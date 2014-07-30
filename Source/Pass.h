#ifndef PASS_H
#define PASS_H

#include <map>
#include "GL.h"
#include "Program.h"
#include "Uniform.h"
#include "Texture.h"

class Pass
{
public:
	void SetProgram(ProgramPtr pipeline)
	{
		this->pipeline = pipeline;
	}
	void AttachTexture(string semantic,TexturePtr texture)
	{
		textures[semantic] = texture;
	}
	void AttachUniform(string semantic,UniformPtr uniform)
	{
		uniforms[semantic] = uniform;
	}
	void Bind(GLPtr gl)
	{
		pipeline->Bind();
		for (auto it=textures.begin(); it!=textures.end(); it++)	
		{
			auto semantic = it->first;
			auto texture = it->second;
			texture->Bind(semantic);
		}
		for (auto it=uniforms.begin(); it!=uniforms.end(); it++)
		{
			auto semantic = it->first;
			auto uniform = it->second;
			uniform->Bind(gl,semantic);
		}
	}
private:
	GLPtr gl;
	ProgramPtr pipeline;
	std::map<string,TexturePtr> textures;
	std::map<string,UniformPtr> uniforms;
};
DECLARE_POINTER_OF(Pass);
DEF_MAKEFUN_OF(Pass);

#endif