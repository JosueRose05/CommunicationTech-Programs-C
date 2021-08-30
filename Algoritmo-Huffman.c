//Codigo de Huffman, Josue Rose
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<math.h>

typedef struct{
	char caracter;
	int frec;
	char label[200];
	char cod[50];
	char rama[2];//en rama se pone que numero lo conecta con el padre, 0 o 1
}Caracter;

typedef struct{
	Caracter caracter;
	struct Nodo *padre;
	struct Nodo *izq;
	struct Nodo *der;
}Nodo;

Caracter list[1000]; 
int cont = 0;//Con esto manejamos la posicion de lits[] a lo largo del programa
int numb, numbn=0;
Nodo *raiz = NULL;

Nodo *nodosOrg[1000];
Nodo *ln[1000];
Nodo *hijos[1000];

int buscar(char t){
	int a;
	for(a=0;a<50;a++){
		if(list[a].caracter != NULL){
			if(t == list[a].caracter){
				return false;
			}
		}		
	}
	return true;
}

void BurbujaMej(int tamanio){
	bool b = false;
	int n,m;
	char auxiliar;
	int auxiliari;
	char auxiliarl[20]=" ";	
	for(n=1;n<tamanio;n++){
		b = false;
		for(m=0;m<tamanio-n;m++){
			if(list[m].frec > list[m+1].frec){
				auxiliar = list[m+1].caracter;
				auxiliari = list[m+1].frec;
				strcpy (auxiliarl, list[m+1].label);
				
				list[m+1].caracter = list[m].caracter;
				list[m+1].frec = list[m].frec;
				strcpy (list[m+1].label, list[m].label);

				list[m].caracter = auxiliar;
				list[m].frec = auxiliari;
				strcpy (list[m].label, auxiliarl);

				b = true;
			}
		}	
		if(!b)
			break;
	}//Fin for principal
}

Nodo* crearNodo(Caracter caracter){
	Nodo *aux = malloc(sizeof(Nodo));//Memory allocation
	
	aux->caracter = caracter;
	aux->izq = NULL;
	aux->der = NULL;
	aux->caracter.rama[0] = "";
	return aux;
}

void generarArbol(int tam){	
	int n=0;
	Nodo *aux = malloc(sizeof(Nodo));
	if(tam>2){//Si hay menos de dos, generamos el nodo padre en el else
		Nodo *p1 = ln[0];//p1 y p2 son los nodos de control, los mandaremos a algun lado para hacer el nodo padre si son los finales, izq
		Nodo *p2 = ln[1];//der
		int a1=0, a2=1;
		int aux;
		printf("Iniciamos con %s %d y %s %d \n", p1->caracter.label, p1->caracter.frec, p2->caracter.label, p2->caracter.frec);
		for(n;n<tam;n++){
			if(ln[n]->caracter.frec < p1->caracter.frec && ln[n]->caracter.caracter != p2->caracter.caracter){
				p1 = ln[n];
				a1 = n;
			}else if(ln[n]->caracter.frec < p2->caracter.frec && ln[n]->caracter.caracter != p1->caracter.caracter){
				p2 = ln[n];
				a2 = n;
			}	
		}
		aux = NULL;
		
		if(p1->caracter.frec < p2->caracter.frec){//Creamos los nodos padres
			Nodo *aux = crearNodo(ln[a1]->caracter);
			strcpy (aux->caracter.label + strlen (aux->caracter.label), ln[a2]->caracter.label);
			aux->caracter.frec = p1->caracter.frec + p2->caracter.frec;
			aux->der = p2;
			aux->izq = p1;
			p1->padre = aux;
			p1->caracter.rama[0] = '0';
			p2->padre = aux;
			p2->caracter.rama[0] = '1';
			ln[a1] = aux;
			for(n=a2;n<tam;n++){
				ln[n] = ln[n+1];
			}
		}else{
			Nodo *aux = crearNodo(ln[a2]->caracter);
			strcpy (aux->caracter.label + strlen (aux->caracter.label), ln[a1]->caracter.label);
			aux->caracter.frec = p1->caracter.frec + p2->caracter.frec;
			aux->der = p1;
			aux->izq = p2;
			p1->padre = aux;
			p1->caracter.rama[0] = '0';
			p2->padre = aux;
			p2->caracter.rama[0] = '1';
			ln[a2] = aux;
			printf(" ");//No se porque necesita esto, si no crashea en ejecucion
			for(n=a1;n<tam;n++){
				ln[n] = ln[n+1];
			}
		}
		
		printf("Nueva lista:\n");
		for(n=0;n<tam-1;n++){
			printf("%s ", ln[n]->caracter.label);
		}
		printf("\n");
		generarArbol(tam-1);
	} else{//Creamos el nodo padre
		Caracter caux;
		caux.frec = ln[0]->caracter.frec + ln[1]->caracter.frec;
		strcpy (caux.label, ln[0]->caracter.label);
		strcpy (caux.label + strlen (caux.label), ln[1]->caracter.label);
		raiz = crearNodo(caux);
		raiz->der = ln[1];
		raiz->izq = ln[0];
		ln[1]->padre = raiz;
		ln[0]->padre = raiz;
		ln[1]->caracter.rama[0] = '1';
		ln[0]->caracter.rama[0] = '0';
		printf("%s %d  \n", raiz->caracter.label, raiz->caracter.frec);
	}
}

