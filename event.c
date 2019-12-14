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

double zoom(double start, double end, double zoomrate)
{
    return start + ((double)(end - start) * zoomrate);
}
double map(int n, double start1, double end1, double start2, double end2)
{
    return ((double)((n - start1) / (double)(end1 - start1))) * (end2 - start2) + start2;
}
int mouse_move(int x, int y, t_win *wi)
{
    //runCL(2000, 1000, wi);
    return (0);
}



int mouse_press(int key, int x, int y, t_win *wi)
{
    double zoomrate;
    int a = 0;
    if (key == 5)
    {
        zoomrate = 0.8;
        wi->max_iteration+=1;
       //printf("iteration == %d\n\n", wi->max_iteration);
    }
    else if (key == 4)
    {
        zoomrate = 1.0/0.8;
        wi->max_iteration+=1;
    }
    else
        a = 1;

    if (a == 0)
    {
        wi->mx = map(x, 0, 1000, wi->Remin, wi->Remax);
        wi->my = map(y, 0, 1000, wi->Immin, wi->Immax);
        printf("          mx == %.100f\n%d\n", wi->mx, key);
        printf("Before Remin == %.100f\n", wi->Remin);
        wi->Remin = zoom(wi->mx, wi->Remin, zoomrate);
        printf("          my == %.100f\n", wi->my);
        printf("       REmin == %.100f\n", wi->Remin);
        wi->Immin = zoom(wi->my, wi->Immin, zoomrate);
        printf("Immin == %.100f\n", wi->Immin);
        wi->Remax = zoom(wi->mx, wi->Remax, zoomrate);
      printf("Remax == %.100f\n", wi->Remax);
        wi->Immax = zoom(wi->my, wi->Immax, zoomrate);
       printf("Immax == %.100f\n\n\n", wi->Immax);

        //runCL(1000, 1000, wi);
    }
    return (0);
}
