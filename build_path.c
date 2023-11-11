#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
* path_builder - a function to help in building the file path
* @dir: the directories
* @command: the command name
* Return: the file path of the directories
*/
char *path_builder(const char *dir, const char *command)
{
char *the_file_path = NULL;
size_t dir_length, cmd_len;
if (dir == NULL || command == NULL)
return (NULL);
dir_length = strlen(dir);
cmd_len = strlen(command);
the_file_path = (char *)malloc(dir_length + cmd_len + 2);
if (the_file_path == NULL)
{
fprintf(stderr, "Memory allocation failed\n");
return (NULL);
}
snprintf(the_file_path, dir_length + cmd_len + 2, "%s/%s", dir, command);
return (the_file_path);
}
