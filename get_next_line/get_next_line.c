/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:00:13 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/01/26 21:48:16 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *save)
{
	char	*buffer;
	int		byte;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	byte = 1;
	while (byte != 0 && chr_n(save) == -1)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buffer); 
			buffer = NULL;
			free(save);
			save = NULL;
			return (buffer);
		}
		buffer[byte] = '\0';
		save = _strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*ft_line(char *save)
{
	char	*line;
	int		i;
	int		index;

	if (_strlen(save) == 0)
		return (NULL);
	index = chr_n(save);
	if (index == -1)
		return (_strdup(save));
	line = malloc(index + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (i < index)
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_save(char *save)
{
	char	*str;
	int		index;

	index = chr_n(save);
	if (index != -1)
	{
		str = _strdup(save + index + 1);
		free(save);
		return (str);
	}
	free(save);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (BUFFER_SIZE <= 0 || (fd <= 2 && fd == -1))
		return (NULL);
	save = ft_read(fd, save);
	if (!save)
	{
		free(save);
		return (NULL);
	}
	line = ft_line(save);
	save = ft_save(save);
	return (line);
}
