/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:50:56 by qdo               #+#    #+#             */
/*   Updated: 2024/09/30 20:08:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

double dot_vec(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	vector_p1_to_p2(t_vec3 point1, t_vec3 point2)
{
	t_vec3	vec;

	vec.x = point2.x - point1.x;
	vec.y = point2.y - point1.y;
	vec.z = point2.z - point1.z;
	return (vec);
}

double	cal_distance(t_vec3 p1, t_vec3 p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) \
		+ pow(p1.y - p2.y, 2) \
		+ pow(p1.z - p2.z, 2)));
}

typedef struct s_cal_helper
{
	double	cone_AO;
	double	cos_alpha;
	double	dv;
	t_vec3	co;
	double	cov;
	double	dco;
	double	a;
	double	b;
	double	c;
} t_cal_helper;

//https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
void	cal_stuff(t_cal_helper *h, t_line *line, t_cone *cone)
{
	h->cone_AO = cal_distance(cone->pA, cone->pO);
	h->cos_alpha = h->cone_AO / sqrt(pow(h->cone_AO, 2) + pow(cone->r, 2));
	h->dv = dot_vec(line->dv, cone->vAO);
	h->co = vector_p1_to_p2(cone->pA, line->p);
	h->cov = dot_vec(h->co, cone->vAO);
	h->dco = dot_vec(line->dv, h->co);
	
	h->a = pow(h->dv, 2) - pow(h->cos_alpha, 2);
	h->b = 2 * (h->dv * h->cov - h->dco * pow(h->cos_alpha, 2));
	h->c = pow(h->cov, 2) - dot_vec(h->co, h->co) * pow(h->cos_alpha, 2);
	return (pow(h->b, 2) - 4 * h->a * h->c);
}

t_points	recheck()
{
	
}

t_points	intersection2(double delta, t_line *line, t_cal_helper *h, t_cone *cone)
{
	double		t;
	t_points	ret;

	t = (-h->b + sqrt(delta)) / (2 * h->a);
	ret.p1.x = line->p.x + line->dv.x * t;
	ret.p1.y = line->p.y + line->dv.y * t;
	ret.p1.z = line->p.z + line->dv.z * t;
	t = (-h->b - sqrt(delta)) / (2 * h->a);
	ret.p2.x = line->p.x + line->dv.x * t;
	ret.p2.y = line->p.y + line->dv.y * t;
	ret.p2.z = line->p.z + line->dv.z * t;
	return (recheck(&ret, cone));
}
t_points	intersection1(double delta, t_line *line, t_cal_helper *h, t_cone *cone)
{
	t_points	ret;
	double		t;

	if (delta == 0)
	{
		ret.amount = 1;
		t = -h->b / (2 * h->a);
		ret.p1.x = line->p.x + line->dv.x * t;
		ret.p1.y = line->p.y + line->dv.y * t;
		ret.p1.z = line->p.z + line->dv.z * t;
		return (recheck(ret, cone));
	}
	return (intersection2(delta, line, h, cone));
}

t_points	intersection(t_line line, t_cone cone)
{
	t_cal_helper	h;
	double			delta;
	t_points		ret;

	delta = call_stuff(&h, &line, &cone);
	if (delta <= 0)
		return (ret.amount = 0, ret);
	return intersection1(delta, &line, &h, &cone);
}
