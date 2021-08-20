#ifndef battleship_ships_h
#define battleship_ships_h

int check_ships(char **grid, int lines, int columns, int x, int y, int direction, int size);
void place_ships(int ship_count, char **ships, int *sizes, char *signs, char **pgrid, char **cgrid, int lines, int columns);
void generate_ships(int ship_count, char **ships, int *sizes, char *signs, char **grid, int lines, int columns);

#endif
