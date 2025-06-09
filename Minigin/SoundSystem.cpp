#include "SoundSystem.h"
#include "Audio.h"
#include <SDL_mixer.h>
#include <iostream>
#include <SDL.h>


SoundSystem::SoundSystem() {
	spec.freq = MIX_DEFAULT_FREQUENCY;
	spec.format = MIX_DEFAULT_FORMAT;
	spec.channels = MIX_DEFAULT_CHANNELS;
	spec.samples = 4096; // Default buffer size
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return;
	}
	else {
		std::cerr << "SDL audio initialized successfully." << std::endl;
	}
	Mix_QuerySpec(&spec.freq, &spec.format, &spec.channels);
}

void SoundSystem::PlaySound(int soundID)
{
	
	 // Initialize audio with default settings
	soundID; // Suppress unused parameter warning
	return;
}

void SoundSystem::StopSound(int soundID)
{
	soundID; // Suppress unused parameter warning
	return;
}

void SoundSystem::SetVolume(int volume)
{
	m_Volume = volume;
}

int SoundSystem::GetVolume()
{
	return m_Volume;
}
