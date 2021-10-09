
NAME	= minishell

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= minishell.h

SRCS	= main.c pipex.c redirect.c distributor.c get_next_line.c get_next_line_utils.c utils_env.c \
            blessed_cmd_maker.c blessed_dollar_pull.c blessed_ft_error.c blessed_init_env.c blessed_list_env.c \
            blessed_parser.c blessed_preparser.c blessed_quotes_killer_command.c blessed_quotes_killer_redirect.c \
            blessed_redirect_parser.c blessed_split_by_pipe.c blessed_preparser_quotes_pipe_redir.c blessed_env.c blessed_pwd_oldpwd.c


%.o: 	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(SRCS) $(HEADER)
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

# -L .brew/opt/readline/lib -I .brew/opt/readline/include
#-L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include