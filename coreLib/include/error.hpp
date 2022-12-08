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

error.hpp

*******************************************************************************/

#include <string>

namespace coreLib
{

class ErrorHandler
{
	// Which library was the source of the error message. This is used to decide
	// which function to call to get the error.
	typedef enum class _sourceType
	{
		SOURCE_CORE	= 1,
		SOURCE_OPENGL,
		SOURCE_VULKAN
	}
	sourceType;

	// Code and message are supplied by the library. Neither is actually
	// required if the library doesn't set one or both for an error.
	sourceType			source;
	unsigned int		code;
	std::string_view	message;

	public:
		ErrorHandler() = delete;
		ErrorHandler(const sourceType src, const int c, const std::string_view &msg);
		~ErrorHandler() = default;

};

} // namespace coreLib
