/*
 * CAJERO AUTOMATICO DIGITAL
 * Lenguaje: C (C99)
 */

#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 5
#define MAX_STR      50

/* Estructura que representa una cuenta de usuario */
typedef struct {
    char   nombre[MAX_STR];   /* nombre de usuario para login  */
    char   clave[MAX_STR];    /* contrasena de acceso          */
    double saldo;             /* dinero disponible en la cuenta */
    char   titular[MAX_STR];  /* nombre real del dueno         */
} Usuario;

int main(void) {

    /* Usuarios predefinidos con saldo inicial */
    Usuario usuarios[MAX_USUARIOS] = {
        {"admin",  "1234",   5000.00, "Administrador"},
        {"jperez", "abcd",   1200.50, "Juan Perez"},
        {"mlopez", "pass1",  3400.75, "Maria Lopez"},
        {"cgomez", "qwerty",  800.00, "Carlos Gomez"},
        {"aruiz",  "9876",  15000.00, "Ana Ruiz"}
    };

    printf("CAJERO AUTOMATICO DIGITAL\n");
    printf("Usuarios cargados: %d\n", MAX_USUARIOS);

    return 0;
}