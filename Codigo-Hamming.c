//Codigo de Hamming Josue Rose
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct{
	char bit;//Guardamos el 0 o el 1 de la palabra o mensaje
	int p;//Si es una potencia de 2, marcamos como 1, si no como 0
	char bin[100]; //Guardamos el numero de la posicion en bits
}posicion;

void generarCodigoPar(char[], int);
void generarCodigoImpar(char[], int);
int calcularP(int);
int verPotencia(int, int[], int);
int compararPesPos(int[], int, int);
	
void obtenerBinario(char*, int);
int decabin(int, int *);
void detectarErrorPar(char[], int, int);
void detectarErrorImpar(char[], int, int);
int calcularP2(int);

int main(){	
	printf("Codigo de hamming\n");
	int n=1,i, op, bitpar;
	char mensaje[100], codigo[100];
	while(n==1 || n ==2){
		printf("Elige una opcion\n1-Ingresar mensaje\n2-Ingresar codigo de Hamming\n3-Salir\n");
		scanf("%d",&n);
		if(n==1){
			printf("1-Par 2-Impar\n");
			scanf("%d",&op);
			printf("Ingresa el mensaje: ");
			scanf("%s",&mensaje);
			strrev(mensaje);
			i = strlen(mensaje);
			if(op == 1)
				generarCodigoPar(mensaje, i);
			else if(op == 2)
				generarCodigoImpar(mensaje, i);
		} else if(n==2){
			printf("1-Par 2-Impar\n");
			scanf("%d",&op);
			printf("Ingresa el codigo de Hamming: ");
			scanf("%s",&codigo);
			printf("Ingresa el bit de paridad adicional: ");
			scanf("%d",&bitpar);
			i = strlen(codigo);//?
			strrev(codigo); 
			if(op == 1)
				detectarErrorPar(codigo, i, bitpar);
			else if(op == 2)
				detectarErrorImpar(codigo, i, bitpar);
		} else
			printf("Bye\n");
		op = -1;
	}
	system("pause");
	return 0;
}

