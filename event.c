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
    wi->mx = map(x, 434, 820 + 434, wi->Remin, wi->Remax);
    wi->my = map(y, 181, 608 + 181, wi->Immin, wi->Immax);
    if (wi->al && wi->h == 0 && wi->jl == 0)
    {
        mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->imgstr, 0, 0);
        runCL(wi);
        mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img4str, x - 25, y - 25);
    }
    else if(wi->h == 0 && wi->jl == 0)
       runCL(wi);
    return (0);
}

// void fractalpha(t_win *wi)
//  {
//      mlx_clear_window(wi->mlx_ptr, wi->win_ptr);
//   while (cl < 1100)
//   {
//     cli = 0;
//     while (cli < 1100)
//     {
//       h = 0;
//       while (h<1)
//       {
//         oh = cli * 4 + cl * width * 4;
//         mlx_string_put(wi->mlx_ptr, wi->win_ptr, cli, cl, (wi->line[oh] << 8) + (wi->line[oh + 1] << 16) + (wi->line[oh + 2]), "h");
//         cli += 11;
//         h++;
//       }
//     }
//     cl += 20;
//   }
//  }
int key_press(int key, t_win *wi)
{
    double temp;
    wi->a = 0;
    if (key < 92 && key > 82)
    {
        init(wi);
        wi->key = key - 82;
    }
    else if (key == 53)
        exit(0);
    else if (key == 69)
        wi->max_iteration += 10;
    else if (key == 78)
        wi->max_iteration -= 10;
    else if (key == 0)
        wi->p += 1;
    else if (key == 1)
        wi->p -= 1;
    else if (key == 15)
        wi->r += 1;
    else if (key == 5)
        wi->g += 1;
    else if (key == 11)
        wi->b += 1;
    else if (key == 6)
        wi->al = !wi->al;
    else if (key == 123)
    {
        temp = 0.1 * (wi->Remax -  wi->Remin);
        wi->Remax += 0.1 * (wi->Remax -  wi->Remin);
        wi->Remin += temp;
    }
    else if (key == 124)
    {
        temp = 0.1 * (wi->Remax -  wi->Remin);
        wi->Remax -= 0.1 * (wi->Remax -  wi->Remin);
        wi->Remin -= temp;
    }
    else if (key == 126)
    {
         temp = 0.1 * (wi->Immax -  wi->Immin);
        wi->Immax += 0.1 * (wi->Immax -  wi->Immin);
        wi->Immin += temp;
    }
    else if (key == 125)
    {
        temp = 0.1 * (wi->Immax -  wi->Immin);
        wi->Immax -= 0.1 * (wi->Immax -  wi->Immin);
        wi->Immin -= temp;
    }
    else if (key == 4)
        wi->h = 0;
    else
        wi->a = 1;
    if (wi->a == 0 && wi->h == 0)
    {
        mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->imgstr, 0, 0);
        runCL(wi);
    }
    if (key == 82)
        mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img2str, 0, 0);
    return 0;
}

int mouse_press(int key, int x, int y, t_win *wi)
{

    if (wi->h == 0)
    {
        wi->a = 0;
        if (key == 5)
        {
            wi->zoomrate = 0.9;
            wi->max_iteration += 1;
        }
        else if (key == 4)
        {
            wi->zoomrate = 1.0 / 0.9;
            wi->max_iteration -= 1;
        }
        else if (key == 2)
        {
            wi->jl = !wi->jl;
        }
        else if (key == 1 && 360 < x && x < 436  && 959 < y && y < 1053)
            exit(0);
        else if (key == 1 && 1255 < x && x < 1527  && 181 < y && y < 789)
        {   
            init(wi);
            wi->key = ( (x - 1254) / 137) * 4 + (y - 171) / 152 + 1;
        }
        else
            wi->a = 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
         if (key == 1 && x > 437 && x < 452 && y > 171 && y < 181)
         {
            mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img2str, 0, 0);
            wi->a = 1;
         }
        else if (key == 1 && x > 439 && x < 565 && y > 270 && y < 283)
        {
            mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img3str, 0, 0);
            wi->h = 1;
        }

        
        if (wi->a == 0)
        {
            wi->mx = map(x, 434, 820 + 434, wi->Remin, wi->Remax);
            wi->my = map(y, 181, 608 + 181, wi->Immin, wi->Immax);
            if (key == 5 || key == 4)
            {
            wi->Remin = zoom(wi->mx, wi->Remin, wi->zoomrate);
            wi->Immin = zoom(wi->my, wi->Immin, wi->zoomrate);
            wi->Remax = zoom(wi->mx, wi->Remax, wi->zoomrate);
            wi->Immax = zoom(wi->my, wi->Immax, wi->zoomrate);
            }
            mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->imgstr, 0, 0);
            runCL(wi);
            if (wi->al)
                mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img4str, x - 25, y - 25);
        }
       
    }
    return (0);
}
