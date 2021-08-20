#ifndef battleship_save_h
#define battleship_save_h

#include <stdbool.h>

void save_game(int ship_count, char **ships, int *sizes, char *signs, char **pgrid, char **cgrid, int lines, int columns, int turn, bool shooting, int X_shooting, int Y_shooting);
bool load_game(int *ship_count, char ***ships, int **sizes, char **signs, char ***pgrid, char ***cgrid, int *lines, int *columns, int *turn, bool *shooting, int *X_shooting, int *Y_shooting);

#endif
