#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "string_view.h"
#include "stack.h"

int main() {
    string_view c = sv("an empty stack just 4 u \n");
    sv_trim(&c); // chop off spaces
    printf("|%.*s| \n", c.size, c.data);
   
    f_stack s = create_f_stack();

    for (int i = 0; i < 10; i++) {
        char input[1024];
        printf("> ");
        fgets(input, sizeof(input), stdin);

        string_view sv_input = sv(input);
        while (sv_input.size > 0) {
            sv_trim(&sv_input);
            string_view first_string = sv_chop_by_delim(&sv_input, ' ');
            if (*first_string.data == 'q') {
                return 0;
            } else {
                // convert to float and push to stack
                push_f(&s, strtof(first_string.data, NULL));
            }
        }
        print_f_stack(&s);
    }
    
    clear_f_stack(&s);
    return 0;
}
