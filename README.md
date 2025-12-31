Pasos a seguir para la implementación de get_next_line:

1. Inicialización del buffer: verificar si está vacío. Si está vacío tengo
que asignar memoria para el buffer. Usar malloc para asignar memoria y manejar
cualquier error de asignación. Si el buffer ya contiene datos de una llamada
anterior, no es necesario volver a asignar memoria

2. Lectura del archivo: usar read para leer datos del archivo y almacenarlos en
el buffer. Hay que manejar los posibles errores de lectura (si read 
devuelve -1). Continúa leyendo hasta que encuentres una nueva línea o se llegue
al final del archivo

3. Busqueda de nueva línea: buscar el carácter de nueva línea (\n) en el buffer.
Si se encuentra, se separa la línea completa y ajusta el buffer para la
siguiente llamada. Si no encuentra nueva línea, continúa leyendo y concatenando
los datos

4. Contrucción de la línea: si no encuentra la nueva línea, sigue leyendo y 
concatenando los datos hasta encontrarla o hasta llegar al final del archivo. 
Usando la variable temporal (tmp) para almacenar los datos intermedios y 
concatenados

5. Manejo del final del archivo: al llegar al final, devuelve la última línea 
leída. Asegurarse de liberar cualquier memoria asignada y cerrar el archivo si
es necesario

6. Retorno de la línea: devuelve la línea completa leída del archivo y hay que
asegurarse de que la memoria asignada para la línea sea liberada correctamente
por la llamada a la función 

7. Manejo de errores: manejar cualquier error que pueda ocurrir durante la
lectura del archivo o la manipulación de la memoria. Si ocurre un error, 
devuelve NULL

8. Funciones de ayuda: implementar funciones auxiliares para manejar tareas
repetitivas, como la búsqueda de caracteres, la concatenación de cadenas y la 
gestión de memoria 