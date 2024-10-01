/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone_1_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:07:29 by qdo               #+#    #+#             */
/*   Updated: 2024/09/30 20:43:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_points	intersection2_2(double t, double delta, t_line *line,
	t_cal_helper *h)
{
	t_points	ret;

	ret.amount = 1;
	ret.t1 = t;
	ret.p1.x = line->p.x + line->dv.x * t;
	ret.p1.y = line->p.y + line->dv.y * t;
	ret.p1.z = line->p.z + line->dv.z * t;
	t = (-h->b - sqrt(delta)) / (2 * h->a);
	if (t > 0)
	{
		ret.amount = 2;
		ret.t2 = t;
		ret.p2.x = line->p.x + line->dv.x * t;
		ret.p2.y = line->p.y + line->dv.y * t;
		ret.p2.z = line->p.z + line->dv.z * t;
	}
	return (ret);
}

t_points	intersection2(double delta, t_line *line, t_cal_helper *h)
{
	t_points	ret;
	double		t;

	ret.amount = 0;
	t = (-h->b + sqrt(delta)) / (2 * h->a);
	if (t > 0)
	{
		ret = intersection2_2(t, delta, line, h);
		return (ret);
	}
	t = (-h->b - sqrt(delta)) / (2 * h->a);
	if (t > 0)
	{
		ret.amount = 1;
		ret.t1 = t;
		ret.p1.x = line->p.x + line->dv.x * t;
		ret.p1.y = line->p.y + line->dv.y * t;
		ret.p1.z = line->p.z + line->dv.z * t;
		return (ret);
	}
	return (ret);
}

t_points	intersection1(t_line *line, t_cal_helper *h)
{
	t_points	ret;
	double		t;

	ret.amount = 0;
	t = (-h->b) / (2 * h->a);
	if (t > 0)
	{
		ret.amount = 1;
		ret.t1 = t;
		ret.p1.x = line->p.x + line->dv.x * t;
		ret.p1.y = line->p.y + line->dv.y * t;
		ret.p1.z = line->p.z + line->dv.z * t;
		return (ret);
	}
	return (ret);
}

//https://lousodrome.
//net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
double	cal_stuff(t_cal_helper *h, t_line *line, t_cone *cone)
{
	h->d_v = dot_vec(line->dv, cone->vao);
	h->co = vector_p1_to_p2(cone->pa, line->p);
	h->co_v = dot_vec(h->co, cone->vao);
	h->d_co = dot_vec(line->dv, h->co);
	h->a = pow(h->d_v, 2) - pow(cone->cos_al, 2);
	h->b = 2 * (h->d_v * h->co_v - h->d_co * pow(cone->cos_al, 2));
	h->c = pow(h->co_v, 2) - dot_vec(h->co, h->co) * pow(cone->cos_al, 2);
	return (pow(h->b, 2) - (4 * h->a * h->c));
}

t_points	intersection(t_line *line, t_cone *cone)
{
	t_cal_helper	h;
	double			delta;
	t_points		ret;

	delta = cal_stuff(&h, line, cone);
	if (delta < 0)
		return (ret.amount = 0, ret);
	if (delta == 0)
		return (intersection1(line, &h));
	return (intersection2(delta, line, &h));
}
