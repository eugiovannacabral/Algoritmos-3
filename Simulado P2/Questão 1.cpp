#include <iostream>

using namespace std;

// Funções para Árvore Binária de Busca ---------------------------------------

//typedef int KeyType;
//typedef int ValueType;

struct dados//dados das tortas
{
    int pf;//preco final
    int key;
};

/*struct DataType {
	KeyType key;
	ValueType value;
};*/

struct Node {
	dados novatorta;
	Node * right;
	Node * left;
} ;


void insert(Node *& curr, dados novatorta)
{	
	if(curr == NULL)
	{
		curr = new Node;
		curr->novatorta = novatorta;
		curr->right = NULL;
		curr->left = NULL;
	} else {
		if(novatorta.pf >= curr->novatorta.pf)
		{
			insert(curr->right, novatorta);
			
		} else if(novatorta.pf < curr->novatorta.pf) 
		{
			insert(curr->left, novatorta);
		}		
	}	
}

/*Node * search(Node * curr, KeyType key){
	if(curr == NULL)
		return NULL;
	if(key == curr->data.key){
		return curr;
	} else {
		if(key > curr->data.key){
			return search(curr->right, key);
		} else if(key < curr->data.key){
			return search(curr->left, key);
		}
	}
	return NULL;
}*/

void show_ordered(Node * curr)      
{
	if(curr->left != NULL) // lista o nó da esquerda
		show_ordered(curr->left);
	cout << curr->novatorta.key << ":" << curr->novatorta.pf << endl; //listando o nó atual
	if(curr->right != NULL)
		show_ordered(curr->right);//lista o nó da direita
}

/*Node * disconnect_lesser(Node *& curr){
	Node * aux = curr;
	if(aux->left == NULL){ 	
		curr = curr->right; 
		return aux;			
	} else {				
		return disconnect_lesser(curr->left);
	}
}*/


/*int remove(Node *& curr, KeyType old_key){
	if(curr == NULL){
		return 0;
	}
	Node * aux;
	if(curr->data.key == old_key){
		aux = curr;		
		if(curr->left == NULL){
			curr = aux->right;
		} else if(curr->right == NULL){
			curr = aux->left;
		} else {
			aux = disconnect_lesser(curr->right);
			curr->data = aux->data;
		}		
		delete aux;
		return 1;		
	} else {
		if(old_key > curr->data.key){
			return remove(curr->right, old_key);
		} else if(old_key < curr->data.key) {
			return remove(curr->left, old_key);
		}
	}
	return 0;
}*/


void destruct(Node *& curr)
{
	if(curr->left != NULL)
		destruct(curr->left);
	if(curr->right != NULL)
	   	destruct(curr->right);
	delete curr;
	curr = NULL;
	return;
}

int main()
{
    Node * root = NULL;
    dados t;
    float em, p, a, d;//caracteristicas da torta
    int n;
    
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> em >> p >> a >> d;
        t.pf = ((em * p * a) + d + a);
        t.key = i;
        insert(root, t);
    }
    
    show_ordered(root);
    destruct(root);
    return 0;
}
// ----------------------------------------------------------------------------
