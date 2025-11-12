/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:22:09 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/12 13:45:24 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	trim_trailing_spaces(char *str)
{
	int	end;

	end = ft_strlen(str);
	while (end > 0 && is_whitespace(str[end - 1]))
	{
		str[end - 1] = '\0';
		end--;
	}
}

void	display_errors(const char *error_msg)
{
	printf(RED "\nError\n \t=> %s \033[0m\n", error_msg);
}

/*
	1 - Extra spaces between key and path
	2 - If the line ends with spaces, remove them
*/
char	*extract_texture_path(char *line, int offset)
{
	char	*path;
	int		len;
	int		start;

	line += offset;
	start = 0;
	while (is_whitespace(line[start]))
		start++;
	line += start;
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	while (len > 0 && is_space(line[len - 1]))
		len--;
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	ft_memcpy(path, line, len);
	path[len] = '\0';
	return (path);
}

int	is_wall_or_space(char c)
{
	return (c == '1' || is_whitespace(c));
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == 0)
		return (1);
	return (0);
}
