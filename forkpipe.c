#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <limits.h>
#include <fcntl.h>

#include <errno.h>
#include <strings.h>

// redirection
// int opened = open("./randw.txt", O_RDWR);

// if (opened < 0)
// 	return (perror("Error"), 1);
// int dup = dup2(opened, 1);
// if (dup < 0)
// 	return (perror("Error"), 1);

// ft_printf("Hello Nico");

// int readable = open("./read.txt", O_RDONLY);
// int writeable = open("./write.txt", O_WRONLY);

// dup2(writeable, 1);
// ft_printf("Hello Writable");

// implement <read.txt wc -c
int main(int argc, char **argv)
{
	int	fd[2];
	int	id;

	execlp("cat", "cat", "read.txt", NULL);
	// if (pipe(fd) == -1)
	// 	return (ft_printf("pipe()"), 1);
	// id = fork();
	// if (id == -1)
	// 	return (ft_printf("fork()"), 1);
	// if (!id)
	// {
	// }
	// else
	// {
	// 	int id_2 = fork();
	// 	if (!id_2)
	// 	{

	// 	}
	// 	else // parent
	// 	{

	// 	}
	// }
	// return (0);
}


// open read write read
// int main(int argc, char **argv)
// {
// 	int	fd[2];
// 	int	id;

// 	pipe(fd); // fd[0] read ~ fd[1] write
// 	id = fork();
// 	if (!id) // child writes to the pipe
// 	{
// 		close(fd[0]);
// 		int opened = open("./read.txt", O_RDONLY);
// 		char *cr = get_next_line(opened);
// 		write(fd[1], cr, ft_strlen(cr));
// 		close(fd[1]);
// 	}
// 	else // parent reads from the pipe
// 	{
// 		close(fd[1]);
// 		char *buff = malloc (sizeof(char) * 31);
// 		buff[30] = '\0';
// 		read(fd[0], buff, 30);
// 		close(fd[0]);
// 	}
// }



// accessibility
// int main(int argc, char **argv)
// {
// 	int accessible = access("./readable.txt", R_OK);
// 	ft_printf("%d\n", accessible);
// 	ft_printf("errno is [%d] which means [%s]\n", errno, strerror(errno));

// 	accessible = access("./notreadable.txt", R_OK);
// 	ft_printf("%d\n", accessible);
// 	ft_printf("errno is [%d] which means [%s]\n", errno, strerror(errno));
// }

// execv
// int main(int argc, char **argv)
// {
// 	pid_t	id;
// 	int		fd[2];

// 	if (pipe(fd))
// 		return (1);

// 	id = fork();
// 	if (id == -1)
// 		return (1);

// 	if (!id) // CHILD - writes
// 	{
// 		execve("/bin/ls", argv, NULL);
// 	}
// 	if (id) // PARENT - reads
// 	{
// 		waitpid(id, NULL, 0);
// 		ft_putstr_fd("*** finish ***", 1);
// 	}
// }

// // One process writes the other reads the first line
// int main(int argc, char **argv)
// {
// 	pid_t	id;
// 	int		fd[2];

// 	if (pipe(fd))
// 		return (1);

// 	id = fork();
// 	if (id == -1)
// 		return (1);

// 	if (id) // PARENT - reads
// 	if (!id) // CHILD - writes
// 	{
// 		close(fd[0]);
// 		ft_putendl_fd("Hello parent!", fd[1]);
// 		ft_putendl_fd("I'm writing the fd[1] for you!", fd[1]);
// 		ft_putendl_fd("Bye parent!", fd[1]);
// 		close(fd[1]);
// 	}
// 	{
// 		close(fd[1]);
// 		wait(NULL);
// 		ft_printf("gnl: %s", get_next_line(fd[0]));
// 		close(fd[0]);
// 	}

// 	return (0);
// }

// One process waiting for the other
// int main()
// {
// 	pid_t	id;

// 	id = fork();
// 	if (id == -1)
// 		return (perror(strerror(errno)), 1);

// 	int i = 0;
// 	if (id)
// 	{
// 		ft_printf("Parent: 'I wait you count until the max int possible...'\n");
// 		int child_id = wait(NULL);
// 		ft_printf("Parent: 'Id of the child was %d'\n", child_id);
// 		ft_printf("Parent: 'Thanks for counting!'\n");
// 	}
// 	if (!id)
// 	{
// 		ft_printf("Child: 'Ok, I start to count...'\n");
// 		ft_printf("*** Counting in process ***\n");
// 		while (i < INT_MAX)
// 			i++;
// 		ft_printf("Child: 'I Counted soooo much'\n");
// 	}

// 	return (0);
// }
