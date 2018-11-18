/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 18:51:23 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int				ch_all_inst(t_inst *inst)
{
	int			i;
	int			j;
	t_inst		*tmp;

	i = -1;
	j = -1;
	tmp = inst;
	DEBUG ? ft_printf("launching ch_all_inst ...\n") : DEBUG;
	while (tmp)
	{
		if (ft_is_valid_opcode(tmp->opcode))
		{
			if (!ch_one_inst(tmp, inst))
			{
				//DEBUG ? prt_one_inst(tmp) : DEBUG;
				ERROR_MSG("Error .s file at line : ");
				ERROR_MSG(tmp->line);
				exit(ERROR_MSG("\n"));
			}
		}
		tmp = tmp->n;
	}
	return (true);
}

void			calc_all_size(t_inst *inst)
{
	t_inst		*tmp;
	int			size;

	tmp = inst;
	size = 0;
	DEBUG ? ft_printf("launching calc_all_size ...\n") : DEBUG;
	while (tmp)
	{
		tmp->size = calc_one_inst_size(tmp);
		tmp = tmp->n;
	}
	tmp = inst;
	while (tmp)
	{
		if (tmp->size != UNDEFINED)
			size += tmp->size;
		tmp = tmp->n;
	}
	if (size > CHAMP_MAX_SIZE)
		exit(ERROR_MSG("champion file too large\n"));
}

int				ft_is_lab(char *arg)
{
	int			len;

	len = ft_strlen(arg);
	if ((*arg == DIRECT_CHAR && len > 2 && *(arg + 1) == LABEL_CHAR)
		|| (len > 2 && *arg == LABEL_CHAR))
		return (true);
	return (false);
}
