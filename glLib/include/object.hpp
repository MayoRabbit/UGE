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

object.hpp

Simple header file containing an abstract base class for the following OpenGL
objects:

- Buffer objects
- Framebuffers
- Program Pipelines
- Textures
- Vertex Array Objects

*******************************************************************************/

#pragma once

#include <memory>
#include <glad/gl.h>

namespace glLib
{

class Object
{
	protected:
		GLuint numObjects;
		std::unique_ptr<GLuint []> names;	// Because OpenGL works with pointers.

	public:
		Object() = default;

		// Derived classes use their own destructors, as they need to call a
		// unique OpenGL function specific to the type of object.
		virtual ~Object() = default;

		Object(const GLuint &numObjs, void (*createFunc)(GLsizei, GLuint *)) :
			numObjects	(numObjs),
			names		(new GLuint[numObjects])
		{
			(*createFunc)(numObjects, names.get());
		}

		// Copy semantics deleted. No two OpenGL objects can share the same
		// resources. Would be bad if one deleted them and another tried to use
		// them after. Maybe.
		Object(const Object &) = delete;
		Object & operator = (const Object &) = delete;

		// Move consructor.
		Object(Object &&obj)
		{
			numObjects = obj.numObjects;
			names.swap(obj.names);
		}

		// Move assignment.
		Object & operator = (Object &&obj)
		{
			numObjects = obj.numObjects;
			names.swap(obj.names);
			return *this;
		}
};

} // namespace glLib
