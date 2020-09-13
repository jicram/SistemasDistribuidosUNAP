
#include <math.h>
#include "mpi.h"   // Biblioteca de MPI
#include <cstdlib> // Incluido para el uso de atoi
#include <iostream>
using namespace std;

int fact(int f){
    int factorial=f;
    if(factorial>1){
        factorial=f*fact(f-1);
        return factorial;
    }else{
        return 1;
    }
}

int main(int argc, char *argv[]){

    int k, // Numero de sumas inversas
		rank, // Identificador de proceso
		size; // Numero de procesos
    double Epsilon = 2.718281828459045235360;
    double em=2.5; //valor minimo de epsilon
    double myep, // Valor local de PI
		ep,   // Valor global de Epsilon
		e;


    MPI_Init(&argc, &argv); // Inicializamos los procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

    // Solo el proceso 0 va a conocer el numero de iteraciones que vamos a
    // ejecutar para la aproximacion de PI
	if (rank == 0) {
		printf("El cálculo de épsilon dependera del valor de K \n");
		cout<<"Digita el valor de K, (k > 3): ";
		cin>>k;
		if (k <= 3){
			printf("El Valor mínimo de Epsilon es: %2f \n",em);
			MPI_Finalize();
			exit (0);
		}else{
			if (k >= size){
				MPI_Bcast(&k, // Puntero al dato que vamos a enviar
						  1,  // Numero de datos a los que apunta el puntero
						  MPI_INT, // Tipo del dato a enviar
						  0, // Identificacion del proceso que envia el dato
						  MPI_COMM_WORLD);
					// Calculando el valor de epsilon
					double e=0.0;
					for(int i = rank + 1;i<=k;i+=size){
						double u=fact(i);
						e+=1/u;
					}
					myep=e;
					MPI_Reduce(&myep, // Valor local de epsilon
								&ep,  // Dato sobre el que vamos a reducir el resto
								1,	  // Numero de datos que vamos a reducir
								MPI_DOUBLE,  // Tipo de dato que vamos a reducir
								MPI_SUM,  // Operacion que aplicaremos
								0, // proceso que va a recibir el dato reducido
								MPI_COMM_WORLD);

							// Imprime el valor de Epsilon.
							if (rank == 0)
							{
								printf("Epsilon: %.30f \n", Epsilon);
								printf("My Epsilon es: %.30f \n ", ep);
								printf("El valor aproximado de Epsilon es: %f, con un error de %.30f \n", ep,fabs(ep - Epsilon));
							}
			}else{
				printf("Ingresar un valor para k superior o igual a la cantidad de procesos \n\n");
				MPI_Finalize();
				exit (0);
			}
		}
	}



    MPI_Finalize();
    return 0;
}
