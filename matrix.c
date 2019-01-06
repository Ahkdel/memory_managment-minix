#include <stdio.h>
#include <stdlib.h>
#define MATSIZE 4 

int main(int argc, char *argv[]) {
	char option;
	int row, column, page, sum; 
	int matriz[MATSIZE][MATSIZE];
	for (row = 0; row < MATSIZE; row++) {
		  for (column = 0; column < MATSIZE; column++) { //* INICIALIZANDO TODAS LAS CASILLAS DE LA MATRIZ EN 0
			  matriz[row][column] = 0;
		  }
	}
do{
	printf("        *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\t||1. MOSTRAR MATRIZ                ||\n");
	printf("\t||2. USAR UNA PAGINA               ||\n");
	printf("\t||3. CONSULTAR PAGINA O PAGINAS LRU||\n");
	printf("\t||0. SALIR DEL PROGRAMA            ||\n");
	printf("        *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("OPCION: ");
	scanf(" %c", &option);
	system("clear");
	switch (option) {
	 case '1':
		for (row = 0; row < MATSIZE; row++) {
		   for (column = 0; column < MATSIZE; column++) {
			 printf("|%d|\t", matriz[row][column]);
		   }
		   printf("PAGINA %d", row);
		   printf("\n");
	    }
	    printf("\n");
	    break;
	 case '2':
        do{
	      printf("ELIJA PAGINA A REFERENCIAR (0,1,2,3)\n");
	      scanf("%d", &page);
	      system("clear");
	     }while(page>3 || page<0);
	     for (row = 0; row < MATSIZE; row++) {
		    for (column = 0; column < MATSIZE; column++) {
		  	   if (row==page){
		  	     matriz[row][column]=1;
		       }
		  	   if (column==page){
			     matriz[row][column]=0;
		       }
	        }
	     }
	    break;
	 case '3':
	    system("clear");
	    printf("LA SIGUIENTE O SIGUIENTES PAGINAS SON LAS MENOS USADAS RECIENTEMENTE\n");
		for (row = 0; row < MATSIZE; row++) {
		  sum = 0;
		  for (column = 0; column < MATSIZE; column++) {
		  	if ((matriz[row][column])==1){
		  	 sum = matriz[row][column] + sum;
		  	}
		  }
		   if (sum == 0){
		  	 	printf("PAGINA: %d\n", row);
		   }
	    }
	    printf("\n");
	    break;
	 default:
	    break;
	 }
}while (option!='0');
    return 0;
}
