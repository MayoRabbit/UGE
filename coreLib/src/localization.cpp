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

localization.cpp

Handles files containing translations for various text strings in various
languages. The language files are stored in the "./locale" directory, with
subdirectories for each language. These subdirectory folder names should be the
language identifier (i.e. "./locale/en_us").

Inside these subdirectories there should be at least 4 text files:
- core.ini
- opengl.ini
- vulkan.ini
- game.ini

The first three contain strings used by this core library, and the OpenGL and
Vulkan wrapper libraries. Only the wrapper library currently in use will have
its language file loaded. The "game.ini" file is for strings used by the game
using these libraries. More than these 4 files may be used, simply add them to
the list of files this system should use.

Each line in a language file supplies a string in the format:

<identifier>="<string>"

The identifiers are the same for each language file, and consist of Latin
characters only. The strings themselves are Unicode. Language files should be
UTF-8 format to accommodate this.

When a program using this library starts, it should look for the language files
specified by the "language" CVAR setting. If this fails, it should look for the
language files specified by the default locale. If this fails, default to the
English language file. If this fails, program fails. Can't run a program using
this library if there's no text to display, can you?

If the language setting is changed during runtime, newer messages will be
displayed in the new locale, but previous messages will be displayed in the old
one. There's no way (that I know of currently) to re-translate everything that's
already been sent to the console outputs.

Finally, the English language files are always loaded, regardless of the locale
setting. This is not only to provide a fallback in case something goes wrong
with other language files (such as a missing string), but to also produce an
English language log file to send if need be.

*******************************************************************************/

#include <iostream>
#include <regex>
#include <SDl2/SDL.h>
#include "console.hpp"
#include "localization.hpp"

namespace coreLib
{

namespace localization
{

// Locale as defined by the user's system. This will be use either by
static const char *systemLocale = std::setlocale(LC_ALL, "");

// Directory for the locale files.
static const std::filesystem::path				localePath("./locale");
static const std::filesystem::directory_entry	localeDir(localePath);

// Map of supported languages and filenames. This is in case the system reports
// a long locale name instead of a short one, then this should help.
static const std::map<const std::string_view, const std::string_view> languages =
{
	{ "English_United States", "en_us" }
};

// English language file is always used, in case of needing a fallback, or other
// special circumstance.
static const LanguageFile defaultLanguageFile("en_us");

// Default message string not found message.
static constexpr std::string_view defStrNotFoundMsg = "Error: Message '%s' not found in language file '%s'!";

// Strings in the language file.
std::map<std::string, std::string> strings;

/**
 * CVARs.
 */

console::Uint8CVAR language;

/**
 * CVAR change callbacks.
 */

bool changeLanguage(const uint8_t &val)
{
	LanguageFile lf("en_us");
	if(!lf.load())
	{
		return false;
	}

	return true;
}

/**
 * LanguageFile class.
 */

// Constructor.
LanguageFile::LanguageFile(const std::string_view &filename) :
	localeFilePath(localePath.string() + "/" + filename.data() + ".ini")
{
	// Message format.
	static const std::regex stringFormat("^\\s*([a-zA-Z]+)=\"(\\w+)\"\\s*$", std::regex_constants::icase);

	std::smatch rm;

	localeFile.open(localeFilePath.string(), std::ios::in);
	if(!localeFile.is_open())
	{

		return;
	}

	strings.clear();

	std::string line;
	std::smatch matches;

	while(std::getline(localeFile, line))
	{
		// If comment, ignore.
		std::regex_match(line, matches, stringFormat);
		if(!matches.size())
		{
			continue;
		}

		if(matches.size() != 2)
		{
			continue;
		}

		std::string_view
			id	= matches[1].str().c_str(),
			str	= matches[2].str().c_str();

		strings[id] = str;
	}

	localeFile.close();
}

/**
 * Move Constructor
 */

LanguageFile::LanguageFile(LanguageFile &&lf)
{
	localeFilePath.swap(lf.localeFilePath);
}

/**
 * Move Assignment
 */

LanguageFile & LanguageFile::operator = (LanguageFile &&lf)
{
	localeFilePath.swap(lf.localeFilePath);
	return *this;
}

/**
 * Console command "loc_listlocales". Displays the available language files.
 */

void listLocales()
{
	static std::string str;

	if(str.empty())
	{

	}
}

/**
 * Gets the list of language files from the ./locale directory. If there are
 * none or the folder doesn't exist at all, it's a fatal error. Can't really do
 * anything if you can't display text to the user at all, can you?
 */

uint8_t init()
{
	// Set the locale to UTF-8.
	std::setlocale(LC_ALL, ".UTF-8");

	// Locale directory.
	if(!localeDir.exists())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR!", "Directory 'locale' does not exist.\nPlease reinstall the program.", nullptr);
		return 1;
	}
	std::filesystem::directory_iterator localeDirIt(localePath);

	// Locale files.
	if(std::filesystem::begin(localeDirIt) == std::filesystem::end(localeDirIt))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR!", "Directory 'locale' contains no language files.\nPlease reinstall the program.", nullptr);
		return 2;
	}

	uint8_t numLangFiles = 0;
	for(auto &langFile : localeDirIt)
		numLangFiles++;

	// CVAR to select language file.
	// The files are numbered 1 to the number of files, in the order the
	// directory iterator lists them.
	// 0 can be used to select the language automatically (system language).
	language = { 0, 0, numLangFiles, "locLanguageDesc", changeLanguage };

	console::systemCVARs.insert( { "loc_language", { &language } } );

	// Initial behavior is to load the locale file specified by the system
	// locale, then reload with the selected language in the configuration
	// file(s). If none of this can be done, use the English file.
	std::string_view sysLangFilename(systemLocale);
	LanguageFile sysLangFile(sysLangFilename);

	if(!sysLangFile)
	{
		//console::giveOutput();
		return 3;
	}

	return 0;
}

void quit()
{

}

bool LanguageFile::load()
{
	static const std::regex strFormat("^\\s*([a-zA-Z_]+)=\"(\\w+)\"\\s*&", std::regex_constants::icase);

	std::ifstream lf(localePath);
	if(!lf.is_open())
	{
		return false;
	}

	// If the file is empty, then WTF?
	std::string line;
	std::smatch matches;

	while(std::getline(lf, line))
	{
		std::regex_match(line, matches, strFormat);

		// There should be three matches. One for the string and two for the
		// submatches (identifier and string).
		if(matches.size() != 3)
		{

		}

		// Scan the string for tokens. Split string into pieces based on where
		// tokens are.
		uint8_t numTokens;

		std::string_view
			name	= matches[1].str().c_str(),
			value	= matches[2].str().c_str();

		//*(LanguageFile::strings[name]) = { };
	}

	lf.close();

	return true;
}

const std::string_view & getString(const std::string_view &name)
{
	return strings[name];
}

} // namespace localization

} // namespace coreLib
