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
	int	id_1;

	if (pipe(pipe_end) == -1)
		return (ft_printf("pipe() failed"), 1);
	id_1 = fork();
	if (id_1 == -1)
		return (ft_printf("fork() failed"), 1);


	if (!id_1) // child
	{

	}
	else // parent
	{

	}
	return (0);
}

