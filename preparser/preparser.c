/*
1) Проверим кавычки, все ли закрыты
2) Проверяем пайпы
3) Проверяем редиректы
*/

#include "preparser.h"

int	preparser(char *str) // Смотрим закрыты ли все кавычки и пайпы и редиректы
{
	int	i;
	int j = 0;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			check_quotes(str, &i);
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			check_pipe_redir(str, &i);
		if (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			i++;
	}
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	// char *str = "'l''s' \"-l'a\" | wc '-\"l'";
	char *str = "echo bash | wc -l | wc -l";
	// char *str = "wc -l | ls '\"-l|a\"' \"|\" < \"<> | |< > |\"5 | grep";
	// char *str = " > '1>         ' \"ec'ho\" '$LOGNA\"MEasd' << 8'asdasd'''''\"ls'd\"228'' |> 2 wc -l < \"$LOGNAME\" $PWD$PW>1 > \"ls'd\" $ASDQWE | $PASDFDSDFERQ cat $LOGNAME \"$P<W\" |  \">'>\" 3>>5>> 6'bash' eihei $PWD '$PWD' <500";
	// char *str = "> 1 echo '$LOGNAMEasd' << 8";
	// char *str = "echo bash > > | <";
	// argv++;
	// char *str = *argv;
	// printf("%s\n", str);
	// char *str = "ls -la >4|>3";
	int i = -1;
	preparser(str);
	// usleep(10000);
	parser(str, env);
	// usleep(10000);
	// while (env[++i])
		// printf("%s\n", env[i]);
		
	// int i = -1;
	// while (str[++i])
	// {
	// 	if (str[i] == '"')
	// 		printf("%d\n", i);
	// }
	// usleep(10000);
	// while (1);
	return (0);
}
