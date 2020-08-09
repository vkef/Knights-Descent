#include <stdio.h>  // defines scanf() and printf()
#include <math.h>   //has math functions; exp(x,y)
#include <stdlib.h> //defines rand()
#include <string.h> //define array characters
#include <time.h>   //defines time()

int nenemies(int level, int rows, int cols);
int nblocks(int level, int rows, int cols);
int freeSpot(int i, int j, char **table);
void printTable(char **tab, int rows, int cols);
int move(char *m, int rows, int cols);

char **table;
int knightPos[2] = {0, 0};
int e, money, turn = 1, c = 0, rcase;

int main()
{
    char *moves;
    char name[50];
    int rows = 10, cols = 10, i, j, k, f;
    int level;
    srand(time(NULL));
    printf("\n");
    printf("WELCOME TO KNIGHTS DECENT!\n");
    printf("***************************\n");
    printf("PRESS ANY KEY TO CONTINUE...");

    getchar();

    do
    {
        printf("Height(5-20):");
        scanf("%d", &rows);
    } while (rows < 5 || rows > 20);

    do
    {
        printf("Length(5-20):");
        scanf("%d", &cols);
    } while (cols < 5 || cols > 20);

    do
    {
        printf("Level(1-3):");
        scanf("%d", &level);
    } while (level < 1 || level > 3);

    //Dynamic memory allocation for tables
    table = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < cols; i++)
    {
        table[i] = (char *)malloc(cols * sizeof(char *));
    }

    //Initializing array
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            table[i][j] = '.';
        }
    }

    //Placing knight in a random free spot
    i = rand() % rows;
    j = rand() % cols;
    table[i][j] = '$';
    knightPos[0] = i;
    knightPos[1] = j;
    rcase = 3;
    //Placing enemies in random free spot
    switch (rcase)
    {
    case 1: // triangle

        for (i = 1; i <= nenemies(level, rows, cols); ++i)
        {
            for (j = 1; j <= i; ++j)
            {
                if (c != nenemies(level, rows, cols))
                {
                    e = (rand() % 3) + 1;
                    table[i][j] = e;
                    e = 0;
                    c = c + 1;
                }
            }
        }
        break;
    case 2: // formation

        for (i = 0; i < nenemies(level, rows, cols); i++)
        {
            for (j = 0; j < nenemies(level, rows, cols) / 2; j++)
            {
                if (c != nenemies(level, rows, cols))
                {
                    e = (rand() % 3) + 1;
                    table[i][j] = e;
                    e = 0;
                    c = c + 1;
                }
            }
        }
        break;

    case 3: //invert triangle

        for (i = nenemies(level, rows, cols); i >= 1; i--)
        {
            for (j = 1; j <= i; j++)
            {
                if (c != nenemies(level, rows, cols))
                {
                    e = (rand() % 3) + 1;
                    table[i][j] = e;
                    e = 0;
                    c = c + 1;
                }
            }
        }
        break;
    } //end of switch

    //Placing blocks in a random free spot
    for (k = 0; k < nblocks(level, rows, cols); k++)
    {
        do
        {
            i = rand() % rows;
            j = rand() % cols;

        } while ((freeSpot(i, j, table)) == 0);
        table[i][j] = '#';
    }

    getchar();

    //Calling and Printing 'moves'
    do
    {
        moves = (char *)malloc(rows * cols * sizeof(char));
        gets(moves);
        if (move(moves, rows, cols))
        {
            break;
        }
        system("clear");
        printf("----------MOVE %d----------\n\n", turn);
        printTable(table, rows, cols);
        printf("\n");
        printf("Level money spent:%d\n", money);
        printf("Game money spent: \n");
        printf("Make your move(s):");
        turn = turn + 1;
        money = money + 5;

    } while (1);

    //Freeing Memory

    //for (j = 0; j < cols; j++)
    //{
    //    free(table[j]);
    // }
    //free(table);
    //free(moves);
}

//---------------------------------------------------//
// End of Main
//---------------------------------------------------//

//Function for generating blocks based in level
int nblocks(int level, int rows, int cols)
{
    int cells = rows * cols;
    if (level == 1)
    {
        return 5 * cells / 100;
    }
    else if (level == 2)
    {
        return 5 * cells / 100;
    }
    else if (level == 3)
    {
        return 10 * cells / 100;
    }
}

//Function for generating enemies based in level
int nenemies(int level, int rows, int cols)
{
    int cells = rows * cols;
    if (level == 1)
    {
        return 5 * cells / 100;
    }
    else if (level == 2)
    {
        return 10 * cells / 100;
    }
    else if (level == 3)
    {
        return 10 * cells / 100;
    }
}

//Function for checking if place is empty
int freeSpot(int i, int j, char **table)
{
    if (table[i][j] == '.')
    {
        return 1; //true
    }
    else
    {
        return 0; //false
    }
}

//Function for printing table
void printTable(char **tab, int rows, int cols)
{
    int i, j;
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
            if (table[i][j] == '#' || table[i][j] == '$')
            {
                printf("%c ", table[i][j]);
            }
            else if (table[i][j] != '.' && table[i][j] != '$')
            {
                printf("%d ", table[i][j]);
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
}

//Fuction for generating moves
int move(char *m, int rows, int cols)
{
    int i, k;
    for (i = 0; i < rows * cols; i++)
    {
        if (m[i] == 'x' || m[i] == 'X')
        {
            printf("\n");
            printf("THANK YOU FOR PLAYING!\n");
            return 1;
        }

        //Upward move
        if (m[i] == 'w' || m[i] == 'W')
        {

            if (!(knightPos[0] == 0) && !k == 0)
            {

                if (table[knightPos[0]][knightPos[1]] == '.')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                }
                else
                {
                    table[knightPos[0]][knightPos[1]] = '.';
                }

                if (table[knightPos[0] - 1][knightPos[1]] == '#')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                    return 0;
                }
                table[knightPos[0] - 1][knightPos[1]] = '$';
                knightPos[0]--;
            }
        }
        //Downward move
        if (m[i] == 's' || m[i] == 'S')
        {

            if (!(knightPos[0] == rows - 1))
            {
                if (table[knightPos[0]][knightPos[1]] == '.')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                }
                else
                {
                    table[knightPos[0]][knightPos[1]] = '.';
                }
                if (table[knightPos[0] + 1][knightPos[1]] == '#')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                    return 0;
                }
                table[knightPos[0] + 1][knightPos[1]] = '$';
                knightPos[0]++;
            }
        }

        //Right move
        if (m[i] == 'd' || m[i] == 'D')
        {

            if (!(knightPos[1] == cols - 1))
            {
                if (table[knightPos[0]][knightPos[1]] == '.')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                }
                else
                {
                    table[knightPos[0]][knightPos[1]] = '.';
                }
                if (table[knightPos[0]][knightPos[1] + 1] == '#')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                    return 0;
                }
                table[knightPos[0]][knightPos[1] + 1] = '$';
                knightPos[1]++;
            }
        }
        //Left move
        if (m[i] == 'a' || m[i] == 'A')
        {

            if (!(knightPos[1] == 0))
            {

                if (table[knightPos[0]][knightPos[1]] == '.')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                }
                else
                {
                    table[knightPos[0]][knightPos[1]] = '.';
                }
                if (table[knightPos[0]][knightPos[1] - 1] == '#')
                {
                    table[knightPos[0]][knightPos[1]] = '$';
                    return 0;
                }
                table[knightPos[0]][knightPos[1] - 1] = '$';
                knightPos[1]--;
            }
        }
        return 0;
    }
}
