# get_next_line

[English](#english) | [Español](#español)

---

## English

### Description

get_next_line is a 42 project that consists of creating a function that reads a line from a file descriptor. This project teaches you about static variables, file descriptors, dynamic memory allocation, and buffer management.

### Table of Contents

- [Function prototype](#function-prototype)
- [Mandatory requirements](#mandatory-requirements)
- [Implementation steps](#implementation-steps)
- [Compilation](#compilation)
- [Usage](#usage)
- [Testing](#testing)

### Function prototype

```c
char *get_next_line(int fd);
```

**Parameters:**
- `fd`: The file descriptor to read from

**Return value:**
- The line read from the file descriptor
- `NULL` if there's nothing more to read or if an error occurred

### Mandatory requirements

- Read from one or more file descriptors without losing the reading thread
- Return the line that has been read, including the terminating `\n` character (except at EOF)
- Return `NULL` when there's nothing more to read or if an error occurs
- Work correctly when reading from a file and when reading from standard input
- The returned line must be correctly terminated with `\0`
- Your function must work with any `BUFFER_SIZE` value

### Implementation steps

#### 1. Buffer initialization
- Check if the static buffer is empty
- If empty, allocate memory using `malloc`
- Handle any allocation errors properly
- If the buffer already contains data from a previous call, no need to reallocate

#### 2. File reading
- Use `read()` to read data from the file into the buffer
- Handle possible read errors (if `read` returns -1)
- Continue reading until a newline is found or EOF is reached

#### 3. Newline search
- Search for the newline character (`\n`) in the buffer
- If found, separate the complete line and adjust the buffer for the next call
- If not found, continue reading and concatenating data

#### 4. Line construction
- If no newline is found, keep reading and concatenating data
- Use a temporary variable (`tmp`) to store intermediate and concatenated data
- Continue until finding a newline or reaching EOF

#### 5. End of file handling
- When reaching EOF, return the last line read
- Ensure any allocated memory is freed
- Close the file if necessary

#### 6. Line return
- Return the complete line read from the file
- Ensure the memory allocated for the line is properly freed by the calling function

#### 7. Error handling
- Handle any errors that may occur during file reading or memory manipulation
- If an error occurs, return `NULL`
- Free all allocated memory before returning on error

#### 8. Helper functions
- Implement auxiliary functions for repetitive tasks:
  - Character searching
  - String concatenation
  - Memory management

### Compilation

```bash
# Compile with a specific BUFFER_SIZE
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test

# Common BUFFER_SIZE values for testing
gcc -D BUFFER_SIZE=1 ...    # Minimum buffer
gcc -D BUFFER_SIZE=42 ...   # Standard buffer
gcc -D BUFFER_SIZE=9999 ... # Large buffer
```

### Usage

#### Basic example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

#### Reading from stdin

```c
int main(void)
{
    char *line;
    
    while ((line = get_next_line(0)) != NULL)
    {
        printf("Read: %s", line);
        free(line);
    }
    
    return (0);
}
```

### Project structure

```
get_next_line/
├── get_next_line.h
├── get_next_line.c
├── get_next_line_utils.c
├── test.txt
├── main.c
└── README.md
```

### Testing

#### Test cases

1. **Small files**: Files with 1-3 lines
2. **Large files**: Files with thousands of lines
3. **Empty files**: Files with no content
4. **No newline at EOF**: Files that don't end with `\n`
5. **Only newlines**: Files containing only `\n` characters
6. **Large lines**: Lines with thousands of characters
7. **Multiple file descriptors**: Opening and reading from multiple files alternately

#### Memory leak testing

```bash
# Compile with debug flags
gcc -g -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Test with valgrind
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```

### Edge cases to consider

- Invalid file descriptor (`fd < 0`)
- `BUFFER_SIZE` <= 0
- `read()` error during execution
- Memory allocation failures
- Empty files
- Files without final newline
- Very large `BUFFER_SIZE` values
- Very small `BUFFER_SIZE` values (1)

### Norm

This project must comply with 42's Norminette:

- Maximum 25 lines per function
- Maximum 5 functions per file
- One static variable per function maximum
- Proper memory management
- No memory leaks

### Authorized functions

- `read`
- `malloc`
- `free`

### Tips

1. Start with a simple implementation before optimizing
2. Test with different `BUFFER_SIZE` values (1, 42, 9999)
3. Use static variables wisely to maintain state between calls
4. Always check memory allocation return values
5. Don't forget to free memory in all execution paths
6. Test with valgrind from the beginning
7. Draw diagrams to understand buffer manipulation
8. Test edge cases thoroughly

---

## Español

### Descripción

get_next_line es un proyecto de 42 que consiste en crear una función que lee una línea desde un file descriptor. Este proyecto te enseña sobre variables estáticas, file descriptors, asignación dinámica de memoria y gestión de buffers.

### Tabla de Contenidos

- [Prototipo de la función](#prototipo-de-la-función)
- [Requisitos obligatorios](#requisitos-obligatorios)
- [Pasos de implementación](#pasos-de-implementación)
- [Compilación](#compilación)
- [Uso](#uso)
- [Testing](#testing)

### Prototipo de la función

```c
char *get_next_line(int fd);
```

**Parámetros:**
- `fd`: El file descriptor desde el que leer

**Valor de retorno:**
- La línea leída del file descriptor
- `NULL` si no hay nada más que leer o si ocurrió un error

### Requisitos obligatorios

- Leer de uno o más file descriptors sin perder el hilo de lectura
- Devolver la línea que ha sido leída, incluyendo el carácter `\n` (excepto en EOF)
- Devolver `NULL` cuando no haya nada más que leer o si ocurre un error
- Funcionar correctamente tanto leyendo de un archivo como de la entrada estándar
- La línea devuelta debe estar correctamente terminada con `\0`
- Tu función debe funcionar con cualquier valor de `BUFFER_SIZE`

### Pasos de implementación

#### 1. Inicialización del buffer
- Verificar si el buffer estático está vacío
- Si está vacío, asignar memoria usando `malloc`
- Manejar cualquier error de asignación correctamente
- Si el buffer ya contiene datos de una llamada anterior, no es necesario reasignar

#### 2. Lectura del archivo
- Usar `read()` para leer datos del archivo y almacenarlos en el buffer
- Manejar los posibles errores de lectura (si `read` devuelve -1)
- Continuar leyendo hasta encontrar una nueva línea o llegar al final del archivo

#### 3. Búsqueda de nueva línea
- Buscar el carácter de nueva línea (`\n`) en el buffer
- Si se encuentra, separar la línea completa y ajustar el buffer para la siguiente llamada
- Si no se encuentra, continuar leyendo y concatenando datos

#### 4. Construcción de la línea
- Si no se encuentra nueva línea, seguir leyendo y concatenando datos
- Usar una variable temporal (`tmp`) para almacenar los datos intermedios y concatenados
- Continuar hasta encontrar una nueva línea o llegar al final del archivo

#### 5. Manejo del final del archivo
- Al llegar al final del archivo, devolver la última línea leída
- Asegurarse de liberar cualquier memoria asignada
- Cerrar el archivo si es necesario

#### 6. Retorno de la línea
- Devolver la línea completa leída del archivo
- Asegurarse de que la memoria asignada para la línea sea liberada correctamente por la función llamadora

#### 7. Manejo de errores
- Manejar cualquier error que pueda ocurrir durante la lectura del archivo o la manipulación de memoria
- Si ocurre un error, devolver `NULL`
- Liberar toda la memoria asignada antes de retornar en caso de error

#### 8. Funciones de ayuda
- Implementar funciones auxiliares para tareas repetitivas:
  - Búsqueda de caracteres
  - Concatenación de cadenas
  - Gestión de memoria

### Compilación

```bash
# Compilar con un BUFFER_SIZE específico
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test

# Valores comunes de BUFFER_SIZE para testing
gcc -D BUFFER_SIZE=1 ...    # Buffer mínimo
gcc -D BUFFER_SIZE=42 ...   # Buffer estándar
gcc -D BUFFER_SIZE=9999 ... # Buffer grande
```

### Uso

#### Ejemplo básico

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

#### Lectura desde stdin

```c
int main(void)
{
    char *line;
    
    while ((line = get_next_line(0)) != NULL)
    {
        printf("Leído: %s", line);
        free(line);
    }
    
    return (0);
}
```

### Estructura del proyecto

```
get_next_line/
├── get_next_line.h
├── get_next_line.c
├── get_next_line_utils.c
├── test.txt
├── main.c
└── README.md
```

### Testing

#### Casos de prueba

1. **Archivos pequeños**: Archivos con 1-3 líneas
2. **Archivos grandes**: Archivos con miles de líneas
3. **Archivos vacíos**: Archivos sin contenido
4. **Sin salto de línea al final**: Archivos que no terminan en `\n`
5. **Solo saltos de línea**: Archivos que contienen solo caracteres `\n`
6. **Líneas largas**: Líneas con miles de caracteres
7. **Múltiples file descriptors**: Abrir y leer de varios archivos alternadamente

#### Testing de memory leaks

```bash
# Compilar con flags de debug
gcc -g -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Testear con valgrind
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```

### Casos edge a considerar

- File descriptor inválido (`fd < 0`)
- `BUFFER_SIZE` <= 0
- Error de `read()` durante la ejecución
- Fallos en asignación de memoria
- Archivos vacíos
- Archivos sin salto de línea final
- Valores muy grandes de `BUFFER_SIZE`
- Valores muy pequeños de `BUFFER_SIZE` (1)

### Norma

Este proyecto debe cumplir con la Norminette de 42:

- Máximo 25 líneas por función
- Máximo 5 funciones por archivo
- Máximo una variable estática por función
- Gestión adecuada de memoria
- Sin leaks de memoria

### Funciones autorizadas

- `read`
- `malloc`
- `free`

### Consejos

1. Comienza con una implementación simple antes de optimizar
2. Prueba con diferentes valores de `BUFFER_SIZE` (1, 42, 9999)
3. Usa las variables estáticas para mantener el estado entre llamadas
4. Siempre verifica los valores de retorno de asignación de memoria
5. No olvides liberar memoria en todos los caminos de ejecución
6. Testea con valgrind desde el principio
7. Dibuja diagramas para entender la manipulación del buffer
8. Prueba exhaustivamente los casos edge

---

## Author / Autor

adruz-to - 42 Málaga

## License / Licencia

This project is part of the 42 curriculum. / Este proyecto es parte del curriculum de 42.
