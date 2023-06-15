#include "SoundManager.h"

SoundManager::SoundManager(ResourceManager* r)
{
    resources = r;

    // --- music
    music.openFromFile("./resources/music/background_music.ogg");
    music.setLoop(true);
    music.setVolume(musicVol);
    music.play();

    backgroundSound.openFromFile("./resources/music/crickets_background_noises.wav");
    backgroundSound.setLoop(true);
    backgroundSound.play();
    backgroundSound.setVolume(bgVol);

    effects.setVolume(effectsVol);
    effectsBg.setVolume(effectsBgVol);

}

SoundManager::~SoundManager()
{
    
}

void SoundManager::playSound(std::string soundName, int channel)
{
    switch(channel) {
    case 1:
        effects.setBuffer(*resources->getSound(soundName));
        effects.play();
        break;
    case 2:
        effectsBg.setBuffer(*resources->getSound(soundName));
        effectsBg.play();
        effectsBg.setLoop(true);
        break;
    }

    Playing = true;
}

void SoundManager::setMuted(bool muted)
{
    if (muted) {
        music.setVolume(0);
        backgroundSound.setVolume(0);
        effects.setVolume(0);
        effectsBg.setVolume(0);
    }
    else {
        music.setVolume(musicVol);
        backgroundSound.setVolume(bgVol);

        effects.setVolume(effectsVol);
        effectsBg.setVolume(effectsBgVol);
    }
}

bool SoundManager::isPlaying()
{
    return Playing;
}
