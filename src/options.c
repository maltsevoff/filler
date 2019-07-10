/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 15:04:45 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/23 15:04:48 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	delete_info(t_game *game)
{
	int		i;

	i = -1;
	ft_strdel(&game->me->let);
	free(game->me);
	ft_strdel(&game->enemy->let);
	free(game->enemy);
	while (++i < game->board->y)
		ft_strdel(&game->board->map[i]);
	free(game->board->map);
	free(game->board);
	i = -1;
	while (++i < game->board->y)
		ft_strdel(&game->piece->map[i]);
	free(game->piece->map);
	free(game->piece);
}

void	work_board(t_game *game, char *line)
{
	char	**coord;

	coord = ft_strsplit(line, ' ');
	game->board->y = ft_atoi(coord[1]);
	game->board->x = ft_atoi(coord[2]);
	free_map(coord);
	make_board(game);
	free(line);
}

void	work_piece(t_game *game, char *line)
{
	char	**coord;

	coord = ft_strsplit(line, ' ');
	game->piece->y = ft_atoi(coord[1]);
	game->piece->x = ft_atoi(coord[2]);
	ft_strdel(&line);
	free_map(coord);
	make_piece(game);
}

void	set_def_info(t_info *cor, int y, int x)
{
	cor->x = x;
	cor->y = y;
	cor->pi_x = 0;
	cor->pi_y = 0;
	cor->flag = 0;
}

int		valid_check(t_info *cor, t_game *game)
{
	if (game->piece->map[cor->pi_y][cor->pi_x] == '*'
		&& ((cor->pi_x + cor->x < 0 || cor->pi_y + cor->y < 0)
		|| (cor->x + cor->pi_x >= game->board->x ||
		cor->y + cor->pi_y >= game->board->y)))
		return (0);
	if (game->piece->map[cor->pi_y][cor->pi_x] == '*' &&
		cor->pi_y + cor->y < game->board->y &&
		cor->pi_x + cor->x < game->board->x)
	{
		if (ft_strchr(game->enemy->let,
			game->board->map[cor->pi_y + cor->y][cor->pi_x + cor->x]))
			return (0);
		if (ft_strchr(game->me->let,
			game->board->map[cor->pi_y + cor->y][cor->pi_x + cor->x]))
			cor->flag++;
	}
	return (1);
}
