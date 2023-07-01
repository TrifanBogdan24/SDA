/*
*	Created by Nan Mihai on 28.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Item value) {
	*root = createTree(value);
	return ;
	// TODO 1
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	
	if (root == NULL) {
		root = createTree(value);
		return root;
	} 

	if (root->value == value) return root;

	if (root->value > value) {
		if (root->left == NULL) {
			root->left = createTree(value);
			return root;
		} else {
			root->left = insert(root->left, value);
			return root; 
		}
	}

	if (root->value < value) {
		if (root->right == NULL) {
			root->right = createTree(value);
			return root;
		} else {
			root->right = insert(root->right, value);
			return root;
		}
	}
	
	
	// TODO 2
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în postordine
*/
void printPostorder(Tree root) {
	//  postordine 
	if (root == NULL) return ;
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d ", root->value);
	// TODO 3
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în preordine
*/
void printPreorder(Tree root) {
	// TODO 4

	// preordine : R-S-D : radacina - stanga - dreapta
	if (root == NULL) return;
	printf("%d ", root->value);
	printPreorder(root->left);
	printPreorder(root->right);
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în inordine
*/
void printInorder(Tree root) {
	// TODO 5

	// inordine : S-R-D : stanga - radacina - dreapta
	if (root == NULL) return;
	printPreorder(root->left);
	printf("%d ", root->value);
	printPreorder(root->right);
	
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void freeTree(Tree *root) {
	if ( (*root) != NULL) {
		// printf("%d ", (*root)->value);
		freeTree(&( (*root)->left) );
		freeTree(&( (*root)->right) );
		// root = NULL;
		free( (*root) );
		(*root) = NULL;
	}
	// TODO 6
}


/*
*	Funcție care determină numărul de noduri dintr-un arbore binar
*/
int size(Tree root) {
	// TODO 7
	
	if (root != NULL) {
		return 1+size(root->left)+size(root->right);
	}
	return 0;
}

/*
*	Funcție care returnează adâncimea maximă a arborelui
*/
int maxDepth(Tree root) {
	// TODO 8

	if (root == NULL) return -1;  // indexarea nivelelor se face de la 0
	else {
		Tree aux = root;
		int st = maxDepth(aux->left);
		int dr = maxDepth(aux->right);
		if (st > dr) return 1 + st;
		else return 1+ dr;
	}
	
}

/*
*	Funcție care construiește oglinditul unui arbore binar
*/
void mirror(Tree root) {
	// TODO 9

	if (root != NULL) {
		Tree new_left = root->right;
		Tree new_right = root->left;

		root->left = new_left;
		root->right = new_right;
		
		mirror(root->left);
		mirror(root->right);
	}
}

/*
*	Funcție care verifică dacă doi arbori binari sunt identici
*/
int sameTree(Tree root1, Tree root2) {
	// TODO 10
	if (root1 == NULL && root2 == NULL) return 1;
	if (root1 == NULL && root2 != NULL) return 0;
	if (root1 != NULL && root2 == NULL) return 0;
	if (root1 != NULL && root2 != NULL) {
		if (root1->value != root2->value) return 0;
		return sameTree(root1->left , root2->left) * sameTree(root1->right , root2->right);
	}
	return 1;
}
