#include <stdio.h>
#include <stdlib.h>

void create_grids(char ***pgrid, char ***cgrid, int lines, int columns)
{
    *pgrid = (char **) malloc(sizeof(char *) * lines);
    *cgrid = (char **) malloc(sizeof(char *) * lines);

    for (int i = 0; i < lines; ++i)
    {
        (*pgrid)[i] = (char *) malloc(sizeof(char) * columns);
        (*cgrid)[i] = (char *) malloc(sizeof(char) * columns);

        for (int j = 0; j < columns; ++j)
        {
            (*pgrid)[i][j] = ' ';
            (*cgrid)[i][j] = ' ';
        }
    }
}

void free_grids(char **pgrid, char **cgrid, int lines, int columns)
{
    for (int i = 0; i < lines; ++i)
    {
        free(pgrid[i]);
        free(cgrid[i]);
    }

    free(pgrid);
    free(cgrid);
}

void display_grids(char **pgrid, char **cgrid, int lines, int columns)
{
    printf("  ");
    for (int i = 0; i < columns; ++i)
        printf(" %c", 'A' + i);
    printf("\t  ");

    for (int i = 0; i < columns; ++i)
        printf(" %c", 'A' + i);
    printf("\n");

    for (int i = 0; i < lines; ++i)
    {
        if (i + 1 < 10)
            printf(" ");
        printf("%d", i + 1);

        for (int j = 0; j < columns; ++j)
            printf(" %c", pgrid[i][j]);
        printf("\t");

        if (i + 1 < 10)
            printf(" ");
        printf("%d", i + 1);

        for (int j = 0; j < columns; ++j)
            if ((cgrid[i][j] != 'X') && (cgrid[i][j] != 'O'))
                printf("  ");
            else
                printf(" %c", cgrid[i][j]);
        printf("\n");
    }
}
