#include "shell.h"

/**
 * _strtok - separates strings with delimiters
 * @line: pointer to array we receive in getline
 * @delim: characters we use to split the string
 *
 * Return: pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;

	for (; *str != '\0'; str++)
	{
		if (_strchr(delim, *str) == NULL)
			break;
	}

	copystr = str;

	if (*copystr == '\0')
		return (NULL);

	for (; *str != '\0'; str++)
	{
		if (_strchr(delim, *str) != NULL)
		{
			*str = '\0';
			str++;
			return (copystr);
		}
	}

	return (copystr);
}

/**
 * tokenize - splits a string into tokens using a delimiter
 * @data: a pointer to the program's data
 *
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int i, counter = 2, length;

	length = str_length(data->input_line);

	if (length > 0 && data->input_line[length - 1] == '\n')
		data->input_line[length - 1] = '\0';

	for (i = 0; data->input_line[i] != '\0'; i++)
	{
		if (_strchr(delimiter, data->input_line[i]) != NULL)
			counter++;
	}

	data->tokens = malloc(counter * sizeof(char *));

	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}

	i = 0;
	data->tokens[i] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);

	while (data->tokens[i] != NULL)
	{
		i++;
		data->tokens[i] = str_duplicate(_strtok(NULL, delimiter));
	}
}

