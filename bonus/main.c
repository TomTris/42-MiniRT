/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:10 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 18:06:01 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

int	get_fd(char *path)
{
	int	fd;

	if (!ends_with(path, ".rt"))
	{
		write(2, "Error\nInputed file must end with .rt\n", 37);
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCouldn't open file\n", 26);
		return (-1);
	}
	return (fd);
}

void	init_data(t_data *data, int fd)
{
	data->fd = fd;
	data->amount_of_spheres = 0;
	data->amount_of_cones = 0;
	data->amount_of_cylinders = 0;
	data->amount_of_planes = 0;
	data->seen_light = 0;
	data->seen_ambitient_light = 0;
	data->seen_camera = 0;
	data->displayed = 0;
	data->amount_of_lights = 0;
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	srand(time(NULL));
	if (ac != 2)
	{
		write(2, "Error\nUsage: [executable] [path_to_scene]\n", 41);
		return (1);
	}
	fd = get_fd(av[1]);
	if (fd == -1)
		return (1);
	init_data(&data, fd);
	if (!parse(&data))
		return (free_data_before_display(&data), 1);
	display(&data);
	free_data_before_display(&data);
	return (0);
}
