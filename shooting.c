#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "save.h"
#include "grids.h"

void shoot_computer(char **pgrid, int lines, int columns, int *x, int *y, bool *shooting, int *X_shooting, int *Y_shooting)
{
    if (!*shooting)
    {
        do
        {
            *x = rand() % columns;
            *y = rand() % lines;
        } while (pgrid[*y][*x] == 'O' || pgrid[*y][*x] == 'X');
    }
    else
    {
        *x = *X_shooting;
        *y = *Y_shooting;
        while (pgrid[*y][*x] == 'X' && *x != 0)
            --*x;
        if (pgrid[*y][*x] != 'O' && pgrid[*y][*x] != 'X')
            return;

        *x = *X_shooting;
        *y = *Y_shooting;
        while (pgrid[*y][*x] == 'X' && *x != columns - 1)
            ++*x;
        if (pgrid[*y][*x] != 'O' && pgrid[*y][*x] != 'X')
            return;

        *x = *X_shooting;
        *y = *Y_shooting;
        while (pgrid[*y][*x] == 'X' && *y != 0)
            --*y;
        if (pgrid[*y][*x] != 'O' && pgrid[*y][*x] != 'X')
            return;

        *x = *X_shooting;
        *y = *Y_shooting;
        while (pgrid[*y][*x] == 'X' && *y != 0)
            ++*y;
        if (pgrid[*y][*x] != 'O' && pgrid[*y][*x] != 'X')
            return;

        *shooting = false; // Give up when no direction is available
        do
        {
            *x = rand() % columns;
            *y = rand() % lines;
        } while (pgrid[*y][*x] == 'O' || pgrid[*y][*x] == 'X');
    }
}

int shooting_stage(int ship_count, char **ships, int *sizes, char *signs, char **pgrid, char **cgrid, int lines, int columns, int turn, bool shooting, int X_shooting, int Y_shooting)
{
    int *pshot = (int *) malloc(sizeof(int) * ship_count);
    int *cshot = (int *) malloc(sizeof(int) * ship_count);
    for (int i = 0; i < ship_count; ++i)
    {
        pshot[i] = sizes[i];
        cshot[i] = sizes[i];
    }

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (pgrid[i][j] != ' ')
            {
                for (int k = 0; k < ship_count; ++k)
                {
                    if (pgrid[i][j] == signs[k])
                    {
                        --cshot[k];
                        break;
                    }
                }
            }

            if (cgrid[i][j] != ' ')
            {
                for (int k = 0; k < ship_count; ++k)
                {
                    if (cgrid[i][j] == signs[k])
                    {
                        --pshot[k];
                        break;
                    }
                }
            }
        }
    }

    int psunk = 0, csunk = 0;
    for (int i = 0; i < ship_count; ++i)
    {
        if (pshot[i] == sizes[i])
            ++psunk;

        if (cshot[i] == sizes[i])
            ++csunk;
    }

    int quit = 0;
    do
    {
        if (turn == 0)
        {
            int x, y;
            do
            {
                char coordinates[100];
                printf("Where would you like to shoot? ");
                scanf("%s", coordinates);

                if ((strlen(coordinates) == 1 && coordinates[0] == 'q') || strcmp(coordinates, "quit") == 0)
                {
                    save_game(ship_count, ships, sizes, signs, pgrid, cgrid, lines, columns, turn, shooting, X_shooting, Y_shooting);
                    printf("This game's state has been saved. You can select \"Load the previous save\" in the menu to resume it next time.\n");
                    quit = 1;
                    break;
                }

                if (strlen(coordinates) != 0 && strlen(coordinates) != 1)
                {
                    x = toupper(coordinates[0]) - 'A';
                    y = atoi(coordinates + 1) - 1;
                }
                else
                {
                    x = -1;
                    y = -1;
                }

                if (x < 0 || x >= columns || y < 0 || y >= lines)
                    printf("The position you entered is invalid. It should be between A1 and %c%d.\n", 'A' + (columns - 1), lines);
                else if (cgrid[y][x] == 'O' || cgrid[y][x] == 'X')
                    printf("You have already shot at this position. Try somewhere else.\n");
            } while (x < 0 || x >= columns || y < 0 || y >= lines || cgrid[y][x] == 'O' || cgrid[y][x] == 'X');

            if (quit) break;

            if (cgrid[y][x] != ' ')
            {
                for (int i = 0; i < ship_count; ++i)
                {
                    if (cgrid[y][x] == signs[i])
                    {
                        ++pshot[i];
                        if (pshot[i] == sizes[i])
                        {
                            printf("\nYou sank an enemy ship! Well played.\n\n");
                            ++psunk;
                            turn = 1;
                        }
                        else
                            printf("\nYou touched an enemy ship!\n\n");
                        break;
                    }
                }

                cgrid[y][x] = 'X';
                display_grids(pgrid, cgrid, lines, columns);
                sleep(2);
            }
            else
            {
                cgrid[y][x] = 'O';
                turn = 1;
                display_grids(pgrid, cgrid, lines, columns);
                sleep(1);
            }
        }
        else
        {
            int x, y;
            shoot_computer(pgrid, lines, columns, &x, &y, &shooting, &X_shooting, &Y_shooting);

            if (pgrid[y][x] != ' ')
            {
                for (int i = 0; i < ship_count; ++i)
                {
                    if (pgrid[y][x] == signs[i])
                    {
                        ++cshot[i];
                        if (cshot[i] == sizes[i])
                        {
                            shooting = false;
                            printf("\nThe enemy sank your %s (%d squares)!\n\n", ships[i], sizes[i]);
                            ++csunk;
                            turn = 0;
                        }
                        else
                        {
                            shooting = true;
                            X_shooting = x;
                            Y_shooting = y;
                            printf("\nThe enemy touched your %s (%d/%d)!\n\n", ships[i], cshot[i], sizes[i]);
                        }
                        break;
                    }
                }

                pgrid[y][x] = 'X';
                display_grids(pgrid, cgrid, lines, columns);
                sleep(2);
            }
            else
            {
                pgrid[y][x] = 'O';
                turn = 0;
                display_grids(pgrid, cgrid, lines, columns);
                sleep(1);
            }
        }
    } while (psunk != ship_count && csunk != ship_count);

    free(pshot);
    free(cshot);

    if (psunk == ship_count)
        printf("Congratulations, you won this game of battleship!!!\n\n");
    else if (csunk == ship_count)
        printf("Sorry, you lost this game of battleship. Looks like the AI takeover has begun.\n\n");

    if (quit)
        return 0;
    else
        return 1;
}
