
NAME	= minishell

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= minishell.h

SRCS	= main.c pipex.c redirect.c distributor.c get_next_line.c get_next_line_utils.c

%.o: 	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(SRCS) $(HEADER)
			$(MAKE) bonus -C ./libft
			$(MAKE) all -C ./libft
			cp libft/libft.a ./$(NAME)
			$(CC) $(SRCS) ./libft/libft.a -lreadline -o ${NAME}
	
all: $(NAME)
	
clean:
	$(MAKE) clean -C ./libft

fclean: clean	
	$(MAKE) fclean -C ./libft
	-rm -rf $(NAME)
	
re:		fclean all

.PHONY: all clean fclean re
