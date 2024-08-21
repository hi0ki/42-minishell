#include "minishell.h"

static char *generate_heredoc_name(void)
{
	static int i;
	char *num;
	char *name;

	i++;
	num = ft_itoa(i);
	name = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (name);
}

void heredoce_start(t_files *file, t_env **env)
{
	char *str;
	int fd;
	char *name;
	int pid;

	name = generate_heredoc_name();
	fd = open(name , O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file->fd == -1)
	{
		printf("exit f heredoc\n");
		perror(file->file_name);
		exit(g_status); // nzid return bach may endich l process
	}
	pid = fork();
	if (pid == 0)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		while (str != NULL && ft_strcmp(str, file->file_name) != 0)
		{
			write(fd, str, ft_strlen(str));
			free(str);
			write(1, "> ", 2);
			str = get_next_line(1);
		}
		free(str);
		close(fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
	}
	file->heredoce_name= ft_strdup(name);
	free(name);
}