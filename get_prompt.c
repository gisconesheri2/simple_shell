#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include "simple_shell.h"

/**
 * is_exit - checks if input entered is the string 'exit'
 * @argv_0: first argument for char **argv
 * Return: 1 if argv_0 is 'exit', o otherwise
 */
int is_built_in_command(char *built_in_command, char *argv_0)
{
	char *bic = built_in_command;
	int same = 0, i;

	for (i = 0; bic[i] != '\0'; i++)
	{
		if (bic[i] == argv_0[i])
		{
			same = 1;
			continue;
		}
		same = 0;
		break;
	}
	return (same);
}
/**
 * main - starts up the simple shell program
 * @ac: number of argumens supplied to main
 * @main_argv: array of strings passed to main
 * @envp: pointer to array of environment variables
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */

int main(__attribute__((unused))int ac, char **main_argv, char **envp)
{
	char *command = NULL;
	size_t len = 10;
	ssize_t nlen = 0;
	int wstatus, exit_status, malloc_called;
	pid_t child_process;
	char *argv[20];
	exit_status = 0, malloc_called = 1;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 10);
	while ((nlen = getline(&command, &len, stdin)) != -1)
	{
		/*if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 10);*/
		split_string(argv, command);
		if (argv[0] == NULL)
			continue;

		if (is_built_in_command("exit", argv[0]) == 1)
		{
			if (argv[1] != NULL)
			{
				exit_status = atoi(argv[1]);
				if (exit_status <= 0)
				{
					dprintf(2, "%s: 1: %s: Illegal number: %s\n", main_argv[0], argv[0], argv[1]);
					exit_status = 2;
				}
			}
			free(argv[0]);
			exit(exit_status);
		}

		if (is_built_in_command("env", argv[0]) == 1)
		{
			malloc_called = 0;
			argv[0] = "/usr/bin/env";
		}
		/*else if (is_built_in_command("setenv", argv[0]) == 1)
		{
			set_env(argv, envp);
			continue;
		}
		else if (is_built_in_command("unsetenv", argv[0]) == 1)
		{
			unset_env(argv, envp);
			continue;
		}*/
		else
			absolute_path(argv, envp);

		if (argv[0] != NULL)
		{
			child_process = fork();
			if (child_process == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (child_process == 0)
			{
				if ((execve(argv[0], argv, envp)) == -1)
					perror(main_argv[0]);
			}
			else
			{
				wait(&wstatus);
				if (WIFEXITED(wstatus))
					exit_status = WEXITSTATUS(wstatus);
			}
		}
		else
		{
			dprintf(2, "%s: 1: %s: not found\n", main_argv[0], command);
			exit_status = 127;
		}
		if (malloc_called)
			free(argv[0]);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 10);
	}
	free(command);
	exit(exit_status);
}
