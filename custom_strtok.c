#include "main.h"
#include <stddef.h>
/**
* custom_strtok - a custom strtok function
* @string: the string to be tokenized
* @delimiter: the delimiter
* Return: tokenized string
*/
char *custom_strtok(char *string, const char *delimiter)
{
static char *the_final_token;
if (string == NULL)
{
string = the_final_token;
}
if (string == NULL || *string == '\0')
{
return (NULL);
}
string += strspn(string, delimiter);
if (*string == ';')
{
the_final_token = string;
return (the_final_token++);
}
the_final_token = string + strcspn(string, delimiter);
if (*the_final_token != '\0')
{
*the_final_token = '\0';
the_final_token++;
}
return (string);
}
