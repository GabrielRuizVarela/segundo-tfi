#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "estructuras.h"

struct Atencion atenciones[100];
int cantidadAtenciones = 0;

void registrarUsuario(const char *archivo, const char *usuario, const char *contrasenia, int rol)
{
    // Abre el archivo en modo de escritura binaria.
    FILE *file = fopen(archivo, "a+b");
    if (file == NULL)
    {
        file = fopen(archivo, "w+b");
        if (file == NULL)
        {
            printf("Error al abrir el archivo");
        }
    }

    // Escribe el usuario en el archivo.
    Usuario u;
    strcpy(u.usuario, usuario);
    strcpy(u.contrasenia, contrasenia);
    u.rol = rol;
    fwrite(&u, sizeof(Usuario), 1, file);

    // Cierra el archivo.
    fclose(file);
}

void validarUsuarioContrasenia(int rol)
{
    char usuario[50];
    char contrasenia[50];
    // Dentro de validarUsuarioContrasenia, despu�s de obtener el nombre de usuario y antes del ciclo while:
    int simbolos_usuario = 0; // Nueva variable para contar los s�mbolos permitidos en el nombre de usuario.

    int mayusculas_usuario = 0;
    int digitos_usuario = 0;
    int mayusculas_contrasenia = 0;
    int minusculas_contrasenia = 0;
    int numeros_consecutivos = 0;
    int letras_consecutivas = 0;
    int i;
    int longitud_usuario = strlen(usuario);
    int longitud_contrasenia = strlen(contrasenia);

    // Verificación del nombre de usuario
    while (1)
    {
        printf(" ---------------------\n");
        printf(" Requisitos a tener en cuenta en el nombre de usuario: ");
        printf("  \n\n 1.- Tener entre 6 y 10 caracteres\n\n 1.2.- Empezar con letra minuscula\n\n 1.3.-Tener dos letras mayusculas\n\n");
        printf(" 1.4.- Solo puede contener letras, numeros y los simbolos +, -, /, *, ?, ¿, !, ¡., como maximo 3 digitos \n\n");
        printf(" ---------------------\n");
        system("pause");
        system("cls"); // limpio la pantalla
        printf("\n\nIngrese nombre de usuario: ");
        scanf("%s", usuario);

        int longitud_usuario = strlen(usuario);

        if (longitud_usuario < 6 || longitud_usuario > 10 || usuario[0] < 'a' || usuario[0] > 'z')
        {
            printf("Advertencia: El nombre de usuario debe tener entre 6 y 10 caracteres y empezar con letra minuscula.\n");
            continue;
        }

        for (i = 0; i < longitud_usuario; i++)
        {
            // Dentro del ciclo for para validar el nombre de usuario:

            if ((usuario[i] >= 'A' && usuario[i] <= 'Z') || (usuario[i] >= 'a' && usuario[i] <= 'z'))
            {
                if (usuario[i] >= 'A' && usuario[i] <= 'Z')
                    mayusculas_usuario++;
            }
            else if (usuario[i] >= '0' && usuario[i] <= '9')
            {
                digitos_usuario++;
            }
            else if (strchr("+-/*?�!�", usuario[i]) != NULL)
            {
                simbolos_usuario++;
            }
            else
            {
                printf("Advertencia: El nombre de usuario solo puede contener letras, números y los símbolos +, -, /, *, ?, ¿, !, ¡.\n");
                break;
            }
        }

        if (mayusculas_usuario < 2)
        {
            printf("Advertencia: El nombre de usuario no cumple con las condiciones de mayusculas.\n");
            printf("Recordar que son 2 Mayusculas\n");
            mayusculas_usuario = 0;
            digitos_usuario = 0;
            continue;
        }
        else if (digitos_usuario > 3)
        {
            printf("Advertencia: El nombre de usuario no cumple con las condiciones de digitos.\n");
            printf("Recordar que son 3 digitos numericos o simbolicos\n");
            mayusculas_usuario = 0;
            digitos_usuario = 0;
            continue;
        }

        printf("Nombre de usuario valido: %s\n", usuario);
        break;
    }
    while (1)
    {
        printf(" ---------------------\n");
        printf(" Requisitos en la creacion de la contrasenia del usuario: ");
        printf("  \n\n 1.- Al menos una letra mayuscula, una letra minuscula y un numero.\n\n 1.2.- Solo caracteres alfanumericos.\n\n");
        printf(" 1.3.- Debera tener entre 6 y 32 caracteres \n\n 1.4.- No debe tener mas de 3 caracteres numericos consecutivos\n\n");
        printf(" 1.5.- No debe tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas (ascendentemente).\n\n 1.5.1.- Este criterio es valido tanto para letras mayusculas, minusculas o combinacion de ambas.\n\n");
        printf(" ---------------------\n");
        system("pause");
        system("cls"); // limpio la pantalla
        printf("Ingrese la contrasenia: ");
        scanf("%s", contrasenia);
        int longitud_contrasenia = strlen(contrasenia);

        if (longitud_contrasenia < 6 || longitud_contrasenia > 32)
        {
            printf("Advertencia: La contrasenia debe tener entre 6 y 32 caracteres.\n");
            continue;
        }

        mayusculas_contrasenia = 0;
        minusculas_contrasenia = 0;
        numeros_consecutivos = 0;
        letras_consecutivas = 0;

        for (i = 0; i < longitud_contrasenia; i++)
        {
            char c = contrasenia[i];
            if (isupper(c))
            {
                mayusculas_contrasenia++;
            }
            else if (islower(c))
            {
                minusculas_contrasenia++;
            }
            else if (isdigit(c))
            {
                // Revisa si los siguientes dos caracteres tambi�n son d�gitos para detectar 3 consecutivos.
                if (i < longitud_contrasenia - 2 && isdigit(contrasenia[i + 1]) && isdigit(contrasenia[i + 2]))
                {
                    numeros_consecutivos = 1; // Encuentra secuencia de tres n�meros.
                }
            }

            // Verifica secuencias alfab�ticas consecutivas, ignorando el primer car�cter.
            if (i > 0 && (tolower(c) - tolower(contrasenia[i - 1])) == 1 && !isdigit(c))
            {
                letras_consecutivas = 1;
            }
        }

        // Ahora eval�a todas las condiciones despu�s de analizar toda la contrase�a.
        if (mayusculas_contrasenia == 0)
        {
            printf("Advertencia: La contrasenia debe tener al menos una letra mayuscula.\n");
        }
        else if (minusculas_contrasenia == 0)
        {
            printf("Advertencia: La contrasenia debe tener al menos una letra minuscula.\n");
        }
        else if (numeros_consecutivos)
        {
            printf("Advertencia: La contrasenia no puede tener mas de 3 caracteres numericos consecutivos.\n");
        }
        else if (letras_consecutivas)
        {
            printf("Advertencia: La contrasenia no puede tener letras consecutivas de forma ascendente.\n");
        }
        else
        {
            printf("Contrasenia valida: %s\n", contrasenia);
            break; // Rompe el ciclo si todas las condiciones son correctas.
        }
    }
    if (rol == 1)
    {
        registrarUsuario("profesionales.dat", usuario, contrasenia, rol);
    }
    else
    {
        registrarUsuario("recepcionistas.dat", usuario, contrasenia, rol);
    }
}

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int extraer_mes(const char* fecha) {
    char strMes[3]; // Necesitamos solo dos caracteres para el mes, más el carácter nulo
    strncpy(strMes, fecha + 2, 2); // Copiamos los caracteres correspondientes al mes
    strMes[2] = '\0'; // Aseguramos que la cadena esté correctamente terminada
    return atoi(strMes); // Convertimos la cadena del mes a entero
}

