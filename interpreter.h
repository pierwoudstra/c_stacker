
void interpret_cmd(f_stack* s, string_view cmd) {
    if (sv_compare(cmd, sv("drop"))) {
        pop_f(s);

    // arithmetic
    } else if (sv_compare(cmd, sv("+"))) {
        if (s->length >= 2) {
            float right = pop_f(s);
            float left = pop_f(s);
            push_f(s, (left + right));
        }
    } else if (sv_compare(cmd, sv("-"))) {
        if (s->length >= 2) {
            float right = pop_f(s);
            float left = pop_f(s);
            push_f(s, (left - right));
        } 
    } else if (sv_compare(cmd, sv("*"))) {
        if (s->length >= 2) {
            float right = pop_f(s);
            float left = pop_f(s);
            push_f(s, (left * right));
        } 
    } else if (sv_compare(cmd, sv("/"))) {
        if (s->length >= 2) {
            float right = pop_f(s);
            float left = pop_f(s);
            push_f(s, (left / right));
        }
    // basic stack functions
    } else if (sv_compare(cmd, sv("swap"))) {
        if (s->length >= 2) {
            float n1 = pop_f(s);
            float n2 = pop_f(s);
            push_f(s, n1);
            push_f(s, n2);
        }

   } else if (sv_compare(cmd, sv("dup"))) {
        if (s->length >= 1) {
            float n1 = pop_f(s);
            push_f(s, n1);
            push_f(s, n1);
        }

   } else if (sv_compare(cmd, sv("over"))) {
        if (s->length >= 2) {
            float n1 = pop_f(s);
            float n2 = pop_f(s);
            push_f(s, n2);
            push_f(s, n1);
            push_f(s, n2);
        }

   } else if (sv_compare(cmd, sv("rot"))) {
        if (s->length >= 3) {
            float n1 = pop_f(s);
            float n2 = pop_f(s);
            float n3 = pop_f(s);
            push_f(s, n2);
            push_f(s, n1);
            push_f(s, n3);
        }
    } else {
        // convert to float and push to stack
        push_f(s, strtof(cmd.data, NULL));
    }
}
