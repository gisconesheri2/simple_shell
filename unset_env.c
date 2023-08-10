#include <string.h>
#include <stdio.h>

int unset_env(char **argv, char **envp)
{
	char *variable, *current_env;
	int same, envp_pos, i;

	if (argv[1] == NULL)
		return (-1);

	variable = argv[1];
	envp_pos = same = i = 0;
	
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
		
		if (same == 1)
		{
			i = envp_pos + 1;
			while (envp[envp_pos])
			{
				envp[envp_pos] = envp[i];
				i++;
				envp_pos++;
			}
			return (2);
		}
		envp_pos++;
	}
	
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
