#include "SoundManager.h"

SoundManager::SoundManager()
{
    // --- music
    music.openFromFile("./resources/music/background_music.ogg");
    music.setLoop(true);
    music.setVolume(5);
    music.play();

    backgroundSound.openFromFile("./resources/music/crickets_background_noises.wav");
    backgroundSound.setLoop(true);
    backgroundSound.play();
    backgroundSound.setVolume(5);
}

SoundManager::~SoundManager()
{

}
