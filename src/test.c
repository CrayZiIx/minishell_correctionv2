#include "../inc/minishell.h"

void	check_string_redir2(char *s, int *i, int *t)
{
		if ((s[(*i)] == '>' && s[(*i) + 1]== '>') || (s[(*i)] == '<' && s[(*i) + 1]== '<'))
		{
			(*i) += 2;
			(*t) = 1;
		}
		else if (t == 0 && (s[(*i)] == '>' || s[(*i)] == '<' || s[(*i)] == '|'))
		{
			(*i) += 1;
			(*t) = 1;
		}
		else
			if (s[(*i)++] != ' ')
				(*t) = 0;
}

int	check_string_redir(char *s)
{
	int i;
	int t;

	i = 0;
	t = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '<' && s[i + 1] == '>')
			return (0);
		else if (t == 1 && ((s[i] == '>' || s[i]== '<')))
			return (1);
		check_string_redir2(s, &i, &t);
		
	}
	if (t)
		return (1);
	return (0);
}

int	check_string_redir_tab(char **s)
{
	int i = 0;

	while (s && s[i] && i <+ 15)
	{
		if (check_string_redir(s[i]))
			printf("s = [%s] and it's an error\n", s[i]);
		else
			printf("s = [%s] and it's an good\n", s[i]);
		i++;
	}
}

int main(void)
{
	char *str_test_tab[15];
	char str_test1[2] = ">";
	char str_test2[2] = "<";
	char str_test3[3] = ">>";
	char str_test4[3] = "<<";
	char str_test5[15] = "<<       s";
	char str_test6[11] = "        >>";
	char str_test7[5] = "<< <";
	char str_test8[9] = "<< >>eof";
	char str_test9[7] = "<<eof\0";
	char str_test10[7] = "| test";
	char str_test11[7] = "<< eof";
	char str_test12[9] = "<< eof |";
	char str_test13[9] = "<> test";
	char str_test14[9] = "\"< t\"est";
	char str_test15[10] = "<<>> test";
	/*--------------------------------*/
	str_test_tab[0] = str_test1;
	str_test_tab[1] = str_test2;
	str_test_tab[2] = str_test3;
	str_test_tab[3] = str_test4;
	str_test_tab[4] = str_test5;
	str_test_tab[5] = str_test6;
	str_test_tab[6] = str_test7;
	str_test_tab[7] = str_test8;
	str_test_tab[8] = str_test9;
	str_test_tab[9] = str_test10;
	str_test_tab[10] = str_test11;
	str_test_tab[11] = str_test12;
	str_test_tab[12] = str_test13;
	str_test_tab[13] = str_test14;
	str_test_tab[14] = str_test15;
	/*--------------------------------*/
	// (void)check_string_redir(str_test1);
	// (void)check_string_redir(str_test2);
	// (void)check_string_redir(str_test3);
	// (void)check_string_redir(str_test4);
	// (void)check_string_redir(str_test5);
	// (void)check_string_redir(str_test6);
	// (void)check_string_redir(str_test7);
	// (void)check_string_redir(str_test8);
	// (void)check_string_redir(str_test9);
	// (void)check_string_redir(str_test10);
	// (void)check_string_redir(str_test11);
	// (void)check_string_redir(str_test12);
	// (void)check_string_redir(str_test13);
	// (void)check_string_redir(str_test14);
	(void)check_string_redir_tab(str_test_tab);
	return (0);
}