/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprivite <marvin@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:04:36 by sprivite          #+#    #+#             */
/*   Updated: 2024/11/21 15:52:33 by sprivite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <stdio.h>

void free_map(char **map) {
    int i = 0;
    while (map[i])
        free(map[i++]);
    free(map);
}

char *read_file(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        write(2, "Error: Cannot open map file\n", 28);
        exit(1);
    }

    char *buffer = malloc(1024 * 1024); // 1 MB di buffer per la mappa
    if (!buffer) {
        write(2, "Error: Memory allocation failed\n", 32);
        close(fd);
        exit(1);
    }

    ssize_t bytes_read = read(fd, buffer, 1024 * 1024 - 1);
    if (bytes_read <= 0) {
        write(2, "Error: Failed to read map file\n", 31);
        free(buffer);
        close(fd);
        exit(1);
    }
    buffer[bytes_read] = '\0'; // Terminatore della stringa
    close(fd);
    return buffer;
}

// Funzione per leggere e suddividere la mappa
char **read_map(const char *path, int *width, int *height) {
    char *file_content = read_file(path);
    char **map = malloc(1024 * sizeof(char *)); // Alloca spazio per 1024 righe
    if (!map) {
        write(2, "Error: Memory allocation failed\n", 32);
        free(file_content);
        exit(1);
    }

    *height = 0;
    char *line = strtok(file_content, "\n"); // Suddivide il contenuto per righe
    while (line) {
        map[*height] = strdup(line); // Copia ogni riga nella mappa
        (*height)++;
        line = strtok(NULL, "\n");
    }
    free(file_content);

    *width = strlen(map[0]); // Calcola la larghezza della mappa (prima riga)
    map[*height] = NULL;     // Terminatore per la matrice

    // Debug: Stampa la mappa
    ft_printf("Map loaded successfully (%dx%d):\n", *width, *height);
    for (int i = 0; i < *height; i++) {
        ft_printf("%s\n", map[i]);
    }

    return map;
}

void put_map(t_game *game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            char tile = game->map[y][x];
            // Draw the floor as the base for every tile
            mlx_put_image_to_window(game->mlx, game->win, game->floor, x * 32, y * 32);

            if (tile == '1') {
                mlx_put_image_to_window(game->mlx, game->win, game->wall, x * 32, y * 32);
            } else if (tile == 'C') {
                mlx_put_image_to_window(game->mlx, game->win, game->collectible, x * 32, y * 32);
            } else if (tile == 'E') {
                mlx_put_image_to_window(game->mlx, game->win, game->exit, x * 32, y * 32);
            } else if (tile == 'P') {
                mlx_put_image_to_window(game->mlx, game->win, game->player, x * 32, y * 32);
                game->player_x = x; // Update player position
                game->player_y = y;
            }
        }
    }
}