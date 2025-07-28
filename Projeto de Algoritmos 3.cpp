#include <iostream>
#include <list>
#include <string>
#include <math.h>
#include <locale.h>
using namespace std;

//Trabalho sobre a crição de um dicionário de uma lingua inventada, 
//criando um vetor e uma árvore binária para armazenar os dados dessa palavra, 
//além de outras funções que realizam a busca de tradução, inserção, calculo de similariedade etc

struct ponto
{
	float x, y, z; 																// Coordenadas da palavra
};

struct dados
{
	string nome; 																// Nome da palavra
	list<string>significado;												    // Significado da palavra
	list<string>sinonimos;														// Lista de sinonimos
	ponto coordenada;															// Coordenadas da palavra
	int ID; 																	// Identificador da palvra
};

struct Aresta																	// Estrutura de dados para representar uma aresta
{
	int origem, destino;
	string peso;
};

struct node 																	// Estrurura de criação dos nós da árvore
{
	dados palavra;
	node *esquerda;
	node *direita;
};

void cria_aresta(list<Aresta>grafo[], int u, int v, string p)					//Função que cria uma aresta
{
	if (v == u)
		grafo[u].push_back({u, v, p}); 											// Se não tiver um sinonimo a palavra possui a mesma origem e destino
	
	else 
	{
		grafo[u].push_back({u, v, p});											//Caso a palavra tenha sinonimo , terá origem e detino
		grafo[v].push_back({v, u, p});	
	}	
}

//--------------------------Funções de Inserção---------------------------------
void inserir_alfabetica(node* &raizAlfabetica, dados novaPalavra) 				//Função que insere as palavras na árvore já respeitando a ordem alfabética
{
	if (raizAlfabetica == NULL) 												//Caso a raiz esteja vazia, cria-se um novo nó adcionando a palavra nele, criando também seus dois filhos a esquerda e a direita
	{
		raizAlfabetica = new node;
		raizAlfabetica->palavra = novaPalavra;
		raizAlfabetica->esquerda = NULL;
		raizAlfabetica->direita = NULL;
	}
	
	else																		//Se já está ocupada(não NULL) verifica para qual lado a palavra vai ser armazenada(esquerda as menores e a direita maiores ou iguais, tudo por ordem alfabetica)
	{
		if (novaPalavra.nome < raizAlfabetica->palavra.nome)
			inserir_alfabetica(raizAlfabetica->esquerda, novaPalavra);
		else
			inserir_alfabetica(raizAlfabetica->direita, novaPalavra);
	}
}

void inserir_por_tamanho(node * &raizTamanho, dados novaPalavra)				//Função que insere as palavras em uma nova árvore pelo tamanho das  palavras
{
	if(raizTamanho == NULL)														//Caso a raiz esteja vazia, cria-se um novo nó adcionando a palavra nele, criando também seus dois filhos a esquerda e a direita
	{
		raizTamanho = new node;
		raizTamanho -> palavra = novaPalavra;
		raizTamanho -> esquerda = NULL;
		raizTamanho -> direita = NULL;
	}
	
	else																		// Se o nó já existe, decide se insere à esquerda (menores) ou à direita (maiores ou iguais), seguindo ordem alfabética
	{
		if(novaPalavra.nome.size() < raizTamanho -> palavra.nome.size())        //Compara o tamanho(numero de caracteres) da nova palavra (novaPalavra.nome.size()) com o tamanho da palavra que já está no nó atual
			inserir_por_tamanho(raizTamanho -> esquerda, novaPalavra);
		else
			inserir_por_tamanho(raizTamanho -> direita, novaPalavra);
	}
}
//------------------------------------------------------------------------------

void adicionaSignificado(node* raiz, string& nome, string& significado) 		//Adiciona significado diretamente na árvore
{
    if (raiz == NULL)
        return;

    if (raiz->palavra.nome == nome) 
	{
        raiz->palavra.significado.push_back(significado);						//Adiciona o significado no vetor de significados da palavra
        return;
    }

    if (nome < raiz->palavra.nome)
        adicionaSignificado(raiz->esquerda, nome, significado);
    else
        adicionaSignificado(raiz->direita, nome, significado);
}
	
