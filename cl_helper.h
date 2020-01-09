/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_helper.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selibrah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 19:09:35 by selibrah          #+#    #+#             */
/*   Updated: 2020/01/08 19:15:22 by selibrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CL_HELPER_H
# define _CL_HELPER_H
# include <OpenCL/OpenCL.h>

char		*load_program_source(const char *filename);
cl_context	create_context(cl_uint *num_devices);
void		check_succeeded(char *message, cl_int err);

#endif
