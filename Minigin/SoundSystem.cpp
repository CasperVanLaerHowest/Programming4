#include "SoundSystem.h"
#include "Audio.h"
#include <SDL_mixer.h>
#include <iostream>
#include <SDL.h>


SoundSystem::SoundSystem() {
	spec.freq = MIX_DEFAULT_FREQUENCY;
	spec.format = MIX_DEFAULT_FORMAT;
	spec.channels = MIX_DEFAULT_CHANNELS;
	//spec.samples = 4096; // Default buffer size
	
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
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
