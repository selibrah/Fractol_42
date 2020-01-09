/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhndl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:19:45 by selibrah          #+#    #+#             */
/*   Updated: 2020/01/08 18:19:58 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

void	printmsg(int i)
{
	ft_putstr("Usage : ./fractol\n1 - Mandelbort\
			\n2 - Sword\n3 - Lightning\
			\n4 - Multibort\n5 - Tricorn\n6 - Burning Ship\
			\n7 - Julia\n8 - Multicorn\n");
	exit(0);
}

void	freecl(t_win *wi)
{
	clFinish((wi)->l.cmdqu);
	clReleaseKernel((wi)->l.kl);
	clReleaseProgram((wi)->l.program);
	clReleaseMemObject((wi)->l.img);
	clReleaseMemObject((wi)->l.inpts);
	clReleaseCommandQueue((wi)->l.cmdqu);
	free(wi->inpt);
}

void	frexit(t_win *wi)
{
	clReleaseContext((wi)->l.cxt);
	mlx_destroy_image(wi->mlx_ptr, wi->img_ptr2);
	mlx_destroy_image(wi->mlx_ptr, wi->img_ptr3);
	mlx_destroy_image(wi->mlx_ptr, wi->img_ptr4);
	mlx_destroy_image(wi->mlx_ptr, wi->img_ptr5);
	mlx_destroy_image(wi->mlx_ptr, wi->img_ptr);
	mlx_destroy_window(wi->mlx_ptr, wi->win_ptr);
	exit(0);
}
