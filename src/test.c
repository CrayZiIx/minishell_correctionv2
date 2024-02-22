#include "../inc/minishell.h"


int falsed(void)
{
	return (0, 1);
}

int	check_string_redir(char *s)
{
	int i;
	int t;

	i = 0;
	t = 0;
	while (s[i] != '\0')
	{
		if (t == 1 && (s[i] == '>' || s[i]== '<'))
			return (printf("error\n"), 1);
		if ((s[i] == '>' && s[i + 1]== '>') || (s[i] == '<' && s[i + 1]== '<'))
		{
			i += 2;
			t = 1;
		}
		else if (t == 0 && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
		{
			i += 1;
			t = 1;
		}
		else
			if (s[i++] != ' ')
				t = 0;
	}
	// return (t);
	if (t)
		return (printf("error\n"), 1);
	return (printf("good\n"),0);
}

int main(void)
{
	char str_test1[2] = ">";
	char str_test2[2] = "<";
	char str_test3[3] = ">>";
	char str_test4[3] = "<<";
	char str_test5[11] = "<<        ";
	char str_test6[11] = "        >>";
	char str_test7[5] = "<< <";
	char str_test8[9] = "<< >>eof";
	char str_test9[7] = "<<eof\0";
	char str_test10[2] = "|";
	char str_test11[7] = "<< eof";
	char str_test12[9] = "<< eof |";
	(void)check_string_redir(str_test1);
	(void)check_string_redir(str_test2);
	(void)check_string_redir(str_test3);
	(void)check_string_redir(str_test4);
	(void)check_string_redir(str_test5);
	(void)check_string_redir(str_test6);
	(void)check_string_redir(str_test7);
	(void)check_string_redir(str_test8);
	(void)check_string_redir(str_test9);
	(void)check_string_redir(str_test10);
	(void)check_string_redir(str_test11);
	(void)check_string_redir(str_test12);
	return (0);
}