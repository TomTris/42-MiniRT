/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:04:54 by qdo               #+#    #+#             */
/*   Updated: 2024/09/27 23:55:57 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

t_point	crpoint(double x, double y, double z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_vec3	crvec3(double x, double y, double z)
{
	t_vec3	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_cone	crcone(t_point pA, t_point pO, t_vec3 vAO, double r)
{
	t_cone	cone;

	cone.pA = pA;
	cone.pO = pO;
	cone.vAO = vAO;
	cone.r = r;
	return (cone);
}

t_line	crline(t_vec3 vec, t_point p)
{
	t_line	line;

	line.direction_vector = vec;
	line.point = p;
	return (line);
}

void print_vector(t_vec3 vec)
{
	printf("%f, %f, %f\n", vec.x, vec.y, vec.z);
}

void print_point(t_point p)
{
	printf("%f, %f, %f\n", p.x, p.y, p.z);
}

int	main(void)
{
	t_line line = crline(crvec3(-4, 0, 1), crpoint(4, 0, 0));
	t_cone cone = crcone(crpoint(0, 0, 1), crpoint(0,0,0), crvec3(0,0,-1), 3.5);
	t_plain plain = plain_of_bottom_area(cone);
	
	t_point point_intersec = point_from_plain_and_line(plain, line);
	printf("%d\n", is_point_inside_bottom_area(cone, point_intersec));


}