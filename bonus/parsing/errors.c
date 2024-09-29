/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:15:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/18 16:26:06 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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
