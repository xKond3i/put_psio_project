#pragma once

#include <SFML/Audio.hpp>

class SoundManager
{
private:
	// --- SOUND & MUSIC
	sf::Music music;
	sf::Music backgroundSound;

public:
	SoundManager();
	~SoundManager();

};
