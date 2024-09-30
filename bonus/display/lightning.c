/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:44:56 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/30 16:31:43 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	is_in_shadow(t_data *data, t_hit *hit, t_vec3 *light_dir, double dist)
{
	t_ray	ray;
	t_hit	new_hit;

	ray.ray_direction = *light_dir;
	ray.ray_origin = add(hit->world_position, scale(hit->world_normal, 0.00001));
	ray_trace(data, &ray, &new_hit);
	if (new_hit.found == 1 && new_hit.hit_distance < dist)
	{
		return (1);
	}
	return (0);
}

typedef struct s_calculate_light
{
	t_vec3	effective_color;
	t_vec3	ambitient;
	t_vec3	light_dir;
	t_vec3	difuse;
	t_vec3	specular;
	double	light_dot;
	t_vec3	reflect;
	double	reflect_dot;
	double	factor;
}	t_calculate_light;

// void	calculate_light2(t_data *data, t_ray *ray, t_hit *hit,
// 		t_calculate_light *cl)
// {
// 	cl->difuse = scale(cl->effective_color, cl->light_dot);
// 	cl->reflect = vec_reflect_norm(scale(cl->light_dir, -1.0), \
// 		hit->world_normal);
// 	cl->reflect_dot = dot_product(cl->reflect, ray->ray_direction);
// 	if (cl->reflect_dot > 0)
// 	{
// 		cl->factor = pow(cl->reflect_dot, 10);
// 		cl->specular = scale(data->light[0].vec3_color, \
// 			data->light[0].ratio * cl->factor);
// 	}
// }

typedef struct s_matrix4
{
	double	cords[4][4];
}	t_matrix4;

t_matrix4	create_scaling_matrix(double x, double y, double z)
{
	t_matrix4	mat;
	int			_y;
	int			_x;

	_y = 0;
	while (_y < 4)
	{
		_x = 0;
		while (_x < 4)
		{
			mat.cords[_y][_x] = 0;
			_x++;
		}
		_y++;
	}
	mat.cords[0][0] = x;
	mat.cords[1][1] = y;
	mat.cords[2][2] = z;
	mat.cords[3][3] = 1;
	return (mat);
}

t_matrix4	create_translating_matrix(double x, double y, double z)
{
	t_matrix4	mat;
	int			_y;
	int			_x;

	_y = 0;
	while (_y < 4)
	{
		_x = 0;
		while (_x < 4)
		{
			mat.cords[_y][_x] = 0;
			_x++;
		}
		_y++;
	}
	mat.cords[0][0] = 1;
	mat.cords[1][1] = 1;
	mat.cords[2][2] = 1;
	mat.cords[0][3] = x;
	mat.cords[1][3] = y;
	mat.cords[2][3] = z;
	mat.cords[3][3] = 1;
	return (mat);
}

double determinant(t_matrix4 m) {
    double det = 0;
    // Calculate the determinant using cofactor expansion
    for (int i = 0; i < 4; i++) {
        double submatrix[3][3];
        for (int j = 1; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (k < i) {
                    submatrix[j - 1][k] = m.cords[j][k];
                } else if (k > i) {
                    submatrix[j - 1][k - 1] = m.cords[j][k];
                }
            }
        }
        double sub_det = submatrix[0][0] * (submatrix[1][1] * submatrix[2][2] - submatrix[1][2] * submatrix[2][1])
                       - submatrix[0][1] * (submatrix[1][0] * submatrix[2][2] - submatrix[1][2] * submatrix[2][0])
                       + submatrix[0][2] * (submatrix[1][0] * submatrix[2][1] - submatrix[1][1] * submatrix[2][0]);
        det += (i % 2 == 0 ? 1 : -1) * m.cords[0][i] * sub_det;
    }
    return det;
}

