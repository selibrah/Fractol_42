/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:04:46 by selibrah          #+#    #+#             */
/*   Updated: 2019/12/10 11:04:47 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

double interpolate(double start, double end, double interpolation)
{
    return start + ((double)(end - start) * interpolation);
}
int mouse_move(int x, int y, t_win *wi)
{
    runCL(1000, 1000, wi);
    return (0);
}

double map(int n, double start1, double end1, double start2, double end2)
{
    return ((double)((n - start1) / (double)(end1 - start1))) * (end2 - start2) + start2;
}

int mouse_press(int key, int x, int y, t_win *wi)
{
    double interpolation;
    int a = 0;
    if (key == 5)
    {
        interpolation = 0.8;
        wi->max_iteration++;
       // printf("iteration == %d\n\n", wi->max_iteration);
    }
    else if (key == 4)
    {
        interpolation = 1/0.5;
        wi->max_iteration--;
    }
    else
        a = 1;

    if (a == 0)
    {
        wi->mx = map(x, 0, 1000, wi->Remin, wi->Remax);
        wi->my = map(y, 0, 1000, wi->Immin, wi->Immax);
        
        wi->Remin = interpolate(wi->mx, wi->Remin, interpolation);
        //printf("REmin == %.20f\n", wi->Remin);
        wi->Immin = interpolate(wi->my, wi->Immin, interpolation);
       // printf("Immin == %.20f\n", wi->Immin);
        wi->Remax = interpolate(wi->mx, wi->Remax, interpolation);
     // printf("Remax == %.20f\n", wi->Remax);
        wi->Immax = interpolate(wi->my, wi->Immax, interpolation);
       // printf("Immax == %.20f\n\n\n", wi->Immax);

        runCL(1000, 1000, wi);
    }
    return (0);
}
