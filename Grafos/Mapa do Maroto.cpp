#include <iostream>
#include <list>

using namespace std;

struct Aresta
{
    int origem, destino, peso;
};

void cria_aresta(list<Aresta>grafo[], int origem, int destino, int peso, int orientado)
{
    grafo[origem].push_back({origem, destino, peso});
    if(orientado == 0)
    {
        grafo[destino].push_back({destino, origem, peso});
    }
}

int main()
{
    int vertices, orientado, origem, destino, peso;
    
    cin >> vertices >> orientado;
    list<Aresta>grafo[vertices];
    list<Aresta>:: iterator p;
    
    cin >> origem >> destino >> peso;
    while(origem != -1 && destino != -1 && peso != -1)
    {
        cria_aresta(grafo, origem, destino, peso, orientado);
        cin >> origem >> destino >> peso;
        
    }
    
    for(int i = 0; i < vertices; i++)
    {
        for(p = grafo[i].begin(); p != grafo[i].end(); p++)
        {
            cout << p -> origem << " "<< p -> destino << " " <<  p-> peso << endl;
        }
       // cout << endl;
    }
    

    return 0;
}
