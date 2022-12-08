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

vao.cpp

Vertex Array Objects.

*******************************************************************************/

#include "vao.hpp"

namespace glLib
{

// Constructor.
VertexArray::VertexArray(const GLuint num) :
	Object(num, glCreateVertexArrays)
{}

// Destructor.
VertexArray::~VertexArray()
{
	if(names)
		glDeleteVertexArrays(numObjects, names.get());
}

// Move constructor.
VertexArray::VertexArray(VertexArray &&va) :
	Object(std::move(va))
{}

// Move assignment.
VertexArray & VertexArray::operator = (VertexArray &&va)
{
	Object::operator = (std::move(va));
	return *this;
}

} // namespace glLib
