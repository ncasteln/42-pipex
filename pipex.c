#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>


int main(int argc, char **argv)
{
	int	file;
	int	pipe_end[2];
	int	id;

	if (pipe(pipe_end) == -1)
		return (ft_printf("pipe() failed"), 1);
	id = fork();
	if (id == -1)
		return (ft_printf("fork() failed"), 1);


	if (!id) // child
	{
		// fd not needed
		close(pipe_end[0]);

		// open file to recieve an input
		file = open(argv[1], O_RDONLY);
		if (file == -1)
			return (ft_printf("open() failed"), 1);

		 // redirection the stdin & close (3)
		dup2(file, 0);
		close(file);
		// 0	stdin		--> 	file
		// 1	stdout		--> 	stdout
		// 2	sterr		--> 	stderr

		// redirection the stdout & close (pipe_end[1])
		dup2(pipe_end[1], 1);
		close(pipe_end[1]);
		// 0	stdin		--> 	file
		// 1	stdout		--> 	pipe_end[1]
		// 2	sterr		--> 	stderr

		if (execlp(argv[2], argv[2], NULL) == -1)
			return (ft_printf("execlp() failed"), 1);
	}
	else // parent
	{
		// fd not needed
		close(pipe_end[1]);

		// redirection stdin to have input from pipe_end[0] & close (pipe_end[0])
		dup2(pipe_end[0], 0);
		close(pipe_end[0]);
		// 0	stdin		--> 	pipe_fd[0]
		// 1	stdout		--> 	stdout
		// 2	sterr		--> 	stderr

		// open the file where to take the input
		int	write_file = open(argv[5], O_RDWR);
		if (write_file == -1)
			return (ft_printf("open() failed"), 1);

		dup2(write_file, 1);
		close(write_file);
		// 0	stdin		--> 	pipe_fd[0]
		// 1	stdout		--> 	write_file
		// 2	sterr		--> 	stderr

		if (execlp(argv[3], argv[3], argv[4], NULL) == -1)
			return (ft_printf("execlp() failed"), 1);
	}
	return (0);
}

