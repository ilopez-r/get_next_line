/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:36:30 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/10/25 12:03:35 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(int fd, char *buffer)
{
	char	*buffer_aux;
	int		i;

	buffer_aux = ft_calloc ((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer_aux)
		return (free (buffer), buffer = NULL, NULL);
	i = 1;
	while (i > 0 && !ft_strchr (buffer_aux, '\n'))
	{
		i = read(fd, buffer_aux, BUFFER_SIZE);
		if (i < 0)
			return (free (buffer), buffer = NULL, free (buffer_aux),
				buffer_aux = NULL, NULL);
		buffer_aux[i] = '\0';
		buffer = ft_strjoin(buffer, buffer_aux);
		if (!buffer)
			return (free (buffer), buffer = NULL, free (buffer_aux),
				buffer_aux = NULL, NULL);
	}
	return (free (buffer_aux), buffer_aux = NULL, buffer);
}

char	*get_line_f(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_calloc ((i + 1 + (buffer[i] == '\n')), sizeof(char));
	if (!line)
		return (NULL);
	if (buffer[i] != '\0')
		line[i + 1] = '\0';
	while (i >= 0)
	{
		line[i] = buffer[i];
		i--;
	}
	return (line);
}

char	*get_rest(char *buffer)
{
	char	*rest_line;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (free (buffer), buffer = NULL, NULL);
	len = ft_strlen(buffer);
	rest_line = ft_calloc (((len - i) + 1), sizeof(char));
	if (!rest_line)
		return (free (buffer), buffer = NULL, NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
	{
		rest_line[j] = buffer[i];
		i++;
		j++;
	}
	rest_line[j] = buffer[i];
	return (free (buffer), buffer = NULL, rest_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
	{
		if (buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = read_fd(fd, buffer);
	if (!buffer)
		return (free (buffer), buffer = NULL, NULL);
	line = get_line_f(buffer);
	if (!line)
		return (free (buffer), buffer = NULL, NULL);
	buffer = get_rest(buffer);
	if (!buffer)
		return (free (buffer), buffer = NULL, line);
	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>
int	main()
{
	int fd = open("test", O_RDONLY);
	char *line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		line = get_next_line(fd);
	}
}*/
