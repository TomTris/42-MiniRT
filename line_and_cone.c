/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:50:56 by qdo               #+#    #+#             */
/*   Updated: 2024/09/29 17:04:03 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"
#include "../include/minirt.h"

double dot_vec(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	vector_p1_to_p2(t_point point1, t_point point2)
{
	t_vec3	vec;

	vec.x = point2.x - point1.x;
	vec.y = point2.y - point1.y;
	vec.z = point2.z - point1.z;
	return (vec);
}

double	cal_distance(t_point p1, t_point p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) \
		+ pow(p1.y - p2.y, 2) \
		+ pow(p1.z - p2.z, 2)));
}

typedef struct s_cal_helper
{
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
double	cal_stuff(t_cal_helper *h, t_line *line, t_cone *cone)
{
	double height = cal_distance(cone->pA, cone->pO);
	h->cos_alpha = height / sqrt(pow(height, 2) + pow(cone->r, 2));
	h->dv = dot_vec(line->dv, cone->vAO);
	h->co.x = line->p.x - cone->pA.x;
	h->co.y = line->p.y - cone->pA.y;
	h->co.z = line->p.z - cone->pA.z;
	h->cov = dot_vec(h->co, cone->vAO);
	h->dco = dot_vec(line->dv, h->co);
	
	h->a = pow(h->dv, 2) - pow(h->cos_alpha, 2);
	h->b = 2 * (h->dv * h->cov - h->dco * pow(h->cos_alpha, 2));
	h->c = pow(h->cov, 2) - dot_vec(h->co, h->co) * pow(h->cos_alpha, 2);
	return (pow(h->b, 2) - 4 * h->a * h->c);
}

double radianToDegree(double radian) {
    return radian * (180.0 / M_PI);
}

t_points	recheck(t_points *ret, t_cone *cone)
{	
	t_vec3	cp;
	double	accos;

	if (ret->amount == 2)
	{
		cp.x = cone->pA.x - ret->p2.x;
		cp.y = cone->pA.y - ret->p2.y;
		cp.z = cone->pA.z - ret->p2.z;
		accos = acos(dot_vec(cp, cone->vAO) / cal_distance(cone->pA, ret->p2));
		if (radianToDegree(accos) > 90)
			ret->amount = 1;
	}
	cp.x = cone->pA.x - ret->p1.x;
	cp.y = cone->pA.y - ret->p1.y;
	cp.z = cone->pA.z - ret->p1.z;
	accos = acos(dot_vec(cp, cone->vAO) / cal_distance(cone->pA, ret->p1));
	if (radianToDegree(accos) > 90)
	{
		ret->amount -= 1;
		ret->p1 = ret->p2;
		ret->t1 = ret->t2;
	}
	return (*ret);
}

t_points	intersection2_2(double t, double delta, t_line *line, t_cal_helper *h)
{
	double		t;
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

t_points	intersection2(double delta, t_line *line, t_cal_helper *h, t_cone *cone)
{
	t_points	ret;
	double		t;

	ret.amount = 0;
	t = (-h->b + sqrt(delta)) / (2 * h->a);
	if (t > 0)
	{
		intersection2_2(t, delta, line, h);
		return (recheck(&ret, cone));
	}
	t = (-h->b - sqrt(delta)) / (2 * h->a);
	if (t > 0)
	{
		ret.amount = 1;
		ret.t1 = t;
		ret.p1.x = line->p.x + line->dv.x * t;
		ret.p1.y = line->p.y + line->dv.y * t;
		ret.p1.z = line->p.z + line->dv.z * t;
	}
	return (recheck(&ret, cone));
}
t_points	intersection1(t_line *line, t_cal_helper *h, t_cone *cone)
{
	t_points	ret;
	double		t;

	ret.amount = 0;
	t = - h->b / (2 * h->a);
	if (t > 0)
	{
		ret.amount = 1;
		ret.t1 = t;
		ret.p1.x = line->p.x + line->dv.x * t;
		ret.p1.y = line->p.y + line->dv.y * t;
		ret.p1.z = line->p.z + line->dv.z * t;
		return (recheck(&ret, cone));
	}
	return (ret);
}

t_points	intersection(t_line *line, t_cone *cone)
{
	t_cal_helper	h;
	double			delta;
	t_points		ret;

	delta = cal_stuff(&h, line, cone);
	if (delta < 0)
		return (ret.amount = 0, ret);
	if (delta = 0)
		return intersection1(line, &h, cone);
	return intersection2(delta, line, &h, cone);
}

t_vec3	vector_cross_product(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_point_x_nor_vec	line_x_cone(t_line *line, t_cone *cone)
{
	t_points points;
	t_point_x_nor_vec ret;
	t_vec3	ap;
	t_vec3	op;

	points = intersection(line, cone);
	if (points.amount = 0)
		return (ret.amount = 0, ret);
	if (points.amount == 2)
		return (ret.amount = 0, perror("Sthwrong in line_x_cone"), ret);
	ret.amount = 1;
	ap = vector_AO_form_A_O(cone->pA, points.p1);	
	op = vector_AO_form_A_O(cone->pO, points.p1);
	ret.v = vector_cross_product(vector_cross_product(ap, op), ap);
	ret.v = normalize(ret.v);
	if (dot_vec(ret.v, op) < 0)
		ret.v = scale(ret.v, -1.0);
	ret.t = points.t1;
	return (ret);
}

