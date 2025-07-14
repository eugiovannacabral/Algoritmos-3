#include <iostream>
#include <list>
#include <string>

using namespace std;

int main(){
    int n; // quant de  usuarios a serem cadastrados
    string nome[10];// nome dos usuarios
    list <int> seguidos[10]; // lista contendo a quant de usuarios seguidos por cada um deles
    list <int> :: iterator p; // ponteiro para a ajudar a varer a lista
    int usuarioseguido; // qaunt de usuarios que uma pessoa segue
    int procurado;// usuario que se deseja vereficar seus seguidores

    cin >> n;

    for(int i = 0; i < n; i++)
    {
        getline(cin >> ws, nome[i]);
    }

    for(int i = 0; i < n; i++) // para percorrer todos os usuarios cadastrados
    {
        cin >> usuarioseguido;
        while(usuarioseguido != -1)
        {
            seguidos[i].push_back(usuarioseguido);
            cin >> usuarioseguido;
        }
    }

    cin >> procurado;
    for(int i = 0; i < n; i++)
    {
        for(p = seguidos[i].begin(); p != seguidos[i].end(); ++p)
        {
            if(procurado == *p)
            {
                cout << nome[i] << endl;
                break;
            }
        }
    }

    int i = 0;
    while (!seguidos[i].empty()) 
    {
        seguidos[i].pop_front();
        i++;
    }

    return 0;
}
/*#include <iostream>
using namespace std;

int main()
{ //grafo = {{},{},{}} caso eu ja soubesse
	int vertices, arestas, origem, destino;
	
	cin >> vertices;
	
	bool grafo[vertices][vertices];
	
	
	for(int i = 0; i < vertices; i++)
	{
		for(int j=0; j < vertices;j++)
		{
			grafo[i][j] = false;
		}
	}		
	
	cin >> arestas;
	
	for(int i = 0; i < arestas; i++)
	{
		cin >> origem >> destino; 
		origem--;destino--;//garante que vai estar na linha e coluna correta da matriz isso tudo devido ao vetor começar com 0
		grafo[origem][destino] = true; // como esse grafo nao tem destino ou seja nao tem setinha eu faço ida  e volta
		grafo[destino][origem] = true; // se for um grafico direcionado eu tiro essa opcao
	}	
	
	//for para conseguir mostrar a matriz no final
	for(int i = 0; i < vertices; i++)
	{
		for(int j=0; j < vertices;j++)
		{
			cout << grafo[i][j] << " \t";
		}
		cout << endl;
	}	
	
	return 0;
}*/
