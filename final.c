#include "main.h"
#define COMMAND_MAX_LENGTH 1024
/**
* main - main shell program
* @ac: number of command line arguments
* @av: an array containing the program command line arguments
* Return: 0
*/
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
char *command = NULL, *sem_ptr, *cmd_ptr, *directory;
char **command_tokens;
size_t buffer_size = 0;
int i_mode = 1, status, line_nbr = 1;
char *program_name = av[0];
while (1)
{
i_mode = isatty(STDOUT_FILENO);
if (i_mode)
{
printf(" ");
}
if (getline(&command, &buffer_size, stdin) == -1)
{
free(command);
exit(EXIT_SUCCESS);
}
if (command[0] == '#')
{
continue;
}
if (handle_exit_command(command, &line_nbr, program_name))
{
free(command);
exit(status);
}
cmd_ptr = command;
while (*cmd_ptr != '\0')
{
sem_ptr = strchr(cmd_ptr, ';');
if (sem_ptr != NULL)
{
*sem_ptr = '\0';
}
command_tokens = tokenize_command(cmd_ptr);
if (command_tokens[0] != NULL)
{
handle_builtin_commands(command_tokens,
	program_name, &line_nbr);
}
free(command_tokens);
if (sem_ptr != NULL)
{
cmd_ptr = sem_ptr + 1;
}
else
{
break;
}
}
}
}
/**
* tokenize_command - function to tokenize commands
* @command: the command to be tokenized
* Return: fully and well tokenized commands
*/
char **tokenize_command(char *command)
{
char **command_tokens;
char *token;
int q = 0;
command_tokens = malloc(sizeof(char *) *
	       	COMMAND_MAX_LENGTH + 1);
if (command_tokens == NULL)
{
perror("malloc failed from tokenize_command");
exit(EXIT_FAILURE);
}
token = custom_strtok(command, " \n");
while (token != NULL)
{
if (token[0] == '#')
{
break;
}
command_tokens[q++] = token;
token = custom_strtok(NULL, " \n");
}
command_tokens[q] = NULL;
free(token);
return command_tokens;
}
/**
 * handle_exit_command - handles the "exit" command
 * @command: the command string
 * @line_nbr: pointer to the line number
 * @program_name: name of the program
 * Return: 1 if the command is "exit", 0 otherwise
 */
int handle_exit_command(char *command,
	       	int *line_nbr, char *program_name)
{
if (strcmp(command, "exit\n") == 0 ||
	     	strcmp(command, "exit 0\n") == 0)
{
free(command);
exit(EXIT_SUCCESS);
}
if (strncmp(command, "exit ", 5) == 0)
{
int status = atoi(command + 5);
if (status >= 0)
{
free(command);
exit(status);
}
else
{
fprintf(stderr, "%s: %d: exit: Illegal
	       	number: %d\n", program_name, *line_nbr, status);
free(command);
exit(2);
}
}
return 0;
}
/**
* handle_builtin_commands - handles built-in commands like "cd"
* @command_tokens: array of command tokens
* @program_name: name of the program
* @line_nbr: pointer to the line number
*/
void handle_builtin_commands(char **command_tokens, char *program_name, int *line_nbr)
{
char *directory;
if (strcmp(command_tokens[0], "cd") == 0)
{
directory = command_tokens[1];
if (directory == NULL || strcmp(directory, "-") == 0)
{
directory = getenv("HOME");
}
if (directory != NULL && chdir(directory) == 0)
{
setenv("PWD", directory, 1);
}
else
{
fprintf(stderr, "%s: %d: cd: %s: No such
	     	file or directory\n", program_name, *line_nbr, directory);
}
}
else
{
exec(command_tokens, program_name);
}
}
