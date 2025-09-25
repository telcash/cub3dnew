#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

# define WIDTH 1288
# define HEIGHT 720
# define BLOCK 32 //bloque 32 pixeles
# define DEBUG 0

# define PI 3.14159265359

# define W 119
# define A 97
# define S 115
# define D 100
# define KEY_ESC 65307
# define KEY_Q 113
# define RIGHT 65363
# define LEFT 65361 

# define ERR_NUM_ARGS "Invalid number of arguments"
# define ERR_INIT_DATA "Error initializing data"
# define ERR_INV_FILE "Invalid map file"
# define ERR_MALLOC_PLAYER "Error allocating memory for player"
# define ERR_MALLOC_MAP "Error allocating memory for map"
# define ERR_MALLOC_DATA "Error allocating memory for data"
# define ERR_OPEN_FILE "Error opening file"
# define DUP_TEXTURE_FILE "Duplicated texture assignment on data file"
# define NOT_TEXTURE_FILE_SPEC "Not texture file specified"
# define DUP_COLOR "Duplicated color assignment on data file"
# define NOT_COLOR_SPEC "Not color specified"
# define INV_COLOR_FORMAT "Invalid color format on data file"
# define INV_RGB_VALUE "Invalid RGB color value on data file. RGB values must be between 0-255"
# define BAD_DATA_FORMAT "Invalid format on data file"
# define BAD_MAP_DIMS "Invalid map dimmensions"
# define NO_PLAYER "Invalid map, there is no player"
# define DUP_PLAYER "Invalid map, must be only one player"
# define OPEN_MAP "Invalid map, the map must be surrounded by walls"
# define ERR_NAV_MAP "Invalid map, the player can't reach all blank spaces"

typedef struct s_rgb
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} t_rgb;

typedef struct s_player
{
    int row;
    int col;
    char view;
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rotate;
    bool right_rotate;
    float angle;
} t_player;

typedef struct s_map
{
    size_t h;
    size_t w;
    char *no_t;
    char *so_t;
    char *we_t;
    char *ea_t;
    t_rgb *f;
    t_rgb *c;
    int coords_fl;
    int num_spaces;
    char **coords;
    t_player *player;   
}   t_map;

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    t_map   *map;
    t_map *map1;
}   t_data;

t_data *init_data(char *file);
void init_game(t_data *data);
int parse_map(t_map *map, char *file);
void free_data(t_data *data);
void	free_split(char **split);
int get_map_data(t_map *map, char *file);
int	ft_isspace(char c);
int get_texture_from_line(char *line, int i, char **texture);
int get_color_from_line(char *line, int i, t_rgb **color);
int ft_is_coord(char c);
int get_map_coords(t_map *map, char *file);

#endif