void cadastro(list<Aresta>grafo[], dados palavra[], int &nVertices, node * &raizAlfabetica, node * &raizTamanho)// Função de cadastros de uma palavra 
{
	int i = 0;
	string escolha = "Sim";
	int origem, destino;
	string peso;
	string aux1, aux2;
	string resposta1 = "Sim", resposta2;

	while(escolha == "Sim" || escolha == "sim")									//Leitura das caracteristicas das palavras
	{
		cout << "Digite o nome da palavra: " << endl;
		getline(cin >> ws, palavra[i].nome);
		cout << "Digite o número de ID da palavra:  " << endl;
		cin >> palavra[i].ID;
		cout << "Digite as coordenadas da palavra: " << endl;
		cin >> palavra[i].coordenada.x;
		cin >> palavra[i].coordenada.y;
		cin >> palavra[i].coordenada.z;
																				//Chamada das funções que inserem por ordem alfabetica e por ordem crescente
		inserir_alfabetica(raizAlfabetica, palavra[i]);
		inserir_por_tamanho(raizTamanho, palavra[i]); 							
		
		i++; 																	// Contador para o looping do for
		nVertices++; 															// Contador a quant de palavras
		cout << endl << "Deseja cadastra mais alguma palavra? " << endl;
		cin >> escolha;
	}
//----------------------------------------------------------------------------- //Montagem do grafo
	cout << "Vamos montar o cadastro do grafo(digite '-1 -1 end' caso queira parar): " << endl;
	cin >> origem >> destino;
	
	cout << "Digite o significado: " << endl;
	getline(cin >> ws, peso);

	while (origem != -1 && destino != -1 && peso != "end")
    {
        cria_aresta(grafo, origem, destino, peso);								//Chama a função para criar uma aresta

        palavra[origem].significado.push_back(peso);							//Atualiza o significado no vetor
        palavra[destino].significado.push_back(peso);

        adicionaSignificado(raizAlfabetica, palavra[origem].nome, peso);		//Atualiza o significado na árvore
        adicionaSignificado(raizAlfabetica, palavra[destino].nome, peso);

        cin >> origem >> destino;
        getline(cin >> ws, peso);
    }

}

//----------------------------Funções de Listagem-------------------------------
void listar_significado(list<Aresta>grafo[], dados palavra[], int nVertices)	//Função que lista os significados das palavras
{
	string busca; 																//Var que  recebe o nome da palavra que se deseja pesquisar
	bool achou = false;															//Var que auxilia na procurada de "busca"
	list<Aresta>::iterator it;

	cout << "Digite o nome da palavra que deseja saber os significados: " << endl;
	getline(cin >> ws, busca);

	for (int i = 0; i < nVertices; i++) 										//Varre o vetor de palavras
	{
		if (palavra[i].nome == busca)											//Verefica se encontrou o nome da palavra desejada
		{
			achou = true;

			cout << endl << "Significados(s): " << endl;						
			for(it = grafo[i].begin(); it != grafo[i].end(); it++)  			//Varre a lista de significados dessa palavra para apontar para o peso da aresta que é aonde estará armazenado os eu significado
				cout << it -> peso << endl;
		}

	}
	
	if(!achou)																	//Se achou for falso, a palavra não foi encontrada
		cout << "Palavra não encontrada" << endl;
}

