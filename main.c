/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:05:08 by selibrah          #+#    #+#             */
/*   Updated: 2020/01/09 01:45:18 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

double	zoom(double start, double end, double zoomrate)
{
	return (start + ((double)(end - start) * zoomrate));
}

void	cons(t_win *wi)
{
	wi->inpt[0] = wi->mx;
	wi->inpt[1] = wi->my;
	wi->inpt[2] = wi->r;
	wi->inpt[3] = wi->g;
	wi->inpt[4] = wi->b;
	wi->inpt[5] = wi->jl;
	wi->inpt[6] = wi->remin;
	wi->inpt[7] = wi->immin;
	wi->inpt[8] = wi->remax;
	wi->inpt[9] = wi->immax;
	wi->inpt[10] = wi->key;
	wi->inpt[11] = wi->p;
	wi->inpt[12] = wi->max_iteration;
}

int		runcl(t_win *wi)
{
	wi->inpt = (double *)malloc(13 * sizeof(double));
	(wi)->l.kl = load_kernel_from_file(wi, (wi)->l.cxt, (wi)->l.fl);
	(wi)->l.cmdqu = clCreateCommandQueue((wi)->l.cxt, \
			(wi)->l.dvs, 0, &(wi)->l.err);
	cons(wi);
	(wi)->l.img = clCreateBuffer((wi)->l.cxt, CL_MEM_WRITE_ONLY,\
			(wi)->l.bfsz, NULL, &(wi)->l.err);
	(wi)->l.inpts = clCreateBuffer((wi)->l.cxt, CL_MEM_READ_WRITE,\
			sizeof(double) * 13, NULL, &(wi)->l.err);
	clEnqueueWriteBuffer((wi)->l.cmdqu,
			(wi)->l.inpts, CL_FALSE, 0,
			sizeof(cl_double) * 13, wi->inpt, 0, NULL, NULL);
	clSetKernelArg((wi)->l.kl, 0, sizeof(cl_mem), &(wi)->l.img);
	clSetKernelArg((wi)->l.kl, 1, sizeof(cl_mem), &(wi)->l.inpts);
	clEnqueueNDRangeKernel((wi)->l.cmdqu, (wi)->l.kl, 2, NULL,\
			wi->device_work_size, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer((wi)->l.cmdqu, (wi)->l.img, CL_TRUE, 0,\
			(wi)->l.bfsz, wi->line, 0, NULL, NULL);
	mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img_ptr, 434, 181);
	if (wi->k == 1)
		fractalpha(wi);
	freecl(wi);
	return (CL_SUCCESS);
}

void	init(t_win *wi, char *ar, int b)
{
	wi->winx = 820;
	wi->winy = 608;
	wi->key = 1;
	wi->mx = 0;
	wi->my = 0;
	wi->remax = 2.69736842;
	wi->remin = -2.69736842;
	wi->immax = 2;
	wi->immin = -2;
	wi->max_iteration = 50;
	wi->r = 10;
	wi->g = 10;
	wi->b = 10;
	wi->al = 0;
	wi->h = 0;
	wi->p = 0;
	wi->et = 1700;
	wi->het = 1275;
	if (48 < ar[0] && ar[0] < 57 && b == 2 && ar[1] == '\0')
		wi->key = ar[0] - 48;
	else
		printmsg(0);
}

int		main(int argc, char **argv)
{
	t_win wi;

	wi.jl = 0;
	wi.k = 0;
	wi.mlx_ptr = mlx_init();
	wi.win_ptr = mlx_new_window(wi.mlx_ptr, 1700, 1275, "Best Fractol Ever");
	wi.img_ptr2 = mlx_new_image(wi.mlx_ptr, 1700, 1275);
	init(&wi, argv[1], argc);
	wi.imgstr = mlx_png_file_to_image(wi.mlx_ptr, "ofah.png", &wi.et, &wi.het);
	mlx_put_image_to_window(wi.mlx_ptr, wi.win_ptr, wi.imgstr, 0, 0);
	wi.img_ptr = mlx_new_image(wi.mlx_ptr, wi.winx, wi.winy);
	wi.line = mlx_get_data_addr(wi.img_ptr, &wi.bpp, &wi.size_line, &wi.endian);
	opnclinit(&wi);
	runcl(&wi);
	wi.img_ptr3 = mlx_new_image(wi.mlx_ptr, 1700, 1275);
	wi.img2str = mlx_png_file_to_image(wi.mlx_ptr, "lt.png", &wi.et, &wi.het);
	wi.img_ptr4 = mlx_new_image(wi.mlx_ptr, 1700, 1275);
	wi.img3str = mlx_png_file_to_image(wi.mlx_ptr, "lks.png", &wi.et, &wi.het);
	wi.img_ptr5 = mlx_new_image(wi.mlx_ptr, 50, 50);
	wi.img4str = mlx_png_file_to_image(wi.mlx_ptr, "al.png", &wi.et, &wi.het);
	mlx_hook(wi.win_ptr, 6, 0, mouse_move, &wi);
	mlx_hook(wi.win_ptr, 4, 0, mouse_press, &wi);
	mlx_hook(wi.win_ptr, 2, 0, key_press, &wi);
	mlx_loop(wi.mlx_ptr);
	return (0);
}
