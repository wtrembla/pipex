#include "pipex.h"

static int	*open_files(char *infile, char *outfile)
{
	int		fd[2];

	if ((fd[0] = open(tmp1, O_RDONLY)) == -1)
	{
		ft_putjoin_fd("open_files: open error ", infile, 2);
		ft_strdel(&infile);
		ft_strdel(&outfile);
		ft_error(NULL);
	}
	if ((fd[1] = open(tmp2, OWRONLY | O_CREAT, S_IRWXU
						| S_IRWXG | S_IRWXO)) == -1)
	{
		ft_strdel(&infile);
		ft_strdel(&outfile);
		ft_putjoin_fd("open_files: open error ", outfile, 2);
		if (close(fd[0]) == -1)
			ft_putjoin_fd("open_files: close error ", infile, 2);
		ft_strdel(&outfile);
		ft_strdel(&infile);
		ft_error(NULL);
	}
	return (fd);
}

static void	*close_files(int *fd, char *infile, char *outfile)
{
	if (close(fd[0]) == -1)
	{
		ft_putendl_fd("close_files: close error ", infile);
		if (close(fd[1]) == -1)
			ft_putendl_fd("close_files: close error ", outfile);
		ft_strdel(&infile);
		ft_strdel(&outfile);
		ft_error(NULL);
	}
	if (close(fd[1]) == -1)
	{
		ft_putendl_fd("close_files: close error ", outfile);
		ft_strdel(&infile);
		ft_strdel(&outfile);
		ft_error(NULL);
	}
}

int			*manage_fd(int status, int *fd, char *infile, char *outfile)
{
	char	*tmp1;
	char	*tmp2;

	fd[0] = 0;
	fd[1] = 0;
	tmp1 = ft_strtrim(infile);
	tmp2 = ft_strtrim(outfile);
	if (status == 1)
		fd = open_files(tmp1, tmp2);
	else if (status == 0)
		close_files(fd, tmp1, tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (fd);
}
