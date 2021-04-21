# CI0117 - Actividad de clase 2
## Ejercicio 1
- Descargar, compilar y ejecutar el programa hello_iw_shr.c
- Discutir las siguientes preguntas y preparar una respuesta común
- ¿Qué ventaja tiene el uso de la estructura private_data_t en este programa respecto de haber creado un arreglo local de tamaño thread_count dentro de la subturina create_threads?
        ¿Qué ventaja o desventaja tiene el uso de la estructura shared_data_t en este programa respecto de haberla creado como una variable local de la subrutina create_threads o como una variable global del programa?
    Use las herramientas de chequeo dinámico y estático y advertir sobre problemas en el código.

## Ejercicio 2 [secret_message]

Suba la solucion a su repositorio personal de Github, siguiendo la siguiente estructura de folders:
```bash
/acividades/[número de actividad]/[nombre de ejercicio]/
```
Basándose en el programa hello_iw_shr.c, cree un programa en c que realice lo siguiente.

- Mantener la lógica para permitir al usuario indicar la cantidad de hilos y que el hilo principal pase información sobre el número total de hilos y el index de cada hilo.
- Todos los hilos deberán tener acceso a una estructura de datos compartida "message" el cual es un arreglo de caracteres de tamaño igual a la cantidad de hilos.
- Cada hilo deberá escribir un caracter en la posición correspondiente (por ej. el hilo 5 escribe en la posición message[5]). El caracter que cada hilo escribe se puede generar de forma aleatoria. Por ej.
```c
char generate_random_letter()
{
    return 'A' + (random() % 26);
}
```
- Cada hilo imprime un mensaje indicando su id y el caracter que está escribiendo.
- El hilo principal debe imprimir el mensaje final luego de que todos los hilos secundarios hayan escrito su mensaje.
