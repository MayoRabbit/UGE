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

localization.cpp

Handles files containing translations for various text strings in various
languages. Currently this only applies to English but maybe it'll get expanded
to other languages. One day.

Each line in a language file supplies a string in the format:

<identifier>="<string>"

The identifiers are the same for each language file, and consist of Latin
characters only. The strings themselves are Unicode. Language files should be
UTF-8 format to accommodate this.

If a specific message cannot be found in a language file, the default English
string will be used, and a warning in the selected language displayed in the
console. If this message itself cannot be found, a hard coded warning in English
will be used instead. None of this should actually happen in practice.

The English language file is always used and loaded. This is so, if a different
language is used by the user, a separate log file (log_en.txt) is saved to send
the developer (me, who only speaks English), to read. And also to use as the
last fallback default if a message cannot be displayed in the user's preferred
language.

*******************************************************************************/

#include <iostream>
#include <locale>
#include <regex>
#include <SDL2/SDL.h>
#include "console.hpp"
#include "cvar.hpp"
#include "localization.hpp"

namespace coreLib
{

namespace localization
{

// System locale.
static const char *systemLocale = std::setlocale(LC_ALL, "");

// Map of supported languages and filenames. This is in case the system reports
// a long locale name instead of a short one, then this should help.
static const std::map<const std::string_view, const std::string_view> languages =
{
	{ "English_United States", "en_us" }
};

// Locale directory.
const std::filesystem::path				LanguageFile::localePath("./locale");
const std::filesystem::directory_entry	LanguageFile::localeDir(localePath);

// Default message string not found message.
static constexpr std::string_view defStrNotFoundMsg = "Error: Message '%s' not found in language file '%s'!";

static LanguageFile lang_en("lang_en");

// This will be filled in once the locale directory is scanned for language
// files.
console::Uint8CVAR language;

/**
 * Constructor
 */

LanguageFile::LanguageFile(const std::string_view &filename) :
	locFilePath(localePath.string() + "/" + filename.data() + ".ini")
{
	// Message format.
	static const std::regex messageFormat("^\\s*([a-zA-Z]+)=\"(\\w+)\"\\s*$", std::regex_constants::icase);

	std::smatch rm;

	// Open language file. If it does not exist, do nothing, as there is nothing
	// to do, obviously.
	locFile.open(locFilePath.string(), std::ios::in);
	if(!locFile.is_open())
	{

		return;
	}

	std::string line;

	while(std::getline(locFile, line))
	{
		std::regex_match(line, rm, messageFormat);
		if(rm.size())
		{
			for(auto &m : rm) printf("%s\n", m.str().c_str());
		}
	}

	locFile.close();

}

/**
 * Move Constructor
 */

LanguageFile::LanguageFile(LanguageFile &&lf)
{
	locFilePath.swap(lf.locFilePath);
}

/**
 * Move Assignment
 */

LanguageFile & LanguageFile::operator = (LanguageFile &&lf)
{
	locFilePath.swap(lf.locFilePath);
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
	// Locale directory.
	if(!LanguageFile::localeDir.exists())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR!", "Directory 'locale' does not exist.\nPlease reinstall the program.", nullptr);
		return 1;
	}
	std::filesystem::directory_iterator localeDirIt(LanguageFile::localePath);

	// Locale files.
	if(std::filesystem::begin(localeDirIt) == std::filesystem::end(localeDirIt))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR!", "Directory 'locale' contains no language files.\nPlease reinstall the program.", nullptr);
		return 2;
	}

	uint8_t numLangFiles = 0;
	for(auto &langFile : localeDirIt)
	{
		numLangFiles++;
		std::cout << "Found language file: '" << langFile << ".'\n";
	}

	// CVAR to select language file.
	// The files are numbered 1 to the number of files, in the order the
	// directory iterator lists them.
	// 0 can be used to select the language automatically (system language).
	language = { 0, 0, numLangFiles, "locLanguageDesc" };

	console::systemCVARs.insert( { "loc_language", &language } );

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

} // namespace localization

} // namespace coreLib
