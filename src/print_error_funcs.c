#include <ft_ls.h>

void		print_error(char *str, t_bool should_exit)
{
	ft_fdprintf(2, str);
	if (should_exit == true)
		exit(2);
}

void		print_error_details(char *str, char *details, t_bool should_exit)
{
	ft_fdprintf(2, str, details);
	if (should_exit == true)
		exit(2);
}

void		print_errno(t_context *ctx, char *str, t_bool should_exit)
{
	perror(str);
	ctx->return_code = 1;
	if (should_exit)
		exit(2);
}
