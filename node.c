#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

// Given a node, print in lexicographic order the words and amounts
char* append_to_string(char *string, char suffix){

	int i = strlen(string);
	char *bigger_string;
	if(!(bigger_string = (char *)realloc(string, i+2))){
    		// if realloc failed
    		printf("error\n");
    		return NULL;
	}
	bigger_string[i] = suffix;
	bigger_string[i + 1] = 0;
	return bigger_string;
}

void remove_last_char(char *string){

	int i = strlen(string);
	if(i == 0){
		return;
	}
	string[i - 1] = 0;
}

// return char* because we get pointer and maybe channged him so we will return the new one 
char* print_lexicographic(node *n, char *string){

	if(n == NULL){
		return string;
	}
	// handle stop condition
	if(n->letter){ //n->letter !=0
		string = append_to_string(string, n->letter);
		if(string == NULL){
			return NULL;
		}
		if(n->count > 0){
			printf("%s %ld\n", string, n->count);
		}
	}    
	for(int i = 0; i < NUM_LETTERS; i++){
		if(n->children[i] != NULL){
			// recursion call
			string = print_lexicographic(n->children[i], string);
			if(string == NULL){
				return NULL;
			}
		}
	}
	remove_last_char(string);
	return string;
}

// return char* because we get pointer and maybe channged him so we will return the new one 
char* print_reversed_lexicographic(node *n, char *string){

	if(n == NULL){
		return string;
	}
	// handle stop condition
	if(n->letter){ // n->letter !=0
		string = append_to_string(string, n->letter);
		if(string == NULL){
			return NULL;
		}
	}
    
	for(int i = NUM_LETTERS - 1; i >= 0; i--){
		if(n->children[i] != NULL){
			// recursion call
			string = print_reversed_lexicographic(n->children[i], string);
			if(string == NULL){
				return NULL;
			}
		}
	}
	if(n->count > 0 && n->letter){
		printf("%s %ld\n", string, n->count);
	}
    
	remove_last_char(string);
	return string;
}

// Given a root, print the whole tree, lexicographic or reversed
void print(int reversed, node *root){

	char *string;
	if(!(string = (char *)malloc(1))){
		printf("error\n");
		free_all_tree(root); // free memorys
		exit(1);
	}
	string[0] = 0;
	if(reversed){	
		string = print_reversed_lexicographic(root, string);
	}else{
        	string = print_lexicographic(root, string);
        }
        if(string){ // string != null
        	free(string); // Delete all used memory
        }
}

// Return a small letter by a capital letter or a small letter 
// if the given char isn't a letter it return's the letter 
int to_lower(char letter){

	if(letter >= 'a' && letter <= 'z'){
		//printf("to lower small letter %d\n", letter);
		return letter;
	}else if(letter >= 'A' && letter <= 'Z'){
		//printf("to lower capital letter %d\n", letter + ('a' - 'A'));
		return letter + ('a' - 'A');
	}else{
		return letter; 
	}
}

// Return Index (by ASCII) by a given char
int char_to_index(char letter){

	//printf("char to index %d\n", to_lower(letter) - 'a');
	return to_lower(letter) - 'a'; 
}

// Returns 0 mean failure
int add_word(node *root, char *string){

	if(strlen(string) == 0){
		root->count++;
	}else {
		int i = char_to_index(string[0]);
		if(!root->children[i]){// == 0 ; The root does not have this "child"
			if(!(root->children[i] = (node *)calloc(1, sizeof(node)))){
				// We use calloc (insted of malloc) so that all members are equal to zero 
				printf("error\n");
				return 0;
			}
		}
		//printf("add word %d\n", to_lower(string[0])); 
		root->children[i]->letter = to_lower(string[0]); 
		return add_word(root->children[i], string + 1); // change the pointer from char '0' in string to '1'
	}
	return 1;
}

void free_all_tree(node *root){

	for(int i = 0; i < NUM_LETTERS; i++){
		if(root->children[i]){ // != null
			free_all_tree(root->children[i]);
		}
	}
	
	free(root); // free get pointer
}

// dinamic get word
char* get_word(int *eof){

	char *word;
	if(!(word = (char *)calloc(1, sizeof(char)))){ // calloc return pointer
		printf("error\n");
		return word; // word = null 
	}

	while(1){
		char input = getchar();
		if(input == EOF){
			*eof = 1;
			return word;
		}else if(input == '\n' || input == ' ' || input == '\t' || input == '\r'){ // separate between words
			return word;
		}else if((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z')){ // to cover all ASCII table
			word = append_to_string(word, input);
		}
	}
	
	printf("we shouldn't get here\n");
	return word;
}

// Given a node, print in lexicographic order the words and amounts
int receive_input(node *root){
	
	int eof = 0;
	int success = 1;
	while(!eof && success){
		char* word = get_word(&eof);
		if(word == NULL){
			return 0;
		}
		if(strlen(word) != 0){
			if(!add_word(root, word)){
				free_all_tree(root);
				success = 0; 
			}
		}
		free(word);
	}
	return success;
}
