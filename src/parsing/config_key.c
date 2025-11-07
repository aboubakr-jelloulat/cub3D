/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:38:05 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/03 12:02:32 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*

printf("line : %s | Line len :  %zu |  matcher : %s  |  
matcher pattern_len : %d\n\n" , line, ft_strlen(line) , 
matcher->pattern, matcher->pattern_len);
*/

static int	check_pattern_match(char *line, t_key_matcher *matcher)
{
	return (ft_strncmp(line, matcher->pattern, matcher->pattern_len) == 0);
}

static int	init_matchers(t_key_matcher *matchers)
{
	matchers[0] = (t_key_matcher){"NO ", 3};
	matchers[1] = (t_key_matcher){"SO ", 3};
	matchers[2] = (t_key_matcher){"WE ", 3};
	matchers[3] = (t_key_matcher){"EA ", 3};
	matchers[4] = (t_key_matcher){"F ", 2};
	matchers[5] = (t_key_matcher){"C ", 2};
	return (6);
}

static bool	is_texture_or_color_key(char *str)
{
	t_key_matcher	matchers[6];
	int				count;
	int				idx;

	count = init_matchers(matchers);
	idx = 0;
	while (idx < count)
	{
		if (check_pattern_match(str, &matchers[idx]))
			return (true);
		idx++;
	}
	return (false);
}

/*
	CASE 1: ila kan file.cub kaybda b empty lines
	CASE 2 : line fih only spaces 
	CASE 3 : must be color or texture NO .. or F C
	CASE 4 : Invalid key not texture and no color  ZO  TO ..
	
*/

int	configuration_key(t_cub *cub, char *line, int i, int *success)
{
	if (line[0] == 0 || line[0] == '\n')
		return (true);
	if (line[i]  == 0)
		return (true);
	if (is_texture_or_color_key(line + i))
	{
		parse_all_wall_textures(cub, line, i, success);
		parse_colors(cub, line, i, success);
		return (true);
	}
	cub->list_status.invalid_key = true;
	return (false);
}
