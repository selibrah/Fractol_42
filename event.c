/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:04:46 by selibrah          #+#    #+#             */
/*   Updated: 2020/01/06 08:01:13 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

int		mouse_move(int x, int y, t_win *wi)
{
	wi->mx = ((double)(x - 434) / (1254 - 434)) \
	* (wi->remax - wi->remin) + wi->remin;
	wi->my = ((double)(y - 181) / (789 - 181)) \
	* (wi->immax - wi->immin) + wi->immin;
	if (wi->al && wi->h == 0 && wi->jl == 0)
	{
		mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->imgstr, 0, 0);
		runcl(wi);
		mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr \
				, wi->img4str, x - 25, y - 25);
	}
	else if (wi->h == 0 && wi->jl == 0)
		runcl(wi);
	return (0);
}

void	fractalpha(t_win *wi)
{
	int cl;
	int cli;
	int oh;

	cl = 0;
	mlx_clear_window(wi->mlx_ptr, wi->win_ptr);
	mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->imgstr, 0, 0);
	while (cl < 608)
	{
		cli = 0;
		while (cli < 810)
		{
			oh = cli * 4 + cl * wi->winx * 4;
			mlx_string_put(wi->mlx_ptr, wi->win_ptr, cli + 434, cl + 201\
			, (wi->line[oh] << 8) + (wi->line[oh + 1] << 16)\
			+ (wi->line[oh + 2]), "h");
			cli += 6;
		}
		cl += 9;
	}
}

void	keyclpiter(int key, t_win *wi)
{
	if (key < 92 && key > 82)
	{
		init(wi, "1", 2);
		wi->key = key - 82;
	}
	else if (key == 53)
		frexit(wi);
	else if (key == 69 || key == 78)
		wi->max_iteration += key == 69 ? 10 : -10;
	else if (key == 0 || key == 1)
		wi->p += key == 0 ? 1 : -1;
	else if (key == 15)
		wi->r += 1;
	else if (key == 5)
		wi->g += 1;
	else if (key == 11)
		wi->b += 1;
	else if (key == 6)
		wi->al = !wi->al;
	else if (key == 4)
		wi->h = 0;
	else if (key == 35)
		wi->k = !wi->k;
	else
		wi->a = 1;
}

int		key_press(int key, t_win *wi)
{
	double temp;

	temp = 0.1 * ((key == 123 || key == 124) ? \
			wi->remax - wi->remin : wi->immax - wi->immin);
	wi->a = 0;
	if (key == 123 || key == 124)
	{
		wi->remax += key == 123 ? temp : -temp;
		wi->remin += key == 123 ? temp : -temp;
	}
	else if (key == 126 || key == 125)
	{
		wi->immax += key == 126 ? temp : -temp;
		wi->immin += key == 126 ? temp : -temp;
	}
	else
		keyclpiter(key, wi);
	if (wi->a == 0 && wi->h == 0)
	{
		mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->imgstr, 0, 0);
		runcl(wi);
	}
	if (key == 82)
		mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img2str, 0, 0);
	return (0);
}

int		mouse_press(int key, int x, int y, t_win *wi)
{
	wi->a = 0;
	if (key == 5 || key == 4)
	{
		wi->zoomrate = key == 5 ? 0.9 : 1.0 / 0.9;
		wi->max_iteration += 5 ? 1 : -1;
	}
	else if (key == 2)
		wi->jl = !wi->jl;
	else if (key == 1 && 360 < x && x < 436 && 959 < y && y < 1053)
		frexit(wi);
	else if (key == 1 && 1255 < x && x < 1527 && 181 < y && y < 789)
	{
		init(wi, "1", 2);
		wi->key = ((x - 1254) / 137) * 4 + (y - 171) / 152 + 1;
	}
	else
		wi->a = 1;
	drwafract(key, x, y, wi);
	return (0);
}
