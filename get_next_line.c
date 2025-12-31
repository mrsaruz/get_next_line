/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:27:15 by adruz-to          #+#    #+#             */
/*   Updated: 2024/12/19 13:17:58 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*This function frees the memory of a given string (str) and returns NULL.
It is used to release memory when an error occurs or when the string is no
longer needed.*/

static char	*ft_free(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

/* This function reads data from the file descriptor (fd) into a buffer until
it finds a newline (\n) or reaches the end of the file. It then concatenates
the contents read so far into the backup string. If an error occurs during
reading, it frees the allocated memory and returns NULL.*/

static char	*read_until_newline(int fd, char *buffer, char *backup)
{
	int		bytes_read;
	char	*char_tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			buffer = ft_free(buffer);
			backup = ft_free(backup);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		char_tmp = backup;
		backup = ft_strjoin(backup, buffer);
		free(char_tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (backup);
}

/* This function extracts a single line from the backup string. It looks for
the newline character (\n) and copies all characters up to and including the
newline (if present) into a new string. If no newline is found, it copies all
characters from backup. It then returns this new line.*/

static char	*extract_line(char *backup)
{
	int		i;
	char	*line;
	char	*newline_pos;

	if (!*backup)
		return (NULL);
	newline_pos = ft_strchr(backup, '\n');
	if (newline_pos)
		i = newline_pos - backup;
	else
		i = ft_strlen(backup);
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_memcpy(line, backup, i);
	if (newline_pos)
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

/* This function updates the backup string by removing the part that was
already read (i.e., the line that has been extracted). It creates a new
backup string containing the remaining data after the newline, freeing
the old backup.*/

static char	*update_backup(char *backup)
{
	char	*new_backup;
	char	*newline_pos;
	int		i;

	newline_pos = ft_strchr(backup, '\n');
	if (!newline_pos)
	{
		free(backup);
		return (NULL);
	}
	i = newline_pos - backup + 1;
	new_backup = ft_strjoin("", backup + i);
	free(backup);
	return (new_backup);
}

/* This is the main function that returns one line from a file. It uses a
static backup variable to store the data between calls. It reads from the
file into a buffer, concatenates the data into backup, extracts a line using
extract_line, and then updates the backup to remove the extracted line. If any
step fails (e.g., memory allocation or reading), it returns NULL.*/

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	backup = read_until_newline(fd, buffer, backup);
	if (!backup)
		return (NULL);
	line = extract_line(backup);
	backup = update_backup(backup);
	return (line);
}
