#include <iostream>
#include <iomanip>

using namespace std;

struct treenode {
    int n;
    treenode *esquerda;
    treenode *direita;
};

typedef treenode *treenodeptr;

void tree_insert(treenodeptr &tree, int insere){
    if(tree == NULL){
        tree = new treenode;
        tree->n = insere;
        tree->esquerda = NULL;
        tree->direita = NULL;
    } else if (insere < tree->n){
        tree_insert(tree->esquerda, insere);
    } else {
        tree_insert(tree->direita, insere);
    }
}

void maior(treenodeptr tree, int &numero_maior){
    if (tree->esquerda != NULL){
        maior(tree->esquerda, numero_maior);
    }
    if (tree->n > numero_maior){
        numero_maior = tree->n;
    }
    if (tree->direita != NULL){
        maior(tree->direita, numero_maior);
    }
}

void menor(treenodeptr tree, int &numero_menor){
    if (tree->direita != NULL){
        menor(tree->direita, numero_menor);
    }
    if (tree->n < numero_menor){
        numero_menor = tree->n;
    }
    if (tree->esquerda != NULL){
        menor(tree->esquerda, numero_menor);
    }
}

void destroy_tree(treenodeptr &tree){
    if (tree != NULL){
        destroy_tree(tree->esquerda);
        destroy_tree(tree->direita);
        delete tree;
    }
    tree = NULL;
}

int main(){
    int n;
    int numero_maior = -9999;
    int numero_menor = 9999;

    treenodeptr tree= NULL;

    cin >> n;
    while(n != -1){
        tree_insert(tree, n);
        cin >> n;
    }

    maior(tree, numero_maior);
    menor(tree, numero_menor);

    cout << numero_menor << " e " << numero_maior << endl;

    destroy_tree(tree);

    return 0;
}
