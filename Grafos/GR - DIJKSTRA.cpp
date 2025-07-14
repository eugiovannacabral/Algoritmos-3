#include <iostream>
#include <list>

#define INF 99999

using namespace std;

struct Aresta 
{
  int origem, destino, peso;
};

void cria_aresta(list<Aresta>grafo[], int u, int v, int p, int orientado) 
{	
	// u, v e p referen-se a origem, destino e peso respectivamente
    //Força a "volta" do grafo se não for orientado
	grafo[u].push_back({u, v, p});
	if (orientado == 0) // caso nao seja orientado
	{
    	grafo[v].push_back({v, u, p});
	}
}

void dijkstra_lista(list<Aresta>grafo[], int vertices, int start, int end) 
{
	bool visitado[vertices];
	int pai[vertices], distancia[vertices], atual;	// Vetores para armazenar as distâncias mínimas e os pais dos vértices
	list <int> pilha_aux;	// Lista auxiliar para armazenar o caminho mínimo
	list <int> :: iterator q; //ponteiro para percorrer essa lista auxiliar
  
    //Inicializando os vetores
	for(int i=0; i<vertices; i++)
	{
		visitado[i] = false;
    	pai[i] = -1;
    	distancia[i] = INF;
	}
  
	distancia[start] = 0; //distancia do vertice de partida é 0
	atual = start;
  
	while(!visitado[atual])
	{
		visitado[atual] = true;
		list<Aresta>::iterator it; // ponteiro para percorrer o grafo
    
    	// Percorre os vértices adjacentes ao vértice atual
		for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)
		{
			int d = it->destino, p = it->peso; //var temporariais
			
      // Atualiza as distâncias mínimas e os pais dos vértices adjacentes se necessário
			if(!visitado[d] && distancia[atual] + p < distancia[d]) 
			{
				distancia[d] = distancia[atual] + p;
				pai[d] = atual;
			}
    	}
	// Encontra o vértice com a menor distância mínima que ainda não está na árvore de menor caminho

		int menor_peso = INF;
    
		for(int i=0; i<vertices; i++) 
		{
			if(!visitado[i] && distancia[i] < menor_peso) 
			{
				menor_peso = distancia[i];
				atual = i;
			}
		}
	}

	atual = end;
	//Insercao dos elementos na pilha e construindo o caminho minimo
	while(atual != start) 
	{
		pilha_aux.push_front(atual);
		atual = pai[atual];
	}

	cout << "Menor caminho: " << start;
	for(q = pilha_aux.begin(); q != pilha_aux.end(); q++) 
	{
		cout << " " << *q;
	}

	cout << endl <<"Custo: "<< distancia[end];
}

int main() 
{
	int vertices, origem, destino, peso, start, end, orientado;

	cin >> vertices >> orientado >> start >> end;

	list<Aresta>grafo[vertices];

	cin >> origem >> destino >> peso;
	while(origem != -1 || destino != -1 || peso != -1) 
	{
		cria_aresta(grafo, origem, destino, peso, orientado);
		cin >> origem >> destino >> peso;
	}

  dijkstra_lista(grafo, vertices, start, end);
  
  /*int i = 0;
    while(!grafo[i].empty()){
        grafo[i].pop_front();                             // Limpeza da lista de adjacência
        i++;
    }
    */
  return 0;
}

/*#include <iostream>
#include <list>
#include <climits>

using namespace std;

// Estrutura de dados para representar uma aresta
struct no{
    int v;         // Identificador do vértice adjacente
    int peso;      // Peso da aresta
};

// Função para criar uma aresta entre dois vértices
void cria_aresta(list<no> adj[], int u, int v, int peso, int orientado) {
    no aux;                       // Cria uma variável auxiliar do tipo 'no' para representar a aresta

    aux.v = v;                    // Define o vértice de destino da aresta na variável auxiliar
    aux.peso = peso;              // Define o peso da aresta na variável auxiliar
    adj[u].push_back(aux);        // Adiciona a aresta à lista de adjacências do nó 'u'

    if (orientado == 0) {         // Verifica se o grafo é não orientado
        aux.v = u;                // Define o vértice de origem da aresta na variável auxiliar
        adj[v].push_back(aux);    // Adiciona a aresta à lista de adjacências do nó 'v' (para grafos não orientados)
    }
}

void dijkstra(list<no> adj[], int nVertices, int start, int end){
    int distancia[nVertices], pai[nVertices];                                  // Vetores para armazenar as distâncias mínimas e os pais dos vértices
    int u, v, i;
    int destino, dist, weight;
    bool inTree[nVertices];                                                    // Vetor para marcar se um vértice está na árvore de menor caminho
    list <no> :: iterator p;                                                   // Iterador para percorrer os nós da lista de adjacência
    list <int> pilha_aux;                                                      // Lista auxiliar para armazenar o caminho mínimo

    // Inicialização dos vetores
    for(u = 0; u < nVertices; u++){
        inTree[u] = false;
        distancia[u] = INT_MAX;                                                // Distâncias iniciam com valor máximo
        pai[u] = -1;                                                           // Pais iniciam com valor inválido
    }

    distancia[start] = 0;                                                      // Distância do vértice de partida é 0
    v = start;

    // Algoritmo de Dijkstra
    while(inTree[v] == false){
        inTree[v] = true;

        // Percorre os vértices adjacentes ao vértice atual
        for(p = adj[v].begin(); p != adj[v].end(); p++){
            destino = p->v;
            weight = p->peso;

            // Atualiza as distâncias mínimas e os pais dos vértices adjacentes se necessário
            if(distancia[destino] > distancia[v] + weight){
                distancia[destino] = distancia[v] + weight;
                pai[destino] = v;
            }
        }

        v = 0;
        dist = INT_MAX;

        // Encontra o vértice com a menor distância mínima que ainda não está na árvore de menor caminho
        for(u = 0; u < nVertices; u++){
            if(inTree[u] == false && dist > distancia[u]){
                dist = distancia[u];
                v = u;
            }
        }
    }

    // Construção do caminho mínimo
    for(i = end; i >= start; i = pai[i]){
        pilha_aux.push_front(i);
    }

    // Impressão do caminho mínimo e do custo total
    cout << "Menor caminho: ";
    while(!pilha_aux.empty()){
        cout << *pilha_aux.begin() << " ";
        pilha_aux.pop_front();
    }

    cout << "Custo: " << distancia[end] << endl;
}

int main(){
    int u, v, peso, start, end, i;
    int nVertices, orientado;
    list <no> adj[10];                                  // Declaração da lista de adjacência

    cin >> nVertices >> orientado >> start >> end;      // Leitura do número de vértices, orientação do grafo, vértice de partida e vértice de destino

    cin >> u >> v >> peso;
    while(u != -1 && v != -1 && peso != -1){
        cria_aresta(adj, u, v, peso,  orientado);       // Criação das arestas do grafo
        cin >> u >> v >> peso;
    }

    dijkstra(adj, nVertices, start, end);               // Chamada da função dijkstra para encontrar o menor caminho

    i = 0;
    while(!adj[i].empty()){
        adj[i].pop_front();                             // Limpeza da lista de adjacência
        i++;
    }

    return 0;                                           // Retorna 0 para indicar que o programa foi executado com sucesso
}
*/


