#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    textures.clear();
}



bool ResourceManager::loadTexture(std::string name, std::string path, bool repeated)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(path)) {
        throw std::runtime_error("[!] failed to load texture... [" + path + "]");
        return false;
    }
    if (textures.count(name) > 0) {
        throw std::runtime_error("[!] overriding texture... [" + name + "]");
        return false;
    }
    texture->setRepeated(repeated);
    textures[name] = texture;
    return true;
}

bool ResourceManager::loadSound(std::string name, std::string path)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    std::shared_ptr<sf::SoundBuffer> sound = std::make_shared<sf::SoundBuffer>();
    if (!sound->loadFromFile(path)) {
        throw std::runtime_error("[!] failed to load sound... [" + path + "]");
        return false;
    }
    if (sounds.count(name) > 0) {
        throw std::runtime_error("[!] overriding sound... [" + name + "]");
        return false;
    }
    sounds[name] = sound;
    return true;
}

bool ResourceManager::loadFont(std::string name, std::string path)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    if (!font->loadFromFile(path)) {
        throw std::runtime_error("[!] failed to load font... [" + path + "]");
        return false;
    }
    if (fonts.count(name) > 0) {
        throw std::runtime_error("[!] overriding font... [" + name + "]");
        return false;
    }
    fonts[name] = font;
    return true;
}




sf::Texture* ResourceManager::getTexture(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    auto pos = textures.find(name);
    if (pos != textures.end()) {
        return pos->second.get();
    }
    return nullptr;
}

sf::SoundBuffer* ResourceManager::getSound(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    auto pos = sounds.find(name);
    if (pos != sounds.end()) {
        return pos->second.get();
    }
    return nullptr;
}

sf::Font* ResourceManager::getFont(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    auto pos = fonts.find(name);
    if (pos != fonts.end()) {
        return pos->second.get();
    }
    return nullptr;
}