void listar_sinonimos(list<Aresta>grafo[], dados palavra[], int nVertices)		//Função para mostrar os sinonimos de uma palavra
{
	int busca; 	
	int totalSinonimos = 0;																//ID da palavra que se deseja pesquisar
	bool achou = false;															//Var que auxilia na procurada de "busca"
	list<Aresta>::iterator it;

	cout << "Digite o ID da palavra que deseja saber os sinônimos: " << endl;
	cin >> busca;

	for (int i = 0; i < nVertices; i++) 										// Varre o vetor de palavras
	{
		if (palavra[i].ID == busca) 											//Verifica se a palavra atual do vetor é a palavra a ser pesquisada
		{
			achou = true;
			cout << endl << "Sinônimos(s):" << endl;
									  
			for(it = grafo[busca].begin(); it != grafo[busca].end(); it++)  	//Varre a lista de significados diretamente pelo ID dessa palavra
			{
				if (it->destino != busca)  										// Só executa se o destino for diferente da própria palavra
                {
                    for (int j = 0; j < nVertices; j++)							//Para cada vizinho encontrado (para cada aresta), percorre o vetor de palavras de novo, para descobrir o nome da palavra de destino
                    {
                        if (palavra[j].ID == it->destino) 						//Se o ID da palavra no vetor for igual ao ID de destino da aresta, exibe o nome da palavra, ou seja, o sinônimo
                        {
							 cout << palavra[j].nome << endl;
                             totalSinonimos ++;
						}
                    }
                }
			}
			
			 if (totalSinonimos == 0)											//Se a palavra não tem sinonimo
            {
                cout << "A palavra " << palavra[i].nome << ", ID = " << palavra[i].ID << ", não tem sinônimos." << endl;
            }
            
		}

	}
	
	if(!achou)
		cout << "Palavra não encontrada" << endl;
}

void listar_ordem_alfabetica(node * raizAlfabetica)								//Função para ordenar a saída das palavras em ordem alfabética
{
	if (raizAlfabetica != NULL)													//Se a raiz nao estiver vazia, ele começa pelo lado esquerdo (letras antecedentes)
	{																			//Depois pelo lado direito (letras sucessoras)
		listar_ordem_alfabetica(raizAlfabetica -> esquerda);
		cout << raizAlfabetica -> palavra.nome << endl;
		listar_ordem_alfabetica(raizAlfabetica -> direita);
	}
}

void listar_ordemTamanho(node * raizTamanho) 											//Função para ordenadar pelo seu tamanho de forma crescente 
{
	if(raizTamanho != NULL)
	{
		listar_ordemTamanho(raizTamanho -> esquerda);
		cout << raizTamanho -> palavra.nome << endl;
		listar_ordemTamanho(raizTamanho -> direita);
	}
}

//------------------------------------------------------------------------------
node* busca(node *raizAlfabetica, string info)
{
    list<string>::iterator it; 													//Iterador que percorre a lista de significados da palavra
    string ultimo = ""; 														//Variavel que vai guardar o ultimo significado impresso (começa vazio)

    node* atual = raizAlfabetica; 												//Busca inicia na raiz

    while (atual != NULL) 														//Roda enquanto nao chegar no fim da arvore
    {
        if (info == atual->palavra.nome) 										//Se encontrar a palavra na arvore...
        {   
            cout << "Traduções: " << endl; 										//Mostra as traducoes

            for (it = atual->palavra.significado.begin(); it != atual->palavra.significado.end(); ++it)
            {
                if (*it != ultimo)  											//Só imprime se for diferente do anterior
                {
                    cout << " - " << *it << endl;
                    ultimo = *it; 												//Atualiza a variavel "ultimo" com esse significado
                }
            }

            return atual;
        }

        if (info < atual->palavra.nome) 										//Se a palavra buscada for alfabeticamente menor vai para a esquerda
            atual = atual->esquerda;
        else 																	//Senão vai para a direita
            atual = atual->direita;
    }

    cout << "Palavra não encontrada!" << endl;
    return NULL;
}


//---------------------------Funções de remoção---------------------------------
node* remover_sucessor(node*& raiz) 											//Função auxiliar para a função de remoção por ordem alfabetica remover um nó que possui dois filhos
{
    if (raiz->esquerda == NULL) 
	{
        node* temp = raiz;
        raiz = raiz->direita;
        return temp;
    } 
	else 
        return remover_sucessor(raiz->esquerda);
}

