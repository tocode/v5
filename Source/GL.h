#ifndef OPENGL_H
#define OPENGL_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <map>
#include <vector>
#include <string>
#include "IDMap.h"
#include "Common.h"

using namespace std;

enum SemanticFormat
{
	RGB_UINT8,
	RGBA_UINT8,
	RGB_FLOAT32,
	RGBA_FLOAT32,
	XYZ_FLOAT32,
	XYZW_FLOAT32,
	UV_FLOAT32,
	INDEX_UINT32,
	DEPTH32,
	//DEPTH24_STENCIL8,
	DEPTH32F_STENCIL8,
};
enum ShaderType
{
	VertexShader = GL_VERTEX_SHADER,
	FragmentShader = GL_FRAGMENT_SHADER,
};
enum DataFormat
{
	DF_INT,
	DF_UINT,
	DF_FLOAT,
	DF_FLOAT2,
	DF_FLOAT3,
	DF_FLOAT4,
	DF_FLOAT4X4,
};
enum PrimitiveType
{
	PRIMITIVE_TRIANGLES,
	//PRIMITIVE_TRIANGLE_FAN,
	//PRIMITIVE_TRIANGLE_STRIP,
	//PRIMITIVE_QUADS,
	//PRIMITIVE_LINES,
	//PRIMITIVE_LINE_STRIP,
	//PRIMITIVE_LINE_LOOP,
	//PRIMITIVE_POINTS,
};

typedef ID ProgramID;
typedef ID ShaderID;
typedef ID VertexBufferID;
typedef ID IndexBufferID;
typedef ID TextureBufferID;
typedef ID TextureID;
typedef ID FrameBufferID;

struct ShaderRecord				{ GLuint id; };
struct VertexBufferRecord		{ GLuint id; };
struct IndexBufferRecord		{ GLuint id; };
struct TextureBufferRecord		{ GLuint id; };
struct TextureRecord			{ GLuint id; GLenum type; SemanticFormat format; };
struct FrameBufferRecord		{ GLuint id; };
struct DepthBufferRecord		{ GLuint id; };

struct IndexBinder				{ IndexBufferID indexbuffer;  GLenum glformat; int count;	};
struct InputBinder
{ 
	string semantic;
	GLuint vbid;
	int offset; 
	GLsizei stride; 
	GLenum gltype; 
	GLint glsize; 
};
struct TextureBinder			{ TextureID texid; };
struct UniformBinder
{
	string semantic;
	DataFormat type;
	GLsizei count;
	void* buffer;
};
struct ProgramRecord 
{ 
	GLuint program_id;
	ShaderID vs;
	ShaderID fs;
	map<string,GLint> alocations; 
	map<string,GLint> ulocations;
	map<string,GLint> tlocations;
	map<string,string> anames;
	map<string,string> tnames;
};

enum BlendFactor
{
	BLEND_ONE,
	BLEND_SRC_ALPHA,
	BLEND_SRC_ONE_MINUS_SRC_ALPHA,
};
enum ExportedType
{
	ET_ATTRIBUTE,
	ET_UNIFORM,
	ET_TEXTURE,
};
struct ExportedDeclaration
{
	ExportedType export_type;
	string name;
	string semantic;
};
class GL
{
public:
	GL(){Init();}
	void				Init();
							
	VertexBufferID	CreateVertexBuffer(const void* buffer, int size);
	IndexBufferID		CreateIndexBuffer(const void* buffer, int size);
	ShaderID			CreateShader(ShaderType type, string src);
	ProgramID		CreateProgram(ShaderID vs, ShaderID fs);
	TextureID		CreateTexture2D(const void* buffer, int width, int height, SemanticFormat format);
	TextureID		CreateTextureCube(void* buffer[], int width[], int height[], SemanticFormat format[]);


	void				DeclareAttribute(string semantic, string attribute, ProgramID pipeline);
	void				DeclareUniform(string semantic, string uniform, ProgramID pipeline);
	void				DeclareTexture(string semantic, string texture, ProgramID pipeline);

