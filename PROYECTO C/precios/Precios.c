#include<stdio.h>
#include<string.h>
#include<math.h>
#define FICHERO1 "PRECIOS.DAT"
#define FICHERO2 "CLIENTES.DAT"
#define FICHERO3 "PRESUPUESTOS.DAT"

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

    //PUNTEROS A FICHEROS
    FILE* p1;

    //FUNCIONES PRECIOS
    void altas_menu();
    void altas_precio(char);
    void listados_precio();
    void modificaciones_precio();

int mainPrecios(){

    //VARIABLES
    int caso, k;
    int long nregistros, nd, ne, nt, ni, nc, na, nu, ns;

    //FUNCION
    p1= fopen(FICHERO1, "rb");
    if(p1== NULL){
        system("cls");
        printf("\tEl fichero PRECIOS.DAT no existe. Pulse cualquier tecla para crearlo.\n");
        getch();
        fclose(p1);
        p1= fopen(FICHERO1, "w+b");

        fseek(p1, 0L, 0);
        nregistros= 0L;
        nd= 0L;
        ne= 0L;
        nt= 0L;
        ni= 0L;
        nc= 0L;
        na= 0L;
        nu= 0L;
        ns= 0L;
        registro01.nregistros= nregistros;
        registro01.nd= nd;
        registro01.ne= ne;
        registro01.nt= nt;
        registro01.ni= ni;
        registro01.nc= nc;
        registro01.na= na;
        registro01.nu= nu;
        registro01.ns= ns;

        //getdate(&fecha_actual);
        //getdate(&fecha_mod);
        for(k= 0; k< 30; k++)
            registro01.blanco[k]= ' ';

        fseek(p1, 0L, 0);
        fwrite(&registro01, sizeof(registro01), 1, p1);
        printf("\tFichero creado.\n\tPulse cualquier tecla para continuar.");
        getch();
    }
    fclose(p1);

   while(1){
        system("cls");
        printf("\n\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    MENU PRECIOS                |\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    CREAR NUEVO PRECIO      | 1 |\n");
        printf("\t|    LISTADO DE PRECIOS      | 2 |\n");
        printf("\t|    MODIFICAR PRECIO        | 3 |\n");
        printf("\t|    FINALIZAR PRECIOS       | 0 |\n");
        printf("\t|--------------------------------|\n\n");

        printf("\tQue desea hacer? Pulse la tecla correspondiente.\n\n\t");

        scanf("%d", &caso);
        switch(caso){
            case 1: altas_menu();
                    break;
            case 2: listados_precio();
                    break;
            case 3: modificaciones_precio();
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

void altas_menu(){

    //VARIABLES LOCALES
    char opcion;

    //FUNCION
    while(1){
        system("cls");
        printf("\tVa a crear un nuevo precio.\n");
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
            printf("\t|    CREAR NUEVO PRECIO          |\n");
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
            scanf("%c", &opcion);
            if(opcion== '0')
                break;

            switch(opcion){
                case 'D': case 'd':
                case 'E': case 'e':
                case 'T': case 't':
                case 'I': case 'i':
                case 'C': case 'c':
                case 'A': case 'a':
                case 'U': case 'u':
                case 'S': case 's': altas_precio(opcion);
                                    break;
                default: printf("\tSeleccion incorrecta\n. Pulse cualquier tecla");
                        getch();
                        break;
            }

        }
    }
}

void altas_precio(char opcion){

    //VARIABLES
    long int n, desplazamiento, n_cap, nd, ne, nt, ni, nc, na, nu, ns;
    int k, i;


    //FUNCION
    if((opcion>=97) && (opcion<=122))
        opcion= opcion- 32;

    p1= fopen(FICHERO1, "r+b");
    fseek(p1, 0L, 0);
    fread(&registro01, sizeof(registro01), 1, p1);
    n= registro01.nregistros;
    nd= registro01.nd;
    ne= registro01.ne;
    nt= registro01.nt;
    ni= registro01.ni;
    nc= registro01.nc;
    na= registro01.na;
    nu= registro01.nu;
    ns= registro01.ns;

    switch(opcion){
        case 'D':   n_cap= nd;
                    nd++;
                    break;
        case 'E':   n_cap= ne;
                    ne++;
                    break;
        case 'T':   n_cap= nt;
                    nt++;
                    break;
        case 'I':   n_cap= ni;
                    ni++;
                    break;
        case 'C':   n_cap= nc;
                    nc++;
                    break;
        case 'A':   n_cap= na;
                    na++;
                    break;
        case 'U':   n_cap= nu;
                    nu++;
                    break;
        case 'S':   n_cap= ns;
                    ns++;
                    break;
    }
    n_cap++;
    n++;

    system("cls");
    printf("\t|--------------------------------|\n");
    printf("\t|    CREAR NUEVO PRECIO          |\n");
    printf("\t|--------------------------------|\n");
    desplazamiento= n* sizeof(precio);
    fseek(p1, desplazamiento, 0);

    precio.letra_capitulo= opcion;
    precio.cod_precio= n_cap;
    printf("\tCodigo: %c%04ld\n", precio.letra_capitulo, precio.cod_precio);

    printf("\tUnidad de medida: ");
    fflush(stdin);
    scanf("%s", &precio.unidad);

    printf("\tDescripcion: ");
    fflush(stdin);
    gets(precio.descripcion);

    printf("\tPrecio de mano de obra (Euros/%s): ", precio.unidad);
    scanf("%f", &precio.mano_obra);

    printf("\tPrecio de materiales (Euros/%s): ", precio.unidad);
    scanf("%f", &precio.material);

    printf("\tPorcentaje de costes indirectos (%): ");
    scanf("%f", &precio.costes_indirectos);

    precio.precio_unitario= ((precio.mano_obra+ precio.material)* (precio.costes_indirectos/100))+ (precio.mano_obra+ precio.material);

    system("cls");
    printf("\tSe acaba de crear el siguiente precio:\n");
    printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
    printf("\t|COD    |UD     |DESCRIPCION                                    |     PRECIO       |\n");
    printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
    printf("\t|%c%04d\t|%s\t|%s", precio.letra_capitulo, precio.cod_precio, precio.unidad, precio.descripcion);
    for(i= (strlen(precio.descripcion)+1); i< 40; i++)
        printf(" ");
    printf("\t|%9.2f Euros/%s|\n", precio.precio_unitario, precio.unidad);
    printf("\t|-------|-------|-----------------------------------------------|------------------|\n");

    fwrite(&precio, sizeof(precio), 1, p1);
    getch();
    n_cap= 0;
    fseek(p1, 0L, 0);
    registro01.nregistros= n;
    registro01.nd= nd;
    registro01.ne= ne;
    registro01.nt= nt;
    registro01.ni= ni;
    registro01.nc= nc;
    registro01.na= na;
    registro01.nu= nu;
    registro01.ns= ns;
    for(k= 0; k< 30; k++)
        registro01.blanco[k]= ' ';
    fwrite(&registro01, sizeof(registro01), 1, p1);
    fflush(p1);
    fclose(p1);
}

void listados_precio(){

    //VARIABLES LOCALES
    char opcion;
    long int num, n, desplazamiento, n_cap, nd, ne, nt, ni, nc, na, nu, ns;
    int i, j;

    //FUNCION
    p1= fopen(FICHERO1, "r+b");
    fseek(p1, 0L, 0);
    fread(&registro01, sizeof(registro01), 1, p1);
    n= registro01.nregistros;
    nd= registro01.nd;
    ne= registro01.ne;
    nt= registro01.nt;
    ni= registro01.ni;
    nc= registro01.nc;
    na= registro01.na;
    nu= registro01.nu;
    ns= registro01.ns;

    while(1){
        system("cls");
        printf("\n\n");
            printf("\t|--------------------------------|\n");
            printf("\t|    LISTADO DE PRECIOS          |\n");
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
        printf("\tQue desea hacer? Pulse la tecla correspondiente.\n\n");

        fflush(stdin);
        scanf("%c", &opcion);
        if(opcion== '0')
            break;
        else{
            if((opcion>=97) && (opcion<=122))
                opcion= opcion- 32;

            system("cls");
            printf("\n\n");
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
            printf("\t|COD    |UD     |DESCRIPCION                                    |     PRECIO       |\n");
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
            for(i= 1; i<= n; i++){
                desplazamiento= i* sizeof(precio);
                fseek(p1, desplazamiento, 0);
                fread(&precio, sizeof(precio), 1, p1);
                if(opcion== precio.letra_capitulo){
                    printf("\t|%c%04d\t|%s\t|%s", precio.letra_capitulo, precio.cod_precio, precio.unidad, precio.descripcion);
                    for(j= (strlen(precio.descripcion)+1); j< 40; j++)
                        printf(" ");
                    printf("\t|%9.2f Euros/%s|\n", precio.precio_unitario, precio.unidad);

                }
            }
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
            getch();
        }
    }
    fflush(p1);
    fclose(p1);
}

void modificaciones_precio(){

    //VARIABLES LOCALES
    char opcion, opcion2;
    char unidad, descripcion;
    float mano_obra, material, costes_indirectos;
    long int num, n, desplazamiento, n_cap, nd, ne, nt, ni, nc, na, nu, ns;
    int i,j , buscar, sw, opcion3, posicion;

    //LISTADO
    p1= fopen(FICHERO1, "r+b");
    fseek(p1, 0L, 0);
    fread(&registro01, sizeof(registro01), 1, p1);
    n= registro01.nregistros;
    nd= registro01.nd;
    ne= registro01.ne;
    nt= registro01.nt;
    ni= registro01.ni;
    nc= registro01.nc;
    na= registro01.na;
    nu= registro01.nu;
    ns= registro01.ns;

    while(1){
        system("cls");
        printf("\n\n");
        printf("\t|--------------------------------|\n");
        printf("\t|    MODIFICAR PRECIO            |\n");
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
        scanf("%c", &opcion);
        if(opcion== '0')
            break;
        else{
            if((opcion>=97) && (opcion<=122))
                opcion= opcion- 32;

            system("cls");
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
            printf("\t|COD    |UD     |DESCRIPCION                                    |     PRECIO       |\n");
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
            for(i= 1; i<= n; i++){
                desplazamiento= i* sizeof(precio);
                fseek(p1, desplazamiento, 0);
                fread(&precio, sizeof(precio), 1, p1);
                if(opcion== precio.letra_capitulo){
                    printf("\t|%c%04d\t|%s\t|%s", precio.letra_capitulo, precio.cod_precio, precio.unidad, precio.descripcion);
                    for(j= (strlen(precio.descripcion)+1); j< 40; j++)
                        printf(" ");
                    printf("\t|%9.2f Euros/%s|\n", precio.precio_unitario, precio.unidad);

                }
            }
            printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
        }

        //MODIFICACION
        printf("\n\n\tSeleccione el numero de precio que desea modificar\n");
        printf("\tNumero (%c00..._): ", opcion);
        fflush(stdin);
        scanf("%d", &buscar);

        sw= 0;
        for(i= 1; i<= n; i++){
            desplazamiento= i* sizeof(precio);
            fseek(p1, desplazamiento, 0);
            fread(&precio, sizeof(precio), 1, p1);
            if(opcion== precio.letra_capitulo){
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
            printf("\tSe va a modificar el precio: %c%04d\n\tDesea continuar? (s/n)\n\t", precio.letra_capitulo, precio.cod_precio);
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
                printf("\t|COD    |UD     |DESCRIPCION                                    |MANO OBRA| MATERIAL| C.I |PRECIO UNITARIO|\n");
                printf("\t|-------|-------|-----------------------------------------------|---------|---------|-----|---------------|\n");
                printf("\t|%c%04d\t|%s\t|%s", precio.letra_capitulo, precio.cod_precio, precio.unidad, precio.descripcion);
                for(j= (strlen(precio.descripcion)+1); j< 40; j++)
                    printf(" ");
                printf("\t|%9.2f|%9.2f| %.2f|      %9.2f|\n", precio.mano_obra, precio.material, precio.costes_indirectos, precio.precio_unitario);
                printf("\t|-------|-------|-----------------------------------------------|---------|---------|-----|---------------|\n");
                printf("\n\n\tElija el campo que desea modificar:\n");
                while(1){
                    printf("\n\n");
                    printf("\t|--------------------------------|\n");
                    printf("\t|    Unidad de medida        | 1 |\n");
                    printf("\t|    Descripcion             | 2 |\n");
                    printf("\t|    Precio mano de obra     | 3 |\n");
                    printf("\t|    Precio materiales       | 4 |\n");
                    printf("\t|    Costes indirectos       | 5 |\n");
                    printf("\t|    Finalizar modificacion  | 0 |\n");
                    printf("\t|--------------------------------|\n\n");

                    fflush(stdin);
                    scanf("%d", &opcion3);
                    if(opcion3== 0)
                        break;
                    switch(opcion3){
                        case 1: printf("\tUnidad de medida: ");
                                fflush(stdin);
                                scanf("%s", &precio.unidad);
                                break;

                        case 2: printf("\tDescripcion: ");
                                fflush(stdin);
                                gets(precio.descripcion);
                                break;

                        case 3: printf("\tPrecio mano de obra: ");
                                fflush(stdin);
                                scanf("%f", &precio.mano_obra);
                                break;

                        case 4: printf("\tPrecio material: ");
                                fflush(stdin);
                                scanf("%f", &precio.material);
                                break;

                        case 5: printf("\tPorcentaje costes indirectos: ");
                                fflush(stdin);
                                scanf("%f", &precio.costes_indirectos);
                                break;
                        default: printf("\tSeleccion incorrecta.\n\tPulse cualquier tecla.\n");
                                getch();
                                break;
                    }
                }
                precio.precio_unitario= ((precio.mano_obra+ precio.material)* (precio.costes_indirectos/100))+ (precio.mano_obra+ precio.material);

                system("cls");
                printf("\tEl nuevo precio es: (Pulse cualquier tecla para continuar)\n");
                printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
                printf("\t|COD    |UD     |DESCRIPCION                                    |     PRECIO       |\n");
                printf("\t|-------|-------|-----------------------------------------------|------------------|\n");
                printf("\t|%c%04d\t|%s\t|%s", precio.letra_capitulo, precio.cod_precio, precio.unidad, precio.descripcion);
                for(i= (strlen(precio.descripcion)+1); i< 40; i++)
                    printf(" ");
                printf("\t|%9.2f Euros/%s|\n", precio.precio_unitario, precio.unidad);
                printf("\t|-------|-------|-----------------------------------------------|------------------|\n");

                desplazamiento= posicion* sizeof(precio);
                fseek(p1, desplazamiento, 0);
                fwrite(&precio, sizeof(precio), 1, p1);
                getch();
            }
        }
    }
    fflush(p1);
    fclose(p1);
}



