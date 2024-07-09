# pipex

pipex is a project developed for 42 Heilbroon School.

## Keywords
C programming - bash - fork - processes - pipe - pipeline - redirection - file decriptors - here_doc

## Subject
The project is a reimplementation of the pipe using C programming language and its built in functions for forking new processes, crating pipe, redirecting input/output and handling file descriptors. The bonus part of the project handles a pipeline with multiple number of pipes, and the here doc redirection. For more info about the requirements, take a look at the [subject](en.subject.pdf) contained in this repo.

## Explanation
The project covers the following topics:


### 1. Input parsing
As the project subject specifies, the input has a specific format. What is taken by default by shell as...
```
> < infile cmd1 | cmd2 > outfile
```
...has to be taken by the `pipex` program in the following format:
```
> ./pipex infile "cmd1" "cmd2" outfile
```

### 2. Collecting data
During the validation process, the data is collected and stored into a so called `t_pipe` structure. The structure contain everything is needed to run the program, so that in case of failure, I can easly find the allocated memory and `free()` it properly. The parsing prepare also the data for the sub-processes.

### 3. Creating pipes
An important part which required some adjustment during the project, was the creation of pipe end using `pipe()` function. This creation is done before forking the new processe, so that every child knows which file descriptors are opened, and they can correctly handle the redirection.

### 4. Forking new processes
The parent has the job to `fork()` a number of process equal to the number of the commands which the user inputs. Every child process thas to handle its own redirection of input and output, close every file descriptor when not used and `execve()` the program. The parent has to `wait()`, close every file descriptor and return the right `exit_code`.

### 5. Error handling
Since `pipex` has to reimplement the shell pipe, the errors has to handled like it. To handle errors I use the `errno` pre-defined global variable, and I customize just a couple of error to be close to the shell behavior. Since the program doesn't handle signals (because the function to do it are not allowed by the subject), the exit codes are not always the same as the shell.

### 6. Leaks free
Like in any other project of 42, the memory allocated by `malloc()` has to be properly freed. No leaks are tolerated. For this project I used `valgrind` to check the memory. At the beginning of the project was vital to think about how to handle this feature so that no child process leaks the memory. That because, the `t_pipe` structure hold everything, and the parent process has the job to free the memory at the end of the programm.

## Bonus
The bonus part of the project ask to implement a multi-pipline and the here-doc functionality. Like the mandatory part, it takes a different input format from the original shell. What is taken by shell as...
```
> cmd1 << EOF | cmd1 >> outfile
```
...has to be taken by `pipex` as:
```
> ./pipex here_doc EOF "cmd1" "cmd2" outfile
```
here_doc is just a keyword used instead of `<<` identifier.

To implement the multi-pipe I find useful to identify what kind of child process the parent forks: the first child which take input from a file, the last child which outputs to the outfile, or a middle child between the first and the last, which take input from the previous one, and output to the next one.

About the `here_doc`, there are different ways to implement it. I choose to create a temporary file which is then destroyed when not more useful.

---

## Try it out
1. Clone the repository:
```
git clone https://github.com/ncasteln/42-pipex.git
```
2. Navigate to the `pipex` directory and `make` program, or `make bonus` for all the functionalities:
```
cd 42-pipex
make bonus
```
3. Execute it, passing a valid input as said in the explaination section of this document.

4. Enjoy!

---

## Notes
For both these two commands, a way to try them is modifying the code in the child processes, making one of them stuck in a `while()` loop, so that you can open a new terminal an run the command to send it the signal.
- `lsof -p [pid]` : with this command is possible to look which files are open in the process identified by  its `[pid]`. To retrieve the `[pid]` you can do that in C using `getpid()` or dirctly in the shell using `top` or `ps aux` commands.
- `kill -n [pid]` : send a signal to the process, which is also recognized by the parent through `WIFSIGNALED(wstatus)` and `WTERMSIG(wstatus)`.
- In case of creating a valid custom command in the same directory with the same name of an already built-in shell command, the shell would execute the custom one only if there is `./` to indicate to see in the current directory, otherwise it is searched in tha `$PATH` variable by default.
- The projct does't cover `awk` and `sed` commands.
- fork bomb: don't know what is? google it!
