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

console.cpp

Handles the system console and a graphical console that can be displayed during
gameplay. The user may type commands into the console to change settings or
perform available actions.

*******************************************************************************/

#include <list>
#include <string>
#include <variant>
#include <SDL2/SDL.h>
#include "console.hpp"
#include "cvar.hpp"

namespace coreLib
{

namespace console
{

// Whether console is open. If it is all inputs will be sent to it and it'll be
// drawn on screen.
static bool isOpen = false;

// System CVARs. The various systems will add to this map as they initialize.
std::map<std::string_view, CVAR *> systemCVARs;

// Custom CVARs.
std::map<std::string_view, std::string_view> customCVARs;

// Console commands. The various systems will add to this map as they initialize.
std::map<std::string_view, std::function<void ()>> CCMDs;

// Number of lines of text displayed in the console. This is changed when either
// the console's vertical height or text size is changed (changing the
// horizontal size has no effect on this), and is used to help with scrolling
// the output window.
static uint8_t visibleLines = 0;

// Input string. User types into this when typing into the console.
// The max length of the input itself is 256 characters, but as this supports
// UTF-8, where each character can be up to 4 bytes, the actual length of the
// string is 1024 bytes, with the last byte always being a null character.
static std::string input(1025, '\0');

// Iterator for the input string. This moves as the user types / deletes
// characters from the string.
static std::string::iterator inputPos;

// Outputs to the console. Each output can be either a string
typedef struct _output
{
	std::variant<std::string, std::string_view> text;
	uint8_t numLines;
}
output;

std::list<output> outputs;

// CVARs.
static FloatCVAR
	alpha(0.75, 0.0, 1.0, "consoleAlphaDesc"),
	borderAlpha(1.0, 0.0, 1.0, "consoleBorderAlphaDesc"),
	xPos(0.0, -0.9, 0.9, "consoleXPosDesc"),
	yPos(0.0, -0.9, 0.9, "consoleYPosDesc"),
	width(0.75, 0.1, 1.0, "consoleWidthDesc"),
	height(0.75, 0.1, 1.0, "consoleHeightDesc"),
	textScale(0.5, 0.1, 0.5, "consoleTextScaleDesc");

// Pixel sizes of console and text.
// Used mainly for some calculations and maths.
static uint16_t pixWidth, pixHeight;
static uint16_t pixTextSize;

// Rendering context objects used to draw the console when it's open. These
// always exist, whether they're used depends on the console being open.
const std::string_view
	vertexShaderName	= "console.vs",
	geometryShaderName	= "console.gs",
	fragmentShaderName	= "console.fs";

/**
 * Console commands "con_width" and "con_height". Changes the width and height
 * of the console. Takes in a float between 0.0 and 1.0 that's a percentage of
 * the screen's width and height.
 */

bool setWidth(const float val)
{
	// Get screen width.
	IntCVAR *display = static_cast<IntCVAR *>(systemCVARs["vid_display"]);
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode((*display), &mode);
	pixWidth = mode.w;

	return true;
}

bool setHeight(const float val)
{
	// Get screen width.
	IntCVAR *display = static_cast<IntCVAR *>(systemCVARs["vid_display"]);
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode((*display), &mode);
	pixHeight = mode.h;

	return true;
}

/**
 * Console command "con_textsize". Sets the size of the console text.
 */

bool setTextSize(const float val)
{
	// Re-render character map.
	return true;
}

/**
 * Renders text.
 */



/**
 * Adds a string to the console's output.
 */

void giveOutput(const std::string_view &str)
{
	outputs.insert(outputs.end(), { str, 1 });
	printf("%s\n", str.data());
}

void giveOutput(const std::string &str)
{
	outputs.insert(outputs.end(), { str, 1});
	printf("%s\n", str.c_str());
}

/**
 * Scrolls the output window up / down. The number of lines to scroll can be
 * either positive (scroll down), or negative (scroll up). If either the Home or
 * End keys are pressed, the value is the max (set by C++ defines), which
 * indicates just moving to the very top / bottom of the output list.
 */

static void scrollOutput(const int8_t numLines)
{
	static uint8_t startLine = 0;

	if(numLines == INT8_MIN)
		startLine = 0;
	else if(numLines == INT8_MAX)
		startLine = numLines - visibleLines;

	// Re-renders text output starting at the specified output and line.

}

/**
 * Draws console. This is done on top of the rendered scene, to allow for
 * any transparency.
 */

void draw()
{
	/*
	renderer::programs["console"]->use();
	renderer::programs["console"]->execute();
	*/
}

/**
 *
 */

uint8_t init()
{
	systemCVARs.insert
	(
		{
			{ "con_alpha",		&alpha },
			{ "con_bdralpha",	&borderAlpha },
			{ "con_xpos",		&xPos },
			{ "con_ypos",		&yPos },
			{ "con_width",		&width },
			{ "con_height",		&height },
			{ "con_textscale",	&textScale }
		}
	);

	return 0;
}

/**
 * Submits the console's input string for processing.
 * This first checks if the input string matches an existing
 */

static void submitInput()
{

}

/**
 *
 */

void quit()
{

}

} // namespace console

} // namespace coreLib

/**
 * Exported functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Console's main function. Should be called by the program using this library
 * when the console is open. Not doing so might cause problems.
 */

void LIB_FUNC_CALL coreConsoleMain()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.scancode)
		{
			// Special case keys. These scroll the output window.
			case SDL_SCANCODE_UP:
				coreLib::console::scrollOutput(-1);
				break;
			case SDL_SCANCODE_DOWN:
				coreLib::console::scrollOutput(1);
				break;
			case SDL_SCANCODE_PAGEUP:
				coreLib::console::scrollOutput(-coreLib::console::visibleLines);
				break;
			case SDL_SCANCODE_PAGEDOWN:
				coreLib::console::scrollOutput(coreLib::console::visibleLines);
				break;
			case SDL_SCANCODE_HOME:
				coreLib::console::scrollOutput(INT8_MIN);
				break;
			case SDL_SCANCODE_END:
				coreLib::console::scrollOutput(INT8_MAX);
				break;

			// Return key submits the output.
			case SDL_SCANCODE_RETURN:
				coreLib::console::submitInput();
				break;

			// Default behavior is to attempt to add the input to the input string.
			default:
				{
					//*inputPos = *;
					return;
				}
		}
	}
	else if(event.type == SDL_MOUSEWHEEL)
	{
		if(event.wheel.y > 0)
			coreLib::console::scrollOutput(-event.wheel.y);
		else if(event.wheel.y < 0)
			coreLib::console::scrollOutput(event.wheel.y);
	}
}

/**
 * Allows program to send output messages to the console.
 */

void LIB_FUNC_CALL coreConsoleOutput(const std::string &str)
{

}

/**
 * Toggles console on / off. Adds / removes console's shader program from the
 * list of active programs. The program using this library should decide what
 * key or combination of keys will do this.
 */

void LIB_FUNC_CALL coreConsoleToggle()
{
	coreLib::console::isOpen = !coreLib::console::isOpen;

	//coreLib::console::isOpen
	//	? coreLib::renderer::programs["console"].enable;
	//	: coreLib::renderer::programs["console"].disable
}

#ifdef __cplusplus
} // extern "C"
#endif
