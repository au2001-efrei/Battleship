#ifndef battleship_grids_h
#define battleship_grids_h

void create_grids(char ***pgrid, char ***cgrid, int lines, int columns);
void free_grids(char **pgrid, char **cgrid, int lines, int columns);
void display_grids(char **pgrid, char **cgrid, int lines, int columns);

#endif
