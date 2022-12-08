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

describable.hpp

A simple class for objects to extend from. Such objects can "describe"
themselves in the console by displaying information about them.

*******************************************************************************/

#pragma once

#include <string>
#include <string_view>

namespace coreLib
{

class Describable
{
	// Description of the object. Can be changed by changing the language file
	// used.
	std::string description;

	public:
		Describable() = default;
		Describable(const std::string_view &desc);
		~Describable() = default;

		// Copy semantics deleted. Any class inheriting from this one should be
		// unique with its own unique description.
		Describable(const Describable &) = delete;
		Describable & operator = (const Describable &) = delete;

		// Move semantics.
		Describable(Describable &&d) :
			description(std::move(d.description))
		{}

		Describable & operator = (Describable &&d)
		{
			description = std::move(d.description);
			return *this;
		}

		// Returns the description string as a const reference. Can be used with
		// other strings and objects. Just can't be modified.
		inline const std::string & describe() const
		{
			return description;
		}
};

} // namespace coreLib
