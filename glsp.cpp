#include"glsp.hpp"

int check_shader(GLuint shader);
GLuint compile_program(const char*const vss, const char*const fss);

void GLSP::use()
{
	glUseProgram(program);
	glBindVertexArray(vao);
}

void GLSP::name_attrib(const GLuint index, const GLchar* name)
{
	glBindAttribLocation(program,index,name);
}

GLSP::~GLSP()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1,&vao);
}
GLSP::GLSP(const char*const vss, const char*const fss)
:program{0},vao{0}
{
	program = compile_program(vss,fss);
	if(!program)return;
	glGenVertexArrays(1,&vao);
}

void GLSP::set(const char*const name, bool value)const
{
	glUniform1i(glGetUniformLocation(program, name),static_cast<int>(value));
	return;
}
void GLSP::set(const char*const name, int value)const
{
	glUniform1i(glGetUniformLocation(program, name),value);
	return;
}
void GLSP::set(const char*const name, float value)const
{
	glUniform1f(glGetUniformLocation(program, name),value);
	return;
}


int check_shader(GLuint shader)
{
	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(success){return 1;}
	{
		GLint size = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
		if ( size > 0 ){
			char*b = new char[size];
			
			glGetProgramInfoLog(shader, size, nullptr, &b[0]);

			SDL_ShowSimpleMessageBox
			(SDL_MESSAGEBOX_ERROR, "Shader error", b, nullptr);
			delete[]b;
		}
	}
	return 0;
}
GLuint compile_shader(GLenum type,const char*const source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader,1,&source,nullptr);
	glCompileShader(shader);
	return shader;
}
GLuint compile_program(const char*const vss, const char*const fss)
{
	GLuint program = 0;
	GLuint vs = compile_shader(GL_VERTEX_SHADER  , vss);
	GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fss);

	if(!check_shader(vs)||!check_shader(fs))
	{
		glDeleteShader(vs);glDeleteShader(fs);
	}
	else
	{
		program = glCreateProgram();

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		
		glLinkProgram(program);
		//check_gl_program(program);

		glDetachShader(program, vs);
		glDetachShader(program, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	return program;
}
