#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * _getenviron - gets the value of the environment variable passed in
 * @name_value: variable of environ to get path of
 * @env_var: the environment variable
 * @envp: pointer to the environment provided by main
 * Return: the value of env_var (what comes after the =)
 */

char *_getenviron(char *name_value, char *env_var, char **envp)
{
	char *name = env_var, *current_var;
	unsigned int i, j, k, value_present;
	char **environ = envp;

	i = j = k = value_present = 0;

	while (environ[i] != NULL)
	{
		current_var = environ[i];
		j = 0;
		while (name[j] != '\0')
		{
			if (name[j] == current_var[j])
			{
				value_present = 1;
				j++;
				continue;
			}
			else
			{
				value_present = 0;
				break;
			}
		}
		k = 0;
		j++;
		if (value_present == 1)
		{
			while (current_var[j] != '\0')
			{
				name_value[k] = current_var[j];
				j++;
				k++;
			}
			name_value[k] = '\0';
			return (name_value);
		}
		i++;
	}
	return (NULL);
}
