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

char  *load_program_source(const char *filename)
{
	struct stat statbuf;
	int         fd;
	char        *source;

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

cl_kernel load_kernel_from_file(t_win *wi,cl_context context, const char *filename)
{
	static int  ij;
	int         err;
	static char *program_source;

	if (ij == 0)
	{
		program_source = load_program_source(filename);
		ij = 1;
	}
	(wi)->l.program = clCreateProgramWithSource(context, 1,
			(const char **)&program_source,
			NULL, &err);
	clBuildProgram((wi)->l.program, 0, NULL, NULL, NULL, NULL);
	(wi)->l.kernel = clCreateKernel((wi)->l.program, "render", &err);
	return ((wi)->l.kernel);
}

cl_context  create_context(cl_uint *num_devices)
{
	cl_int        err;
	cl_device_id  *devices;
  	cl_context    context;

	devices = malloc(1 * sizeof(cl_device_id));
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, devices, num_devices);
	context = clCreateContext(0, *num_devices, devices, NULL, NULL, &err);
	free(devices);
	return (context);
}
