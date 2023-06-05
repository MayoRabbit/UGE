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

main.hpp

The file to include for a program using this library. Should include other
headers to include all the exported functions necessary to use it. Should.

*******************************************************************************/

#pragma once

#include <cstdint>	// For uint8_t and such.
#include "osd.hpp"
#include "console.hpp"
#include "cvar.hpp"

/**
 * Exported functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

const int	LIB_FUNC_CALL coreInit();
void		LIB_FUNC_CALL coreQuit();

#ifdef __cplusplus
} // extern "C"
#endif
