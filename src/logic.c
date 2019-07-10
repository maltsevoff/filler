/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:10:17 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/17 19:10:19 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			validate_pos(t_game *game, int x, int y)
{
	t_info		cor;

	set_def_info(&cor, y, x);
	while (cor.pi_y < game->piece->y)
	{
		cor.pi_x = 0;
		while (cor.pi_x < game->piece->x)
		{
			if (valid_check(&cor, game) == 0)
				return (0);
			cor.pi_x++;
		}
		cor.pi_y++;
	}
	if (cor.flag == 1 && cor.pi_x * cor.pi_y == game->piece->x * game->piece->y)
		return (1);
	return (0);
}

int			find_next(t_coord *cor, t_game *game, t_coord *pos, t_coord *pi_cor)
{
	while (cor->y < game->board->y)
	{
		cor->x = 0;
		while (cor->x < game->board->x)
		{
			if (ft_strchr(game->enemy->let, game->board->map[cor->y][cor->x]))
			{
				if (compare_coord(pi_cor->x + pos->x,
					pi_cor->y + pos->y, cor, game) == 1)
				{
					game->x = pos->x;
					game->y = pos->y;
				}
				cor->x++;
				cor->y++;
				return (1);
			}
			cor->x++;
		}
		cor->y++;
	}
	return (0);
}

int			compare_coord(int x, int y, t_coord *x_cor, t_game *game)
{
	if (game->x == 0 && game->y == 0)
	{
		game->min = ABS(x - x_cor->x) + ABS(y - x_cor->y);
		return (1);
	}
	else if (game->min >= ABS(x - x_cor->x) + ABS(y - x_cor->y))
	{
		game->min = ABS(x - x_cor->x) + ABS(y - x_cor->y);
		return (1);
	}
	return (0);
}

void		calculate_coord(t_game *game, int x, int y)
{
	t_coord		*pi_cor;
	t_coord		*x_cor;
	t_coord		*pos;

	pos = set_def_cor();
	pos->x = x;
	pos->y = y;
	pi_cor = set_def_cor();
	while (pi_cor->y < game->piece->y)
	{
		pi_cor->x = -1;
		while (++pi_cor->x < game->piece->x)
		{
			if (game->piece->map[pi_cor->y][pi_cor->x] == '*')
			{
				x_cor = set_def_cor();
				while (find_next(x_cor, game, pos, pi_cor))
					;
				free(x_cor);
			}
		}
		pi_cor->y++;
	}
	free(pos);
	free(pi_cor);
}

void		find_position(t_game *game)
{
	int		x;
	int		y;

	y = -game->piece->y + 1;
	game->x = 0;
	game->y = 0;
	game->min = 0;
	while (y < game->board->y)
	{
		x = -game->piece->x + 1;
		while (x < game->board->x)
		{
			if (validate_pos(game, x, y))
			{
				calculate_coord(game, x, y);
			}
			x++;
		}
		y++;
	}
}
