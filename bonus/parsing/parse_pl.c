/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:44:00 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/01 18:59:37 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	error_message_parse_pl(int update)
{
	if (update == 0)
	{
		display_error_message("`pl` not valid 1st argument must be 3 \
		numbers separated by commas");
	}
	else if (update == 1)
	{
		display_error_message("`pl` not valid 3rd argument must be 3 (checker)\
		integers separated by commas in range [0, 255]");
	}
	else if (update == 2)
	{
		display_error_message("`pl` not valid 2nd argument must be 3 \
		integers separated by commas in range [-1.0, 1.0]");
	}
}

void	helper_pl(double *pos, char *number)
{
	int		sign;
	char	*numb;
	int		move;

	move = 0;
	sign = get_sign(number, &move);
	numb = number + move;
	*pos = str_to_double(numb) * (double)sign;
}

int	set_pos_pl(char *number, int ind, int update, t_plane *plane)
{
	int		res;
	double	pos;

	res = int_double_notvalid(number, 0, 0);
	if (res == 2)
		return (0);
	helper_pl(&pos, number);
	if (update == 0)
		plane->cords[ind] = pos;
	else if (update == 1)
	{
		if (res == 1 || pos < 0 || pos > 255)
			return (0);
		plane->colors[ind] = pos;
	}
	else
	{
		if (pos < -1.0 || pos > 1.0)
			return (0);
		plane->vector[ind] = pos;
	}
	return (1);
}

int	get_first_arg_pl(char *str, int update, t_plane *plane)
{
	char			**numbers;
	int				ind;

	numbers = ft_split(str, ',');
	if (!numbers)
		return (display_error_message("Memmory Allocation Error"), 0);
	if (update == 1 && len2d_array(numbers) == 1)
		return (open_texture(&plane->texture, numbers));
	if (!(len2d_array(numbers) == 3 || (update == 1 && \
	len2d_array(numbers) == 4 && !str_compare("1", numbers[3]))))
		return (error_message_parse_pl(update), freeing(numbers), 0);
	ind = 0;
	while (ind < 3)
	{
		if (set_pos_pl(numbers[ind], ind, update, plane) == 0)
			return (error_message_parse_pl(update), freeing(numbers), 0);
		ind++;
	}
	if (update == 1 && len2d_array(numbers) == 4)
		plane->checkers = 1;
	freeing(numbers);
	return (1);
}

int	parse_pl(t_data *data, char **splited)
{
	t_plane	*planes;

	planes = malloc(sizeof(t_plane) * (data->amount_of_planes + 1));
	if (!planes)
		return (display_error_message("Memmory Allocation Error"), 0);
	copy_all_stuff(planes, data->planes, sizeof(t_plane) * \
	data->amount_of_planes);
	planes[data->amount_of_planes].checkers = 0;
	planes[data->amount_of_planes].texture = NULL;
	if (len2d_array(splited) != 4)
		return (display_error_message("`pl` must have 3 args"), 0);
	if (!get_first_arg_pl(splited[1], 0, &(planes[data->amount_of_planes])))
		return (0);
	if (!get_first_arg_pl(splited[3], 1, &(planes[data->amount_of_planes])))
		return (0);
	if (!get_first_arg_pl(splited[2], 2, &(planes[data->amount_of_planes])))
		return (0);
	data->amount_of_planes += 1;
	if (data->amount_of_planes != 1)
		free(data->planes);
	data->planes = planes;
	return (1);
}
