/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprivite <marvin@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:02:22 by sprivite          #+#    #+#             */
/*   Updated: 2024/11/21 15:54:42 by sprivite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

// Funzione per liberare tutte le risorse allocate
void free_game(t_game *game) {
    if (game->map) {
        for (int i = 0; i < game->map_height; i++)
            free(game->map[i]);
        free(game->map);
    }
    if (game->mlx && game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx) {
        if (game->player) mlx_destroy_image(game->mlx, game->player);
        if (game->wall) mlx_destroy_image(game->mlx, game->wall);
        if (game->collectible) mlx_destroy_image(game->mlx, game->collectible);
        if (game->exit) mlx_destroy_image(game->mlx, game->exit);
        if (game->floor) mlx_destroy_image(game->mlx, game->floor);
        free(game->mlx);
    }
}

// Funzione per validare la mappa
void validate_map(t_game *game) {
    int player = 0, exit_count = 0, collectibles = 0;

    for (int y = 0; y < game->map_height; y++) {
        if ((int)ft_strlen(game->map[y]) != game->map_width) {
            ft_printf("Row %d is not rectangular: %s\n", y, game->map[y]);
            write(2, "Error: Map must be rectangular\n", 31);
            free_game(game);
            exit(1);
        }
        for (int x = 0; x < game->map_width; x++) {
            char c = game->map[y][x];
            if (c == 'P') {
                player++;
                game->player_x = x;
                game->player_y = y;
            } else if (c == 'E') {
                exit_count++;
            } else if (c == 'C') {
                collectibles++;
            } else if (c != '1' && c != '0') {
                ft_printf("Invalid character '%c' at (%d, %d)\n", c, y, x);
                write(2, "Error: Invalid map character\n", 29);
                free_game(game);
                exit(1);
            }
        }
    }

    ft_printf("Player: %d, Exits: %d, Collectibles: %d\n", player, exit_count, collectibles);
    if (player != 1 || exit_count < 1 || collectibles < 1) {
        write(2, "Error: Map must have 1 player, at least 1 exit, and 1 collectible\n", 65);
        free_game(game);
        exit(1);
    }
    game->collectibles = collectibles;
}


// Funzione per inizializzare gli assets grafici
void init_assets(t_game *game) {
    game->player = mlx_xpm_file_to_image(game->mlx, "textures/Mario_corre_dxt.xpm", &(int){32}, &(int){32});
    // game->player[1] = mlx_xpm_file_to_image(game->mlx, "textures/Mario_corre_sxt.xpm", &(int){32}, &(int){32});
    // game->player[2] = mlx_xpm_file_to_image(game->mlx, "textures/Mario_Verso_alto.xpm", &(int){32}, &(int){32});
    // game->player[3] = mlx_xpm_file_to_image(game->mlx, "textures/Mario_vola.xpm", &(int){32}, &(int){32});
    game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &(int){32}, &(int){32});
    game->collectible = mlx_xpm_file_to_image(game->mlx, "textures/coin.xpm", &(int){32}, &(int){32});
    game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &(int){32}, &(int){32});
    game->floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &(int){32}, &(int){32});
    // if (!game->player[0] || !game->wall || !game->collectible || !game->exit || !game->floor) {
    //     write(2, "Error: Failed to load assets\n", 29);
    //     free_game(game);
    //     exit(1);
    // }
}

// Funzione per inizializzare il gioco
void init_game(t_game *game, const char *map_path) {
    game->mlx = mlx_init();
    if (!game->mlx) {
        write(2, "Error: Failed to initialize MiniLibX\n", 36);
        exit(1);
    }

    game->map = read_map(map_path, &game->map_width, &game->map_height);
    validate_map(game);

    game->win = mlx_new_window(game->mlx, game->map_width * 32, game->map_height * 32, "So Long");
    if (!game->win) {
        write(2, "Error: Failed to create window\n", 31);
       close_game(game);
        exit(1);
    }
    init_assets(game);
    game->moves = 0;
}

int handle_keypress(int key, t_game *game) {
    int new_x = game->player_x;
    int new_y = game->player_y;

    // Calculate new player position based on the key pressed
    if (key == 119) // W - Move up
        new_y--;
    else if (key == 115) // S - Move down
        new_y++;
    else if (key == 97) // A - Move left
        new_x--;
    else if (key == 100) // D - Move right
        new_x++;
    else if (key == 65307) // ESC - Close the game
        close_game(game);

    // Check if the new position is walkable
    if (game->map[new_y][new_x] != '1') { // '1' is a wall
        // If stepping on a collectible
        if (game->map[new_y][new_x] == 'C') {
            game->collectibles--; // Decrease collectible count
        }

        // If stepping on the exit
        if (game->map[new_y][new_x] == 'E') {
            if (game->collectibles > 0) {
                ft_printf("Collect all coins before exiting!\n");
                return (0); // Prevent movement onto the exit
            } else {
                write(1, "You Win!\n", 9);
                close_game(game); // Exit the game if all collectibles are collected
            }
        }

        // Update the map matrix for movement
        game->map[game->player_y][game->player_x] = '0'; // Clear old player position
        game->map[new_y][new_x] = 'P'; // Set new player position

        // Update the player's position
        game->player_x = new_x;
        game->player_y = new_y;

        // Increment the move counter and print it
        game->moves++; // Increment move count
        ft_printf("Moves made: %d\n", game->moves);

        // Redraw the map with the updated matrix
        put_map(game);
    }
    return (0);
}



