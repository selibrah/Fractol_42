# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selibrah <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 11:04:39 by selibrah          #+#    #+#              #
#    Updated: 2019/12/10 11:16:29 by selibrah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = gcc
CFLAGS =
MLX_PATH = mlx
OPENCL = -framework OpenCL -lmlx  -L  $(MLX_PATH) -I $(MLX_PATH)include -framework OpenGL -framework AppKit -lz

all: mandelbrot

mandelbrot: main.c event.o cl_helper.o
	$(C) $(CFLAGS) $(OPENCL) -o mandelbrot main.c event.o cl_helper.o 

event.o: event.c bmp.h
	$(C) $(CFLAGS) -c event.c

cl_helper.o: cl_helper.c cl_helper.h
	$(C) $(CFLAGS) -c cl_helper.c


clean:
	rm -f mandelbrot output.bmp *.o
