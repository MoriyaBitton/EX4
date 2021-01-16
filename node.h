#pragma once

#define NUM_LETTERS ((int)26)

typedef struct node {
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
} node;

char* append_to_string(char *string, char suffix);
void remove_last_char(char *string);
char* print_lexicographic(node *n, char *string);
char* print_reversed_lexicographic(node *n, char *string);
void print(int reversed, node *root);
int to_lower(char letter);
int char_to_index(char letter);
int add_word(node *root, char *string);
void free_all_tree(node *root);
char* get_word(int *eof);
int receive_input(node *root);
