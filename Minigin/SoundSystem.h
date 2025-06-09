#pragma once
#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>
class SoundSystem :
    public Audio
{
public:
	SoundSystem();
	~SoundSystem() override = default;
	void PlaySound(int soundID) override;
	void StopSound(int soundID) override;
	void SetVolume(int volume) override;
	int GetVolume() override;
private:
	int m_Volume{ 100 }; // Default volume set to 100%
	SDL_AudioSpec spec{};
};

