#include "main.h"
/**
* exec - function that executes a command
* @argv: an array containing the program command line arguments
* @program_name: the name of the program
*/
void exec(char **argv, char *program_name)
{
char *cmd = NULL, *true_cmd = NULL;
int line_num = 1;
int cs, the_pipefd[2];
pid_t pid;
char buffer[BUFSIZ];
if (argv == NULL || argv[0] == NULL)
{
fprintf(stderr, "%s: No command provided\n", program_name);
return;
}
cmd = argv[0];
if (strcmp(cmd, "env") == 0)
{
if (env_func() == -1)
{
fprintf(stderr, "Error executing env_func\n");
return;
}
return;
}
true_cmd = path_func(cmd);
if (true_cmd == NULL)
{
fprintf(stderr, "%s: %d: %s:not found
\n", program_name, line_num, argv[0]);
exit(EXIT_FAILURE);
}
pipe(the_pipefd);
pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
close(the_pipefd[0]);
dup2(the_pipefd[1], STDOUT_FILENO);
close(the_pipefd[1]);
if (execve(true_cmd, argv, environ) == -1)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else
{
close(the_pipefd[1]);
while ((cs = read(the_pipefd[0], buffer,
sizeof(buffer))) > 0)
{
write(STDOUT_FILENO, buffer, cs);
}
if (waitpid(pid, &cs, 0) == -1)
{
perror("waitpid");
exit(EXIT_FAILURE);
}
else if (WIFSIGNALED(cs))
{
exit(WEXITSTATUS(cs));
}
}
free(true_cmd);
}
