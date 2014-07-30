#ifndef CUBEDATA_H
#define CUBEDATA_H

static char cube_vs_src[] =  
	"attribute vec4 a_position;								\n"
	"attribute vec4 a_normal;									\n"
	"attribute vec2 a_texcood;									\n"
	"uniform mat4 u_mvp;										\n"
	"varying vec4 v_normal;									\n"
	"varying vec2 v_texcood;									\n"
	"void main()												\n"
	"{														\n"
	"   gl_Position = u_mvp * a_position;						\n"
	"   v_normal = a_normal;									\n"
	"	v_texcood = a_texcood;									\n"
	"}														\n";

static char cube_fs_src[] =  
	"varying vec4 v_normal;									\n"
	"varying vec2 v_texcood;									\n"
	"uniform sampler2D s_texture;								\n"
	"void main()												\n"
	"{														\n"
	"	gl_FragColor = texture2D(s_texture,v_texcood);			\n"
	"}														\n";

const int cube_vertex_number = 24;
const int cube_position_size = 3*sizeof(float)*cube_vertex_number;
const int cube_normal_size = 3*sizeof(float)*cube_vertex_number;
const int cube_texcood_size = 2*sizeof(float)*cube_vertex_number;
const int cube_tex_width = 4;
const int cube_tex_height = 4;
const int cube_tex_size = 3*sizeof(float)*cube_tex_width*cube_tex_height;
const int cube_index_number = 36;
const int cube_index_size = sizeof(unsigned int)*cube_index_number;

static float cube_positions[cube_vertex_number*3] =
{
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f,  0.5f, 0.5f,
	0.5f,  0.5f, 0.5f, 
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	0.5f,  0.5f, -0.5f,
};

static float cube_normals[cube_vertex_number*3] =
{
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
};

static float cube_texcoods[cube_vertex_number*2] =
{
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
};

static float cube_texture[3*cube_tex_width*cube_tex_height]=
{
	1,	0,	0,
	1,	0,	0,
	0,	1,	0,
	0,	1,	0,
	1,	0,	0,
	1,	0,	0,
	0,	1,	0,
	0,	1,	0,
	0,	0,	1,
	0,	0,	1,
	1,	1,	0,
	1,	1,	0,
	0,	0,	1,
	0,	0,	1,
	1,	1,	0,
	1,	1,	0,
};

static unsigned int cube_indices[cube_index_number] =
{
	0, 2, 1,
	0, 3, 2, 
	4, 5, 6,
	4, 6, 7,
	8, 9, 10,
	8, 10, 11, 
	12, 15, 14,
	12, 14, 13, 
	16, 17, 18,
	16, 18, 19, 
	20, 23, 22,
	20, 22, 21
};

#endif