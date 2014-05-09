#include "pipex.h"

static void		pipex_left(char *cmd, int fd_in, int *pipefd)
{
	close(pipefd[0]);
	dup2(pipefd[1], 0);
	command_proc(cmd, fd_in, pipefd[1]);
	exit(EXIT_SUCCESS);
}

static void		pipex_right(char *cmd, int fd_out, int *pipefd)
{
	close(pipefd[1]);
	dup2(pipefd[2], 1);
	command_proc(cmd, pipefd[0], fd_out);
	exit(EXIT_SUCCESS);
}

void			pipex(char **av)
{
	int		fd[2];
	int		pipefd[2];
	pid_t	father1;
	pid_t	father2;

	fd = manage_fd(1, fd, av[0], av[3]);
	if (pipe(pipefd) == -1)
		ft_error("pipex: call system pipe error");
	if ((father1 = fork()) == -1)
		ft_error("pipex: call system fork error");
	if (father1 == 0)
		pipex_left(av[1], fd[0], pipefd);
	if ((father2 = fork()) == -1)
		ft_error("pipex: call system fork error");
	if (father2 == 0)
		pipex_right(av[2], fd[1], pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(father1, NULL, 0);
	waitpid(father2, NULL, 0);
	manage_fd(0, fd, av[0], av[3]);
}
