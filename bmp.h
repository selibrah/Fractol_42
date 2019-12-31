/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:28 by selibrah          #+#    #+#             */
/*   Updated: 2019/12/10 11:15:30 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <OpenCL/OpenCL.h>
#include <stdio.h>
#include <stdlib.h>
#include <OpenCL/OpenCL.h>
#include "cl_helper.h"

typedef struct s_opncl
{
    cl_kernel kl;
    cl_command_queue cmdqu;
    cl_context cxt;
    cl_int err;
    cl_uint ndvs;
    cl_device_id dvs;
    int bytesPerLine;
    const char *fl;
    size_t rtsz;
    size_t bfsz;
    cl_mem img;
    cl_mem inpts;
	cl_program  program;
	cl_kernel   kernel;
} t_opncl;

typedef struct s_win
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    void *img_ptr2;
    void *img_ptr3;
    char *img2str;
    void *img_ptr4;
    char *img3str;
    void *img_ptr5;
    char *img4str;
    char *imgstr;
    double mx;
    double my;
    char *line;
    char *rgb;
    int winx;
    int winy;
    double p;
    int max_iteration;
    int bpp;
    int size_line;
    int endian;
    double Remin;
    double Immin;
    double Remax;
    double Immax;
    int key;
    double r;
    double g;
    double b;
    int al;
    int a;
    int et;
    int het;
    int h;
    int u;
    int jl;
    double *inpt;
    double zoomrate;
    size_t device_work_size[2];
    t_opncl l;

} t_win;



int write_bmp(const char *filename, int width, int height, char *rgb, t_win *wi);
int mouse_move(int x, int y, t_win *wi);
int		mouse_press(int key,int x, int y, t_win *wi);
int runCL(t_win *wi);
double map(int n, double start1, double end1, double start2, double end2);
int key_press(int key , t_win *wi);
void init(t_win *wi);
void opnclinit(t_win *wi);
cl_kernel load_kernel_from_file(t_win *wi,cl_context context, const char *filename);