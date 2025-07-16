# Manual de Usuario – Programa de Cifrado Multi-Algoritmo en C++

Este programa de consola permite cifrar y descifrar archivos de texto utilizando diferentes algoritmos clásicos de criptografía, así como un método adicional de cifrado irrompible. Es una herramienta desarrollada para propósitos educativos, con enfoque en demostrar las técnicas de cifrado simétrico, ataques de fuerza bruta y análisis de texto cifrado aprendidos en mi clase de criptografía impartida por el profesor Roberto Charretón Kaplun.

---

## Requisitos

* Compilador con soporte para C++17 o superior (g++, MSVC, Clang)
* Archivos de texto plano `.txt`
* Uso en entornos de consola (Windows/Linux/MacOS)

---

## Archivos de ejemplo

El repositorio incluye dos carpetas:

* `Datos crudos/`: Contiene archivos de texto plano listos para cifrar.
* `Datos cifrados/`: Almacena los archivos ya cifrados por el programa, separados por algoritmo si se desea.

---

## Instrucciones de uso

### Compilación

Usa tu compilador preferido para compilar el programa principal.

Ejemplo con g++:

```bash
g++ main.cpp -o Cifrador -std=c++17
```

Ejecuta el archivo resultante:

```bash
./Cifrador
```

---

## Menú principal

Al iniciar el programa, verás el siguiente menú:

```
========= MENU PRINCIPAL =========
1. Cifrado Irrompible (XOR y llave descartada)
2. Cifrado XOR (Reversible)
3. Cifrado César
4. Cifrado Vigenère
5. Cifrado DES
6. Salir
```

---

## Modo 1: Cifrado Irrompible

* Utiliza XOR con una clave aleatoria de 16 caracteres.
* La clave **no se almacena**, por lo tanto, el archivo cifrado **no puede descifrarse**.
* Este método está diseñado para ser teóricamente irrompible.

**Entrada solicitada:**

* Ruta del archivo original (puede usar uno de `Datos crudos/`)
* Nombre del archivo cifrado (se recomienda guardarlo en `Datos cifrados/`)

**Resultado esperado:**

* Archivo cifrado en formato hexadecimal.
* Mensaje de verificación de éxito.

---

## Modo 2: Cifrado XOR Reversible

* Utiliza el mismo algoritmo XOR, pero con una clave proporcionada por el usuario.
* Puede cifrarse y luego descifrarse con la misma clave.

**Entrada solicitada:**

* Ruta del archivo original o cifrado.
* Clave personalizada (texto alfanumérico).
* Archivo de salida.

---

## Modo 3: Cifrado César

* Desplaza letras y dígitos numéricos un número fijo de posiciones.

**Opciones disponibles:**

1. Cifrar con desplazamiento manual.
2. Descifrar con desplazamiento conocido.
3. Ataque de fuerza bruta (probar todos los desplazamientos posibles).
4. Estimar clave por frecuencia de letras.

---

## Modo 4: Cifrado Vigenère

* Cifra texto con una clave basada en una palabra.

**Entrada solicitada:**

* Clave (solo letras).
* Modo cifrado o descifrado.
* Permite romper el cifrado por fuerza bruta si no se conoce la clave, indicando longitud máxima.

---

## Modo 5: Cifrado DES (simplificado)

* Usa bloques de 8 bytes y claves de hasta 8 caracteres.
* Permite cifrar y descifrar con la misma clave.

**Importante:**

* El archivo debe tener una longitud múltiplo de 8 (el programa lo rellena si es necesario).
* La clave ingresada se transforma internamente en formato binario válido.

**Entrada solicitada:**

* Ruta del archivo.
* Clave de 1 a 8 caracteres.
* Archivo de salida.

---

## Salida y verificación

Después de cada operación válida, el programa mostrará un mensaje como el siguiente:

```
[✓] Operación completada con éxito.
[✓] Verificación: El contenido descifrado coincide con el original.
```

En caso de error (por ejemplo, archivo no encontrado, clave inválida), se mostrará un mensaje descriptivo sin cerrar el programa, permitiendo reintentar la operación.

---

## Consideraciones

* Las rutas pueden ser relativas (`./Datos crudos/archivo.txt`) o absolutas (`C:/Ruta/Completa/archivo.txt`).
* El sistema no sobrescribe archivos existentes, a menos que el usuario proporcione el mismo nombre de salida.
* El programa retorna al menú principal tras cada operación exitosa o fallida.

---

## Créditos

Autor: Iván Licea Godinez 
Co-Autor: Roberto Charreton Kaplun

---

