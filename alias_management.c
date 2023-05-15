#include "shell.h"

/**
 * print_alias - add, remove, or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if success, or other number if it's declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
				&& data->alias_list[i][alias_length] == '='))
			{
				buffer[0] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i]);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - get the value of an alias
 * @data: struct for the program's data
 * @name: name of the requested alias
 * Return: value of the alias if found, NULL otherwise
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			return (data->alias_list[i] + alias_length + 1);
		}
	}

	return (NULL);
}

/**
 * set_alias - add or override an alias
 * @alias_string: alias to be set in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'\0'}, *temp = NULL;

	if (alias_string == NULL || data->alias_list == NULL)
		return (1);

	for (i = 0; alias_string[i] && alias_string[i] != '='; i++)
		buffer[i] = alias_string[i];

	for (j = 0; data->alias_list[j]; j++)
	{
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}
	}

	if (alias_string[i] == '=')
	{
		temp = get_alias(data, alias_string + i + 1);
		if (temp)
		{
			buffer_add(buffer, "=");
			buffer_add(buffer, temp);
			data->alias_list[j] = str_duplicate(buffer);
		}
		else
		{
			data->alias_list[j] = str_duplicate(alias_string);
		}
	}

	return (0);
}

