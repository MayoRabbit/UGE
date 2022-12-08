/*******************************************************************************

<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2022 <name of author>

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

render.cpp

*******************************************************************************/

#include <unordered_map>
#include <vector>
#include "render.hpp"

namespace coreLib
{

static std::vector<std::unordered_map<std::string_view, void *>> objects;

/**
 * Clears all the maps of their object pointers. This is generally done with the
 * context for a graphics library is destroyed (either through program shutdown
 * or when manually restarting the video system). Destroying the context will
 * destroy all objects, this just ensures all the resulting invalid pointers are
 * deleted.
 */

void clearAll()
{
	//for(auto &group : objects)
		//()
}

}
