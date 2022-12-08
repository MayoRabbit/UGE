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

shader.hpp

*******************************************************************************/

#pragma once

#include <glad/gl.h>

namespace glLib
{

class Shader
{
	GLuint id;

	public:
		Shader() = delete;
		Shader(const GLenum type);
		~Shader();

		// Copy semantics deleted.
		Shader(const Shader &) = delete;
		Shader & operator = (const Shader &) = delete;

		// Move semantics.
		Shader(Shader &&s);
		Shader & operator = (Shader &&s);
};

class Program
{
	GLuint id;

	public:
		Program();
		~Program();

		// Copy semantics deleted.
		Program(const Program &) = delete;
		Program & operator = (const Program &) = delete;

		// Move semantics.
		Program(Program &&p);
		Program & operator = (Program &&p);
};

}
