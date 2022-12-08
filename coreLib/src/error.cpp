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

error.cpp

Error handling. A list of errors that occur during runtime may be generated, and
looked through for debugging or other purposes. This is mainly to get around the
limitations of other libraries such as OpenGL, which cannot generate a new error
until the previous error is dealt with.

*******************************************************************************/

#include "error.hpp"

namespace coreLib
{

ErrorHandler::ErrorHandler(const sourceType src, const int c, const std::string_view &msg) :
	source(src),
	code(c),
	message(std::move(msg))
{}

}
