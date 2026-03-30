typedef struct string_view {
    const char* data;
    uint16_t size;
} string_view;

string_view sv(const char* cstr) {
    return (string_view) {
        .data = cstr,
        .size = strlen(cstr),
    };
}

void sv_chop_left(string_view* sv, uint16_t n) {
    if (n > sv->size) n = sv->size;   
    sv->size -= n;
    sv->data += n;
}

void sv_chop_right(string_view* sv, uint16_t n) {
    if (n > sv->size) n = sv->size;
    sv->size -= n;
}

void sv_trim_left(string_view* sv) {
    while (sv->size > 0 && isspace(sv->data[0])) {
        sv_chop_left(sv, 1);
    }
}

void sv_trim_right(string_view* sv) {
    while (sv->size > 0 && isspace(sv->data[sv->size-1])) {
        sv_chop_right(sv, 1);
    }
}

void sv_trim(string_view* sv) {
    sv_trim_left(sv);
    sv_trim_right(sv);
}

string_view sv_chop_by_delim(string_view* sv, char delim) {
    // returns part up until delimiter
    uint16_t i = 0;
    while (i < sv->size && sv->data[i] != delim) {
        i += 1;
    }

    // case if there is a delimiter
    if (i < sv->size) {
        string_view result = {
            .data = sv->data,
            .size = i,
        };
        sv_chop_left(sv, i + 1);
        return result;
    }
    
    // the case if there is no delimiter
    string_view result = *sv;
    sv_chop_left(sv, sv->size);
    return result;
}

bool sv_compare(string_view input, string_view compare) {
    if (&input == NULL || &compare == NULL) return false;
    bool flag = true;
    if (input.size != compare.size) return false;
    for (int i = 0; i < input.size; i++) {
        if (input.data[i] != compare.data[i]) {
            flag = false;
        } 
    }
    return flag;
}
