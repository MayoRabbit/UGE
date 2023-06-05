/*******************************************************************************

<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2022-2023  <name of author>

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

Handles the video system supplied by SDL.

*******************************************************************************/

#include <SDL2/SDL.h>
#include "console.hpp"
#include "renderer.hpp"
#include "video.hpp"

namespace coreLib
{

namespace video
{

static std::vector<VideoDriver *>	videoDrivers;
static std::vector<VideoDisplay *>	videoDisplays;

// SDL stuff.
static SDL_Window *sdlWindow;

// Stores whether the user's screen saver was enabled when the program was
// loaded. If it was, will re-enable it when program ends.
static bool screenSaverWasEnabled;

// These are filled in after SDL acquires video information.
console::IntCVAR
	display,	// Display monitor.
	driver;		// Display driver.

// Each display gets a set of these, as not all displays may be able to use the
// same custom width and height values.
std::vector<console::IntCVAR>
	customHeight,
	customWidth,
	modes;

// This doesn't need to be.
console::BoolCVAR fullscreen(1, "videoFullscreenDesc");

/**
 * VideoDriver class.
 */

// Constructor.
VideoDriver::VideoDriver(const int i) :
	id	(i),
	name(SDL_GetVideoDriver(i))
{}

/**
 * VideoDisplay class.
 */

// Constructor.
VideoDisplay::VideoDisplay(const int i) :
	id	(i),
	name(SDL_GetDisplayName(i))
{}

/**
 * Lists the available video drivers.
 */

void listDrivers()
{
	for(const auto vd : videoDrivers)
		vd->describe();
}

/**
 * Lists the available video displays.
 */

void listDisplays()
{
	for(const auto vd : videoDisplays)
		vd->describe();
}

/**
 * Restarts video system.
 * Switches graphics libraries if that setting has been changed.
 */

void restart()
{
	sdlWindow = SDL_CreateWindow("BOO!", 10, 10, 640, 480, SDL_WINDOW_OPENGL);
}

/**
 * Initializes video system. If anything, and I mean anything, goes wrong, it's
 * a fatal error, and program may not continue.
 */

uint8_t init()
{
	// SDL video system.
	if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		return 2;

	// Get video drivers. If this fails, we cannot proceed.
	int numDrivers = SDL_GetNumVideoDrivers();

	if(numDrivers < 0)
		return 3;

	// Get video displays. Again, failure means no continue.
	int numDisplays = SDL_GetNumVideoDisplays();

	if(numDisplays < 0)
		return 4;

	screenSaverWasEnabled = SDL_IsScreenSaverEnabled();
	if(screenSaverWasEnabled)
		SDL_DisableScreenSaver();


	videoDrivers.resize(numDrivers);

	for(int i = 0; i < numDrivers; i++)
		videoDrivers[i] = new VideoDriver(i);

	// Get video displays.

	customHeight.resize(numDisplays);
	customWidth.resize(numDisplays);
	videoDisplays.resize(numDisplays);

	for(int i = 0; i < numDisplays; i++)
		videoDisplays[i] = new VideoDisplay(i);

	// CVARs.
	driver	= { 0, 0, (numDrivers - 1), "cvarVidDriverDesc" };
	display	= { 0, 0, (numDisplays - 1), "cvarVidDisplayDesc" };

	// Highest supported width and height values for each display as determined
	// by SDL. These are used for the "max" values for the custom width and
	// height settings for each display.
	int
		maxHeight	= 0,
		maxWidth	= 0;

	SDL_DisplayMode mode;

	modes.resize(numDisplays);
	for(int i = 0; i < numDisplays; i++)
	{
		int numModes = SDL_GetNumDisplayModes(i);
		modes[i] = { 0, 0, (numModes - 1), "cvarVidModeDesc" };

		for(int j = 0; j < SDL_GetNumDisplayModes(i); j++)
		{
			SDL_GetDisplayMode(i, j, &mode);
			if(mode.h > maxHeight)
				maxHeight = mode.h;

			if(mode.w > maxWidth)
				maxWidth = mode.w;
		}

		customHeight[i]	= { maxHeight, 480, maxHeight, "cvarVidCustomHeightDesc" };
		customWidth[i]	= { maxWidth, 640, maxWidth, "cvarVidCustomwWidthDesc" };
	}

	// Console variables.
	console::systemCVARs.insert
	(
		{
			{ "vid_customwidth",	&customWidth[0] },
			{ "vid_customheight",	&customHeight[0] },
			{ "vid_display",		&display },
			{ "vid_driver",			&driver },
			{ "vid_mode",			&modes[0] },
			{ "vid_fullscreen", 	&fullscreen }
		}
	);

	// Console commands.
	console::CCMDs.insert
	(
		{
			{ "vid_listDisplays",	listDisplays },
			{ "vid_listDrivers",	listDrivers },
			{ "vid_restart",		restart }
		}
	);

	listDrivers();
	listDisplays();

	restart();

	return 0;
}

/**
 * Shuts down video system.
 */

void quit()
{
	//libQuitFunc();

	// Re-enable screen saver if it was disabled by this library.
	if(screenSaverWasEnabled)
		SDL_EnableScreenSaver();

	SDL_DestroyWindow(sdlWindow);
}

} // namespace video

} // namespace coreLib
