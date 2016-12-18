//#define Version "1.14"

// Uncomment the line below if you are compiling on Windows.

/*#include <stdio.h>
#include <stdlib.h>
#include "Header.h"*/
//#include <stdbool.h>



// Default order is 4.
//#define DEFAULT_ORDER 5

// Minimum order is necessarily 3.  We set the maximum
// order arbitrarily.  You may change the maximum order.


// Constants for printing part or all of the GPL license.
/*#define LICENSE_FILE "LICENSE.txt"
#define LICENSE_WARRANTEE 0
#define LICENSE_CONDITIONS 1*/

// TYPES.
// GLOBALS.
// FUNCTION PROTOTYPES.
// Output and utility.

//void license_notice( void );
//void print_license( int licence_part );
/*void usage_1( void );
void usage_2( void );
void usage_3( void );*/

//int height( node * root );
//
//void print_leaves( node * root );

//void find_and_print(node * root, int key, bool verbose); 
//void find_and_print_range(node * root, int range1, int range2, bool verbose); 
//int find_range( node * root, int key_start, int key_end, bool verbose,
		//int returned_keys[], void * returned_pointers[]); 
//
//
//int cut( int length );

// Insertion.
// Deletion.
// FUNCTION DEFINITIONS.
// OUTPUT AND UTILITIES

/* Copyright and license notice to user at startup. 
 */
/*void license_notice( void ) {
	printf("bpt version %s -- Copyright (C) 2010  Amittai Aviram "
			"http://www.amittai.com\n", Version);
	printf("This program comes with ABSOLUTELY NO WARRANTY; for details "
			"type `show w'.\n"
			"This is free software, and you are welcome to redistribute it\n"
			"under certain conditions; type `show c' for details.\n\n");
}*/


/* Routine to print portion of GPL license to stdout.
 */
/*void print_license( int license_part ) {
	int start, end, line;
	FILE * fp;
	char buffer[0x100];

	switch(license_part) {
	case LICENSE_WARRANTEE:
		start = LICENSE_WARRANTEE_START;
		end = LICENSE_WARRANTEE_END;
		break;
	case LICENSE_CONDITIONS:
		start = LICENSE_CONDITIONS_START;
		end = LICENSE_CONDITIONS_END;
		break;
	default:
		return;
	}

	fp = fopen(LICENSE_FILE, "r");
	if (fp == NULL) {
		perror("print_license: fopen");
		exit(EXIT_FAILURE);
	}
	for (line = 0; line < start; line++)
		fgets(buffer, sizeof(buffer), fp);
	for ( ; line < end; line++) {
		fgets(buffer, sizeof(buffer), fp);
		printf("%s", buffer);
	}
	fclose(fp);
}*/


/* First message to the user.
 */
/*void usage_1( void ) {
	printf("B+ Tree of Order %d.\n", order);
    printf("Following Silberschatz, Korth, Sidarshan, Database Concepts, "
           "5th ed.\n\n"
           "To build a B+ tree of a different order, start again and enter "
           "the order\n"
           "as an integer argument:  bpt <order>  ");
	printf("(%d <= order <= %d).\n", MIN_ORDER, MAX_ORDER);
    printf("To start with input from a file of newline-delimited integers, \n"
           "start again and enter the order followed by the filename:\n"
           "bpt <order> <inputfile> .\n");
}*/


/* Second message to the user.
 */
/*void usage_2( void ) {
	printf("Enter any of the following commands after the prompt > :\n"
	"\ti <k>  -- Insert <k> (an integer) as both key and value).\n"
	"\tf <k>  -- Find the value under key <k>.\n"
	"\tp <k> -- Print the path from the root to key k and its associated "
           "value.\n"
	"\tr <k1> <k2> -- Print the keys and values found in the range "
			"[<k1>, <k2>\n"
	"\td <k>  -- Delete key <k> and its associated value.\n"
	"\tx -- Destroy the whole tree.  Start again with an empty tree of the "
           "same order.\n"
	"\tt -- Print the B+ tree.\n"
	"\tl -- Print the keys of the leaves (bottom row of the tree).\n"
	"\tv -- Toggle output of pointer addresses (\"verbose\") in tree and "
           "leaves.\n"
	"\tq -- Quit. (Or use Ctl-D.)\n"
	"\t? -- Print this help message.\n");
}*/


/* Brief usage note.
 */
/*void usage_3( void ) {
	printf("Usage: ./bpt [<order>]\n");
	printf("\twhere %d <= order <= %d .\n", MIN_ORDER, MAX_ORDER);
}*/


/* Helper function for printing the
 * tree out.  See print_tree.
 */



/* Helper function for printing the
 * tree out.  See print_tree.
 */



/* Prints the bottom row of keys
 * of the tree (with their respective
 * pointers, if the verbose_output flag is set.
 */
/*void print_leaves( node * root ) {
	int i;
	node * c = root;
	if (root == NULL) {
		printf("Empty tree.\n");
		return;
	}
	while (!c->is_leaf)
		c = c->pointers[0];
	while (true) {
		for (i = 0; i < c->num_keys; i++) {
			if (verbose_output)
				printf("%lx ", (unsigned long)c->pointers[i]);
			printf("%d ", c->keys[i]);
		}
		if (verbose_output)
			printf("%lx ", (unsigned long)c->pointers[order - 1]);
		if (c->pointers[order - 1] != NULL) {
			printf(" | ");
			c = c->pointers[order - 1];
		}
		else
			break;
	}
	printf("\n");
}*/


