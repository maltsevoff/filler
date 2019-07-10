/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:04:18 by omaltsev          #+#    #+#             */
/*   Updated: 2019/03/16 18:05:31 by omaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

int		g_fd;

typedef struct	s_player
{
	int		p_num;
	char	*let;
}				t_player;

typedef struct	s_elem
{
	int		x;
	int		y;
	char	**map;
}				t_elem;

typedef struct	s_coord
{
	int		x;
	int		y;
	int		min;
}				t_coord;

typedef struct	s_info
{
	int		pi_x;
	int		pi_y;
	int		x;
	int		y;
	int		flag;
}				t_info;

typedef struct	s_game
{
	int			min;
	int			x;
	int			y;
	t_elem		*board;
	t_elem		*piece;
	t_player	*me;
	t_player	*enemy;
}				t_game;

int				start_game(t_game *game);
void			make_board(t_game *game);
void			malloc_board(t_game *game);
void			make_piece(t_game *game);
void			work_piece(t_game *game, char *line);
void			work_board(t_game *game, char *line);
void			find_position(t_game *game);
int				validate_pos(t_game *game, int x, int y);
void			set_player(t_game *game, char *str);
void			show_coord(t_game *game);
t_coord			*set_def_cor(void);
int				find_next(t_coord *cor, t_game *game,
					t_coord *pos, t_coord *pi_cor);
int				compare_coord(int x, int y, t_coord *x_cor, t_game *game);
void			delete_info(t_game *game);
void			calculate_coord(t_game *game, int x, int y);
void			free_map(char **map);
int				valid_check(t_info *cor, t_game *game);
void			set_def_info(t_info *cor, int y, int x);

#endif
