#include <ft_ls.h>

void	parse_subargs(t_context *ctx, char *args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (args[i] == 'l')
			ctx->long_format = true;
		else if (args[i] == 'a')
			ctx->all = true;
		else if (args[i] == 'r')
			ctx->sort_reverse = true;
		else if (args[i] == 't')
			ctx->comp_func = &sort_by_date;
		else if (args[i] == 'R')
			ctx->recursive = true;
		else
			print_error_details("ls: invalid option: -%.1s\n", &(args[i]), true);
		++i;
	}
}

void	parse_args(int ac, char **av, t_context *ctx)
{
	int		i;
	t_bool	stop_parsing;
	t_bool	print_default_dir;

	i = 0;
	stop_parsing = false;
	print_default_dir = true;
	while (++i < ac)
	{
		if (stop_parsing == true || av[i][0] != '-')
		{
			add_entry_end(ctx, &ctx->entries, av[i], av[i]);
			print_default_dir = false;
		}
		else if (ft_strcmp(av[i], "--") == 0)
			stop_parsing = true;
		else
			parse_subargs(ctx, av[i]);
	}
	if (print_default_dir == true)
		add_entry_end(ctx, &ctx->entries, ".\0", ".\0");
}
