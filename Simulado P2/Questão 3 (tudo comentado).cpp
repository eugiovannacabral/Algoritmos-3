#include <iostream>
#include <cmath>
using namespace std;

// Funções para Árvore Binária de Busca ---------------------------------------

struct dados//dados das tortas
{
    int pf; //preco final
    int key;//codigo
};

struct Node 
{
	dados torta;
	Node * right;           //ponteiro para os filhos
	Node * left;
} ;

struct ponto
{
    int x, y;
};

double distancia(ponto p1, ponto p2)
{
    return round(sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)));
}

void insert(Node *& curr, dados torta)                                          //é um ponteiro por referência, ou seja, permite alterar o ponteiro original 
                                                                                //que está na função chamadora (como root).
{	
	if(curr == NULL)                                                            //cria um novo nó caso a posição esteja vazia
	{
		curr = new Node;
		curr->torta = torta;                                                    //inseri os dados da torta
		curr->right = NULL;                                                     //cria seus filhos da esquerda e direita vazios
		curr->left = NULL;
	}else {                                                                     //caso a raiz já esteja ocupada
		if(torta.pf >= curr->torta.pf)                                          // comparar o pf da nova torta com o pf do nó atual para decidir para que lado seguir
		{
			insert(curr->right, torta);                                         //da direita caso o valor seja maior ou igual 
		} else if(torta.pf < curr->torta.pf){
			insert(curr->left, torta);                                          //da esuqerda os menores
		}		
	}	
}

/*Node * search(Node * curr, KeyType key)
{
	if(curr == NULL)                                                            //Se a árvore ou subárvore acabou (nó inexistente), retorna NULL → valor não foi encontrado.
		return NULL;
	if(key == curr->data.key){                                                  // a info foi encontrada na raiz fazendo o ponteiro a ponta para esse nó
		return curr;
	} else {
		if(key > curr->data.key){                                               //Se o valor procurado é maior que o atual, chama a função recursivamente no filho direito
			return search(curr->right, key);
		} else if(key < curr->data.key){                                        //Se o valor procurado é menor que o atual, chama a função recursivamente no filho esquerda
			return search(curr->left, key);
		}
	}
	return NULL;
}*/

void show_ordered(Node * curr, int pfmin, int pfmax)                            //  Percuro in-order
{                                                                               //Antes de mostrar o valor do nó atual, a função chama recursivamente o lado esquerdo.
        if(curr->left != NULL)                                                  //Isso significa que os nós com valores menores serão visitados primeiro
		    show_ordered(curr->left, pfmin, pfmax);
		if(curr->torta.pf >= pfmin && curr->torta.pf <= pfmax)
	        cout << curr->torta.key << ":" << curr->torta.pf << endl;
	    if(curr->right != NULL)                                                 //Depois que aqui vai mostrar os valores maiores
		    show_ordered(curr->right, pfmin, pfmax);
}

/*Node * disconnect_lesser(Node *& curr){                                       //Isso é para caso Um nó tenha 2 filhos
	Node * aux = curr;                                                          //salva o menor nó
	if(aux->left == NULL){ 	                                                    //Chegamos no menor valor da subárvore (nó mais à esquerda).
		curr = curr->right;                                                     //remove o menor nó da árvore e liga o pai dele diretamente ao seu filho direito (caso exista).
		return aux;			                                                    //devolve o menor nó encontrado para ser usado na função remove
	} else {				
		return disconnect_lesser(curr->left);                                   //Se ainda existe filho à esquerda, continua descendo até achar o menor nó.
	}
}

int remove(Node *& curr, KeyType old_key){
	if(curr == NULL){
		return 0;                                                               //Nó não encontrado
	}
	Node * aux;
	if(curr->data.key == old_key)
	{                                                                           //Achou a info a ser removida
		aux = curr;		
		                                                                        //Para quando o nó atual só tem um filho(esquerda ou direita)
		if(curr->left == NULL){                                                 //Se não tem filho há esquerda
			curr = aux->right;                                                  //Conecta o pai diretamente ao filho da direita
		} else if(curr->right == NULL){                                         //Se não tiver filho há direita
			curr = aux->left;                                                   //Conecta o pai diretamente ao filho da esquerda
			                                                
		} else {                                                                //Nó com dois filhos
			aux = disconnect_lesser(curr->right);                               //Substitui o valor do nó atual pelo menor da subárvore à direita.    
			curr->data = aux->data;                                             //Remove esse menor da árvore (feito pela repoint_less).
		}		
		delete aux;
		return 1;		
	} else {                                                                    //caso não tenha achado a info contnua descendo pela arvore ou pelo lado esquerdo ou direito
		if(old_key > curr->data.key){
			return remove(curr->right, old_key);
		} else if(old_key < curr->data.key) {
			return remove(curr->left, old_key);
		}
	}
	return 0;                                                                   //A função recebe o ponteiro curr por referência (&) para que o valor do ponteiro original (como root) também seja alterado para NULL.

                                                                                //Assim, ao final da execução, root será NULL, indicando que a árvore foi completamente destruída.
}
*/

