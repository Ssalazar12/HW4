#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*
 	Importante usa rlos rand() bien porque sino mandan unos numeros loquisimos y segmentation error 11 :'v
*/

/* i y j estan reservados como indices dentro de funciones */
/* Numero de columnas 744, numero de filas 500 */
#define ROWS 500
#define COLS 744
#define DATA_POINTS 400000
#define PI 3.14159265

int *matrix[ROWS];
int max_x;	//coord. x del polo de inaccesibilidad
int max_y;	//coord. y del polo de inaccesibilidad
float max_area; //area del circulo del polo a algun punto con tierra
//variables try guardan los intentos para comparar con la variable max de la iteracion actual
int try_x;
int try_y;
float try_area;

float alpha; //guarda la razon entre try y max area para decidir que se hace con el punto
float beta; //para hacer la segunda comparacion de alpha

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
	i=0;
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
	fclose(fstream);
}	

/* Inicializa las variables*/
void init(){
	int i;
	//asigna un espacio a los pinters de las columnas en las filas
	for (i=0; i<ROWS; i++){
		matrix[i] = (int *)malloc(COLS * sizeof(int));
	}
	//inicializa el resto
	max_area= 0;
	alpha = 0;
	beta = 0;
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
	float std=2; //desviacion estandar
	
	//srand(time(NULL)); 
	//generamos u1, u2 entre -1 y 1 tal que U1^2 + U2^2 <1
	u1=  2 * (double)rand()/RAND_MAX +0.5 - 1;
	u2= 2 * (double)rand()/RAND_MAX +0.5 - 1;
	w = pow(u1,2) + pow(u2,2);
	while(w >= 1 || w==0){
		//u1= (2)*((double) rand()/RAND_MAX) -1;
		//u2= (2)*((double) rand()/RAND_MAX) -1;	
		u1= 2 * (double)rand()/RAND_MAX +0.5 - 1;
		u2= 2 * (double)rand()/RAND_MAX +0.5 - 1;
		w = pow(u1,2) + pow(u2,2);

	}
	x1= b + std* (u1*sqrt( -2*log(w)/w ));
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
		//pregunta si le da la vuelta al mundo a la derecha
		if(xp+v>=COLS-1){
			xp=0;	
		}
		//pregunta si le da la vuelta al mundo a la izquierda
		if(xp-v<0){
			xp=COLS-1;	
		}
		// si se pasa por arriba se encuentra de una con un cero
		if(yp-v<=0){
			break;	
		}	
		v+=1;
	}
	
	rad = sqrt( pow(v,2) + pow(v,2));
	area = PI * pow(rad,2);
	return area;
}

/*Escribe los resultados en archivos de datos*/
void files(){
	FILE *fout;
	fout = fopen("polo.csv" , "w+");
	fprintf(fout, "%d %d %f", max_x, max_y, max_area);	
}

int main(){
	
	int t; //indice para iterar MCMC
	/*inicializa variables*/	
	init();
	
	/*lee los datos y los pone en matrix*/
	read_f();
	
	/* Implementacion de MCMC para encontrar el polo sur de inaccesibilidad*/
	//Primer intento genera 2 numeros aleatorios: x entre 0 y 743 y y entre 499 (deben ser enteros)
	srand(time(NULL)); //da nuevas seeds al rand
	
	max_x= 742* (double)rand()/RAND_MAX + 0.5 ;
	max_y= 498* (double)rand()/RAND_MAX + 0.5 ;
	
	printf("%d %d\n", max_x, max_y);

	//Se asegura que no esten en tierra (osea sobre un 1)
	while(matrix[max_y][max_x]==1){
		max_x= 743* (double)rand()/RAND_MAX +0.5;
		max_y= 499* (double)rand()/RAND_MAX +0.5;	
		}
	
	//Encuentra el maximo circulo posible para el primer intento
	//printf("%d %d %d \n", max_x, max_y, matrix[max_y][max_x]);

	max_area = circle(max_y, max_x);
	int counter;
	counter =0;
	//Comienza el ciclo
	for(t=0; t<DATA_POINTS; t++){
		counter+=1;
		//printf("%d %d %d %d %f \n", max_x, max_y, matrix[max_y][max_x], counter, beta);
		try_x=(int) rand_normal(max_x);
		try_y=(int) rand_normal(max_y);
		
		while(matrix[try_y][try_x]==1 || try_x<=0 || try_y<=0 || try_x>=COLS-1 || try_y >= ROWS-1){
			try_x=(int) rand_normal(max_x);
			try_y=(int) rand_normal(max_y);
		} 
			
		try_area = circle(try_y, try_x);
		//Comienza a decidir si guarda los try como nuevos max
		alpha =  try_area/max_area;
		//actualiza las variables max
		if(alpha>=1){
			max_x= try_x;
			max_y= try_y;
			max_area= try_area;	
		}
		else{
			beta= (double)rand()/RAND_MAX; 
			//printf("%f \n", beta);
			//en este caso rechaza las variables try
			if(alpha<beta){
				continue; //ojo con esto podria generar un error
			}
			
			//si alpha es mayor a beta entonces actualiza las variables max
			else{
				max_x= try_x;
				max_y= try_y;
				max_area= try_area;
			}	
		}
	}
	
	printf("%d %d %d %f \n", max_x, max_y, counter, beta);
	
/*
	Al final de este for deberiamos tener el polo de inaccesibilidad sur y 
	se pasa a crear los archivos de datos
*/
	files();

return(0);	
}