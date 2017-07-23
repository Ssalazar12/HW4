#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* i y j estan reservados como indices dentro de funciones */
/* Numero de columnas 744, numero de filas 500 */
#define ROWS 500
#define COLS 744

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
	
	init();
	
	read_f();
	
	files();

return(0);	
}