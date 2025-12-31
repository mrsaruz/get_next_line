#include "get_next_line.h"

#include <fcntl.h> // Abrir y manipular archivos como open()
#include <stdio.h> // Entrada y salida estándar, printf(), perror()
#include <stdlib.h> // Gestión de la memoria dinámica, malloc, free
#include <unistd.h> // read(), write(), close(), exit()

char	*get_next_line(int fd);

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: %s <filename>", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	printf("File opened successfully\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

/* int	main(int argc, char **argv)
{
	int		fd; //Descriptor de archivo
	char	*line; //Almacena la línea leída del archivo

	if (argc != 2) //Comprobar si el programa se ejecuta con el número correcto de argumentos
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY); // usamos open() para abrir el archivo, O_RDONLY de lectura
	if (fd == -1) 
	{
		perror("Error opening file");
		return (1);
	}
	printf("File opened successfully\n");
	line = get_next_line(fd);
	while (line != NULL) //usamos el bucle para leer las líneas hasta que devuelva NULL
	{
		if (line != NULL)
		{
			printf("Line in main: %s\n", line);
			free(line);
		}
		line = get_next_line(fd);
	}
	printf("Finished reading the file\n"); //imprime un mensaje de fin, cierra y retorna
	close(fd); //Cerramos el archivo
	return (0); //Salir con éxito
} */

// main for stdin

/* #include <fcntl.h> // Abrir y manipular archivos como open()
#include <stdio.h> // Entrada y salida estándar, printf(), perror()
#include <stdlib.h> // Gestión de la memoria dinámica, malloc, free
#include <unistd.h> // read(), write(), close(), exit()

char	*get_next_line(int fd);

int	main(void)
{
char	*line; //Almacena la línea leída del archivo
	line = get_next_line(0);
	while (line != NULL) //usamos el bucle para leer las líneas hasta que devuelva NULL
	{
		if (line != NULL)
		{
			printf("Line in main: %s\n", line);
			free(line);
		}
		line = get_next_line(0);
	}
	return (0); //Salir con éxito
}
 */