#ifndef _GLSP_HPP
#define _GLSP_HPP

#include"system.h"
class GLSP
{
	GLuint program;
	GLuint vao; // the structure of the data
	public:
		void use();
		void name_attrib(const GLuint index, const GLchar* name);
		~GLSP();
		GLSP(const char*const vss, const char*const fss);
		void set(const char*const name, bool value)const;
		void set(const char*const name, int value)const;
		void set(const char*const name, float value)const;
};

#endif//_GLSP_HPP
