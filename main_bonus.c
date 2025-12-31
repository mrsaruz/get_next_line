#include "get_next_line_bonus.h"
#include <fcntl.h>  // Abrir y manipular archivos como open()
#include <stdio.h>  // Entrada y salida estándar, printf(), perror()
#include <stdlib.h> // Gestión de la memoria dinámica, malloc, free
#include <unistd.h> // read(), write(), close(), exit()

char	*get_next_line(int fd);

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("text1.txt", O_RDONLY);
	if (fd1 == -1)
	{
		perror("Error abriendo text1.txt");
		close(fd1);
		return (1);
	}
	fd2 = open("text2.txt", O_RDONLY);
	if (fd2 == -1)
	{
		perror("Error abriendo text2.txt");
		close(fd2);
		return (1);
	}
	fd3 = open("1char.txt", O_RDONLY);
	if (fd3 == -1)
	{
		perror("Error abriendo 1char.txt");
		close(fd3);
		return (1);
	}
	 // Bucle que lee todas las líneas de los tres archivos
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("fd[1] line [%d]: %s", i, line);
			free(line);
		}
		else
			line = NULL;

		line = get_next_line(fd2);
		if (line)
		{
			printf("fd[2] line [%d]: %s", i, line);
			free(line);
		}
		else
			line = NULL;

		line = get_next_line(fd3);
		if (line)
		{
			printf("fd[3] line [%d]: %s", i, line);
			free(line);
		}
		else
			line = NULL;

		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
