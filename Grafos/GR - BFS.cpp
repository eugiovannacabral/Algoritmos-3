#include <iostream>
#include <list>
using namespace std;

struct Aresta 
{
    int origem, destino, peso;
};

void cria_aresta(list<Aresta>grafo[], int u, int v, int p)
{
    //u origem e v destino , fez isso pois é um grafo não orientdado
    grafo[u].push_back({u,v,p});
    grafo[v].push_back({v,u,p});
}

void bfs(list<Aresta>grafo[], int vertices, int s)
{
    char state[vertices];
    int pai[vertices];
    list<int> Q; // uma pilha
    list<Aresta>::iterator p;
    int u;
    int v;
    
    // Iniciação do das variaveis com o meu v_inicial
    state[s] = 'd';
    pai[s] =-1;
    Q.push_back(s);
    
    for(u = 0; u < vertices; u++)
    {
        if(u != s)
        {
            state[u] = 'u';//nao visitado
            pai[u] = -1;
        }
    }
    
    while(!Q.empty()) //executa até a lista estar vazia
    {
        u = *Q.begin();
        Q.pop_front(); //tira o primeiro elemento da lista
        cout << u << endl;
        
        for(p = grafo[u].begin(); p!= grafo[u].end(); p++)
        {
            v = p->destino;
            cout << u << " " << v << endl;
            
            //verifica se foi visitado
            if(state[v] == 'u')
            {
                //se sim marca como visitado
                state[v] = 'd';
                pai[v] = u;
                Q.push_back(v); //marca que visitou na lista tambem
            }
        }
        state[u] = 'p'; //indica que esta sendo visitado no momento
    }
    
}

int main()
{
    int vertices, v_inicial, origem, destino, peso;
    
    cin >> vertices >> v_inicial; //vertices é a quant de vertcices e v_inicial é aonde u quero começar a olhar
    list<Aresta> grafo[vertices];
    //list<Aresta>::iterator p;
    
    cin >> origem >> destino >> peso;
    while(origem != -1 && destino != -1 && peso != -1)
    {
        cria_aresta(grafo, origem ,destino, peso);
        cin >> origem >> destino >> peso;
    }
    
    bfs(grafo, vertices, v_inicial);
    /*for(int i = 0; i < vertices; i++)
    {
        for(p = grafo[i].begin(); p != garfo[i].end(); ++p)
        {
            cout << i << " "<< p->destino << " ">> p->peso << endl;
        }
    }
    */
    return 0;
}
