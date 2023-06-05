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

localization.hpp

*******************************************************************************/

#pragma once

#include <functional>
#include <variant>

namespace coreLib
{

/**
 * LanguageFile class.
 * Each instance of this class represents a language file in the "./locale"
 * directory.
 */

namespace localization
{

class LanguageFile
{
	// Localization system.
	friend uint8_t	init();
	friend void		quit();

	// Locale file. These can (and should) only be read from.
	std::filesystem::path	localeFilePath;
	std::ifstream			localeFile;

	public:
		LanguageFile() = delete;
		LanguageFile(const std::string_view &filename);
		~LanguageFile() = default;

		// Copy semantics deleted.
		LanguageFile(const LanguageFile &) = delete;
		LanguageFile & operator = (const LanguageFile &) = delete;

		// Move semantics.
		LanguageFile(LanguageFile &&lf);
		LanguageFile & operator = (LanguageFile &&lf);

		// Operator overloads.
		inline bool operator ! ()
		{
			return !std::filesystem::exists(localeFilePath);
		}

		bool load();
		std::string parseString(const std::string_view &id, const std::vector<std::variant<std::string_view, int, float>> &values);
};

uint8_t	init();
void	quit();

} // namespace loclaization

} // namespace coreLib
