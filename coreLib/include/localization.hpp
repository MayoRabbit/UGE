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

#include <concepts>
#include <filesystem>
#include <map>
#include <regex>
#include <string_view>
#include <vector>

namespace coreLib
{

namespace localization
{

// For the string parsing function for this class.
//
template<typename T>
concept isNumeric = std::integral<T> || std::floating_point<T>;

class LanguageFile
{
	friend uint8_t	init();
	friend void		quit();

	// Directory for locale files. Should be "./locale".
	static const std::filesystem::path				localePath;
	static const std::filesystem::directory_entry	localeDir;

	// Locale file path.
	std::filesystem::path locFilePath;
	std::fstream locFile;

	// Information about a string.
	typedef struct _stringInfo
	{
		std::vector<std::string>	parts;
		size_t	length, adjLength;
	}
	stringInfo;

	// List of messages currently loaded. This can be modified to add / remove
	// strings depending on what the program needs at a certain point in time.
	static std::map<std::string_view, stringInfo> strings;

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
			return !std::filesystem::exists(locFilePath);
		}

		/**
		 * Parses a locale string. Similar to functions such as sprintf(),
		 * except this takes a vector of values to use instead of being
		 * variadic.
		 */

		template<typename T> requires isNumeric<T>
		static std::string parseString(const std::string_view &id, const std::vector<T> &values)
		{
			// If there are no tokens, just return the string.
			if(strings[id].parts.size() == 1)
				return strings[id].parts[0];

			std::string str;

			// Length of new string.
			auto length	= strings[id].adjLength;
			auto value	= values.cbegin();

			do
			{
				length += (*value).length();
				value++;
			}
			while(value != values.end());

			str.resize(length);

			// Copies the conte
			//do
			//{

			//}
			//while();

			return str;
		}
};

uint8_t	init();
void	quit();

} // namespace localization

} // namespace coreLib
