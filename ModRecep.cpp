#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h" 

#define MAX_USUARIO 100
#define MAX_PACIENTE 100
#define MAX_DATOS 100
#define MAX_NOMBRE_USUARIO_LENGTH 50
#define MAX_CONTRASENIA_LENGTH 50
#define MAX_NOMBRE_LENGTH 50


Usuario us[MAX_USUARIO];
int contador_usuario = 0;

Paciente pa[MAX_PACIENTE];
int contador_paciente = 0;

Datos da[MAX_DATOS];
int contador_datos = 0;

// Funci�n para verificar el usuario y la contrasena
int verificar_usuario(const char *username, const char *password)
{
    for (int i = 0; i < contador_usuario; i++)
    {
        if (strcmp(us[i].usuario, username) == 0 && strcmp(us[i].contrasenia, password) == 0)
        {
            return us[i].rol; // Retorna el rol del usuario
        }
    }
    return 0; // Retorna 0 si no se encuentra el usuario o la contrasena no coincide
}

// Funci�n para iniciar sesion
void iniciar_sesion()
{
    char usuario[MAX_NOMBRE_USUARIO_LENGTH];
    char contrasenia[MAX_CONTRASENIA_LENGTH];

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", usuario);

    printf("Ingrese su contrasena: ");
    scanf("%s", contrasenia);

    // Condici�n espec�fica para el usuario "recepcionista"
    // usuario = recepcionista y clave  = tfi2
    if (strcmp(usuario, "recepcionista") == 0 && strcmp(contrasenia, "tfi2") == 0)
    {
        printf("Inicio de sesion exitoso. Bienvenido, Recepcionista!\n");
        // Puedes realizar acciones espec�ficas para el recepcionista aqu�
    }
    else
    {
        int rol = verificar_usuario(usuario, contrasenia);

        if (rol > 0)
        {
            printf("Inicio de sesion exitoso. Bienvenido!\n");

            // Ahora 'role' contiene el tipo de usuario (1: Medico, 2: Recepcionista)
            // Puedes realizar acciones espec�ficas seg�n el tipo de usuario aqu�
        }
        else
        {
            printf("Inicio de sesion fallido. Usuario o contrasena incorrectos.\n");
            exit(1); // Salir del programa si el inicio de sesion falla
        }
    }
}

// Funci�n para guardar datos en un archivo.
void guardar_datos()
{
    FILE *file = fopen("data.txt", "w");
    if (file == NULL)
    {
        printf("Error al abrir el archivo para guardar datos.\n");
        exit(1);
    }
    fprintf(file, "%d\n", contador_usuario);
    for (int i = 0; i < contador_usuario; i++)
    {
        fprintf(file, "%s %s %d\n", us[i].usuario, us[i].contrasenia, us[i].rol);
    }

    fprintf(file, "%d\n", contador_paciente);
    for (int i = 0; i < contador_paciente; i++)
    {
        fprintf(file, "%s %s %s %s %s %s %s\n", pa[i].name, pa[i].apellido, pa[i].dni, pa[i].domicilio, pa[i].peso, pa[i].talla, pa[i].fecha);
    }

    fprintf(file, "%d\n", contador_datos);
    for (int i = 0; i < contador_datos; i++)
    {
        fprintf(file, "%s %s %s\n", da[i].profesional, da[i].paciente, da[i].date);
    }
    fclose(file);
}

