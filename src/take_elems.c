/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:06:58 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/21 12:08:33 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	malloc_piece(t_game *game)
{
	int		i;

	i = 0;
	game->piece->map = (char **)malloc(sizeof(char *) * (game->board->y + 1));
	while (i < game->board->y)
	{
		game->piece->map[i] = ft_strnew(game->board->x);
		i++;
	}
	game->board->map[i] = NULL;
}

void	make_piece(t_game *game)
{
	int			i;
	char		*str;
	static int	flag = 0;

	i = 0;
	if (flag == 0)
		malloc_piece(game);
	while (i < game->piece->y)
	{
		get_next_line(g_fd, &str);
		game->piece->map[i] = ft_strncpy(game->piece->map[i],
								str, game->piece->x);
		ft_strdel(&str);
		i++;
	}
	flag = 1;
}

void	make_board(t_game *game)
{
	int			i;
	char		*str;
	static int	flag = 0;

	i = 0;
	get_next_line(g_fd, &str);
	ft_strdel(&str);
	if (flag == 0)
		malloc_board(game);
	else
	{
		while (i < game->board->y)
		{
			get_next_line(g_fd, &str);
			game->board->map[i] = ft_strncpy(game->board->map[i],
					str + 4, game->board->x);
			ft_strdel(&str);
			i++;
		}
	}
	flag = 1;
}

void	malloc_board(t_game *game)
{
	int		i;
	char	*str;

	i = 0;
	game->board->map = (char **)malloc(sizeof(char *) * game->board->y + 1);
	while (i < game->board->y)
	{
		get_next_line(g_fd, &str);
		game->board->map[i] = ft_strdup(str + 4);
		ft_strdel(&str);
		i++;
	}
	game->board->map[i] = NULL;
}

t_coord	*set_def_cor(void)
{
	t_coord		*res;

	res = (t_coord *)malloc(sizeof(t_coord));
	res->x = 0;
	res->y = 0;
	res->min = 0;
	return (res);
}
