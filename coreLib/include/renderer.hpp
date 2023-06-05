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

render.hpp

*******************************************************************************/

#pragma once

#include <SDL2/SDL.h>

namespace coreLib
{

namespace renderer
{


uint8_t	init();
void	quit();

} // namespace renderer

} // namespace coreLib

/**
 * Exported functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

// Object creation.
void LIB_FUNC_CALL coreCreateBuffer(const void *data);
void LIB_FUNC_CALL coreCreateFramebuffer(const void *data);
void LIB_FUNC_CALL coreCreateProgram(const void *data);
void LIB_FUNC_CALL coreCreateShader(const void *data);
void LIB_FUNC_CALL coreCreateTexture(const void *data);

// Object deletion.
void LIB_FUNC_CALL coreDeleteBuffer(const void *data);
void LIB_FUNC_CALL coreDeleteFramebuffer(const void *data);
void LIB_FUNC_CALL coreDeleteProgram(const void *data);
void LIB_FUNC_CALL coreDeleteShader(const void *data);
void LIB_FUNC_CALL coreDeleteTexture(const void *data);

#ifdef __cplusplus
} // extern "C"
#endif
