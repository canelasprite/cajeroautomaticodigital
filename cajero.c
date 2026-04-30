/*
 * CAJERO AUTOMATICO DIGITAL
 * Lenguaje: C (C99)
 */

#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 5
#define MAX_STR      50

typedef struct {
    char   nombre[MAX_STR];
    char   clave[MAX_STR];
    double saldo;
    char   titular[MAX_STR];
} Usuario;

/* Prototipos */
int  iniciarSesion(Usuario u[], int *idx);
void mostrarMenu(void);

int main(void) {

    Usuario usuarios[MAX_USUARIOS] = {
        {"admin",  "1234",   5000.00, "Administrador"},
        {"jperez", "abcd",   1200.50, "Juan Perez"},
        {"mlopez", "pass1",  3400.75, "Maria Lopez"},
        {"cgomez", "qwerty",  800.00, "Carlos Gomez"},
        {"aruiz",  "9876",  15000.00, "Ana Ruiz"}
    };

    int idx = -1, opcion = 0;

    printf("====================================\n");
    printf("     CAJERO AUTOMATICO DIGITAL\n");
    printf("====================================\n\n");

    if (!iniciarSesion(usuarios, &idx)) {
        printf("[!] Acceso denegado. Credenciales incorrectas.\n");
        return 1;
    }

    printf("\nBienvenido/a, %s!\n", usuarios[idx].titular);

    /* Bucle principal: se mantiene activo hasta que el usuario elija salir */
    do {
        mostrarMenu();
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: printf("(Consultar saldo - en construccion)\n"); break;
            case 2: printf("(Depositar - en construccion)\n");       break;
            case 3: printf("(Retirar - en construccion)\n");         break;
            case 4: printf("\nSesion cerrada. Hasta luego!\n\n");    break;
            default: printf("[!] Opcion invalida.\n");               break;
        }
    } while (opcion != 4);

    return 0;
}

/* iniciarSesion: valida usuario y clave, devuelve 1 si son correctos */
int iniciarSesion(Usuario u[], int *idx) {
    char nombre[MAX_STR], clave[MAX_STR];
    int i;

    printf("Usuario   : "); scanf("%49s", nombre);
    printf("Contrasena: "); scanf("%49s", clave);

    for (i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(u[i].nombre, nombre) == 0 &&
            strcmp(u[i].clave, clave)   == 0) {
            *idx = i;
            return 1;
        }
    }

    return 0;
}

/* mostrarMenu: imprime las opciones disponibles */
void mostrarMenu(void) {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Consultar saldo\n");
    printf("2. Depositar dinero\n");
    printf("3. Retirar dinero\n");
    printf("4. Salir\n");
    printf("----------------------\n");
}
