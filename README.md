# README - Programa de Cifrado de Archivos (Examen Parcial 2 | Cripto Analisis)

## Descripción

Este programa permite cifrar un archivo de texto usando un algoritmo XOR con una clave aleatoria generada internamente.
El archivo cifrado se guarda en formato hexadecimal. El proceso de descifrado se realiza internamente solo para verificar que el cifrado y descifrado sean correctos, **pero no se expone al usuario ni se guarda la clave**, por lo que el archivo cifrado no puede ser descifrado fuera del programa.

---

## Requisitos

* Windows, Linux o macOS con compilador C++ compatible (Visual Studio recomendado).
* El archivo a cifrar debe ser un archivo de texto (puede contener cualquier tipo de texto).
* El programa se ejecuta desde la consola o terminal.

---

## Uso

1. Ejecuta el programa.
2. El programa mostrará la ruta actual donde se está ejecutando (para tu referencia).
3. Se te pedirá que ingreses la ruta completa del archivo original que quieres cifrar.

   * Ejemplo: `C:\Users\TuUsuario\Documents\archivo.txt`
   * O solo el nombre del archivo si está en la carpeta de ejecución.
4. Se te pedirá que ingreses el nombre del archivo donde quieres guardar el archivo cifrado.

   * Ejemplo: `archivo_cifrado.txt`
   * Puedes incluir ruta completa si quieres guardarlo en otra carpeta.
5. El programa generará una clave secreta internamente (no visible ni guardada) y cifrará el contenido del archivo.
6. El archivo cifrado se guarda en el archivo que especificaste, en formato hexadecimal.
7. El programa realizará una verificación interna para asegurarse de que el cifrado y descifrado funcionaron correctamente.
8. Se mostrará un mensaje en pantalla indicando si la verificación fue exitosa:

   * `¡Éxito! El contenido coincide.`
   * O en caso de error: `Fallo: El contenido no coincide.`

---

## Importante

* No es posible descifrar el archivo cifrado con este programa ni con otro porque la clave **no se guarda ni se muestra en ningún lado**.
* Si pierdes la clave (que no puedes ver), no podrás recuperar el archivo original.
* Asegúrate de conservar el archivo original si necesitas consultarlo.
* El programa está diseñado para proteger la información de forma segura y evitar que otros puedan descifrar el archivo.

---

## Ejemplo de ejecución

```plaintext
Ruta de ejecución actual: C:\Users\TuUsuario\Documents

Ruta del archivo original a cifrar: datos_sensibles.txt
Nombre del archivo cifrado a guardar: datos_sensibles_cifrado.txt

Verificación: ¡Éxito! El contenido coincide.
```

---
