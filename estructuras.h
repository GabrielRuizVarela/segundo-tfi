#include <stdio.h>

#define MAX_NOMBRE_USUARIO_LENGTH 50
#define MAX_CONTRASENIA_LENGTH 50
#define MAX_NOMBRE_LENGTH 50

typedef struct {
    char dniPaciente[MAX_NOMBRE_LENGTH]; // DNI del paciente para vincular la historia
    char fechaAtencion[MAX_NOMBRE_LENGTH]; // Fecha en que se atendió al paciente
    char usuario[MAX_NOMBRE_LENGTH]; // Usuario que atendió al paciente
    char notaHistoria[381]; // Notas de la historia clínica, hasta 380 caracteres
} HistoriaClinica;


// // ADNINISTRACION
// struct User
// {
//     char nombre[11];
//     char password[33];
// };

// struct Usuario
// {
//     char nombre[50];
//     char password[64];
// };
// // CONSULTORIO
// struct Fecha
// {
//     int anio;
// };

// struct usuarios
// {
//     char usuario[10];
//     char contrasenia[32];
// };
// struct registro
// {
//     char ApeNomP[60];
//     char Domicilio[60];
//     int DniPaciente[8];
//     char Localidad[60];
//     Fecha fec;
//     int edad;
//     float peso;
//     float talla;
//     int Telefono;
// };
// RECEPCION
typedef struct
{
    char usuario[MAX_NOMBRE_USUARIO_LENGTH];
    char contrasenia[MAX_CONTRASENIA_LENGTH];
    int rol; // 1: medico, 2: Recepcionista
} Usuario;

typedef struct
{
    char name[MAX_NOMBRE_LENGTH];
    char apellido[MAX_NOMBRE_LENGTH];
    char dni[MAX_NOMBRE_LENGTH];
    char domicilio[MAX_NOMBRE_LENGTH];
    char localidad[MAX_NOMBRE_LENGTH];
    char peso[MAX_NOMBRE_LENGTH];
    char talla[MAX_NOMBRE_LENGTH];
    char fecha[MAX_NOMBRE_LENGTH];
} Paciente;

typedef struct
{
    char name[MAX_NOMBRE_LENGTH];
    char apellido[MAX_NOMBRE_LENGTH];
    char contrasenia[MAX_CONTRASENIA_LENGTH];
    char dni[MAX_NOMBRE_LENGTH];
    char domicilio[MAX_NOMBRE_LENGTH];
    char telefono[MAX_NOMBRE_LENGTH];
} Profesional;

typedef struct
{
    char usuario[MAX_NOMBRE_LENGTH];
    char dniPaciente[MAX_NOMBRE_LENGTH];
    char fecha[MAX_NOMBRE_LENGTH];
} Turno;
