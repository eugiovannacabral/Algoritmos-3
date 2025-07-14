#include <iostream>
#include <cmath>
using namespace std;

struct ponto
{
	int x;
	int y;	
};

/*double area_triangulo(
	Ponto a, 
	Ponto b, 
	Ponto c
){
	return 
		((a.x*b.y) - (a.y*b.x) + 
		(a.y*c.x) - (a.x*c.y) + 
		(b.x*c.y) - (b.y*c.x))/2.0;  
}
*/
double distancia(ponto c, ponto d)      //para achar o diametro
{
    return round(sqrt((c.x - d.x)*(c.x - d.x) + (c.y - d.y)*(c.y - d.y))); 
}

/*int orientacao(Ponto a, Ponto b, Ponto c){
	double area = area_triangulo(a,b,c);
	if(area > 0){
		return 1; 
	} else if(area < 0){
		return -1; 
	} else {
		return 0; 
	}
}
*/

int main()
{
    ponto a, b, c, d;       //leitura dos pontos
    
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
    cin >> d.x >> d.y;
    
    //Mas na verdade é pra fazer a distancia entre dois pontos em todos os casos
    cout << abs(b.x - a.x) << endl; //abs é modulo //espessura
    cout << distancia(c, d) << endl;// diametro
    cout << abs(a.y - c.y) << endl;//altura
    
    return 0;
}
