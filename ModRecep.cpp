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

Turno da[MAX_DATOS];
int contador_datos = 0;

Usuario prof[MAX_USUARIO];
int contador_profesional = 0;

// Función para buscar un usuario por nombre y verificar si es médico
int buscar_indice_profesional(const char *usuarioProfesional)
{
    for (int i = 0; i < contador_usuario; i++)
    {
        if (strcmp(prof[i].usuario, usuarioProfesional) == 0)
        {
            return 1;
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

void guardar_usuarios(Usuario *usuarios, int contador, const char *archivo)
{
    FILE *file = fopen(archivo, "wb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo %s.\n", archivo);
        return;
    }
    fwrite(usuarios, sizeof(Usuario), contador, file);
    fclose(file);
}

void cargar_profesionales(Usuario *usuarios, int *contador, const char *archivo)
{
    FILE *file = fopen(archivo, "rb");
    if (file == NULL)
    {
        file = fopen(archivo, "wb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo %s.\n", archivo);
        }
        *contador = 0; // Asegurar que el contador es 0 si el archivo no existe
        return;
    }
    *contador = fread(usuarios, sizeof(Usuario), MAX_USUARIO, file);
    fclose(file);
}

void cargar_usuarios(Usuario *usuarios, int *contador, const char *archivo)
{
    FILE *file = fopen(archivo, "rb");
    if (file == NULL)
    {
        file = fopen(archivo, "wb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo %s.\n", archivo);
        }
        *contador = 0; // Asegurar que el contador es 0 si el archivo no existe
        return;
    }
    *contador = fread(usuarios, sizeof(Usuario), MAX_USUARIO, file);
    fclose(file);
}

void guardar_pacientes(Paciente *pacientes, int contador, const char *archivo)
{
    FILE *file = fopen(archivo, "wb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo %s para guardar.\n", archivo);
        return;
    }
    fwrite(pacientes, sizeof(Paciente), contador, file);
    fclose(file);
}

void cargar_pacientes(Paciente *pacientes, int *contador, const char *archivo)
{
    FILE *file = fopen(archivo, "rb");
    if (file == NULL)
    {
        file = fopen(archivo, "wb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo %s para cargar.\n", archivo);
        }
        *contador = 0; // Asegurar que el contador es 0 si el archivo no existe
        return;
    }
    *contador = fread(pacientes, sizeof(Paciente), MAX_PACIENTE, file);
    fclose(file);
}

void guardar_turnos(Turno *turnos, int contador, const char *archivo)
{
    FILE *file = fopen(archivo, "wb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo %s para guardar.\n", archivo);
        return;
    }
    fwrite(turnos, sizeof(Turno), contador, file);
    fclose(file);
}

void cargar_turnos(Turno *turnos, int *contador, const char *archivo)
{
    FILE *file = fopen(archivo, "rb");
    if (file == NULL)
    {
        // crea el archivo si no existe
        file = fopen(archivo, "wb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo %s para cargar.\n", archivo);
        }
        *contador = 0; // Asegurar que el contador es 0 si el archivo no existe
        return;
    }
    *contador = fread(turnos, sizeof(Turno), MAX_DATOS, file);
    fclose(file);
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

    printf("Ingrese la localidad del paciente: ");
    fgets(nuevoPaciente.localidad, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.localidad[strcspn(nuevoPaciente.localidad, "\n")] = '\0'; // Eliminar el salto de línea al final

    printf("Ingrese el peso del paciente: ");
    fgets(nuevoPaciente.peso, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.peso[strcspn(nuevoPaciente.peso, "\n")] = '\0'; // Eliminar el salto de línea al final

    printf("Ingrese la fecha de ingreso (DD/MM/YYYY): ");
    fgets(nuevoPaciente.fecha, MAX_NOMBRE_LENGTH, stdin);
    nuevoPaciente.fecha[strcspn(nuevoPaciente.fecha, "\n")] = '\0'; // Eliminar el salto de línea al final

    pa[contador_paciente] = nuevoPaciente;
    contador_paciente++;
    guardar_pacientes(pa, contador_paciente, "pacientes.dat");
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

    Turno nuevoTurno;
    printf("\nIngrese usuario del profesional de la salud (médico): ");
    scanf("%s", nuevoTurno.usuario);
    getchar();

    // Validar la existencia del profesional
    int indiceProfesional = buscar_indice_profesional(nuevoTurno.usuario);
    if (indiceProfesional == -1)
    {
        printf("Profesional de la salud no encontrado o no es un médico válido.\n");
        return;
    }

    printf("Ingrese la fecha del turno: ");
    getchar();
    fgets(nuevoTurno.fecha, MAX_NOMBRE_LENGTH, stdin);
    nuevoTurno.fecha[strcspn(nuevoTurno.fecha, "\n")] = '\0'; // Eliminar el salto de línea al final

    printf("Ingrese el dni del paciente: ");
    getchar();
    fgets(nuevoTurno.dniPaciente, MAX_NOMBRE_LENGTH, stdin);
    nuevoTurno.dniPaciente[strcspn(nuevoTurno.dniPaciente, "\n")] = '\0'; // Eliminar el salto de línea al final

    da[contador_datos] = nuevoTurno; // Agregar el nuevo turno
    contador_datos++;
    guardar_turnos(da, contador_datos, "turnos.dat");

    printf("Turno registrado con exito.\n");
}

// Funci�n para generar un informe de pacientes atendidos por un profesional en una fecha espec�fica.
void generar_informe()
{
    char usuario[MAX_NOMBRE_LENGTH];
    char fecha[MAX_NOMBRE_LENGTH];

    printf("\nIngrese el usuario del profesional de la salud (medico): ");
    scanf("%s", usuario);

    printf("Ingrese la fecha del informe (DD/MM/YYYY): ");
    scanf("%s", fecha);

    printf("\nListado de atenciones para el profesional %s en la fecha %s:\n", usuario, fecha);
    printf("=============================================================\n");

    for (int i = 0; i < contador_datos; i++)
    {
        if (strcmp(da[i].usuario, usuario) == 0 && strcmp(da[i].fecha, fecha) == 0)
        {
            for (int j = 0; j < contador_paciente; j++)
            {
                printf("TEST: %s %s\n", pa[j].dni, da[i].dniPaciente);
                if (strcmp(da[i].dniPaciente, pa[j].dni) == 0)
                {
                    printf("Paciente: %s %s\n", pa[j].name, pa[j].apellido);
                }
            }
        }
    }
}

int main()
{
    cargar_usuarios(us, &contador_usuario, "recepcionistas.dat");
    cargar_profesionales(prof, &contador_profesional, "profesionales.dat");
    cargar_pacientes(pa, &contador_paciente, "pacientes.dat");
    cargar_turnos(da, &contador_datos, "turnos.dat");
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
    return 0;
}
