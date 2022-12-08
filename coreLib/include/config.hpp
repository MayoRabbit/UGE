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

config.hpp

*******************************************************************************/

#pragma once

#include <filesystem>
#include <fstream>
#include <regex>
#include <string_view>

namespace coreLib
{

namespace config
{

/**
 * Configuration file class.
 */

class CFGFile
{
	friend uint8_t	init();
	friend void		quit();

	// Directory config files are stored in. Default is "./config".
	static const std::filesystem::path				cfgDirPath;
	static const std::filesystem::directory_entry	cfgDirectory;

	std::filesystem::path	cfgFilePath;
	std::fstream			cfgFile;

	public:
		CFGFile() = delete;
		CFGFile(const std::string_view &filename);
		~CFGFile() = default;

		// Copy semantics deleted.
		CFGFile(const CFGFile &) = delete;
		CFGFile & operator = (const CFGFile &) = delete;

		// Move semantics.
		CFGFile(CFGFile &&cf);
		CFGFile & operator = (CFGFile &&cf);

		// Operator ! overload.
		inline bool operator ! ()
		{
			return !std::filesystem::exists(cfgFilePath);
		}

		void load();
		void save();
};

uint8_t	init();
void	quit();

} // namespace config

} // namespace coreLib
