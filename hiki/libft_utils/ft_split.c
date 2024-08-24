/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:48:05 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/21 21:48:09 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	c_word(char const *s, char *c)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (s[i] == c[j] && s[i])
				break ;
			j++;
		}
		if (c[j] == '\0')
		{
			cnt++;
			while (s[i] && !ft_strchr(c, s[i]))
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

static char	**ft_free(char **str, int i)
{
	while (i > 0)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return (NULL);
}

static char	**ft_alloc(char *s, char *c, int c_word, char **str)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < c_word)
	{
		while (ft_strchr(c, s[start]) && s[start])
			start++;
		end = start;
		while (!ft_strchr(c, s[end]) && s[end])
			end++;
		str[i] = ft_substr(s, start, end - start);
		if (!str[i])
			return (ft_free(str, i));
		start = end;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char *s, char *c)
{
	char	**str;
	int		len_w;

	if (!s)
		return (NULL);
	len_w = c_word(s, c);
	str = (char **)malloc(sizeof(char *) * (len_w + 1));
	if (!str)
		return (NULL);
	str = ft_alloc((char *)s, c, len_w, str);
	return (str);
}
