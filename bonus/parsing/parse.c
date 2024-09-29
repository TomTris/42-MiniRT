/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:40:45 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 17:43:07 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	error_not_valid_identifier(char *str)
{
	write(2, "Error\n", 6);
	write(2, "invalid identifier ", 20);
	write(2, str, str_len(str));
	write(2, "\n", 1);
}

int	detect_type(t_data *data, char **splited)
{
	if (!str_compare(splited[0], "A"))
		return (parse_a(data, splited));
	else if (!str_compare(splited[0], "C"))
		return (parse_c(data, splited));
	else if (!str_compare(splited[0], "L"))
		return (parse_l(data, splited));
	else if (!str_compare(splited[0], "sp"))
		return (parse_sp(data, splited));
	else if (!str_compare(splited[0], "pl"))
		return (parse_pl(data, splited));
	else if (!str_compare(splited[0], "cy"))
		return (parse_cy(data, splited));
	else if (!str_compare(splited[0], "co"))
		return (parse_co(data, splited));
	else
		return (error_not_valid_identifier(splited[0]), 0);
}

int	parse_line(t_data *data, char *line)
{
	char	**splited;

	change_new_line(line);
	change_app(line, '#', 0);
	delete_useless_spaces(line);
	if (str_len(line) == 0)
		return (1);
	splited = ft_split(line, ' ');
	if (!splited)
		return (0);
	if (!detect_type(data, splited))
		return (freeing(splited), 0);
	freeing(splited);
	return (1);
}

int	parse(t_data *data)
{
	char	*line;
	int		finished;

	while (1)
	{
		finished = 0;
		line = get_next_line(data->fd, &finished);
		if (line == NULL && finished == 0)
			return (display_error_message("Memmory Allocation"), 0);
		if (!line)
			break ;
		if (!parse_line(data, line))
			return (free(line), 0);
		free(line);
		line = NULL;
	}
	if (!check_if_ok(data))
		return (0);
	// output_data(data);
	return (1);
}
