/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:02:41 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/17 19:10:28 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_map(char **map)
{
	int		i;

	i = 0;
	if (map[i] == NULL)
		return ;
	while (map[i])
	{
		ft_strdel(&map[i]);
		i++;
	}
	free(map);
}

int		start_game(t_game *game)
{
	char	*line;

	while (get_next_line(g_fd, &line))
	{
		if (ft_strstr(line, "Plateau") != NULL)
			work_board(game, line);
		else if (ft_strstr(line, "Piece") != NULL)
		{
			work_piece(game, line);
			find_position(game);
			show_coord(game);
			if (game->x == 0 && game->y == 0)
			{
				delete_info(game);
				exit(0);
			}
		}
		else
		{
			if (line != NULL)
				ft_strdel(&line);
			return (0);
		}
	}
	return (1);
}

void	show_coord(t_game *game)
{
	ft_putnbr(game->y);
	ft_putchar(' ');
	ft_putnbr(game->x);
	ft_putchar('\n');
}

int		main(void)
{
	char		*str;
	t_game		*game;

	g_fd = 0;
	game = (t_game *)malloc(sizeof(t_game));
	get_next_line(g_fd, &str);
	if (ft_strstr(str, "$$$"))
		set_player(game, str);
	ft_strdel(&str);
	while (1)
	{
		if (start_game(game) == 0)
			break ;
	}
	delete_info(game);
	return (0);
}

void	set_player(t_game *game, char *str)
{
	game->me = (t_player *)malloc(sizeof(t_player));
	game->enemy = (t_player *)malloc(sizeof(t_player));
	if (str[10] - 48 == 1)
	{
		game->me->let = ft_strdup("oO");
		game->me->p_num = 1;
		game->enemy->let = ft_strdup("xX");
		game->enemy->p_num = 2;
	}
	else
	{
		game->me->let = ft_strdup("xX");
		game->me->p_num = 2;
		game->enemy->let = ft_strdup("oO");
		game->enemy->p_num = 1;
	}
	game->min = 0;
	game->x = 0;
	game->y = 0;
	game->board = (t_elem *)malloc(sizeof(t_elem));
	game->piece = (t_elem *)malloc(sizeof(t_elem));
}
