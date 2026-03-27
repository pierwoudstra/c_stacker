#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "string_view.h"
#include "stack.h"
#include "sound.h"
#include "interpreter.h"

int main() {
    string_view message = sv("an empty stack just 4 u");
    printf("|%.*s| \n", message.size, message.data);
   
    f_stack s = create_f_stack();
    audio_data* a = init_audio();
    
    string_view quit = sv("q");

    for (int i = 0; i < 10; i++) {
        printf("\e[1;1H\e[2J"); // flush
        print_f_stack(&s);
        play_f_stack(a, &s);

        char input[1024];
        printf("> ");
        fgets(input, sizeof(input), stdin);

        string_view sv_input = sv(input);
        while (sv_input.size > 0) {
            sv_trim(&sv_input);
            string_view first_string = sv_chop_by_delim(&sv_input, ' ');
            if (sv_compare(&first_string, &quit)) {
                return 0;
            } else {
                interpret_cmd(&s, first_string);
            }
        }
        
    }
    
    uninit_audio(a);
    clear_f_stack(&s);
    return 0;
}
