#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

///CONSTANTES
int const fila=5;
int const columna=7;

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
    float hora;

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
int horario();
void mostrarTurno(int documento);






///INICIO DEL MAIN
int main()
{
    int matriz [fila][columna];
    paciente datos;

    int menu=menuPrincipal();
    opciones(menu);



    return 0;
}
///FIN DEL MAIN



///------------------------------------FUNCIONES---------------------------------------------
int menuPrincipal()
{

    int opcion=0;
    int flag=0;

    while(flag==0)
    {
        printf("------ Menu Principal ------\n");
        printf("1. Ver turnos disponibles\n");
        printf("2. Solicitar turno\n");
        printf("3. Salir\n");
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
    switch(menu)
    {
    case 1:
        printf("Usted ya esta ingresado en nuestro sistema (S/N):\n ");
        fflush(stdin);
        scanf("%c", &ingresado);


                    int documento;

    printf("Ingrese el número de documento: ");
    scanf("%d", &documento);

    mostrarTurno(documento);

        if (ingresado == 'n')
        {
            noEstaIngresado(datos);
            printf("inicie sesion con su nueva cuenta\n");
            validacion = siEstaIngresado(datos);
            if(validacion==1){



            }
            else{
                printf("vuelva a ingresar al sistema");
            }
        }
        else if (ingresado == 's')
        {

          validacion = siEstaIngresado(datos);
           if(validacion==1){


            }
            else{
                printf("vuelva a ingresar al sistema");
            }

        }
        else
        {
            printf("Opcion no valida. Por favor, elija una opción correcta.\n");

        }


        break;

    case 2:
        printf("Usted ya esta ingresado en nuestro sistema (S/N): ");
        fflush(stdin);
        scanf("%c", &ingresado);

        if (ingresado == 'n')
        {
              noEstaIngresado(datos);
              printf("inicie sesion con su nueva cuenta \n");

             validacion = siEstaIngresado(datos);
              if(validacion==1){

                areas ();

            }
            else{
                printf("vuelva a ingresar al sistema");
            }



        }
        else if (ingresado == 's')
        {

           validacion = siEstaIngresado(datos);
            if(validacion==1){

                areas ();

            }
            else{
                printf("vuelva a ingresar al sistema");
            }


        }
        else
        {
            printf("Opcion no valida. Por favor, elija una opción correcta.\n");

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
            printf("\nIngrese su DNI: ");
            fflush(stdin);
            scanf("%d", &datos.dni);
            printf("\nIngrese su nombre: ");
            fflush(stdin);
            gets(datos.nombre);
            printf("\nIngrese su genero (M/F): ");
            fflush(stdin);
            scanf("%c",&datos.genero);
            printf("\nIngrese su edad: ");
            fflush(stdin);
            scanf("%d", &datos.edad);
            fwrite(&datos,sizeof(paciente),1,archivo);
            printf("\n¿Desea cargar algun otro paciente? (S/N): ");
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
            printf("Ingrese su documento para ingresar al sistema\n");
            fflush(stdin);
            scanf("%i", &docu);

            // Comparar el documento ingresado con los documentos almacenados en el arreglo
            for (int j = 0; j < numPacientes; j++)
            {
                if (pacientes[j].dni == docu)
                {
                    printf("------BIENVENIDO------\n");
                    flag = 1;





                }
            }

            if (!flag)
            {
                printf("El dato que ingreso es incorrecto, vuelva a intentarlo.\n");
            }
        }

        if (i >= 3 && !flag)
        {
            printf("Ha excedido el número máximo de intentos permitidos.\n");
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

    printf("1. Pediatria\t\t 2. Traumatologia\t\t 3. Cardiologia\n");
    printf("4. Dermatologia \t\t 5. Oftalmologia\t\t 6. Urologia\n");
    printf("7. Oncologia\t\t 8. Alergia e Inmunologia\t 9. Cirugia\n");

    printf("\nIngrese el numero de la especialidad que desea sacar turno: ");
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:
        printf("Estos son los días disponibles\n");
        cargarTurno();
        break;
    case 2:
        printf("Estos son los dias disponibles.\n\n");
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
    turnos turno;
    char eleccion='s';
    FILE *archivo2;
    archivo2=fopen("turno.bin","ab");
    if(archivo2!=NULL){
        while(eleccion=='s'){
          turno.mes = calendario();
//            printf("ingrese el mes en el que desea atenderse");
//            fflush(stdin);
//            scanf("%i",&turno.mes);
            printf("ingrese el dia en el que quiere atenderse \n");
            fflush(stdin);
            scanf("%i",&turno.dia);
            horario();
//            printf("elija su horario");
//            fflush(stdin);
//            scanf("%f",&turno.hora);
            printf("ingrese su documento para confirmar el turno, no nos hacemos responsables si lo ingresa mal \n");
            fflush(stdin);
            scanf("%i",&turno.documento);
            fwrite(&turno,sizeof(turnos),1,archivo2);
            printf("¿desea seguir cargando mas turnos?S/N");
            fflush(stdin);
            scanf("%c",&eleccion);
            }
            fclose(archivo2);
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


int horario(){

    int i=8;
    int j=0;
    int hora;
    int minuto;

    Pila horas;
    Pila minutos;

    inicpila(&horas);
    inicpila(&minutos);

    while(i<21)
    {
        apilar(&horas, i);
        i++;
    }
    while(j<60)
    {
        apilar(&minutos, j);
        j=j+15;
    }
    printf("\nHoras: ");
    mostrar(&horas);


    printf("Elija la hora: ");
    fflush(stdin);
    scanf("%i", &hora);
    if  (hora<8 || hora>20)
    {
        printf("El horario no es valido");
    }
    else
    {
        printf("\nMinutos: ");
        mostrar(&minutos);

        printf("Elija el minuto: ");
        fflush(stdin);
        scanf("%i", &minuto);
        if (minuto!=0 && minuto!=15 && minuto!=30 && minuto!=45)
        {
            printf("Ese minuto no es valido \n");
        }
        else
        {
            printf("El horario elegido es: %i:%i \n\n", hora, minuto);
        }
    }
}


void mostrarTurno(int documento)
{
    turnos turno;

    FILE *archivo;
    archivo = fopen("turno.bin", "rb");
    if (archivo != NULL)
    {
        // Leer los turnos del archivo y buscar el turno correspondiente al documento
        while (fread(&turno, sizeof(turnos), 1, archivo) == 1)
        {
            if (turno.documento == documento)
            {
                printf("Turno encontrado:\n");
                printf("Mes: %d\n", turno.mes);
                printf("Dia: %d\n", turno.dia);
                printf("Hora: %.2f\n", turno.hora);
                fclose(archivo);
                return;
            }
        }

        fclose(archivo);  // Cerrar el archivo después de buscar el turno
    }
    else
    {
        printf("No se pudo abrir el archivo de turnos.\n");
    }

    // Si se llega a este punto, significa que no se encontró el turno
    printf("No se encontró un turno para el documento ingresado.\n");
}








