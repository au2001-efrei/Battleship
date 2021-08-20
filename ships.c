#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "grids.h"

int check_ships(char **grid, int lines, int columns, int x, int y, int direction, int size)
{
    switch (direction)
    {
    case 1:
        if (x < 0 || x + (size - 1) >= columns || y < 0 || y >= lines)
            return 1;
        break;
    case 2:
        if (x < 0 || x >= columns || y - (size - 1) < 0 || y >= lines)
            return 1;
        break;
    default:
        return 3;
    }

    for (int i = 0; i < size; ++i)
    {
        if (direction == 1)
        {
            if (grid[y][x + i] != ' ')
                return 2;
        }
        else
        {
            if (grid[y - i][x] != ' ')
                return 2;
        }
    }
    return 0;
}

void place_ships(int ship_count, char **ships, int *sizes, char *signs, char **pgrid, char **cgrid, int lines, int columns)
{
    for (int i = 0; i < ship_count; ++i)
    {
        char *ship = ships[i];
        int size = sizes[i];
        char sign = signs[i];

        display_grids(pgrid, cgrid, lines, columns);

        int x, y, direction, check;
        do
        {
            x = -1;
            y = -1;

            do
            {
                char coordinates[100];
                printf("Give the coordinates of the bottom left corner of your %s (of length %d squares): ", ship, size);
                scanf("%s", coordinates);

                if (strlen(coordinates) != 0 && strlen(coordinates) != 1)
                {
                    x = toupper(coordinates[0]) - 'A';
                    y = atoi(coordinates + 1) - 1;
                }

                if (x < 0 || x >= columns || y < 0 || y >= lines)
                    printf("The position you entered is invalid. It should be between A1 and %c%d.\n", 'A' + (columns - 1), lines);
            } while (x < 0 || x >= columns || y < 0 || y >= lines);

            do
            {
                printf("Do you want to place your %s 1. horizontally or 2. vertically? ", ship);
                int n = scanf("%d", &direction);

                if (n < 1)
                {
                    char null[100];
                    scanf("%s", null);
                    printf("Please enter an integer.\n");
                }
                else if (direction != 1 && direction != 2)
                    printf("Invalid direction, please select between horizontal and vertical.\n");
            } while (direction != 1 && direction != 2);

            check = check_ships(pgrid, lines, columns, x, y, direction, size);
            if (check == 1)
                printf("Your %s would go outside of the grid. Place it somewhere else.\n", ship);
            else if (check == 2)
                printf("Your %s would overlap with another ship. Place it somewhere else.\n", ship);
        } while (check != 0);

        for (int j = 0; j < size; ++j)
        {
            if (direction == 1)
                pgrid[y][x + j] = sign;
            else
                pgrid[y - j][x] = sign;
        }
    }
}

void generate_ships(int ship_count, char **ships, int *sizes, char *signs, char **grid, int lines, int columns)
{
    for (int i = 0; i < ship_count; ++i)
    {
        int size = sizes[i];
        char sign = signs[i];

        int x, y, direction, check;
        do
        {
            direction = rand() % 2 + 1;
            x = rand() % (direction == 1? columns - size + 1 : columns);
            y = rand() % (direction == 1? lines : lines - size + 1);
            check = check_ships(grid, lines, columns, x, y, direction, size);
        } while (check != 0);

        for (int j = 0; j < size; ++j)
        {
            if (direction == 1)
                grid[y][x + j] = sign;
            else
                grid[y - j][x] = sign;
        }
    }
}