t_matrix4 adjugate(t_matrix4 m) {
	t_matrix4 adj;
	// Calculate the adjugate matrix
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			double submatrix[3][3];
			int subi = 0;
			for (int row = 0; row < 4; row++) {
				if (row == i) continue;
				int subj = 0;
				for (int col = 0; col < 4; col++) {
					if (col == j) continue;
					submatrix[subi][subj] = m.cords[row][col];
					subj++;
				}
				subi++;
			}
			// Calculate the determinant of the 3x3 submatrix
			double sub_det = submatrix[0][0] * (submatrix[1][1] * submatrix[2][2] - submatrix[1][2] * submatrix[2][1])
							- submatrix[0][1] * (submatrix[1][0] * submatrix[2][2] - submatrix[1][2] * submatrix[2][0])
							+ submatrix[0][2] * (submatrix[1][0] * submatrix[2][1] - submatrix[1][1] * submatrix[2][0]);
			adj.cords[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * sub_det; // Transpose and apply sign
		}
	}
	return adj;
}

t_matrix4 inverse(t_matrix4 m) {
    t_matrix4 inv;
    double det = determinant(m);
    if (det == 0) {
        // Return an identity matrix or handle the error as needed
        printf("Matrix is not invertible\n");
		inv.cords[0][0] = 0;
        return (inv);
    }
    t_matrix4 adj = adjugate(m);
    // Multiply adjugate by 1/det to get the inverse
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            inv.cords[i][j] = adj.cords[i][j] / det;
        }
    }
    return inv;
}

t_vec3	multiply_mat_vec3(t_matrix4 m, t_vec3 p)
{
	t_vec3	result;
	double	w;

	result.x = m.cords[0][0] * p.x + m.cords[0][1] * p.y + m.cords[0][2] * p.z + m.cords[0][3];
    result.y = m.cords[1][0] * p.x + m.cords[1][1] * p.y + m.cords[1][2] * p.z + m.cords[1][3];
    result.z = m.cords[2][0] * p.x + m.cords[2][1] * p.y + m.cords[2][2] * p.z + m.cords[2][3];
	w = m.cords[3][0] * p.x + m.cords[3][1] * p.y + m.cords[3][2] * p.z + m.cords[3][3];
	if (w != 0)
	{
		result = scale(result, 1.0 / w);
	}
	return result;
}

// double u = 0.5 + atan2(vec.z, vec.x) / 2.0 / M_PI;
// double v = 0.5 + asin(vec.y);

t_vec3	get_vec3(t_hit *hit)
{
	double	d;

	d = dot_product(hit->cords, hit->normal);
	if (hit->normal.x == 0)
		return (create_vec3(1, 0, 0));
	if (hit->normal.y == 0)
		return (create_vec3(0, 1, 0));
	if (hit->normal.z == 0)
		return (create_vec3(0, 0, 1));
	if (d == 0)
	{
		return (subtract(hit->cords, create_vec3(-(hit->normal.y / hit->normal.x), 1, 0)));
	}
	return (subtract(hit->cords, create_vec3(d, 0, 0)));
}

