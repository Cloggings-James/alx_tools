#include "shell.h"

/**
 * builtin_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int builtin_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
	{
		print_environ(data);
	}
	else
	{
		char *var_copy = NULL;
		char cpname[50] = {'\0'};
		int i;

		for (i = 0; data->tokens[1][i] && data->tokens[1][i] != '='; i++)
			cpname[i] = data->tokens[1][i];

		if (data->tokens[1][i] == '=')
		{
			var_copy = env_get_key(cpname, data);
			env_set_key(cpname, data->tokens[1] + i + 1, data);
			print_environ(data);
			if (var_copy == NULL)
				_print(data->tokens[1]);
			else
				env_set_key(cpname, var_copy, data);
		}
		else
		{
			errno = 2;
			perror(data->command_name);
			errno = 127;
		}
	}

	return (0);
}

/**
 * builtin_set_env - sets the value of an environment variable
 * @data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL || data->tokens[3] != NULL)
	{
		errno = (data->tokens[3] != NULL) ? E2BIG : EINVAL;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - unsets an environment variable
 * @data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] != NULL)
	{
		errno = (data->tokens[2] != NULL) ? E2BIG : EINVAL;
		perror(data->command_name);
		return (5);
	}

	env_remove_key(data->tokens[1], data);

	return (0);
}

