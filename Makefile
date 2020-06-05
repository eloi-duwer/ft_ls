SRC_NAME = main.c \
	entry_control.c \
	print_error_funcs.c \
	args_parsing.c \
	sort_funcs.c \
	helpers.c \
	print_entries_funcs.c \

NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -g -I./include -I./libft/include

SRCF = ./src/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

LFT = libft/libft.a

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -g -L./libft -lft

$(LFT):
	make -C ./libft

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.c)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
