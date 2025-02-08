#pragma once
#include "raylib.h"

class SoundPlayer {
public:
    SoundPlayer();
    ~SoundPlayer();

    void PlaySoundToPlay(const char* filePath);
    void UnloadSoundIfNeeded();
    bool IsSoundUnloaded() const;

private:
    Sound sound;
    bool isLoaded = false;
};