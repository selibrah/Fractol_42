/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:05:08 by selibrah          #+#    #+#             */
/*   Updated: 2019/12/29 10:27:00 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void cons(t_win *wi)
{
	wi->inpt[0] = wi->mx;
	wi->inpt[1] = wi->my;
	wi->inpt[2] = wi->r;
	wi->inpt[3] = wi->g;
	wi->inpt[4] = wi->b;
	wi->inpt[5] = wi->jl;
	wi->inpt[6] = wi->Remin;
	wi->inpt[7] = wi->Immin;
	wi->inpt[8] = wi->Remax;
	wi->inpt[9] = wi->Immax;
	wi->inpt[10] = wi->key;
	wi->inpt[11] = wi->p;
	wi->inpt[12] = wi->max_iteration;
}
void opnclinit(t_win *wi)
{
	(wi)->l.err = 0;
	(wi)->l.ndvs = 0;
	(wi)->l.fl = "mandelbrot.cl";
	(wi)->l.rtsz = 0;
	(wi)->l.bfsz = sizeof(char) * wi->winx * wi->winy * 4;
	
	(wi)->l.cxt = create_context(&(wi)->l.ndvs);
	clGetContextInfo((wi)->l.cxt, CL_CONTEXT_DEVICES, \
            sizeof(cl_device_id), &(wi)->l.dvs, NULL);
  	wi->device_work_size[0] = wi->winx; 
  	wi->device_work_size[1] = wi->winy;
}

int runCL(t_win *wi)
{
	wi->inpt = (double *) malloc(13 * sizeof(double));
	(wi)->l.kl = load_kernel_from_file(wi,(wi)->l.cxt, (wi)->l.fl);
	(wi)->l.cmdqu = clCreateCommandQueue((wi)->l.cxt, \
  (wi)->l.dvs, 0, &(wi)->l.err);
	cons(wi);
	(wi)->l.img = clCreateBuffer((wi)->l.cxt, CL_MEM_WRITE_ONLY,\
   (wi)->l.bfsz, NULL, &(wi)->l.err);
	(wi)->l.inpts = clCreateBuffer((wi)->l.cxt, CL_MEM_READ_WRITE,\
   sizeof(double) * 14, NULL, &(wi)->l.err);
	clEnqueueWriteBuffer((wi)->l.cmdqu,
			(wi)->l.inpts, CL_FALSE, 0,
			sizeof(cl_double) * 13, wi->inpt, 0, NULL, NULL);
	clSetKernelArg((wi)->l.kl, 0, sizeof(cl_mem), &(wi)->l.img);
	clSetKernelArg((wi)->l.kl, 1, sizeof(cl_mem), &(wi)->l.inpts);
	clEnqueueNDRangeKernel((wi)->l.cmdqu, (wi)->l.kl, 2, NULL,\
			wi->device_work_size, NULL, 0, NULL,NULL);
	clFinish((wi)->l.cmdqu);
	clEnqueueReadBuffer((wi)->l.cmdqu, (wi)->l.img, CL_TRUE, 0,\
	(wi)->l.bfsz, wi->line, 0, NULL, NULL);
	clReleaseKernel((wi)->l.kl);
	clReleaseProgram((wi)->l.program);
	clReleaseMemObject((wi)->l.img);
	clReleaseMemObject((wi)->l.inpts);
	clReleaseCommandQueue((wi)->l.cmdqu);
	mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img_ptr, 434, 181);
	free(wi->inpt);
	return CL_SUCCESS;
}
void init(t_win *wi)
{
	wi->winx = 820;
	wi->winy = 608;
	wi->key = 1;
	wi->mx = 0;
	wi->my = 0;
	wi->Remax = 2.69736842;
	wi->Remin = -2.69736842;
	wi->Immax = 2;
	wi->Immin = -2;
	wi->max_iteration = 50;
	wi->r = 10;
	wi->g = 10;
	wi->b = 10;
	wi->al = 0;
	wi->h = 0;
	wi->p = 2;
	wi->et = 1700;
	wi->het = 1275;
}

int main(int argc, const char *argv[])
{
	t_win wi;

	wi.jl = 0;
	wi.mlx_ptr = mlx_init();
	wi.win_ptr = mlx_new_window(wi.mlx_ptr, 1700, 1275, "Best Fractol Ever");
	wi.img_ptr2 = mlx_new_image(wi.mlx_ptr, 1700, 1275);
	init(&wi);
	wi.imgstr = mlx_png_file_to_image(wi.mlx_ptr, "ofah.png", &wi.et, &wi.het);
	mlx_put_image_to_window(wi.mlx_ptr, wi.win_ptr, wi.imgstr, 0, 0);
	wi.img_ptr = mlx_new_image(wi.mlx_ptr, wi.winx, wi.winy);
	wi.line = mlx_get_data_addr(wi.img_ptr, &wi.bpp, &wi.size_line, &wi.endian);
	opnclinit(&wi);
	runCL(&wi);
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
	return 0;
}
