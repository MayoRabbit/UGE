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

audio.hpp

*******************************************************************************/

#pragma once

#include <string_view>
#include <SDL2/SDL_mixer.h>

namespace coreLib
{

namespace audio
{

/**
 * AudioDevice class.
 */

class AudioDevice
{
	// ID number the device currently opened.
	static int openID;

	// Device ID number.
	const int id;

	// Description of device displayed in the console.
	std::string description;

	public:
		AudioDevice() = delete;
		AudioDevice(const int id);
		~AudioDevice();

		// Copy and move semantics deleted. Devices are determined when
		// the program starts, and they are constant.
		AudioDevice(const AudioDevice &)	= delete;
		AudioDevice(AudioDevice &&)			= delete;
		AudioDevice & operator = (const AudioDevice &)	= delete;
		AudioDevice & operator = (AudioDevice &&)		= delete;

		void open() const;

		inline void close() const
		{
			Mix_CloseAudio();
		}

		// Outputs device info to console.
		inline void describe() const
		{
			printf("%i: %s\n", id, SDL_GetAudioDeviceName(id, 0));
		}
};

/**
 * AudioDriver class.
 */

class AudioDriver
{
	// ID of the audio driver currently in use.
	static int openID;

	// Driver ID number.
	const int id;

	// Description of driver displayed in the console.
	std::string description;

	public:
		AudioDriver() = delete;
		AudioDriver(const int i);
		~AudioDriver();

		// Copy and move semantics deleted. Drivers are determined when
		// the program starts, and they are constant.
		AudioDriver(const AudioDriver &)	= delete;
		AudioDriver(AudioDriver &&)			= delete;
		AudioDriver & operator = (const AudioDriver &)	= delete;
		AudioDriver & operator = (AudioDriver &&)		= delete;

		// Outputs driver info to console.
		inline void describe() const
		{
			printf("%i: %s\n", id, SDL_GetAudioDriver(id));
		}
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
 * AudioStream class. Abstract.
 * Basic audio features.
 */

class AudioStream
{
	public:
		AudioStream() = delete;
		AudioStream(const std::string_view &filename);
		AudioStream(const void *data);
		virtual ~AudioStream();

		virtual bool play() = 0;
		virtual bool stop() = 0;
};

/**
 * MusicStream class.
 * These support looping because it's what music is supposed to do.
 */

class MusicStream : public AudioStream
{
	Mix_MusicType type;
	double loopStart = 0.0;

	public:
		MusicStream() = delete;
		MusicStream(const std::string_view &filename);
		MusicStream(const void *data);
		~MusicStream();

	bool play();
	bool stop();
	bool pause();

	inline void loop()
	{
		Mix_SetMusicPosition(loopStart);
	}
};

/**
 * SoundStream class.
 * For sound effects that play, then stop. Then possibly repeat.
 */

class SoundStream : public AudioStream
{
	Mix_Chunk chunk;

	public:
		SoundStream() = delete;
		SoundStream(const std::string_view &filename);
		~SoundStream();

		bool play();
		bool stop();
};

uint8_t	init();
void	quit();

} // namespace audio

} // namespace audio

/**
 * Exported functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

const bool	LIB_FUNC_CALL coreAudioCreateSound(const char *name, const void *data);
const bool	LIB_FUNC_CALL coreAudioCreateMusic(const char *name, const void *data);
void		LIB_FUNC_CALL coreAduioDeleteSound(const char *name);
void		LIB_FUNC_CALL coreAudioDeleteMusic(const char *name);

#ifdef __cplusplus
} // extern "C"
#endif
