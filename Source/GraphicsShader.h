static char graphics_vs_src[] =  
	"attribute vec4 a_position;									\n"
	"attribute vec4 a_normal;									\n"
	"attribute vec2 a_texcood;									\n"
	"uniform mat4	u_wvp;										\n"
	"varying vec4	v_normal;									\n"
	"varying vec2	v_texcood;									\n"
	"void main()												\n"
	"{															\n"
	"	gl_Position = u_wvp * a_position;						\n"
	"	v_normal = a_normal;									\n"
	"	v_texcood = a_texcood;									\n"
	"}															\n";

static char graphics_fs_src[] =  
	"varying vec4 v_normal;										\n"
	"varying vec2 v_texcood;									\n"
	"uniform sampler2D s_texture;								\n"
	"void main()												\n"
	"{															\n"
	"	gl_FragColor = texture2D(s_texture,v_texcood);			\n"
	"}															\n";
