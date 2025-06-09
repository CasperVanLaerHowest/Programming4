#pragma once
class Audio {
public:
	virtual ~Audio() = default;
	virtual void PlaySound(int soundID) = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void SetVolume(int volume) = 0;
	virtual int GetVolume() = 0;
private:
	int m_Volume{ 100 }; // Default volume set to 100%
};