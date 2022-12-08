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

audio.cpp

Handles audio with SDL and SDL mixer.

*******************************************************************************/

#include <string>
#include <vector>

#include "audio.hpp"
#include "console.hpp"
#include "cvar.hpp"

namespace coreLib
{

namespace audio
{

static std::vector<const AudioDevice *> audioDevices;
static std::vector<const AudioDriver *> audioDrivers;

/**
 * CVARs.
 */

console::IntCVAR
	device, driver, // Filled in after SDL is loaded.
	numChannels(2, 1, 8, "audioChannelsCvarDesc"),
	sampleRate(48000, 24000, 48000, "audioSampleRateCvarDesc");

console::FloatCVAR
	mainVolume(0.75, 0.0, 1.0, "audioMainVolumeCvarDesc"),
	musicVolume(0.75, 0.0, 1.0, "audioMusicVolumeCvarDesc"),
	effectVolume(0.75, 0.0, 1.0, "audioEffectVolumeCvarDesc");

/**
 * Console commands.
 */

static void listDevices()
{
	for(const auto &ad : audioDevices)
		ad->describe();
}

static void listDrivers()
{
	for(const auto &ad : audioDevices)
		ad->describe();
}

/**
 * Restarts audio system.
 */

static void restart()
{
	audioDevices[device]->close();

	// Close the currently used device.
}

/**
 * AudioDevice class.
 */

// Constructor. Attempts to load an SDL audio device.
AudioDevice::AudioDevice(const int i) :
	id(i)
{}

// Destructor. Frees the device.
AudioDevice::~AudioDevice()
{}

void AudioDevice::open() const
{
	Mix_OpenAudioDevice
	(sampleRate,
		AUDIO_S16,
		2,
		2048,
		SDL_GetAudioDeviceName(id, 0),
		SDL_AUDIO_ALLOW_FORMAT_CHANGE|SDL_AUDIO_ALLOW_SAMPLES_CHANGE
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

}

/**
 * Initializes audio system(s).
 */

uint8_t init()
{
	// SDL.
	SDL_InitSubSystem(SDL_INIT_AUDIO);

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
	device = { 0, 0, numDevices - 1, "audioDeviceCvarDesc" };
	driver = { 0, 0, numDrivers - 1, "audioDriverCvarDesc" };

	console::systemCVARs.insert
	({
		{ "aud_device",			&device },
		{ "aud_driver",			&driver },
		{ "aud_effectvolume",	&effectVolume },
		{ "aud_mainvolume",		&mainVolume },
		{ "aud_musicvolume",	&musicVolume }
	});

	console::CCMDs.insert
	({
		{ "aud_listdevices", &listDevices },
		{ "aud_listdrivers", &listDrivers }
	});

	// Go ahead and list the found devices and drivers.
	listDevices();
	listDrivers();

	return 0;
}

/**
 * Shuts down audio system(s).
 */

void quit()
{
	for(auto &ad : audioDevices)
		delete ad;

	for(auto &ad : audioDrivers)
		delete ad;
}

} // namespace audio

} // namespace coreLib
