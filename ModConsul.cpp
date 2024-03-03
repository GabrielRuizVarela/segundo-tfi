
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estructuras.h"

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
    char usuario[100], contrasenia[100];
    int mayusculas = 0, i;
    // si quiero corroborar que anda bien hacer fallar usuario no contrase�a
    printf("Ingrese nombre de usuario: ");
    scanf("%s", usuario);

    printf("Ingrese contrase�a : ");
    scanf("%s", contrasenia);

    FILE *file = fopen("profesionales.dat", "rb");
    if (file == NULL)
    {
        printf("Error al abrir el archivo");
        exit(1);
    }
    int encontrado = 0;
    while (fread(&res[0], sizeof(Usuario), 1, file))
    {
        if (strcmp(usuario, res[0].usuario) == 0 && strcmp(contrasenia, res[0].contrasenia) == 0)
        {
            encontrado = 1;
            break;
        }
    }
    fclose(file);
    if (encontrado)
    {
        printf("Bienvenido a nuestro sistema..\n");
    }
    else
    {
        printf("Usuario y contrase�a incorrectos\n");
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
int menu()
{
    int opcion;
    printf("=========================\n");
    printf("Modulo Consultorio\n");
    printf("=========================\n");
    printf("1- Iniciar sesion\n");
    printf("2- Visualizar lista de espera de turnos(informe)\n");
    printf("3- Registrar historia clinica\n");
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

        switch (seleccion)
        {
        case 1:
        {
            Iniciarsesion();
            break;
        }
        case 2:
        {
            VisualizarLista();
            break;
        }
        case 3:
        {
            RegistrarHistoria();
            break;
        }
        case 0:
        {
            printf("Gracias por usar nuestro sistema...");
            break;
        }
        default:
        {
            printf("Opci�n inv�lida");
            break;
        }
        }
    } while (seleccion != 0);
    return 0;
}
