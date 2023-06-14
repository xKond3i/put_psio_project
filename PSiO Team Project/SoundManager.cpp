#include "SoundManager.h"

SoundManager::SoundManager(ResourceManager* r)
{
    // --- music
    music.openFromFile("./resources/music/background_music.ogg");
    music.setLoop(true);
    music.setVolume(10);
    music.play();

    backgroundSound.openFromFile("./resources/music/crickets_background_noises.wav");
    backgroundSound.setLoop(true);
    backgroundSound.play();
    backgroundSound.setVolume(25);

    resources = r;
   

}

SoundManager::~SoundManager()
{
    
}

void SoundManager::playSound(std::string soundName)
{
    effects.setBuffer(*resources->getSound(soundName));
    effects.setVolume(5);
    effects.play();
}
