#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#include <windows.h>


///CONSTANTES
int const fila=5;
int const columna=7;


///COLORES PARA PERSONALIZAR
#define ROJO 12
#define VERDE 10
#define AMARILLO 14
#define MAGENTA 13
#define CYAN 11
#define BLANCO 15

///ESCTRUCTURAS
typedef struct
{
    int dni;
    char nombre[50];
    char genero;
    int edad;
} paciente;


typedef struct
{
    int documento;
    int dia;
    int mes;
    int hora;
    int minuto;


} turnos;

/// PROTOTIPADO DE FUNCIONES
int menuPrincipal();
void areas ();
void noEstaIngresado(paciente datos);
int siEstaIngresado(paciente datos);
void cargarTurno();
void opciones(int menu);
void cargarCalendario(int calendario[][columna], int fila, int columna, int dias);
void mostrarCalendario(int calendario[][columna], int dias);
int hora();
int minutos();
void inicio();
void mostrarTurno(int documento);





///INICIO DEL MAIN
int main()
{

inicio();

    return 0;
}
///FIN DEL MAIN



///------------------------------------FUNCIONES---------------------------------------------
void inicio(){
    system("cls");
 int matriz [fila][columna];
    paciente datos;

    int menu=menuPrincipal();
    opciones(menu);


}


int menuPrincipal()
{

    int opcion=0;
    int flag=0;

    while(flag==0)
    {

        printf("\t\t\t\t\t|------ Menu Principal ------|\n", color(VERDE));
        printf("\t\t\t\t\t|1. Ver turnos disponibles   |\n");
        printf("\t\t\t\t\t|2. Solicitar turno\t     |\n");
        printf("\t\t\t\t\t|3. Salir\t\t     |\n");
        printf("\t\t\t\t\t------------------------------\n\n");
        fflush(stdin);
        scanf("%i",&opcion);
        if(opcion==1 || opcion==2 || opcion==3 )
        {
            flag=1;
        }


        else
        {
            printf("Ese numero no se encuentra disponible, ingrese uno de los disponibles en el menu");
        }

    }

    return opcion;
}

void opciones(int menu){
     paciente datos;
     int validacion=0;
     char ingresado;
     int documento;
    switch(menu)

    {
    case 1:
        system("cls");

        printf("Usted ya esta ingresado en nuestro sistema (S/N):\n ", color(CYAN));
        fflush(stdin);
        scanf("%c", &ingresado);
       //system("pause");

        if (ingresado == 'n')
        {
            noEstaIngresado(datos);
            printf("inicie sesion con su nueva cuenta\n");
            validacion = siEstaIngresado(datos);
            if(validacion==1){


    printf("Ingrese el número de documento: ", color(CYAN));
    scanf("%d", &documento);
    mostrarTurno(documento);




            }
            else{
                printf("vuelva a ingresar al sistema", color(ROJO));
            }
        }
        else if (ingresado == 's')
        {

          validacion = siEstaIngresado(datos);
           if(validacion==1){
                printf("Ingrese el número de documento: ", color(CYAN));
    scanf("%d", &documento);
    mostrarTurno(documento);




            }
            else{
                printf("vuelva a ingresar al sistema", color(ROJO));
            }

        }
        else
        {
            printf("Opcion no valida. Por favor, elija una opción correcta.\n", color(ROJO));

        }


        break;

    case 2:
        system("cls");
        printf("Usted ya esta ingresado en nuestro sistema (S/N): ", color(CYAN));
        fflush(stdin);
        scanf("%c", &ingresado);

        if (ingresado == 'n')
        {
              noEstaIngresado(datos);
              printf("inicie sesion con su nueva cuenta \n", color(CYAN));

             validacion = siEstaIngresado(datos);
              if(validacion==1){

                areas ();

            }
            else{
                printf("vuelva a ingresar al sistema", color(ROJO));
            }



        }
        else if (ingresado == 's')
        {

           validacion = siEstaIngresado(datos);
            if(validacion==1){

                areas ();

            }
            else{
                printf("vuelva a ingresar al sistema", color(ROJO));
            }


        }
        else
        {
            printf("Opcion no valida. Por favor, elija una opción correcta.\n", color(ROJO));

        }


        break;


    }

}




