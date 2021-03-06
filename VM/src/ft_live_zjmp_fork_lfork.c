/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live_zjmp_fork_lfork.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:31:38 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/09 16:46:27 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
** DEBUG ? ft_printf("launching ft_live ...\n") : DEBUG;
** DEBUG ? ft_printf("un processus dit que le joueur %d(%s) est en vie\n", \
**													ps->uid, ps->playr) : DEBUG;
** DEBUG ? print_memory(vm->mem + ps->pc, OPCODE_SIZE \
** + DIR_SIZE_P(OP_TAB_INDEX(LIVE))) : DEBUG;
*/

static void			ft_live_sub(t_vm_mem *vm, t_ps *ps, t_ps *lst)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->playr_uid[i] == lst->uid)
			break ;
	(vm->playr_live[i])++;
	g_verbose == 2 ? ft_printf("ps->playr = %s\nJe suis en vie !\nps->live \
							= %d\n\n", ps->playr, ps->live) : g_verbose;
	vm->last_live = lst->uid;
	vm->lives++;
}

int					ft_live(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int				arg0;
	t_ps			*lst;
	int				i;

	(void)opcode;
	i = -1;
	arg0 = 0;
	while (++i < DIR_SIZE_P(OP_TAB_INDEX(LIVE)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + ft_mem_cir_pos(ps->pc + OPCODE_SIZE + i));
	ps->live++;
	lst = *(vm->ps_st);
	while (lst)
	{
		if (lst->uid == arg0)
			break ;
		lst = lst->next;
	}
	ps->op_size = OPCODE_SIZE + DIR_SIZE_P(OP_TAB_INDEX(LIVE));
	if (lst == NULL)
		return (ft_next_op(ps, NO_CARRY, EMPTY_VAL));
	ft_live_sub(vm, ps, lst);
	return (ft_next_op(ps, NO_CARRY, EMPTY_VAL));
}

int					ft_zjmp(t_vm_mem *vm, t_ps *ps, int opcode)
{
	short			arg0;
	int				i;

	(void)opcode;
	i = -1;
	arg0 = 0;
	DEBUG ? ft_printf("launching ft_zjmp ...\n") : DEBUG;
	while (++i < DIR_SIZE_P(OP_TAB_INDEX(ZJMP)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + ft_mem_cir_pos(ps->pc + OPCODE_SIZE + i));
	arg0 = (short)arg0;
	if (ps->carry == 1)
	{
		ps->pc = ft_mem_cir_pos(ps->pc + arg0 % IDX_MOD);
		return (ft_next_op(ps, NO_CARRY, EMPTY_VAL));
	}
	ps->op_size = OPCODE_SIZE + DIR_SIZE_P(OP_TAB_INDEX(ZJMP));
	return (ft_next_op(ps, NO_CARRY, EMPTY_VAL));
}

int					ft_fork(t_vm_mem *vm, t_ps *lst_ps, int opcode)
{
	t_ps			*new;
	int				arg0;
	t_ps			*ps;
	int				i;

	i = -1;
	arg0 = 0;
	ps = lst_ps;
	DEBUG ? ft_printf("launching ft_fork ...\n") : DEBUG;
	while (++i < DIR_SIZE_P(OP_TAB_INDEX(FORK)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + ft_mem_cir_pos(ps->pc + OPCODE_SIZE + i));
	arg0 = (short)arg0;
	new = ft_cpy_playr(vm, ps);
	if (opcode == FORK)
		new->pc = ft_mem_cir_pos(ps->pc + (arg0 % IDX_MOD));
	else if (opcode == LFORK)
		new->pc = ft_mem_cir_pos(ps->pc + arg0);
	ps->op_size = OPCODE_SIZE + DIR_SIZE_P(OP_TAB_INDEX(FORK));
	return (ft_next_op(lst_ps, NO_CARRY, EMPTY_VAL));
}
