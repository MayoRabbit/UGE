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

framebuffer.cpp

*******************************************************************************/

#include "framebuffer.hpp"

namespace glLib
{

// Constructor.
Framebuffer::Framebuffer(const GLuint numFramebuffers) :
	Object(numFramebuffers, glCreateFramebuffers)
{}

// Destructor.
Framebuffer::~Framebuffer()
{
	if(names)
		glDeleteFramebuffers(numObjects, names.get());
}

// Move constructor.
Framebuffer::Framebuffer(Framebuffer &&fb) :
	Object(std::move(fb))
{}

// Move assignment.
Framebuffer & Framebuffer::operator = (Framebuffer &&fb)
{
	Object::operator = (std::move(fb));
	return *this;
}

} // namespace glLib
