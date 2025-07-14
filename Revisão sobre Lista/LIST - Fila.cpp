#include <iostream>
#include <list>

using namespace std;

int main()
{
    list <int> lista;
    list <int> ::iterator p;
    int i;
    int x;
    
    for(i = 0; i < 4; i++) {
        cin >> x;
        lista.push_back(x);
    }
    
    // for(p = lista.begin(); p != lista.end(); p++)
    // {
    //     cout << *p << " ";
    // }
    
    while (!lista.empty())  //lista.empty  di enquanto ela não for vazia // é só usado para limpar
    {
        cout << *lista.begin() << " ";
        lista.pop_front(); //remove p elemento na lista
    }
    
    return 0;
}
