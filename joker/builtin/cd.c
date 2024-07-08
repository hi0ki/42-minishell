/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:16:22 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/08 12:49:58 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

typedef struct s_env{
	char			*bfr_eql;
	char			*after_eql;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

char	*ft_strjoin(char const *s1, const char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) +1);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

int	add_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	if (old_pwd = ft_strjoin("OLDPWD=", cwd))
		return (-1);
	
}

void	go_path(int opt, t_env *env)
{
	if (opt == 0)
	{
		add_oldpwd(env);
	}
}

void    ft_cd(char **av, t_env *env)
{

	if (!av[1])
		return (go_path(0, env));
}
