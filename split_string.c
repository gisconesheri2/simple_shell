#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * split_string - split a string from getline function into an array
 * to be passed on to the argv portion of execve
 * @argv: array of pointers to pass onto execve
 * @getline_string: string gotten from the stdin by getline function
 * Return: an array of string pointers
 */

char **split_string(char **argv, char *getline_string)
{
	char *program_name, *last_string;
	int len = 0, ls_len = 0;

	program_name = strtok(getline_string, " ");

	argv[0] = program_name;

	while (program_name != NULL)
	{
		len++;
		program_name = strtok(NULL, "  ");

		argv[len] = program_name;

		if (program_name == NULL)
		{
			last_string = argv[len - 1];
			ls_len = strlen(last_string);
			if (ls_len == 1 && last_string[0] == '\n')
				last_string = NULL;
			else
				last_string[ls_len - 1] = '\0';
			argv[len - 1] = last_string;
		}

	}

	return (argv);
}
