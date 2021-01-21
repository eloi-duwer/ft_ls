/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:10:22 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/21 20:20:16 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		print_error(char *str, bool should_exit)
{
	ft_fdprintf(2, str);
	if (should_exit == true)
		exit(2);
}

void		print_error_details(char *str, char *details, bool should_exit)
{
	ft_fdprintf(2, str, details);
	if (should_exit == true)
		exit(2);
}

void		print_errno(t_context *ctx, char *str, bool should_exit)
{
	perror(str);
	ctx->return_code = 1;
	if (should_exit)
		exit(2);
}
