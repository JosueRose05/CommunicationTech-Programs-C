#include <iostream>
#include<cmath>
using namespace std;
const double PI = 3.141592654;

class Cplx{
	public: 
		double r;
		double i;
		
	public:
		Cplx(){
			
		}
		
		Cplx(double _r, double _i){
			r = _r;
			i = _i;
		}
		
		Cplx multi(Cplx cp1, Cplx cp2){
			double rt = (cp1.r*cp2.r) - (cp1.i*cp2.i);
			double it = (cp1.r*cp2.i) + (cp1.i*cp2.r);
			Cplx tmp(rt, it);
			return tmp;
		}
		
		Cplx suma(Cplx cp1, Cplx cp2){
			double rt = (cp1.r+cp2.r);
			double it = (cp1.i+cp2.i);
			Cplx tmp(rt, it);
			return tmp;
		}
};

class Fourier{
	public:
		Cplx vector[1000];
		int t;
		
	public: 
		Fourier(int _t){
			t = _t;	
		}
		
		void llenarVector(){
			double temp;
			int i;
			int lim = t;
			for(i=0; i<lim; i++){
				cout<< "Ingresa el valor real "<<i<<": ";
				cin >> temp;
				vector[i] = Cplx(temp, 0);
			}
		}
		
		void llenarVectorIn(){
			double temp, temp2;
			int i;
			int lim = t;
			//Descomendar para hacerlo manual
			/*
			for(i=0; i<lim; i++){
				cout<< "Ingresa el valor real "<<i<<": ";
				cin >> temp;
				cout<< "Ingresa el valor imaginario "<<i<<": ";
				cin >> temp2;
				vector[i] = Cplx(temp, temp2);
			}
			*/
			double vectorReal[] = {30, 8.7781, -11, -6.778, -4, -6.778, -11, 8.77817};
			double vectorImg[] = {0, 5.292, -3, -6.707, 0, 6.707, 3, -5.29289};
			for(int i=0;i<8;i++){
				vector[i].r = vectorReal[i];
				vector[i].i = vectorImg[i];
			}
			
		}
		
		void calcularFourier(){			
			Cplx matriz[t][t];
			
			int pos=0;
			for(int k=0;k<t;k++){
				for(int n=0;n<t;n++){
					pos = (k*n)%t;
					matriz[k][n].r = cos((pos*(360/t))*PI/180);
					matriz[k][n].i = -sin((pos*(360/t))*PI/180);
				}
			}
			
			for(int k=0;k<t;k++){//imprimimos la matriz
				for(int n=0; n<t; n++){
					cout << matriz[k][n].r;
					cout<<"+j" <<matriz[k][n].i<<" , ";
				}
				cout<<"\n";
			}
			
			double xk, xj;
			for(int k=0; k<t; k++){
				xk = 0;
				xj = 0;
				for(int n=0; n<t; n++){
					xk += vector[n].r * matriz[k][n].r;
					xj += vector[n].r * matriz[k][n].i;
				}
				cout <<k<<": " <<xk <<" + "<<xj<<"j"<<endl;
			}
		}
		
		void calcularFourierIn(){
			int pos;
			Cplx matriz[t][t], m, res(0,0);
			
			for(int k=0;k<t;k++){//Llenamos la matriz
				for(int n=0; n<t; n++){
					pos = (k*n)%t;
					matriz[k][n].r = cos((pos*(360/t))*PI/180);
					matriz[k][n].i = -sin((-pos*(360/t))*PI/180);
				}
			}
			
			for(int k=0;k<t;k++){//imprimimos la matriz
				for(int n=0; n<t; n++){
					cout << matriz[k][n].r;
					cout<<"+j" <<matriz[k][n].i<<" , ";
				}
				cout<<"\n";
			}
			
			for(int k=0;k<t;k++){
				res.r = 0;
				res.i = 0;
				for(int n=0; n<t; n++){
					res = m.suma(res, m.multi(vector[n], matriz[k][n]));
				}
				cout <<k<<": "<< res.r/t <<" "<<res.i/t<<"j\n";
			}
		}
};

int main(){
	int bandera=1, op, tam;
	while(bandera == 1){
		cout <<"Elige una opcion:\n1-Transformada de Fourier\n2-Transformada Inversa de Fourier\n3-Salir\n";
		cin >> op;
		if(op == 1){
			cout << "Ingresa el tamano del vector: ";
			cin >> tam;
			Fourier fourier(tam);
			fourier.llenarVector();
			fourier.calcularFourier();
			bandera = 1;
		} else if(op == 2){
			cout << "Ingresa el tamano del vector: ";
			cin >> tam;
			Fourier fourier(tam);
			fourier.llenarVectorIn();
			fourier.calcularFourierIn();
			bandera = 1;
		} else if(op==3){
			cout << "Bye, pongame 10 :)"<<endl;
			bandera = 0;
		} 
	}
	return 0;
}
