/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:00:32 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/01/25 16:47:17 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	*_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*s;

	i = 0;
	dest = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	return (dst);
}

char	*_strjoin(char *s1, char *s2)
{
	char	*str;
	int		dlen;
	int		slen;

	if (!s2)
		return (NULL);
	dlen = _strlen(s1);
	slen = _strlen(s2);
	str = malloc((dlen + slen + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	_memcpy(str, s1, dlen);
	_memcpy(str + dlen, s2, slen);
	str[dlen + slen] = '\0';
	free(s1);
	return (str);
}

char	*_strdup(char *s1)
{
	char	*str;

	str = malloc(_strlen(s1) + 1 * sizeof(char));
	if (!str)
		return (NULL);
	_memcpy(str, s1, _strlen(s1));
	str[_strlen(s1)] = '\0';
	return (str);
}

int	chr_n(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
