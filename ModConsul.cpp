
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "estructuras.h"
#define MAX_TURNOS 100 // Un límite arbitrario para la demostración

Turno turnosEncontrados[MAX_TURNOS]; // Arreglo global de turnos encontrados
int cantidadTurnos = 0;              // Contador global de turnos encontrados

Usuario usuarioActual; // Variable global para almacenar el usuario que inició sesión

int usuarioLogueado = 0; // 0: no logueado, 1: logueado

Paciente pacientes[MAX_TURNOS]; // Arreglo global de pacientes encontrados
int cantidadPacientes = 0;      // Contador global de pacientes encontrados

void limpiar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void cargar_pacientes()
{
    FILE *file = fopen("pacientes.dat", "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    int encontrado = 0;
    Paciente tempPaciente; // Variable temporal para leer pacientes del archivo
    while (fread(&tempPaciente, sizeof(Paciente), 1, file))
    {
        pacientes[cantidadPacientes++] = tempPaciente; // Almacenar el paciente encontrado
        cantidadPacientes++;
    }
    fclose(file);
}

void cargar_turnos()
{
    FILE *file = fopen("turnos.dat", "rb");
    if (file == NULL)
    {
        file = fopen("turnos.dat", "wb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo");
            exit(1);
        }
    }
    int encontrado = 0;
    Turno tempTurno; // Variable temporal para leer turnos del archivo
    while (fread(&tempTurno, sizeof(Turno), 1, file))
    {
        turnosEncontrados[encontrado++] = tempTurno; // Almacenar el turno encontrado
    }
    cantidadTurnos = encontrado;
    fclose(file);
}

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
        cargar_pacientes();
    }
    else
    {
        printf("Usuario y contraseña incorrectos\n");
        exit(1);
    }
}

void removerPaciente(HistoriaClinica hc)
{
    Turno nuevoTurnosEncontrados[MAX_TURNOS]; // Arreglo temporal para almacenar los turnos que no se eliminarán
    int cantidadNuevosTurnos = 0;             // Contador temporal de turnos que no se eliminarán

    for (int i = 0; i < cantidadTurnos; i++)
    {
        if (strcmp(hc.dniPaciente, turnosEncontrados[i].dniPaciente) != 0 || strcmp(hc.fechaAtencion, turnosEncontrados[i].fecha) != 0)
        {
            nuevoTurnosEncontrados[cantidadNuevosTurnos++] = turnosEncontrados[i]; // Almacenar el turno que no se eliminará
        }
    }

    memcpy(turnosEncontrados, nuevoTurnosEncontrados, sizeof(nuevoTurnosEncontrados)); // Actualizar el arreglo global de turnos encontrados
    cantidadTurnos = cantidadNuevosTurnos;                                             // Actualizar el contador global de turnos encontrados

    FILE *file = fopen("turnos.dat", "wb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo");
        exit(1);
    }
    for (int i = 0; i < cantidadTurnos; i++)
    {
        fwrite(&turnosEncontrados[i], sizeof(Turno), 1, file);
    }
    fclose(file);

    printf("Paciente removido de la lista de espera.\n");
}

void registrarHistoriaClinica()
{
    HistoriaClinica hc;

    printf("Registro de Historia Clínica\n");
    printf("Ingrese DNI del paciente: ");
    scanf("%s", hc.dniPaciente);
    limpiar_buffer();

    printf("Ingrese fecha de atención (DDMMYYYY): ");
    scanf("%s", hc.fechaAtencion);
    limpiar_buffer();

    // validar que tiene un turno para esa fecha
    int turnoEncontrado = 0;
    for (int i = 0; i < cantidadTurnos; i++)
    {
        if (strcmp(hc.fechaAtencion, turnosEncontrados[i].fecha) == 0 && strcmp(hc.dniPaciente, turnosEncontrados[i].dniPaciente) == 0)
        {
            turnoEncontrado = 1;
            break;
        }
    }

    if (!turnoEncontrado)
    {
        printf("No se encontró un turno para el paciente con DNI %s en la fecha %s.\n", hc.dniPaciente, hc.fechaAtencion);
        return;
    }

    printf("Ingrese notas de la historia clínica (hasta 380 caracteres): ");
    fgets(hc.notaHistoria, 381, stdin);

    FILE *file = fopen("historias.dat", "ab");
    if (file == NULL)
    {
        file = fopen("historias.dat", "wb");
        if (file == NULL)
        {
            printf("Error al abrir el archivo");
            exit(1);
        }
    }
    fwrite(&hc, sizeof(HistoriaClinica), 1, file);
    fclose(file);

    printf("Historia clínica registrada con éxito.\n");
    // remover paciente de la lista de espera
    removerPaciente(hc);
}

int calcularEdad(const char *fechaNacimiento)
{
    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm tiempoActual = *localtime(&t);

    // Extraer año, mes y día de la fecha de nacimiento
    char strAnio[5], strMes[3], strDia[3];
    strncpy(strAnio, fechaNacimiento + 4, 4); // Año está en las posiciones 4 a 7
    strAnio[4] = '\0';

    strncpy(strMes, fechaNacimiento + 2, 2); // Mes está en las posiciones 2 y 3
    strMes[2] = '\0';

    strncpy(strDia, fechaNacimiento, 2); // Día está en las posiciones 0 y 1
    strDia[2] = '\0';

    int anioNac = atoi(strAnio);
    int mesNac = atoi(strMes);
    int diaNac = atoi(strDia);

    // Calcular la edad preliminar
    int edad = tiempoActual.tm_year + 1900 - anioNac;

    // Ajustar la edad basándose en si la persona ya cumplió años este año
    if (mesNac > (tiempoActual.tm_mon + 1) ||
        (mesNac == (tiempoActual.tm_mon + 1) && diaNac > tiempoActual.tm_mday))
    {
        edad--; // Restar un año si no ha cumplido años aún
    }

    return edad;
}

void turnos_del_dia()
{

    char fecha[MAX_NOMBRE_LENGTH];
    printf("Ingrese la fecha del turno a buscar (DDMMYYYY): ");
    scanf("%s", fecha);
    limpiar_buffer(); // Limpia el buffer después de usar scanf

    // Opcional: imprimir los turnos almacenados en la variable global
    if (cantidadTurnos == 0)
    {
        printf("No se encontraron turnos para %s en la fecha %s.\n", usuarioActual.usuario, fecha);
    }
    else
    {
        int edad = 0;
        printf("Turnos encontrados para %s en la fecha %s:\n", usuarioActual.usuario, fecha);
        for (int i = 0; i < cantidadTurnos; i++)
        {
            // buscar con dni del paciente
            for (int j = 0; j < cantidadPacientes; j++)
            {
                if (strcmp(turnosEncontrados[i].dniPaciente, pacientes[j].dni) == 0)
                {
                    edad = calcularEdad(pacientes[j].fecha);
                    printf("TURNO %d:\n", i + 1);
                    printf("Paciente: %s %s edad: %d\n", pacientes[j].name, pacientes[j].apellido, edad);
                    break;
                }
            }
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
    cargar_turnos();
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
                turnos_del_dia();
            break;
        case 3:
            if (usuarioLogueado)
                registrarHistoriaClinica();
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
