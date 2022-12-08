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

cvar.hpp

*******************************************************************************/

#pragma once

#include <concepts>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <typeinfo>
#include "config.hpp"
#include "describable.hpp"

namespace coreLib
{

// CVARs are part of the console system.
namespace console
{

/**
 * Base CVAR class. Abstract.
 */

class CVAR : public Describable
{
	// These need to read the values of CVARs.
	friend uint8_t	config::init();
	friend void		config::CFGFile::load();
	friend void		config::CFGFile::save();

	protected:
		std::string_view
			defaultValue,	// Hard coded.
			descriptionID;	// Description of CVAR provided by language file. Hopefully.

		std::string value;	// Current value.

	public:
		CVAR() = default;
		CVAR(const std::string_view &defVal, const std::string_view &descID);
		virtual ~CVAR() = default;

		// Copy semantics deleted.
		CVAR(const CVAR &) = delete;
		CVAR & operator = (const CVAR &) = delete;

		// Move semantics.
		CVAR(CVAR &&cv);
		CVAR & operator = (CVAR &&cv);

		// Resets CVAR to its default value, applying any other changes in the process.
		void reset()
		{
			*this = defaultValue;
		}

		// Purely virtual.
		virtual void operator = (const std::string_view &) = 0;
};

/**
 * Numeric CVAR.
 *
 * Template to support various types, as long as they're numeric types.
 * Includes min and max values.
 */

template<typename T>
concept isNumericCVAR = std::integral<T> || std::floating_point<T>;

template<typename T> requires isNumericCVAR<T>
class NumericCVAR final : public CVAR
{
	T numDefaultValue, numMinValue, numMaxValue, numValue;
	std::string_view minValue, maxValue;

	// Optional callback function to call when attempting to change the CVAR's
	// value. Can be used for extra validation checks that this class does not
	// perform.
	bool(*changeFunc)(const T val);

	public:
		NumericCVAR() = default;
		~NumericCVAR() = default;

		// Copy semantics deleted.
		NumericCVAR(const NumericCVAR &) = delete;
		NumericCVAR & operator = (const NumericCVAR &) = delete;

		// Constructor.
		NumericCVAR(const T defVal, const T minVal, const T maxVal, const std::string_view &descID, bool(*cf)(const T) = nullptr) :
			CVAR(std::to_string(defVal), descID),
			numDefaultValue(defVal),
			numMinValue(minVal),
			numMaxValue(maxVal),
			minValue(std::to_string(numMinValue)),
			maxValue(std::to_string(numMaxValue)),
			changeFunc(cf)
		{}

		// Move constructor.
		NumericCVAR(NumericCVAR &&cv) :
			CVAR(std::move(cv))
		{
			minValue.swap(cv.minValue);
			maxValue.swap(cv.maxValue);
			numDefaultValue	= cv.numDefaultValue;
			numMinValue		= cv.numMinValue;
			numMaxValue		= cv.numMaxValue;
			changeFunc		= cv.changeFunc;
		}

		// Move assignment.
		NumericCVAR & operator = (NumericCVAR &&cv)
		{
			CVAR::operator = (std::move(cv));
			minValue.swap(cv.minValue);
			maxValue.swap(cv.maxValue);
			numDefaultValue	= cv.numDefaultValue;
			numMinValue		= cv.numMinValue;
			numMaxValue		= cv.numMaxValue;
			changeFunc		= cv.changeFunc;
			return *this;
		}

		// Get a CVAR's value.
		inline operator T()
		{
			return numValue;
		}

		/**
		 * Attempts to change a CVAR's value.
		 */

		void operator = (const std::string_view &val) override
		{
			T nVal;

			try
			{
				nVal = (T)std::stof(val.data());
			}
			catch(std::invalid_argument &ia)
			{
				printf("%s\n", ia.what());
			}

			if(nVal < numMinValue || nVal > numMaxValue)
			{

			}

			// If the CVAR does not have a function to validate the value, or if
			// it does and it returns true, the value is valid, and may be
			// assigned.
			if(!changeFunc || (*changeFunc)(nVal))
			{
				value.clear();
				value = val;
			}
		}
};

/**
 * Boolean CVAR. Specialized template.
 */

template<>
class NumericCVAR<bool> final : public CVAR
{
	bool numDefaultValue, numValue;

	bool(*changeFunc)(const bool val);

	public:
		NumericCVAR() = default;
		NumericCVAR(const bool defVal, const std::string_view &descID);
		~NumericCVAR() = default;

		// Copy semantics deleted.
		NumericCVAR(const NumericCVAR &) = delete;
		NumericCVAR & operator = (const NumericCVAR &) = delete;

		// Move semantics.
		NumericCVAR(NumericCVAR &&cv);
		NumericCVAR & operator = (NumericCVAR &&cv);

		// Operator overloads.
		void operator = (const std::string_view &val) override;

		/**
		 *
		 */

		inline operator bool()
		{
			return numValue;
		}

		/**
		 * Toggles CVAR on / off.
		 */

		inline void toggle()
		{
			*this = numValue ? "0" : "1";
		}
};

// Some typedefs for easier use.
typedef NumericCVAR<uint8_t>	Uint8CVAR;
typedef NumericCVAR<int>		IntCVAR;
typedef NumericCVAR<float>		FloatCVAR;
typedef NumericCVAR<bool>		BoolCVAR;

} // namespace console

} // namespace coreLib
