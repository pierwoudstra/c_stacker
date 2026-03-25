// TODO implement different types of nodes (char and string?) (stack can stay the same (only change the name) )

typedef struct f_node {
    float value;
    struct f_node* next_node;
} f_node;

typedef struct {
    uint16_t length;
    struct f_node* top_node;
} f_stack;

f_stack create_f_stack() {
    f_stack empty_f_stack = {0, NULL};
    return empty_f_stack;
}

void push_f(f_stack* stack_ptr, float value) {
    if (stack_ptr == NULL) return;
    f_node* new_node = malloc(sizeof(f_node)); // allocate mem
    new_node->value = value; // assign value
    if (stack_ptr->top_node != NULL) {
        // if this new node is not the first node
        // then set (ex-)first node as next node
        new_node->next_node = stack_ptr->top_node;
    } else {
        // this means it is the first node
        // meaning it points to nothing
        new_node->next_node = NULL;
    }
    stack_ptr->top_node = new_node;
    stack_ptr->length++;
}

float pop_f(f_stack* stack_ptr) {
    if (stack_ptr == NULL) return 0.f;
    f_node* node_to_be_removed = stack_ptr->top_node;
    float value = node_to_be_removed->value;
    f_node* new_top_node = node_to_be_removed->next_node;
    stack_ptr->top_node = new_top_node;
    stack_ptr->length--;
    free(node_to_be_removed);

    return value;
}

void clear_f_stack(f_stack* stack_ptr) {
    if (stack_ptr == NULL) return;
    while (stack_ptr->top_node != NULL) {
        (void)pop_f(stack_ptr);
    }
}
