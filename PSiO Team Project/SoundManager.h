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
	ResourceManager *resources;

public:
	SoundManager(ResourceManager* r);
	~SoundManager();

	void playSound(std::string soundName);

	void setMuted(bool muted);

};
