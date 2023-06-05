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

renderer.cpp

Handles objects for the various graphics libraries supported. This assigns names
to objects to allow for easier use, and so the user doesn't have to deal with
the graphics libraries directly. I mean you still can if you want to. There's
actually nothing that stops you from doing so alongside this. This is a free
country, after all.

*******************************************************************************/

#include <array>
#include <functional>
#include <iostream>
#include <string_view>
#include "console.hpp"
#include "renderer.hpp"

namespace coreLib
{

namespace renderer
{

// Filenames for the GL / Vulkan wrapper libs, one of which will be loaded
// during video initialization.
// OS dependent, so a bit o' preprocessor here.
static constexpr std::array<std::string_view, 2> graphicsLibs =
{
#ifdef _WIN64
	"gl.dll",
	"vulkan.dll"
#else
	#error "__FILE__ __LINE__: Invalid OS option for graphics libraries."
#endif
};

// Handle to whichever library file is being used.
static void *sdlLibHandle;

// Functions in whichever lib file is being used.
static std::function<bool(SDL_Window *)>	libInitFunc;
static std::function<void()>				libQuitFunc;

// 0 = OpenGL, 1 = Vulkan.
static console::BoolCVAR renderer(0, "videoRendererDesc");

static std::unordered_map<std::string_view, void *> handles;

// Possibly unnecessary? Different libs might not support all these objects?
static std::unordered_map<std::string_view, void *>
	buffers,
	programs,
	pipelines,
	shaders,
	textures,
	VAOs;

/**
 * Initializes renderer system.
 * This
 */

uint8_t init()
{
	console::systemCVARs.insert( { "vid_renderer", &renderer } );

	sdlLibHandle = SDL_LoadObject(graphicsLibs[renderer].data());
	return 0;

	// Load currently selected library.
	sdlLibHandle = SDL_LoadObject(graphicsLibs[renderer].data());
	if(!sdlLibHandle)
		printf("%s\n", SDL_GetError());

	//libInitFunc(sdlWindow);
}

void quit()
{
	std::cout << "Closing rendering module...\n";
}

/**
 * Clears all the maps of their object pointers. This is generally done with the
 * context for a graphics library is destroyed (either through program shutdown
 * or when manually restarting the video system). Destroying the context will
 * destroy all objects, this just ensures all the resulting invalid pointers are
 * deleted.
 */

void clearAll()
{
	//for()
		//()
}

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
void LIB_FUNC_CALL coreCreateBuffer(const void *data)
{

}

void LIB_FUNC_CALL coreCreateFramebuffer(const void *data)
{

}

void LIB_FUNC_CALL coreCreateProgram(const void *data)
{

}

void LIB_FUNC_CALL coreCreateShader(const void *data)
{

}

void LIB_FUNC_CALL coreCreateTexture(const void *data)
{

}

// Object deletion.
void LIB_FUNC_CALL coreDeleteBuffer(const void *data)
{

}

void LIB_FUNC_CALL coreDeleteFramebuffer(const void *data)
{

}

void LIB_FUNC_CALL coreDeleteProgram(const void *data)
{

}

void LIB_FUNC_CALL coreDeleteShader(const void *data)
{

}

void LIB_FUNC_CALL coreDeleteTexture(const void *data)
{

}

#ifdef __cplusplus
} // extern "C"
#endif
