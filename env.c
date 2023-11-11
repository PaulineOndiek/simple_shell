#include "main.h"
#include <stdio.h>
/**
* env_func - function to display environment
*/
void env_func(void)
{
char **env = environ;
while (*env)
{
puts(*env);
env++;
}
}
