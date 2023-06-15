#include "SoundManager.h"

SoundManager::SoundManager(ResourceManager* r)
{
    resources = r;

    // --- music
    music.openFromFile("./resources/music/background_music.ogg");
    music.setLoop(true);
    music.setVolume(10);
    music.play();

    backgroundSound.openFromFile("./resources/music/crickets_background_noises.wav");
    backgroundSound.setLoop(true);
    backgroundSound.play();
    backgroundSound.setVolume(25);

    effects.setVolume(5);

}

SoundManager::~SoundManager()
{
    
}

void SoundManager::playSound(std::string soundName)
{
    effects.setBuffer(*resources->getSound(soundName));
    effects.play();
    Playing = true;
}

void SoundManager::setMuted(bool muted)
{
    if (muted) {
        music.setVolume(0);
        backgroundSound.setVolume(0);
        effects.setVolume(0);
    }
    else {
        music.setVolume(10);
        backgroundSound.setVolume(25);
        effects.setVolume(5);
    }
}

bool SoundManager::isPlaying()
{
    return Playing;
}
