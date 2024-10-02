/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:40:54 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 22:29:56 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	clean_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->amount_of_spheres)
		if (data->spheres[i].texture)
			mlx_delete_texture(data->spheres[i].texture);
	i = -1;
	while (++i < data->amount_of_cones)
		if (data->cones[i].texture)
			mlx_delete_texture(data->cones[i].texture);
	i = -1;
	while (++i < data->amount_of_cylinders)
		if (data->cylinders[i].texture)
			mlx_delete_texture(data->cylinders[i].texture);
	i = -1;
	while (++i < data->amount_of_planes)
		if (data->planes[i].texture)
			mlx_delete_texture(data->planes[i].texture);
}

void	free_data_before_display(t_data *data)
{
	clean_textures(data);
	if (data->amount_of_spheres)
		free(data->spheres);
	if (data->amount_of_cones)
		free(data->cones);
	if (data->amount_of_planes)
		free(data->planes);
	if (data->amount_of_cylinders)
		free(data->cylinders);
	if (data->amount_of_lights)
		free(data->light);
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
