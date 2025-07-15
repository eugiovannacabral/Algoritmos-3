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

int main(){
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
        else if(tipo == 'b')
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
