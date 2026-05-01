/*
 * ============================================================
 *  CAJERO AUTOMATICO DIGITAL
 *  Simulacion de cajero con cuentas de usuarios predefinidas
 *  Lenguaje: C (C99)
 *
 *  MEJORAS IMPLEMENTADAS:
 *  1. Limite de intentos en inicio de sesion (max. 3)
 *     - Por que: Evita accesos no autorizados por fuerza bruta
 *     - Como:    Contador de intentos; bloqueo al llegar al limite
 *
 *  2. Historial de transacciones por sesion
 *     - Por que: El usuario puede revisar sus operaciones
 *     - Como:    Arreglo de strings que registra depositos y retiros
 *
 *  3. Cambio de contrasena
 *     - Por que: Buena practica de seguridad
 *     - Como:    Opcion en el menu que valida la clave actual
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

/* ── Constantes ─────────────────────────────────────── */
#define MAX_USUARIOS  5    /* Numero de usuarios registrados       */
#define MAX_STR       50   /* Longitud maxima de cadenas           */
#define MAX_INTENTOS  3    /* Intentos maximos de login            */
#define MAX_HISTORIAL 10   /* Maximo de transacciones por sesion   */

/* ── Estructura de usuario ──────────────────────────── */
typedef struct {
    char   nombre[MAX_STR];   /* Nombre de usuario para login  */
    char   clave[MAX_STR];    /* Contrasena de acceso          */
    double saldo;             /* Dinero disponible en la cuenta */
    char   titular[MAX_STR];  /* Nombre real del dueno         */
} Usuario;

/* ── Prototipos ─────────────────────────────────────── */
int  iniciarSesion(Usuario u[], int *idx);
void mostrarMenu(void);
void consultarSaldo(Usuario *u);
void depositar(Usuario *u, char hist[][MAX_STR], int *cnt);
void retirar(Usuario *u, char hist[][MAX_STR], int *cnt);
void cambiarClave(Usuario *u);
void verHistorial(char hist[][MAX_STR], int cnt);

/* ── Funcion principal ──────────────────────────────── */
int main(void) {

    /* Usuarios predefinidos con saldo inicial asignado */
    Usuario usuarios[MAX_USUARIOS] = {
        {"admin",  "1234",   5000.00, "Administrador"},
        {"jperez", "abcd",   1200.50, "Juan Perez"},
        {"mlopez", "pass1",  3400.75, "Maria Lopez"},
        {"cgomez", "qwerty",  800.00, "Carlos Gomez"},
        {"aruiz",  "9876",  15000.00, "Ana Ruiz"}
    };

    int  idx = -1;       /* Indice del usuario autenticado        */
    int  opcion = 0;     /* Opcion seleccionada en el menu        */
    int  cnt = 0;        /* Cantidad de transacciones registradas */
    char historial[MAX_HISTORIAL][MAX_STR];

    printf("====================================\n");
    printf("     CAJERO AUTOMATICO DIGITAL\n");
    printf("====================================\n\n");

    /* Autenticar al usuario antes de continuar */
    if (!iniciarSesion(usuarios, &idx)) {
        printf("[!] Acceso bloqueado. Demasiados intentos fallidos.\n");
        return 1;
    }

    printf("\nBienvenido/a, %s!\n", usuarios[idx].titular);

    /* Bucle principal: activo hasta que el usuario elija salir */
    do {
        mostrarMenu();
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: consultarSaldo(&usuarios[idx]);              break;
            case 2: depositar(&usuarios[idx], historial, &cnt);  break;
            case 3: retirar(&usuarios[idx], historial, &cnt);    break;
            case 4: cambiarClave(&usuarios[idx]);                break;
            case 5: verHistorial(historial, cnt);                break;
            case 6: printf("\nSesion cerrada. Hasta luego!\n\n"); break;
            default: printf("[!] Opcion invalida.\n");           break;
        }
    } while (opcion != 6);

    return 0;
}

/*
 * iniciarSesion
 * Solicita usuario y clave. Permite MAX_INTENTOS intentos fallidos.
 * Parametros: u[]  → arreglo de usuarios
 *             idx  → puntero donde se guarda el indice del usuario autenticado
 * Retorna: 1 si la autenticacion fue exitosa, 0 si se agotaron los intentos
 */
int iniciarSesion(Usuario u[], int *idx) {
    char nombre[MAX_STR], clave[MAX_STR];
    int  intentos = 0, i;

    while (intentos < MAX_INTENTOS) {
        printf("Usuario   : "); scanf("%49s", nombre);
        printf("Contrasena: "); scanf("%49s", clave);

        /* Buscar el usuario en el arreglo */
        for (i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(u[i].nombre, nombre) == 0 &&
                strcmp(u[i].clave, clave)   == 0) {
                *idx = i;
                return 1;   /* Autenticacion exitosa */
            }
        }

        intentos++;
        printf("[!] Credenciales incorrectas. Intentos restantes: %d\n\n",
               MAX_INTENTOS - intentos);
    }

    return 0;   /* Se agotaron los intentos */
}

/*
 * mostrarMenu
 * Imprime las opciones disponibles en pantalla.
 */
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

/*
 * consultarSaldo
 * Muestra el nombre del titular y el saldo disponible.
 * Parametros: u → puntero al usuario autenticado
 */
void consultarSaldo(Usuario *u) {
    printf("\nTitular: %s\n", u->titular);
    printf("Saldo  : $%.2f\n", u->saldo);
}

/*
 * depositar
 * Solicita un monto y lo agrega al saldo si es positivo.
 * Registra la operacion en el historial.
 * Parametros: u    → puntero al usuario
 *             hist → arreglo del historial
 *             cnt  → puntero al contador de transacciones
 */
void depositar(Usuario *u, char hist[][MAX_STR], int *cnt) {
    double monto;

    printf("Monto a depositar: $");
    scanf("%lf", &monto);

    if (monto <= 0) { printf("[!] El monto debe ser mayor a cero.\n"); return; }

    u->saldo += monto;
    printf("[OK] Deposito de $%.2f. Nuevo saldo: $%.2f\n", monto, u->saldo);

    /* Guardar en historial si hay espacio disponible */
    if (*cnt < MAX_HISTORIAL)
        sprintf(hist[(*cnt)++], "DEP +$%.2f | $%.2f", monto, u->saldo);
}

/*
 * retirar
 * Solicita un monto y lo descuenta si hay fondos suficientes.
 * Registra la operacion en el historial.
 * Parametros: u    → puntero al usuario
 *             hist → arreglo del historial
 *             cnt  → puntero al contador de transacciones
 */
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

/*
 * cambiarClave
 * Permite al usuario actualizar su contrasena verificando la actual.
 * Parametros: u → puntero al usuario autenticado
 */
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

/*
 * verHistorial
 * Muestra todas las transacciones realizadas en la sesion actual.
 * Parametros: hist → arreglo del historial
 *             cnt  → numero de transacciones guardadas
 */
void verHistorial(char hist[][MAX_STR], int cnt) {
    int i;
    printf("\n--- HISTORIAL DE TRANSACCIONES ---\n");
    if (cnt == 0) { printf("Sin transacciones registradas.\n"); return; }
    for (i = 0; i < cnt; i++)
        printf("%d. %s\n", i + 1, hist[i]);
    printf("----------------------------------\n");
}
