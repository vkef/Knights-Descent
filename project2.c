#include <stdio.h>  // defines scanf() and printf()
#include <math.h>   //has math functions; exp(x,y)
#include <stdlib.h> //defines rand()
#include <string.h> //
#include <time.h>   //defines time(

int numberOfLions(int level, int rows, int cols);
int freeSpot(int i, int j, char **table);
void printTable(char **tab, int rows, int cols);
int move(char *m, int rows, int cols);

char **table;
char **table2;
int tarzanPos[2] = {0, 0};
int foundJ = 0;
int life = 2;

int main()
{
    char *moves;
    char name[50];
    int rows = 10, cols = 10, i, j, k, lions;
    int level;
    srand(time(NULL));

    do
    {
        printf("Height:\n");
        scanf("%d", &rows);
    } while (rows < 8 || rows > 30);

    do
    {
        printf("Length:\n");
        scanf("%d", &cols);
    } while (cols < 8 || cols > 30);

    do
    {
        printf("Level:\n");
        scanf("%d", &level);
    } while (level < 1 || level > 4);

    //Dynamic memory allocation for tables
    table = (char **)malloc(rows * sizeof(char *));
    table2 = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < cols; i++)
    {
        table[i] = (char *)malloc(cols * sizeof(char *));
        table2[i] = (char *)malloc(cols * sizeof(char *));
    }

    //Initializing array
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            table[i][j] = '#';
            table2[i][j] = '.';
        }
    }
    //Placing T in a random spot
    lions = numberOfLions(level, rows, cols);
    i = rand() % rows;
    j = rand() % cols;
    table[i][j] = 'T';
    tarzanPos[0] = i;
    tarzanPos[1] = j;

    //Placing J in a random spot
    do
    {
        i = rand() % rows;
        j = rand() % cols;
    } while ((freeSpot(i, j, table)) == 0);
    table[i][j] = 'J';

    //Placing enemies in a random spot
    for (k = 0; k < numberOfLions(level, rows, cols); k++)
    {
        do
        {
            i = rand() % rows;
            j = rand() % cols;

        } while ((freeSpot(i, j, table)) == 0);
        table[i][j] = 'L';
    }
    //Placing Z in a random place (Z=2*L)
    for (k = 0; k < (3.0 / 2) * numberOfLions(level, rows, cols); k++)
    {
        do
        {
            i = rand() % rows;
            j = rand() % cols;

        } while ((freeSpot(i, j, table)) == 0);
        table[i][j] = 'Z';
    }

    //Drawing the Table1
    printf("    ");
    for (j = 0; j < cols; j++)
    {
        if (j < 9)
        {
            printf("%d ", j + 1);
        }
        else
        {
            printf("%d", j + 1);
        }
    }
    printf("\n");
    printf("    ");
    for (j = 0; j < cols; j++)
    {
        printf("_ ");
    }
    printf("\n");
    for (i = 0; i < rows; i++)
    {
        if (i < 9)
        {
            printf("%d | ", i + 1);
        }
        else
        {
            printf("%d| ", i + 1);
        }
        for (j = 0; j < cols; j++)
        {
            if (table[i][j] != '#')
            {
                printf("%c ", table[i][j]);
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            table2[i][j] = table[i][j];
            table[i][j] = '#';
        }
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (table2[i][j] == '#')
            {
                table2[i][j] = '.';
            }
        }
    }

    getchar();
    while (getchar() != '\n')
        ;
    {
        printf("    ");
        for (j = 0; j < cols; j++)
        {
            if (j < 9)
            {
                printf("%d ", j + 1);
            }
            else
            {
                printf("%d", j + 1);
            }
        }
        printf("\n");
        printf("    ");
        for (i = 0; i < rows; i++)
        {
            if (i < 9)
            {
                printf("%d | ", i + 1);
            }
            else
            {
                printf("%d| ", i + 1);
            }
            for (j = 0; j < cols; j++)
            {
                if (table2[i][j] == 'T')
                {
                    printf("%c ", table2[i][j]);
                }
                else
                {
                    printf("# ");
                }
            }
        }
        printf("\n");
    }

    life = 2;
    //Caling and Printing 'moves'
    do
    {
        moves = (char *)malloc(rows * cols * sizeof(char));
        gets(moves);
        if (move(moves, rows, cols))
        {
            break;
        }
        if (foundJ == 1)
        {
            printf("\nYou won! Tarzan found J!\n");
            break;
        }
        for (i = 0; i < rows * cols; i++)
        {
            if (moves[i] == 'x' || moves[i] == 'X')
            {
                break;
            }
        }
        printTable(table, rows, cols);
    } while (1);

    //Freeing Memory
    if (foundJ != 1)
    {
        printTable(table, rows, cols);
        printf("\nYou Lost!\n");
    }
    for (j = 0; j < cols; j++)
    {
        free(table[j]);
        free(table2[j]);
    }
    free(table);
    free(table2);
    free(moves);
} //End of main

