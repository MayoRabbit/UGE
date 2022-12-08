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

main.cpp

*******************************************************************************/

#include <array>
#include <functional>
#include <SDL2/SDL.h>
#include "audio.hpp"
#include "config.hpp"
#include "console.hpp"
#include "localization.hpp"
#include "video.hpp"
#include "main.hpp"

namespace coreLib
{

// Error handling stuff. This is used in case something goes wrong.
// Which I'm pretty sure is your fault, not mine.
static struct
{
	int					code;
	std::string_view	message;

	/**
	 * Set global error message.
	 * This uses a string in the language file to parse the message.
	 */

	void set(const std::string_view &msg)
	{
		message = msg;
	}

} errorHandler;

} // namespace coreLib

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Initializes core library and systems, which in turn initialize SDL and its
 * systems.
 *
 * If anything goes wrong, sets an internal error code and message (similar to
 * how other libraries handle errors), and returns false. The calling program
 * should retrieve the code and message and handle it on its own accord.
 */

uint8_t LIB_FUNC_CALL coreInit()
{
	// Should stay 0.
	uint8_t errCode = 0;

	// Call initialization functions for each system. These simply set things up
	// to get them ready. Program isn't started yet. We don't need the array
	// after this so this part is block scoped.
	{
		const std::array<std::function<uint8_t ()>, 5> initFuncs =
		{
			coreLib::config::init,
			coreLib::localization::init,
			coreLib::console::init,
			coreLib::audio::init,
			coreLib::video::init
		};

		for(auto initFunc : initFuncs)
		{
			errCode = initFunc();
			if(errCode)
			{
				return errCode;
			}
		}
	}

	// Initialize SDL. Fatal Error if this cannot be done.
	if(SDL_Init(SDL_INIT_TIMER) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "X", SDL_GetError(), NULL);
		return 1;
	}

	printf("Done.\n");

	// All good. Assuming.
	return errCode;
}

/**
 * Shuts down core library and systems. Includes SDL's stuff too.
 */

void LIB_FUNC_CALL coreQuit()
{
	printf("Unloading core library...\n");
	SDL_Quit();
	coreLib::config::quit();
}

/**
 * Gives the currently set error message to the calling program.
 */

const char * LIB_FUNC_CALL getCoreError()
{
	return coreLib::errorHandler.message.data();
}

#ifdef __cplusplus
} // extern "C"
#endif
