/*******************************************************************************

<one line to give the program's name and a brief idea of what it does.>
Copyright (C) <year>  <name of author>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

********************************************************************************

shader.cpp

OpenGL shader and shader program objects. These aren't considered part of the
same paradigm as other OpenGL objects, so they do not extend from the Object
class.

*******************************************************************************/

#include "shader.hpp"

namespace glLib
{

Shader::Shader(const GLenum type) :
	id(glCreateShader(type))
{}

Shader::~Shader()
{
	if(id)
		glDeleteShader(id);
}

Shader::Shader(Shader &&s)
{
	id		= s.id;
	s.id	= 0;
}

Shader & Shader::operator = (Shader &&s)
{
	id		= s.id;
	s.id	= 0;
	return *this;
}


Program::Program() :
	id(glCreateProgram())
{}

Program::~Program()
{
	if(id)
		glDeleteProgram(id);
}

Program::Program(Program &&p)
{
	id		= p.id;
	p.id	= 0;
}

Program & Program::operator = (Program &&p)
{
	id		= p.id;
	p.id	= 0;
	return *this;
}

} // namespace glLib
