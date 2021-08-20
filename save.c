#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void save_game(int ship_count, char **ships, int *sizes, char *signs, char **pgrid, char **cgrid, int lines, int columns, int turn, bool shooting, int X_shooting, int Y_shooting)
{
    FILE *fp = fopen("./save", "w+");

    fprintf(fp, "%d\n", ship_count);

    for (int i = 0; i < ship_count; ++i)
        fprintf(fp, "%s %d %c\n", ships[i], sizes[i], signs[i]);

    fprintf(fp, "%d %d\n", lines, columns);

    for (int i = 0; i < lines; ++i)
    {
        fprintf(fp, "%c", pgrid[i][0] == ' '? '.' : pgrid[i][0]);
        for (int j = 1; j < columns; ++j)
            fprintf(fp, " %c", pgrid[i][j] == ' '? '.' : pgrid[i][j]);
        fprintf(fp, "\n");
    }

    for (int i = 0; i < lines; ++i)
    {
        fprintf(fp, "%c", cgrid[i][0] == ' '? '.' : cgrid[i][0]);
        for (int j = 1; j < columns; ++j)
            fprintf(fp, " %c", cgrid[i][j] == ' '? '.' : cgrid[i][j]);
        fprintf(fp, "\n");
    }

    fprintf(fp, "%d %d %d %d\n", turn, shooting, X_shooting, Y_shooting);

    fclose(fp);
}

bool load_game(int *ship_count, char ***ships, int **sizes, char **signs, char ***pgrid, char ***cgrid, int *lines, int *columns, int *turn, bool *shooting, int *X_shooting, int *Y_shooting)
{
    FILE *fp = fopen("./save", "r");

    if (!fp)
        return false;

    int previous_ship_count = *ship_count;
    int n = fscanf(fp, "%d\n", ship_count);
    if (n < 1) {
        fclose(fp);
        return false;
    }

    for (int i = *ship_count; i < previous_ship_count; ++i)
        free((*ships)[i]);

    *ships = (char **) realloc(*ships, sizeof(char *) * *ship_count);
    *sizes = (int *) realloc(*sizes, sizeof(int) * *ship_count);
    *signs = (char *) realloc(*signs, sizeof(char) * *ship_count);

    for (int i = previous_ship_count; i < *ship_count; ++i)
        (*ships)[i] = (char *) malloc(sizeof(char) * 100);

    for (int i = 0; i < *ship_count; ++i)
    {
        n = fscanf(fp, "%s %d %c\n", (*ships)[i], &(*sizes)[i], &(*signs)[i]);
        if (n < 3) {
            fclose(fp);
            return false;
        }
    }

    n = fscanf(fp, "%d %d\n", lines, columns);
    if (n < 2) {
        fclose(fp);
        return false;
    }

    for (int i = 0; i < *lines; ++i)
    {
        n = fscanf(fp, "%c", &(*pgrid)[i][0]);
        if (n < 1) {
            fclose(fp);
            return false;
        }

        if ((*pgrid)[i][0] == '.')
            (*pgrid)[i][0] = ' ';

        for (int j = 1; j < *columns; ++j)
        {
            n = fscanf(fp, " %c", &(*pgrid)[i][j]);
            if (n < 1) {
                fclose(fp);
                return false;
            }

            if ((*pgrid)[i][j] == '.')
                (*pgrid)[i][j] = ' ';
        }

        fscanf(fp, "\n");
    }

    for (int i = 0; i < *lines; ++i)
    {
        n = fscanf(fp, "%c", &(*cgrid)[i][0]);
        if (n < 1) {
            fclose(fp);
            return false;
        }

        if ((*cgrid)[i][0] == '.')
            (*cgrid)[i][0] = ' ';

        for (int j = 1; j < *columns; ++j)
        {
            n = fscanf(fp, " %c", &(*cgrid)[i][j]);
            if (n < 1) {
                fclose(fp);
                return false;
            }

            if ((*cgrid)[i][j] == '.')
                (*cgrid)[i][j] = ' ';
        }

        fscanf(fp, "\n");
    }

    int shooting_int;
    n = fscanf(fp, "%d %d %d %d\n", turn, &shooting_int, X_shooting, Y_shooting);
    if (n < 4) {
        fclose(fp);
        return false;
    }
    *shooting = shooting_int;

    fclose(fp);
    return true;
}
