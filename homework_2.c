#include <stdio.h>
#include <stdlib.h>

int** get_matrix(int* strings);
int is_simple_cycle(int** matrix, int strings);
void free_matrix(int** matrix, int strings);

int main(int argc, char **argv)
{
    int strings, result;
    int** graph = get_matrix(&strings);
    result = is_simple_cycle(graph, strings);
    if (result == 1)
    {
        printf("It's a simple cycle!");
    }
    else
    {
        printf("It's not a simple cycle...");
    }
    return 0;
}

int** get_matrix(int* strings)
{
    int i;
    printf("Please, write the size of your adjacency matrix: "); // Get the size of matrix in form of "4x5"
    scanf("%d", strings);                        // and assign it to the variables.
    /*if (*strings != *strings)
    {
        printf("Wrong input :(");   // the matrix can be only square
        exit(1);
    }*/
    int** matrix = (int**) malloc(*strings * sizeof(int*));
    for(i = 0; i < *strings; ++i)                                    // Create a two-dimensional array and
    {                                                               // and allocate memory for it.
        matrix[i] = (int*) malloc(*strings * sizeof(int));
    }
    printf("   |");
    for (i = 1; i <= *strings; ++i)  // output of the column numeration
    {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < *strings; ++i)   // input of the user's matrix into 2d array
    {
        printf(" %3d|", (i + 1));
        for(int g = 0; g < *strings; ++g)
        {
            scanf(" %3d", &matrix[i][g]);
            if (matrix[i][g] != 0 && matrix[i][g] != 1)
            {
                printf("Wrong input :(");   // user can write only 0 or 1
                exit(1);
            }
        }
    }

    return matrix;
    /*для вывода записанной в массив матрицы:
    printf("   |");
    for (i = 1; i <= *strings; ++i)
    {
        printf(" %3d", i);
    }
    printf("\n");
    for (i = 0; i < *strings; ++i)
    {
        printf(" %3d|", (i + 1));
        for(int g = 0; g < *strings; ++g)
        {
            printf(" %3d", matrix[i][g]);
        }
        printf("\n");
    }*/
}

int is_simple_cycle(int** matrix, int strings)
{
    int i, prev, next, counter;
    counter = 0;
    for (i = 0; i < strings; ++i)
    {
        //printf("it is the %d iteration of i \n", i);
        for(int g = 0; g < strings; ++g)
        {
            //printf("it is the %d iteration of g \n", g);
            if ((g == i) && (matrix[i][g] == 1))    //checking for noose
            {
                return 0;
            }
            else if (i == 0)
            {
                prev = strings - 1;
                next = 1;
            }
            else if (i == (strings - 1))
            {
                prev = strings - 2;
                next = 0;
            }
            else
            {
                prev = i - 1;
                next = i + 1;
            }

            if (matrix[i][g] == 1 && ((g == prev) || (g == next)))
            {
                ++counter;
            }
        }
    }
    if (counter == strings*2)
    {
        printf("final counter %d\n", counter);
        return 1;
    }
    else
    {
        printf("final counter %d\n", counter);
        return 0;
    }
}