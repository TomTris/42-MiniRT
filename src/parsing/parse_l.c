/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:44:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/19 13:54:28 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	error_message_parse_l(int update)
{
	if (update == 0)
	{
		display_error_message("`L` not valid 1st argument must be 3 \
		numbers separated by commas");
	}
	else if (update == 0)
	{
		display_error_message("`L` not valid 3rd argument must be 3 \
		integers separated by commas in range [0, 255]");
	}
	else
	{
		display_error_message("`L` not valid 2nd argument must be a \
		number");
	}
}

int	set_pos_l(t_data *data, char *number, int ind, int update)
{
	int		res;
	int		sign;
	int		move;
	double	pos;
	char	*numb;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (0);
	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	pos = str_to_double(numb) * (double)sign;
	if (update == 0)
		data->light.cords[ind] = pos;
	else
	{
		if (res == 1 || pos < 0 || pos > 255)
			return (0);
		data->light.colors[ind] = pos;
	}
	return (1);
}

int	get_first_arg_l(t_data *data, char *str, int update)
{
	char	**numbers;
	int		ind;

	numbers = ft_split(str, ',');
	if (!numbers)
		return (display_error_message("Memmory Allocation Error"), 0);
	if (len2d_array(numbers) != 3)
		return (error_message_parse_l(update), freeing(numbers), 0);
	ind = 0;
	while (ind < 3)
	{
		if (set_pos_l(data, numbers[ind], ind, update) == 0)
			return (error_message_parse_l(update), freeing(numbers), 0);
		ind++;
	}
	freeing(numbers);
	return (1);
}

int	get_ratio(t_data *data, char *number)
{
	int		res;
	int		sign;
	int		move;
	double	pos;
	char	*numb;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (display_error_message("`C` not valid 2nd argument must be a \
		number in range [0.0, 1.0]"), 0);
	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	pos = str_to_double(numb) * (double)sign;
	if (pos > 1.0 || pos < 0.0)
		return (display_error_message("`C` not valid 2nd argument must be a \
		number in range [0.0, 1.0]"), 0);
	data->light.ratio = pos;
	return (1);
}

int	parse_l(t_data *data, char **splited)
{
	if (data->seen_light)
		return (display_error_message("`L` cant be defined twice"), 0);
	if (len2d_array(splited) != 4)
		return (display_error_message("`L` must have 3 args"), 0);
	if (!get_first_arg_l(data, splited[1], 0))
		return (0);
	if (!get_first_arg_l(data, splited[3], 1))
		return (0);
	if (!get_ratio(data, splited[2]))
		return (0);
	data->seen_light = 1;
	return (1);
}
