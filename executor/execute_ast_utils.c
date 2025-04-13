/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:07:24 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 22:03:06 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_builtin(char **args)
{
	if (!args || !*args)
		return (1);
	if (args && args[0] && ft_strncmp(args[0], "echo", 5) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "pwd", 4) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "cd", 3) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "export", 7) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "env", 4) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "unset", 6) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "exit", 5) == 0)
		return (0);
	return (-1);
}

int	run_builting(t_msh *msh, char **args, char **expanded_args)
{
	if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], \
	"echo", 5) == 0)
		return (ft_echo(expanded_args));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], \
	"pwd", 4) == 0)
		return (ft_pwd(msh));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], \
	"cd", 3) == 0)
		return (ft_cd(expanded_args[1], msh));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], \
	"env", 3) == 0)
		return (ft_env(msh->env));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], \
	"unset", 6) == 0)
		return (ft_unset(msh->env, expanded_args));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], \
	"export", 7) == 0)
		return (ft_export(args, msh));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], \
	"exit", 5) == 0)
		ft_exit(msh, expanded_args);
	return (1);
}

int	handle_unexistant_path_var(char **args, char **env)
{
	if (access(args[0], F_OK) == 0)
	{
		if (access(args[0], X_OK) == 0)
			return (execute_simple_cmd(ft_strdup(args[0]), args, env));
		ft_printf_error(args[0], ": ", "Permission denied", "\n");
		free_2d_array(env);
		free_2d_array(args);
		return (126);
	}
	ft_printf_error(args[0], ": ", strerror(errno), "\n");
	free_arr(args);
	free_2d_array(env);
	return (127);
}

static int	init_and_check(t_msh *msh, t_ast *ast, char ***args, char ***env)
{
	if (!ast || !ast->data)
		return (1);
	(1) && (*args = (char **)ast->data);
	if ((*args)[0] && (*args)[0][0] == '\0')
		return (0);
	(1) && (*env = make_env(msh->env), *args = expand((char **)ast->data, msh));
	if (!(*args)[0])
		return (free_2d_array(*args), free_2d_array(*env), 0);
	if ((*args)[0] && !(*args)[0][0])
		return (ft_printf_error((*args)[0], ": ", "command not found", "\n"), \
				free_2d_array(*args), free_2d_array(*env), 1);
	return (-1);
}

int	execute_word(t_msh *msh, t_ast *ast)
{
	char	**args;
	char	*path;
	char	*path_var;
	int		i;
	char	**env;

	i = init_and_check(msh, ast, &args, &env);
	if (i != -1)
		return (i);
	i = 0;
	path_var = get_from_env("PATH", msh->env);
	if (!path_var)
		return (handle_unexistant_path_var(args, env));
	path = get_cmd_path(args[0], env, &i);
	if (path)
		return (execute_simple_cmd(path, args, env));
	else if (i)
		ft_printf_error(args[0], ": ", "command not found", "\n");
	return (free_2d_array(env), free_arr(args), 127);
}
