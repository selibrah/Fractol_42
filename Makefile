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

NAME = Fractol
C = gcc
MLX_PATH = mlx
OBJ =  event.o cl_helper.o errorhndl.o
OPENCL = -framework OpenCL -lmlx  -L  $(MLX_PATH) -I $(MLX_PATH)include -framework OpenGL -framework AppKit -lz

all: $(NAME)

$(NAME): main.c $(OBJ)
	$(C) $(CFLAGS) $(OPENCL) -o mandelbrot main.c $(OBJ)

event.o: event.c bmp.h
	$(C) $(CFLAGS) -c event.c

cl_helper.o: cl_helper.c cl_helper.h bmp.h
	$(C) $(CFLAGS) -c cl_helper.c

errorhndl.o: errorhndl.c bmp.h
	$(C) $(CFLAGS) -c errorhndl.c
clean:
	rm -f mandelbrot output.bmp *.o
