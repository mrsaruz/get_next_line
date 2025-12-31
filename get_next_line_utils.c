/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:27:38 by adruz-to          #+#    #+#             */
/*   Updated: 2024/12/18 11:38:42 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* This function calculates the length of a string of characters. It takes a
pointer to char and uses a loop to count characters until it finds the null
character. It returns the total number of characters counted, representing
the length of the string.*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/* This function concatenates two strings, s1 and s2, into a new dynamically
allocated string. First, it checks that both strings are not NULL, then
allocates memory, copies s1, appends s2 to the end, and ends with a null
character. It returns the concatenated string, assuming ft_strlen is correctly
implemented.*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
/* This function searches for the first occurrence of a character in a string.
If it finds the character, it returns a pointer to its position; if it does
not, it returns NULL. It also handles the null character case correctly,
returning a pointer to the end of the string if that character is 
searched for.*/

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}
/* This function copies a block of memory from one location to another.
It takes three parameters: the destination pointer (dest), the source 
pointer (src), and the number of bytes to copy (n). Its goal is to transfer
data from src to dest byte by byte. At the end, it returns the pointer to the
destination, allowing it to be used in other operations. However, it does not
handle situations where memory blocks overlap; for that, memmove is
recommended.*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
