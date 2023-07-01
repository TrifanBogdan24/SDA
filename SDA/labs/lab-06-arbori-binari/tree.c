/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
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
void init(Tree (*root), Tree parent, Item value) {
	// TODO 0
	((*root))->parent = parent;
	((*root))->left = NULL;
	((*root))->right = NULL;
	((*root))->value = value;
	return;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	// TODO 1

	// varinata recursiva :
	if (root == NULL) {
		root = createTree(root, value);
		return root;
	}
    
	if (value < root->value) {
		if(root->left == NULL) {
			root->left = createTree(root, value);
			return root;
		} else {
			root->left = insert(root->left, value);
			return root;
		}
	} else if (value > root->value) {
		if(root->right == NULL) {
			root->right = createTree(root, value);
			return root;
		} else {
			root->right = insert(root->right, value);
			return root;
		}
	} else return root;
	return root;
	
	/* varianta recursiva
	Tree nod_val = root;
	int OK = 1;  // e cam degeaba, de vreme ce return - ul iese din functie, nu doar din while
	while (OK == 1) {
			
		if (nod_val->value == value) {
			OK = 0;
			return root;
		} 
		if (value < nod_val->value) {
			if (nod_val->left == NULL) {
				Tree new_left = createTree(nod_val, value);
				nod_val->left = new_left;
				OK = 0;
				return root;
			} else {
				nod_val = nod_val->left;
			}
		} else {
			// value > nod_val->value
			if (nod_val->right == NULL) {
				Tree new_right = createTree(nod_val, value);
				nod_val->right = new_right;
				OK = 0;
				return root;
			} else {
				nod_val = nod_val->right;
			}
		}
	}
	*/
	
}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	// TODO 2
	return (root == NULL);
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	// TODO 3
	if (tree == NULL) return 0;
	if (tree->value == value) return 1;
	if (contains(tree->left, value) == 1) return 1;
	if (contains(tree->right, value) == 1) return 1;
	return 0;
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree minimum(Tree tree) {
	// TODO 4.1
	if (tree != NULL) {
		if (tree->left == NULL) return tree;
		return minimum(tree->left);
	}
	return NULL;
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	// TODO 4.2
	if (tree != NULL) {
		if (tree->right == NULL) return tree;
		return maximum(tree->right);
	}
	return NULL;

}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree successor(Tree root, Item value) {
	// TODO 5

	// noi cautam : value + 1
	if (root == NULL) return NULL;
	if (maximum(root)->value == value) return NULL;
	Tree nod_val = root;
	
	while (nod_val->value != value) {
		if (value < nod_val->value) nod_val = nod_val->left;
		else if (value > nod_val->value) nod_val = nod_val->right;
	}
	//printf("%d %d %d\n" , maximum(root)->value, nod_val->value, nod_val->parent->value);
	
	if (nod_val->right != NULL) {
		// daca elementul este radacina
		// cautam minimul de pe subarborele drept
	
		return minimum(nod_val->right);
	}

	// printf("%d ", nod_val->value);
	// Tree rasp = nod_val;
	// return rasp;
	while (nod_val != root && nod_val != nod_val->parent->left) { // && rasp->value < value) {
		nod_val = nod_val->parent;
	}
	// printf("%d \n" , rasp->parent->value);
	return nod_val->parent;
}

/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
	// TODO 6
	
	if (root == NULL) return NULL;
	if (minimum(root)->value == value) return NULL;
	Tree nod_val = root;
	
	while (nod_val->value != value) {
		if (value < nod_val->value) nod_val = nod_val->left;
		else if (value > nod_val->value) nod_val = nod_val->right;
	}
	//printf("%d %d %d\n" , maximum(root)->value, nod_val->value, nod_val->parent->value);
	
	if (nod_val->left != NULL) {
		// daca elementul este radacina
		// cautam minimul de pe subarborele drept
	
		return maximum(nod_val->left);
	}

	// printf("%d ", nod_val->value);
	// Tree rasp = nod_val;
	// return rasp;
	while (nod_val != root && nod_val != nod_val->parent->right) { // && rasp->value < value) {
		nod_val = nod_val->parent;
	}
	// printf("%d \n" , rasp->parent->value);
	return nod_val->parent;
	
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree (*root)) {
	// TODO 6
	
	if ( (*root) != NULL) {
		// printf("%d ", (*root)->value);
		destroyTree(&( (*root)->left) );
		destroyTree(&( (*root)->right) );
		free( (*root) );
		// (*root) = NULL;
	}
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	// TODO 7
	
	if (root == NULL) {
		printf("Nodul %d nu a fost gasit.\n" , root->value);
		return root; 
	} else if (root->value > value) {
		root->left = delete(root->left , value);
	} else if (root->value < value) {
		root->right = delete(root->right , value);
	} else {
		// am gasit nodul cautat
		if (root->left != NULL && root->right != NULL) {
			// nodul are ambii fii
			Tree new_nod = minimum(root->right);
			root->value = new_nod->value;
			root->right = delete(root->right , new_nod->value);
		} else {
			// nodul are un singur fiu
			Tree new_nod = root;

			if (root->left != NULL) {
				// && root->right == NULL
				// nodul are doar fiul stang
				root = root->left;
			} else {
				// && root->left == NULL
				// nodul are doar fiul drept
				root = root->right;
			}

			free(new_nod);
		}
	}
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
	// TODO 8
	
	if (root == NULL) return NULL;
	
	while ( (value1 - root->value) * (value2 - root->value) > 0) {
		if (value1 > root->value) root = root->right;
		else if (value1 < root->value) root = root->left;
	}	
	return root;
}