void generarHojas(int tam){
	int p;
	for(p=0; p<tam; p++){
		Nodo *aux = crearNodo(list[p]);
		ln[p] = aux;
		nodosOrg[p] = aux;
	}
		
}

void pre(Nodo *nodo){
	if(nodo != NULL){
		printf("%s,",nodo->caracter.label);
		pre(nodo->izq);
		pre(nodo->der);
	}
}

void hacerCodigos(int tam){
	int i=0;//Tenemos la lista de las hojas, hay que recorrer los padres hasta la raiz
	
	for(i;i<tam;i++){
		Nodo *padreaux = nodosOrg[i];
		while(padreaux != raiz){
			strcpy (nodosOrg[i]->caracter.cod + strlen (nodosOrg[i]->caracter.cod), padreaux->caracter.rama);
			padreaux = padreaux->padre;
		}
	}
	
	printf("\n\nCodigos:\n");
	for (i=0;i<tam;i++){
		strrev(nodosOrg[i]->caracter.cod);
		printf("%s | %s\n", nodosOrg[i]->caracter.label, nodosOrg[i]->caracter.cod );
		numbn += strlen(nodosOrg[i]->caracter.cod) * nodosOrg[i]->caracter.frec;
	}
	printf("\nEL mensaje final usa %d bits para el texto vs %d originales, es el %f porciento del original\n", numbn, numb, (float)numbn/numb);
}

int main(){
	int i=0, j;
	char texto[1000];
	printf("Ingrese el parrafo a comprimir, para terminar presione Tab + Enter\n");
	scanf("%1000[^\t]",texto);
	printf("\nTexto original:\n");
	printf("'%s'\n", texto);
	int tam = strlen(texto);//Con strlen obtenemos cuantos caracteres hay en la cadena
	printf("Numero de caracteres: %d = %d bits\n", tam, tam*8);
	numb = tam * 8;
	
	char aux[1];
	int contAux2;
	int cont3 = 0;
	for(i=0;i<tam;i++){
		aux[0] = texto[i];
		bool b = buscar(aux[0]);
		if(b){//Si no encuentra el dato en la lista, contamos cuantas veces aparece en el texto
			contAux2 = 0;
			for(j=0;j<tam;j++){
				if(aux[0] == texto[j]){
					 contAux2++;
				}
			}
			list[cont].caracter = aux[0];
			list[cont].label[0] = aux[0];
			list[cont].frec = contAux2;
			cont++;
			cont3++;
		}	
	}
	printf("Son %d caracteres individuales\n", cont3);
	BurbujaMej(cont3);//cont3 tiene el numero de caracteres que hay en la lista
	float prob;
	for(i=0;i<cont3;i++){
		prob = (float)list[i].frec/tam;
		printf("La letra %c aparece  %d veces con una probabilidad de %f\n", list[i].caracter, list[i].frec, prob);
	}
	printf("Generamos el arbol\n");
	generarHojas(tam-1);
	generarArbol(cont3);
	printf("\nPreorden\n");
	pre(raiz);

	hacerCodigos(cont3);
	printf("Codigo nuevo:\n");
	int y;
	for(i=0;i<tam;i++){
		for(y=0;y<cont3;y++){
			if(texto[i] == nodosOrg[y]->caracter.caracter){
				printf("%s ", nodosOrg[y]->caracter.cod);
			}
		}
	}
	printf("\n");
	
	system("pause");
	return 0;
}
