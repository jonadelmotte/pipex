SRCS		=	./src/main.c\
				./src/pipex_utils.c\
				./src/split_pipex.c\

SRCS_BONUS	=	./src_bonus/pipex_bonus.c\
				./src_bonus/pipex_utils_bonus.c\
				./src_bonus/gnl_pipex.c\
				./src_bonus/split_pipex.c\

OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
NAME		= pipex
NAME_BONUS	= pipex_bonus

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

RM			= rm -f

all: $(NAME) bonus

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus: $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re