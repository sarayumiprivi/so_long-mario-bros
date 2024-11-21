/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprivite <marvin@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:02:00 by sprivite          #+#    #+#             */
/*   Updated: 2024/11/21 15:12:47 by sprivite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int close_game(t_game *game) {
    free_game(game);
    exit(0);
    return (0);
}

int main(int argc, char **argv) {
    t_game game;

    if (argc != 2) {
        write(2, "Usage: ./so_long map.ber\n", 25);
        return (1);
    }
    init_game(&game, argv[1]);
    put_map(&game);
    mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
    mlx_hook(game.win, 17, 0, close_game, &game);
    mlx_loop(game.mlx);
    return (0);
}
