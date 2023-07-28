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
	int	id;
	int	wait_status;
	int	status_code;

	id = fork();
	if (!id) // child
	{
		// what happens here:
		// 0	stdin		--> 	stdin
		// 1	stdout		--> 	randw.txt
		// 2	sterr		--> 	stderr
		// 3	randw.txt	--> 	randw.txt
		int opened = open("./randw.txt", O_RDWR);
		int redirected = dup2(opened, 1); // from now, the things printed to 1 are printed into the file

		ft_printf("This stuff will be printed into the file.\n[opened] is [%d]\n", opened);
		close(opened);
		ft_printf("Also these.\n[opened] is [%d]\n", redirected);

		if (execlp("cat", "cat", "read.txt", NULL) == -1)
			return (ft_printf("execlp() failed"), 1);
	}
	else // parent
	{
		waitpid(id, &wait_status, 0);
		if (WIFEXITED(wait_status))
		{
			status_code = WEXITSTATUS(wait_status);
			if (!status_code)
				ft_printf("*** Everything fine ***\n");
			else
				return (ft_printf("*** The program executed made errors ***\n"), 1);
		}
		ft_printf("*** Parent waited for child ***\n");
	}
	return (0);
}

