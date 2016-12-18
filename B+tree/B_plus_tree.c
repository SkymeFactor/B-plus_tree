#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

//Globlas initialize
char * input_file = "Data.txt";
int order = DEFAULT_ORDER;
node * queue = NULL;



int main() {
	FILE * f = fopen(input_file, "r");
	node * root = NULL;
	int input_value;
	char command;

	if (f != NULL) {
		fscanf(f, "%c", &input_value);
		if (input_value != '\0')
		while (!feof(f)) {
			fscanf(f, "%d", &input_value);
				root = insert(root, input_value, input_value);
		}
		fclose(f);
	}
	show_help();

	printf("> ");
	while (scanf("%c", &command) != -1) {
		switch (command) {
		case 'd':
			scanf("%d", &input_value);
			root = delete(root, input_value);
			print_tree(root);
			break;
		case 'i':
			scanf("%d", &input_value);
			root = insert(root, input_value, input_value);
			print_tree(root);
			break;
		case 'f':
			if (root) root = destroy_tree(root);
			print_tree(root);
		break;
		case 'q': return 0; break;
		case 'p': print_tree(root); break;
		case 's': save_tree(root); break;
		case '?': show_help(); break;
		default: printf("Error: No such command existed\n"); break;
		}
		while (getchar() != '\n');
		printf("> ");
	}
	printf("\n");
	return 0;
}