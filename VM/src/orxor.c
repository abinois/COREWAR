/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orxor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:19:25 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/17 16:07:17 by avanhers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fc_or(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];

	ft_bzero(elem, sizeof(elem));
	param = fill_param(A, op, PRO, elem);
	elem[0] = param.type[0] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[0]) % IDX_MOD) : elem[0];
	elem[1] = param.type[1] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[1]) % IDX_MOD) : elem[1];
	param.data = elem[0] | elem[1];
	param.dest_pc = param.value[2];
	PRO->param = param;
}

void	execute_or(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
	PRO->carry = !PRO->param.data ? 1 : 0;
}

void	fc_xor(t_op op, t_process *process, t_arena *arena)
{
	t_param	param;
	int		elem[3];

	ft_bzero(elem, sizeof(elem));
	param = fill_param(A, op, PRO, elem);
	elem[0] = param.type[0] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[0]) % IDX_MOD) : elem[0];
	elem[1] = param.type[1] == IND_CODE ? fill_index_content(A, PRO,
			(short)chen4(param.value[1]) % IDX_MOD) : elem[1];
	param.data = elem[0] ^ elem[1];
	param.dest_pc = param.value[2];
	PRO->param = param;
}

void	execute_xor(t_process *process, t_arena *arena)
{
	(void)A;
	put_data_in_reg(PRO, PRO->param.data, PRO->param.dest_pc);
	PRO->carry = !PRO->param.data ? 1 : 0;
}
