#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

///Creates a new record
record * add_new_record(int value) {
	record * new_record = (record *)malloc(sizeof(record));
	return new_record;
}

///Create a new node
node * add_new_node(void) {
	node * new_node;
	new_node = malloc(sizeof(node));
	new_node->keys = malloc((order - 1) * sizeof(int));
	new_node->pointers = malloc(order * sizeof(void *));
	new_node->is_leaf = false;
	new_node->num_keys = 0;
	new_node->parent = NULL;
	new_node->next = NULL;
	return new_node;
}

///Create a new leaf
node * add_new_leaf() {
	node * leaf = add_new_node();
	leaf->is_leaf = true;
	return leaf;
}


node * insert_into_leaf_after_splitting(node * root, node * leaf, int key, record * pointer) {
	node * new_leaf;
	int * temp_keys;
	void ** temp_pointers;
	int insertion_index, split, new_key;

	new_leaf = add_new_leaf();
	temp_keys = malloc(order * sizeof(int));
	temp_pointers = malloc(order * sizeof(void *));

	insertion_index = 0;
	while (insertion_index < order - 1 && leaf->keys[insertion_index] < key)
		insertion_index++;

	for (int i = 0, j = 0; i < leaf->num_keys; i++, j++) {
		if (j == insertion_index) j++;
		temp_keys[j] = leaf->keys[i];
		temp_pointers[j] = leaf->pointers[i];
	}

	temp_keys[insertion_index] = key;
	temp_pointers[insertion_index] = pointer;

	leaf->num_keys = 0;

	split = cut(order - 1);

	for (int i = 0; i < split; i++) {
		leaf->pointers[i] = temp_pointers[i];
		leaf->keys[i] = temp_keys[i];
		leaf->num_keys++;
	}

	for (int i = split, j = 0; i < order; i++, j++) {
		new_leaf->pointers[j] = temp_pointers[i];
		new_leaf->keys[j] = temp_keys[i];
		new_leaf->num_keys++;
	}

	free(temp_pointers);
	free(temp_keys);

	new_leaf->pointers[order - 1] = leaf->pointers[order - 1];
	leaf->pointers[order - 1] = new_leaf;

	for (int i = leaf->num_keys; i < order - 1; i++)
		leaf->pointers[i] = NULL;
	for (int i = new_leaf->num_keys; i < order - 1; i++)
		new_leaf->pointers[i] = NULL;

	new_leaf->parent = leaf->parent;
	new_key = new_leaf->keys[0];

	return insert_into_parent(root, leaf, new_key, new_leaf);
}

///Insert a new key and pointer into a node
node * insert_into_node(node * root, node * n, int left_index, int key, node * right) {
	for (int i = n->num_keys; i > left_index; i--) {
		n->pointers[i + 1] = n->pointers[i];
		n->keys[i] = n->keys[i - 1];
	}
	n->pointers[left_index + 1] = right;
	n->keys[left_index] = key;
	n->num_keys++;
	return root;
}

///Insert a new key and pointer into a node
///In case of a node must be splitted
node * insert_into_node_after_splitting(node * root, node * old_node, int left_index, int key, node * right) {
	int i, j, split, k_prime;
	node * new_node, *child;
	int * temp_keys;
	node ** temp_pointers;

	temp_pointers = malloc((order + 1) * sizeof(node *));
	temp_keys = malloc(order * sizeof(int));

	for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {
		if (j == left_index + 1) j++;
		temp_pointers[j] = old_node->pointers[i];
	}

	for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {
		if (j == left_index) j++;
		temp_keys[j] = old_node->keys[i];
	}

	temp_pointers[left_index + 1] = right;
	temp_keys[left_index] = key;

	//Create the node and copy half the keys into both of them
	split = cut(order);
	new_node = add_new_node();
	old_node->num_keys = 0;
	for (i = 0; i < split - 1; i++) {
		old_node->pointers[i] = temp_pointers[i];
		old_node->keys[i] = temp_keys[i];
		old_node->num_keys++;
	}
	old_node->pointers[i] = temp_pointers[i];
	k_prime = temp_keys[split - 1];
	for (++i, j = 0; i < order; i++, j++) {
		new_node->pointers[j] = temp_pointers[i];
		new_node->keys[j] = temp_keys[i];
		new_node->num_keys++;
	}
	new_node->pointers[j] = temp_pointers[i];

	free(temp_pointers);
	free(temp_keys);

	new_node->parent = old_node->parent;
	for (i = 0; i <= new_node->num_keys; i++) {
		child = new_node->pointers[i];
		child->parent = new_node;
	}
	return insert_into_parent(root, old_node, k_prime, new_node);
}


node * insert_into_parent(node * root, node * left, int key, node * right) {
	int left_index = 0;
	node * parent;

	parent = left->parent;

	//If no parents available
	if (parent == NULL) 
		return insert_into_new_root(left, key, right);
	
	//Else find the parent's pointer to the left node.
	left_index = 0;
	while (left_index <= parent->num_keys && parent->pointers[left_index] != left)
		left_index++;

	if (parent->num_keys < order - 1)//If everything's alright
		return insert_into_node(root, parent, left_index, key, right);
	return insert_into_node_after_splitting(root, parent, left_index, key, right);//Else split a node
}


node * insert_into_new_root(node * left, int key, node * right) {

	node * root = add_new_node();
	root->keys[0] = key;
	root->pointers[0] = left;
	root->pointers[1] = right;
	root->num_keys++;
	root->parent = NULL;
	left->parent = root;
	right->parent = root;
	return root;
}


node * insert(node * root, int key, int value) {

	record * pointer;
	node * leaf;

	//Ignore duplicates
	if ( find_record(root, key) != NULL)
		return root;

	// Create a new record for the value
	pointer = add_new_record(value);

	//If the tree does not exist, create a new tree
	if (root == NULL){
		root = add_new_leaf();
		root->keys[0] = key;
		root->pointers[0] = pointer;
		root->pointers[order - 1] = NULL;
		root->parent = NULL;
		root->num_keys++;
		return root;
	}

	leaf = find_leaf(root, key);

	//There are places in the found leaf for both of key and pointer
	if (leaf->num_keys < order - 1) {
		int insertion_point = 0;

		while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key)
			insertion_point++;

		for (int i = leaf->num_keys; i > insertion_point; i--) {
			leaf->keys[i] = leaf->keys[i - 1];
			leaf->pointers[i] = leaf->pointers[i - 1];
		}
		leaf->keys[insertion_point] = key;
		leaf->pointers[insertion_point] = pointer;
		leaf->num_keys++;

		return root;
	}
	//If the leaf must be splitted
	return insert_into_leaf_after_splitting(root, leaf, key, pointer);
}