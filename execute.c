#include "shell.h"

/**
 * execute - Execute a command with its entire path variables.
 * @data: A pointer to the program's data.
 *
 * Return: If success returns zero, otherwise, return -1.
 */
int execute(data_of_program *data)
{
	int retval = 0, status;
	pid_t pid;

	retval = builtins_list(data);
	if (retval != -1)
		return retval;

	retval = find_program(data);
	if (retval)
		return retval;
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}

	return 0;
}

