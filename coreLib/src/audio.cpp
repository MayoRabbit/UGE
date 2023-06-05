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

audio.cpp

Audio system. Uses SDL and SDL mixer. Supported formats include WAV, FLAC, and
OGG. Other formats might be supported later. Don't quote me on it, though.

*******************************************************************************/

#include <vector>
#include <SDL2/SDL.h>
#include "audio.hpp"
#include "console.hpp"

namespace coreLib
{

namespace audio
{

// Devices and drivers.
static std::vector<const AudioDevice *> audioDevices;
static std::vector<const AudioDriver *> audioDrivers;

// Sound and music streams.
static std::map<std::string, SoundStream *> soundStreams;
static std::map<std::string, MusicStream *> musicStreams;

/**
 * CVARs.
 */

static console::IntCVAR
	audioDevice, audioDriver, // Filled in after SDL is loaded.
	numChannels	(2, 1, 8, "audioChannelsCvarDesc"),
	sampleRate	(48000, 24000, 48000, "audioSampleRateCvarDesc");

static console::FloatCVAR
	mainVolume	(0.75, 0.0, 1.0, "audioMainVolumeCvarDesc"),
	musicVolume	(0.75, 0.0, 1.0, "audioMusicVolumeCvarDesc"),
	effectVolume(0.75, 0.0, 1.0, "audioEffectVolumeCvarDesc");

/**
 * Console commands.
 */

static void listDevices()
{
	printf("SDL Audio Devices Detected:\n");

	for(const auto &ad : audioDevices)
		ad->describe();
}

static void listDrivers()
{
	printf("SDL Audio Drivers Detected:\n");

	for(const auto &ad : audioDrivers)
		ad->describe();
}

static void restart()
{

}

/**
 * AudioDevice class.
 */

// Constructor. Attempts to collect information about an SDL audio device.
// This does not open the device, as only one device can be open at any time,
// that must be done with the open() function.
AudioDevice::AudioDevice(const int i) :
	id(i)
{

}

// Destructor. Frees the device.
AudioDevice::~AudioDevice()
{
	Mix_CloseAudio();
}

// Attempts to open the device using the settings stored in the relevant
// CVARs. If it can't allow conversion, and set the CVARs to the values
// that were chosen. Log these events so the user knows.
void AudioDevice::open() const
{
	int allocatedChannels = Mix_AllocateChannels(numChannels);
	if(allocatedChannels != numChannels)
	{

	}

	// Get the
	Mix_OpenAudioDevice
	(
		sampleRate,
		AUDIO_S16,
		2,
		2048,
		SDL_GetAudioDeviceName(id, 0),
		SDL_AUDIO_ALLOW_FORMAT_CHANGE | SDL_AUDIO_ALLOW_SAMPLES_CHANGE
	);
}

/**
 * AudioDriver class.
 */

AudioDriver::AudioDriver(const int i) :
	id(i)
{

}

AudioDriver::~AudioDriver()
{
	if(id == currentID);
}

/**
 * Initializes audio system(s).
 */

uint8_t init()
{
	// SDL.
	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{

	}

	// SDL mixer.
	int flags = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG);

	// SDL mixer init failed!
	if(!flags)
	{

	}

	// No FLAC support!
	if(!(flags & MIX_INIT_FLAC))
	{

	}

	// No OGG support!
	if(!(flags & MIX_INIT_OGG))
	{

	}

	int
		numDevices = SDL_GetNumAudioDevices(0),
		numDrivers = SDL_GetNumAudioDrivers();

	audioDevices.resize(numDevices);
	audioDrivers.resize(numDrivers);

	for(int i = 0; i < numDevices; i++)
		audioDevices[i] = new const AudioDevice(i);

	for(int i = 0; i < numDrivers; i++)
		audioDrivers[i] = new const AudioDriver(i);

	// CVARs.
	audioDevice = { 0, 0, numDevices - 1, "audioDeviceCvarDesc" };
	audioDriver = { 0, 0, numDrivers - 1, "audioDriverCvarDesc" };

	console::systemCVARs.insert
	(
		{
			{ "aud_device",			&audioDevice },
			{ "aud_driver",			&audioDriver },
			{ "aud_effectvolume",	&effectVolume },
			{ "aud_mainvolume",		&mainVolume },
			{ "aud_musicvolume",	&musicVolume }
		}
	);

	console::CCMDs.insert
	(
		{
			{ "aud_listdevices",	listDevices },
			{ "aud_listdrivers",	listDrivers },
			{ "aud_restart",		restart }
		}
	);

	// Go ahead and list the found devices and drivers.
	listDevices();
	listDrivers();

	return 0;
}

/**
 * Shuts down audio system.
 */

void quit()
{
	// Delete devices and drivers.
	for(auto ad : audioDevices)
		delete ad;

	for(auto ad : audioDrivers)
		delete ad;
}

} // namespace audio

} // namespace coreLib

/**
 * Exported functions.
 */

#ifdef __cplusplus
extern "C"
{
#endif

const bool	LIB_FUNC_CALL coreAudioCreateSound(const char *name, const void *data)


const bool	LIB_FUNC_CALL coreAudioCreateMusic(const char *name, const void *data)


void		LIB_FUNC_CALL coreAduioDeleteSound(const char *name)


void		LIB_FUNC_CALL coreAudioDeleteMusic(const char *name)



#ifdef __cplusplus
} // extern "C"
#endif

