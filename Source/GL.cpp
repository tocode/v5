#ifndef OPENGLRENDERER_IMP
#define OPENGLRENDERER_IMP

#include "GL.h"
#include <map>
#include <assert.h>


void GL::Init()
{
	CurrentFrameBufferID = CreateFrameBuffer();
	Reset();
}
VertexBufferID GL::CreateVertexBuffer(const void* buffer, int size)
{
	VertexBufferRecord vertexbuffer;
	glGenBuffers(1,&vertexbuffer.id);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer.id);
	glBufferData(GL_ARRAY_BUFFER,size,buffer,GL_STATIC_DRAW);
	return VertexBufferRecords.insert(vertexbuffer);
}
IndexBufferID GL::CreateIndexBuffer(const void* buffer, int size)
{
	IndexBufferRecord indexbuffer;
	glGenBuffers(1,&indexbuffer.id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexbuffer.id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,buffer,GL_STATIC_DRAW);
	return IndexBufferRecords.insert(indexbuffer);
}
ShaderID GL::CreateShader( ShaderType type,string src )
{
	ShaderRecord shader;
	GLenum gltype = type;
	GLuint glshader = glCreateShader(gltype);
	shader.id = glshader;

	if ( !glshader)	return 0;

	const char* p = src.c_str();
	glShaderSource(glshader,1,&p,NULL);

	glCompileShader(glshader);

	GLint compiled;
	glGetShaderiv(glshader, GL_COMPILE_STATUS, &compiled );

	if ( !compiled ) // Check the compile status
	{
		GLint infoLen = 0;
		glGetShaderiv ( glshader, GL_INFO_LOG_LENGTH, &infoLen );
		if ( infoLen > 1 )
		{
			char* infoLog = (char*) malloc (sizeof(char) * infoLen );
			glGetShaderInfoLog ( glshader, infoLen, NULL, infoLog );
			ERR("Error compiling shader:\n%s\n",infoLog);            
			free ( infoLog );
		}
		glDeleteShader ( glshader );
		shader.id = 0;
	}
	return ShaderRecords.insert(shader);
}
void GL::BindShader(ShaderType type, ShaderID sd)
{
	switch (type)
	{
		case VertexShader:
			CurrentVS = sd;
			break;
		case FragmentShader:
			CurrentFS = sd;
			break;
		default:
			assert(0);
	}
}
ProgramID GL::CreateProgram( ShaderID vs, ShaderID fs)
{
	ProgramRecord program;
	program.program_id = glCreateProgram();
	
	glAttachShader(program.program_id,ShaderRecords[vs]->id);
	glAttachShader(program.program_id,ShaderRecords[fs]->id);

	glLinkProgram(program.program_id);

	GLint linked;
	glGetProgramiv(program.program_id, GL_LINK_STATUS, &linked );

	if ( !linked ) // Check the link status
	{
		GLint infoLen = 0;
		glGetProgramiv ( program.program_id, GL_INFO_LOG_LENGTH, &infoLen );
		if ( infoLen > 1 )
		{
			char* infoLog = (char*) malloc (sizeof(char) * infoLen );
			glGetProgramInfoLog ( program.program_id, infoLen, NULL, infoLog );
			ERR("Error linking program:\n%s\n",infoLog);            
			free ( infoLog );
		}
		glDeleteProgram ( program.program_id );
		program.program_id = 0;
	}
	
	return ProgramRecords.insert(program);
}
/*TextureBufferID OpenGLRenderer::CreateTextureBuffer( const void* buffer, int size )
{
	TextureBufferRecord texturebuffer;
	glGenBuffers(1,&texturebuffer.id);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,texturebuffer.id);
	glBufferData(GL_PIXEL_UNPACK_BUFFER,size,buffer,GL_STATIC_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
	return TextureBufferRecords.insert(texturebuffer);
}*/
/*
TextureID OpenGLRenderer::CreateTexture2D( TextureBufferID texbuf, int width, int height, SemanticFormat format )
{
	TextureRecord texture;
	GLenum glformat=0;
	GLenum gltype=0;
	switch (format)
	{
	case RGB_FLOAT32:
		glformat = GL_RGB;
		gltype = GL_FLOAT;
		break;
	case RGBA_FLOAT32:
		glformat = GL_RGBA;
		gltype = GL_FLOAT;
		break;
	default:
		assert(0);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&texture.id);

	glBindTexture(GL_TEXTURE_2D,texture.id);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,TextureBufferRecords[texbuf]->id);
			glTexImage2D(GL_TEXTURE_2D, 0, glformat, width, height, 0, glformat, gltype, NULL);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);

	return TextureRecords.insert(texture);
}*/
TextureID GL::CreateTexture2D( const void* buffer, int width, int height, SemanticFormat format )
{
	TextureRecord texture;
	GLenum glinternal,glformat,gltype;
	switch (format)
	{
	case RGB_UINT8:
		glinternal = glformat = GL_RGB;
		gltype = GL_UNSIGNED_BYTE;
		break;
	case RGBA_UINT8:
		glinternal = glformat = GL_RGBA;
		gltype = GL_UNSIGNED_BYTE;
		break;
	case RGB_FLOAT32:
		glinternal = GL_RGB32F;
		glformat = GL_RGB;
		gltype = GL_FLOAT;
		break;
	case RGBA_FLOAT32:
		glinternal = GL_RGBA32F;
		glformat = GL_RGBA;
		gltype = GL_FLOAT;
		break;
	case DEPTH32:
		glinternal = GL_DEPTH_COMPONENT32;
		glformat = GL_DEPTH_COMPONENT;
		gltype = GL_FLOAT;
		break;
	/*case DEPTH24_STENCIL8:
		glinternal = GL_DEPTH24_STENCIL8;
		glformat = GL_DEPTH_STENCIL;
		gltype = GL_UNSIGNED_INT_24_8;
		break;
	*/
	case DEPTH32F_STENCIL8:
		glinternal = GL_DEPTH32F_STENCIL8;
		glformat = GL_DEPTH_COMPONENT;
		gltype = GL_FLOAT;
		break;
	case XYZ_FLOAT32:
		glinternal = GL_RGB32F;
		glformat = GL_RGB;
		gltype = GL_FLOAT;
		break;
	default:
		assert(0);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&texture.id);

	glBindTexture(GL_TEXTURE_2D,texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, glinternal, width, height, 0, glformat, gltype, buffer);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		if (format==DEPTH32)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		}
	glBindTexture(GL_TEXTURE_2D,0);

	texture.type = GL_TEXTURE_2D;
	texture.format = format;
	return TextureRecords.insert(texture);
}
static const GLenum cubetex_types[6] = {  
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
TextureID GL::CreateTextureCube(void* buffers[], int width[], int height[], SemanticFormat format[])
{
	TextureRecord texture;
	

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&texture.id);

	glBindTexture(GL_TEXTURE_CUBE_MAP,texture.id);
	
		for(int i=0; i<6; i++)
		{
			GLenum glformat=0;
			GLenum gltype=0;
			switch (format[i])
			{
			case RGB_UINT8:
				glformat = GL_RGB;
				gltype = GL_UNSIGNED_BYTE;
			case RGBA_UINT8:
				glformat = GL_RGBA;
				gltype = GL_UNSIGNED_BYTE;
				break;
			case RGB_FLOAT32:
				glformat = GL_RGB;
				gltype = GL_FLOAT;
				break;
			case RGBA_FLOAT32:
				glformat = GL_RGBA;
				gltype = GL_FLOAT;
				break;
			default:
				assert(0);
			}
			glTexImage2D(cubetex_types[i], 0, glformat, width[i], height[i], 0, glformat, gltype, buffers[i]);
		}
	
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);
	
	texture.type = GL_TEXTURE_CUBE_MAP;
	
	return TextureRecords.insert(texture);
}
FrameBufferID GL::CreateFrameBuffer()
{
	FrameBufferRecord framebuffer;
	glGenFramebuffers(1,&framebuffer.id);
	return FrameBufferRecords.insert(framebuffer);
}
void GL::BindInput( string semantic, VertexBufferID vb, int offset,int stride, DataFormat format )
{
	assert(vb);
	GLenum gltype;
	GLint glsize;
	switch (format)
	{
	case DF_FLOAT3:
		gltype = GL_FLOAT;
		glsize = 3;
		break;
	case DF_FLOAT4:
		gltype = GL_FLOAT;
		glsize = 4;
		break;
	case DF_FLOAT2:
		gltype = GL_FLOAT;
		glsize = 2;
		break;
	default:
		assert(0);
	}
	InputBinder input = { semantic, VertexBufferRecords[vb]->id, offset, stride, gltype, glsize };
	InputSlots[semantic] = input;
}
void GL::BindIndex( IndexBufferID ib, DataFormat format, int count )
{
	assert(ib);
	GLenum glformat;
	switch(format)
	{
		case DF_UINT:
			glformat = GL_UNSIGNED_INT;
			break;
		default:
			assert(0);
	}
	IndexBinder index = { ib,glformat,count };
	CurrentIndex = index;
}
void GL::BindUniform( string semantic,DataFormat type,void* buffer,int count/*=1*/ )
{
	UniformBinder uniform = { semantic, type, count, buffer };
	UniformSlots[semantic] = uniform;
}
void GL::BindProgram(ProgramID pg)
{
	CurrentProgramID = pg;
}
void GL::DeclareAttribute( string semantic,string attribute,ProgramID pl)
{
	ProgramRecords[pl]->anames[semantic] = attribute;
	ProgramRecords[pl]->alocations[semantic] = glGetAttribLocation(ProgramRecords[pl]->program_id,attribute.c_str());
}
void GL::DeclareUniform(string semantic,string uniform,ProgramID pl)
{
	GLint location = glGetUniformLocation(ProgramRecords[pl]->program_id, uniform.c_str());
	ProgramRecords[pl]->ulocations[semantic] = location;
}
void GL::DeclareTexture(string semantic,string texture,ProgramID pl)
{
	GLint location = glGetUniformLocation(ProgramRecords[pl]->program_id,texture.c_str());
	ProgramRecords[pl]->tlocations[semantic] = location;
	ProgramRecords[pl]->tnames[semantic] = texture;
}
ProgramID GL::CreateTheProgram(string vs_src, string fs_src, ExportedDeclaration* export_declararions, int export_declarations_num)
{
	ShaderID vs = CreateShader(VertexShader,vs_src);
	ShaderID fs = CreateShader(FragmentShader,fs_src);
	ProgramID pg = CreateProgram(vs,fs);

	for (int i=0; i<export_declarations_num; i++)
		switch(export_declararions[i].export_type)
		{
		case ET_ATTRIBUTE:
			DeclareAttribute(export_declararions[i].semantic,export_declararions[i].name,pg);
			break;
		case ET_UNIFORM:
			DeclareUniform(export_declararions[i].semantic,export_declararions[i].name,pg);
			break;
		case ET_TEXTURE:
			DeclareTexture(export_declararions[i].semantic,export_declararions[i].name,pg);
			break;
		}

	return pg;
}

