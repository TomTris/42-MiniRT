/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:15:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	error_message_parse_cy(int update)
{
	if (update == 0)
		display_error_message("`cy` not valid 1st argument must be 3 \
		numbers separated by commas");
	else if (update == 1)
		display_error_message("`cy` not valid 5th argument must be 3 \
		integers separated by commas in range [0, 255]");
	else if (update == 2)
		display_error_message("`cy` not valid 2nd argument must be 3 \
		integers separated by commas in range [-1.0, 1.0]");
	else if (update == 3)
	{
		display_error_message("`cy` not valid 3rd argument must be  \
		a number");
	}
	else if (update == 4)
	{
		display_error_message("`cy` not valid 4th argument must be  \
		a number");
	}
}

void	error_message_parse_co(int update)
{
	if (update == 0)
		display_error_message("`co` not valid 1st argument must be 3 \
		numbers separated by commas");
	else if (update == 1)
		display_error_message("`co` not valid 5th argument must be 3 \
		integers separated by commas in range [0, 255]");
	else if (update == 2)
		display_error_message("`co` not valid 2nd argument must be 3 \
		integers separated by commas in range [-1.0, 1.0]");
	else if (update == 3)
	{
		display_error_message("`co` not valid 3rd argument must be  \
		a number");
	}
	else if (update == 4)
	{
		display_error_message("`co` not valid 4th argument must be  \
		a number");
	}
}

int	open_texture(mlx_texture_t **texture, char **path)
{
	*texture = mlx_load_png(path[0]);
	free(path[0]);
	free(path);
	if (!(*texture))
		return (display_error_message("Couldnt open texture"), 0);
	return (1);
}

void	set_null(mlx_texture_t **texture, int *checkers)
{
	*checkers = 0;
	*texture = NULL;
}
