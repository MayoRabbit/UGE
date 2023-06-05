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

video.hpp

*******************************************************************************/

#pragma once

#include <string_view>

namespace coreLib
{

namespace video
{

class VideoDriver
{
	const int			id;
	std::string_view	name;

	public:
		VideoDriver() = delete;
		VideoDriver(const int i);
		~VideoDriver() = default;

		// Copy and move semantics deleted. Drivers are determined when
		// the program starts, and they are constant.
		VideoDriver(const VideoDriver &)	= delete;
		VideoDriver(VideoDriver &&)			= delete;
		VideoDriver & operator = (const VideoDriver &)	= delete;
		VideoDriver & operator = (VideoDriver &&)		= delete;

		inline void describe() const
		{
			printf("%i: %s\n", id, name.data());
		}
};

class VideoDisplay
{
	const int id;
	std::string_view name;

	public:
		VideoDisplay() = delete;
		VideoDisplay(const int i);
		~VideoDisplay() = default;

		// Copy and move semantics deleted. Displays are determined when
		// the program starts, and they are constant.
		VideoDisplay(const VideoDisplay &)	= delete;
		VideoDisplay(VideoDisplay &&)		= delete;
		VideoDisplay & operator = (const VideoDisplay &)	= delete;
		VideoDisplay & operator = (VideoDisplay &&)			= delete;

		inline void describe()
		{
			printf("%i: %s\n", id, name.data());
		}
};

uint8_t	init();
void	quit();

} // namespace video

} // namespace coreLib
