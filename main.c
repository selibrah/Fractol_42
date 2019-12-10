/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:05:08 by selibrah          #+#    #+#             */
/*   Updated: 2019/12/10 11:05:14 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>

#include <OpenCL/OpenCL.h>

#include "bmp.h"
#include "cl_helper.h"

int runCL(int width, int height, t_win *wi)
{
  static int init = 0;
  static cl_kernel kernel;

  static cl_command_queue cmd_queue;
  static cl_context context;

  static cl_int err = 0;
  static cl_uint num_devices = 0;
  static cl_device_id devices[16];
  int bytesPerLine;

  size_t returned_size = 0;

  // Multiply by 3 here, since we need red, green and blue for each pixel
  static size_t buffer_size;

  cl_mem image;
  if (init == 0)
  {
    buffer_size = sizeof(char) * width * height * 4;
    context = create_context(&num_devices);
    if (num_devices == 0)
    {
      printf("No compute devices found\n");
      return -1;
    }
    print_debug_info(context);

    err = clGetContextInfo(context, CL_CONTEXT_DEVICES, sizeof(cl_device_id) * 16,
                           &devices, NULL);
    check_succeeded("Getting context info", err);
    init = 1;
  }

  
    cmd_queue = clCreateCommandQueue(context, devices[0], 0, &err);
    check_succeeded("Creating command queue", err);


  // Mark this write only, since the kernel does not have to read the image it
  // is writing. I am not sure if this has any performance benefit.
  image = clCreateBuffer(context, CL_MEM_WRITE_ONLY, buffer_size, NULL, &err);
  check_succeeded("Creating buffer", err);

  // Load the program source from disk
  const char *filename = "mandelbrot.cl";
  kernel = load_kernel_from_file(context, filename);

  // Now setup the arguments to our kernel
  // In our case, we just need to give it a pointer to the image
  int mx = wi->mx;

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &image);
  err |= clSetKernelArg(kernel, 1, sizeof(double), &wi->mx);
  err |= clSetKernelArg(kernel, 2, sizeof(double), &wi->my);
  err |= clSetKernelArg(kernel, 3, sizeof(double), &wi->Remin);
  err |= clSetKernelArg(kernel, 4, sizeof(double), &wi->Immin);
  err |= clSetKernelArg(kernel, 5, sizeof(double), &wi->Remax);
  err |= clSetKernelArg(kernel, 6, sizeof(double), &wi->Immax);
  err |= clSetKernelArg(kernel, 7, sizeof(int), &wi->max_iteration);
  check_succeeded("Setting kernel arg", err);

  // Run the calculation by enqueuing it and forcing the
  // command queue to complete the task
  // To support multiple compute devices, need to split this up
  // among all of them. Easiest way to split up is block alloc.
  //
  // Assuming that num_devices divides width and height evenly

  size_t device_work_size[2] = {width, height};
  size_t local_work_size = 25;
  
  err = clEnqueueNDRangeKernel(cmd_queue, kernel, 2, NULL,
                                 device_work_size, NULL, 0, NULL, NULL);
  check_succeeded("Running kernel", err);

    // Non-blocking read, so we can continue queuing up more kernels
  err = clEnqueueReadBuffer(cmd_queue, image, CL_FALSE, 0,
                              buffer_size,
                              wi->line, 0, NULL, NULL);
  check_succeeded("Reading buffer", err);
  clFinish(cmd_queue);
 

  // Now write the file
  // wi->rgb = host_image;
  //write_bmp("output.bmp", width, height, host_image,wi);
  mlx_put_image_to_window(wi->mlx_ptr, wi->win_ptr, wi->img_ptr, 0, 0);

  // Release OpenCL objects
  clReleaseMemObject(image);
  clReleaseCommandQueue(cmd_queue);
  clReleaseContext(context);

  return CL_SUCCESS;
}

int main(int argc, const char *argv[])
{
  t_win wi;

  wi.winx = 1000;
  wi.winy = 1000;
  wi.mlx_ptr = mlx_init();
  wi.win_ptr = mlx_new_window(wi.mlx_ptr, wi.winx, wi.winy, "Best Fractol Ever");
  wi.img_ptr = mlx_new_image(wi.mlx_ptr, wi.winx, wi.winy);
  wi.mx = 0;
  wi.my = 0;
  wi.Remax = 2;
  wi.Remin = -2;
  wi.Immax = 2;
  wi.Immin = -2;
  wi.max_iteration = 1000;

  wi.line = mlx_get_data_addr(wi.img_ptr, &wi.bpp, &wi.size_line, &wi.endian);
  runCL(1000, 1000, &wi);
  mlx_hook(wi.win_ptr, 6, 0, mouse_move, &wi);
  mlx_hook(wi.win_ptr, 4, 0, mouse_press, &wi);
  mlx_loop(wi.mlx_ptr);

  return 0;
}
