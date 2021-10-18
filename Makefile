
NAME	= minishell

#CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= minishell.h

SRCS	=	main.c pipex.c redirect.c distributor.c get_next_line.c get_next_line_utils.c ./env_export/utils_env.c \
            blessed_cmd_maker.c blessed_dollar_pull.c blessed_dollar_pull_redirect.c blessed_ft_error.c ./env_export/blessed_init_env.c ./env_export/blessed_list_env.c \
            ./parser/blessed_parser.c ./parser/list_free_utils.c ./preparser/blessed_preparser.c blessed_quotes_killer_command.c blessed_quotes_killer_redirect.c \
            blessed_redirect_parser.c blessed_split_by_pipe.c ./preparser/blessed_preparser_quotes_pipe_redir.c ./env_export/blessed_env.c ./env_export/blessed_pwd_oldpwd.c \
			blessed_free_whole_project.c ./env_export/blessed_shlvl_changing.c ./env_export/blessed_init_env_utils.c


%.o: 	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(SRCS) $(HEADER)
			$(MAKE) all -C ./libft
			cp libft/libft.a ./$(NAME)
			$(CC) $(SRCS) -g ./libft/libft.a -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -o ${NAME} -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
	
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
