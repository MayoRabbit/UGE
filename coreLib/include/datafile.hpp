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

datafile.hpp

*******************************************************************************/

#include <filesystem>
#include <vector>

namespace coreLib
{

/**
 * Datafile class.
 */

class Datafile
{
	// Datafile entry. All the entries make up the table of contents, and each
	// entry is stored as follows:
	// - A null-terminated string giving the entry's name. Theoretically this
	//   can have no limit in length but plz don't do that.
	// - 8 bytes for the address of the entry in the datafile.
	// - 4 bytes for the size of the entry's data.
	typedef struct _entry
	{
		std::string_view	name;
		void				*address;
		uint32_t			length;
	}
	entry;

	std::vector<entry> tableOfContents;

	public:
		Datafile() = delete;
		Datafile(const std::filesystem::path &filename);
		~Datafile();

		// Copy semantics deleted.
		Datafile(const Datafile &) = delete;
		Datafile & operator = (const Datafile &) = delete;

		// Move semantics.
		Datafile(Datafile &&df);
		Datafile & operator = (Datafile &&df);

		void *getEntryAddress(const std::string_view &name);
		void *getEntryName(const void *address);
};

} // namespace coreLib
