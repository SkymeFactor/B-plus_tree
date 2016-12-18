#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


node * remove_entry_from_node(node * n, int key, node * pointer) {
	int i = 0, num_pointers;
	while (n->keys[i] != key)
		i++;
	for (++i; i < n->num_keys; i++)
		n->keys[i - 1] = n->keys[i];
	num_pointers = n->is_leaf ? n->num_keys : n->num_keys + 1;
	i = 0;
	while (n->pointers[i] != pointer)
		i++;
	for (++i; i < num_pointers; i++)
		n->pointers[i - 1] = n->pointers[i];
	n->num_keys--;
	if (n->is_leaf)
		for (i = n->num_keys; i < order - 1; i++)
			n->pointers[i] = NULL;
	else
		for (i = n->num_keys + 1; i < order; i++)
			n->pointers[i] = NULL;
	return n;
}

///In case of the root has been splitted
node * adjust_root(node * root) {
	node * new_root;
	if (root->num_keys > 0)
		return root;
	if (!root->is_leaf) {
		new_root = root->pointers[0];
		new_root->parent = NULL;
	}
	else
		new_root = NULL;
	free(root->keys);
	free(root->pointers);
	free(root);
	return new_root;
}

///If a node has become too small after deletion
node * merge_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime) {
	int i, j, neighbor_insertion_index, n_end;
	node * tmp;

	if (neighbor_index == -1) {
		tmp = n;
		n = neighbor;
		neighbor = tmp;
	}

	neighbor_insertion_index = neighbor->num_keys;

	if (!n->is_leaf) {
		neighbor->keys[neighbor_insertion_index] = k_prime;
		neighbor->num_keys++;
		n_end = n->num_keys;

		for (i  = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
			neighbor->keys[i] = n->keys[j];
			neighbor->pointers[i] = n->pointers[j];
			neighbor->num_keys++;
			n->num_keys--;
		}

		neighbor->pointers[i] = n->pointers[j];

		for (i = 0; i < neighbor->num_keys + 1; i++) {
			tmp = (node *)neighbor->pointers[i];
			tmp->parent = neighbor;
		}
	}
	else {
		for (i = neighbor_insertion_index, j = 0; j < n->num_keys; i++, j++) {
			neighbor->keys[i] = n->keys[j];
			neighbor->pointers[i] = n->pointers[j];
			neighbor->num_keys++;
		}
		neighbor->pointers[order - 1] = n->pointers[order - 1];
	}

	root = delete_entry(root, n->parent, k_prime, n);
	free(n->keys);
	free(n->pointers);
	free(n);
	return root;
}

///Redistributes entries between two nodes
node * redistribute_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime_index, int k_prime) {
	int i;
	node * tmp;

	//If n has a neighbor to the left.
	if (neighbor_index != -1) {
		if (!n->is_leaf)
			n->pointers[n->num_keys + 1] = n->pointers[n->num_keys];
		for (i = n->num_keys; i > 0; i--) {
			n->keys[i] = n->keys[i - 1];
			n->pointers[i] = n->pointers[i - 1];
		}
		if (!n->is_leaf) {
			n->pointers[0] = neighbor->pointers[neighbor->num_keys];
			tmp = (node *)n->pointers[0];
			tmp->parent = n;
			neighbor->pointers[neighbor->num_keys] = NULL;
			n->keys[0] = k_prime;
			n->parent->keys[k_prime_index] = neighbor->keys[neighbor->num_keys - 1];
		}
		else {
			n->pointers[0] = neighbor->pointers[neighbor->num_keys - 1];
			neighbor->pointers[neighbor->num_keys - 1] = NULL;
			n->keys[0] = neighbor->keys[neighbor->num_keys - 1];
			n->parent->keys[k_prime_index] = n->keys[0];
		}
	}

	//n is the leftmost node
	else {
		if (n->is_leaf) {
			n->keys[n->num_keys] = neighbor->keys[0];
			n->pointers[n->num_keys] = neighbor->pointers[0];
			n->parent->keys[k_prime_index] = neighbor->keys[1];
		}
		else {
			n->keys[n->num_keys] = k_prime;
			n->pointers[n->num_keys + 1] = neighbor->pointers[0];
			tmp = (node *)n->pointers[n->num_keys + 1];
			tmp->parent = n;
			n->parent->keys[k_prime_index] = neighbor->keys[0];
		}
		for (i = 0; i < neighbor->num_keys - 1; i++) {
			neighbor->keys[i] = neighbor->keys[i + 1];
			neighbor->pointers[i] = neighbor->pointers[i + 1];
		}
		if (!n->is_leaf)
			neighbor->pointers[i] = neighbor->pointers[i + 1];
	}
	n->num_keys++;
	neighbor->num_keys--;

	return root;
}

///Deletes an entry from the tree
node * delete_entry(node * root, node * n, int key, void * pointer) {
	int min_keys;
	node * neighbor;
	int neighbor_index;
	int k_prime_index, k_prime;
	int capacity;

	n = remove_entry_from_node(n, key, pointer);

	//In case of the root
	if (n == root)
		return adjust_root(root);

	//Below the root
	//Determine minimal size of node
	min_keys = n->is_leaf ? cut(order - 1) : cut(order) - 1;
	if (n->num_keys >= min_keys)
		return root;

	//Find the neighbor to merge and primary key in the parent
	for (int i = 0; i <= n->parent->num_keys; i++)
		if (n->parent->pointers[i] == n)
			neighbor_index =  i - 1;
	k_prime_index = neighbor_index == -1 ? 0 : neighbor_index;
	k_prime = n->parent->keys[k_prime_index];
	neighbor = neighbor_index == -1 ? n->parent->pointers[1] :
		n->parent->pointers[neighbor_index];

	capacity = n->is_leaf ? order : order - 1;

	if (neighbor->num_keys + n->num_keys < capacity)
		return merge_nodes(root, n, neighbor, neighbor_index, k_prime);
	else
		return redistribute_nodes(root, n, neighbor, neighbor_index, k_prime_index, k_prime);
}


node * delete(node * root, int key) {
	node * key_leaf;
	record * key_record;

	key_record = find_record(root, key);
	key_leaf = find_leaf(root, key);
	if (key_record != NULL && key_leaf != NULL) {
		root = delete_entry(root, key_leaf, key, key_record);
		free(key_record);
	}
	return root;
}


node * destroy_tree(node * root) {
	if (root->is_leaf)
		for (int i = 0; i < root->num_keys; i++)
			free(root->pointers[i]);
	else
		for (int i = 0; i < root->num_keys + 1; i++)
			destroy_tree(root->pointers[i]);
	free(root->pointers);
	free(root->keys);
	free(root);
	return NULL;
}