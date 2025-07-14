#include<iostream>
#include<list>
using namespace std;

/*struct no
{
    int v; // vertice adjacente
    int peso; // peso da aresta
};*/

struct Aresta
{
    int origem, destino, peso;
};

// u = origem
// v = destino
void cria_aresta(list<Aresta>grafo[], int u, int v, int p, int orientado)
{
    //Força a "volta" do grafo se não for orientado
    grafo[u].push_back({u, v, p});
    if (orientado == 0) {
        grafo[v].push_back({v, u, p});
    }
}

int main()
{
    int vertices, arestas, origem, destino, peso, orientado; //vertice = no
	cin>>vertices;
	list<Aresta> grafo[vertices];
	list <Aresta>::iterator p;
    
    cin >> orientado; //para saber se é orientado ou não
    
    cin >> origem >> destino >> peso;
    while (origem != -1 && destino != -1 && peso != -1) {
        //Chama a função para receber a origem destino e peso
        cria_aresta(grafo, origem, destino, peso, orientado);
        cin >> origem >> destino >> peso;
    }
    
    // Sair com a lista
    for (int i = 0; i < vertices; i++) {
        for (p = grafo[i].begin(); p != grafo[i].end(); ++p) {
            // O ponteiro aponta para os elementos da lista, as inf do vertice e tudo que esta ligado a ele
            cout << i << " " << p->destino << " " << p->peso << endl;
        }
    }
    
    // Limpar a locação da memória dinâmica
    // int k = 0;
    // while (!grafo[k].empty()) {
    //     grafo[k].pop_front();
    //     k++;
    // }
    
    
    return 0;
}
