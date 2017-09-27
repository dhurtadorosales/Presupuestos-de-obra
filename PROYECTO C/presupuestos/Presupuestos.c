#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define FICHERO1 "PRECIOS.DAT"
#define FICHERO2 "CLIENTES.DAT"
#define FICHERO3 "PRESUPUESTOS.DAT"
#define FICHERO4 "PARTIDAS.DAT"
#define anno 16

    //ESTRUCTURA DE PRECIOS
    typedef struct{
        char letra_capitulo;
        int cod_precio;
        char unidad[4];
        char descripcion[40];
        float mano_obra;
        float material;
        float costes_indirectos;
        float precio_unitario;
    }Precio;
    static Precio precio;

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

    //ESTRUCTURA DE PRESUPUESTO
    typedef struct{
        int numero_presupuesto;
        char nombre_presupuesto[50];
        Cliente cliente_presupuesto;
        float suma;
        float gastos_generales;
        float beneficio_industrial;
        float base_imponible;
        float iva;
        float total_presupuesto;
    }Presupuesto;
    static Presupuesto presupuesto;

    //ESTRUCTURA DE PARTIDA
    typedef struct{
        int numero_partida;
        int numero_registro;
        float cantidad_partida;
        char unidad4[4];
        char descripcion4[40];
        float precio_unitario4;
        float importe_partida;
    }Partida;
    static Partida partida;

    //ESTRUCTURA REGISTRO 01
    typedef struct{
        long int nregistros;    //numero registros totales
        long int nd;            //numero registros demoliciones
        long int ne;            //numero registros estructuras
        long int nt;            //numero registros tabiqueria
        long int ni;            //numero registros instalaciones
        long int nc;            //numero registros carpinterias
        long int na;            //numero registros acabados
        long int nu;            //numero registros urbanizacion
        long int ns;            //numero registros seguridad y salud
        char blanco[30];
    }Primer_registro1;
    static Primer_registro1 registro01;

    //ESTRUCTURA REGISTRO 02
    typedef struct{
        long int nregistros;    //numero registros totales
        char blanco[174];
    }Primer_registro2;
    static Primer_registro2 registro02;

    //ESTRUCTURA REGISTRO 03
    typedef struct{
        long int nregistros;    //numero registros totales
        char blanco[254];
    }Primer_registro3;
    static Primer_registro3 registro03;

    //ESTRUCTURA REGISTRO 04
    typedef struct{
        long int nregistros;    //numero registros totales
        char blanco[58];
    }Primer_registro4;
    static Primer_registro4 registro04;

    //PUNTEROS A FICHEROS
    FILE* p1;
    FILE* p2;
    FILE* p3;
    FILE* p4;

    //FUNCIONES PRECIOS
    void altas_presupuesto();
    void asignar_cliente();
    void calculo_presupuesto();
    void imprimir_presupuesto();
    void seleccionar_cliente();
    void seleccionar_precio();
    void listados_presupuesto();
    void modificar_presupuesto();
    void modificar_cliente_presupuesto(int);
    void modificar_partida_presupuesto(int);