void noEstaIngresado(paciente datos)
{
    FILE *archivo;
    archivo=fopen("pacientes.bin","ab");
    int i=0;
    char eleccion = 's';
    if(archivo!=NULL)
    {
        while (eleccion == 's')
        {
            printf("\nIngrese su DNI: ", color(CYAN));
            fflush(stdin);
            scanf("%d", &datos.dni);
            printf("\nIngrese su nombre: ", color(CYAN));
            fflush(stdin);
            gets(datos.nombre);
            printf("\nIngrese su genero (M/F): ", color(CYAN));
            fflush(stdin);
            scanf("%c",&datos.genero);
            printf("\nIngrese su edad: ", color(CYAN));
            fflush(stdin);
            scanf("%d", &datos.edad);
            fwrite(&datos,sizeof(paciente),1,archivo);
            printf("\n¿Desea cargar algun otro paciente? (S/N): ", color(AMARILLO));
            fflush(stdin);
            scanf(" %c", &eleccion);
            i++;
        }
        fclose(archivo);


    }

}

int siEstaIngresado(paciente datos)
{
    int i = 0;
    int flag = 0;
    int docu;

    FILE *archivo;
    archivo = fopen("pacientes.bin", "rb");
    if (archivo != NULL)
    {
        paciente pacientes[100];  // Arreglo para almacenar los pacientes
        int numPacientes = 0;    // Contador de pacientes

        // Leer todos los pacientes del archivo y almacenarlos en el arreglo
        while (fread(&datos, sizeof(paciente), 1, archivo) == 1)
        {
            pacientes[numPacientes] = datos;
            numPacientes++;
        }

        fclose(archivo);  // Cerrar el archivo después de leer los pacientes

        // Intentar iniciar sesión hasta 3 intentos o hasta que el documento coincida
        for (i = 0; i < 3 && !flag; i++)
        {
            printf("Ingrese su documento para ingresar al sistema\n", color(CYAN));
            fflush(stdin);
            scanf("%i", &docu);

            // Comparar el documento ingresado con los documentos almacenados en el arreglo
            for (int j = 0; j < numPacientes; j++)
            {
                if (pacientes[j].dni == docu)
                {
                    printf("------BIENVENIDO------\n", color(VERDE));
                    flag = 1;

                }
            }

            if (!flag)
            {
                printf("El dato que ingreso es incorrecto, vuelva a intentarlo.\n", color(ROJO));
            }
        }

        if (i >= 3 && !flag)
        {
            printf("Ha excedido el número máximo de intentos permitidos.\n", color(ROJO));
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de pacientes.\n");
    }

    return flag;
}
void areas ()
{
    int opc;

    printf("1. Pediatria\t\t 2. Traumatologia\t\t 3. Cardiologia\n", color(VERDE));
    printf("4. Dermatologia \t\t 5. Oftalmologia\t\t 6. Urologia\n");
    printf("7. Oncologia\t\t 8. Alergia e Inmunologia\t 9. Cirugia\n");

    printf("Ingrese el numero de la especialidad que desea sacar turno: ");
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:
        printf("Estos son los días disponibles\n");
        cargarTurno();
        break;
    case 2:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    case 3:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    case 4:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    case 5:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    case 6:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    case 7:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    case 8:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    case 9:
        printf("Estos son los dias disponibles.\n");
        cargarTurno();
        break;
    default:
        printf("Opcion no válida. Por favor, elija una opcion correcta.\n");
        cargarTurno();
        break;
    }

}

void cargarTurno(){
    char eleccion1;

    turnos turno;
    char eleccion='s';
    int minuto1=0;
    int hora1=0;
    FILE *archivo2;
    archivo2=fopen("turno.bin","ab");
    if(archivo2!=NULL){
        while(eleccion=='s'){
          turno.mes = calendario();
            printf("ingrese el dia en el que quiere atenderse: \n");
            fflush(stdin);
            scanf("%i",&turno.dia);
            hora1=hora();
            turno.hora=hora1;
             minuto1=minutos();
            turno.minuto=minuto1;
            printf("El horario elegido es: %i:%i \n\n", hora1, minuto1);
            printf("vuelva a ingresar su documento para confimar su turno:\n");
            fflush(stdin);
            scanf("%i",&turno.documento);
            fwrite(&turno,sizeof(turnos),1,archivo2);
            printf("¿desea seguir cargando mas turno?S/N\n");
            fflush(stdin);
            scanf("%c",&eleccion);
            }
            fclose(archivo2);
}
            printf("Desea volver al menu principal?");
            fflush(stdin);
            scanf("%c", &eleccion1);
            if (eleccion1=='s'){
                inicio();
            }
}


