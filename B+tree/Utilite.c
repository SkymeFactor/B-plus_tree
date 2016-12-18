#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


void show_help() {
	printf("Help about how use the B+ tree:\n"
		"\ti <k> - Insert key <k>\n"
		"\td <k> - Delete key <k>\n"
		"\tf - Destroy the tree\n"
		"\tp - Print the tree\n"
		"\tq - Quit\n"
		"\ts - Save the tree into Data.txt"
		"\t? - Show the help message\n");
}

void put_into_queue(node * new_node) {
	node * t;
	if (queue == NULL) {
		queue = new_node;
		queue->next = NULL;
	}
	else {
		t = queue;
		while (t->next != NULL) {
			t = t->next;
		}
		t->next = new_node;
		new_node->next = NULL;
	}
}

node * extrect_from_queue() {
	node * n = queue;
	queue = queue->next;
	n->next = NULL;
	return n;
}

void print_tree(node * root) {

	node * n = NULL;
	int rank = 0;
	int new_rank = 0;

	if (root == NULL) {
		printf("Empty tree\n");
		return;
	}
	queue = NULL;
	put_into_queue(root);
	while (queue != NULL) {
		n = extrect_from_queue();
		if (n->parent != NULL && n == n->parent->pointers[0]) {
			//count the path to root
			new_rank = 0;
			node * c = n;
			while (c != root) {
				c = c->parent;
				new_rank++;
			}
			if (new_rank != rank) {
				rank = new_rank;
				printf("\n");
			}
		}
		for (int i = 0; i < n->num_keys; i++) {
			printf("%d ", n->keys[i]);
		}
		if (!n->is_leaf)
			for (int i = 0; i <= n->num_keys; i++)
				put_into_queue(n->pointers[i]);
		printf("| ");
	}
	printf("\n");
}

void save_tree(node * root) {


	FILE *f = fopen(input_file, "w");
	node * t, * n = NULL;

	if (f != NULL) {
		if (root == NULL) {
			fprintf(f, "\0");
			fclose(f);
			printf("Successfully completed\n");
			return;
		}

		fprintf(f, "1");
		queue = NULL;
		put_into_queue(root);
		while (queue != NULL) {
			n = extrect_from_queue();
			if (n->is_leaf)
				for (int i = 0; i < n->num_keys; i++)
					fprintf(f, "%d ", n->keys[i]);
			else
				for (int i = 0; i <= n->num_keys; i++)
					put_into_queue(n->pointers[i]);
		}
		fclose(f);
	}
	printf("Successfully completed\n");
}

node * find_leaf(node * root, int key) {
	int i = 0;
	node * t = root;
	if (t == NULL) return t;
	while (!t->is_leaf) {
		while (i < t->num_keys) {
			if (key >= t->keys[i]) i++;
			else break;
		}
		t = (node *)t->pointers[i];
	}
	return t;
}


record * find_record(node * root, int key) {
	int i = 0;
	node * t = find_leaf(root, key);
	if (t == NULL) return NULL;
	for (i = 0; i < t->num_keys; i++)
		if (t->keys[i] == key) break;
	if (i == t->num_keys)
		return NULL;
	else
		return (record *)t->pointers[i];
}


int cut(int length) {
	if (length % 2 == 0)
		return length / 2;
	else
		return length / 2 + 1;
}