/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_fun_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:39:35 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/01 20:13:35 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void				ft_chg_mem_uid(t_vm_mem *vm, t_ps *ps, int pos, int size)
{
	int				i;

	i = -1;
	while (++i < size)
		*(vm->mem_uid + ft_mem_cir_pos(ps->pc + pos + i)) = ps->uid;
}

/*
** arg_i : argument index (0, 1, 2)
*/

int					ft_is_type(t_vm_mem *vm, t_ps *ps, int arg_i, \
														unsigned int type)
{
	DEBUG ? ft_printf("launching ft_is_type ...\n") : DEBUG;
	if (!(g_op_tab[OP_TAB_INDEX(ps->opcode)].ocp_param))
	{
		if (type == T_DIR)
			if (g_op_tab[OP_TAB_INDEX(ps->opcode)].param[0] & C_DIR)
				return (true);
		if (type == T_REG)
			if (g_op_tab[OP_TAB_INDEX(ps->opcode)].param[0] & C_REG)
				return (true);
		if (type == T_IND)
			if (g_op_tab[OP_TAB_INDEX(ps->opcode)].param[0] & C_IND)
				return (true);
	}
	else if (ft_get_ocp(vm, ps, arg_i) == type)
		return (true);
	return (false);
}

/*
** this function gets ocp for each param specifically
** if arg_i = 3, get the supposed last 0x00 value (check errors)
*/

unsigned char		ft_get_ocp(t_vm_mem *vm, t_ps *ps, int arg_i)
{
	unsigned char	ocp;

	DEBUG ? ft_printf("launching ft_get_ocp ...\n") : DEBUG;
	(void)vm;
	ocp = ps->ocp;
	ocp = (ocp >> ((3 - arg_i) * 2));
	ocp = ocp & 0b11;
	return (ocp);
}

static int			check_ocp_param(t_vm_mem *vm, t_ps *ps, int arg_i)
{
	unsigned int	code;

	DEBUG ? ft_printf("launching check_ocp_param ...\n") : DEBUG;
	code = ft_get_ocp(vm, ps, arg_i);
	if (code == T_DIR)
		return (g_op_tab[OP_TAB_INDEX(ps->opcode)].param[arg_i] & C_DIR);
	if (code == T_REG)
		return (g_op_tab[OP_TAB_INDEX(ps->opcode)].param[arg_i] & C_REG);
	if (code == T_IND)
		return (g_op_tab[OP_TAB_INDEX(ps->opcode)].param[arg_i] & C_IND);
	if (!VALID_OCP_PART(code))
		return (false);
	return (true);
}

int					check_ocp_fmt(t_vm_mem *vm, t_ps *ps, int nb_arg)
{
	DEBUG ? ft_printf("launching check_ocp_fmt ...\n") : DEBUG;
	if (nb_arg == 1 && !check_ocp_param(vm, ps, 0))
		return (false);
	if (nb_arg == 2 && (!check_ocp_param(vm, ps, 0)
				|| !check_ocp_param(vm, ps, 1)))
		return (false);
	if (nb_arg == 3 && (!check_ocp_param(vm, ps, 0)
				|| !check_ocp_param(vm, ps, 1)
				|| !check_ocp_param(vm, ps, 2)))
		return (false);
	if (CHECK_OCP_END_00(ft_get_ocp(vm, ps, 3)))
		return (false);
	return (true);
}
