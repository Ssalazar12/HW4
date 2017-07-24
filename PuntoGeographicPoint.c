#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* i y j estan reservados como indices dentro de funciones */
/* Numero de columnas 744, numero de filas 500 */
#define ROWS 500
#define COLS 744
#define DATA_POINTS 100000
#define PI 3.14159265
#define e

int **matrix;

/*Lee los archivos*/
void read_f(){
	int i;
	int j;
	char *line; // recibe la linea de buffer
	char *part; // recibe las partes de la linea
	FILE *fstream;
	char buffer[1000];
	
	fstream=fopen("map_data.txt", "r"); //abre el stream
	
	if(fstream == NULL) {//asegura si abrio el archivo
		printf("\n No se pudo abrir el archivo \n ");
	}
	
	//itera sobre las lineas del archivo
	/*
	for(i=0;i<ROWS;i++){
		line=fgets(buffer, sizeof(buffer), fstream);
		if(line!=NULL){
			part= strtok(line, " ");
			for(j=0;j<COLS;j++){
				//printf("%s \n", part);
				matrix[i][j]=atoi(part);
				printf("%d \n", matrix[i]);	
				part=strtok(NULL," ");
			}	
		}	
	}
	fclose(fstream);
	*/
	
	while(fgets(buffer, sizeof(buffer), fstream)!=NULL){
		j=0;
		line=fgets(buffer, sizeof(buffer), fstream);
		part=strtok(line, " ");
		while(part!=NULL){
			matrix[i][j]= atoi(part);
			part=strtok(NULL, " ");
			j+=1;
		}
		i+=1;
	}
}	

/* Inicializa las variables*/
void init(){
	int i;
	
	//inicializa matrix
	matrix= (int **)malloc(ROWS * sizeof(int));
	for (i=0; i<ROWS; i++){
		matrix[i] = (int *)malloc(COLS * sizeof(int));
	}
}

/* retorna una gaussiana (punto) centrada en b que es un entero que corresponde a la 
	posicion de un elemento del array. Se usa el método polar tomado de
	https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/
 */
float rand_normal(int b){
	int point;
	float u1, u2;
	float w;
	float x1;
	//generamos u1, u2 entre -1 y 1 tal que U1^2 + U2^2 <1
	u1= (2)*rand() - 1;
	u2= (2)*rand() - 1;
	w = pow(u1,2) + pow(u2,2);
	while(w >= 1 || w==0){
		u1= (2)*((double) rand()/RAND_MAX) -1;
		u2= (2)*((double) rand()/RAND_MAX) -1;	
		w = pow(u1,2) + pow(u2,2);

	}
	x1= b + u1 * sqrt( -2*log(w)/w );
	return x1;
}

/* recibe una tupla (x_in y_in) y crea un circulo, aumentando su radio hasta tocar un 1 */
float circle(int y_in, int x_in){
	//las siguientes variables buscan 1's en todas las direcciones 
	int v; //busca por todas partes
	int xp;
	int yp;
	float rad;
	float area;
	
	v=0;
	xp=x_in;
	yp=y_in;
	 
	//tener un solo loop asegura que v y h sean de igual tamaño
	while(matrix[yp+v][xp]!=1 && matrix[yp-v][xp]!=1 && matrix[yp][xp+v]!=1 && matrix[yp][xp-v]!=1){
		printf("%d %d \n", v, matrix[yp][xp]);
		//pregunta si le da la vuelta al mundo a la derecha
		if(xp+v>=COLS-1){
			printf("se va a la derecha \n");
			xp=0;	
		}
		//pregunta si le da la vuelta al mundo a la izquierda
		if(xp-v<0){
			printf("se va a la izquierda \n");
			xp=COLS-1;	
		}
		// si se pasa por arriba se encuentra de una con un cero
		if(yp-v<=0){
			printf("se va arriba \n");
			break;	
		}	
		v+=1;
	}
	
	rad = sqrt( pow(v,2) + pow(v,2));
	area = PI * pow(rad,2);
	return area;
}

/*Escribe los resultados en archivos de datos*/
/*
void files(){
	FILE *out;
	int i;
	char tokens[COLS * 2]= {"%f"};
	tokens[743]= '\n';
	out = fopen("data.txt" , "w+");
	for(i=0;i<ROWS; i++){
		fprintf(out, tokens, matrix[i]);
	}
	fclose(out);
}

*/

int main(){
	float number;
	
	init();

	read_f();
	
return(0);	
}