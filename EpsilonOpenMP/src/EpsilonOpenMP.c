/*
 ============================================================================
 Name        : EpsilonOpenMP.c
 Author      : Jimmy Calderon
 Version     :
 Copyright   : Your copyright notice
 Description : Calculo de Épsilon
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int factorial(int f){
	int fact=f;
	if(fact>=1){
		fact=f*factorial(f-1);
		return fact;
	}else{
		return 1;
	}
}

int main (int argc, char *argv[]) {
  int k;
  double mye;

  printf("\n ***************************************************");
  printf("\n Fuera de la región paralela, se utilizan 4 threads");
  printf("\n ***************************************************");
  printf("\n \n Ingresa un valor para k : ");
  scanf("%d",&k);

  omp_set_num_threads(4);
#pragma omp parallel
 {
   int id = omp_get_thread_num();
   int nt = omp_get_num_threads();
   double e=0;
   for (int i=id; i<k; i+=nt){
	   double m=factorial(i);
	   e+=1.0/m;  //e=e+1.0/fact
     }
   printf("El valor de épsilon es : %f \n",e);
 }
 /*if (tid==3){
 for (int tid=0; tid<ntt; tid++){
	 mye+=mye;
 }
 }*/
 //printf("El valor de épsilon es: ,%10f",mye);
 return 0;
}