	ProgramID		CreateTheProgram(string vs_src,string fs_src,ExportedDeclaration* export_declararions,int export_declarations_num);

	void				BindShader(ShaderType type, ShaderID sd);
	void				BindInput(string semantic, VertexBufferID vb, int offset, int stride, DataFormat format);
	void				BindIndex(IndexBufferID ib, DataFormat format, int count);
	void				BindUniform(string semantic, DataFormat type, void* buffer, int count=1);
	void				BindTexture(string semantic, TextureID tx);
	void				BindProgram(ProgramID program);
	
	void				BindDepthStencilBuffer(TextureID texture);
	void				BindColorBuffer(int i,TextureID texture);

	void				DeleteVertexBuffer(VertexBufferID& vb);
	void				DeleteIndexBuffer(IndexBufferID& ib);
	void				DeleteShader(ShaderID& sd);
	void				DeleteTexture(TextureID& tx);
	void				DeleteProgram(ProgramID& pl);
	void				DeleteFrameBuffer(FrameBufferID& framebuffer);

	void				Scissor(float x,float y,float w,float h);
	
	void				ClearColorBuffer(float r = 0, float g = 0, float b = 0, float a = 0);
	void				ClearDepthBuffer(float depth = 1);
	void				ClearStencilBuffer(int s = 0);
	
	void				BindPrimitiveTopology(PrimitiveType primitive);

	void				Draw();

	void				Reset();
	void				ResetShaders();
	void				ResetInputs();
	void				ResetIndex();
	void				ResetTextures();
	void				ResetUniforms();
	void				ResetProgram();
	void				ResetDepthBuffer();
	void				ResetColorBuffer();

	void				SetBlendState(bool enable,BlendFactor src,BlendFactor dst);

private:
	FrameBufferID		CreateFrameBuffer();
	//void				BindFrameBuffer(FrameBufferID framebuffer);
	void				AttachTextureToFrameBuffer(FrameBufferID framebuffer, GLenum attachment, TextureID texture);
	//void				BeginFrameBuffer();
	void				BeginFrameBuffer();
	void				BeginInput(GLuint vb,int offset, GLsizei stride, GLenum gltype, GLint glsize, string attname);
	void				BeginUniform(GLint location, DataFormat type, void* buffer, GLsizei count);
	void				BeginTexture(GLuint texture, GLenum type, string name, int slot, GLuint program);
	void				BeginProgram();
	void				BeginProgram2();

	void				EndInput(string attname);
	void				EndTexture(string texname, int slot, GLuint program);
	void				EndUniform(GLint location,DataFormat type,GLsizei count);

public:
	
	ProgramID					CurrentProgramID;

	map<string,InputBinder>		InputSlots;
	map<string,UniformBinder>		UniformSlots;
	map<string,TextureBinder>		TextureSlots;

	IndexBinder					CurrentIndex; 
	PrimitiveType					CurrentPrimitiveTopology;
	TextureID					CurrentDepthStencilBufferID;
	
	FrameBufferID					CurrentFrameBufferID;
	vector<TextureID>				CurrentColorBufferIDs;
						
	ShaderID						CurrentVS;
	ShaderID						CurrentFS;
	GLuint						CurrentProgramGLID;

	IDMap<ProgramRecord>			ProgramRecords;
	IDMap<VertexBufferRecord>		VertexBufferRecords;
	IDMap<IndexBufferRecord>		IndexBufferRecords;
	IDMap<TextureRecord>			TextureRecords;
	IDMap<ShaderRecord>			ShaderRecords;
	IDMap<FrameBufferRecord>		FrameBufferRecords;

	bool							use_depth_stencil_buffer;
	bool							use_colorbuffer;

};
DECLARE_POINTER_OF(GL);
DEF_MAKEFUN_OF(GL);

#endif