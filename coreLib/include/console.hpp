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

console.hpp

*******************************************************************************/

#pragma once

#include <functional>
#include <map>
#include <string>
#include <string_view>
#include "cvar.hpp"
#include "osd.hpp"

namespace coreLib
{

namespace console
{

// System CVARs are settings supplied by this library. Custom CVARs are set by
// the user, such as aliases, batch commands, etc.
extern std::map<std::string_view, CVAR *>			systemCVARs;
extern std::map<std::string_view, std::string_view>	customCVARs;

// Console Commands. Commands you can input into the console and execute.
// If the program will let you.
extern std::map<std::string_view, std::function<void ()>> CCMDs;

// Simple typedef to identify which functions are console commands. Might
// improve readability. Might not. Might figure it out later. Might not.
typedef void CCMD;

uint8_t	init();
void	quit();

// For other portions of this library to use.
void giveOutput(const std::string_view &str);
void giveOutput(const std::string &str);

} // namespace console

} // namespace coreLib

/**
 * Exported functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

void LIB_FUNC_CALL coerConsoleMain();
void LIB_FUNC_CALL coreConsoleToggle();
void LIB_FUNC_CALL coreConsoleOutput(const std::string &str);

#ifdef __cplusplus
} // extern "C"
#endif
