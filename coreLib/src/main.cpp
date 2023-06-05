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

main.cpp

*******************************************************************************/

#include <iostream>
#include <SDL2/SDL.h>
#include "audio.hpp"
#include "config.hpp"
#include "localization.hpp"
#include "main.hpp"
#include "video.hpp"

// Language file strings.
namespace coreLib
{
	std::string initSuccessMsg;
}

/**
 * Exported functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Initializes core library and systems, which in turn initialize the SDL
 * libraries and their systems.
 *
 * If anything goes wrong, sets an internal error code and message (similar to
 * how other libraries handle errors), and returns the error code. The calling
 * program should retrieve the code and message and handle it on its own accord.
 */

const int LIB_FUNC_CALL coreInit()
{
	// Attempt to initialize SDL. If we can't, that's bad.
	if(SDL_Init(SDL_INIT_TIMER) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot initialize SDL!", SDL_GetError(), NULL);
		return 1;
	}

	// Initialize localization system. Fails if either the locale directory does
	// not exist, or if it's empty. Program cannot run without at least the
	// English (en_us) language file.
	int errorCode = coreLib::localization::init();
	if(errorCode)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot initialize SDL Video System!", SDL_GetError(), NULL);
		return errorCode;
	}

	// Initialize video system. Failure results in program exit.
	// Can't run a game if you can't show anything, I think.
	errorCode = coreLib::video::init();

	if(errorCode)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Cannot initialize SDL Video System!", SDL_GetError(), NULL);
		return errorCode;
	}

	// Initialize audio system. This can fail, which may result in no audio
	// output. The log file should indicate why.
	errorCode = coreLib::audio::init();

	if(errorCode)
	{
		coreLib::console::giveOutput(coreLib::localizaion::strings["audioInitFailMsg"]);
	}

	// Initialize audio system.
	// Load main configuration file.
	coreLib::configuration::init();

	std::cout << coreLib::initSuccessMsg << std::endl;

	return 0;
}

/**
 * Shuts down core library and systems. Includes SDL's stuff too.
 */

void LIB_FUNC_CALL coreQuit()
{
	coreLib::video::quit();
	SDL_Quit();
	std::cout << "CORE LIBRARY UNLOADED!";
}

#ifdef __cplusplus
} // extern "C"
#endif
