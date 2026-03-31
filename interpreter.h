
void interpret_cmd(f_stack* s, string_view cmd) {
    if (sv_compare(cmd, sv("pop"))) {
        pop_f(s);
    } else {
        // convert to float and push to stack
        push_f(s, strtof(cmd.data, NULL));
    }
}
