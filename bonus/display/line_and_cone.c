/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_and_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:50:56 by qdo               #+#    #+#             */
/*   Updated: 2024/09/29 21:53:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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
	return (sqrt( \
		pow(p1.x - p2.x, 2) \
		+ pow(p1.y - p2.y, 2) \
		+ pow(p1.z - p2.z, 2)));
}

typedef struct s_cal_helper
{
	double	cos_alpha;
	double	d_v;
	t_vec3	co;
	double	co_v;
	double	d_co;
	double	a;
	double	b;
	double	c;
} t_cal_helper;

//https://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
double	cal_stuff(t_cal_helper *h, t_line *line, t_cone_tom *cone)
{
	double height = cal_distance(cone->pA, cone->pO);

	h->cos_alpha = height / sqrt(height * height + cone->r * cone->r);
	h->d_v = dot_vec(line->dv, cone->vAO);
	h->co = vector_p1_to_p2(cone->pA, line->p);
	h->co_v = dot_vec(h->co, cone->vAO);
	h->d_co = dot_vec(line->dv, h->co);
	h->a = pow(h->d_v, 2) - pow(h->cos_alpha, 2);
	h->b = 2 * (h->d_v * h->co_v - h->d_co * pow(h->cos_alpha, 2));
	h->c = pow(h->co_v, 2) - dot_vec(h->co, h->co) * pow(h->cos_alpha, 2);
	return (pow(h->b, 2) - (4 * h->a * h->c));
}

double radianToDegree(double radian) {
    return radian * (180.0 / M_PI);
}

double	degree_2_vector(t_vec3 *v1, t_vec3 *v2)
{
	return (radianToDegree( \
		acos( \
		(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z) \
			/ (sqrt(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z) \
				+ sqrt(v2->x * v2->x + v2->y * v2->y + v2->z * v2->z)))));
}

t_points	intersection2_2(double t, double delta, t_line *line, t_cal_helper *h)
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
	t = (- h->b) / (2 * h->a);
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

t_points	intersection(t_line *line, t_cone_tom *cone)
{
	t_cal_helper	h;
	double			delta;
	t_points		ret;

	delta = cal_stuff(&h, line, cone);
	if (delta < 0)
		return (ret.amount = 0, ret);
	if (delta == 0)
		return intersection1(line, &h);
	return intersection2(delta, line, &h);
}

t_vec3	vector_cross_product(t_vec3 v1, t_vec3 v2)
{
	t_vec3	vec;

	vec.x = v1.y * v2.z - v1.z * v2.y;
	vec.y = v1.z * v2.x - v1.x * v2.z;
	vec.z = v1.x * v2.y - v1.y * v2.x;
	return (vec);
}

t_point_x_nor_vec	line_x_cone(t_line *line, t_cone_tom *cone)
{
	static int i = 0;
	i++;
	t_points points;
	t_point_x_nor_vec ret;
	t_vec3	ap;
	t_vec3	op;

	points = intersection(line, cone);
	t_vec3	cp;
	double 	s = sqrt(cone->r * cone->r + pow(cal_distance(cone->pA, cone->pO), 2));

	if (points.amount == 0)
		return (ret.amount = 0, ret);
	if (points.amount == 1)
	{
		cp.x = points.p1.x - cone->pA.x;
		cp.y = points.p1.y - cone->pA.y;
		cp.z = points.p1.z - cone->pA.z;
		if (degree_2_vector(&cp, &cone->vAO) > 90 || cal_distance(points.p1, cone->pA) > s)
		{
			ret.amount = 0;
			return (ret);
		}
		else
		{
			ret.amount = 1;
			ret.t = points.t1;
			ap = vector_p1_to_p2(cone->pA, points.p1);
			op = vector_p1_to_p2(cone->pO, points.p1);
			ret.v = vector_cross_product(vector_cross_product(ap, op), ap);
			ret.v = normalize(ret.v);
			if (dot_vec(ret.v, op) < 0)
			{
				ret.v.x *= -1;
				ret.v.y *= -1;
				ret.v.y *= -1;
			}
			return (ret);
		}
	}
	if (points.amount == 2)
	{
		cp.x = points.p2.x - cone->pA.x;
		cp.y = points.p2.y - cone->pA.y;
		cp.z = points.p2.z - cone->pA.z;
		if (degree_2_vector(&cp, &cone->vAO) > 90 || cal_distance(points.p2, cone->pA) > s)
		{
			points.amount = 1;
		}
		cp.x = points.p1.x - cone->pA.x;
		cp.y = points.p1.y - cone->pA.y;
		cp.z = points.p1.z - cone->pA.z;
		if (degree_2_vector(&cp, &cone->vAO) > 90 || cal_distance(points.p1, cone->pA) > s)
		{
			points.amount -= 1;
			points.p1 = points.p2;
			points.t1 = points.t2;
		}
	}

	if (points.amount == 0)
	{
		return (ret.amount = 0, ret);
	}
	if (points.amount == 2)
	{
		if (cal_distance(points.p1, line->p) > cal_distance(points.p2, line->p))
		{
			points.p1 = points.p2;
			points.t1 = points.t2;
		}
	}
	ret.amount = 1;
	ret.t = points.t1;
	ap = vector_p1_to_p2(cone->pA, points.p1);
	op = vector_p1_to_p2(cone->pO, points.p1);
	ret.v = vector_cross_product(vector_cross_product(ap, op), ap);
	ret.v = normalize(ret.v);
	if (dot_vec(ret.v, op) < 0)
	{
		ret.v.x *= -1;
		ret.v.y *= -1;
		ret.v.y *= -1;
	}
	return (ret);
}

