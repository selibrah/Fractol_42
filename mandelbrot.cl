
/*# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mandelbrot.cl                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selibrah <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 11:07:15 by selibrah          #+#    #+#              #
#    Updated: 2019/12/10 11:09:48 by selibrah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #*/

int index(int x, int y, int width)
{
    return 4 * width * y + x * 4;
}

double map(int n, double start1, double end1, double start2, double end2)
{
    return ((double)((n - start1) / (double)(end1 - start1))) * (end2 - start2) + start2;
}

double mapX(double x, double Remin, double Remax)
{
    return x * (Remax - Remin) + Remin;
}

double mapY(double y, double Immin, double Immax)
{
    return y * (Immax - Immin) + Immin;
}

double multipx(double x, double y, double x1, double y1)
{
    return x * x1 - y * y1; 
}
double multipy(double x, double y, double x1, double y1)
{
    return x * y1 + x1 * y;
}
__kernel void render(__global char *out, __global double *inputs)
{
    int x_dim = get_global_id(0);
    int y_dim = get_global_id(1);
    size_t width = get_global_size(0);
    size_t height = get_global_size(1);
    int idx = index(x_dim, y_dim, width);
     double x_origin = (double)mapX((double)x_dim / width, inputs[6], inputs[8]);
    double y_origin = (double)mapY((double)y_dim / height, inputs[7], inputs[9]);
    double x = x_origin;
    double y = y_origin;
   if (inputs[10] == 8 || inputs[10] == 9)
   {
        x_origin = inputs[0];
        y_origin = inputs[1];
   }
    int iteration = 0;
    double xtemp;
    double ytemp;
    double x1 = x;
    double y1 = y;
    double teta = 0;
    double r = 0;
    int p = 0;
    
    
    while (iteration < inputs[12])
    {
        
        if (inputs[10] == 5 || inputs[10] == 4 || inputs[10] == 7)
        {
            if (inputs[10] == 4)
            {
                x = x >= 0 ? x : -x;
                y = y >= 0 ? y : -y;
            }
           r = pow(x * x + y * y, inputs[11] / 2.0);
            if (inputs[10] == 7)
                teta = atan2(x, y);
            else
                teta = atan2(y, x);
            x = r * cos(inputs[11] * teta) + x_origin;
            y = r * sin(inputs[11] * teta) + y_origin;
        }
        else if (inputs[10] == 1 || inputs[10] == 6 || inputs[10] == 8 || inputs[10] == 9)
        {
            if (inputs[10] == 6)
            {
                x = x >= 0 ? x : -x;
                y = y >= 0 ? y : -y;
            }
            p = 0;
            while(p <= inputs[11])
            {
                xtemp = multipx(x, y, x1, y1);
                ytemp = multipy(x, y, x1, y1);
                x1 = xtemp;
                y1 = ytemp;     
                p++;
            }
            x1 = xtemp + x_origin;
            y1 = ytemp + y_origin;
            y = ytemp + y_origin;
            x = xtemp + x_origin;
        }
        else if (inputs[10] == 2)
        {
            xtemp = x_origin * x_origin * x_origin - 3 * x_origin * y_origin * y_origin;
            y_origin = 3 * x_origin * x_origin * y_origin - y_origin * y_origin * y_origin;
            x_origin = xtemp;
            xtemp = x * x - y * y;
            y = 2 * x * y + y_origin;
            x = xtemp + x_origin - 1.401155;
        }
        else if (inputs[10] == 3)
        {
            xtemp = (double)(x * x_origin + y * y_origin) / (x_origin * x_origin + y_origin * y_origin);
            y = (double)(-x * y_origin + y * x_origin) / (x_origin * x_origin + y_origin * y_origin);
            x = xtemp;
            //xtemp = cosh(-y) * cos(x);
            //y = sinh(-y) * sin(x);
            x = xtemp;
        }
        if (x * x + y * y > 4)
            break;
        iteration++;
    }

    if (iteration == inputs[12])
    {
        out[idx] = 0;
        out[idx + 1] = 0;
        out[idx + 2] = 0;
        out[idx + 3] = 0;
    }
    else
    {
        out[idx] = (iteration)*1.9 * inputs[4];
        out[idx + 1] = (iteration)*1.7 * inputs[3];
        out[idx + 2] = (iteration)*1.4 * inputs[2];
        out[idx + 3] = 0;
    }
}
