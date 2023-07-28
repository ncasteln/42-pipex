#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>


/* the work of child_1 is:
- take argv[1], which is a file, open it
- redirect stdin to argv[1]
- redirect stdout to pipe[1]
- execve argv[2]
*/
void	child_1(char **argv, int *pipe_fd)
{
	int	infile;

	close(pipe_fd[0]);
	infile = open(argv[1], O_RDONLY); // how set that also O_RDWR is also ok to use ???
	if (infile == -1)
		exit(1);

	if (dup2(infile, 0) == -1)
		exit(1);
	close(infile);

	if (dup2(pipe_fd[1], 1) == -1)
		exit(1);
	close(pipe_fd[1]);

	if (execlp(argv[2], argv[2], NULL) == -1)
		exit(1);
}


/* the work of child_2 is:
- use pipe[0] as an input (redirect 1)
- open a writable file (argv[4]) and use as output (redirect 2)
- execve argv[3]
*/
int	child_2(char **argv, int *pipe_fd)
{
	int	outfile;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0); // redirect (1)
	close(pipe_fd[0]);

	outfile = open(argv[4], O_RDWR);
	if (outfile == -1)
		return (1);
	if (dup2(outfile, 1) == -1) // redirect (2)
		return (1);

	if (execlp(argv[3], argv[3], "-1", NULL) == -1)
		return (1);
	return (0);
}


void	check_status(int status_code)
{

}


int main(int argc, char **argv)
{
	int	pipe_fd[2];
	int	id_1;
	int	id_2;
	int	*status;


	// validation of the arguments (ex. access())

	// pipe() and fork()
	if (pipe(pipe_fd) == -1)
		return (ft_printf("pipe() failed"), 1);
	id_1 = fork();
	if (id_1 == -1)
		return (ft_printf("fork() failed"), 1);


	if (!id_1) // child_1
		child_1(argv, pipe_fd);
	else
	{
		id_2 = fork();
		if (!id_2) // child_2
			child_2(argv, pipe_fd);
		else // parent
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			waitpid(id_1, status, 0);
			// check status
			waitpid(id_2, status, 0);
			// check status
		}
	}
	return (0);
}

