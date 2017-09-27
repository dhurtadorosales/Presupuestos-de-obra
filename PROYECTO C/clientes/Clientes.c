#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define FICHERO1 "PRECIOS.DAT"
#define FICHERO2 "CLIENTES.DAT"
#define FICHERO3 "PRESUPUESTOS.DAT"

    //ESTRUCTURA DE CLIENTES
    typedef struct{
        int numero_cliente;
        char tipo_cliente;
        char cif[11];
        char nombre[50];
        char direccion[50];
        char localidad[30];
        char provincia[15];
        char cp[7];
        char tel[10];
    }Cliente;
    static Cliente cliente;

    //ESTRUCTURA REGISTRO 02
    typedef struct{
        long int nregistros;    //numero registros totales
        char blanco[174];
    }Primer_registro2;
    static Primer_registro2 registro02;

    //PUNTEROS A FICHEROS
    FILE* p2;

    //FUNCIONES PRECIOS
    void altas_cliente();
    void listados_cliente();
    void modificaciones_cliente();

int mainClientes(){

    //VARIABLES
    int caso, k;
    int long nregistros;

    //FUNCION
    p2= fopen(FICHERO2, "rb");
    if(p2== NULL){
        system("cls");
        printf("\tEl fichero CLIENTES.DAT no existe. Pulse cualquier tecla para crearlo.\n");
        getch();
        fclose(p2);
        p2= fopen(FICHERO2, "w+b");

        fseek(p2, 0L, 0);
        nregistros= 0L;
        registro02.nregistros= nregistros;

        for(k= 0; k< 172; k++)
            registro02.blanco[k]= ' ';

        fseek(p2, 0L, 0);
        fwrite(&registro02, sizeof(registro02), 1, p2);
        printf("\tFichero creado.\n\tPulse cualquier tecla para continuar.");
        getch();
    }
    fclose(p2);

   while(1){
        system("cls");
        printf("\n\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    MENU CLIENTES               |\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    CREAR NUEVO CLIENTE     | 1 |\n");
        printf("\t|    LISTADO DE CLIENTES     | 2 |\n");
        printf("\t|    MODIFICAR CLIENTE       | 3 |\n");
        printf("\t|    FINALIZAR CLIENTES      | 0 |\n");
        printf("\t|--------------------------------|\n\n");

        printf("\tQue desea hacer? Pulse la tecla correspondiente.\n\n\t");

        scanf("%d", &caso);
        switch(caso){
            case 1: altas_cliente();
                    break;
            case 2: listados_cliente();
                    break;
            case 3: modificaciones_cliente();
                    break;
            case 0:
                    return 0;
            default: printf("\tSeleccion incorrecta\n. Pulse cualquier tecla");
                getch();
                break;
        }
   }
    return 0;
}