void destruct(Node *& curr){                                                    //Liberar toda a memória alocada dinamicamente pelos nós da árvore, evitando vazamentos de memória.

	if(curr->left != NULL)                                                      //Destroi todos os filhos da esquerda
		destruct(curr->left);
	if(curr->right != NULL)                                                     //Destroi todos os da direita
	   	destruct(curr->right);
	delete curr;                                                                //Destroi o atual
	curr = NULL;                                                                //Garante que foi destruido
	return;
}

// ----------------------------------------------------------------------------
int main()
{
    int n;
    int p;                        // peso da torta
    int em;                      // espessura da torta
    int di;                      // diametro da torta
    int al;                     // altura da torta
    int pfmin, pfmax;
    dados t;                  // var recebe o preco final e o codigo de cada torta
    ponto a, b, c, d;
    Node * root = NULL;
    
    cin >> n;                // quant de tortas
    
    for(int i = 0; i < n; i++)
    {
        cin >> a.x >> a.y;
        cin >> b.x >> b.y;
        cin >> c.x >> c.y;
        cin >> d.x >> d.y;
        cin >> p;
        
        em = abs(distancia(a,b));
        di = abs(distancia(c,d));
        al = abs(distancia(a,c));
        
        t.pf = ((em * p * al) + di + al);
        t. key = i;
        insert(root, t);
    }
    
    cin >> pfmin >> pfmax;
    
    show_ordered(root, pfmin, pfmax);
    destruct(root);
    
    return 0;
}

/*

double area_triangulo(
	Ponto a, 
	Ponto b, 
	Ponto c
){
	return 
		((a.x*b.y) - (a.y*b.x) + 
		(a.y*c.x) - (a.x*c.y) + 
		(b.x*c.y) - (b.y*c.x))/2.0;  
}


int orientacao(Ponto a, Ponto b, Ponto c){
	double area = area_triangulo(a,b,c);
	if(area > 0){                                                               //ponto c está à esquerda da reta ab (orientação anti-horária)
		return 1; 
	} else if(area < 0){                                                        //ponto c está à direita da reta ab (orientação anti-horária)
		return -1; 
	} else {                                                                    //pontos estão alinhados
		return 0; 
	}
}

void levels(Node * curr)
{
    if(curr == NULL)
        return;
        
    list<Node*> fila_visitacao;
    fila_visitacao.push_back(curr);
    while(!fila_visitacao.empty())
    {
        Node * visitado =fila_visitacao.front();
        cout << visitado->info.codigo<< ":" << visitado->info.preco_final<< endl;
        if(curr->left != NULL)
            fila_visitacao.push_back(visitada->left);
        if(curr->right != NULL)
            fila_visitacao.push_back(visitado->right);
        fila_visitacao.pop_front();
    }
}
                                                                                //Fazendo uma busca por largura(BFS), ela busca por níveis e precsa indicar um primeiro nó para começar
void levels(Node * curr)
{                                                                           
    if(curr == NULL)                                                            // Se a árvore estiver vazia, não faz nada
        return;
        
    list<Node*> fila_visitacao;                                                 // Cria uma fila para armazenar os nós a serem visitados
    fila_visitacao.push_back(curr);                                             // Insere o nó raiz na fila (primeiro nó a ser visitado)
    
    while(!fila_visitacao.empty())                                              // Enquanto ainda houver nós na fila
    {
        Node * visitado = fila_visitacao.front();                               // Pega o primeiro nó da fila (nó atual a ser visitado)
        
        cout << visitado->info.codigo << ":" << visitado->info.preco_final << endl;     // Exibe os dados do nó (neste caso: código e preço final da torta)
        
        if(visitado->left != NULL)                                              // Se o nó tiver filho à esquerda, adiciona o filho esquerdo na fila
            fila_visitacao.push_back(visitado->left);
        
        if(visitado->right != NULL)                                             // Se o nó tiver filho à direita, adiciona o filho direito na fila
            fila_visitacao.push_back(visitado->right);
        
        fila_visitacao.pop_front();                                             // Remove o nó visitado da fila (pois já foi processado)
    }
}



*/
