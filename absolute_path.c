#include <stdio.h>
#include <string.h>
#include "simple_shell.h"
#include <stdlib.h>
/**
 * absolute_path - generates an absolute file path for command using
 * PATH variable
 * @argv: array of pointers that will be passed to execve
 * @envp: array of environment variables to be used by _getenviron
 * Return: the absolute filepath or NULL if not found
 */

char *absolute_path(char **argv, char **envp)
{
	char *supplied_name, *path_value, *abs_path;
	int i, j, z;
	char name_value[200];

	supplied_name = argv[0];

	abs_path = malloc(sizeof(char) * 200);

	if (supplied_name[0] == '/')
	{
		for (z = 0; supplied_name[z]; z++)
			abs_path[z] = supplied_name[z];

		argv[0] = abs_path;
		return (argv[0]);
	}
	if (abs_path == NULL)
	{
		argv[0] = NULL;
		return (argv[0]);
	}
	if (supplied_name[0] == '.')
	{
		i = j = 0;
		while (supplied_name[i] != '\0')
		{
			if (supplied_name[i] == '.' || supplied_name[i] == '/')
			{
				i++;
				continue;
			}
		supplied_name[j] = supplied_name[i];
		j++;
		i++;
		}
		supplied_name[j] = '\0';
		path_value = _getenviron(name_value, "PWD", envp);
		argv[0] = path_exists_pwd2(abs_path, path_value, supplied_name);
	}
	else
	{
		path_value = _getenviron(name_value, "PATH", envp);
		argv[0] = path_exists(abs_path, path_value, supplied_name);
	}
	if (argv[0] == NULL)
		free(abs_path);


	return (argv[0]);
}
