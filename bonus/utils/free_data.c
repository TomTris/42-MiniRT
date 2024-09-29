/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:40:54 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/19 13:54:54 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	free_data_before_display(t_data *data)
{
	if (data->amount_of_spheres)
		free(data->spheres);
	if (data->amount_of_cones)
		free(data->cones);
	if (data->amount_of_planes)
		free(data->planes);
	if (data->amount_of_cylinders)
		free(data->cylinders);
	if (data->fd != -1)
		close(data->fd);
}

void	freeing(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
