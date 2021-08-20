#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"
#include "menus.h"
#include "grids.h"
#include "ships.h"
#include "shooting.h"
#include "constants.h"

int main()
{
    srand(time(NULL));

    int lines = DEFAULT_LINES, columns = DEFAULT_COLUMNS, ship_count = DEFAULT_SHIP_COUNT, turn = 0, X_shooting = 0, Y_shooting = 0;
    bool shooting = false;
    char **ships = (char **) malloc(sizeof(char *) * ship_count);
    int *sizes = (int *) malloc(sizeof(int) * ship_count);
    char *signs = (char *) malloc(sizeof(char) * ship_count);

    for (int i = 0; i < ship_count; ++i)
    {
        ships[i] = (char *) malloc(sizeof(char) * 100);

        for (int j = 0; j < strlen(DEFAULT_SHIPS[i]) + 1; ++j)
            ships[i][j] = DEFAULT_SHIPS[i][j];

        sizes[i] = DEFAULT_SIZES[i];
        signs[i] = DEFAULT_SIGNS[i];
    }

    char **pgrid, **cgrid;
    create_grids(&pgrid, &cgrid, lines, columns);

    int screen;
    do
    {
        screen = menu(&ship_count, &ships, &sizes, &signs, &pgrid, &cgrid, &lines, &columns, &turn, &shooting, &X_shooting, &Y_shooting);

        switch (screen)
        {
        case 1:
            {
                place_ships(ship_count, ships, sizes, signs, pgrid, cgrid, lines, columns);
                generate_ships(ship_count, ships, sizes, signs, cgrid, lines, columns);
                display_grids(pgrid, cgrid, lines, columns);

                int month, day, year;
                do
                {
                    month = 0;
                    day = 0;
                    year = 0;

                    printf("When did you sail for the last time? ");
                    int n = scanf("%d/%d/%d", &month, &day, &year);

                    if (n < 3)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Invalid date, please enter one in the format MM/DD/YYYY.\n");
                    } else if (day < 1 || day > get_days_in_month(month, year))
                        printf("This date doesn't exist, please enter a valid one.\n");
                } while (day < 1 || day > get_days_in_month(month, year));

                printf("Well, the computer never sailed... So you will start first.\n");
                turn = 0;
                screen = 2;
            }

        case 2:
            {
                screen = shooting_stage(ship_count, ships, sizes, signs, pgrid, cgrid, lines, columns, turn, shooting, X_shooting, Y_shooting);

                free_grids(pgrid, cgrid, lines, columns);
                create_grids(&pgrid, &cgrid, lines, columns);
                turn = 0;
                shooting = false;
                X_shooting = 0;
                Y_shooting = 0;
            }
            break;
        }
    } while (screen != 0);

    return 0;
}
