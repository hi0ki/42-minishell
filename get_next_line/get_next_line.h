/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:00:20 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/01/24 17:45:43 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_save(char *save);
char	*ft_line(char *save);
char	*ft_read(int fd, char *save);
int		_strlen(char *str);
void	*_memcpy(void *dst, const void *src, size_t n);
char	*_strjoin(char *s1, char *s2);
char	*_strdup(char *s1);
int		chr_n(char *str);

#endif
