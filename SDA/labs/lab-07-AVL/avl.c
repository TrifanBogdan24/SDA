/*
*	Created by Nan Mihai on 11.04.2023
*	Copyright (c) 2023 Nan Mihai. All rights reserved.
*	Laborator 7 - Structuri de date și algoritmi
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2022-2023, Seria CD
*/
#include "avl.h"

Tree createTree(T value) {
	Tree nod = malloc(sizeof(Tree));
	nod->left = nod->right = NULL;
	nod->value = value;
	nod->height = 0;
	return nod;
}

int max(int a, int b) {
	
	if (a > b) return a;
	else return b;
}

int height(Tree root) {
	
	if (root == NULL)
		return -1;

	return root->height;
}

int balancedFactor(Tree root) {
	if (root == NULL) return 0;
	return height(root->right) - height(root->left);
}

void updateHeight(Tree root) {
	
	if (root == NULL) {
		return;
	} else {
		int h_st = height(root->left);
		int h_dr = height(root->right);

		if (h_st > h_dr)
			root->height = h_st + 1;
		else
			root->height = h_dr + 1;
		
	}

}

Tree leftRotation(Tree x) {
	
	if (x == NULL) return x;
	if (x->right == NULL) return x;

	Tree y = x->right;
	Tree b = x->right->left;

	x->right = b;
	y->left = x;
	updateHeight(x);
	updateHeight(y);
	return y;
}

Tree rightRotation(Tree x) {
	
	if (x == NULL) return x;
	if (x->left == NULL) return x;

	Tree b = x->left->right;
	Tree y = x->left;
	x->left = b;
	y->right = x;


	updateHeight(x);
	updateHeight(y);

	return y;
}

Tree minimum(Tree root) {
		if (root != NULL) {
		if (root->left == NULL) return root;
		return minimum(root->left);
	}
	return NULL;
}


Tree AVL(Tree root) {
	if (root == NULL) return NULL;
	int bf = balancedFactor(root);
	if (balancedFactor(root) < -1) {
		// problema este pe LEFT
		if (balancedFactor(root->left) < -1) {
			// problema este pe LEFT - LEFT
			root = rightRotation(root);
		} else if (balancedFactor(root->left) > 1){
			// problema este pe LEFT - RIGHT
			root->left = leftRotation(root->left);
			root = rightRotation(root);
		}

	} else {
		// problema este pe RIGHT
		if (balancedFactor(root->right) < -1) {
			// problema este pe RIGHT - LEFT
			root->right = rightRotation(root->right);
			root = leftRotation(root);
		} else if (balancedFactor(root->right) > 1 ) {
			// problema este pe RIGHT - RIGHT
			root = leftRotation(root);
		}
	}
	root->left = AVL(root->left);
	root->right = AVL(root->right);
	updateHeight(root);
	return root;
}

Tree insert(Tree root, T value) {
	if (root == NULL) {
		// arborele este vid
		root = createTree(value);
		return root;
	}

	if (value < root->value) {
		root->left = insert(root->left, value);
	} else if (value > root->value) {
		root->right = insert(root->right, value);
	} else {
		return root;
	}


	updateHeight(root);

	int bal_factor = balancedFactor(root);

	if (bal_factor < -1 && value < root->left->value) {
		/* cazul 1 : Left-Left
			1
		  2
		3	
		*/
		return rightRotation(root);	// 1
	}

	else if (bal_factor > 1 && value > root->right->value) {
		/* cazul 2 : Right-Right
			1
			  2
			    3
		*/
		return leftRotation(root); // 1
	}

	else if (bal_factor < -1 && value > root->left->value) {
		/* cazul 3 : Left-Right
			1
		  2
		   3
		*/
		root->left = leftRotation(root->left);	// 2
		return rightRotation(root);				// 1
	}

	else if (bal_factor > 1 && value < root->right->value) {
		/* cazul 4 : Right-Left
			1
		       2
			  3
		*/
		root->right = rightRotation(root->right);	// 2
		return leftRotation(root);					// 1
	}

	return root;
}

Tree delete(Tree root, T value) {
	
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

	root = AVL(root);
	updateHeight(root);
	return root;
}

Tree freeTree(Tree root) {
	
	if ( root != NULL) {
		// printf("%d ", root->value);
		freeTree(root->left);
		freeTree(root->right);
		free(root);
		// root = NULL;
	}
}