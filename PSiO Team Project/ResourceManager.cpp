#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    textures.clear();
}

bool ResourceManager::loadTexture(std::string path)
{
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(path)) {
        throw std::runtime_error("[!] failed to load texture... [" + path + "]");
        return false;
    }
    textures[path] = texture;
    return true;
}

sf::Texture* ResourceManager::getTexture(std::string path)
{
    auto pos = textures.find(path);
    if (pos != textures.end()) {
        return pos->second.get();
    }
    return nullptr;
}
