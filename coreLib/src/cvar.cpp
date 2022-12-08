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

cvar.cpp

Console Variables. Some settings may be changed through the graphical console by
typing in the setting's name and a new value. Not all CVARs may be changed this
way, and some may require the forced restart of the system they're associated
with (if not the whole program) in order to change. See a specific CVAR for any
details.

There are two types of CVARs. System CVARs are hard coded and are all strictly
numeric values. Custom CVARs may contain various types including strings, and
may be used to create aliases and batch commands.

This idea was "borrowed" from games like Quake. Don't tell on me plz.

*******************************************************************************/

#include "cvar.hpp"

namespace coreLib
{

namespace console
{

/**
 * CVAR class.
 */

// Constructor.
CVAR::CVAR(const std::string_view &defVal, const std::string_view &descID) :
	defaultValue	(defVal),
	descriptionID	(descID)
{}

// Move constructor.
CVAR::CVAR(CVAR &&cv)
{
	defaultValue.swap(cv.defaultValue);
	descriptionID.swap(cv.descriptionID);
}

// Move assignment.
CVAR & CVAR::operator = (CVAR &&cv)
{
	defaultValue.swap(cv.defaultValue);
	descriptionID.swap(cv.descriptionID);
	return *this;
}

/**
 * Boolean CVAR.
 */

// Constructor.
NumericCVAR<bool>::NumericCVAR(const bool defVal, const std::string_view &descID) :
	CVAR(std::to_string(defVal), descID)
{
	// String version of a boolean's value is limited to being either "0" or
	// "1", so the length of the string is limited too.
	value.resize(2);
	value[1] = '\0';
}

// Move constructor.
NumericCVAR<bool>::NumericCVAR(NumericCVAR &&cv) :
	CVAR(std::move(cv))
{
	defaultValue.swap(cv.defaultValue);
	descriptionID.swap(cv.descriptionID);
	numDefaultValue	= cv.numDefaultValue;
	numValue		= cv.numValue;
}

// Move assignment.
NumericCVAR<bool> & NumericCVAR<bool>::operator = (NumericCVAR &&cv)
{
	defaultValue.swap(cv.defaultValue);
	descriptionID.swap(cv.descriptionID);
	numDefaultValue	= cv.numDefaultValue;
	numValue		= cv.numValue;
	return *this;
}

//
void NumericCVAR<bool>::operator = (const std::string_view &val)
{
	if(val == "0")
	{
		value[0] = '0';
		numValue = false;
	}
	else
	{
		value[0] = '1';
		numValue = true;
	}
}

} // namespace console

} // namespace coreLib
