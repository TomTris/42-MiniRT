/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:44:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/03 15:54:42 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

int	get_radius_cy(char *number, t_cylinder *cylinder, int update)
{
	int		res;
	int		sign;
	int		move;
	double	pos;
	char	*numb;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (error_message_parse_cy(update + 3), 0);
	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	pos = str_to_double(numb) * (double)sign;
	if (update == 0)
		cylinder->diameter = pos;
	else
		cylinder->height = pos;
	return (1);
}

void	helper_cy(double *pos, char *number)
{
	int		sign;
	char	*numb;
	int		move;

	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	*pos = str_to_double(numb) * (double)sign;
}

int	set_pos_cy(char *number, int ind, int update, t_cylinder *cylinder)
{
	int		res;
	double	pos;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (0);
	helper_cy(&pos, number);
	if (update == 0)
		cylinder->cords[ind] = pos;
	else if (update == 1)
	{
		if (res == 1 || pos < 0 || pos > 255)
			return (0);
		cylinder->colors[ind] = pos;
	}
	else
	{
		if (pos < -1.0 || pos > 1.0)
			return (0);
		cylinder->vector[ind] = pos;
	}
	return (1);
}

int	get_first_arg_cy(char *str, int update, t_cylinder *cylinder)
{
	char			**numbers;
	int				ind;

	numbers = ft_split(str, ',');
	if (!numbers)
		return (display_error_message("Memmory Allocation Error"), 0);
	if (update == 1 && len2d_array(numbers) == 1)
		return (open_texture(&cylinder->texture, numbers));
	if (!(len2d_array(numbers) == 3 || (update == 1 && \
		len2d_array(numbers) == 4 && !str_compare("1", numbers[3]))))
		return (error_message_parse_cy(update), freeing(numbers), 0);
	ind = 0;
	while (ind < 3)
	{
		if (set_pos_cy(numbers[ind], ind, update, cylinder) == 0)
			return (error_message_parse_cy(update), freeing(numbers), 0);
		ind++;
	}
	if (update == 1 && len2d_array(numbers) == 4)
		cylinder->checkers = 1;
	freeing(numbers);
	return (1);
}

int	parse_cy(t_data *data, char **splited)
{
	t_cylinder	*cylinders;
	t_cylinder	*cylinder;

	cylinders = malloc(sizeof(t_cylinder) * (data->amount_of_cylinders + 1));
	if (!cylinders)
		return (display_error_message("Memmory Allocation Error"), 0);
	copy_all_stuff(cylinders, data->cylinders, sizeof(t_cylinder) * \
	data->amount_of_cylinders);
	cylinder = &(cylinders[data->amount_of_cylinders]);
	set_null(&cylinder->texture, &cylinder->checkers);
	if (len2d_array(splited) != 6)
		return (display_error_message("`cy` must have 5 args"), free(cylinders), 0);
	if (!get_first_arg_cy(splited[1], 0, cylinder))
		return (free(cylinders), 0);
	if (!get_first_arg_cy(splited[5], 1, cylinder))
		return (free(cylinders), 0);
	if (!get_first_arg_cy(splited[2], 2, cylinder))
		return (free(cylinders), 0);
	if (!get_radius_cy(splited[3], cylinder, 0))
		return (free(cylinders), 0);
	if (!get_radius_cy(splited[4], cylinder, 1))
		return (free(cylinders), 0);
	if (++data->amount_of_cylinders && data->amount_of_cylinders != 1)
		free(data->cylinders);
	return (data->cylinders = cylinders, 1);
}