t_vec3	checker_plane(t_hit *hit)
{
	t_vec3	vector1;
	t_vec3	vector2;
	t_vec3	vector3;

	vector3 = subtract(hit->world_position, hit->cords);
	if (dot_product(vector3, vector3) < TOLARANCE / 100)
		return (create_vec3(1, 1, 1));
	vector1 = normalize(get_vec3(hit));
	vector2 = normalize(cross(vector1, hit->normal));
	// dprintf(1, "%f %f %f\n", vector3.x, vector3.y, vector3.z);
	// dprintf(1, "%f %f %f\n", vector2.x, vector2.y, vector2.z);
	// dprintf(1, "%f %f %f\n", vector1.x, vector1.y, vector1.z);
	// exit(1);
	double ax;
	double bx;
	double ay;
	double by;
	double cx;
	double cy;
	int seen = 0;
	if (vector1.x != 0 || vector2.x != 0)
	{
		ax = vector1.x;
		bx = vector2.x;
		cx = vector3.x;
		seen = 1;
	}
	if (vector1.y != 0 || vector2.y != 0)
	{
		if (seen == 1)
		{
			ay = vector1.y;
			by = vector2.y;
			cy = vector3.y;
		}
		else
		{
			ax = vector1.y;
			bx = vector2.y;
			cx = vector3.y;
		}
		seen++;
	}
	if (seen == 1 && (vector1.z != 0 || vector2.z != 0))
	{
		ay = vector1.z;
		by = vector2.z;
		cy = vector3.z;
		seen++;
	}
	if (seen != 2)
		return (create_vec3(1, 1, 1));
	double u;
	double v;
	
	if (ax == 0 && by == 0)
	{
		v = cx / bx;
		u = cy / ay;
	
	}
	else if (ax == 0)
	{
		v = cx / bx;
		u = (cy - v * by) / ay;

	}
	else if (by == 0)
	{
		u = cy / ay;
		v = (cx - u * ax) / bx;
	}
	else
	{
		v = (cy - cx * ay) / (by * ax - bx * ay);
		u = (cx - v * bx) / ax;
			// dprintf(1, "%f %f\n", u, v);
	}
	
	if (((long long)floor(u * 5) + (long long)floor(v * 5)) % 2 == 0)
		return (create_vec3(1, 1, 1));
	return (hit->color);
}

t_vec3	stripe_at(t_vec3 point, t_vec3 color1, t_vec3 color2)
{
	if (((long long)floor(point.x) +(long long)floor(point.y) + (long long)floor(point.z)) % 2)
		return color1;
	return color2;
}

t_vec3	stripe_at_object(t_hit *hit)
{
	if (hit->type == 2)
	{
		// return (hit->color);
		return (checker_plane(hit));
	}
	t_vec3	object_point = multiply_mat_vec3(inverse(create_scaling_matrix(0.2, 0.2, 0.2)), hit->world_position);
	t_vec3	pattern_point = multiply_mat_vec3(inverse(create_translating_matrix(100, 0, 0)), object_point);
	return (stripe_at(pattern_point, hit->color, create_vec3(1.0, 1.0, 1.0)));
}


t_vec3	calculate_light(t_data *data, t_ray *ray, t_hit *hit)
{
	double				dist;
	t_calculate_light	cl;
	int					i;
	t_vec3				final;
	t_vec3				color;

	color = hit->color;
	if (1)
	{
		color = stripe_at_object(hit);
	}

	(void)ray;
	cl.ambitient = scale(multiply_vec3(color, \
		data->ambitient_light.vec3_color), data->ambitient_light.ratio);

	final = create_vec3(0, 0, 0);
	i = 0;
	while (i < data->amount_of_lights)
	{
		cl.effective_color = multiply_vec3(color, \
		scale(data->light[i].vec3_color, data->light[i].ratio));
		cl.difuse = create_vec3(0, 0, 0);
		cl.specular = create_vec3(0, 0, 0);
		cl.light_dir = subtract(data->light[i].vec3_cords, hit->world_position);
		dist = sqrt(dot_product(cl.light_dir, cl.light_dir));
		cl.light_dir = normalize(cl.light_dir);
		cl.light_dot = dot_product(cl.light_dir, hit->world_normal);
		if (cl.light_dot > 0 && !is_in_shadow(data, hit, &cl.light_dir, dist))
		{
			cl.difuse = scale(cl.effective_color, cl.light_dot);
			cl.reflect = vec_reflect_norm(scale(cl.light_dir, -1.0), \
				hit->world_normal);
			cl.reflect_dot = dot_product(cl.reflect, ray->ray_direction);
			if (cl.reflect_dot > 0)
			{
				cl.factor = pow(cl.reflect_dot, 10);
				cl.specular = scale(data->light[i].vec3_color, \
					data->light[i].ratio * cl.factor);
			}
		}
		final = add(final, add(cl.difuse, cl.specular));
		i++;
	}
	return (add(final, cl.ambitient));
}
