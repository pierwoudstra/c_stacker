// #include "miniaudio/miniaudio.h"

#include "miniaudio/miniaudio.c"
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

typedef struct audio_data {
    ma_result result;
    ma_engine engine;
    ma_sound sound;
} audio_data;

audio_data* init_audio() {
    audio_data* data = malloc(sizeof(audio_data));
    if (!data) return NULL;

    ma_result result = ma_engine_init(NULL, &data->engine);
    if (result != MA_SUCCESS) {
        printf("failed to initialize engine\n");
        free(data);
        return NULL;
    }

    result = ma_sound_init_from_file(&data->engine, "sound.wav", 0, NULL, NULL, &data->sound);
    if (result != MA_SUCCESS) {
        ma_engine_uninit(&data->engine);
        printf("failed to load sound\n");
        free(data);
        return NULL;
    }

    data->result = result;
    return data;
}

void uninit_audio(audio_data* data) {
    ma_sound_uninit(&data->sound);
    ma_engine_uninit(&data->engine);
    free(data);
}

float midi_to_playback_speed(float midi) {

    // 0 = 1 .. 12 = 2 // 24 = 4 enz
    return pow(2.0, (midi/12.f));
}

void play_f_stack(audio_data* data, f_stack* s) {
    for (int i = (s->length-1); i >= 0; i--) {
        ma_sound_set_pitch(&data->sound, midi_to_playback_speed(view_index_f_stack(s, i)));
        ma_sound_seek_to_pcm_frame(&data->sound, 0);
        ma_sound_start(&data->sound);

        #ifdef _WIN32
        Sleep(1000);
        #else
        usleep(1000000); // 1000 ms
        #endif
    }
}
