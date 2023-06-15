#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include "ResourceManager.h"

class SoundManager
{
private:
	// --- SOUND & MUSIC
	sf::Music music;
	sf::Music backgroundSound;

	sf::Sound effects;
	sf::Sound effectsBg;
	ResourceManager *resources;

	bool Playing = false;

	// initial volume
	static const unsigned int musicVol = 5;
	static const unsigned int bgVol = 10;

	static const unsigned int effectsVol = 15;
	static const unsigned int effectsBgVol = 15;

public:
	SoundManager(ResourceManager* r);
	~SoundManager();

	void playSound(std::string soundName, int channel);

	void setMuted(bool muted);

	bool isPlaying();

};
