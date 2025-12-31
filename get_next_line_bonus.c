/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:57:26 by adruz-to          #+#    #+#             */
/*   Updated: 2024/12/19 13:17:43 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

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

char	*get_next_line(int fd)
{
	static char	*backups[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	backups[fd] = read_until_newline(fd, buffer, backups[fd]);
	if (!backups[fd])
		return (NULL);
	line = extract_line(backups[fd]);
	backups[fd] = update_backup(backups[fd]);
	return (line);
}
