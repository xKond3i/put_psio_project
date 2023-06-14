#include "SoundManager.h"

SoundManager::SoundManager()
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
}

SoundManager::~SoundManager()
{

}