int calendario(){
int opc;
int calendario [fila][columna];
int dias;

printf("1. Enero            2. Febrero       3. Marzo           4. Abril\n5. Mayo             6. Junio         7. Julio           8. Agosto\n9. Septiembre      10. Octubre      11. Noviembre      12. Diciembre\n");

printf("Ingrese el numero de mes en el que desee sacar el turno: \n");
fflush(stdin);
scanf("%i", &opc);

switch (opc){
case 1:
    dias=31;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 2:
    dias=28;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 3:
    dias=31;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 4:
    dias=30;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 5:
    dias=31;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 6:
    dias=30;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 7:
    dias=31;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 8:
    dias=31;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 9:
    dias=30;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 10:
    dias=31;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 11:
    dias=30;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
case 12:
    dias=31;
    cargarCalendario(calendario, fila, columna, dias);
    mostrarCalendario(calendario,dias);
    break;
default:
    printf("Este mes no existe");
    break;
}
return opc;
}
void cargarCalendario(int calendario[][columna], int fila, int columna, int dias)
 {
    int i, j;
    int valor = 1;

    for (i = 0; i < fila; i++)
     {
        for (j = 0; j < columna; j++)
        {
            if (valor <= dias)
            {
                calendario[i][j] = valor;
                valor++;
            }
            else
            {
                calendario[i][j] = 0;
            }
        }
    }
}



void mostrarCalendario(int calendario[][columna], int dias)
{
    int i, j;

    for (i = 0; i < fila; i++)
     {
        for (j = 0; j < columna; j++) {
            if (calendario[i][j] != 0) {
            printf("| %3d |", calendario[i][j]);
            }
        }
        printf("\n");
    }
}


int hora(){

    int i=8;

    int hora;
    int flag=0;


    Pila horas;


    inicpila(&horas);


    while(i<21)
    {
        apilar(&horas, i);
        i++;
    }


    while(flag==0){
             printf("\nHoras: \n");
    mostrar(&horas);


    printf("Elija la hora: \n");
    fflush(stdin);
    scanf("%i", &hora);
         if  (hora<8 || hora>20)
    {
        printf("El horario no es valido");
    }
    else{
        flag=1;
    }
    }





     return hora;

}
int minutos(){
int j=0;
int minuto;
int flag=0;
 Pila minutos;
 inicpila(&minutos);
 while(j<60)
    {
        apilar(&minutos, j);
        j=j+15;
    }



        while(flag==0){
                printf("\nMinutos: ");
        mostrar(&minutos);
                printf("Elija el minuto: \n");
        fflush(stdin);
        scanf("%i", &minuto);
           if (minuto!=0 && minuto!=15 && minuto!=30 && minuto!=45)
        {
            printf("Ese minuto no es valido \n");
        }
         else{
            flag=1;


         }

        }

return minuto;

}


void mostrarTurno(int documento)
{
    turnos turno;
    char eleccion;

    FILE *archivo;
    archivo = fopen("turno.bin", "rb");
    if (archivo != NULL)
    {

        system("cls");
        while(!feof(archivo))
            { // Leer los turnos del archivo y buscar el turno correspondiente al documento
            while ( fread(&turno, sizeof(turnos), 1, archivo) == 1)
        {
            if (turno.documento == documento)
            {
               printf("------------------------------\n");
               printf("Turno encontrado:\n");
                printf("Mes: %d\n", turno.mes);
                printf("Dia: %d\n", turno.dia);
                printf("Hora: %i:%i\n", turno.hora,turno.minuto);

                printf("------------------------------\n");
                system("pause");


            }
        }

        }



        fclose(archivo);  // Cerrar el archivo después de buscar el turno
    }
    else
    {
        printf("No se pudo abrir el archivo de turnos.\n");
    }

    // Si se llega a este punto, significa que no se encontró el turno
    printf("No se encontro otro turno para el documento ingresado.\n");
    printf("Desea volver al menu? S/N");
    fflush(stdin);
    scanf("%c",&eleccion);
    if (eleccion=='s'){
        inicio();
    }

}
void color(int color)
{
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, color);
}


