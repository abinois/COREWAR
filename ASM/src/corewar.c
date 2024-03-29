/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltimsit- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:37:22 by ltimsit-          #+#    #+#             */
/*   Updated: 2019/09/21 17:58:36 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		init_data(t_data *data)
{
	ft_bzero(D, sizeof(t_data));
	if (!(D->gc = (t_gc *)malloc(sizeof(t_gc))))
		get_error(D, malloc_err, NULL);
	ft_bzero(D->gc, sizeof(t_gc));
	if (!(D->label = (t_label *)ft_alloc_gc(1, sizeof(t_label), D->gc)))
		get_error(D, malloc_err, NULL);
	ft_bzero(D->label, sizeof(t_label));
	D->curr_line = 1;
	D->curr_index = 1;
	D->mem_stock_index = sizeof(D->header);
	D->mem_size = MEMSIZE;
	D->header.magic = COREWAR_EXEC_MAGIC;
	fill_op_and_err_tab();
	return (1);
}

void	print_error(t_data *data, char *elem)
{
	if (D->err)
	{
		if (D->err == 8)
			ft_printf("{red}%s{reset} : [%.3d:%.3d]\n", g_err_tab[D->err],
					D->curr_line, D->curr_index);
		else if (!elem)
			ft_printf("{red}%s\n{reset}", g_err_tab[D->err]);
		else
			ft_printf("{red}%s{reset} : [%.3d:%.3d] -> {blink}\"%s\"{reset}\n",
					g_err_tab[D->err], D->curr_line, D->curr_index, elem);
	}
}

void	get_fd_file(char *filename, t_data *data)
{
	char	*dot;

	D->fd = open(filename, O_RDONLY);
	if (D->fd == -1)
	{
		ft_printf("{red}Read error or File \"%s\" does not exist\n{reset}",
				filename);
		ft_free_gc(D->gc);
		ft_memdel((void**)&(D->gc), 0);
		exit(EXIT_FAILURE);
	}
	dot = ft_strrchr(filename, '.');
	if (!dot || *(dot + 1) != 's' || *(dot + 2) != '\0')
		get_error(D, file_err, NULL);
}

void	write_in_file(t_data *data, char *output, char *filename)
{
	int		fd;
	char	file[128];
	char	*dot;
	int		i;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot - filename >= 128 - 4)
		get_error(D, file_err, NULL);
	file[dot - filename] = '\0';
	i = -1;
	while (++i < dot - filename)
		file[i] = filename[i];
	ft_strcat(file, ".cor");
	if ((fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1)
		get_error(D, open_err, NULL);
	ft_printf("{cyan}{italic}Writing output program to \"%s\"{reset}\n", file);
	write(fd, output, D->size_mem_tot);
	if ((i = close(fd)) == -1)
		get_error(D, close_err, NULL);
}

int		main(int ac, char **av)
{
	t_data		data;
	int			i;

	if (ac < 2)
		print_usage();
	i = 0;
	while (++i < ac)
	{
		init_data(&D);
		get_fd_file(av[i], &D);
		get_header(&D);
		write_in_file(&D, D.mem_stock, av[i]);
		ft_free_gc(D.gc);
		ft_memdel((void**)&(D.gc), 0);
	}
	return (0);
}