void GL::BindTexture( string semantic,TextureID tx)
{
	assert(tx);
	assert(TextureSlots.size()<16);
	TextureBinder texbinder = { tx };
	TextureSlots[semantic] = texbinder;	
}
/*void GL::BindFrameBuffer(FrameBufferID fb)
{
	CurrentFrameBufferID = fb;
}*/
void GL::AttachTextureToFrameBuffer(FrameBufferID framebuffer, GLenum attachment, TextureID texture)
{
	if (framebuffer!=0)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,FrameBufferRecords[framebuffer]->id);
			if (texture==0)
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, 0, 0);
			else
				glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, TextureRecords[texture]->id, 0);
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}
}
void GL::BindDepthStencilBuffer(TextureID texture)
{
	assert(texture>=0);
	CurrentDepthStencilBufferID = texture;
	use_depth_stencil_buffer = texture;
}
void GL::BindColorBuffer(int i,TextureID texture)
{
	assert(texture>=0);
	CurrentColorBufferIDs[i] = texture;
}
void GL::Reset()
{
	ResetShaders();
	ResetInputs();
	ResetTextures();
	ResetUniforms();
	ResetProgram();
	ResetDepthBuffer();
	ResetColorBuffer();
}
void GL::ResetShaders()
{
	BindShader(VertexShader,0);
	BindShader(FragmentShader,0);
}
void GL::ResetInputs()
{
	InputSlots.clear();
}
void GL::ResetIndex()
{
}
void GL::ResetTextures()
{
	TextureSlots.clear();
}
void GL::ResetUniforms()
{
	UniformSlots.clear();
}
void GL::ResetProgram()
{
	CurrentProgramID = 0;
}
void GL::ResetDepthBuffer()
{
	CurrentDepthStencilBufferID = 0;
	use_depth_stencil_buffer = false;
}
void GL::ResetColorBuffer()
{
	CurrentColorBufferIDs.clear();
	CurrentColorBufferIDs.resize(8);
	use_colorbuffer = false;
}
void GL::SetBlendState(bool enable,BlendFactor src,BlendFactor dst)
{

}
void GL::DeleteVertexBuffer( VertexBufferID& vb )
{
	assert(VertexBufferRecords[vb]);
	glDeleteBuffers(1,&VertexBufferRecords[vb]->id);
	VertexBufferRecords.remove(vb);
	vb = 0;
}
void GL::DeleteIndexBuffer( IndexBufferID& ib )
{
	assert(IndexBufferRecords[ib]);
	glDeleteBuffers(1,&IndexBufferRecords[ib]->id);
	IndexBufferRecords.remove(ib);
	ib = 0;
}
void GL::DeleteShader( ShaderID& sd )
{
	assert(ShaderRecords[sd]);
	glDeleteShader(ShaderRecords[sd]->id);
	ShaderRecords.remove(sd);
	sd = 0;
}
void GL::DeleteTexture( TextureID& tx )
{
	assert(TextureRecords[tx]);
	glDeleteTextures(1,&(TextureRecords[tx]->id));
	TextureRecords.remove(tx);
	tx = 0;
}
void GL::DeleteFrameBuffer(FrameBufferID& fb)
{
	assert(FrameBufferRecords[fb]);
	glDeleteFramebuffers(1,&FrameBufferRecords[fb]->id);
	FrameBufferRecords.remove(fb);
	fb = 0;
}
void GL::DeleteProgram(ProgramID& pl)
{
	assert(ProgramRecords[pl]);
	ProgramRecords.remove(pl);
	pl = 0;
}
void GL::Scissor(float x,float y,float w,float h)
{
	glScissor(x,y,w,h);
}
void GL::ClearColorBuffer(float r,float g,float b,float a)
{
	BeginFrameBuffer();
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void GL::ClearDepthBuffer(float depth)
{
	BeginFrameBuffer();
	glClearDepth(depth);
	glClear(GL_DEPTH_BUFFER_BIT);
}
void GL::ClearStencilBuffer(int s)
{
	BeginFrameBuffer();
	glClearStencil(s);
	glClear(GL_STENCIL_BUFFER_BIT);
}
void GL::BindPrimitiveTopology(PrimitiveType primitive)
{
	CurrentPrimitiveTopology = primitive;
}
void GL::Draw()
{
	BeginProgram2();

	BeginFrameBuffer();

	// apply uniforms
	for (auto it = UniformSlots.begin(); it!=UniformSlots.end(); it++)
	{
		string semantic = it->first;
		UniformBinder binder = it->second;
		GLint location = ProgramRecords[CurrentProgramID]->ulocations[semantic];
		BeginUniform(location,binder.type,binder.buffer,binder.count);
	}
	// apply textures
	assert(TextureSlots.size()<=16);
	int tx_slot = 1;
	for (auto it=TextureSlots.begin(); it!=TextureSlots.end(); it++)
	{
		string semantic = it->first;
		TextureBinder binder = it->second;
		if (ProgramRecords[CurrentProgramID]->tnames.find(semantic)!=ProgramRecords[CurrentProgramID]->tnames.end())
			BeginTexture(TextureRecords[binder.texid]->id,TextureRecords[binder.texid]->type,ProgramRecords[CurrentProgramID]->tnames[semantic],tx_slot++,ProgramRecords[CurrentProgramID]->program_id);
		//else
			//assert(0);
	}
	// apply inputs
	for (auto it = InputSlots.begin(); it!=InputSlots.end(); it++)
	{
		string semantic = it->first;
		InputBinder binder = it->second;
		if (ProgramRecords[CurrentProgramID]->anames.find(semantic)!=ProgramRecords[CurrentProgramID]->anames.end())
			BeginInput(binder.vbid,binder.offset,binder.stride,binder.gltype,binder.glsize,ProgramRecords[CurrentProgramID]->anames[semantic]);
		//else
			//WARNING("No matching attribute declared for semantic '%s'",semantic.c_str());
	}
	// apply index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IndexBufferRecords[CurrentIndex.indexbuffer]->id);

	GLenum glprimitive;
	switch(CurrentPrimitiveTopology)
	{
	case PRIMITIVE_TRIANGLES:
		glprimitive = GL_TRIANGLES;
		break;
	default:
		assert(0);
	}
	glDrawElements( glprimitive, CurrentIndex.count, GL_UNSIGNED_INT, 0 );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	// close inputs
	for (auto it = InputSlots.begin(); it!=InputSlots.end(); it++)
	{
		string semantic = it->first;
		InputBinder binder = it->second;
		if (ProgramRecords[CurrentProgramID]->anames[semantic]!="")
			EndInput(ProgramRecords[CurrentProgramID]->anames[semantic]);
	}
	// close textures
	tx_slot = 1;
	for (auto it=TextureSlots.begin(); it!=TextureSlots.end(); it++)
	{
		string semantic = it->first;
		TextureBinder binder = it->second;
		if (ProgramRecords[CurrentProgramID]->tnames.find(semantic)!=ProgramRecords[CurrentProgramID]->tnames.end())
			EndTexture(ProgramRecords[CurrentProgramID]->tnames[semantic],tx_slot++,ProgramRecords[CurrentProgramID]->program_id);
		//else
			//assert(0);
	}
	// close uniforms
	for (auto it = UniformSlots.begin(); it!=UniformSlots.end(); it++)
	{
		string semantic = it->first;
		UniformBinder binder = it->second;
		GLint location = ProgramRecords[CurrentProgramID]->ulocations[semantic];
		EndUniform(location,binder.type,binder.count);
	}
}
void GL::BeginProgram2()
{
	BeginProgram();
	if ( CurrentVS && CurrentFS )
	{
		glAttachShader(CurrentProgramGLID,ShaderRecords[CurrentVS]->id);
		glAttachShader(CurrentProgramGLID,ShaderRecords[CurrentFS]->id);

		glLinkProgram(CurrentProgramGLID);

		GLint linked;
		glGetProgramiv(CurrentProgramGLID, GL_LINK_STATUS, &linked );

		if ( !linked ) // Check the link status
		{
			GLint infoLen = 0;
			glGetProgramiv ( CurrentProgramGLID, GL_INFO_LOG_LENGTH, &infoLen );
			if ( infoLen > 1 )
			{
				char* infoLog = (char*) malloc (sizeof(char) * infoLen );
				glGetProgramInfoLog ( CurrentProgramGLID, infoLen, NULL, infoLog );
				ERR("Error linking program:\n%s\n",infoLog);            
				free ( infoLog );
			}
			glDeleteProgram ( CurrentProgramGLID );
			CurrentProgramGLID = 0;
		}
		assert(CurrentProgramGLID);
		glUseProgram(CurrentProgramGLID);
	}

}
void GL::BeginFrameBuffer()
{
	bool use_colorbuffer = false;
	for (int i=0; i<8; i++)	
		if (CurrentColorBufferIDs[i]>0)
		{	
			use_colorbuffer = true;
			break;
		}
	if (use_depth_stencil_buffer||use_colorbuffer)
	{
		GLenum drawbuffers[8];
		int k=0;
		if (CurrentDepthStencilBufferID!=0)
		{
			SemanticFormat format = TextureRecords[CurrentDepthStencilBufferID]->format;
			GLenum attachment;
			switch (format)
			{
				case DEPTH32:
					attachment = GL_DEPTH_ATTACHMENT;
					break;
				case DEPTH32F_STENCIL8:
					attachment = GL_DEPTH_STENCIL_ATTACHMENT;
					break;
				default:
					assert(0);
			}
			AttachTextureToFrameBuffer(CurrentFrameBufferID, attachment, CurrentDepthStencilBufferID);
		}
		for (int i=0; i<8; i++)
		{
			AttachTextureToFrameBuffer(CurrentFrameBufferID,GL_COLOR_ATTACHMENT0+i,CurrentColorBufferIDs[i]);
			if (CurrentColorBufferIDs[i]!=0)
				drawbuffers[k++] = GL_COLOR_ATTACHMENT0+i;
		}
		glBindFramebuffer(GL_FRAMEBUFFER,CurrentFrameBufferID);
		glDrawBuffers(k,drawbuffers);
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status!=GL_FRAMEBUFFER_COMPLETE)
			printf("FB error:%x\n",status);
		glBindFramebuffer(GL_FRAMEBUFFER,FrameBufferRecords[CurrentFrameBufferID]->id);
	}
	else
		glBindFramebuffer(GL_FRAMEBUFFER,0);
}
void GL::BeginInput(GLuint vb,int offset,GLsizei stride,GLenum gltype,GLint glsize,string attname)
{
	GLint location = glGetAttribLocation(ProgramRecords[CurrentProgramID]->program_id,attname.c_str());	
	if (location==-1) return;
	glEnableVertexAttribArray(location);
	
	glBindBuffer(GL_ARRAY_BUFFER,vb);
		glVertexAttribPointer(location,glsize,gltype,GL_FALSE,stride,(void*)offset);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
void GL::EndInput(string attname)
{
	GLint location = glGetAttribLocation(ProgramRecords[CurrentProgramID]->program_id,attname.c_str());
	if (location==-1) return;
	glDisableVertexAttribArray(location);
}
void GL::BeginUniform(GLint location,DataFormat type,void* buffer,GLsizei count)
{
	if (location!=-1)
	{
		switch (type)
		{
		case DF_INT:
			glUniform1iv(location,count,(int*)buffer);
			break;
		case DF_FLOAT:
			glUniform1fv(location,count,(float*)buffer);
			break;
		case DF_FLOAT3:
			glUniform3fv(location,count,(float*)buffer);
			break;
		case DF_FLOAT4:
			glUniform4fv(location,count,(float*)buffer);
			break;
		case DF_FLOAT4X4:
			glUniformMatrix4fv(location, count, GL_FALSE, (float*)buffer);
			break;
		default:
			assert(0);
		}
	}
}
void GL::EndUniform(GLint location,DataFormat type,GLsizei count)
{
	static int ZERO_INT = 0;
	static float ZERO_FLOAT = 0;
	static float ZERO_VECTOR3F[] = { 0,0,0 };
	static float ZERO_VECTOR4F[] = { 0,0,0,0 };
	static float ZERO_MATRIX4F[] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
	if (location!=-1)
	{
		switch (type)
		{
		case DF_INT:
			glUniform1iv(location,count,&ZERO_INT);
			break;
		case DF_FLOAT:
			glUniform1fv(location,count,&ZERO_FLOAT);
			break;
		case DF_FLOAT3:
			glUniform3fv(location,count,ZERO_VECTOR3F);
			break;
		case DF_FLOAT4:
			glUniform4fv(location,count,ZERO_VECTOR4F);
			break;
		case DF_FLOAT4X4:
			glUniformMatrix4fv(location, count, GL_FALSE, ZERO_MATRIX4F);
			break;
		default:
			assert(0);
		}
	}
}
void GL::BeginTexture( GLuint texture, GLenum type,string texname, int slot, GLuint program)
{
	GLint location = glGetUniformLocation(program,texname.c_str());
	//assert(location!=-1);
	glUniform1i(location, slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(type,texture);
}
void GL::EndTexture(string texname, int slot, GLuint program)
{
	GLint location = glGetUniformLocation(program,texname.c_str());
	//assert(location!=-1);
	glUniform1i(location, slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D,0);
}
void GL::BeginProgram()
{
	assert(CurrentProgramID);
	glUseProgram(ProgramRecords[CurrentProgramID]->program_id);
}



#endif