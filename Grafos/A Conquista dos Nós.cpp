#include <iostream>
using namespace std;

int main()
{ 
	int n, m, origem, destino;//n é vertice e m é aresta
	
	cin >> n;
	
	bool grafo[n][n];
	
	
	for(int i = 0; i < n; i++)
	{
		for(int j=0; j < n; j++)
		{
			grafo[i][j] = false;
		}
	}		
	
	cin >> m;
	
	for(int i = 0; i < m; i++)
	{
		cin >> origem >> destino; 
		origem--;destino--;//garante que vai estar na linha e coluna correta da matriz isso tudo devido ao vetor começar com 0
		grafo[origem][destino] = true; // como esse grafo nao tem destino ou seja nao tem setinha eu faço ida  e volta
		grafo[destino][origem] = true; // se for um grafico direcionado eu tiro essa opcao
	}	
	
	//for para conseguir mostrar a matriz no final
	for(int i = 0; i < n; i++)
	{
		for(int j=0; j < n; j++)
		{
			cout << grafo[i][j] << " \t";
		}
		cout << endl;
	}	
	
	return 0;
}
