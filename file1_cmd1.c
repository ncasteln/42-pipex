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

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		return (ft_printf("open() failed"), 1);

	dup2(file, 0); // redirection
	// 0	stdin		--> 	file
	// 1	stdout		--> 	stdout
	// 2	sterr		--> 	stderr
	// 3	file		--> 	file
	close(file); // closes (3)

	if (execlp(argv[2], argv[2], NULL) == -1)
		return (ft_printf("execlp() failed"), 1);

	return (0);
}

