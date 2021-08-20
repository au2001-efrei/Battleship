#include <stdio.h>
#include <stdlib.h>

#include "save.h"
#include "grids.h"

void customize_fleet(int *ship_count, char ***ships, int **sizes, char **signs, int lines, int columns)
{
    int option;
    do
    {
        printf("\n###### Your fleet ######\n\n");
        printf("Number of ships: %d\n", *ship_count);
        for (int i = 0; i < *ship_count; ++i)
            printf("#%d. %s (%c): %d squares\n", i + 1, (*ships)[i], (*signs)[i], (*sizes)[i]);

        option = 0;
        do
        {
            printf("\nSelect an option among:\n1. Add a ship to your fleet\n2. Change the name of a ship\n3. Change the size of a ship\n4. Delete a ship from your fleet\n5. Go back to the settings\n");
            int n = scanf("%d", &option);

            if (n < 1)
            {
                char null[100];
                scanf("%s", null);
                printf("Please enter an integer.\n");
            }
            else if (option < 1 || option > 5)
                printf("Please select an option between 1 and 5.\n");
        } while (option < 1 || option > 5);

        switch (option)
        {
        case 1:
            {
                *ships = (char **) realloc(*ships, sizeof(char *) * (*ship_count + 1));
                *sizes = (int *) realloc(*sizes, sizeof(int) * (*ship_count + 1));
                *signs = (char *) realloc(*signs, sizeof(char) * (*ship_count + 1));

                (*ships)[*ship_count] = (char *) malloc(sizeof(char) * 100);
                printf("What should be the name of your new ship? ");
                scanf("%s", (*ships)[*ship_count]);

                (*sizes)[*ship_count] = 0;
                do
                {
                    printf("What should be its size? ");
                    int n = scanf("%d", &(*sizes)[*ship_count]);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter an integer.\n");
                    }
                    else if ((*sizes)[*ship_count] < 1 || ((*sizes)[*ship_count] > lines && (*sizes)[*ship_count] > columns))
                        printf("This size is invalid, please select one between 1 and %d.\n", lines >= columns? lines : columns);
                } while ((*sizes)[*ship_count] < 1 || ((*sizes)[*ship_count] > lines && (*sizes)[*ship_count] > columns));

                scanf("%c", &(*signs)[*ship_count]); // This scanf always returns \n so we use this line to discard it
                (*signs)[*ship_count] = '\0';
                do
                {
                    printf("What should be its symbol? ");
                    int n = scanf("%c", &(*signs)[*ship_count]);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter a valid symbol, different from O and X.\n");
                    }
                } while ((*signs)[*ship_count] == '\0' || (*signs)[*ship_count] == 'O' || (*signs)[*ship_count] == 'X');

                // TODO: Check that this symbol is not already used
                // TODO: Check that all the ships can fit on the grid

                ++(*ship_count);
            }
            break;

        case 2:
            {
                int i = 0;
                do
                {
                    printf("Which ship's name do you want to change? ");
                    int n = scanf("%d", &i);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter an integer.\n");
                    }
                    else if (i < 1 || i > *ship_count)
                        printf("This boat doesn't exist, please select one between between 1 and %d.\n", *ship_count);
                } while (i < 1 || i > *ship_count);
                --i;

                printf("What should be its new name? ");
                scanf("%s", (*ships)[i]);

                scanf("%c", &(*signs)[i]); // This scanf always returns \n so we use this line to discard it
                (*signs)[i] = '\0';
                do
                {
                    printf("What should be its new symbol? ");
                    int n = scanf("%c", &(*signs)[i]);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter a valid symbol, different from O and X.\n");
                    }
                } while ((*signs)[i] == '\0' || (*signs)[i] == 'O' || (*signs)[i] == 'X');

                // TODO: Check that this symbol is not already used
            }
            break;

        case 3:
            {
                int i = 0;
                do
                {
                    printf("Which ship's size do you want to change? ");
                    int n = scanf("%d", &i);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter an integer.\n");
                    }
                    else if (i < 1 || i > *ship_count)
                        printf("This boat doesn't exist, please select one between between 1 and %d.\n", *ship_count);
                } while (i < 1 || i > *ship_count);
                --i;

                (*sizes)[i] = 0;
                do
                {
                    printf("What should be its size? ");
                    int n = scanf("%d", &(*sizes)[i]);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter an integer.\n");
                    }
                    else if ((*sizes)[i] < 1 || ((*sizes)[i] > lines && (*sizes)[i] > columns))
                        printf("This size is invalid, please select one between 1 and %d.\n", lines >= columns? lines : columns);
                } while ((*sizes)[i] < 1 || ((*sizes)[i] > lines && (*sizes)[i] > columns));

                // TODO: Check that all the ships can fit on the grid
            }
            break;

        case 4:
            {
                int i = 0;
                do
                {
                    printf("Which ship do you want to delete? ");
                    int n = scanf("%d", &i);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter an integer.\n");
                    }
                    else if (i < 1 || i > *ship_count)
                        printf("This boat doesn't exist, please select one between between 1 and %d.\n", *ship_count);
                } while (i < 1 || i > *ship_count);
                --i;

                free((*ships)[i]);

                --(*ship_count);
                for (; i < *ship_count; ++i)
                {
                    (*ships)[i] = (*ships)[i + 1];
                    (*sizes)[i] = (*sizes)[i + 1];
                    (*signs)[i] = (*signs)[i + 1];
                }

                *ships = (char **) realloc(*ships, sizeof(char *) * *ship_count);
                *sizes = (int *) realloc(*sizes, sizeof(int) * *ship_count);
                *signs = (char *) realloc(*signs, sizeof(char) * *ship_count);
            }
            break;
        }
    } while (option != 5);
}

