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

buffer.hpp

Wrappers for the various OpenGL buffer objects.

*******************************************************************************/

#pragma once

#include <type_traits>
#include "object.hpp"

namespace glLib
{

/**
 * Buffer class.
 */

class Buffer : public Object
{
	public:
		Buffer() = default;
		Buffer(const GLuint &numBuffers);
		virtual ~Buffer();

		// Copy semantics deleted.
		Buffer(const Buffer &) = delete;
		Buffer & operator = (const Buffer &) = delete;

		// Move semantics.
		Buffer(Buffer &&b);
		Buffer & operator = (Buffer &&b);

		// Bind object to context.
		virtual inline GLvoid bind(GLuint index) = 0;

		/**
		 * Replaces data in the buffer, either in part or in whole.
		 * If the buffer was created with glBufferData(), this can reallocate
		 * the data store, where as if it was created with glBufferStorage(),
		 * relocation is not possible. So only an update on the buffer may be
		 * performed.
		 */

		template<typename T>
		void operator = (const T *data)
		{

		}
};

/**
 * Vertex buffer.
 */

class VertexBuffer : public Buffer
{

	public:

		VertexBuffer() = default;
		~VertexBuffer() = default;
};

/**
 * Uniform buffer.
 */

class UniformBuffer : public Buffer
{

	public:
		UniformBuffer() = default;
		~UniformBuffer() = default;


};

} // namespace glLib

/**
 * Exported C functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

LIB_FUNC_CALL GLuint createVertexBuffer();
GLuint * createVertexBuffers();

#ifdef __cplusplus
}
#endif