void atencionesPorProfesional() {
    FILE *archivo = fopen("turnos.dat", "rb"); // Asegúrate de abrir en modo lectura binaria
    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        exit(1); // Considera manejar el error de manera diferente para no terminar abruptamente
    }

    char usuarioProfesional[MAX_NOMBRE_LENGTH];
    int mes, contadorAtenciones = 0;

    printf("Ingrese el usuario del profesional: ");
    scanf("%s", usuarioProfesional);
    limpiar_buffer(); // Limpia el buffer después de usar scanf

    printf("Ingrese el mes (1-12): ");
    scanf("%d", &mes);
    limpiar_buffer(); // Limpia el buffer después de usar scanf

    Turno turno;

    while (fread(&turno, sizeof(Turno), 1, archivo)) {
        int mesTurno = extraer_mes(turno.fecha);

        if (strcmp(turno.usuario, usuarioProfesional) == 0 && mes == mesTurno) {
            contadorAtenciones++;
        }
    }

    fclose(archivo);

    printf("El profesional %s tiene %d atenciones en el mes %d.\n", usuarioProfesional, contadorAtenciones, mes);
}

typedef struct {
    char usuario[MAX_NOMBRE_LENGTH];
    int atenciones;
} ProfesionalAtencion;

void rankingProfesionales() {
    FILE *archivo = fopen("turnos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura\n");
        exit(1);
    }

    ProfesionalAtencion profesionales[MAX_NOMBRE_LENGTH];
    int numProfesionales = 0;
    Turno turno;

    // Inicializar el conteo de atenciones a 0 para todos los profesionales
    for (int i = 0; i < MAX_NOMBRE_LENGTH; i++) {
        profesionales[i].atenciones = 0;
    }

    // Leer turnos y contar atenciones por profesional
    while (fread(&turno, sizeof(Turno), 1, archivo)) {
        int encontrado = 0;
        for (int i = 0; i < numProfesionales; i++) {
            if (strcmp(profesionales[i].usuario, turno.usuario) == 0) {
                profesionales[i].atenciones++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado && numProfesionales < MAX_NOMBRE_LENGTH) {
            strncpy(profesionales[numProfesionales].usuario, turno.usuario, MAX_NOMBRE_LENGTH);
            profesionales[numProfesionales].atenciones = 1;
            numProfesionales++;
        }
    }

    fclose(archivo);

    // Ordenar profesionales por cantidad de atenciones
    for (int i = 0; i < numProfesionales - 1; i++) {
        for (int j = i + 1; j < numProfesionales; j++) {
            if (profesionales[i].atenciones < profesionales[j].atenciones) {
                ProfesionalAtencion temp = profesionales[i];
                profesionales[i] = profesionales[j];
                profesionales[j] = temp;
            }
        }
    }

    // Mostrar ranking
    printf("Ranking de Profesionales por Atenciones:\n");
    for (int i = 0; i < numProfesionales; i++) {
        printf("%d. %s - %d atenciones\n", i + 1, profesionales[i].usuario, profesionales[i].atenciones);
    }
}

int menu()
{
    int opcion;
    printf("=========================\n");
    printf("Modulo Administracion\n");
    printf("=========================\n");
    printf("1- Registrar Profesionales\n");
    printf("2- Registrar Usuario Recepcionista\n");
    printf("3- Atenciones por profesional\n");
    printf("4- Ranking de Profesionales por Atenciones\n");
    printf("5- Registrar Atencion\n");
    printf("0- Cerrar la aplicacion.\n");
    printf("\nIngrese una opcion:\n ");
    scanf("%d", &opcion);
    return opcion;
}

int main()
{
    const char *password;
    const char *username;
    int seleccion;
    do
    {
        seleccion = menu();

        switch (seleccion)
        {
        case 1:
        {
            validarUsuarioContrasenia(1);
            break;
        }
        case 2:
        {
            validarUsuarioContrasenia(2);
            break;
        }
        case 3:
        {
            atencionesPorProfesional();
            break;
        }
        case 4:
        {
            rankingProfesionales();
            break;
        }
        case 0:
        {
            printf("Gracias por usar nuestro sistema...");
            break;
        }
        default:
        {
            printf("Opcion invalida");
            break;
        }
        }
    } while (seleccion != 0);
}
