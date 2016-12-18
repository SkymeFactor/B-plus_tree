#ifndef C_LANG
#define C_LANG

#include <stdio.h>
#include <stdlib.h>
#define bool char
#define false 0
#define true 1

#endif

#ifndef B_PLUS_TREE
#define B_PLUS_TREE
	//Consts
	#define DEFAULT_ORDER 4

	//Structs
	typedef struct record {
		int value;
	} record;

	typedef struct node {
		void ** pointers;
		int * keys;
		struct node * parent;
		bool is_leaf;
		int num_keys;
		struct node * next; // Used for queue.
	} node;

	//Globals
	extern char * input_file;
	extern int order;
	extern node * queue;
#endif

#ifndef UTILITE_FUNCTIONS
#define UTILITE_FUNCTIONS
	void show_help();
	void put_into_queue(node * new_node);
	node * extrect_from_queue();
	void print_tree(node * root);
	void save_tree(node * root);
	node * find_leaf(node * root, int key);
	record * find_record(node * root, int key);
	int cut(int length);
#endif


#ifndef INSERTION_FUNCTIONS
#define INSERTION_FUNCTIONS
	record * add_new_record(int value);
	node * add_new_node(void);
	node * add_new_leaf(void);
	node * insert_into_leaf_after_splitting(node * root, node * leaf, int key, record * pointer);
	node * insert_into_node(node * root, node * parent, int left_index, int key, node * right);
	node * insert_into_node_after_splitting(node * root, node * parent, int left_index, int key, node * right);
	node * insert_into_parent(node * root, node * left, int key, node * right);
	node * insert_into_new_root(node * left, int key, node * right);
	node * insert(node * root, int key, int value);
#endif


#ifndef DELETION_FUNCTIONS
#define DELETION_FUNCTIONS
	node * adjust_root(node * root);
	node * merge_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime);
	node * redistribute_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime_index, int k_prime);
	node * delete_entry(node * root, node * n, int key, void * pointer);
	node * delete(node * root, int key);
	node * destroy_tree(node * root);
#endif