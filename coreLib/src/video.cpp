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

video.cpp



*******************************************************************************/

#include <array>
#include <string_view>
#include <SDL2/SDL.h>
#include <vector>
#include "console.hpp"
#include "cvar.hpp"
#include "video.hpp"

namespace coreLib
{

namespace video
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

// SDL stuff.
static SDL_Window	*sdlWindow;
static void			*sdlLibHandle;

// Functions in whichever lib file is being used.
static bool (*libInitFunc)(SDL_Window *);
static void (*libQuitFunc)();

// Stores whether the user's screen saver was enabled when the program was
// loaded. If it was, will re-enable it when program ends.
static bool screenSaverWasEnabled;

// These are filled in after SDL acquires video information.
console::IntCVAR
	customWidth,	// Used if the value of `mode` is -1.
	customHeight,	// Same.
	display,		// Display monitor.
	driver;			// Display driver.

// One display mode per display.
std::vector<console::IntCVAR> modes;

// These don't need to be.
console::BoolCVAR
	fullscreen(1, "videoFullscreenDesc"),
	renderer(0, "videoRendererDesc"); // 0 = OpenGL, 1 = Vulkan.

/**
 * Restarts video system.
 * Switches graphics libraries if that setting has been changed.
 */

void restart()
{
	// Free graphics library resources and unload the dynamic lib.
	(*libQuitFunc)();
	SDL_UnloadObject(sdlLibHandle);

	// Load currently selected library.
	sdlLibHandle = SDL_LoadObject(graphicsLibs[renderer].data());
	if(!sdlLibHandle)
		printf("%s\n", SDL_GetError());

	(*libInitFunc)(sdlWindow);
}

/**
 * Initializes video system.
 */

uint8_t init()
{
	int errorCode = 0;

	// SDL.
	if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{

	}

	screenSaverWasEnabled = SDL_IsScreenSaverEnabled();
	if(screenSaverWasEnabled)
		SDL_DisableScreenSaver();

	// Initialize CVARs.
	int numDisplays = SDL_GetNumVideoDisplays();
	display = { 0, 0, (numDisplays - 1), "cvarVidDisplayDesc" };

	int numDrivers = SDL_GetNumVideoDrivers();
	driver = { 0 , 0, (numDrivers - 1), "cvarVidDriverDesc" };

	// Custom width and height can be set to any value that fits the integer
	// type. If the value can't be used, the library should revert back to
	// the last valid settings.
	customWidth		= { 640, INT_MIN, INT_MAX, "cvarVidCustomwWidthDesc" };
	customHeight	= { 480, INT_MIN, INT_MAX, "cvarVidCustomHeightDesc" };

	modes.resize(numDisplays);
	for(int i = 0; i < numDisplays; i++)
	{
		int numModes = SDL_GetNumDisplayModes(i);
		modes[i] = { 0, 0, (numModes - 1), "cvarVidModeDesc" };
	}

	// CVARs.
	console::systemCVARs.insert
	({
		{ "vid_customwidth",	&customWidth },
		{ "vid_customheight",	&customHeight },
		{ "vid_display",		&display },
		{ "vid_driver",			&driver },
		{ "vid_mode",			&modes[0] },
		{ "vid_fullscreen", 	&fullscreen },
		{ "vid_renderer",		&renderer }
	});

	return errorCode;
}

/**
 * Shuts down video system.
 */

void quit()
{
	(*libQuitFunc)();

	// Re-enable screen saver if it was disabled by this library.
	if(screenSaverWasEnabled)
		SDL_EnableScreenSaver();

	SDL_DestroyWindow(sdlWindow);
}

} // namespace video

} // namespace coreLib
