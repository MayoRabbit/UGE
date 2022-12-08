/*******************************************************************************

<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2022 <name of author>

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

#include <bitset>
#include <cstdlib>
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

// System CVARs. The various systems will add to this map as they initialize.
std::map<std::string_view, CVAR *> systemCVARs;

// Custom CVARs.
std::map<std::string_view, std::string_view> customCVARs;

// Console commands. The various systems will add to this map as they initialize.
std::map<std::string_view, void(*)()> CCMDs;

// Input string. User types into this when typing into the console.
// Max length of this string is 257 characters; 256 is the string itself, the
// 257th is always a null character.
std::string input(257, '\0');

// Output strings that make up the log displayed in the console.
//
std::list<std::variant<std::string_view, std::string>> outputs;

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

/**
 * Console commands "con_width" and "con_height". Changes the width and height
 * of the console. Takes in a float between 0.0 and 1.0 that's a percentage
 * of the screen's width and height.
 */

bool setWidth(const float val)
{
	//shaders["console"]->attibute["width"] = val;
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
	outputs.insert(outputs.end(), str);
	printf("%s\n", str.data());
}

void giveOutput(const std::string &str)
{
	outputs.insert(outputs.end(), str);
	printf("%s\n", str.c_str());
}

/**
 * Scrolls the output window up / down. Called by the console's input handling
 * function if the appropriate inputs are given:
 * - Mousewheel up / down. Scrolls by a number of lines between 2 and
 * - Arrow key up / down. Scrolls one line at a time. Hold the key to scroll
 *   faster.
 * - Home / End / Page Up / Page Down. Scrolls by the number of lines displayed
 *   in the window, or until either end is reached.
 *
 */

static void scrollOutput(const std::bitset<5> &flags)
{
	static uint16_t startLine = 0;

	if(flags[0])
	{
	}
	else
	{
	}
}

/**
 * Draws console. This is done on top of the rendered scene, to allow for
 * any transparency.
 */

void draw()
{
	/*
	shaders["console"]->use();

	*/
}

/**
 *
 */

uint8_t init()
{
	systemCVARs.insert
	({
		{ "con_alpha",		&alpha },
		{ "con_bdralpha",	&borderAlpha },
		{ "con_xpos",		&xPos },
		{ "con_ypos",		&yPos },
		{ "con_width",		&width },
		{ "con_height",		&height },
		{ "con_textscale",	&textScale }
	});

	return 0;
}

/**
 * Console input handler.
 */

void addInput()
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
