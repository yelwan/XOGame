#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : isLoaded(false) {}

SoundPlayer::~SoundPlayer() {
    UnloadSoundIfNeeded();
}

void SoundPlayer::PlaySoundToPlay(const char* filePath) {
    UnloadSoundIfNeeded();

    sound = LoadSound(filePath);
    isLoaded = true;
    SetMasterVolume(1.0f);
    PlaySound(sound);

}

void SoundPlayer::UnloadSoundIfNeeded() {
    if (isLoaded) {
        UnloadSound(sound);
        isLoaded = false;
    }
}

bool SoundPlayer::IsSoundUnloaded() const {
    return !isLoaded;
}