bool remover(node*& raiz, string nome) 											//Função para remover a palavra na ordem alfabetica
{
    if (raiz == NULL) return false;

    if (nome < raiz->palavra.nome) 
        return remover(raiz->esquerda, nome);
    
	else if (nome > raiz->palavra.nome)
        return remover(raiz->direita, nome);
    
    else 
	{		
		node* temp = raiz;												        //Se não tem filho há esquerda
        if (raiz->esquerda == NULL) 
            raiz = raiz->direita;											    //Conecta o pai diretamente ao filho da direita
		else if (raiz->direita == NULL) 										//Se não tem há direita
            raiz = raiz->esquerda;												//Conecta o pai diretamnete ao filho da direita
		else 
		{
            node* sucessor = remover_sucessor(raiz->direita);					//Para quando o nó tem dois filhos
            raiz->palavra = sucessor->palavra;									//Substitui o valor do nó atual pelo menor da subárvore à direita
            delete sucessor;													//Deleta esse menor nó
            return true;
        }
        delete temp;
        return true;
    }
}


node* remover_sucessor_tamanho(node*& raizTamanho) 								//Função auxiliar para a função de remoção por ordem alfabetica remover um nó que possui dois filhos
{							
    if (raizTamanho->esquerda == NULL) {
        node* temp = raizTamanho;
        raizTamanho = raizTamanho->direita;
        return temp;
    } else {
        return remover_sucessor_tamanho(raizTamanho->esquerda);
    }
}

bool remover_por_tamanho(node*& raizTamanho, string nome) 						//Função para remover a palavra por ordem de tamanho
{
    if (raizTamanho == NULL) 
		return false;

    if (nome.length() < raizTamanho -> palavra.nome.length()) 
        return remover_por_tamanho(raizTamanho->esquerda, nome);
	else if (nome.length() > raizTamanho->palavra.nome.length()) 
        return remover_por_tamanho(raizTamanho->direita, nome);
	else {
        if (raizTamanho->palavra.nome != nome) {
   																		        // Mesmo tamanho, mas nomes diferentes. Verifica ambos os lados.
            return remover_por_tamanho(raizTamanho->esquerda, nome) || remover_por_tamanho(raizTamanho->direita, nome);
        }

        node* temp = raizTamanho;
        if (raizTamanho->esquerda == NULL) 
            raizTamanho = raizTamanho->direita;
		else if (raizTamanho->direita == NULL) 
            raizTamanho = raizTamanho->esquerda;
		else 
		{
            node* sucessor = remover_sucessor_tamanho(raizTamanho->direita);
            raizTamanho->palavra = sucessor->palavra;
            delete sucessor;
            return true;
        }
        delete temp;
        return true;
    }
}


void destruct(node * & raiz){													//Liberar toda a memória alocada dinamicamente pelos nós da árvore, evitando vazamentos de memória
    if(raiz != NULL){
        destruct(raiz->esquerda);
        destruct(raiz->direita);
        delete raiz;
    }
}
//------------------------------------------------------------------------------
																				//Função que calcula a similariedade de duas palavras
void calcular_similaridade(dados palavra[], int nVertices, string Palavra1, string Palavra2) 
{
    ponto p1, p2;																//Vars que recebem as coordenadas da palavra
    bool encontrou1 = false, encontrou2 = false;

    for (int i = 0; i < nVertices; i++)											//Caso as palavras existam no sistema, armazena as coordenadas dela
    {
        if (palavra[i].nome == Palavra1)
        {
            p1 = palavra[i].coordenada;
            encontrou1 = true;
        }

        if (palavra[i].nome == Palavra2)
        {
            p2 = palavra[i].coordenada;
            encontrou2 = true;
        }
	}

    if (!encontrou1 || !encontrou2)												//Caso não tenha encontrado alguma palavra
    {
        cout << "Uma ou ambas as palavras não foram encontradas!" << endl;
        return;
    }
																				//Cálculo da distancia entre dois pontos
    float similaridade = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));

    cout << "Distância entre as palavras: " << similaridade << endl;
    
	if(Palavra1 == Palavra2)
	{
		cout << "A palavra é a mesma" << endl;
	}else{																		//Classificando a similariedade por faixa de distância
		if(similaridade <= 2)
        	cout << "As palavras são muito similares" << endl;
    	else if(similaridade <=5)
    		cout << "As palavras são similares" << endl;
    	else if (similaridade <= 8)
        	cout << "As palavras são pouco similares" << endl;
    	else
        	cout << "As palavras não são similares" << endl;
	}
}

