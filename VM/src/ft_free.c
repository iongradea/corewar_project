/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:15:35 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/08 15:16:54 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void		ft_free_ps(t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_free_ps ...\n") : DEBUG;
	free(ps->playr);
	free(ps->code);
	free(ps);
}

void		ft_free_all_ps(t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_free_all_ps ...\n") : DEBUG;
	while (ps->next)
	{
		if (ps->prev)
			ft_free_ps(ps->prev);
		ps = ps->next;
	}
	ft_free_ps(ps);
}
