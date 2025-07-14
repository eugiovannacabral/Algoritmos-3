#include <iostream>
#include <list>
#define INF 99999
using namespace std;

struct Aresta{
	int origem, destino, peso;
};

void cria_aresta(list<Aresta>grafo[], int u, int v, int p, int orientado)
{
    // u, v e p referen-se a origem, destino e peso respectivamente
    //Força a "volta" do grafo se não for orientado
    
    grafo[u].push_back({u, v, p});
    if (orientado == 0)  // se não for orientado possui uma seta de volta também
    {
        grafo[v].push_back({v, u, p});
    }
}


void prim_lista(list<Aresta>grafo[], int vertices, int start)
{
	bool visitados[vertices];
	int pai[vertices], distancia[vertices], atual; // distanci[i]->Qual foi o menor peso de aresta que chegou até i.
	
	for(int i=0; i<vertices; i++)
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
			int d = it->destino, p = it->peso;
			if(!visitados[d] && p < distancia[d])
			{
				distancia[d] = p;
				pai[d] = atual;	
			}
		}
		
		
		int menor_distancia = INF;
		for(int i=0; i<vertices; i++)
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
    cout << "Arvore Geradora Minima:" << endl;
    for(int i = 0; i < vertices; i++) 
    {
        if(pai[i] != -1) 
        { // Evita mostrar a raiz (não tem pai)
            cout << pai[i] << " " << i << endl;
            peso_mst += distancia[i]; //a menor aresta que liga um vértice i à árvore está salva em distancia[i]. Assim, somando todas essas distâncias (exceto a do vértice inicial), você tem o custo total da AGM.
        }
    }
    cout << "Custo: "<< peso_mst;

	
}

int main()
{
	int vertices, origem, destino, peso, start, orientado;
	
	cin >> vertices >> orientado >> start; // é o vertice inicial
	list<Aresta> grafo[vertices];
	
	cin >> origem >> destino >> peso;
	while(origem != -1 && destino != -1 && peso != -1)
	{
	    cria_aresta(grafo, origem, destino, peso, orientado);
	    cin >> origem >> destino >> peso;
	    
	}
	
	//Isso é só para visualizar o grafo, não faz parte do algoritmo de Prim.
	/*for(int i=0; i<vertices; i++){
		list<Aresta>::iterator it;
		for(it = grafo[i].begin(); it != grafo[i].end(); it++){
			cout << "(";
			cout << it->destino << "," << it->peso;
			cout<< ")";

		}
		cout<<endl;
	
	}
	*/
	prim_lista(grafo, vertices, start);
	return 0;
}
