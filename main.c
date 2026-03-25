#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "string_view.h"
#include "stack.h"

int main() {
    string_view c = sv("           Hello, World          ");
    sv_trim(&c); // chop off spaces
    string_view hello = sv_chop_by_delim(&c, ','); // split hello and _world
    printf("|%.*s| \n", c.size, c.data);
    printf("|%.*s| \n", hello.size, hello.data);

    // stack tests
    f_stack s = create_f_stack();
    const uint16_t size = 10;

    for (int i = 0; i < size; i++) {
        push_f(&s, (float)i);
    }

    printf("the length is: %u \n", s.length);

    for (int i = 0; i < size; i++) {
        printf("%u \n", s.length);
        // pop_f(&s);
        printf("%f \n", pop_f(&s));
    }

    clear_f_stack(&s);
}
