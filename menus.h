#ifndef battleship_menus_h
#define battleship_menus_h

void customize_fleet(int *ship_count, char ***ships, int **sizes, char **signs, int lines, int columns);
void settings(int *ship_count, char ***ships, int **sizes, char **signs, char ***pgrid, char ***cgrid, int *lines, int *columns);
int menu(int *ship_count, char ***ships, int **sizes, char **signs, char ***pgrid, char ***cgrid, int *lines, int *columns, int *turn, bool *shooting, int *X_shooting, int *Y_shooting);

#endif
