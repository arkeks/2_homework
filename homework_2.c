#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct graph
{
    int length;
    bool** matrix;
};

struct graph get_graph();
bool is_simple_cycle(struct graph u_graph);
void graph_vis(struct graph);
//void free_matrix(int** matrix, int strings);

int main(void)
{
    int a;
    bool result;
    struct graph our_graph = get_graph();
    result = is_simple_cycle(our_graph);
    if (result == true)
    {
        printf("It's a simple cycle!");
    }
    else
    {
        printf("It's not a simple cycle...");
    }
    graph_vis(our_graph);
    a = system("dot -Tpng graph.dot -o graph.png");
    printf("%d", a);
    return 0;
}

struct graph get_graph()
{
    int i;
    struct graph u_graph;
    //struct graph* graph_p = &u_graph;
    printf("Please, write the size of your adjacency matrix: "); // Get the size of matrix in form of "4x5"
    scanf("%d", &u_graph.length);                                         // and assign it to the variables.
    bool** matrix = (bool**) malloc(u_graph.length * sizeof(bool*));
    for(i = 0; i < u_graph.length; ++i)                                        // Create a two-dimensional bool array and
    {                                                                   // and allocate memory for it.
        matrix[i] = (bool*) malloc(u_graph.length * sizeof(bool));
    }
    printf("   |");
    for (i = 1; i <= u_graph.length; ++i)  // output of the column numeration
    {
        printf("%d ", i);
    }
    printf("\n");
    for (i = 0; i < u_graph.length; ++i)   // input the user's matrix into 2d array
    {
        printf("  %d|", (i + 1));
        for(int g = 0; g < u_graph.length; ++g)
        {
            scanf(" %3d", (int*)&matrix[i][g]);
            if (matrix[i][g] != 0 && matrix[i][g] != 1)
            {
                printf("Wrong input :(");   // user can write only 0 or 1
                exit(1);
            }
        }
    }
    u_graph.matrix = matrix;
    return u_graph;
    /*для вывода записанной в массив матрицы:
    printf("   |");
    for (i = 1; i <= u_graph.length; ++i)
    {
        printf(" %3d", i);
    }
    printf("\n");
    for (i = 0; i < u_graph.length; ++i)
    {
        printf(" %3d|", (i + 1));
        for(int g = 0; g < u_graph.length; ++g)
        {
            printf(" %3d", u_graph.matrix[i][g]);
        }
        printf("\n");
    }*/
}

bool is_simple_cycle(struct graph u_graph)
{
    int i, prev, next, counter;
    counter = 0;
    for (i = 0; i < u_graph.length; ++i)
    {
        for(int g = 0; g < u_graph.length; ++g)
        {
            if ((g == i) && (u_graph.matrix[i][g] == 1))    //checking for noose
            {
                return 0;
            }
            else if (i == 0)
            {
                prev = u_graph.length - 1;
                next = 1;
            }
            else if (i == (u_graph.length - 1))
            {
                prev = i - 1;
                next = 0;
            }
            else
            {
                prev = i - 1;
                next = i + 1;
            }
            if (u_graph.matrix[i][g] == 1)
            {
                if (g == next)
                {
                    ++counter;
                }
                else if (g == prev);
                else
                {
                    --counter;
                }
            }
        }
    }
    if (counter == u_graph.length)
    {
        printf("final counter %d\n", counter);
        return true;
    }
    else
    {
        printf("final counter %d\n", counter);
        return false;
    }
}
void graph_vis(struct graph u_graph)
{
    FILE *dot = fopen("graph.dot", "w");
    fprintf(dot, "graph test {\n\t");
    for (int i = 0; i < u_graph.length; ++i)
    {
        for (int g = i; g < u_graph.length; ++g)
        {
            if (u_graph.matrix[i][g] == 1)
            {
                fprintf(dot, "%d -- %d;\n\t", i, g);
            }
        }
    }
    fprintf(dot, "}");
}