/* Utility function to give the height
 * of the tree, which length in number of edges
 * of the path from the root to any leaf.
 */
/*int height( node * root ) {
	int h = 0;
	node * c = root;
	while (!c->is_leaf) {
		c = c->pointers[0];
		h++;
	}
	return h;
}*/





/* Prints the B+ tree in the command
 * line in level (rank) order, with the 
 * keys in each node and the '|' symbol
 * to separate nodes.
 * With the verbose_output flag set.
 * the values of the pointers corresponding
 * to the keys also appear next to their respective
 * keys, in hexadecimal notation.
 */



/* Finds the record under a given key and prints an
 * appropriate message to stdout.
 */
/*void find_and_print(node * root, int key, bool verbose) {
	record * r = find(root, key, verbose);
	if (r == NULL)
		printf("Record not found under key %d.\n", key);
	else 
		printf("Record at %lx -- key %d, value %d.\n",
				(unsigned long)r, key, r->value);
}*/


/* Finds and prints the keys, pointers, and values within a range
 * of keys between key_start and key_end, including both bounds.
 */
/*void find_and_print_range( node * root, int key_start, int key_end,
		bool verbose) {
	int i;
	int array_size = key_end - key_start + 1;
	int *returned_keys;
	returned_keys = malloc(array_size * sizeof(int));
	void ** returned_pointers;
	* returned_pointers = malloc(array_size * sizeof(int));
	int num_found = find_range( root, key_start, key_end, verbose,
			returned_keys, returned_pointers );
	if (!num_found)
		printf("None found.\n");
	else {
		for (i = 0; i < num_found; i++)
			printf("Key: %d   Location: %lx  Value: %d\n",
					returned_keys[i],
					(unsigned long)returned_pointers[i],
					((record *)
					 returned_pointers[i])->value);
	}
}*/


/* Finds keys and their pointers, if present, in the range specified
 * by key_start and key_end, inclusive.  Places these in the arrays
 * returned_keys and returned_pointers, and returns the number of
 * entries found.
 */
/*int find_range( node * root, int key_start, int key_end, bool verbose,
		int returned_keys[], void * returned_pointers[]) {
	int i, num_found;
	num_found = 0;
	node * n = find_leaf( root, key_start, verbose );
	if (n == NULL) return 0;
	for (i = 0; i < n->num_keys && n->keys[i] < key_start; i++) ;
	if (i == n->num_keys) return 0;
	while (n != NULL) {
		for ( ; i < n->num_keys && n->keys[i] <= key_end; i++) {
			returned_keys[num_found] = n->keys[i];
			returned_pointers[num_found] = n->pointers[i];
			num_found++;
		}
		n = n->pointers[order - 1];
		i = 0;
	}
	return num_found;
}*/
// INSERTION
// DELETION.


/*void destroy_tree_nodes(node * root) {
	int i;
	if (root->is_leaf)
		for (i = 0; i < root->num_keys; i++)
			free(root->pointers[i]);
	else
		for (i = 0; i < root->num_keys + 1; i++)
			destroy_tree_nodes(root->pointers[i]);
	free(root->pointers);
	free(root->keys);
	free(root);
}

node * destroy_tree(node * root) {
	destroy_tree_nodes(root);
	return NULL;
}

// MAIN
int main( int argc, char ** argv ) {

	char * input_file;
	FILE * fp;
	node * root;
	int input, range2;
	char instruction;
	char license_part;

	root = NULL;
	verbose_output = false;

	if (argc > 1) {
		order = atoi(argv[1]);
		if (order < MIN_ORDER || order > MAX_ORDER) {
			fprintf(stderr, "Invalid order: %d .\n\n", order);
			//usage_3();
			exit(EXIT_FAILURE);
		}
	}

	//license_notice();
	//usage_1();  
	//usage_2();

	if (argc > 2) {
		input_file = argv[2];
		fp = fopen(input_file, "r");
		if (fp == NULL) {
			perror("Failure to open input file.");
			exit(EXIT_FAILURE);
		}
		while (!feof(fp)) {
			fscanf(fp, "%d\n", &input);
			root = insert(root, input, input);
		}
		fclose(fp);
		print_tree(root);
	}

	printf("> ");
	while (scanf("%c", &instruction) != EOF) {
		switch (instruction) {
		case 'd':
			scanf("%d", &input);
			root = delete(root, input);
			print_tree(root);
			break;
		case 'i':
			scanf("%d", &input);
			root = insert(root, input, input);
			print_tree(root);
			break;
		//case 'f':
		/*case 'p':
			scanf("%d", &input);
			find_and_print(root, input, instruction == 'p');
			break;*/
		/*case 'r':
			scanf("%d %d", &input, &range2);
			if (input > range2) {
				int tmp = range2;
				range2 = input;
				input = tmp;
			}
			find_and_print_range(root, input, range2, instruction == 'p');
			break;*/
		/*case 'l':
			print_leaves(root);
			break;*/
		/*case 'q':
			while (getchar() != (int)'\n');
			return EXIT_SUCCESS;
			break;
		case 't':
			print_tree(root);
			break;
		case 'v':
			verbose_output = !verbose_output;
			break;
		case 'x':
			if (root)
				root = destroy_tree(root);
			print_tree(root);
			break;
		default:
			//usage_2();
			break;
		}
		while (getchar() != (int)'\n');
		printf("> ");
	}
	printf("\n");

	return EXIT_SUCCESS;
}*/