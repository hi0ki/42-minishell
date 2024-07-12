/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:13:19 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/12 13:16:20 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

typedef struct s_env{
	char			*bfr_eql;
	char			*after_eql;
	struct s_env	*next;
}	t_env;

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putstrn_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int ft_env(t_env *env)
{
    // red lbal wach atbghi tb9a mpointer 3la neud lkhra wela bghiti twssel tal NULL ...hna rak drbty NULL
    while (env)
    {
        ft_putstr_fd(env->bfr_eql, 1);
        write(1, "=", 1);
        ft_putstrn_fd(env->after_eql, 1);
        env = env->next;
    }
    return (0);
}