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
	sf::Sound effects2;
	ResourceManager *resources;

	bool Playing = false;

public:
	SoundManager(ResourceManager* r);
	~SoundManager();

	void playSound(std::string soundName, int canal);

	void setMuted(bool muted);

	bool isPlaying();

};
