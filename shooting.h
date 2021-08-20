#ifndef battleship_shooting_h
#define battleship_shooting_h

void shoot_computer(char **pgrid, int lines, int columns, int *x, int *y, bool *shooting, int *X_shooting, int *Y_shooting);
int shooting_stage(int ship_count, char **ships, int *sizes, char *signs, char **pgrid, char **cgrid, int lines, int columns, int turn, bool shooting, int X_shooting, int Y_shooting);

#endif
