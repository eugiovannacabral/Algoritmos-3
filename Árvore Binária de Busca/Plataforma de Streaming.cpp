#include <iostream>
#include<string>
using namespace std;

struct dados
{
    string nome;    //titulo do filme
    string genero;  // genero do filme
    int duracao;    //quant tempo dura o filme
    int classfi;    //classificação 
    int ano;        //ano do filme
};
struct node
{
	dados info; 
	node * left;  
	node * right;

};

void insert(node * &curr, dados info)
{
	if(curr == NULL)
	{
		curr = new node;
		curr->info = info;
		curr->left = NULL;
		curr->right = NULL;
	}else
	{
		if(info.nome < curr->info.nome)
		{
			insert(curr->left, info);
		}else
		{
			insert(curr->right, info);
		}
	}
	
}

node * search(node * curr, string info)
{
	if(curr == NULL)
	{
		return NULL;
	}else
	{
		if(curr->info.nome == info)
		{
			return curr;
		}else
		{
			if(info < curr->info.nome)
			{
				return search(curr->left, info);
			}else
			{
				return search(curr->right, info);
			}
		}
	}
}

int main()
{
    int op;       // opcao que o usuario informara caso deseje inserir(1), busca(2) ou sair(0)
    string busca; // nome do filme que o usuario deseja procurar
    node * curr;
    dados info;   //informação de um filme
    
    cin >> op;
    
    while(op != 0)
    {
        if(op == 1)
        {
            getline(cin >> ws, info.nome);
            getline(cin >> ws, info.genero);
            cin >> info.duracao;
            cin >> info.classfi;
            cin >> info.ano;
            
            insert(curr, info);
        }else if(op == 2)
        {
            getline(cin >> ws, busca);
                
            // dados temp;         //criando uma variavel temporaria devido a incompatibilidade do tipo de busca e do segundo parametro de search
            // temp.nome = busca;  // recebendo o nome do filme desejado 
            node* resultado = search(curr, busca); // Se o filme existir, resultado será o endereço do nó onde estão as informações do filme.
                
            if(resultado == NULL)
            {
                cout << "Filme nao encontrado"<< endl;    
            }else
            {
                cout << "Nome: "<< resultado->info.nome << endl;
                cout << "Genero: "<< resultado->info.genero << endl;
                cout << "Duracao: "<< resultado->info.duracao <<  " mins" << endl;
                cout << "Classificacao: "<< resultado->info.classfi<< endl;
                cout << "Ano: "<<resultado->info.ano << endl;
            }
        }else
        {
            cout << "Operacao invalida" << endl;
        }
            
        cin >> op;
    }
    
	return 0;
}
