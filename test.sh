static t_tok	*separator_token(char	*s, int *i)
{
	t_tok	*tok;

	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (NULL);
	if (s[*i] == '|')
	{
		*i += 1;
		if (s[*i] == '|')
		{
			tok->content = ft_strdup("||");
			tok->type = OR;
		}
		else
		{
			tok->content = ft_strdup("|");
			tok->type = PIPE;
		}
		return (tok);
	}
	else if (s[*i] == '&')
	{
		*i += 2;
		if (s[*i] == '&')
		{
			tok->content = ft_strdup("&&");
			tok->type = AND;
		}
		return (tok); } return (NULL);
}

static char	*get_tok_content(char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i] && s[*i] != '|' && s[*i] != '&')
	{
		if (s[*i] == '(')
		{
			skip_parentheses(s, i);
			continue ;
		}
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			skip_quotes(s, i, s[*i]);
			continue ;
		}
		*i += 1;
	}
	return (ft_substr(s, start, *i - start));
}

static t_tok	*get_next_tok(char	*s, int *i)
{
	t_tok	*tok;

	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!s[*i])
		return (NULL);
	tok = separator_token(s, i);
	if (tok)
		return (tok);
	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (NULL);
	else
	{
		tok->content = get_tok_content(s, i);
		if (!tok->content)
			return (free(tok), NULL);
		tok->type = BLOCK;
		return (tok);
	}
	return (NULL);
}

t_list	*tokenize(char	*prompt)
{
	t_list	*tok_list;
	t_tok	*tok;
	int		i;

	i = 0;
	tok_list = NULL;
	tok = get_next_tok(prompt, &i);
	while (tok)
	{
		ft_lstadd_back(&tok_list, ft_lstnew(tok));
		tok = get_next_tok(prompt, &i);
	}
	return (tok_list);
}