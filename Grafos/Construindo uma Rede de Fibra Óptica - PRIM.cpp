#include <iostream>
#include <list>
#define INF 99999
using namespace std;

struct Aresta
{
	int u, v, c;
};

int prim_lista(list<Aresta>grafo[], int n, int start)
{
	bool visitados[n];
	int pai[n], distancia[n], atual; // distanci[i]->Qual foi o menor peso de aresta que chegou até i.
	
	for(int i=0; i<n; i++)
	{
		visitados[i] = false;
		pai[i] = -1;
		distancia[i] = INF;
	}
	atual = start;
	distancia[atual] = 0;
	
	while(!visitados[atual]){ // pode ser escrito visitado[atual] == false tbm 
		visitados[atual] = true;
		list<Aresta>::iterator it;
		
		for(it = grafo[atual].begin(); it!= grafo[atual].end(); it++)
		{
			int d = it->v, p = it->c;
			if(!visitados[d] && p < distancia[d])
			{
				distancia[d] = p;
				pai[d] = atual;	
			}
		}
		
		
		int menor_distancia = INF;
		for(int i=0; i<n; i++)
		{
			if(!visitados[i] && distancia[i] < menor_distancia)
			{
				menor_distancia = distancia[i];
				atual = i;
			}
		}
	}
	//Mostra as arestas da arvore geradora minima
	int peso_mst = 0;
	for(int i=0; i < n; i++){
		peso_mst += distancia[i];
	}
	return peso_mst;

}

int main()
{
	int n, m, u, v, c;
	
	cin >> n >> m; // n é o numero de vertices e m o de arestas
	list<Aresta> grafo[n];
	
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> c; // u é origem, v destino e c o peso
        u--;v--;
        grafo[u].push_back({u,v,c});
        grafo[v].push_back({v,u,c});
    }
    
	//Isso é só para visualizar o grafo, não faz parte do algoritmo de Prim.
	/*for(int i = 0; i < vertices; i++)
	{
		cout << i << ": ";
		for(it = grafo[i].begin(); it != grafo[i].end(); it++)
		{
			cout << "(" << it->destino+1 << "," << it->peso << "), ";
		}
		
		cout << endl;
	}
	*/
	cout << prim_lista(grafo, n, 0);
	return 0;
}
