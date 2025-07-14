#include <iostream>
#include <list>

#define INF 99999

using namespace std;

struct Aresta 
{
  int u, v, t;
};


void dijkstra_lista(list<Aresta>grafo[], int n, int a, int b) 
{
	bool visitado[n];
	int pai[n], distancia[n], atual;	// Vetores para armazenar as distâncias mínimas e os pais dos vértices
	list <int> pilha_aux;	// Lista auxiliar para armazenar o caminho mínimo
	list <int> :: iterator q; //ponteiro para percorrer essa lista auxiliar
  
    //Inicializando os vetores
	for(int i=0; i<n; i++)
	{
		visitado[i] = false;
    	pai[i] = -1;
    	distancia[i] = INF;
	}
  
	distancia[a] = 0; //distancia do vertice de partida é 0
	atual = a;
  
	while(!visitado[atual])
	{
		visitado[atual] = true;
		list<Aresta>::iterator it; // ponteiro para percorrer o grafo
    
    	// Percorre os vértices adjacentes ao vértice atual
		for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)
		{
			int d = it->v, p = it->t; //var temporariais
			
      // Atualiza as distâncias mínimas e os pais dos vértices adjacentes se necessário
			if(!visitado[d] && distancia[atual] + p < distancia[d]) 
			{
				distancia[d] = distancia[atual] + p;
				pai[d] = atual;
			}
    	}
	// Encontra o vértice com a menor distância mínima que ainda não está na árvore de menor caminho

		int menor_peso = INF;
    
		for(int i=0; i<n; i++) 
		{
			if(!visitado[i] && distancia[i] < menor_peso) 
			{
				menor_peso = distancia[i];
				atual = i;
			}
		}
	}

	atual = b;
	//Insercao dos elementos na pilha e construindo o caminho minimo
	while(atual != a) 
	{
		pilha_aux.push_front(atual);
		atual = pai[atual];
	}

	/*for(q = pilha_aux.begin(); q != pilha_aux.end(); q++) 
	{
		cout << " " << *q;
	}*/

	cout << distancia[b];
}

int main() 
{
	int n, m, u, v, t, a, b;

	cin >> n >> m;//n é o numero de vertices e m o de arestas

	list<Aresta>grafo[n];

	for(int i = 0; i < m; i++)
	{
	    cin >> u >> v >> t;// indicam a origem, destino e peso ,respectivamente, de cada vertice
	    u--;v--;
	    grafo[u].push_back({u,v,t});
	    grafo[v].push_back({v,u,t});
	}
	
    cin >> a >> b; //como se fossem start e end
    a--;b--;
    
    dijkstra_lista(grafo, n, a, b);
  
  /*int i = 0;
    while(!grafo[i].empty()){
        grafo[i].pop_front();                             // Limpeza da lista de adjacência
        i++;
    }
    */
  return 0;
}

