#include <iostream>
#include <list>

using namespace std;

bool encontrar(list<int>lista, int x)
{
    list<int>::iterator p;
    
    for(p = lista.begin(); p != lista.end(); p++) {
        if (*p == x) {
            return true;
        }
    }
    
    return false;
}

int main()
{
    list<int>lista;
    int n, x;
    
    cin >> n;
    while(n != 0)
    {
        lista.push_back(n);
        cin >> n;
    }
    
    cin >> x;
    
    if (encontrar(lista, x)) {
        cout << "Encontrado" << endl;
    } else {
        cout << "Nao encontrado" << endl;
    }
    
    return 0;
}
