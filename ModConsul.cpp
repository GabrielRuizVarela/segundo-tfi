
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"
#define MAX_TURNOS 100 // Un límite arbitrario para la demostración

Turno turnosEncontrados[MAX_TURNOS]; // Arreglo global de turnos encontrados
int cantidadTurnos = 0;              // Contador global de turnos encontrados

Usuario usuarioActual; // Variable global para almacenar el usuario que inició sesión

int usuarioLogueado = 0; // 0: no logueado, 1: logueado

struct Fecha
{
    int anio;
};

struct registro
{
    char ApeNomP[60];
    char Domicilio[60];
    int DniPaciente[8];
    char Localidad[60];
    Fecha fec;
    int edad;
    float peso;
    float talla;
    int Telefono;
};
Usuario res[60];
void Iniciarsesion()
{
    char usuario[MAX_NOMBRE_LENGTH], contrasenia[MAX_CONTRASENIA_LENGTH];
    printf("Ingrese nombre de usuario: ");
    scanf("%s", usuario);

    printf("Ingrese contrase�a: ");
    scanf("%s", contrasenia);

    FILE *file = fopen("profesionales.dat", "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    int encontrado = 0;
    Usuario tempUser; // Variable temporal para leer usuarios del archivo
    while (fread(&tempUser, sizeof(Usuario), 1, file))
    {
        if (strcmp(usuario, tempUser.usuario) == 0 && strcmp(contrasenia, tempUser.contrasenia) == 0)
        {
            usuarioActual = tempUser; // Almacenar el usuario que inició sesión en la variable global
            encontrado = 1;
            usuarioLogueado = 1; // Marcar como logueado  
            break;
        }
    }
    fclose(file);

    if (encontrado)
    {
        printf("Bienvenido a nuestro sistema, %s.\n", usuarioActual.usuario);
    }
    else
    {
        printf("Usuario y contraseña incorrectos\n");
        exit(1);
    }
}

void registrarUsuario()
{
    FILE *file = fopen("consultorios.dat", "ab");
    if (file == NULL)
    {
        printf("Error al abrir el archivo");
        exit(1);
    }
    fwrite(&res[0], sizeof(struct registro), 1, file);
    fclose(file);
}
void VisualizarLista()
{
    FILE *file = fopen("consultorios.dat", "r+b");
    registro res;
    int eleccion;
    printf("Desea visualizar datos (1-si || 2-no): ");
    scanf("%d", &eleccion);

    while (eleccion == 1)
    {
        printf("Nombre : ");
        scanf("%s", &res.ApeNomP);
        printf("Edad:");
        scanf("%d", &res.edad);
        printf("Domicilio: ");
        fflush(stdin);
        gets(res.Domicilio);
        fwrite(&res, sizeof(struct registro), 1, file);

        while (!feof(file))
        {
            printf("Apellido y nombre: %s\n", res.ApeNomP);
            printf("Edad: %d\n", res.edad);
            printf("Domicilio: %s\n", res.Domicilio);
            break;
        }
        printf("Desea seguir visualizar datos (1-si || 2-no): ");
        scanf("%d", &eleccion);
    }
    fclose(file);
}
void RegistrarHistoria()
{
    FILE *file = fopen("consultorios.dat", "r+b");
    registro res;
    int documento, opc;

    printf("Desea registrar historia del paciente (1-si || 2-no): ");
    scanf("%d", &opc);
    printf("Ingrese el dni del paciente a registrar su historia:");
    scanf("%d", &documento);

    printf("El paciente de documento %d fue registrado en el hospital avellaneda por dolencias en la pierna izquierda\n", documento);
}
void limpiar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void turnos_del_dia()
{
    FILE *file = fopen("turnos.dat", "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    char fecha[MAX_NOMBRE_LENGTH];
    printf("Ingrese la fecha del turno a buscar (DDMMYYYY): ");
    scanf("%s", fecha);
    limpiar_buffer(); // Limpia el buffer después de usar scanf

    cantidadTurnos = 0; // Reiniciar el contador de turnos
    Turno turno;
    while (fread(&turno, sizeof(Turno), 1, file) && cantidadTurnos < MAX_TURNOS)
    {
        if (strcmp(fecha, turno.fecha) == 0 && strcmp(usuarioActual.usuario, turno.usuario) == 0)
        {
            turnosEncontrados[cantidadTurnos++] = turno; // Almacenar el turno encontrado
        }
    }

    fclose(file);

    // Opcional: imprimir los turnos almacenados en la variable global
    if (cantidadTurnos == 0)
    {
        printf("No se encontraron turnos para %s en la fecha %s.\n", usuarioActual.usuario, fecha);
    }
    else
    {
        printf("Turnos encontrados para %s en la fecha %s:\n", usuarioActual.usuario, fecha);
        for (int i = 0; i < cantidadTurnos; i++)
        {
            printf("Turno %d: %s\n", i + 1, turnosEncontrados[i].fecha); // Ejemplo de cómo acceder
        }
    }
}

int menu()
{
    int opcion;
    printf("=========================\n");
    printf("Modulo Consultorio\n");
    printf("=========================\n");
    if (!usuarioLogueado)
    {
        // Usuario no ha iniciado sesión
        printf("1- Iniciar sesion\n");
    }
    else
    {
        // Usuario ha iniciado sesión
        printf("2- Visualizar lista de espera de turnos (informe)\n");
        printf("3- Registrar historia clinica\n");
    }
    printf("0- Cerrar la aplicacion.\n");
    printf("\nIngrese una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

int main()
{
    int seleccion;
    do
    {
        seleccion = menu();

        if (!usuarioLogueado && seleccion != 1 && seleccion != 0)
        {
            printf("Por favor, inicie sesión primero.\n");
            continue; // Regresa al inicio del ciclo
        }

        switch (seleccion)
        {
        case 1:
            Iniciarsesion();
            break;
        case 2:
            if (usuarioLogueado)
                VisualizarLista();
            break;
        case 3:
            if (usuarioLogueado)
                RegistrarHistoria();
            break;
        case 0:
            printf("Gracias por usar nuestro sistema...\n");
            break;
        default:
            printf("Opción inválida\n");
            break;
        }
    } while (seleccion != 0);
    return 0;
}
