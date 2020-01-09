/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:04:53 by selibrah          #+#    #+#             */
/*   Updated: 2019/12/19 15:36:44 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sysctl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bmp.h"

char		*load_program_source(const char *filename)
{
	struct stat	statbuf;
	int			fd;
	char		*source;

	fd = open(filename, O_RDONLY);
	if (fd == 0)
		return (0);
	stat(filename, &statbuf);
	source = (char *)malloc(statbuf.st_size + 1);
	read(fd, source, statbuf.st_size);
	source[statbuf.st_size] = '\0';
	close(fd);
	return (source);
}

void		drwafract(int key, int x, int y, t_win *wi)
{
	if (key == 1 && x > 437 && x < 452 && y > 171 && y < 181)
	{
		mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img2str, 0, 0);
		wi->h = 1;
	}
	else if (key == 1 && x > 439 && x < 565 && y > 270 && y < 283)
		mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img3str, 0, 0);
	if (wi->a == 0 && wi->h == 0)
	{
		wi->mx = ((double)(x - 434) / (1254 - 434)) \
		* (wi->remax - wi->remin) + wi->remin;
		wi->my = ((double)(y - 181) / (789 - 181)) \
		* (wi->immax - wi->immin) + wi->immin;
		if (key == 5 || key == 4)
		{
			wi->remin = zoom(wi->mx, wi->remin, wi->zoomrate);
			wi->immin = zoom(wi->my, wi->immin, wi->zoomrate);
			wi->remax = zoom(wi->mx, wi->remax, wi->zoomrate);
			wi->immax = zoom(wi->my, wi->immax, wi->zoomrate);
		}
		runcl(wi);
		if (wi->al)
			mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, \
					wi->img4str, x - 25, y - 25);
	}
}

void		opnclinit(t_win *wi)
{
	(wi)->l.err = (1 < 0 ? 0 : 0);
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

cl_kernel	load_kernel_from_file(t_win *wi, cl_context ctxt, const char *flnm)
{
	static int	ij;
	int			err;
	static char	*program_source;

	if (ij == 0)
	{
		program_source = load_program_source(flnm);
		ij = 1;
	}
	(wi)->l.program = clCreateProgramWithSource(ctxt, 1,
			(const char **)&program_source,
			NULL, &err);
	clBuildProgram((wi)->l.program, 0, NULL, NULL, NULL, NULL);
	(wi)->l.kernel = clCreateKernel((wi)->l.program, "render", &err);
	if (ij == 0)
		free(program_source);
	return ((wi)->l.kernel);
}

cl_context	create_context(cl_uint *num_devices)
{
	cl_int			err;
	cl_device_id	*devices;
	cl_context		context;

	devices = malloc(1 * sizeof(cl_device_id));
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, devices, num_devices);
	context = clCreateContext(0, *num_devices, devices, NULL, NULL, &err);
	free(devices);
	return (context);
}
