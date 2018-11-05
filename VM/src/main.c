/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea           #+#    #+#             */
/*   Updated: 2018/11/05 21:03:47 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
 *	ft_new_mem	= Instantiate VM
 *	ft_parse_opt = parse cli arg
 *	get_playr	= check argument players
 *
 */
int				main(int ac, char **av)
{
	int			fd;
	t_ps		*ps;
	t_vm_mem	*vm;

	fd = 0;
	ps = NULL;
	if (ac < 2)
		exit(ft_usage());
	vm = ft_new_mem();
	ft_parse_opt(ac, av, vm);
	get_playr(fd, &ps, ac, av);
	add_data_vm(vm, ps);
	cpu(vm, ps);
	//ft_main_debug(vm, ps);
	//ft_prt_mem(vm, ps);
	exit(EXIT_SUCCESS);
}
