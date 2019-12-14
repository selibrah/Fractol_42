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



#include <mlx.h>
typedef struct s_win
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    double mx;
    double my;
    char *line;
    char *rgb;
    int winx;
    int winy;
    int max_iteration;
    int bpp;
    int size_line;
    int endian;
    double Remin;
    double Immin;
    double Remax;
    double Immax;

} t_win;

int write_bmp(const char *filename, int width, int height, char *rgb, t_win *wi);
int mouse_move(int x, int y, t_win *wi);
int		mouse_press(int key,int x, int y, t_win *wi);
int runCL(int width, int height, t_win *wi);
double map(int n, double start1, double end1, double start2, double end2);
