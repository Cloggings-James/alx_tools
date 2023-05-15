#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - Find a program in the PATH.
 * @data: A pointer to the program's data.
 *
 * Return: 0 if success, error code otherwise.
 */
int find_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/* If it is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data); /* Search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{
		/* Append the command_name to each path directory */
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			/* The file was found, is not a directory, and has execute permissions */
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - Tokenize the PATH into directories.
 * @data: A pointer to the program's data.
 *
 * Return: Array of path directories.
 */
char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int num_directories = 2;
	char **directories = NULL;
	char *path;

	/* Get the PATH value */
	path = env_get_key("PATH", data);
	if (path == NULL || path[0] == '\0')
	{
		/* Path not found */
		return (NULL);
	}

	path = str_duplicate(path);

	/* Find the number of directories in the PATH */
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
			num_directories++;
	}

	/* Allocate space for the array of pointers */
	directories = malloc(sizeof(char *) * num_directories);

	/* Tokenize and duplicate each token of path */
	i = 0;
	directories[i] = str_duplicate(_strtok(path, ":"));
	while (directories[i++])
	{
		directories[i] = str_duplicate(_strtok(NULL, ":"));
	}

	free(path);
	path = NULL;
	return (directories);
}

/**
 * check_file - Check if a file exists, if it is not a directory, and
 * if it has execution permissions.
 * @full_path: Pointer to the full file name.
 *
 * Return: 0 on success, or error code if it doesn't exist.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(full_path, X

