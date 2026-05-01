#  Cajero Automático Digital

Simulación de un cajero automático en lenguaje C. Permite a usuarios predefinidos autenticarse y realizar operaciones básicas sobre su cuenta.

# Funcionalidades

- Inicio de sesión con validación de usuario y contraseña
- Bloqueo tras 3 intentos fallidos de login
- Consultar saldo disponible
- Depositar dinero (validando monto positivo)
- Retirar dinero (validando fondos suficientes)
- Cambiar contraseña (verificando la clave actual)
- Ver historial de transacciones de la sesión

# Usuarios de prueba

| Usuario  | Contraseña | Titular           | Saldo        |
|----------|------------|-------------------|--------------|
| admin    | 1234       | Administrador     | $5,000.00    |
| jperez   | abcd       | Juan Perez        | $1,200.50    |
| mlopez   | pass1      | Maria Lopez       | $3,400.75    |
| cgomez   | qwerty     | Carlos Gomez      | $800.00      |
| aruiz    | 9876       | Ana Ruiz          | $15,000.00   |

---

# Compilar y ejecutar

Requiere cualquier compilador de C (gcc, clang, etc.).

```bash
# Compilar
gcc -o cajero cajero.c

# Ejecutar
./cajero          # Linux / Mac
cajero.exe        # Windows
```

---

## Mejoras implementadas

### 1. Límite de intentos de login
**Qué se agregó:** Máximo de 3 intentos antes de bloquear el acceso.  
**Por qué:** Evita accesos no autorizados por prueba y error de contraseñas.  
**Cómo funciona:** Un contador se incrementa en cada fallo; al llegar a 3, `iniciarSesion` retorna 0 y el programa termina.

### 2. Historial de transacciones
**Qué se agregó:** Registro de todos los depósitos y retiros realizados en la sesión.  
**Por qué:** El usuario puede revisar qué operaciones hizo durante su sesión.  
**Cómo funciona:** Un arreglo de strings guarda cada transacción; la opción 5 del menú lo muestra.

### 3. Cambio de contraseña
**Qué se agregó:** Opción en el menú para actualizar la contraseña.  
**Por qué:** Buena práctica de seguridad que permite al usuario mantener sus credenciales actualizadas.  
**Cómo funciona:** Verifica la clave actual, solicita la nueva dos veces y la guarda si ambas coinciden.
