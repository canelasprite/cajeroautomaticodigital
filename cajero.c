/*
 * CAJERO AUTOMATICO DIGITAL
 * Lenguaje: C (C99)
 *
 * MEJORAS:
 * - Limite de intentos en login (max. 3)
 * - Historial de transacciones por sesion
 * - Cambio de contrasena
 */

#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS  5
#define MAX_STR       50
#define MAX_INTENTOS  3
#define MAX_HISTORIAL 10   /* Maximo de transacciones por sesion */

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
void depositar(Usuario *u, char hist[][MAX_STR], int *cnt);
void retirar(Usuario *u, char hist[][MAX_STR], int *cnt);
void cambiarClave(Usuario *u);
void verHistorial(char hist[][MAX_STR], int cnt);

int main(void) {

    Usuario usuarios[MAX_USUARIOS] = {
        {"admin",  "1234",   5000.00, "Administrador"},
        {"jperez", "abcd",   1200.50, "Juan Perez"},
        {"mlopez", "pass1",  3400.75, "Maria Lopez"},
        {"cgomez", "qwerty",  800.00, "Carlos Gomez"},
        {"aruiz",  "9876",  15000.00, "Ana Ruiz"}
    };

    int  idx = -1, opcion = 0, cnt = 0;
    char historial[MAX_HISTORIAL][MAX_STR];

    printf("====================================\n");
    printf("     CAJERO AUTOMATICO DIGITAL\n");
    printf("====================================\n\n");

    if (!iniciarSesion(usuarios, &idx)) {
        printf("[!] Acceso bloqueado. Demasiados intentos fallidos.\n");
        return 1;
    }

    printf("\nBienvenido/a, %s!\n", usuarios[idx].titular);

    do {
        mostrarMenu();
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: consultarSaldo(&usuarios[idx]);                    break;
            case 2: depositar(&usuarios[idx], historial, &cnt);        break;
            case 3: retirar(&usuarios[idx], historial, &cnt);          break;
            case 4: cambiarClave(&usuarios[idx]);                      break;
            case 5: verHistorial(historial, cnt);                      break;
            case 6: printf("\nSesion cerrada. Hasta luego!\n\n");      break;
            default: printf("[!] Opcion invalida.\n");                 break;
        }
    } while (opcion != 6);

    return 0;
}

/* iniciarSesion: valida credenciales con maximo de MAX_INTENTOS intentos */
int iniciarSesion(Usuario u[], int *idx) {
    char nombre[MAX_STR], clave[MAX_STR];
    int  intentos = 0, i;

    while (intentos < MAX_INTENTOS) {
        printf("Usuario   : "); scanf("%49s", nombre);
        printf("Contrasena: "); scanf("%49s", clave);

        for (i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(u[i].nombre, nombre) == 0 &&
                strcmp(u[i].clave, clave)   == 0) {
                *idx = i;
                return 1;
            }
        }

        intentos++;
        printf("[!] Credenciales incorrectas. Intentos restantes: %d\n\n",
               MAX_INTENTOS - intentos);
    }

    return 0;
}

/* mostrarMenu: imprime las opciones del sistema */
void mostrarMenu(void) {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Consultar saldo\n");
    printf("2. Depositar dinero\n");
    printf("3. Retirar dinero\n");
    printf("4. Cambiar contrasena\n");
    printf("5. Ver historial\n");
    printf("6. Salir\n");
    printf("----------------------\n");
}

/* consultarSaldo: muestra el saldo actual del usuario */
void consultarSaldo(Usuario *u) {
    printf("\nTitular: %s\n", u->titular);
    printf("Saldo  : $%.2f\n", u->saldo);
}

/* depositar: agrega monto positivo al saldo y registra en historial */
void depositar(Usuario *u, char hist[][MAX_STR], int *cnt) {
    double monto;

    printf("Monto a depositar: $");
    scanf("%lf", &monto);

    if (monto <= 0) { printf("[!] El monto debe ser mayor a cero.\n"); return; }

    u->saldo += monto;
    printf("[OK] Deposito de $%.2f. Nuevo saldo: $%.2f\n", monto, u->saldo);

    if (*cnt < MAX_HISTORIAL)
        sprintf(hist[(*cnt)++], "DEP +$%.2f | $%.2f", monto, u->saldo);
}

/* retirar: descuenta monto si hay fondos y registra en historial */
void retirar(Usuario *u, char hist[][MAX_STR], int *cnt) {
    double monto;

    printf("Saldo disponible: $%.2f\n", u->saldo);
    printf("Monto a retirar : $");
    scanf("%lf", &monto);

    if (monto <= 0)       { printf("[!] El monto debe ser mayor a cero.\n"); return; }
    if (monto > u->saldo) { printf("[!] Fondos insuficientes.\n");           return; }

    u->saldo -= monto;
    printf("[OK] Retiro de $%.2f. Nuevo saldo: $%.2f\n", monto, u->saldo);

    if (*cnt < MAX_HISTORIAL)
        sprintf(hist[(*cnt)++], "RET -$%.2f | $%.2f", monto, u->saldo);
}

/* cambiarClave: actualiza la clave tras verificar la actual */
void cambiarClave(Usuario *u) {
    char actual[MAX_STR], nueva[MAX_STR], confirmar[MAX_STR];

    printf("Contrasena actual   : "); scanf("%49s", actual);
    if (strcmp(u->clave, actual) != 0) { printf("[!] Contrasena incorrecta.\n"); return; }

    printf("Nueva contrasena    : "); scanf("%49s", nueva);
    printf("Confirmar contrasena: "); scanf("%49s", confirmar);

    if (strcmp(nueva, confirmar) != 0) { printf("[!] Las contrasenas no coinciden.\n"); return; }

    strcpy(u->clave, nueva);
    printf("[OK] Contrasena actualizada correctamente.\n");
}

/* verHistorial: muestra todas las transacciones de la sesion */
void verHistorial(char hist[][MAX_STR], int cnt) {
    int i;
    printf("\n--- HISTORIAL DE TRANSACCIONES ---\n");
    if (cnt == 0) { printf("Sin transacciones registradas.\n"); return; }
    for (i = 0; i < cnt; i++)
        printf("%d. %s\n", i + 1, hist[i]);
    printf("----------------------------------\n");
}
