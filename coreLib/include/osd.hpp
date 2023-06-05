/*******************************************************************************

<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2022-2023 <name of author>

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

osd.hpp

OS dependent stuff. For Windows sets the declspec type. For other operating
systems, who knows? I'll cross that bridge once I'm ready to add support.

*******************************************************************************/

#pragma once

#ifdef _WIN64
	#include <windows.h>

	#ifdef BUILD_LIB
		#define LIB_FUNC_CALL __declspec(dllexport)
	#else
		#define LIB_FUNC_CALL __declspec(dllimport)
	#endif
#endif

