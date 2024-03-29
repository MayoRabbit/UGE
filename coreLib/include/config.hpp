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

config.hpp

*******************************************************************************/

#pragma once

#include <filesystem>
#include <fstream>

namespace coreLib
{

namespace configuration
{

/**
 * Configuration file class.
 */

class CFGFile
{
	friend const uint8_t	init();
	friend void				quit();

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
		CFGFile(CFGFile &&f);
		CFGFile & operator = (CFGFile &&f);

		// Operator ! overload.
		inline bool operator ! ()
		{
			return !std::filesystem::exists(cfgFilePath);
		}

		void load();
		void save();
};

const uint8_t	init();
void			quit();

} // namespace configuration

} // namespace coreLib