void settings(int *ship_count, char ***ships, int **sizes, char **signs, char ***pgrid, char ***cgrid, int *lines, int *columns)
{
    int option;
    do
    {
        printf("\n###### Settings ######\n\n");
        printf("Size of the grid: %d x %d\nNumber of ships: %d\n", *lines, *columns, *ship_count);

        option = 0;
        do
        {
            printf("\nSelect an option among:\n1. Customize your fleet\n2. Change the size of the grid\n3. Go back to the menu\n");
            int n = scanf("%d", &option);

            if (n < 1)
            {
                char null[100];
                scanf("%s", null);
                printf("Please enter an integer.\n");
            }
            else if (option < 1 || option > 3)
                printf("Please select an option between 1 and 3.\n");
        } while (option < 1 || option > 3);

        switch (option)
        {
        case 1:
            customize_fleet(ship_count, ships, sizes, signs, *lines, *columns);
            break;

        case 2:
            {
                int previous_lines = *lines, previous_columns = *columns;

                *lines = 0;
                do
                {
                    printf("Give the number of lines: ");
                    int n = scanf("%d", lines);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter an integer.\n");
                    }
                    else if (*lines < 1 || *lines > 99) // We limit at 99 lines not to have to handle numbers with 3 digits
                        printf("The number of lines must be between 1 and 99.\n");
                } while (*lines < 1 || *lines > 99);

                *columns = 0;
                do
                {
                    printf("Give the number of columns: ");
                    int n = scanf("%d", columns);

                    if (n < 1)
                    {
                        char null[100];
                        scanf("%s", null);
                        printf("Please enter an integer.\n");
                    }
                    else if (*columns < 1 || *columns > 26) // We limit at 26 columns not to have to handle when there are more columns than letters in the alphabet
                        printf("The number of columns must be between 1 and 26.\n");
                } while (*columns < 1 || *columns > 26);

                // TODO: Check that all the ships can fit on the grid

                /*
                for (int i = *lines; i < previous_lines; ++i)
                {
                    free((*pgrid)[i]);
                    free((*cgrid)[i]);
                }

                *pgrid = (char **) realloc(*pgrid, sizeof(char) * *lines);
                *cgrid = (char **) realloc(*cgrid, sizeof(char) * *lines);

                for (int i = 0; i < *lines && i < previous_lines; ++i)
                {
                    (*pgrid)[i] = (char *) realloc((*pgrid)[i], sizeof(char) * *columns);
                    (*cgrid)[i] = (char *) realloc((*cgrid)[i], sizeof(char) * *columns);

                    for (int j = previous_columns; j < *columns; ++j)
                    {
                        (*pgrid)[i][j] = ' ';
                        (*cgrid)[i][j] = ' ';
                    }
                }

                for (int i = previous_lines; i < *lines; ++i)
                {
                    (*pgrid)[i] = (char *) malloc(sizeof(char) * *columns);
                    (*cgrid)[i] = (char *) malloc(sizeof(char) * *columns);

                    for (int j = 0; j < *columns; ++j)
                    {
                        (*pgrid)[i][j] = ' ';
                        (*cgrid)[i][j] = ' ';
                    }
                }
                */

                free_grids(*pgrid, *cgrid, previous_lines, previous_columns);
                create_grids(pgrid, cgrid, *lines, *columns);
            }
            break;
        }
    } while (option != 3);
}

int menu(int *ship_count, char ***ships, int **sizes, char **signs, char ***pgrid, char ***cgrid, int *lines, int *columns, int *turn, bool *shooting, int *X_shooting, int *Y_shooting)
{
    int option;
    do
    {
        printf("\n###### Main menu ######\n");

        option = 0;
        do
        {
            printf("\nSelect an option among:\n1. Play the game\n2. Open the settings\n3. Load the previous save\n4. Quit the game\n");
            int n = scanf("%d", &option);

            if (n < 1)
            {
                char null[100];
                scanf("%s", null);
                printf("Please enter an integer.\n");
            }
            else if (option < 1 || option > 4)
                printf("Please select an option between 1 and 4.\n");
        } while (option < 1 || option > 4);

        switch (option)
        {
        case 2:
            settings(ship_count, ships, sizes, signs, pgrid, cgrid, lines, columns);
            break;
        case 3:
            if (!load_game(ship_count, ships, sizes, signs, pgrid, cgrid, lines, columns, turn, shooting, X_shooting, Y_shooting))
            {
                printf("Failed to load the previous save. None exists or it was altered since then.\n");
                option = 0;
            }
            break;
        }
    } while (option != 1 && option != 3 && option != 4);

    if (option == 1)
        return 1;
    else if (option == 3)
        return 2;
    else
        return 0;
}
