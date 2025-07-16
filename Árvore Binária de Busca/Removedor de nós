#include<iostream>
using namespace std;

struct Node
{
    int info;
    Node * left;
    Node * right;
};

void insert(Node* &curr, int info)
{
    if(curr == NULL)
    {
        curr = new Node;
        curr->info = info;
        curr->right = NULL;
        curr->left = NULL;
    }else
    {
        if(info < curr->info)
        {
            insert(curr->left, info);
        }else
        {
            insert(curr->right, info);
        }
        
    }
        
}

Node * disconnect_lesser(Node *& curr)
{
	Node * aux = curr;
	if(aux->left == NULL){ 	
		curr = curr->right; 
		return aux;			
	} else {				
		return disconnect_lesser(curr->left);
	}
}


int remove(Node *& curr, int info)
{
    if(curr == NULL)
        return 0;

    // Primeiro, percorre os filhos antes de mexer no nó atual
    remove(curr->left, info);
    remove(curr->right, info);

    Node * aux;
    if(curr->info == info)
    {
        aux = curr;
        if(curr->left == NULL)
        {
            curr = aux->right;
        }
        else if(curr->right == NULL)
        {
            curr = aux->left;
        }
        else
        {
            aux = disconnect_lesser(curr->right);
            curr->info = aux->info;
            delete aux;
            // IMPORTANTE: pode ser que o novo valor seja igual a x também!
            // Então depois de substituir, verifica de novo o mesmo nó
            remove(curr, info);
            return 1;
        }
        delete aux;
        return 1;
    }
    return 0;
}


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

void show_ordered(Node * curr)                                                  //  Percuro in-order
{                                                                               //Antes de mostrar o valor do nó atual, a função chama recursivamente o lado esquerdo.
    if(curr->left != NULL)                                                  //Isso significa que os nós com valores menores serão visitados primeiro
        show_ordered(curr->left);
    cout << curr->info << " ";
	if(curr->right != NULL)                                                 //Depois que aqui vai mostrar os valores maiores
		show_ordered(curr->right);
		
}

int main()
{
    int i, n, x; // numeos a serem inseridos e o numero que deseja procurar, respectivamente
    Node * root = NULL;
    i = 0;
    
    cin >> n;
    while(n != 0)
    {
        insert(root, n);
        //i++;
        cin >> n;
    }
    
    cin  >> x;
    remove(root, x);
    show_ordered(root);

    return 0;
}
