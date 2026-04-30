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
void consultarSaldo(Usuario *u);
void depositar(Usuario *u);
void retirar(Usuario *u);

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

    do {
        mostrarMenu();
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: consultarSaldo(&usuarios[idx]); break;
            case 2: depositar(&usuarios[idx]);      break;
            case 3: retirar(&usuarios[idx]);        break;
            case 4: printf("\nSesion cerrada. Hasta luego!\n\n"); break;
            default: printf("[!] Opcion invalida.\n");            break;
        }
    } while (opcion != 4);

    return 0;
}

/* iniciarSesion: valida usuario y clave */
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

/* mostrarMenu: imprime las opciones del sistema */
void mostrarMenu(void) {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Consultar saldo\n");
    printf("2. Depositar dinero\n");
    printf("3. Retirar dinero\n");
    printf("4. Salir\n");
    printf("----------------------\n");
}

/* consultarSaldo: muestra el saldo actual del usuario */
void consultarSaldo(Usuario *u) {
    printf("\nTitular: %s\n", u->titular);
    printf("Saldo  : $%.2f\n", u->saldo);
}

/* depositar: agrega un monto positivo al saldo del usuario */
void depositar(Usuario *u) {
    double monto;

    printf("Monto a depositar: $");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("[!] El monto debe ser mayor a cero.\n");
        return;
    }

    u->saldo += monto;
    printf("[OK] Deposito de $%.2f. Nuevo saldo: $%.2f\n", monto, u->saldo);
}

/* retirar: descuenta un monto si el usuario tiene fondos suficientes */
void retirar(Usuario *u) {
    double monto;

    printf("Saldo disponible: $%.2f\n", u->saldo);
    printf("Monto a retirar : $");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("[!] El monto debe ser mayor a cero.\n");
        return;
    }

    if (monto > u->saldo) {
        printf("[!] Fondos insuficientes. Saldo actual: $%.2f\n", u->saldo);
        return;
    }

    u->saldo -= monto;
    printf("[OK] Retiro de $%.2f. Nuevo saldo: $%.2f\n", monto, u->saldo);
}
