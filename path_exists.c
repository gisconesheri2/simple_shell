#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * path_exists - builds and absolute path name and
 *  checks if the path for command is valid/exists
 * @abs_path: pointer to the absolute path
 * @path_value: the PATH value from envrion
 * @command: the command supplied by user
 * Return: the absolute file path containing the command
 * NULL if no path exists
 */

char *path_exists(char *abs_path, char *path_value, char *command)
{
	int i, j;
	char *current_file, *current_path;
	struct stat file_info;
	char *temp_path = NULL, *saveptr = NULL;

	i = j = 0;
	temp_path = path_value;
	if (temp_path == NULL)
		return (NULL);
	
/*get the first path in PATH out of the path string using strtok_r*/
	current_path = strtok_r(temp_path, ":", &saveptr);
	current_file = command;
	/*iterate thrhough all paths in the the PATH*/
	while (current_path != NULL)
	{
		for (i = 0; current_path[i] != '\0'; i++)
			abs_path[i] = current_path[i];

		if (abs_path[i - 1] == '/')
			i--;
		abs_path[i] = '/';

		/*add the argument supplied to the semi-finished path name*/
		for (j = 0, i++; current_file[j] != '\0'; i++, j++)
			abs_path[i] = current_file[j];

		abs_path[i] = '\0';

/*search if the full path name can be found in the system using STAT()*/
		if ((stat(abs_path, &file_info)) == 0)
			return (abs_path);
/*Move to the next path in PATH, strtok needs NULL pointer after first call*/
		current_path = strtok_r(NULL, ":", &saveptr);
	}

		abs_path = NULL;
		return (abs_path);
}