// Funci�n para agregar un nuevo paciente.
void agregar_paciente()
{
    if (contador_paciente >= MAX_PACIENTE)
    {
        printf("No se pueden agregar mas pacientes. Limite alcanzado.\n");
    }
    printf("\nIngrese el nombre del paciente: ");
    getchar(); // Consumir el salto de l�nea pendiente del buffer
    fgets(pa[contador_paciente].name, MAX_NOMBRE_LENGTH, stdin);
    pa[contador_paciente].name[strcspn(pa[contador_paciente].name, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    printf("Ingrese el apellido del paciente: ");
    fgets(pa[contador_paciente].apellido, MAX_NOMBRE_LENGTH, stdin);
    pa[contador_paciente].apellido[strcspn(pa[contador_paciente].apellido, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    printf("Ingrese el DNI del paciente: ");
    fgets(pa[contador_paciente].dni, MAX_NOMBRE_LENGTH, stdin);
    pa[contador_paciente].dni[strcspn(pa[contador_paciente].dni, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    printf("Ingrese el domicilio del paciente: ");
    fgets(pa[contador_paciente].domicilio, MAX_NOMBRE_LENGTH, stdin);
    pa[contador_paciente].domicilio[strcspn(pa[contador_paciente].domicilio, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    printf("Ingrese el peso del paciente: ");
    fgets(pa[contador_paciente].peso, MAX_NOMBRE_LENGTH, stdin);
    pa[contador_paciente].peso[strcspn(pa[contador_paciente].peso, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    printf("Ingrese la fecha de ingreso (DD/MM/YYYY): ");
    fgets(pa[contador_paciente].fecha, MAX_NOMBRE_LENGTH, stdin);
    pa[contador_paciente].fecha[strcspn(pa[contador_paciente].fecha, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    contador_paciente++;

    printf("Paciente registrado con exito.\n");
}

// Funci�n para agregar un nuevo turno.
void agregar_turno()
{
    char nombre[30];
    char profesional[MAX_NOMBRE_LENGTH];
    int indice_profesional;
    printf("\nIngrese el nombre de usuario del profesional de la salud (medico): ");
    scanf("%s", nombre);
    getchar();

    if (indice_profesional == -1)
    {
        printf("Profesional de la salud no encontrado o no es un medico valido.\n");
        exit(1);
    }

    strcpy(da[contador_datos].profesional, us[indice_profesional].usuario);

    printf("Ingrese el nombre del paciente: ");
    getchar();
    fgets(da[contador_datos].paciente, MAX_NOMBRE_LENGTH, stdin);
    da[contador_datos].paciente[strcspn(da[contador_datos].paciente, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    printf("Ingrese la fecha del turno: ");
    fgets(da[contador_datos].date, MAX_NOMBRE_LENGTH, stdin);
    da[contador_datos].date[strcspn(da[contador_datos].date, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    contador_datos++;

    printf("Turno registrado con exito.\n");
}

// Funci�n para generar un informe de pacientes atendidos por un profesional en una fecha espec�fica.
void generar_informe()
{
    char profesional[MAX_NOMBRE_LENGTH];
    char fecha[MAX_NOMBRE_LENGTH];

    printf("\nIngrese el nombre del profesional de la salud (medico): ");
    scanf("%s", profesional);

    printf("Ingrese la fecha para el informe: ");
    scanf("%s", fecha);

    printf("\nInforme de pacientes atendidos el %s por el profesional %s:\n", fecha, profesional);

    int bandera = 0;
    for (int i = 0; i < contador_datos; i++)
    {
        if (strcmp(da[i].profesional, profesional) == 0 &&
            strcmp(da[i].date, fecha) == 0)
        {
            printf("- Paciente: %s\n", da[i].paciente);
            bandera = 1;
        }
    }

    if (!bandera)
    {
        printf("No se encontraron pacientes atendidos por el profesional %s en la fecha %s.\n", profesional, fecha);
    }
}

int main()
{
    int opcion;
    int logeado = 0; // Bandera que indica si el usuario ha iniciado sesion como recepcionista

    do
    {
        if (!logeado)
        {
            // Si el usuario no ha iniciado sesion, pedir que inicie sesion
            printf("\n=========================\n");
            printf("Modulo del recepcionista\n");
            printf("=========================\n");
            iniciar_sesion(); // Se solicita el inicio de sesion
            logeado = 1;     // Cambiar la bandera a indicar que ha iniciado sesion
        }
        else
        {
            // Si el usuario ha iniciado sesion, mostrar el men� normalmente
            printf("\n=========================\n");
            printf("Modulo del recepcionista\n");
            printf("=========================\n");
            printf("1- Registrar Pacientes\n");
            printf("2- Registrar Turno\n");
            printf("3- Listado de Atenciones por Profesional y Fecha\n");
            printf("0- Cerrar la aplicacion\n");

            printf("\nIngrese una opcion: ");
            scanf("%d", &opcion);

            switch (opcion)
            {
            case 1:
            {
                agregar_paciente();
                break;
            }
            case 2:
            {
                agregar_turno();
                break;
            }
            case 3:
            {
                generar_informe();
                break;
            }
            case 0:
            {
                printf("Gracias por usar nuestra sistema.\n");
                exit(1);
                break;
            }
            default:
            {
                printf("\nOpcion no valida. Por favor, seleccione una opcion valida.\n\n");
            }
            }
        }
    } while (opcion != 0);
    guardar_datos();
    return 0;
}
