/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:55:57 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/18 17:02:10 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	check_all_vectors(t_data *data)
{
	(void)data;
	return (1);
}


int	check_if_ok(t_data *data)
{
	if (!data->seen_ambitient_light)
		return (display_error_message("Ambitient light is missing"), 0);
	if (!data->seen_camera)
		return (display_error_message("Camera is missing"), 0);
	if (!data->seen_light)
		return (display_error_message("Light is missing"), 0);
	if (!check_all_vectors(data))
		return (0);
	return (1);
}