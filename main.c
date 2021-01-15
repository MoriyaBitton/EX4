#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

// argc = count of the argumets 
// argv = the arguments
//
// ./frequency r
// argc = 2
// argv = {"./frequency", "r"}
int main(int argc, char **argv){
	
	// (void *) - general pointer
	// (void **) - general arr(pointer) of pointers
	
	int reversed = 1;
	if(argc == 2){
		if(argv[1][0] == 'r' && argv[1][1] == 0){
           		reversed = 1;
		}else{
         		printf("Usage: %s [r]\n", argv[0]);
         		return 1;
       	}
	}else if (argc == 1){
		reversed = 0;
	}else{
		printf("Usage: %s or %s r\n", argv[0], argv[0]);
		return 1; // error message
	}

	node *root;
	if(!(root = (node *)calloc(1, sizeof(node)))){ // calloc return pointer
		printf("error\n");
	} 
	if(receive_input(root)){ // 1 = true
		print(reversed, root);
	}
	
	free_all_tree(root);
    return 0;
}
