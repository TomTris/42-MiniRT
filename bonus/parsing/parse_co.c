/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_co.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:44:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/01 18:59:50 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	get_radius_co(char *number, t_cone *cone, int update)
{
	int		res;
	int		sign;
	int		move;
	double	pos;
	char	*numb;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (error_message_parse_co(update + 3), 0);
	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	pos = str_to_double(numb) * (double)sign;
	if (update == 0)
		cone->diameter = pos;
	else
		cone->height = pos;
	return (1);
}

void	helper_co(double *pos, char *number)
{
	int		sign;
	char	*numb;
	int		move;

	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	*pos = str_to_double(numb) * (double)sign;
}

int	set_pos_co(char *number, int ind, int update, t_cone *cone)
{
	int		res;
	double	pos;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (0);
	helper_co(&pos, number);
	if (update == 0)
		cone->cords[ind] = pos;
	else if (update == 1)
	{
		if (res == 1 || pos < 0 || pos > 255)
			return (0);
		cone->colors[ind] = pos;
	}
	else
	{
		if (pos < -1.0 || pos > 1.0)
			return (0);
		cone->vector[ind] = pos;
	}
	return (1);
}

int	get_first_arg_co(char *str, int update, t_cone *cone)
{
	char			**numbers;
	int				ind;

	numbers = ft_split(str, ',');
	if (!numbers)
		return (display_error_message("Memmory Allocation Error"), 0);
	if (update == 1 && len2d_array(numbers) == 1)
		return (open_texture(&cone->texture, numbers));
	if (!(len2d_array(numbers) == 3 || (update == 1 && \
		len2d_array(numbers) == 4 && !str_compare("1", numbers[3]))))
		return (error_message_parse_cy(update), freeing(numbers), 0);
	ind = 0;
	while (ind < 3)
	{
		if (set_pos_co(numbers[ind], ind, update, cone) == 0)
			return (error_message_parse_co(update), freeing(numbers), 0);
		ind++;
	}
	if (update == 1 && len2d_array(numbers) == 4)
		cone->checkers = 1;
	freeing(numbers);
	return (1);
}

int	parse_co(t_data *data, char **splited)
{
	t_cone	*cones;
	t_cone	*cone;

	cones = malloc(sizeof(t_cone) * (data->amount_of_cones + 1));
	if (!cones)
		return (display_error_message("Memmory Allocation Error"), 0);
	copy_all_stuff(cones, data->planes, sizeof(t_cone) * \
	data->amount_of_cones);
	cone = &(cones[data->amount_of_cones]);
	set_null(&cone->texture, &cone->checkers);
	if (len2d_array(splited) != 6)
		return (display_error_message("`co` must have 5 args"), 0);
	if (!get_first_arg_co(splited[1], 0, cone))
		return (0);
	if (!get_first_arg_co(splited[5], 1, cone))
		return (0);
	if (!get_first_arg_co(splited[2], 2, cone))
		return (0);
	if (!get_radius_co(splited[3], cone, 0))
		return (0);
	if (!get_radius_co(splited[4], cone, 1))
		return (0);
	if (++data->amount_of_cones && data->amount_of_cones != 1)
		free(data->cones);
	return (data->cones = cones, 1);
}