void altas_cliente(){

    //VARIABLES LOCALES
    char opcion;
    long int n2, desplazamiento;
    int i, k;
    char tipo_cliente;
    char cif[11];
    char nombre[50];
    char direccion[50];
    char localidad[30];
    char provincia[15];
    char cp[7];
    char tel[10];

    //FUNCION
    p2= fopen(FICHERO2, "r+b");
    fseek(p2, 0L, 0);
    fread(&registro02, sizeof(registro02), 1, p2);
    n2= registro02.nregistros;

    while(1){
        system("cls");
        printf("\n\n\tVa a crear un nuevo cliente.\n");
        printf("\tContinuar? (s/n)\n\t");
        fflush(stdin);
        scanf("%c", &opcion);

        if((opcion>=97) && (opcion<=122))
            opcion= opcion- 32;

        if(opcion== 'N')
            break;
        if((opcion!= 'S') && (opcion!= 'N')){
            printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar\n");
            getch();
            continue;
        }
        if(opcion== 'S'){
            system("cls");
            printf("\n\n");
            printf("\t|--------------------------------|\n");
            printf("\t|    CREAR NUEVO CLIENTE         |\n");
            printf("\t|--------------------------------|\n");

            n2++;

            desplazamiento= n2* sizeof(cliente);
            fseek(p2, desplazamiento, 0);

            printf("\tSeleccione si el cliente es particular o empresa. (p/e): ");
            fflush(stdin);
            scanf("%c", &tipo_cliente);

            if((tipo_cliente>=97) && (tipo_cliente<=122))
                tipo_cliente= tipo_cliente- 32;

            if((tipo_cliente!= 'P') && (tipo_cliente!= 'E')){
                printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar\n");
                getch();
                continue;
            }
            if(tipo_cliente== 'P'){
                printf("\tNIF del particular (00000000A): ");

                fflush(stdin);
                gets(cif);//***************************************************************************pierde P

                if((cif[8]>=97) && (cif[8]<=122))
                    cif[8]= cif[8]- 32;

                printf("\tNombre y apellidos del particular: ");
                fflush(stdin);
                gets(nombre);
            }

            if(tipo_cliente== 'E'){
                printf("\tCIF de la empresa (A00000000): ");
                fflush(stdin);
                scanf("%s", &cif);
                if((cif[0]>=97) && (cif[0]<=122))
                    cif[0]= cif[0]- 32;

                printf("\tRazon social de la empresa: ");
                fflush(stdin);
                gets(nombre);
            }

            printf("\tDireccion (Tipo/ Nombre de calle, Nº, piso-letra): ");
            fflush(stdin);
            gets(direccion);

            printf("\tLocalidad: ");
            fflush(stdin);
            gets(localidad);

            printf("\tProvincia: ");
            fflush(stdin);
            gets(provincia);

            printf("\tCodigo Postal: ");//********************************************** pierde provincia
            fflush(stdin);
            gets(cp);

            printf("\tTelefono: ");
            fflush(stdin);
            gets(tel);

            system("cls");
            printf("\n\n\tSe acaba de crear el siguiente cliente:\n");
            printf("\t|----|--------------|-------------------------------------------------|\n");
            printf("\t|NUM.|TIPO|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |\n");
            printf("\t|----|--------------|-------------------------------------------------|\n");
            fflush(stdout);
            printf("\t|%0d   |%c   |%s|%s", n2, tipo_cliente, cif, nombre);
            for(i= (strlen(nombre)+1); i< 50; i++)
                printf(" ");
            printf("|\n");
            printf("\t|----|--------------|-------------------------------------------------|\n");
            printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
            printf("\t|DIRECCION                                        |LOCALIDAD                    |PROVINCIA     |CP   |TELEFONO    |\n");
            printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
            printf("\t|%s", direccion);
            for(i= (strlen(direccion)+1); i< 50; i++)
                printf(" ");
            printf("|%s", localidad);
            for(i= (strlen(localidad)+1); i< 30; i++)
                printf(" ");
            printf("|%s", provincia);
            for(i= (strlen(provincia)+1); i< 15; i++)
                printf(" ");
            printf("|%s", cp);
            printf("|");
            printf("%c", tel[0]);
            printf("%c", tel[1]);
            printf("%c", tel[2]);
            printf(" ");
            printf("%c", tel[3]);
            printf("%c", tel[4]);
            printf(" ");
            printf("%c", tel[5]);
            printf("%c", tel[6]);
            printf(" ");
            printf("%c", tel[7]);
            printf("%c", tel[8]);
            printf("|\n");
            printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");

            fflush(stdin);
            cliente.numero_cliente= n2;
            cliente.tipo_cliente= tipo_cliente;
            strcpy(cliente.cif, cif);
            strcpy(cliente.nombre, nombre);
            strcpy(cliente.direccion, direccion);
            strcpy(cliente.localidad, localidad);
            strcpy(cliente.provincia, provincia);
            strcpy(cliente.cp, cp);
            strcpy(cliente.tel, tel);

            fwrite(&cliente, sizeof(cliente), 1, p2);
            getch();
        }
    }
    fseek(p2, 0L, 0);
    registro02.nregistros= n2;
    for(k= 0; k< 174; k++)
        registro02.blanco[k]= ' ';
    fwrite(&registro02, sizeof(registro02), 1, p2);
    fflush(p2);
    fclose(p2);
}

