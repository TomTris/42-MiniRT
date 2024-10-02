/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:40:40 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 23:16:32 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

int	get_first_arg(t_data *data, char **splited)
{
	int		res;
	int		sign;
	int		move;
	double	ratio;
	char	*numb;

	res = int_double_notvalid(splited[1], 0, 0);
	if (res == 2)
		return (display_error_message("`A` not valid 1st argument must be a \
		number in range [0.0,1.0]"), 0);
	move = 0;
	sign = get_sign(splited[1], &move);
	numb = (splited[1]) + move;
	if (sign == -1 || (res == 0 && str_len(numb) > 4) || \
	(res == 1 && get_pos_of_char(numb, '.') > 3))
		return (display_error_message("`A` not valid 1st argument must be a \
		number in range [0.0,1.0]"), 0);
	ratio = str_to_double(numb);
	if (ratio > 1.0 || ratio < 0.0)
		return (display_error_message("`A` not valid 1st argument must be a \
		number in range [0.0,1.0]"), 0);
	data->ambitient_light.ratio = ratio;
	return (1);
}

int	set_color_a(t_data *data, char *number, int ind)
{
	int		res;
	int		sign;
	int		move;
	int		color;
	char	*numb;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2 || res == 1)
		return (0);
	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	if (sign == -1)
		return (0);
	if (str_len(numb) > 10)
		return (0);
	color = str_to_long_long(numb);
	if (color < 0 || color > 255)
		return (0);
	data->ambitient_light.colors[ind] = color;
	return (1);
}

int	get_second_arg_a(t_data *data, char **splited)
{
	char	**numbers;
	int		ind;

	numbers = ft_split(splited[2], ',');
	if (!numbers)
		return (0);
	if (len2d_array(numbers) != 3)
		return (display_error_message("`A` not valid 2nd argument must be 3 \
		int separated by commas in range [0, 255]"), freeing(numbers), 0);
	ind = 0;
	while (ind < 3)
	{
		if (set_color_a(data, numbers[ind], ind) == 0)
			return (display_error_message("`A` not valid 2nd argument must be 3 \
			int separated by commas in range [0, 255]"), freeing(numbers), 0);
		ind++;
	}
	freeing(numbers);
	return (1);
}

int	parse_a(t_data *data, char **splited)
{
	if (data->seen_ambitient_light)
		return (display_error_message("`A` cant be defined twice"), 0);
	if (len2d_array(splited) != 3)
		return (display_error_message("`A` must have exact 2 args"), 0);
	if (!get_first_arg(data, splited))
		return (0);
	if (!get_second_arg_a(data, splited))
		return (0);
	data->seen_ambitient_light = 1;
	return (1);
}
