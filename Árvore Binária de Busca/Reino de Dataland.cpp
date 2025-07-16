#include <iostream>
using namespace std;

struct node
{
	int info; 
	node * left;
	node * right;

};

void insert(node * &curr, int info)
{
	if(curr == NULL)
	{
		curr = new node;
		curr->info = info;
		curr->left = NULL;
		curr->right = NULL;
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

node * search(node * curr, int info)
{
	if(curr == NULL)
	{
		return NULL;
	}else
	{
		if(curr->info == info)
		{
			return curr;
		}else
		{
			if(info < curr->info)
			{
				return search(curr->left, info);
			}else
			{
				return search(curr->right, info);
			}
		}
	}
}

node * repoint_less(node * &curr)
{
	if(curr->left == NULL)
	{
		node * aux = curr;
		curr = curr->right;
		return aux;
	}else
	{
		return repoint_less(curr->left);
	}
}

bool remove(node * &curr, int info)
{
	if(curr == NULL)
	{
		return false;
	}else
	{
		if(curr->info == info)
		{	
			node * aux = curr;
			                                        //ou ele tem um filho a direita ou a esquerda
			if(curr->left == NULL)
			{
				curr = curr->right;			       //ta dizendo que nao tem filho para a esquerda		//fazer a remoção
			}else if(curr->right == NULL)
			{
				curr = curr->left;
			}else                                 //Esse caso é para quando o nó tem dois filhos
			{
				aux = repoint_less(curr->right); // vai pegar o menor da subarvore à direita e vai salva-lo 
				curr->info = aux->info;		    // 16 = 16	//ex:16 caso queira remover a raiz, alem disso faz o pai do menor encontrado aponta para o filho
			}
			delete aux;
			aux = NULL;                        //só para garantir
			return true;
			
		}else
		{
			if(info < curr->info)
			{
				return remove(curr->left, info);
			}else
			{
				return remove(curr->right, info);
			}
		}
	}
}

void destruct(node * & curr)
{
	if(curr != NULL)
	{
		destruct(curr->left);
		destruct(curr->right);
		delete curr;
	}
}

int main()
{
    int N;
    char tipo;
    node * curr;
    int info;
    cin>>N;
    
    for (int i; i < N; i++)
    {
        cin>>tipo;
        
        if(tipo == 'i'){
            cin>>info;
            insert(curr, info);
        }
        else if(tipo == 'r')
        {
            remove(curr, info);
            
        }else
        {
            cin>>info;
            if(search(curr, info) == NULL)
            {
                cout << "Não" << endl;
            }else
                cout << "Sim" << endl;
            
        }
        
    }

    return 0;
}