void listados_cliente(){

    //VARIABLES LOCALES
    char opcion;
    long int n2, desplazamiento;
    int i, j, buscar, sw;

    //FUNCION
    p2= fopen(FICHERO2, "r+b");
    fseek(p2, 0L, 0);
    fread(&registro02, sizeof(registro02), 1, p2);
    n2= registro02.nregistros;

    while(1){
        system("cls");
        printf("\n\n");
        printf("\t|-----------------------------------------------------------------------------|\n");
        printf("\t|                           LISTADO DE CLIENTES                               |\n");
        printf("\t|----|---------|-------------------------------------------------|------------|\n");
        printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
        printf("\t|----|---------|-------------------------------------------------|------------|\n");

        for(i= 1; i<= n2; i++){
            desplazamiento= i* sizeof(cliente);
            fseek(p2, desplazamiento, 0);
            fread(&cliente, sizeof(cliente), 1, p2);

            printf("\t|%0d   |%s|%s", cliente.numero_cliente, cliente.cif, cliente.nombre);
            for(j= (strlen(cliente.nombre)+1); j< 50; j++)
                printf(" ");

            printf("|");
            printf("%c", cliente.tel[0]);
            printf("%c", cliente.tel[1]);
            printf("%c", cliente.tel[2]);
            printf(" ");
            printf("%c", cliente.tel[3]);
            printf("%c", cliente.tel[4]);
            printf(" ");
            printf("%c", cliente.tel[5]);
            printf("%c", cliente.tel[6]);
            printf(" ");
            printf("%c", cliente.tel[7]);
            printf("%c", cliente.tel[8]);
            printf("|\n");
        }
        printf("\t|-----------------------------------------------------------------------------|\n");

        printf("\n\tSeleccione el numero de cliente para ver mas detalles o pulse 0 para salir.");
        fflush(stdin);
        scanf("%d", &buscar);
        if (buscar==0)
            break;
        if(buscar!= 0){
            for(i= 1; i<= n2; i++){
                sw= 0;
                desplazamiento= i* sizeof(cliente);
                fseek(p2, desplazamiento, 0);
                fread(&cliente, sizeof(cliente), 1, p2);
                if(buscar== cliente.numero_cliente){
                    sw= 1;
                    break;
                }
            }
            if(sw==1){
                system("cls");
                printf("\n\t|----|----|---------|-------------------------------------------------|\n");
                printf("\t|NUM.|TIPO|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |\n");
                printf("\t|----|----|---------|-------------------------------------------------|\n");
                fflush(stdout);
                printf("\t|%d   |%c   |%s|%s", cliente.numero_cliente, cliente.tipo_cliente, cliente.cif, cliente.nombre);
                for(i= (strlen(cliente.nombre)+1); i< 50; i++)
                    printf(" ");
                printf("|\n");
                printf("\t|----|----|---------|-------------------------------------------------|\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
                printf("\t|DIRECCION                                        |LOCALIDAD                    |PROVINCIA     |CP   |TELEFONO    |\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
                printf("\t|%s", cliente.direccion);
                for(i= (strlen(cliente.direccion)+1); i< 50; i++)
                    printf(" ");
                printf("|%s", cliente.localidad);
                for(i= (strlen(cliente.localidad)+1); i< 30; i++)
                    printf(" ");
                printf("|%s", cliente.provincia);
                for(i= (strlen(cliente.provincia)+1); i< 15; i++)
                    printf(" ");
                printf("|%s", cliente.cp);
                printf("|");
                printf("%c", cliente.tel[0]);
                printf("%c", cliente.tel[1]);
                printf("%c", cliente.tel[2]);
                printf(" ");
                printf("%c", cliente.tel[3]);
                printf("%c", cliente.tel[4]);
                printf(" ");
                printf("%c", cliente.tel[5]);
                printf("%c", cliente.tel[6]);
                printf(" ");
                printf("%c", cliente.tel[7]);
                printf("%c", cliente.tel[8]);
                printf("|\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");

                printf("\n\tPulse cualquier tecla para volver.");
                getch();
            }
        }
    }

    fflush(p2);
    fclose(p2);
}

void modificaciones_cliente(){

    //VARIABLES LOCALES
    char opcion, opcion2, opcion3;
    long int n2, desplazamiento;
    int i, j, buscar, sw, posicion;

    //LISTADO
    p2= fopen(FICHERO2, "r+b");
    fseek(p2, 0L, 0);
    fread(&registro02, sizeof(registro02), 1, p2);
    n2= registro02.nregistros;


    while(1){
        system("cls");
        printf("\n\n");
        printf("\t|-----------------------------------------------------------------------------|\n");
        printf("\t|                           LISTADO DE CLIENTES                               |\n");
        printf("\t|----|---------|-------------------------------------------------|------------|\n");
        printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
        printf("\t|----|---------|-------------------------------------------------|------------|\n");

        for(i= 1; i<= n2; i++){
            desplazamiento= i* sizeof(cliente);
            fseek(p2, desplazamiento, 0);
            fread(&cliente, sizeof(cliente), 1, p2);

            printf("\t|%d   |%s|%s", n2, cliente.cif, cliente.nombre);
            for(j= (strlen(cliente.nombre)+1); j< 50; j++)
                printf(" ");

            printf("|");
            printf("%c", cliente.tel[0]);
            printf("%c", cliente.tel[1]);
            printf("%c", cliente.tel[2]);
            printf(" ");
            printf("%c", cliente.tel[3]);
            printf("%c", cliente.tel[4]);
            printf(" ");
            printf("%c", cliente.tel[5]);
            printf("%c", cliente.tel[6]);
            printf(" ");
            printf("%c", cliente.tel[7]);
            printf("%c", cliente.tel[8]);
            printf("|\n");
        }
        printf("\t|-----------------------------------------------------------------------------|\n");

        //MODIFICACION
        printf("\n\n\tSeleccione el numero de cliente que desea modificar.\n\tPara salir pulse 0\n");
        printf("\tNumero de cliente: ");
        fflush(stdin);
        scanf("%d", &buscar);
        if (buscar==0)
            break;

        sw= 0;
        for(i= 1; i<= n2; i++){
            desplazamiento= i* sizeof(cliente);
            fseek(p2, desplazamiento, 0);
            fread(&cliente, sizeof(cliente), 1, p2);
            if(buscar== cliente.numero_cliente){
                posicion= i;
                sw= 1;
                break;
            }
        }
        if(sw== 0){
            printf("\tEste cliente no existe\n");
            getch();
            continue;
        }
        if(sw== 1){
            system("cls");
            printf("\tSe va a modificar el cliente: \n");
            printf("\t|----|--------------|-------------------------------------------------|\n");
            printf("\t|NUM.|TIPO|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |\n");
            printf("\t|----|--------------|-------------------------------------------------|\n");
            fflush(stdout);
            printf("\t|%d   |%c   |%s|%s", cliente.numero_cliente, cliente.tipo_cliente, cliente.cif, cliente.nombre);
            for(i= (strlen(cliente.nombre)+1); i< 50; i++)
                printf(" ");
            printf("|\n");
            printf("\t|----|--------------|-------------------------------------------------|\n");
            printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
            printf("\t|DIRECCION                                        |LOCALIDAD                    |PROVINCIA     |CP   |TELEFONO    |\n");
            printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
            printf("\t|%s", cliente.direccion);
            for(i= (strlen(cliente.direccion)+1); i< 50; i++)
                printf(" ");
            printf("|%s", cliente.localidad);
            for(i= (strlen(cliente.localidad)+1); i< 30; i++)
                printf(" ");
            printf("|%s", cliente.provincia);
            for(i= (strlen(cliente.provincia)+1); i< 15; i++)
                printf(" ");
            printf("|%s", cliente.cp);
            printf("|");
            printf("%c", cliente.tel[0]);
            printf("%c", cliente.tel[1]);
            printf("%c", cliente.tel[2]);
            printf(" ");
            printf("%c", cliente.tel[3]);
            printf("%c", cliente.tel[4]);
            printf(" ");
            printf("%c", cliente.tel[5]);
            printf("%c", cliente.tel[6]);
            printf(" ");
            printf("%c", cliente.tel[7]);
            printf("%c", cliente.tel[8]);
            printf("|\n");
            printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");

            printf("\n\tDesea continuar? (s/n)\n\t");
            fflush(stdin);
            scanf("%c", &opcion2);
            if(opcion2== 'n')
                break;
            if((opcion2!= 's') && (opcion2!= 'n')){
                printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar\n");
                getch();
                continue;
            }
            if(opcion2== 's'){
                system("cls");
                printf("\t|----|--------------|-------------------------------------------------|\n");
                printf("\t|NUM.|TIPO|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |\n");
                printf("\t|----|--------------|-------------------------------------------------|\n");
                fflush(stdout);
                printf("\t|%d   |%c   |%s|%s", cliente.numero_cliente, cliente.tipo_cliente, cliente.cif, cliente.nombre);
                for(i= (strlen(cliente.nombre)+1); i< 50; i++)
                    printf(" ");
                printf("|\n");
                printf("\t|----|--------------|-------------------------------------------------|\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
                printf("\t|DIRECCION                                        |LOCALIDAD                    |PROVINCIA     |CP   |TELEFONO    |\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
                printf("\t|%s", cliente.direccion);
                for(i= (strlen(cliente.direccion)+1); i< 50; i++)
                    printf(" ");
                printf("|%s", cliente.localidad);
                for(i= (strlen(cliente.localidad)+1); i< 30; i++)
                    printf(" ");
                printf("|%s", cliente.provincia);
                for(i= (strlen(cliente.provincia)+1); i< 15; i++)
                    printf(" ");
                printf("|%s", cliente.cp);
                printf("|");
                printf("%c", cliente.tel[0]);
                printf("%c", cliente.tel[1]);
                printf("%c", cliente.tel[2]);
                printf(" ");
                printf("%c", cliente.tel[3]);
                printf("%c", cliente.tel[4]);
                printf(" ");
                printf("%c", cliente.tel[5]);
                printf("%c", cliente.tel[6]);
                printf(" ");
                printf("%c", cliente.tel[7]);
                printf("%c", cliente.tel[8]);
                printf("|\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");

                printf("\n\n\tElija el campo que desea modificar:\n");
                while(1){
                    printf("\n\n");
                    printf("\t|--------------------------------|\n");
                    printf("\t|    Nombre                  | 1 |\n");
                    printf("\t|    Direccion               | 2 |\n");
                    printf("\t|    Localidad               | 3 |\n");
                    printf("\t|    Provincia               | 4 |\n");
                    printf("\t|    Codigo postal           | 5 |\n");
                    printf("\t|    Telefono                | 6 |\n");
                    printf("\t|    Finalizar modificacion  | 0 |\n");
                    printf("\t|--------------------------------|\n\n");

                    fflush(stdin);
                    scanf("%d", &opcion3);
                    if(opcion3== 0)
                        break;
                    switch(opcion3){
                        case 1: printf("\tNombre: ");
                                fflush(stdin);
                                gets(cliente.nombre);
                                break;

                        case 2: printf("\tDireccion: ");
                                fflush(stdin);
                                gets(cliente.direccion);
                                break;

                        case 3: printf("\tLocalidad: ");
                                fflush(stdin);
                                gets(cliente.localidad);
                                break;

                        case 4: printf("\tProvincia: ");
                                fflush(stdin);
                                gets(cliente.provincia);
                                break;

                        case 5: printf("\tCodigo Postal: ");
                                fflush(stdin);
                                gets(cliente.cp);
                                break;
                        case 6: printf("\tTelefono: ");
                                fflush(stdin);
                                gets(cliente.tel);
                                break;
                        default: printf("\tSeleccion incorrecta.\n\tPulse cualquier tecla.\n");
                                getch();
                                break;
                    }
                }


                system("cls");
                printf("\tCliente actualizado: (Pulse cualquier tecla para continuar)\n");

                printf("\t|----|--------------|-------------------------------------------------|\n");
                printf("\t|NUM.|TIPO|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |\n");
                printf("\t|----|--------------|-------------------------------------------------|\n");
                fflush(stdout);
                printf("\t|%d   |%c   |%s|%s", cliente.numero_cliente, cliente.tipo_cliente, cliente.cif, cliente.nombre);
                for(i= (strlen(cliente.nombre)+1); i< 50; i++)
                    printf(" ");
                printf("|\n");
                printf("\t|----|--------------|-------------------------------------------------|\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
                printf("\t|DIRECCION                                        |LOCALIDAD                    |PROVINCIA     |CP   |TELEFONO    |\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");
                printf("\t|%s", cliente.direccion);
                for(i= (strlen(cliente.direccion)+1); i< 50; i++)
                    printf(" ");
                printf("|%s", cliente.localidad);
                for(i= (strlen(cliente.localidad)+1); i< 30; i++)
                    printf(" ");
                printf("|%s", cliente.provincia);
                for(i= (strlen(cliente.provincia)+1); i< 15; i++)
                    printf(" ");
                printf("|%s", cliente.cp);
                printf("|");
                printf("%c", cliente.tel[0]);
                printf("%c", cliente.tel[1]);
                printf("%c", cliente.tel[2]);
                printf(" ");
                printf("%c", cliente.tel[3]);
                printf("%c", cliente.tel[4]);
                printf(" ");
                printf("%c", cliente.tel[5]);
                printf("%c", cliente.tel[6]);
                printf(" ");
                printf("%c", cliente.tel[7]);
                printf("%c", cliente.tel[8]);
                printf("|\n");
                printf("\t|-------------------------------------------------|-----------------------------|--------------|-----|------------|\n");


                desplazamiento= posicion* sizeof(cliente);
                fseek(p2, desplazamiento, 0);
                fwrite(&cliente, sizeof(cliente), 1, p2);
                getch();
            }
        }
    }
    fflush(p2);
    fclose(p2);
}



