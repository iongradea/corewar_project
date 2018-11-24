/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 19:33:21 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void			init_get_inst_sub(char ***tab, char **line, t_inst *inst)
{
	DEBUG ? ft_printf("launching init_get_inst_sub ...\n") : DEBUG;
	ft_clean_comment(line);
	ft_clean_sp(line);
	ft_strcpy(inst->line, *line);
	*tab = ft_strsplit(*line);
}

/*
** DEBUG ? ft_printf("launching get_inst_sub ...\n") : DEBUG;
** DEBUG ? prt_tab(tab) : DEBUG;
*/

static int			get_inst_sub(char *line, t_inst *inst)
{
	char			**tab;
	int				index;
	int				i;

	index = 0;
	i = -1;
	DEBUG ? ft_printf("launching get_inst_sub ...\n") : DEBUG;
	init_get_inst_sub(&tab, &line, inst);
	if (!ft_arrlen(tab))
		return (EXIT_SUCCESS);
	ft_ch_err_lab(tab[0]) ? exit(ERROR_MSG("syntax error\n")) : true;
	if (ft_ch_rm_lab_c(&tab[0]) && (index = 1))
		inst->label = ft_strtrim(tab[0]);
	ft_arrlen(tab) < 2 ? exit(ERROR_MSG("syntax error\n")) : true;
	!ft_ch_opcode(tab[index]) ? exit(ERROR_MSG("syntax error\n")) : true;
	inst->opcode = op_tab[ft_ret_opcode(tab[index])].opcode;
	if (ft_arrlen(tab) - index >
		OPCODE + op_tab[ft_ret_opcode(tab[index])].nb_max_par)
		exit(ERROR_MSG("Lexical error, too many parameters\n"));
	while (((++i + index) < ft_arrlen(tab)) && tab[i + index])
		inst->args[i] = ft_strtrim(tab[i + index]);
	ft_free_tab(tab);
	return (EXIT_SUCCESS);
}

static void 		get_inst_annex(t_inst *new, t_inst *tmp, t_inst **inst)
{
	if (!tmp)
		*inst = new;
	else
	{
		tmp->n = new;
		new->p = tmp;
	}
}

int					get_inst(char *line, t_inst **inst, t_header *head)
{
	t_inst			*new;
	t_inst			*tmp;
	static int		flag = FL_STANDARD;

	tmp = *inst;
	DEBUG ? ft_printf("tmp : %p\n", tmp) : DEBUG;
	DEBUG ? ft_printf("launching get_inst ...\n") : DEBUG;
	if (ft_is_empty_line(line))
		return (EXIT_SUCCESS);
	else if ((IS_COMMENT_LINE(line) && !(flag & FL_COMMENT))
			|| (FL_COMMENT_LINES & flag))
		return (get_prog_comment(line, &flag, head));
	else if ((IS_NAME_LINE(line) && !(flag & FL_NAME))
			|| (FL_NAME_LINES & flag))
		return (get_prog_name(line, &flag, head));
	else if (ft_is_special_line(line))
		exit(ERROR_MSG("Lexical error\n"));
	DEBUG ? ft_printf("HERE_0\n") : DEBUG;
	//DEBUG ? ft_printf("tmp : %p\n", tmp) : DEBUG;
	//DEBUG ? ft_printf("tmp->n : %p\n", tmp->n) : DEBUG;
	DEBUG ? prt_inst(*inst) : DEBUG;
	if (tmp && tmp->n)
		while (tmp->n)
			tmp = tmp->n;
	DEBUG ? ft_printf("HERE_1\n") : DEBUG;
	new = ft_new_inst(line);
	get_inst_annex(new, tmp, inst);
	return (get_inst_sub(line, new));
}
