/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ncurse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:53:12 by romontei          #+#    #+#             */
/*   Updated: 2019/01/08 17:01:59 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
** init_pair(0, COLOR_YELLOW, COLOR_BLACK);
** init_pair(1, COLOR_BLUE, COLOR_BLACK);
** init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
** init_pair(3, COLOR_CYAN, COLOR_BLACK);
** init_pair(4, COLOR_RED, COLOR_BLACK);
** init_pair(5, COLOR_GREEN, COLOR_BLACK);
** init_pair(6, COLOR_YELLOW, COLOR_BLACK);
** init_pair(7, COLOR_BLACK, COLOR_BLUE);
** init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
** init_pair(9, COLOR_BLACK, COLOR_CYAN);
** init_pair(10, COLOR_BLACK, COLOR_RED);
** init_pair(11, COLOR_BLACK, COLOR_GREEN);
** init_pair(12, COLOR_WHITE, COLOR_BLACK);
** init_pair(13, COLOR_BLACK, COLOR_GREEN);
*/

void			ft_init_ncurses(void)
{
	initscr();
	noecho();
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(7, COLOR_WHITE, COLOR_CYAN);
	init_pair(8, COLOR_WHITE, COLOR_RED);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_YELLOW);
	curs_set(FALSE);
}

void			ft_print_lives(t_vm_mem *vm, int i)
{
	int			k;
	int			cycles;
	t_ps		*ps;

	ps = *(vm->ps_st);
	while (ps)
	{
		if (ps->uid == vm->playr_uid[i])
			break ;
		ps = ps->next;
	}
	attron(COLOR_PAIR(1 + (i % 4)));
	cycles = (vm->playr_live[i] < 161) ? vm->playr_live[i] : 161;
	k = -1;
	printw("\nplayr %s (%d)", ps->playr, vm->playr_uid[i]);
	printw("\nLives : %-5d", vm->playr_live[i]);
	while (++k < cycles)
		addch(ACS_CKBOARD);
	attroff(COLOR_PAIR(1 + (i % 4)));
}

void			ft_print_game_stats(t_vm_mem *vm, t_ps *ps)
{
	int			i;

	i = -1;
	(void)ps;
	while (++i < MAX_PLAYERS)
		if (vm->playr_uid[i])
			ft_print_lives(vm, i);
	attron(COLOR_PAIR(9));
	printw("\n\nNb of processes : %d\n\n", vm->nb_live_ps);
	printw("\n\nCycle: %-10d Total Number of lives: %d/%-10d \
			Checks: %d/%d > Decrease cycle to die with: %d \
			Cycles to die: %d/%d\n\n", vm->cycle, vm->lives, NBR_LIVE, \
		vm->check, MAX_CHECKS, CYCLE_DELTA, vm->cycle_to_die, vm->real_cycle);
	attroff(COLOR_PAIR(9));
	refresh();
}

static int		ft_get_playr_index_2(t_vm_mem *vm, int uid)
{
	int			i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (vm->playr_uid[i] == uid)
			return (i);
	}
	return (uid);
}

void			ft_init_arena(t_vm_mem *vm, t_ps *ps)
{
	int			i;
	int			index;
	t_ps		*tmp;

	i = -1;
	tmp = ps;
	while (++i < MEM_SIZE)
	{
		vm->a[i].hex = vm->mem[i];
		vm->a[i].playr_uid = vm->mem_uid[i];
		index = ft_get_playr_index_2(vm, vm->mem_uid[i]);
		vm->a[i].color = index != UNDEFINED ? 1 + (index % 4) : UNDEFINED;
		vm->a[i].color_pc = index != UNDEFINED ? \
						1 + (index % 4) + 4 : 10;
	}
	while (tmp)
	{
		index = ft_get_playr_index_2(vm, tmp->uid);
		tmp->color_pc = index != UNDEFINED ? \
						1 + (index % 4) + 4 : 10;
		tmp = tmp->next;
	}
}
