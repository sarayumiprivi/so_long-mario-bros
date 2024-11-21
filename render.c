/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprivite <marvin@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:03:16 by sprivite          #+#    #+#             */
/*   Updated: 2024/11/21 13:14:48 by sprivite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void render_game(t_game *game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall, x * 32, y * 32);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible, x * 32, y * 32);
            else if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit, x * 32, y * 32);
            else
                mlx_put_image_to_window(game->mlx, game->win, game->floor, x * 32, y * 32);
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->player, game->player_x * 32, game->player_y * 32);
}
