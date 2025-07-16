#include<iostream>
using namespace std;

struct Node {
	int info;
	Node * right;
	Node * left;
} ;


void insert(Node *& curr, int info)
{	
	if(curr == NULL)
	{
		curr = new Node;
		curr->info = info;
		curr->right = NULL;
		curr->left = NULL;
	} else {
		if(info >= curr->info)
		{
			insert(curr->right, info);
			
		} else if(info < curr->info) 
		{
			insert(curr->left, info);
		}		
	}	
}

void show_ordered(Node * curr)      
{
	if(curr->right != NULL) 
		show_ordered(curr->right);
	cout << curr->info << " "; //listando o nó atual
	if(curr->left != NULL)
		show_ordered(curr->left);
}

int main()
{
    Node * root = NULL;
    int n;
    
    cin >> n;
    while(n != -1)
    {
        insert(root, n);
        cin >> n;
    }
    
    show_ordered(root);
    return 0;
}
// ----------------------------------------------------------------------------
