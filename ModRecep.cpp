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

// Función para buscar un usuario por nombre y verificar si es médico
int buscar_indice_profesional(const char *nombreProfesional)
{
    for (int i = 0; i < contador_usuario; i++)
    {
        if (strcmp(us[i].usuario, nombreProfesional) == 0 && us[i].rol == 1)
        {
            return i; // Retorna el índice del usuario si es médico
        }
    }
    return -1; // Retorna -1 si no se encuentra el profesional o no es médico
}

// Verificar si el paciente ya existe por DNI
int verificar_paciente_existente(const char *dni)
{
    for (int i = 0; i < contador_paciente; i++)
    {
        if (strcmp(pa[i].dni, dni) == 0)
        {
            return 1; // Paciente ya existe
        }
    }
    return 0; // Paciente no existe
}

// Verificar si el turno ya existe por profesional y fecha
int verificar_turno_existente(const char *profesional, const char *fecha)
{
    for (int i = 0; i < contador_datos; i++)
    {
        if (strcmp(da[i].profesional, profesional) == 0 && strcmp(da[i].date, fecha) == 0)
        {
            return 1; // Turno ya existe
        }
    }
    return 0; // Turno no existe
}

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
    FILE *file = fopen("data.txt", "w"); // Abrir el archivo en modo de escritura
    if (file == NULL)
    {
        printf("Error al abrir el archivo para guardar datos.\n");
        exit(1);
    }

    // Guardar usuarios
    fprintf(file, "%d\n", contador_usuario);
    for (int i = 0; i < contador_usuario; i++)
    {
        fprintf(file, "%s %s %d\n", us[i].usuario, us[i].contrasenia, us[i].rol);
    }

    // Guardar pacientes
    fprintf(file, "%d\n", contador_paciente);
    for (int i = 0; i < contador_paciente; i++)
    {
        fprintf(file, "%s %s %s %s %s %s %s\n", pa[i].name, pa[i].apellido, pa[i].dni, pa[i].domicilio, pa[i].peso, pa[i].talla, pa[i].fecha);
    }

    // Guardar datos (turnos, etc.)
    fprintf(file, "%d\n", contador_datos);
    for (int i = 0; i < contador_datos; i++)
    {
        fprintf(file, "%s %s %s\n", da[i].profesional, da[i].paciente, da[i].date);
    }

    fclose(file); // Cerrar el archivo
    printf("Datos guardados con éxito.\n");
}

// Funcion para cargar datos desde un archivo.
void cargar_datos()
{
    FILE *file = fopen("data.txt", "r"); // Abrir el archivo en modo de lectura
    if (file == NULL)
    {
        printf("No se encontró el archivo de datos o no se pudo abrir.\n");
        return; // Si no se puede abrir el archivo, salir de la función
    }

    // Cargar usuarios
    fscanf(file, "%d\n", &contador_usuario);
    for (int i = 0; i < contador_usuario; i++)
    {
        fscanf(file, "%s %s %d\n", us[i].usuario, us[i].contrasenia, &us[i].rol);
    }

    // Cargar pacientes
    fscanf(file, "%d\n", &contador_paciente);
    for (int i = 0; i < contador_paciente; i++)
    {
        fscanf(file, "%s %s %s %s %s %s %s\n", pa[i].name, pa[i].apellido, pa[i].dni, pa[i].domicilio, pa[i].peso, pa[i].talla, pa[i].fecha);
    }

    // Cargar datos (turnos, etc.)
    fscanf(file, "%d\n", &contador_datos);
    for (int i = 0; i < contador_datos; i++)
    {
        fscanf(file, "%s %s %s\n", da[i].profesional, da[i].paciente, da[i].date);
    }

    fclose(file); // Cerrar el archivo
    printf("Datos cargados con éxito.\n");
}

// Funci�n para agregar un nuevo paciente.
void agregar_paciente()
{
    if (contador_paciente >= MAX_PACIENTE)
    {
        printf("No se pueden agregar mas pacientes. Limite alcanzado.\n");
    }

    Paciente nuevoPaciente;
    printf("\nIngrese el DNI del paciente: ");
    getchar(); // Consumir el salto de línea pendiente del buffer
    fgets(nuevoPaciente.dni, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.dni[strcspn(nuevoPaciente.dni, "\n")] = '\0'; // Eliminar el salto de línea al final

    if (verificar_paciente_existente(nuevoPaciente.dni))
    {
        printf("Error: Ya existe un paciente con el mismo DNI.\n");
        return;
    }

    printf("Ingrese el nombre del paciente: ");
    fgets(nuevoPaciente.name, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.name[strcspn(nuevoPaciente.name, "\n")] = '\0'; // Eliminar el salto de línea al final

    printf("Ingrese el apellido del paciente: ");
    fgets(nuevoPaciente.apellido, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.apellido[strcspn(nuevoPaciente.apellido, "\n")] = '\0'; // Eliminar el salto de línea al final

    printf("Ingrese el domicilio del paciente: ");
    fgets(nuevoPaciente.domicilio, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.domicilio[strcspn(nuevoPaciente.domicilio, "\n")] = '\0'; // Eliminar el salto de línea al final

    printf("Ingrese el peso del paciente: ");
    fgets(nuevoPaciente.peso, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.peso[strcspn(nuevoPaciente.peso, "\n")] = '\0'; // Eliminar el salto de línea al final

    printf("Ingrese la fecha de ingreso (DD/MM/YYYY): ");
    fgets(nuevoPaciente.fecha, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.fecha[strcspn(nuevoPaciente.fecha, "\n")] = '\0'; // Eliminar el salto de línea al final

    pa[contador_paciente] = nuevoPaciente;
    contador_paciente++;
    guardar_datos();
    printf("Paciente registrado con exito.\n");
}

// Funcion para agregar un nuevo turno.
void agregar_turno()
{

    if (contador_datos >= MAX_DATOS)
    {
        printf("No se pueden agregar más turnos. Límite alcanzado.\n");
        return;
    }

    Datos nuevoTurno;
    printf("\nIngrese el nombre de usuario del profesional de la salud (médico): ");
    scanf("%s", nuevoTurno.profesional);
    getchar();

    // Validar la existencia del profesional
    int indiceProfesional = buscar_indice_profesional(nuevoTurno.profesional);
    if (indiceProfesional == -1)
    {
        printf("Profesional de la salud no encontrado o no es un médico válido.\n");
        return;
    }

    printf("Ingrese la fecha del turno: ");
    fgets(nuevoTurno.date, MAX_NOMBRE_LENGTH, stdin);
    nuevoTurno.date[strcspn(nuevoTurno.date, "\n")] = '\0'; // Eliminar el salto de línea al final

    if (verificar_turno_existente(nuevoTurno.profesional, nuevoTurno.date))
    {
        printf("Error: Ya existe un turno para el profesional en la fecha indicada.\n");
        return;
    }

    printf("Ingrese el nombre del paciente: ");
    getchar();
    fgets(da[contador_datos].paciente, MAX_NOMBRE_LENGTH, stdin);
    da[contador_datos].paciente[strcspn(da[contador_datos].paciente, "\n")] = '\0'; // Eliminar el salto de l�nea al final

    da[contador_datos] = nuevoTurno; // Agregar el nuevo turno
    contador_datos++;
    guardar_datos();

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
    cargar_datos();
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
            logeado = 1;      // Cambiar la bandera a indicar que ha iniciado sesion
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
