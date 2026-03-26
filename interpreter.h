
void interpret_cmd(f_stack* s, string_view cmd) {
    // convert to float and push to stack
    push_f(s, strtof(cmd.data, NULL)); 

}
