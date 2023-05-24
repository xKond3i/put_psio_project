#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <map>

class ResourceManager
{
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

public:
	ResourceManager();
	~ResourceManager();

	bool loadTexture(std::string path);

	sf::Texture* getTexture(std::string path);
};
