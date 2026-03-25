#include "miniaudio/miniaudio.h"
#include <stdio.h>
#include <stdlib.h>


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "stack.h"

int main()
{

    f_stack s = create_f_stack();
    push_f(&s, 1.2);
    push_f(&s, 1.1);
    push_f(&s, 1.7);
    push_f(&s, 0.9);

    ma_result result;
    ma_engine engine;
    ma_sound sound;

    
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return -1;
    }

    result = ma_sound_init_from_file(&engine, "sound.wav", 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        ma_engine_uninit(&engine);
        return -1;
    }

    for (int i = 0; i < s.length; i++) {
        ma_sound_set_pitch(&sound, view_index_f_stack(&s, i));
        ma_sound_seek_to_pcm_frame(&sound, 0);
        ma_sound_start(&sound);

        #ifdef _WIN32
        Sleep(1000);
        #else
        usleep(1000000); // 10 ms
        #endif
    }

    ma_sound_uninit(&sound); 
    ma_engine_uninit(&engine);

    return 0;
}