int mainPresupuestos(){

    //VARIABLES
    int caso, k;
    int long nregistros;

    //FUNCION
    p3= fopen(FICHERO3, "rb");
    if(p3== NULL){
        system("cls");
        printf("\tEl fichero PRESUPUESTOS.DAT no existe. Pulse cualquier tecla para crearlo.\n");
        getch();
        fclose(p3);
        p3= fopen(FICHERO3, "w+b");

        fseek(p3, 0L, 0);
        nregistros= 0L;
        registro03.nregistros= nregistros;

        for(k= 0; k< 254; k++)
            registro03.blanco[k]= ' ';

        fseek(p3, 0L, 0);
        fwrite(&registro03, sizeof(registro03), 1, p3);
        printf("\tFichero creado.\n\tPulse cualquier tecla para continuar.");
        getch();
    }
    fclose(p3);

    p4= fopen(FICHERO4, "rb");
    if(p4== NULL){
        system("cls");
        printf("\tEl fichero PARTIDAS.DAT no existe. Pulse cualquier tecla para crearlo.\n");
        getch();
        fclose(p4);
        p4= fopen(FICHERO4, "w+b");

        fseek(p4, 0L, 0);
        nregistros= 0L;
        registro04.nregistros= nregistros;

        for(k= 0; k< 78; k++)
            registro04.blanco[k]= ' ';

        fseek(p4, 0L, 0);
        fwrite(&registro04, sizeof(registro04), 1, p4);
        printf("\tFichero creado.\n\tPulse cualquier tecla para continuar.");
        getch();
    }
    fclose(p4);

   while(1){
        system("cls");
        printf("\n\n");
        printf("\t|---------------------------------|\n");
        printf("\t|    MENU PRESUPUESTOS            |\n");
        printf("\t|---------------------------------|\n");
        printf("\t|    CREAR NUEVO PRESUPUESTO  | 1 |\n");
        printf("\t|    LISTADO DE PRESUPUESTOS  | 2 |\n");
        printf("\t|    MODIFICAR PRESUPUESTO    | 3 |\n");
        printf("\t|    FINALIZAR PRESUPUESTOS   | 0 |\n");
        printf("\t|---------------------------------|\n\n");

        printf("\tQue desea hacer? Pulse la tecla correspondiente.\n\n\t");

        scanf("%d", &caso);
        switch(caso){
            case 1: altas_presupuesto();
                    break;
            case 2: listados_presupuesto();
                    break;
            case 3: modificar_presupuesto();
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

void altas_presupuesto(){

    //VARIABLES LOCALES
    char opcion;
    long int n3, desplazamiento;
    int k, i, caso;

    //EJECUCION
    p3= fopen(FICHERO3, "r+b");
    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    while(1){
        printf("\n\tSe va a crear un nuevo presupuesto. Desea continuar? (s/n)");
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
            n3++;
            presupuesto.numero_presupuesto= n3;
            desplazamiento= n3* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fwrite(&presupuesto, sizeof(presupuesto), 1, p3);

            registro03.nregistros= n3;
            for(k= 0; k< 254; k++)
                registro03.blanco[k]= ' ';
            fseek(p3, 0L, 0);
            fwrite(&registro03, sizeof(registro03), 1, p3);

            while(1){
                system("cls");
                printf("\n\n");
                printf("\t|---------------------------------|\n");
                printf("\t|    PRESUPUESTO %ld/%d             |\n", presupuesto.numero_presupuesto, anno);
                printf("\t|---------------------------------|\n");
                printf("\t|    NOMBRE PRESUPUESTO       | 1 |\n");
                printf("\t|    ASIGNAR CLIENTE          | 2 |\n");
                printf("\t|    CALCULO DE PRESUPUESTO   | 3 |\n");
                printf("\t|    IMPRIMIR PRESUPUESTO     | 4 |\n");
                printf("\t|    FINALIZAR PRESUPUESTO    | 0 |\n");
                printf("\t|---------------------------------|\n\n");

                printf("\tQue desea hacer? Pulse la tecla correspondiente. ");

                scanf("%d", &caso);
                switch(caso){
                    case 1: system("cls");
                            printf("\n\tIntroduzca nombre del presupuesto: ");
                            fflush(stdin);
                            gets(presupuesto.nombre_presupuesto);
                            desplazamiento= n3* sizeof(presupuesto);
                            fseek(p3, desplazamiento, 0);
                            fwrite(&presupuesto, sizeof(presupuesto), 1, p3);

                            registro03.nregistros= n3;
                            for(k= 0; k< 254; k++)
                                registro03.blanco[k]= ' ';
                            fseek(p3, 0L, 0);
                            fwrite(&registro03, sizeof(registro03), 1, p3);
                            break;

                    case 2: fclose(p3);
                            asignar_cliente();
                            p3= fopen(FICHERO3, "r+b");
                            break;
                    case 3: fclose(p3);
                            calculo_presupuesto();
                            p3= fopen(FICHERO3, "r+b");
                            break;
                    case 4: fclose(p3);
                            imprimir_presupuesto();
                            p3= fopen(FICHERO3, "r+b");
                            break;
                    case 0:
                            return 0;
                    default: printf("\tSeleccion incorrecta.\n\tPulse cualquier tecla");
                        getch();
                        break;
                }
            }
            desplazamiento= n3* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fwrite(&presupuesto, sizeof(presupuesto), 1, p3);

            registro03.nregistros= n3;
            for(k= 0; k< 254; k++)
                registro03.blanco[k]= ' ';
            fseek(p3, 0L, 0);
            fwrite(&registro03, sizeof(registro03), 1, p3);
        }
    }
    fclose(p3);
}

void asignar_cliente(){

    //VARIABLES LOCALES
    char opcion;
    long int n3, desplazamiento;
    int k, i;


    //EJECUCION
    p3= fopen(FICHERO3, "r+b");
    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    while(1){
        printf("\tDesea finalizar la asignacion de cliente? (s/n)\n\t");
        fflush(stdin);
        scanf("%c", &opcion);

        if((opcion>=97) && (opcion<=122))
            opcion= opcion- 32;

        if(opcion== 'S')
            break;
        if((opcion!= 'S') && (opcion!= 'N')){
            printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar\n");
            getch();
            continue;
        }
        if(opcion== 'N'){

            desplazamiento= n3* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fread(&presupuesto, sizeof(presupuesto), 1, p3);

            while(1){
                system("cls");
                printf("\n\n");
                printf("\t|--------------------------------|\n");
                printf("\t|    ASIGNAR CLIENTE             |\n");
                printf("\t|--------------------------------|\n");
                printf("\t|    PRESUPUESTO %ld/%d            |\n", presupuesto.numero_presupuesto, anno);
                printf("\t|--------------------------------|\n");
                printf("\t|    SELECCIONAR CLIENTE     | S |\n");
                printf("\t|    CREAR NUEVO CLIENTE     | C |\n");
                printf("\t|    SALIR                   | 0 |\n");
                printf("\t|--------------------------------|\n\n");
                printf("\tQue desea hacer? Pulse la tecla correspondiente.\n\n\t");

                fflush(stdin);
                scanf("%c", &opcion);
                if(opcion== '0')
                    break;

                switch(opcion){
                    case 'S': case 's': fclose(p3);
                                        seleccionar_cliente();
                                        p3= fopen(FICHERO3, "r+b");
                                        continue;
                    case 'C': case 'c': fclose(p3);
                                        mainClientes();
                                        p3= fopen(FICHERO3, "r+b");
                                        break;
                    default: printf("\tSeleccion incorrecta\n. Pulse cualquier tecla");
                            getch();
                            break;

                }
            }
        }
    }
    fclose(p3);
}

void seleccionar_cliente(){

    //VARIABLES
    long int n2, n3, desplazamiento;
    int k, i, j, sw, posicion;
    int buscar;
    char opcion2;

    //EJECUCION
    p2= fopen(FICHERO2, "r+b");
    p3= fopen(FICHERO3, "r+b");

    fseek(p2, 0L, 0);
    fread(&registro02, sizeof(registro02), 1, p2);
    n2= registro02.nregistros;

    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    desplazamiento= n3* sizeof(presupuesto);
    fseek(p3, desplazamiento, 0);
    fread(&presupuesto, sizeof(presupuesto), 1, p3);

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

        //SELECCION DE CLIENTE
        printf("\n\n\tSeleccione el numero de cliente: ");
        fflush(stdin);
        scanf("%d", &buscar);


        for(i= 1; i<= n2; i++){
            sw= 0;
            desplazamiento= i* sizeof(cliente);
            fseek(p2, desplazamiento, 0);
            fread(&cliente, sizeof(cliente), 1, p2);
            if(buscar==cliente.numero_cliente){
                posicion= i;
                sw= 1;
                break;
            }
        }
        if(sw== 0){
            printf("\tEste cliente no existe\n");
            getch();
        }
        if(sw== 1){

            system("cls");
            printf("\n\tEl presupuesto %ld/16 sera asignado al cliente: \n\n", presupuesto.numero_presupuesto);
            printf("\t|-----------------------------------------------------------------------------|\n");
            printf("\t|                           LISTADO DE CLIENTES                               |\n");
            printf("\t|----|---------|-------------------------------------------------|------------|\n");
            printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
            printf("\t|----|---------|-------------------------------------------------|------------|\n");

            desplazamiento= posicion* sizeof(cliente);
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
            printf("\t|-----------------------------------------------------------------------------|\n");
        }
        printf("\n\tDesea asignar este cliente? (s/n): ");
        fflush(stdin);
        scanf("%c", &opcion2);

        if((opcion2>=97) && (opcion2<=122))
            opcion2= opcion2- 32;

        if(opcion2== 'N')
            break;
        if((opcion2!= 'S') && (opcion2!= 'N')){
            printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar. ");
            getch();
            continue;
        }
        if(opcion2== 'S'){
            presupuesto.cliente_presupuesto= cliente;

            desplazamiento= n3* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fwrite(&presupuesto, sizeof(presupuesto), 1, p3);
            break;
        }

    }

    fflush(p2);
    fclose(p2);
    fflush(p3);
    fclose(p3);
}

void calculo_presupuesto(){

    //VARIABLES LOCALES
    char opcion;
    long int n3, desplazamiento;
    int k, i;


    //EJECUCION
    p3= fopen(FICHERO3, "r+b");
    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    while(1){
        printf("\tDesea finalizar el calculo? (s/n)\n\t");
        fflush(stdin);
        scanf("%c", &opcion);

        if((opcion>=97) && (opcion<=122))
            opcion= opcion- 32;

        if(opcion== 'S')
            break;
        if((opcion!= 'S') && (opcion!= 'N')){
            printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar\n");
            getch();
            continue;
        }
        if(opcion== 'N'){
            desplazamiento= n3* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fread(&presupuesto, sizeof(presupuesto), 1, p3);

            system("cls");
            printf("\n\n");
            printf("\t|--------------------------------|\n");
            printf("\t|    CALCULO DE PRESUPUESTO      |\n");
            printf("\t|--------------------------------|\n");
            printf("\t|    PRESUPUESTO %ld/%d            |\n", presupuesto.numero_presupuesto, anno);
            printf("\t|--------------------------------|\n");
            printf("\t|    SELECCIONAR PRECIO      | S |\n");
            printf("\t|    CREAR NUEVO PRECIO      | C |\n");
            printf("\t|    SALIR                   | 0 |\n");
            printf("\t|--------------------------------|\n\n");
            printf("\tQue desea hacer? Pulse la tecla correspondiente.\n\n\t");

            fflush(stdin);
            scanf("%c", &opcion);
            if(opcion== '0')
                break;

            switch(opcion){
                case 'S': case 's': fclose(p3);
                                    seleccionar_precio();
                                    p3= fopen(FICHERO3, "r+b");
                                    break;
                case 'C': case 'c': fclose(p3);
                                    mainPrecios();
                                    p3= fopen(FICHERO3, "r+b");
                                    break;
                default: printf("\tSeleccion incorrecta\n. Pulse cualquier tecla");
                        getch();
                        break;
            }
        }
    }
    fclose(p3);
}

void seleccionar_precio(){

    //VARIABLES
    long int n1, n3, n4, desplazamiento, nd, ne, nt, ni, nc, na, nu, ns;
    int k, i, j, sw, posicion, buscar;
    char opcion2;
    float cantidad, suma= 0, precio2;

    //EJECUCION
    p1= fopen(FICHERO1, "r+b");
    p3= fopen(FICHERO3, "r+b");
    p4= fopen(FICHERO4, "r+b");

    fseek(p1, 0L, 0);
    fread(&registro01, sizeof(registro01), 1, p1);
    n1= registro01.nregistros;
    nd= registro01.nd;
    ne= registro01.ne;
    nt= registro01.nt;
    ni= registro01.ni;
    nc= registro01.nc;
    na= registro01.na;
    nu= registro01.nu;
    ns= registro01.ns;

    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    while(1){
        system("cls");
        printf("\n\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    SELECCIONAR PRECIO          |\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    CAPITULOS                   |\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    DEMOLICIONES            | D |\n");
        printf("\t|    ESTRUCTURAS             | E |\n");
        printf("\t|    TABIQUERIA              | T |\n");
        printf("\t|    INSTALACIONES           | I |\n");
        printf("\t|    CARPINTERIAS            | C |\n");
        printf("\t|    ACABADOS                | A |\n");
        printf("\t|    URBANIZACION            | U |\n");
        printf("\t|    SEGURIDAD Y SALUD       | S |\n");
        printf("\t|    SALIR                   | 0 |\n");
        printf("\t|--------------------------------|\n\n");
        printf("\tQue desea hacer? Pulse la tecla correspondiente.\n\n\t");

        fflush(stdin);
        scanf("%c", &opcion2);
        if(opcion2== '0')
            break;
        else{
            if((opcion2>=97) && (opcion2<=122))
                opcion2= opcion2- 32;

            system("cls");
            printf("\n\n");
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
            printf("\t|COD    |UD     |DESCRIPCION                                    |     PRECIO       |\n");
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
            for(i= 1; i<= n1; i++){
                desplazamiento= i* sizeof(precio);
                fseek(p1, desplazamiento, 0);
                fread(&precio, sizeof(precio), 1, p1);
                if(opcion2== precio.letra_capitulo){
                    printf("\t|%c%04d\t|%s\t|%s", precio.letra_capitulo, precio.cod_precio, precio.unidad, precio.descripcion);
                    for(j= (strlen(precio.descripcion)+1); j< 40; j++)
                        printf(" ");
                    printf("\t|%9.2f Euros/%s|\n", precio.precio_unitario, precio.unidad);

                }
            }
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
        }

        printf("\n\n\tSeleccione precio\n");
        printf("\tNumero (%c00..._): ", opcion2);
        fflush(stdin);
        scanf("%d", &buscar);

        sw= 0;
        for(i= 1; i<= n1; i++){
            desplazamiento= i* sizeof(precio);
            fseek(p1, desplazamiento, 0);
            fread(&precio, sizeof(precio), 1, p1);
            if(opcion2== precio.letra_capitulo){
                if(buscar== precio.cod_precio){
                    posicion= i;
                    sw= 1;
                    break;
                }
            }
        }
        if(sw== 0){
            printf("\tEste numero no existe\n");
            getch();
            continue;
        }
        if(sw== 1){
            printf("\tSe ha seleccionado el precio: %c%04d\n\tDesea continuar? (s/n)\n\t", precio.letra_capitulo, precio.cod_precio);
            fflush(stdin);
            scanf("%c", &opcion2);

            if((opcion2>=97) && (opcion2<=122))
                opcion2= opcion2- 32;

            if(opcion2== 'N')
                break;
            if((opcion2!= 'S') && (opcion2!= 'N')){
                printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar\n");
                getch();
                continue;
            }
            if(opcion2== 'S'){
                system("cls");
                printf("\t|-------|-------|-----------------------------------------------|---------|---------|-----|---------------|\n");
                printf("\t|COD    |UD     |DESCRIPCION                                    |MANO OBRA| MATERIAL| C.I |precio UNITARIO|\n");
                printf("\t|-------|-------|-----------------------------------------------|---------|---------|-----|---------------|\n");
                printf("\t|%c%04d\t|%s\t|%s", precio.letra_capitulo, precio.cod_precio, precio.unidad, precio.descripcion);
                for(j= (strlen(precio.descripcion)+1); j< 40; j++)
                    printf(" ");
                printf("\t|%9.2f|%9.2f| %.2f|      %9.2f|\n", precio.mano_obra, precio.material, precio.costes_indirectos, precio.precio_unitario);
                printf("\t|-------|-------|-----------------------------------------------|---------|---------|-----|---------------|\n");

                printf("\n\tCANTIDAD: ");
                fflush(stdin);
                scanf("%f", &cantidad);

                fseek(p4, 0L, 0);
                fread(&registro04, sizeof(registro04), 1, p4);
                n4= registro04.nregistros;

                n4++;
                partida.numero_partida= presupuesto.numero_presupuesto;
                partida.numero_registro= n4;
                partida.cantidad_partida= cantidad;
                strcpy(partida.unidad4,precio.unidad);
                strcpy(partida.descripcion4,precio.descripcion);
                partida.precio_unitario4= precio.precio_unitario;
                partida.importe_partida= partida.cantidad_partida* partida.precio_unitario4;

                desplazamiento= n4* sizeof(partida);
                fseek(p4, desplazamiento, 0);
                fwrite(&partida, sizeof(partida), 1, p4);

                registro04.nregistros= n4;
                for(k= 0; k< 58; k++)
                    registro04.blanco[k]= ' ';
                fseek(p4, 0L, 0);
                fwrite(&registro04, sizeof(registro04), 1, p4);

                printf("\n\tTOTAL PARTIDA: %.2f\n", partida.importe_partida);
                suma= suma+ partida.importe_partida;
                printf("\n\tTOTAL ACUMULADO: %.2f\n\n", suma);

                printf("\tDesea crear otra partida? (s/n)\n\t");
                fflush(stdin);
                scanf("%c", &opcion2);

                if((opcion2>=97) && (opcion2<=122))
                opcion2= opcion2- 32;

                if(opcion2== 'N'){
                    presupuesto.suma= suma;
                    presupuesto.gastos_generales= presupuesto.suma* 0.13;
                    presupuesto.beneficio_industrial= presupuesto.suma* 0.06;
                    presupuesto.base_imponible= presupuesto.suma+ presupuesto.gastos_generales+ presupuesto.beneficio_industrial;
                    presupuesto.iva= presupuesto.base_imponible* 0.21;
                    presupuesto.total_presupuesto= presupuesto.base_imponible+ presupuesto.iva;

                    desplazamiento= n3* sizeof(presupuesto);
                    fseek(p3, desplazamiento, 0);
                    fwrite(&presupuesto, sizeof(presupuesto), 1, p3);
                    break;
                }
                if((opcion2!= 'S') && (opcion2!= 'N')){
                    printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar\n");
                    getch();
                    continue;
                }
                if(opcion2== 'S')
                    continue;
            }
        }
    }
    presupuesto.numero_presupuesto= 0;
    for(i= 0; i<= strlen(presupuesto.nombre_presupuesto)-1; i++)
        presupuesto.nombre_presupuesto[i]= ' ';
    Cliente cliente_presupuesto;
    presupuesto.suma= 0;
    presupuesto.gastos_generales= 0;
    presupuesto.beneficio_industrial= 0;
    presupuesto.base_imponible= 0;
    presupuesto.iva= 0;
    presupuesto.total_presupuesto= 0;
    fflush(p1);
    fclose(p1);
    fflush(p3);
    fclose(p3);
    fflush(p4);
    fclose(p4);
}

void imprimir_presupuesto(){

     //VARIABLES LOCALES
    char opcion;
    long int n3, n4, desplazamiento;
    int k, i, j, caso;

    //EJECUCION
    p3= fopen(FICHERO3, "rb");
    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    p4= fopen(FICHERO4, "rb");
    fseek(p4, 0L, 0);
    fread(&registro04, sizeof(registro04), 1, p4);
    n4= registro04.nregistros;

    desplazamiento= n3* sizeof(presupuesto);
    fseek(p3, desplazamiento, 0);
    fread(&presupuesto, sizeof(presupuesto), 1, p3);

    system("cls");
    printf("\n");
    printf("\t|-----------------------------------------------------------------------------|\n");
    printf("\t|    PRESUPUESTO %ld/%d                                                         |\n", presupuesto.numero_presupuesto, anno);
    printf("\t|-----------------------------------------------------------------------------|\n");
    printf("\t|    CLIENTE                                                                  |\n");
    printf("\t|-----------------------------------------------------------------------------|\n");
    printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
    printf("\t|----|---------|-------------------------------------------------|------------|\n");

    printf("\t|%0d   |%s|%s", presupuesto.cliente_presupuesto.numero_cliente, presupuesto.cliente_presupuesto.cif, presupuesto.cliente_presupuesto.nombre);
    for(j= (strlen(presupuesto.cliente_presupuesto.nombre)+1); j< 50; j++)
        printf(" ");
    printf("|");
    printf("%c", presupuesto.cliente_presupuesto.tel[0]);
    printf("%c", presupuesto.cliente_presupuesto.tel[1]);
    printf("%c", presupuesto.cliente_presupuesto.tel[2]);
    printf(" ");
    printf("%c", presupuesto.cliente_presupuesto.tel[3]);
    printf("%c", presupuesto.cliente_presupuesto.tel[4]);
    printf(" ");
    printf("%c", presupuesto.cliente_presupuesto.tel[5]);
    printf("%c", presupuesto.cliente_presupuesto.tel[6]);
    printf(" ");
    printf("%c", presupuesto.cliente_presupuesto.tel[7]);
    printf("%c", presupuesto.cliente_presupuesto.tel[8]);
    printf("|\n");
    printf("\t|-----------------------------------------------------------------------------|\n");
    printf("\t                                                                               \n");
    printf("\t   OBRA: %s", presupuesto.nombre_presupuesto);
    printf("\n");
    printf("\t                                                                               \n");
    printf("\t|-----------------------------------------------------------------------------|\n");
    printf("\t| UD   CONCEPTO                                 CANTIDAD  PRECIO    IMPORTE   |\n");
    printf("\t|-----------------------------------------------------------------------------|\n");
    for(i= 1; i<= n4; i++){
        desplazamiento= i* sizeof(partida);
        fseek(p4, desplazamiento, 0);
        fread(&partida, sizeof(partida), 1, p4);
        if(presupuesto.numero_presupuesto==partida.numero_partida){
            printf("\t|%s | %s", partida.unidad4, partida.descripcion4);
            for(j= (strlen(partida.descripcion4)+1); j< 42; j++)
                printf(" ");

            printf("|  %6.2f|  %6.2f|      %6.2f|\n", partida.cantidad_partida, partida.precio_unitario4, partida.importe_partida);
        }
    }
    printf("\t|   |                                          |        |        |            |\n");
    printf("\t|   |                                          |        |        |            |\n");
    printf("\t|----------------------------------------------------------------|------------|\n");
    printf("\t|                                    |Suma                       |      %6.2f|\n", presupuesto.suma);
    printf("\t|                                    |Gastos generales           |      %6.2f|\n", presupuesto.gastos_generales);
    printf("\t|                                    |Beneficio industrial       |      %6.2f|\n", presupuesto.beneficio_industrial);
    printf("\t|                                    |---------------------------|------------|\n");
    printf("\t|                                    |Base imponible             |      %6.2f|\n", presupuesto.base_imponible);
    printf("\t|                                    |I.V.A. 21                  |      %6.2f|\n", presupuesto.iva);
    printf("\t|                                    |---------------------------|------------|\n");
    printf("\t|                                    |TOTAL                      |      %6.2f|\n", presupuesto.total_presupuesto);
    printf("\t|-----------------------------------------------------------------------------|\n");

    printf("\n\tPulse cualquier tecla para volver.");

    getch();
    fclose(p3);
    fclose(p4);
}

void listados_presupuesto(){
    //VARIABLES LOCALES
    char opcion;
    long int n3, n4, desplazamiento;
    int i, j, buscar, sw;

    //FUNCION
    p3= fopen(FICHERO3, "r+b");
    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    p4= fopen(FICHERO4, "r+b");
    fseek(p4, 0L, 0);
    fread(&registro04, sizeof(registro04), 1, p4);
    n4= registro04.nregistros;

    while(1){
        system("cls");
        printf("\n\n");
        printf("\t|-----------------------------------------------------------------------------|\n");
        printf("\t|                           LISTADO DE PRESUPUESTOS                           |\n");
        printf("\t|----|-----------------------------------------------------------|------------|\n");
        printf("\t|NUM.|NOMBRE DE PRESUPUESTO                                      |IMPORTE     |\n");
        printf("\t|----|-----------------------------------------------------------|------------|\n");

        for(i= 1; i<= n3; i++){
            desplazamiento= i* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fread(&presupuesto, sizeof(presupuesto), 1, p3);

            printf("\t|  %0d |%s", presupuesto.numero_presupuesto, presupuesto.nombre_presupuesto);

            for(j= (strlen(presupuesto.nombre_presupuesto)+1); j< 50; j++)
                printf(" ");
            printf("          |      %6.2f|\n", presupuesto.total_presupuesto);
        }
        printf("\t|-----------------------------------------------------------------------------|\n");

        printf("\n\tSeleccione el numero de presupuesto para ver mas detalles o pulse 0 para salir.");
        fflush(stdin);
        scanf("%d", &buscar);
        if (buscar==0)
            break;
        if(buscar!= 0){
            for(i= 1; i<= n3; i++){
                sw= 0;
                desplazamiento= i* sizeof(presupuesto);
                fseek(p3, desplazamiento, 0);
                fread(&presupuesto, sizeof(presupuesto), 1, p3);
                if(buscar== presupuesto.numero_presupuesto){
                    sw= 1;
                    break;
                }
            }
            if(sw==1){
                system("cls");
                printf("\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t|    PRESUPUESTO %ld/%d                                                         |\n", presupuesto.numero_presupuesto, anno);
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t|    CLIENTE                                                                  |\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
                printf("\t|----|---------|-------------------------------------------------|------------|\n");

                printf("\t|%0d   |%s|%s", presupuesto.cliente_presupuesto.numero_cliente, presupuesto.cliente_presupuesto.cif, presupuesto.cliente_presupuesto.nombre);
                for(j= (strlen(presupuesto.cliente_presupuesto.nombre)+1); j< 50; j++)
                    printf(" ");
                printf("|");
                printf("%c", presupuesto.cliente_presupuesto.tel[0]);
                printf("%c", presupuesto.cliente_presupuesto.tel[1]);
                printf("%c", presupuesto.cliente_presupuesto.tel[2]);
                printf(" ");
                printf("%c", presupuesto.cliente_presupuesto.tel[3]);
                printf("%c", presupuesto.cliente_presupuesto.tel[4]);
                printf(" ");
                printf("%c", presupuesto.cliente_presupuesto.tel[5]);
                printf("%c", presupuesto.cliente_presupuesto.tel[6]);
                printf(" ");
                printf("%c", presupuesto.cliente_presupuesto.tel[7]);
                printf("%c", presupuesto.cliente_presupuesto.tel[8]);
                printf("|\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t                                                                               \n");
                printf("\t   OBRA: %s", presupuesto.nombre_presupuesto);
                printf("\n");
                printf("\t                                                                               \n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t| UD   CONCEPTO                                 CANTIDAD  PRECIO    IMPORTE   |\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                for(i= 1; i<= n4; i++){
                    desplazamiento= i* sizeof(partida);
                    fseek(p4, desplazamiento, 0);
                    fread(&partida, sizeof(partida), 1, p4);
                    if(presupuesto.numero_presupuesto==partida.numero_partida){
                        printf("\t|%s | %s", partida.unidad4, partida.descripcion4);
                        for(j= (strlen(partida.descripcion4)+1); j< 42; j++)
                            printf(" ");

                        printf("|  %6.2f|  %6.2f|      %6.2f|\n", partida.cantidad_partida, partida.precio_unitario4, partida.importe_partida);
                    }
                }
                printf("\t|   |                                          |        |        |            |\n");
                printf("\t|   |                                          |        |        |            |\n");
                printf("\t|----------------------------------------------------------------|------------|\n");
                printf("\t|                                    |Suma                       |      %6.2f|\n", presupuesto.suma);
                printf("\t|                                    |Gastos generales           |      %6.2f|\n", presupuesto.gastos_generales);
                printf("\t|                                    |Beneficio industrial       |      %6.2f|\n", presupuesto.beneficio_industrial);
                printf("\t|                                    |---------------------------|------------|\n");
                printf("\t|                                    |Base imponible             |      %6.2f|\n", presupuesto.base_imponible);
                printf("\t|                                    |I.V.A. 21                  |      %6.2f|\n", presupuesto.iva);
                printf("\t|                                    |---------------------------|------------|\n");
                printf("\t|                                    |TOTAL                      |      %6.2f|\n", presupuesto.total_presupuesto);
                printf("\t|-----------------------------------------------------------------------------|\n");

                printf("\n\tPulse cualquier tecla para volver.");
                getch();
            }
        }
    }

    fflush(p3);
    fclose(p3);
    fflush(p4);
    fclose(p4);
}

void modificar_presupuesto(){
    //VARIABLES LOCALES
    char opcion, opcion2, opcion3;
    long int n3, n4, desplazamiento;
    int i, j, buscar, sw, posicion;
    float suma;

    //LISTADO
    p3= fopen(FICHERO3, "r+b");
    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    p4= fopen(FICHERO4, "r+b");
    fseek(p4, 0L, 0);
    fread(&registro04, sizeof(registro04), 1, p4);
    n4= registro04.nregistros;

    while(1){
        system("cls");
        printf("\n\n");

        printf("\t|-----------------------------------------------------------------------------|\n");
        printf("\t|                           LISTADO DE PRESUPUESTOS                           |\n");
        printf("\t|----|-----------------------------------------------------------|------------|\n");
        printf("\t|NUM.|NOMBRE DE PRESUPUESTO                                      |IMPORTE     |\n");
        printf("\t|----|-----------------------------------------------------------|------------|\n");

        for(i= 1; i<= n3; i++){
            desplazamiento= i* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fread(&presupuesto, sizeof(presupuesto), 1, p3);

            printf("\t|  %0d |%s", presupuesto.numero_presupuesto, presupuesto.nombre_presupuesto);

            for(j= (strlen(presupuesto.nombre_presupuesto)+1); j< 50; j++)
                printf(" ");
            printf("          |      %6.2f|\n", presupuesto.total_presupuesto);
        }
        printf("\t|-----------------------------------------------------------------------------|\n");

        //MODIFICACION
        printf("\n\n\tSeleccione el numero de presupuesto que desea modificar.\n\tPara salir pulse 0\n");
        printf("\tNumero de presupuesto: ");
        fflush(stdin);
        scanf("%d", &buscar);
        if (buscar==0)
            break;

        sw= 0;
        for(i= 1; i<= n3; i++){
            desplazamiento= i* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fread(&presupuesto, sizeof(presupuesto), 1, p3);
            if(buscar== presupuesto.numero_presupuesto){
                posicion= i;
                sw= 1;
                break;
            }
        }
        if(sw== 0){
            printf("\tEste presupuesto no existe\n");
            getch();
            continue;
        }
        if(sw== 1){
            system("cls");
            printf("\tSe va a modificar el presupuesto: \n");

            printf("\n");
            printf("\t|-----------------------------------------------------------------------------|\n");
            printf("\t|    PRESUPUESTO %ld/%d                                                         |\n", presupuesto.numero_presupuesto, anno);
            printf("\t|-----------------------------------------------------------------------------|\n");
            printf("\t|    CLIENTE                                                                  |\n");
            printf("\t|-----------------------------------------------------------------------------|\n");
            printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
            printf("\t|----|---------|-------------------------------------------------|------------|\n");

            printf("\t|%0d   |%s|%s", presupuesto.cliente_presupuesto.numero_cliente, presupuesto.cliente_presupuesto.cif, presupuesto.cliente_presupuesto.nombre);
            for(j= (strlen(presupuesto.cliente_presupuesto.nombre)+1); j< 50; j++)
                printf(" ");
            printf("|");
            printf("%c", presupuesto.cliente_presupuesto.tel[0]);
            printf("%c", presupuesto.cliente_presupuesto.tel[1]);
            printf("%c", presupuesto.cliente_presupuesto.tel[2]);
            printf(" ");
            printf("%c", presupuesto.cliente_presupuesto.tel[3]);
            printf("%c", presupuesto.cliente_presupuesto.tel[4]);
            printf(" ");
            printf("%c", presupuesto.cliente_presupuesto.tel[5]);
            printf("%c", presupuesto.cliente_presupuesto.tel[6]);
            printf(" ");
            printf("%c", presupuesto.cliente_presupuesto.tel[7]);
            printf("%c", presupuesto.cliente_presupuesto.tel[8]);
            printf("|\n");
            printf("\t|-----------------------------------------------------------------------------|\n");
            printf("\t                                                                               \n");
            printf("\t   OBRA: %s", presupuesto.nombre_presupuesto);
            printf("\n");
            printf("\t                                                                               \n");
            printf("\t|-----------------------------------------------------------------------------|\n");
            printf("\t| UD   CONCEPTO                                 CANTIDAD  PRECIO    IMPORTE   |\n");
            printf("\t|-----------------------------------------------------------------------------|\n");
            for(i= 1; i<= n4; i++){
                desplazamiento= i* sizeof(partida);
                fseek(p4, desplazamiento, 0);
                fread(&partida, sizeof(partida), 1, p4);
                if(presupuesto.numero_presupuesto==partida.numero_partida){
                    printf("\t|%s | %s", partida.unidad4, partida.descripcion4);
                    for(j= (strlen(partida.descripcion4)+1); j< 42; j++)
                        printf(" ");

                    printf("|  %6.2f|  %6.2f|      %6.2f|\n", partida.cantidad_partida, partida.precio_unitario4, partida.importe_partida);
                }
            }
            printf("\t|   |                                          |        |        |            |\n");
            printf("\t|   |                                          |        |        |            |\n");
            printf("\t|----------------------------------------------------------------|------------|\n");
            printf("\t|                                    |Suma                       |      %6.2f|\n", presupuesto.suma);
            printf("\t|                                    |Gastos generales           |      %6.2f|\n", presupuesto.gastos_generales);
            printf("\t|                                    |Beneficio industrial       |      %6.2f|\n", presupuesto.beneficio_industrial);
            printf("\t|                                    |---------------------------|------------|\n");
            printf("\t|                                    |Base imponible             |      %6.2f|\n", presupuesto.base_imponible);
            printf("\t|                                    |I.V.A. 21                  |      %6.2f|\n", presupuesto.iva);
            printf("\t|                                    |---------------------------|------------|\n");
            printf("\t|                                    |TOTAL                      |      %6.2f|\n", presupuesto.total_presupuesto);
            printf("\t|-----------------------------------------------------------------------------|\n");

            printf("\n\tPulse cualquier tecla para volver.");

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
                while(1){
                    system("cls");
                    printf("\n\n\tElija el campo que desea modificar:\n");
                    printf("\n\n");
                    printf("\t|-------------------------------------|\n");
                    printf("\t|    Nombre de presupuesto        | 1 |\n");
                    printf("\t|    Cliente                      | 2 |\n");
                    printf("\t|    Anadir partida               | 3 |\n");
                    printf("\t|    Modificar/Eliminar partida   | 4 |\n");
                    printf("\t|    Finalizar modificacion       | 0 |\n");
                    printf("\t|-------------------------------------|\n\n");

                    fflush(stdin);
                    scanf("\t%d", &opcion3);
                    if(opcion3== 0)
                        break;
                    switch(opcion3){
                        case 1: system("cls");
                                printf("\n\tIntroduzca nombre del presupuesto: ");
                                fflush(stdin);
                                gets(presupuesto.nombre_presupuesto);
                                desplazamiento= posicion* sizeof(presupuesto);
                                fseek(p3, desplazamiento, 0);
                                fwrite(&presupuesto, sizeof(presupuesto), 1, p3);
                                break;

                        case 2: fclose(p3);
                                fclose(p4);
                                modificar_cliente_presupuesto(posicion);
                                p3= fopen(FICHERO3, "r+b");
                                p4= fopen(FICHERO4, "r+b");
                                break;

                        case 3: fclose(p3);
                                fclose(p4);
                                calculo_presupuesto();
                                p3= fopen(FICHERO3, "r+b");
                                p4= fopen(FICHERO4, "r+b");
                                fseek(p4, 0L, 0);
                                fread(&registro04, sizeof(registro04), 1, p4);
                                n4= registro04.nregistros;

                                suma= 0;
                                desplazamiento= posicion* sizeof(presupuesto);
                                fseek(p3, desplazamiento, 0);
                                fread(&presupuesto, sizeof(presupuesto), 1, p3);

                                for(i= 1; i<= n4; i++){
                                    desplazamiento= i* sizeof(partida);
                                    fseek(p4, desplazamiento, 0);
                                    fread(&partida, sizeof(partida), 1, p4);
                                    if(presupuesto.numero_presupuesto==partida.numero_partida){
                                        suma= suma+ partida.importe_partida;
                                    }
                                }
                                presupuesto.suma= suma;
                                presupuesto.gastos_generales= presupuesto.suma* 0.13;
                                presupuesto.beneficio_industrial= presupuesto.suma* 0.06;
                                presupuesto.base_imponible= presupuesto.suma+ presupuesto.gastos_generales+ presupuesto.beneficio_industrial;
                                presupuesto.iva= presupuesto.base_imponible* 0.21;
                                presupuesto.total_presupuesto= presupuesto.base_imponible+ presupuesto.iva;

                                desplazamiento= posicion* sizeof(presupuesto);
                                fseek(p3, desplazamiento, 0);
                                fwrite(&presupuesto, sizeof(presupuesto), 1, p3);

                                break;

                        case 4: fclose(p3);
                                fclose(p4);
                                modificar_partida_presupuesto(posicion);
                                p3= fopen(FICHERO3, "r+b");
                                p4= fopen(FICHERO4, "r+b");
                                break;


                        default: printf("\tSeleccion incorrecta.\n\tPulse cualquier tecla.\n");
                                getch();
                                break;
                    }
                }


                system("cls");
                printf("\tPresupuesto actualizado: (Pulse cualquier tecla para continuar)\n");

                printf("\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t|    PRESUPUESTO %ld/%d                                                         |\n", presupuesto.numero_presupuesto, anno);
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t|    CLIENTE                                                                  |\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
                printf("\t|----|---------|-------------------------------------------------|------------|\n");

                printf("\t|%0d   |%s|%s", presupuesto.cliente_presupuesto.numero_cliente, presupuesto.cliente_presupuesto.cif, presupuesto.cliente_presupuesto.nombre);
                for(j= (strlen(presupuesto.cliente_presupuesto.nombre)+1); j< 50; j++)
                    printf(" ");
                printf("|");
                printf("%c", presupuesto.cliente_presupuesto.tel[0]);
                printf("%c", presupuesto.cliente_presupuesto.tel[1]);
                printf("%c", presupuesto.cliente_presupuesto.tel[2]);
                printf(" ");
                printf("%c", presupuesto.cliente_presupuesto.tel[3]);
                printf("%c", presupuesto.cliente_presupuesto.tel[4]);
                printf(" ");
                printf("%c", presupuesto.cliente_presupuesto.tel[5]);
                printf("%c", presupuesto.cliente_presupuesto.tel[6]);
                printf(" ");
                printf("%c", presupuesto.cliente_presupuesto.tel[7]);
                printf("%c", presupuesto.cliente_presupuesto.tel[8]);
                printf("|\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t                                                                               \n");
                printf("\t   OBRA: %s", presupuesto.nombre_presupuesto);
                printf("\n");
                printf("\t                                                                               \n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                printf("\t| UD   CONCEPTO                                 CANTIDAD  PRECIO    IMPORTE   |\n");
                printf("\t|-----------------------------------------------------------------------------|\n");
                for(i= 1; i<= n4; i++){
                    desplazamiento= i* sizeof(partida);
                    fseek(p4, desplazamiento, 0);
                    fread(&partida, sizeof(partida), 1, p4);
                    if(presupuesto.numero_presupuesto==partida.numero_partida){
                        printf("\t|%s | %s", partida.unidad4, partida.descripcion4);
                        for(j= (strlen(partida.descripcion4)+1); j< 42; j++)
                            printf(" ");

                        printf("|  %6.2f|  %6.2f|      %6.2f|\n", partida.cantidad_partida, partida.precio_unitario4, partida.importe_partida);
                    }
                }
                printf("\t|   |                                          |        |        |            |\n");
                printf("\t|   |                                          |        |        |            |\n");
                printf("\t|----------------------------------------------------------------|------------|\n");
                printf("\t|                                    |Suma                       |      %6.2f|\n", presupuesto.suma);
                printf("\t|                                    |Gastos generales           |      %6.2f|\n", presupuesto.gastos_generales);
                printf("\t|                                    |Beneficio industrial       |      %6.2f|\n", presupuesto.beneficio_industrial);
                printf("\t|                                    |---------------------------|------------|\n");
                printf("\t|                                    |Base imponible             |      %6.2f|\n", presupuesto.base_imponible);
                printf("\t|                                    |I.V.A. 21                  |      %6.2f|\n", presupuesto.iva);
                printf("\t|                                    |---------------------------|------------|\n");
                printf("\t|                                    |TOTAL                      |      %6.2f|\n", presupuesto.total_presupuesto);
                printf("\t|-----------------------------------------------------------------------------|\n");

                printf("\n\tPulse cualquier tecla para volver.");

                getch();
            }
        }
    }
    fflush(p3);
    fclose(p3);
    fflush(p4);
    fclose(p4);
}

void modificar_cliente_presupuesto(int posicion){

    //VARIABLES
    long int n2, n3, desplazamiento;
    int k, i, j, sw;
    int buscar, posicion2;
    char opcion2;

    //EJECUCION
    p2= fopen(FICHERO2, "r+b");
    p3= fopen(FICHERO3, "r+b");

    fseek(p2, 0L, 0);
    fread(&registro02, sizeof(registro02), 1, p2);
    n2= registro02.nregistros;

    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    desplazamiento= posicion* sizeof(presupuesto);
    fseek(p3, desplazamiento, 0);
    fread(&presupuesto, sizeof(presupuesto), 1, p3);

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

        //SELECCION DE CLIENTE
        printf("\n\n\tSeleccione el numero de cliente: ");
        fflush(stdin);
        scanf("%d", &buscar);


        for(i= 1; i<= n2; i++){
            sw= 0;
            desplazamiento= i* sizeof(cliente);
            fseek(p2, desplazamiento, 0);
            fread(&cliente, sizeof(cliente), 1, p2);
            if(buscar==cliente.numero_cliente){
                posicion2= i;
                sw= 1;
                break;
            }
        }
        if(sw== 0){
            printf("\tEste cliente no existe\n");
            getch();
        }
        if(sw== 1){

            system("cls");
            printf("\n\tEl presupuesto %ld/16 sera asignado al cliente: \n\n", presupuesto.numero_presupuesto);
            printf("\t|-----------------------------------------------------------------------------|\n");
            printf("\t|                           LISTADO DE CLIENTES                               |\n");
            printf("\t|----|---------|-------------------------------------------------|------------|\n");
            printf("\t|NUM.|NIF/CIF  |NOMBRE/RAZON SOCIAL                              |TELEFONO    |\n");
            printf("\t|----|---------|-------------------------------------------------|------------|\n");

            desplazamiento= posicion2* sizeof(cliente);
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
            printf("\t|-----------------------------------------------------------------------------|\n");
        }
        printf("\n\tDesea asignar este cliente? (s/n): ");
        fflush(stdin);
        scanf("%c", &opcion2);

        if((opcion2>=97) && (opcion2<=122))
            opcion2= opcion2- 32;

        if(opcion2== 'N')
            break;
        if((opcion2!= 'S') && (opcion2!= 'N')){
            printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar. ");
            getch();
            continue;
        }
        if(opcion2== 'S'){
            presupuesto.cliente_presupuesto= cliente;

            desplazamiento= posicion* sizeof(presupuesto);
            fseek(p3, desplazamiento, 0);
            fwrite(&presupuesto, sizeof(presupuesto), 1, p3);
            break;
        }

    }

    fflush(p2);
    fclose(p2);
    fflush(p3);
    fclose(p3);
}