// Game level
int numberOfLions(int level, int rows, int cols)
{
    int cells = rows * cols;
    if (level == 1)
    {
        return 2 * cells / 100;
    }
    else if (level == 2)
    {
        return 5 * cells / 100;
    }
    else if (level == 3)
    {
        return 10 * cells / 100;
    }
    else if (level == 4)
    {
        return 20 * cells / 100;
    }
}

//Check if place is empty
int freeSpot(int i, int j, char **table)
{
    if (table[i][j] == '#')
    {
        return 1; //true
    }
    else
    {
        return 0; //false
    }
}
//Reading and generating moves
int move(char *m, int rows, int cols)
{
    int i;
    for (i = 0; i < rows * cols; i++)
    {
        //Upper Table
        if (m[i] == 'x' || m[i] == 'X')
        {
            return 1;
        }
        if (m[i] == 'u' || m[i] == 'U')
        {
            if (!(tarzanPos[0] == 0))
            {
                if (table[tarzanPos[0]][tarzanPos[1]] == '@')
                {
                    table[tarzanPos[0]][tarzanPos[1]] == 'Z';
                    table2[tarzanPos[0]][tarzanPos[1]] == 'Z';
                }
                else
                {
                    table[tarzanPos[0]][tarzanPos[1]] == '.';
                    table2[tarzanPos[0]][tarzanPos[1]] == '.';
                }
                if (table2[tarzanPos[0] - 1][tarzanPos[1]] == 'L')
                {
                    table[tarzanPos[0] - 1][tarzanPos[1]] == 'L';
                    return 1;
                }
                if (table2[tarzanPos[0] - 1][tarzanPos[1]] == 'Z')
                {
                    table[tarzanPos[0] - 1][tarzanPos[1]] == '@';
                    life--;
                    tarzanPos[0]--;
                    if (life == 0)
                    {
                        return 1;
                    }
                    return 0;
                }
                if (table2[tarzanPos[0] - 1][tarzanPos[1]] == 'J')
                {
                    foundJ = 1;
                    return 0;
                }
                table[tarzanPos[0] - 1][tarzanPos[1]] == 'T';
                table2[tarzanPos[0] - 1][tarzanPos[1]] == 'T';
                tarzanPos[0]--;
            }
        }
        //Lower Table
        if (m[i] == 'd' || m[i] == 'D')
        {
            if (!(tarzanPos[0] == rows - 1))
            {
                if (table[tarzanPos[0]][tarzanPos[1]] == '@')
                {
                    table[tarzanPos[0]][tarzanPos[1]] == 'Z';
                    table2[tarzanPos[0]][tarzanPos[1]] == 'Z';
                }
                else
                {
                    table[tarzanPos[0]][tarzanPos[1]] == '.';
                    table2[tarzanPos[0]][tarzanPos[1]] == '.';
                }
                if (table2[tarzanPos[0] + 1][tarzanPos[1]] == 'L')
                {
                    table[tarzanPos[0] + 1][tarzanPos[1]] == 'L';
                    return 1;
                }
                if (table2[tarzanPos[0] - 1][tarzanPos[1]] == 'Z')
                {
                    table[tarzanPos[0] + 1][tarzanPos[1]] == '@';
                    life--;
                    tarzanPos[0]++;
                    if (life == 0)
                    {
                        return 1;
                    }
                    return 0;
                }
                if (table2[tarzanPos[0] - 1][tarzanPos[1]] == 'J')
                {
                    foundJ = 1;
                    return 0;
                }
                table[tarzanPos[0] + 1][tarzanPos[1]] == 'T';
                table2[tarzanPos[0] + 1][tarzanPos[1]] == 'T';
                tarzanPos[0]++;
            }
        }
        //Left Table
        if (m[i] == 'l' || m[i] == 'L')
        {
            if (!(tarzanPos[1] == 0))
            {
                if (table[tarzanPos[0]][tarzanPos[1]] == '@')
                {
                    table[tarzanPos[0]][tarzanPos[1]] == 'Z';
                    table2[tarzanPos[0]][tarzanPos[1]] == 'Z';
                }
                else
                {
                    table[tarzanPos[0]][tarzanPos[1]] == '.';
                    table2[tarzanPos[0]][tarzanPos[1]] == '.';
                }
                if (table2[tarzanPos[0]][tarzanPos[1] - 1] == 'L')
                {
                    table[tarzanPos[0]][tarzanPos[1] - 1] == 'L';
                    return 1;
                }
                if (table2[tarzanPos[0]][tarzanPos[1] - 1] == 'Z')
                {
                    table[tarzanPos[0]][tarzanPos[1] - 1] == '@';
                    life--;
                    tarzanPos[1]--;
                    if (life == 0)
                    {
                        return 1;
                    }
                    return 0;
                }
                if (table2[tarzanPos[0]][tarzanPos[1] - 1] == 'J')
                {
                    foundJ = 1;
                    return 0;
                }
                table[tarzanPos[0]][tarzanPos[1] - 1] == 'T';
                table2[tarzanPos[0]][tarzanPos[1] - 1] == 'T';
                tarzanPos[1]--;
            }
        }
        //Right Table
        if (m[i] == 'r' || m[i] == 'R')
        {
            if (!(tarzanPos[1] == cols - 1))
            {
                if (table[tarzanPos[0]][tarzanPos[1]] == '@')
                {
                    table[tarzanPos[0]][tarzanPos[1]] == 'Z';
                    table2[tarzanPos[0]][tarzanPos[1]] == 'Z';
                }
                else
                {
                    table[tarzanPos[0]][tarzanPos[1]] == '.';
                    table2[tarzanPos[0]][tarzanPos[1]] == '.';
                }
                if (table2[tarzanPos[0]][tarzanPos[1] + 1] == 'L')
                {
                    table[tarzanPos[0]][tarzanPos[1] + 1] == 'L';
                    return 1;
                }
                if (table2[tarzanPos[0]][tarzanPos[1] + 1] == 'Z')
                {
                    table[tarzanPos[0]][tarzanPos[1] + 1] == '@';
                    life--;
                    tarzanPos[1]++;
                    if (life == 0)
                    {
                        return 1;
                    }
                    return 0;
                }
                if (table2[tarzanPos[0]][tarzanPos[1] + 1] == 'J')
                {
                    foundJ = 1;
                    return 0;
                }
                table[tarzanPos[0]][tarzanPos[1] + 1] == 'T';
                table2[tarzanPos[0]][tarzanPos[1] + 1] == 'T';
                tarzanPos[1]++;
            }
        }
    }
    return 0;
}

//Generating table
void printTable(char **tab, int rows, int cols)
{
    int i, j;
    printf("    ");
    for (j = 0; j = cols; j++)
    {
        if (j < 9)
        {
            printf("%d ", j + 1);
        }
        else
        {
            printf("%d", j + 1);
        }
    }
    printf("\n");
    printf("    ");
    for (j = 0; j < cols; j++)
    {
        printf("_ ");
    }
    printf("\n");
    for (i = 0; i < rows; i++)
    {
        if (i < 9)
        {
            printf("%d | ", i + 1);
        }
        else
        {
            printf("%d| ", i + 1);
        }
        for (j = 0; j < cols; j++)
        {
            if (table2[i][j] == 'T')
            {
                printf("T ");
            }
            else
            {
                printf("%c ", table[i][j]);
            }
            printf("\n");
        }
    }
}