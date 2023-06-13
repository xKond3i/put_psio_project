#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <string>
#include <map>
#include <algorithm>

class ResourceManager
{
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
	// [TO DO] Add Font support

public:
	ResourceManager();
	~ResourceManager();

	bool loadTexture(std::string name, std::string path, bool repeated=false);
	bool loadSound(std::string name, std::string path);

	sf::Texture* getTexture(std::string name);
	sf::SoundBuffer* getSound(std::string name);
};
