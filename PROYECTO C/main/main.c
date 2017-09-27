#include<stdio.h>
#include<string.h>
#include<math.h>
#define FICHERO1 "PRECIOS.DAT"


int main(){

    //VARIABLES
    int caso, k;
    int long nregistros, nd, ne, nt, ni, nc, na, nu, ns;

    //FUNCION
    system("cls");

    printf("\n\t|--------------------------------|\n");
    printf("\t|     BIENVENIDO AL PROGRAMA     |\n");
    printf("\t|--------------------------------|\n");
    printf("\tPulse cualquier tecla para continuar.");
    getch();

    while(1){

        system("cls");

        printf("\n\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    MENU PRINCIPAL              |\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    PRECIOS                 | 1 |\n");
        printf("\t|    CLIENTES                | 2 |\n");
        printf("\t|    PRESUPUESTOS            | 3 |\n");
        printf("\t|    FINALIZAR PROGRAMA      | 0 |\n");
        printf("\t|--------------------------------|\n\n");
        printf("\tQue desea hacer? Pulse la tecla correspondiente.");

        scanf("%d", &caso);
        switch(caso){
            case 1: mainPrecios();
                    break;
            case 2: mainClientes();
                    break;
            case 3: mainPresupuestos();
                    break;
            case 0:
                    return 0;
            default: printf("Seleccion incorrecta\n. Pulse cualquier tecla");
                getch();
                break;
        }
    }

    return 0;
}
