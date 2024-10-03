/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:44:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/03 15:42:24 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	error_message_parse_sp(int update)
{
	if (update == 0)
	{
		display_error_message("`sp` not valid 1st argument must be 3 \
		numbers separated by commas");
	}
	else if (update == 1)
	{
		display_error_message("`sp` not valid 3rd argument must be 3 (checker) \
		integers separated by commas in range [0, 255]");
	}
	else
	{
		display_error_message("`sp` not valid 2nd argument must \
		be a number");
	}
}

int	set_pos_sp(char *number, int ind, int update, t_sphere *sphere)
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
		sphere->cords[ind] = pos;
	else
	{
		if (res == 1 || pos < 0 || pos > 255)
			return (0);
		sphere->colors[ind] = pos;
	}
	return (1);
}

int	get_first_arg_sp(char *str, int update, t_sphere *sphere)
{
	char			**numbers;
	int				ind;

	numbers = ft_split(str, ',');
	if (!numbers)
		return (display_error_message("Memmory Allocation Error"), 0);
	if (update == 1 && len2d_array(numbers) == 1)
		return (open_texture(&sphere->texture, numbers));
	if (!(len2d_array(numbers) == 3 || (update == 1 && \
	len2d_array(numbers) == 4 && !str_compare("1", numbers[3]))))
		return (error_message_parse_sp(update), freeing(numbers), 0);
	ind = 0;
	while (ind < 3)
	{
		if (set_pos_sp(numbers[ind], ind, update, sphere) == 0)
			return (error_message_parse_sp(update), freeing(numbers), 0);
		ind++;
	}
	if (update == 1 && len2d_array(numbers) == 4)
		sphere->checkers = 1;
	freeing(numbers);
	return (1);
}

int	get_radius_sp(char *number, t_sphere *sphere)
{
	int		res;
	int		sign;
	int		move;
	double	pos;
	char	*numb;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (error_message_parse_sp(2), 0);
	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	pos = str_to_double(numb) * (double)sign;
	sphere->diameter = pos;
	return (1);
}

int	parse_sp(t_data *data, char **splited)
{
	t_sphere	*spheres;

	spheres = malloc(sizeof(t_sphere) * (data->amount_of_spheres + 1));
	if (!spheres)
		return (display_error_message("Memmory Allocation Error"), 0);
	copy_all_stuff(spheres, data->spheres, sizeof(t_sphere) * \
	data->amount_of_spheres);
	spheres[data->amount_of_spheres].checkers = 0;
	spheres[data->amount_of_spheres].texture = NULL;
	if (len2d_array(splited) != 4)
		return (display_error_message("`sp` must have 3 args"), free(spheres), 0);
	if (!get_first_arg_sp(splited[1], 0, &(spheres[data->amount_of_spheres])))
		return (free(spheres), 0);
	if (!get_first_arg_sp(splited[3], 1, &(spheres[data->amount_of_spheres])))
		return (free(spheres), 0);
	if (!get_radius_sp(splited[2], &(spheres[data->amount_of_spheres])))
		return (free(spheres), 0);
	data->amount_of_spheres += 1;
	if (data->amount_of_spheres != 1)
		free(data->spheres);
	data->spheres = spheres;
	return (1);
}
