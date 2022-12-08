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

vao.hpp

*******************************************************************************/

#pragma once

#include "object.hpp"

namespace glLib
{

class VertexArray : public Object
{
	public:
		VertexArray() = default;
		VertexArray(const GLuint num);
		~VertexArray();

		// Copy semantics deleted.
		VertexArray(const VertexArray &) = delete;
		VertexArray & operator = (const VertexArray &) = delete;

		// Move semantics.
		VertexArray(VertexArray &&va);
		VertexArray & operator = (VertexArray &&va);
};

} // namespace glLib