//------------------------------------------------------------------------------ 
int main()
{
	setlocale(LC_ALL, "Portuguese");											//Permite palavras com acento
	
	int nVertices = 0;           					 							// Declaração do número de vértices que é a quant de palavras
	list<Aresta>grafo[50];                   		 							// Lista de adjacência para armazenar as arestas do grafo																	//Contador
	list<Aresta>::iterator q;													// Iterador para lista do tipo Aresta
	dados palavra[50];															//Vetor do tipo dados(struct), armazena as informacoes das palavras
	int op; 																	//Var que responsavel por receber a opcao escolhida pelo usuario
	node * raizAlfabetica = NULL;												//Nó raiz para função de ordem alfabetica
	node * raizTamanho = NULL;													// Nó raiz para função de ordem por tamanho
	
	string Palavra1, Palavra2;													//Vars que recebem as palavras que o usuario deseja verificar a similariedade
																				
	bool continua = true;														//Var boleana que auxilia na repeticicao do while, enquanto ele for verdadeiro
	
	cout << "Dicionário: " <<endl;
	while (continua)															// Looping que permite voltar pra seleção de opções
	{																			//Menu com as opcoes do dicionario
		cout << endl << "1. Cadastrar palavra" << endl;
		cout << "2. Listar significado" << endl;
		cout << "3. Listar sinônimos" << endl;
		cout << "4. Listar palavras em ordem alfabética" << endl;
		cout << "5. Listar palavras por ordem de tamanho" << endl;
		cout << "6. Buscar palavra" << endl;
		cout << "7. Remover palavra" << endl;
		cout << "8. Calcular similaridades entre duas palavras" << endl;
		cout << "9. Fechar o dicionário" << endl;
		cout << endl << "Selecione uma opcao: " << endl;

		cin >> op;

		switch (op)
		{
			
			case 1:																//Função para o cadastro das palavras
				cadastro(grafo, palavra, nVertices, raizAlfabetica, raizTamanho);
				break;
	
				
			case 2:																//Função que lista os significados
				listar_significado(grafo, palavra, nVertices);
				break;
	
				
			case 3:																//Função que mostra os sinônimos da palavra
				listar_sinonimos(grafo, palavra, nVertices);
				break;
	
			
			case 4:																//Função que exibe uma lista das palavras em ordem alfabética
				listar_ordem_alfabetica(raizAlfabetica);													
				break;
	
			case 5:																//Função que exibe uma lista das palavras por ordem de tamanho					
			{
				cout << endl << "Palavras em ordem crescente de tamanho: " << endl << endl;
				listar_ordemTamanho(raizTamanho); 
				break;
			}																	
	
			case 6:																//Função que busca a tradução através da árvore
			{
				string pesquisa;												//Palavra que o usuario deseja saber a tarcao
				cout << "Digite a palavra que deseja saber a traducao: ";
    			getline(cin >> ws, pesquisa);																									 															// Busca da tradução de uma palavra cadastrada								
				busca(raizAlfabetica, pesquisa); 
				break;
            }	
			case 7:																//Função que remove uma palavra cadastrada
			{
				string nomeRemover;												//Palavra que o usuario deseja remover
				
                cout << "Digite o nome da palavra que deseja remover: ";
                getline(cin >> ws, nomeRemover);

                bool removido1 = remover(raizAlfabetica, nomeRemover);
                bool removido2 = remover_por_tamanho(raizTamanho, nomeRemover);

                if (removido1 || removido2)
                    cout << "Palavra removida com sucesso!" << endl;
                else
                    cout << "Palavra nao encontrada." << endl;
                 break;
			}

			case 8:																//Função que calcula a da similariedade entre as palavras
			{
				
				cout << "Digite as duas palavras que você deseja calcular a similaridade" << endl;
			    getline(cin >> ws, Palavra1);
			    getline(cin >> ws, Palavra2);
			    
				calcular_similaridade(palavra, nVertices, Palavra1, Palavra2);
				
				break;
			}
			
			case 9:																// Termina o programa
				continua = false;
				break;
		}
	}

	return 0;
}
