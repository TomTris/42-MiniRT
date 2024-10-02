/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:40:40 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:58 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	error_message_parse_c(int update)
{
	if (update == 0)
	{
		display_error_message("`C` not valid 1st argument must be 3 \
		numbers separated by commas");
	}
	else
	{
		display_error_message("`C` not valid 2nd argument must be 3 \
		numbers separated by commas in range [-1.0, 1.0]");
	}
}

int	get_fov(t_data *data, char *str)
{
	int		res;
	int		sign;
	int		move;
	int		fov;
	char	*numb;

	res = int_double_notvalid(str, 0, 0);
	if (res == 2 || res == 1)
		return (display_error_message("`C` not valid 3rd argument must be an \
		integer in range [0, 180]"), 0);
	move = 0;
	sign = get_sign(str, &move);
	numb = str + move;
	if (sign == -1 || (res == 0 && str_len(numb) > 4))
		return (display_error_message("`C` not valid 3rd argument must be an \
		integer in range [0, 180]"), 0);
	fov = str_to_long_long(numb);
	if (fov <= 0 || fov > 180)
		return (display_error_message("`C` not valid 3rd argument must be an \
		integer in range [0, 180]"), 0);
	data->camera.fov = (double)fov / 180.0 * M_PI;
	return (1);
}

int	set_pos_c(t_data *data, char *number, int ind, int update)
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
		data->camera.cords[ind] = pos;
	else
	{
		if (pos > 1.0 || pos < -1.0)
			return (0);
		data->camera.vector[ind] = pos;
	}
	return (1);
}

int	get_first_arg_c(t_data *data, char *str, int update)
{
	char	**numbers;
	int		ind;

	numbers = ft_split(str, ',');
	if (!numbers)
		return (display_error_message("Memmory Allocation Error"), 0);
	if (len2d_array(numbers) != 3)
		return (error_message_parse_c(update), freeing(numbers), 0);
	ind = 0;
	while (ind < 3)
	{
		if (set_pos_c(data, numbers[ind], ind, update) == 0)
			return (error_message_parse_c(update), freeing(numbers), 0);
		ind++;
	}
	freeing(numbers);
	return (1);
}

int	parse_c(t_data *data, char **splited)
{
	if (data->seen_camera)
		return (display_error_message("`C` cant be defined twice"), 0);
	if (len2d_array(splited) != 4)
		return (display_error_message("`C` must have 3 args"), 0);
	if (!get_first_arg_c(data, splited[1], 0))
		return (0);
	if (!get_first_arg_c(data, splited[2], 1))
		return (0);
	if (!get_fov(data, splited[3]))
		return (0);
	data->seen_camera = 1;
	return (1);
}
