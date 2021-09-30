#include "minishell.h"

int	ft_error(int code)
{
	if (code == 1)
	{
		printf("Minishell: error: unclosed quotes detected\n");
		// exit (1);
	}
	if (code == 2)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		// exit (1);
	}
	if (code == 3)
	{
		printf("Minishell: error: unclosed pipe detected\n"); //syntax error near unexpected token `<'
		// exit (1);
	}
	if (code == 4)
	{
		printf("Minishell: syntax error near unexpected token `<'\n"); //syntax error near unexpected token `<'
		// exit (1);
	}
	if (code == 5)
	{
		printf("Minishell: syntax error near unexpected token `newline'\n"); //syntax error near unexpected token `<'
		// exit (1);
	}
	if (code == 6)
	{
		printf("Minishell: syntax error near unexpected token `>'\n"); //syntax error near unexpected token `<'
		// exit (1);
	}
	return (0);
}
