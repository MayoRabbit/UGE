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

audio.hpp

*******************************************************************************/

#pragma once

#include <string_view>
#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include "describable.hpp"

namespace coreLib
{

namespace audio
{

/**
 * AudioDevice class.
 */

class AudioDevice : public Describable
{
	const int id;

	public:
		AudioDevice() = delete;
		AudioDevice(const int id);
		~AudioDevice();

		// Copy and move semantics deleted. Devices are determined when
		// the program starts, and they are constant.
		AudioDevice(const AudioDevice &) = delete;
		AudioDevice(AudioDevice &&) = delete;
		AudioDevice & operator = (const AudioDevice &) = delete;
		AudioDevice & operator = (AudioDevice &&) = delete;

		void open() const;

		inline void close() const
		{
			Mix_CloseAudio();
		}
};

/**
 * AudioDriver class.
 */

class AudioDriver : public Describable
{
	const int id;

	public:
		AudioDriver() = delete;
		AudioDriver(const int i);
		~AudioDriver();

		// Copy and move semantics deleted. Drivers are determined when
		// the program starts, and they are constant.
		AudioDevice(const AudioDevice &) = delete;
		AudioDevice(AudioDevice &&) = delete;
		AudioDevice & operator = (const AudioDevice &) = delete;
		AudioDevice & operator = (AudioDevice &&) = delete;
};

/**
 * AudioChannel class.
 * Might be used.
 */

class AudioChannel
{
	public:
		AudioChannel();
		~AudioChannel();
};

/**
 * AudioFile class. Abstract.
 * Basic audio file stuff.
 */

class AudioFile
{
	Mix_Chunk		chunk;
	SDL_AudioFormat	format;

	public:
		AudioFile() = delete;
		AudioFile(const std::string_view &filename);
		virtual ~AudioFile();

		virtual bool play() = 0;
		virtual bool stop() = 0;
};

/**
 * MusicFile class.
 * This version of the library only supports WAV, FLAC, and OGG formats.
 * If you fork this, feel free to add support for others.
 */

class MusicFile : public AudioFile
{
	// Format.
	typedef enum _format
	{
		AFF_FLAC,
		AFF_OGG,
		AFF_WAV
	} format;

	public:
		MusicFile() = delete;
		MusicFile(const std::string_view &filename);
		~MusicFile();

	bool play();
	bool stop();
	bool pause();
};

/**
 * SoundFile class.
 * All sound files are in WAV format. For now. Maybe.
 */

class SoundFile : public AudioFile
{

	public:
		SoundFile() = delete;
		SoundFile(const std::string_view &filename);
		~SoundFile();

		bool play();
		bool stop();
};

uint8_t	init();
void	quit();

} // namespace audio

} // namespace audio
