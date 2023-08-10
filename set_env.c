#include <string.h>
#include <stdio.h>

int set_env(char **argv, char **envp)
{
	char *variable, *value, *current_env;
	int same, envp_pos, i, value_pos;

	if (argv[1] == NULL)
		return (-1);
	if (argv[2] == NULL)
		return (-1);

	variable = argv[1];
	value = argv[2];
	envp_pos = same = i = value_pos = 0;
	
	while (envp[envp_pos])
	{
		current_env = envp[envp_pos];

		for (i = 0; current_env[i] != '='; i++)
		{
			if (current_env[i] == variable[i])
			{
				same = 1;
				continue;
			}
			same = 0;
			break;
		}
		
		if (same == 1 && value != NULL)
		{
			for (i++, value_pos = 0; value[value_pos] != '\0'; i++, value_pos++)
				current_env[i] = value[value_pos];
			current_env[i] = '\0';
			return (2);
		}
		envp_pos++;
	}
	
	for (i = 0; current_env[i]; i++)
		current_env[i] = 0;

	for (i = 0; variable[i]; i++)
		current_env[i] = variable[i];
	if (value != NULL)
	{
		current_env[i] = '=';
		for (i++, value_pos = 0; value[value_pos]; i++, value_pos++)
			current_env[i] = value[value_pos];
		current_env[i] = '\0';
	}
	envp[envp_pos] = current_env;
	envp[envp_pos++] = NULL;
	return (1);
}

/*int main(int __attribute__((unused))ac, char **argv, char **env)
{
	
	int i = 0;

	set_env(argv, env);
	printf("_______________________________________________");
	printf("_______________________________________________");
	printf("_______________________________________________");
	while (env[i])
	{
		printf("env is %s\n", env[i]);
		i++;
	}
	return (0);
}*/