void generarCodigoPar(char mensaje[], int i){//No usar i para los bucles en esta funcion
	int p = calcularP(i);
	int j, x, cont;
	int longitud = p+i;
	posicion codigo[longitud+1];//En este array ponemos el codigo final
	char cod[longitud+1];//En este array ponemos el codigo final
	int potencias[p];//Aqui guardamos las posiciones de p sub x
	for(x=0;x<p;x++)//Guardamos las posiciones de p sub x
		potencias[x] = pow(2,x);
	
	cont=0;
	for(x=1;x<=longitud;x++){//Ponemos los destos en las posiciones i y p
		obtenerBinario(codigo[x-1].bin, x);
		if(verPotencia(x, potencias, p) == 1){//Si la posicion es una posicion de p le ponemos un guion de mientras
			codigo[x-1].bit = '_';
			codigo[x-1].p = 1;
		}else{//Si no, le ponemos el valor
			codigo[x-1].bit = mensaje[cont];
			codigo[x-1].p = 0;
			cont++;
		}
	}

	printf("\n\n",p);	
	cont=0;
	int cont2 = 0;
	for(x=0;x<=longitud+1;x++){
		if(codigo[x].p == 1){//Si es un bit de paridad lo calculamos
			printf("Calculamos el bit de paridad %d\n", x);
			cont=0;//cont guarda el numero de unos
			for(j=x;j<=longitud;j++){
				if(codigo[j].bin[cont2] == '1'){//Si es una posicion con la que evaluar, lo añadimos //Aqui puede que este el error
					if(codigo[j].bit == '1'){
						cont++;
					}
					
				}
			}
			printf("cont=%d\n", cont);
			if(cont%2 == 0){
				codigo[x].bit = '0';
			} else{
				codigo[x].bit = '1';
			}
			cont2++;
		}//Fin del if	
	}
	printf("\n");
	printf("\n");	
	for(x=longitud-1;x>=0;x--){
		printf("%c", codigo[x].bit);
	}
	printf("\n");
	int bitpariedad;
	if(longitud == 7 ){
		bitpariedad = (codigo[0].bit - '0') ^ (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0');
	}
	if(longitud == 13 ){
		bitpariedad = (codigo[0].bit - '0') ^ (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[10].bit - '0') ^ (codigo[11].bit - '0') ^ (codigo[12].bit - '0');
	}
	printf("bit extra de paridad: %d\n", bitpariedad);	
}

void generarCodigoImpar(char mensaje[], int i){//No uses i para ciclos en esta funcion
	int p = calcularP(i);
	int j, x, cont;
	int longitud = p+i;
	posicion codigo[longitud+1];//En este array ponemos el codigo final
	char cod[longitud+1];//En este array ponemos el codigo final
	int potencias[p];//Aqui guardamos las posiciones de p sub x
	for(x=0;x<p;x++)//Guardamos las posiciones de p sub x
		potencias[x] = pow(2,x);
	
	cont=0;
	for(x=1;x<=longitud;x++){//Ponemos los destos en las posiciones i y p
		obtenerBinario(codigo[x-1].bin, x);
		if(verPotencia(x, potencias, p) == 1){//Si la posicion es una posicion de p le ponemos un guion de mientras
			codigo[x-1].bit = '_';
			codigo[x-1].p = 1;
		}else{//Si no, le ponemos el valor
			codigo[x-1].bit = mensaje[cont];
			codigo[x-1].p = 0;
			cont++;
		}
	}
	
	//Imprimimos el codigo antes de calcular las pariedades
	printf("Precodigo:\n");
	for(j=0;j<longitud;j++){
		printf("%c", codigo[j].bit);
	}
	
	printf("\n\n",p);//Hasta aqui vamos bien
	//Calculamos lo
		
	cont=0;
	int cont2 = 0;
	for(x=0;x<=longitud+1;x++){
		if(codigo[x].p == 1){//Si es un bit de paridad lo calculamos
			printf("Calculamos el bit de paridad %d\n", x);
			cont=0;//cont guarda el numero de unos
			for(j=x;j<=longitud;j++){
				if(codigo[j].bin[cont2] == '1'){//Si es una posicion con la que evaluar, lo añadimos //Aqui puede que este el error
					//printf("Evaluamos el bit de %d\n",j);
					if(codigo[j].bit == '1'){
						cont++;
					}
					
				}
			}
			printf("cont=%d\n", cont);
			if(cont%2 == 0){
				codigo[x].bit = '1';
			} else{
				codigo[x].bit = '0';
			}
			cont2++;
		}//Fin del if	
	}
	printf("\n");

	printf("\n");	
	for(x=longitud-1;x>=0;x--){
		printf("%c", codigo[x].bit);
	}
	printf("\n");
	int bitpariedad;
	if(longitud == 7 ){
		bitpariedad = (codigo[0].bit - '0') ^ (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0');
		printf("bit extra de paridad: %d\n", bitpariedad);
	}
	if(longitud == 13 ){
		bitpariedad = (codigo[0].bit - '0') ^ (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[10].bit - '0') ^ (codigo[11].bit - '0') ^ (codigo[12].bit - '0');
		printf("bit extra de paridad: %d\n", bitpariedad);
	}	
}

int calcularP(int i){
	int j=0, p=-1;
	while(p==-1){
		if(pow(2,j)-j >= i+1)
			p = j;
		j++;
	}
	return p;
}

int verPotencia(int n, int arr[], int t){
	int i=0;
	for(i;i<t;i++){
		if(n == arr[i])
			return 1;
	}
	return 0;
}

void obtenerBinario(char* bin, int n){//Obtenemos el binario de la posicion que recibimos, ojo, lo guarda al reves
	int i = 0;
    int R;
    while( n ){
        n = decabin( n, &R );
        bin[i] = R + '0';  
        i++;
    }
} 

int decabin(int n, int *R){//Esta funcion es de ayuda para la de obtener binario
    *R = n%2;               
    return (n - *R)/2;
}

int compararPesPos(int pes[], int n, int tam){//Si la posicion que recibe es parte de p, retorna un 1 o verdadero
	int i;
	for(i=0;i<tam;i++){
		if(n == pes[i])
			return 1;
	}
	return 0;
}

void detectarErrorPar(char mensaje[], int tam, int bitadd){
	posicion codigo[tam+1];//En este array ponemos el codigo final
	int x,j,cont=0;
	int p = calcularP2(tam);
	int potencias[p];//guardamos las posiciones de los bits de pariedad
	char bitsorg[p];//Aqui guardamos los bits de paridad originales
	for(x=0;x<p;x++)
		potencias[x] = pow(2,x);
		
	int cont2 = 0;
	for(x=tam;x>0;x--){
		codigo[x].bit = mensaje[cont];
		obtenerBinario(codigo[x].bin, x);
		cont++;
	}	
	printf("\n");

	cont=0;
	int verpariedad;
	int errorbit = 1;//si es 1, significa que hay error en el bit de paridad adicional
	if(tam==7){
		verpariedad = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0') ^ (codigo[7].bit - '0');
		if(verpariedad != bitadd)
			errorbit = 1;
		else
			errorbit = 0;
	}
	else if(tam==13){
		verpariedad = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[10].bit - '0') ^ (codigo[11].bit - '0') ^ (codigo[12].bit - '0') ^ (codigo[13].bit - '0');
		if(verpariedad != bitadd)
			errorbit = 1;
		else
			errorbit = 0;
	}
		
	int c1,c2,c3, c4;
	if(tam<=7){//1 en el array = 7
		c1 = (codigo[7].bit - '0')  ^ (codigo[5].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[1].bit - '0');
		c2 = (codigo[6].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[1].bit - '0');
		c3 = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0');
	
		if(c1 == 1 || c2 == 1 || c3 == 1){
			if(errorbit == 0){
				printf("Hay mas de 1 error\n");
				return;
			}		
			int pos = 0;
			if(c1 == 1)
				pos += 1;
			if(c2 == 1)
				pos += 2;
			if(c3 == 1)
				pos += 4;
			printf("Hay error\n");
			pos = abs(pos-tam)+1;
			printf("%d%d%d pos del array = %d\n", c3,c2,c1, pos);
			if(codigo[pos].bit == '0')
				codigo[pos].bit = '1';
			else
				codigo[pos].bit = '0';
			
			printf("\nCodigo corregido:");
			for(x=1;x<=tam;x++){
				printf("%c", codigo[x].bit);
			}
			
		}else{
			printf("No hay error\n");
		}	
	}else if(tam==13){//fin del if 7
		c1 = (codigo[13].bit - '0')  ^ (codigo[11].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[1].bit - '0');
		c2 = (codigo[12].bit - '0') ^ (codigo[11].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[3].bit - '0');
		c3 = (codigo[10].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[1].bit - '0');
		c4 = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0');
	
		if(c1 == 1 || c2 == 1 || c3 == 1 || c4 == 1){
			if(errorbit == 0){
				printf("Hay mas de 1 error\n");
				return;
			}
			int pos = 0;
			if(c1 == 1)
				pos += 1;
			if(c2 == 1)
				pos += 2;
			if(c3 == 1)
				pos += 4;
			if(c4 == 1)
				pos += 8;
			printf("Hay error\n");
			pos = abs(pos-tam)+1;
			printf("%d%d%d%d pos del array = %d\n", c4,c3,c2,c1, pos);
			if(codigo[pos].bit == '0')
				codigo[pos].bit = '1';
			else
				codigo[pos].bit = '0';
				
			printf("\nCodigo corregido:");
			for(x=1;x<=tam;x++){
				printf("%c", codigo[x].bit);
			}
		}else{
			printf("No hay error\n");
		}	
	}else
		printf("No hay error");
	printf("\n");	
}

void detectarErrorImpar(char mensaje[], int tam, int bitadd){
	posicion codigo[tam+1];//En este array ponemos el codigo final
	int x,j,cont=0;
	int p = calcularP2(tam);
	int potencias[p];//guardamos las posiciones de los bits de pariedad
	char bitsorg[p];//Aqui guardamos los bits de paridad originales
	for(x=0;x<p;x++)
		potencias[x] = pow(2,x);
		
	int cont2 = 0;
	for(x=tam;x>0;x--){
		codigo[x].bit = mensaje[cont];
		obtenerBinario(codigo[x].bin, x);
		cont++;
	}	
	printf("\n");

	cont=0;
	int verpariedad;
	int errorbit = 1;//si es 1, significa que hay error en el bit de paridad adicional
	if(tam==7){
		verpariedad = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0') ^ (codigo[7].bit - '0');
		if(verpariedad != bitadd)
			errorbit = 1;
		else
			errorbit = 0;
	}
	else if(tam==13){
		verpariedad = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[10].bit - '0') ^ (codigo[11].bit - '0') ^ (codigo[12].bit - '0') ^ (codigo[13].bit - '0');
		if(verpariedad != bitadd)
			errorbit = 1;
		else
			errorbit = 0;
	}
		
	int c1,c2,c3, c4;
	if(tam<=7){
		c1 = (codigo[7].bit - '0')  ^ (codigo[5].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[1].bit - '0');
		c2 = (codigo[6].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[1].bit - '0');
		c3 = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0');
		if(c1 == 0 || c2 == 0 || c3 == 0){
			if(errorbit == 0){
				printf("Hay mas de 1 error\n");
				return;
			}		
			int pos = 0;
			if(c1 == 1)
				pos += 1;
			if(c2 == 1)
				pos += 2;
			if(c3 == 1)
				pos += 4;
			pos = pos+1;
			printf("Hay error en %d\n", pos);
			if(codigo[pos].bit == '0')
				codigo[pos].bit = '1';
			else
				codigo[pos].bit = '0';
			
			printf("\nCodigo corregido:");
			for(x=1;x<=tam;x++){
				printf("%c", codigo[x].bit);
			}
		}else{
			printf("No hay error\n");
		}	
	}else if(tam==13){//fin del if 7
		c1 = (codigo[13].bit - '0')  ^ (codigo[11].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[1].bit - '0');
		c2 = (codigo[12].bit - '0') ^ (codigo[11].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[3].bit - '0');
		c3 = (codigo[10].bit - '0') ^ (codigo[9].bit - '0') ^ (codigo[8].bit - '0') ^ (codigo[7].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[1].bit - '0');
		c4 = (codigo[1].bit - '0') ^ (codigo[2].bit - '0') ^ (codigo[3].bit - '0') ^ (codigo[4].bit - '0') ^ (codigo[5].bit - '0') ^ (codigo[6].bit - '0');
	
		if(c1 == 0 || c2 == 0 || c3 == 0 || c4 == 0){
			if(errorbit == 0){
				printf("Hay mas de 2 errores\n");
				return;
			}
			int pos = 0;
			if(c1 == 1)
				pos += 1;
			if(c2 == 1)
				pos += 2;
			if(c3 == 1)
				pos += 4;
			if(c4 == 1)
				pos += 8;
			printf("Hay error\n");
			pos = pos-1;
			printf("%d%d%d%d pos del array = %d\n", c4,c3,c2,c1, pos);
			if(codigo[pos].bit == '0')
				codigo[pos].bit = '1';
			else
				codigo[pos].bit = '0';
				
			printf("\nCodigo corregido:");
			for(x=1;x<=tam;x++){
				printf("%c", codigo[x].bit);
			}
		}else{
			printf("No hay error\n");
		}	
	}else
		printf("No hay error");
	printf("\n");
}

int calcularP2(int tam){//a aprtir del tamaño hay que calcular cuantas posiciones de p hay
	int p=0;
	for(p;p<tam;p++){
		if(pow(2,p) >= tam)
			return p;
	}	
}