void modificar_partida_presupuesto(int posicion){

     //VARIABLES
    long int n3, n4, desplazamiento;
    int k, i, j, sw, opcion3;
    int buscar, posicion2;
    char opcion2;
    float suma;

    //EJECUCION
    p4= fopen(FICHERO4, "r+b");
    p3= fopen(FICHERO3, "r+b");

    fseek(p4, 0L, 0);
    fread(&registro04, sizeof(registro04), 1, p4);
    n4= registro04.nregistros;

    fseek(p3, 0L, 0);
    fread(&registro03, sizeof(registro03), 1, p3);
    n3= registro03.nregistros;

    desplazamiento= posicion* sizeof(presupuesto);
    fseek(p3, desplazamiento, 0);
    fread(&presupuesto, sizeof(presupuesto), 1, p3);

    while(1){
        system("cls");
        printf("\n\n");
        printf("\t|--------------------------------------------------------------------------------------|\n");
        printf("\t|                    LISTADO DE PARTIDAS DEL PRESUPUESTO %ld/%d                          |\n", presupuesto.numero_presupuesto, anno);
        printf("\t|---|-------|-------|-----------------------------------------------|------------------|\n");
        printf("\t|NUM|CANT.  |UD     |DESCRIPCION                                    |     PRECIO       |\n");
        printf("\t|---|-------|-------|-----------------------------------------------|------------------|\n");
        for(i= 1; i<= n4; i++){
            desplazamiento= i* sizeof(partida);
            fseek(p4, desplazamiento, 0);
            fread(&partida, sizeof(partida), 1, p4);
            if(partida.numero_partida== presupuesto.numero_presupuesto){
                printf("\t|%3d| %6.2f|%s     |%s", partida.numero_registro, partida.cantidad_partida, partida.unidad4, partida.descripcion4);
                for(j= (strlen(partida.descripcion4)+1); j< 45; j++)
                    printf(" ");
                printf("\t|%9.2f Euros/%s|\n", partida.precio_unitario4, partida.unidad4);

            }
        }
        printf("\t|---|-------|-------|-----------------------------------------------|------------------|\n");

        //SELECCION DE PARTIDA
        printf("\n\n\tSeleccione el numero de partida que desea modificar o pulse 0 para salir: ");
        fflush(stdin);
        scanf("%d", &buscar);

        if (buscar== 0)
            break;

        for(i= 1; i<= n4; i++){
            sw= 0;
            desplazamiento= i* sizeof(partida);
            fseek(p4, desplazamiento, 0);
            fread(&partida, sizeof(partida), 1, p4);
            if(buscar==partida.numero_registro){
                posicion2= i;
                sw= 1;
                break;
            }
        }
        if(sw== 0){
            printf("\tEsta partida no existe\n");
            getch();
        }
        if(sw== 1){

            system("cls");
            printf("\n\tSe va a modificar la partida: \n\n");
            printf("\t|--------------------------------------------------------------------------------------|\n");
            printf("\t|NUM|CANT.  |UD     |DESCRIPCION                                    |     PRECIO       |\n");
            printf("\t|---|-------|-------|-----------------------------------------------|------------------|\n");

            desplazamiento= posicion2* sizeof(partida);
            fseek(p4, desplazamiento, 0);
            fread(&partida, sizeof(partida), 1, p4);
            if(partida.numero_partida== presupuesto.numero_presupuesto){
                printf("\t|%3d| %6.2f|%s     |%s", partida.numero_registro, partida.cantidad_partida, precio.unidad, precio.descripcion);
                for(j= (strlen(precio.descripcion)+1); j< 46; j++)
                    printf(" ");
                printf("\t|%9.2f Euros/%s|\n", precio.precio_unitario, precio.unidad);

            }
            printf("\t|---|-------|-------|-----------------------------------------------|------------------|\n");

        }
        printf("\n\tDesea modificar esta partida? (s/n): ");
        fflush(stdin);
        scanf("%c", &opcion2);

        if((opcion2>=97) && (opcion2<=122))
            opcion2= opcion2- 32;

        if(opcion2== 'N')
            break;
        if((opcion2!= 'S') && (opcion2!= 'N')){
            printf("\tOpcion incorrecta. Pulse cualquier tecla para continuar. ");
            getch();
            continue;
        }
        if(opcion2== 'S'){
            while(1){
                system("cls");
                printf("\n\n\tQue desea hacer?\n");
                printf("\n\n");
                printf("\t|-------------------------------------|\n");
                printf("\t|    Modificar cantidad           | 1 |\n");
                printf("\t|    Eliminar partida completa    | 2 |\n");
                printf("\t|    Finalizar modificacion       | 0 |\n");
                printf("\t|-------------------------------------|\n\n");

                fflush(stdin);
                scanf("\t%d", &opcion3);
                if(opcion3== 0)
                    break;
                switch(opcion3){
                    case 1: desplazamiento= posicion2* sizeof(partida);
                            fseek(p4, desplazamiento, 0);
                            fread(&partida, sizeof(partida), 1, p4);

                            printf("\tCantidad: ");
                            fflush(stdin);
                            scanf("%f", &partida.cantidad_partida);
                            partida.importe_partida= partida.cantidad_partida* partida.precio_unitario4;

                            desplazamiento= posicion2* sizeof(partida);
                            fseek(p4, desplazamiento, 0);
                            fwrite(&partida, sizeof(partida), 1, p4);
                            break;

                    case 2: desplazamiento= posicion2* sizeof(partida);
                            fseek(p4, desplazamiento, 0);
                            fread(&partida, sizeof(partida), 1, p4);

                            partida.numero_partida= 0;

                            desplazamiento= posicion2* sizeof(partida);
                            fseek(p4, desplazamiento, 0);
                            fwrite(&partida, sizeof(partida), 1, p4);
                            break;

                    default: printf("\tSeleccion incorrecta.\n\tPulse cualquier tecla.\n");
                            getch();
                            break;
                }
                suma= 0;
                desplazamiento= posicion* sizeof(presupuesto);
                fseek(p3, desplazamiento, 0);
                fread(&presupuesto, sizeof(presupuesto), 1, p3);

                for(i= 1; i<= n4; i++){
                    desplazamiento= i* sizeof(partida);
                    fseek(p4, desplazamiento, 0);
                    fread(&partida, sizeof(partida), 1, p4);
                    if(presupuesto.numero_presupuesto==partida.numero_partida){
                        suma= suma+ partida.importe_partida;
                    }
                }
                presupuesto.suma= suma;
                presupuesto.gastos_generales= presupuesto.suma* 0.13;
                presupuesto.beneficio_industrial= presupuesto.suma* 0.06;
                presupuesto.base_imponible= presupuesto.suma+ presupuesto.gastos_generales+ presupuesto.beneficio_industrial;
                presupuesto.iva= presupuesto.base_imponible* 0.21;
                presupuesto.total_presupuesto= presupuesto.base_imponible+ presupuesto.iva;

                desplazamiento= posicion* sizeof(presupuesto);
                fseek(p3, desplazamiento, 0);
                fwrite(&presupuesto, sizeof(presupuesto), 1, p3);

            }
        }

    }

    fflush(p3);
    fclose(p3);
    fflush(p4);
    fclose(p4);
}
