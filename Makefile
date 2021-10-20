NAME	= minishell

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= minishell.h

SRCS	=	main.c \
			main_utils.c \
			pipex.c \
			distributor.c \
\
			./redirect/redirect.c \
			./redirect/key_handler.c \
			./redirect/ft_chek_all_files.c \
\
			./built_ins/b-ins_pwd_export_unset.c \
			./built_ins/ft_cd.c \
			./built_ins/ft_echo.c \
			./built_ins/ft_exit.c \
			./built_ins/ft_exit_utils.c \
\
			./ft_realization/ft_realization.c \
			./ft_realization/ft_realization_daughter.c \
\
			./signals/signals.c \
\
			./env_export/utils_env.c \
			./env_export/blessed_init_env.c \
			./env_export/blessed_list_env.c \
			./env_export/blessed_env.c \
			./env_export/blessed_pwd_oldpwd.c \
			./env_export/blessed_shlvl_changing.c \
			./env_export/blessed_init_env_utils.c \
			./env_export/export_env_append_utils.c \
\
			./preparser/blessed_ft_error.c \
			./preparser/blessed_preparser.c \
			./preparser/blessed_preparser_quotes_pipe_redir.c \
\
			./parser/split_by_pipe/blessed_split_by_pipe.c \
            ./parser/redirect_parser/blessed_redirect_parser.c \
			./parser/redirect_parser/add_redirect.c \
			./parser/redirect_parser/redirect_cut_from_str.c \
			./parser/redirect_parser/flag_putter.c \
\
			./parser/dollar_pull/blessed_dollar_pull.c \
			./parser/dollar_pull/blessed_dollar_pull_utils.c \
			./parser/dollar_pull/dollar_pull_redirect/blessed_dollar_pull_redirect.c \
			./parser/dollar_pull/dollar_pull_redirect/blessed_dollar_pull_redirect_utils.c \
\
            ./parser/cmd_maker/blessed_cmd_maker.c \
            ./parser/blessed_parser.c \
			./parser/quotes_killer/blessed_quotes_killer_command.c \
			./parser/quotes_killer/blessed_quotes_killer_redirect.c \
			./parser/quotes_killer/blessed_quotes_killer_utils.c \
			./parser/free_utils/blessed_free_whole_project.c \
			./parser/free_utils/list_free_utils.c \
			


%.o: 	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(SRCS) $(HEADER)
			$(MAKE) all -C ./libft
			cp libft/libft.a ./$(NAME)
			$(CC) $(SRCS) $(CFLAGS) -g ./libft/libft.a -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -o ${NAME} -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
	
all: $(NAME)
	
clean:
	$(MAKE) clean -C ./libft

fclean: clean	
	$(MAKE) fclean -C ./libft
	-rm -rf $(NAME)
	
re:		fclean all

.PHONY: all clean fclean re