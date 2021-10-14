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
void mem_clear(struct graph* graph_ptr);

int main(void)
{
    bool result;
    struct graph our_graph = get_graph();
    result = is_simple_cycle(our_graph);
    if (result)
    {
        printf("It's a simple cycle!\n");
    }
    else {
        printf("It's not a simple cycle...\n");
    }
    graph_vis(our_graph);
    mem_clear(&our_graph);
    system("mimeopen graph.png");
    return 0;
}

struct graph get_graph()
{
    int i;
    struct graph u_graph;
    //struct graph* graph_p = &u_graph;
    printf("Please, write the size of your adjacency matrix: ");   // Get the size of matrix in form of "4"
    scanf("%d", &u_graph.length);                                  // and assign it to the variables.
    bool** matrix = (bool**) malloc(u_graph.length * sizeof(bool*));
    for(i = 0; i < u_graph.length; ++i)                                   // Create a two-dimensional bool array and
    {                                                                     // and allocate memory for it.
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
        }
    }
    u_graph.matrix = matrix;
    return u_graph;
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
        return true;
    }
    else
    {
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
            for (int k = 0; k < u_graph.matrix[i][g]; ++k)
            {
                fprintf(dot, "%d -- %d;\n\t", (i+1), (g+1));
            }
        }
    }
    fprintf(dot, "}");
    fclose(dot);
    system("dot -Tpng graph.dot -o graph.png");
}
void mem_clear(struct graph* graph_ptr)
{
    for (int i = 0; i < graph_ptr -> length; ++i)
    {
        free(graph_ptr -> matrix[i]);
    }
    free(graph_ptr -> matrix);
}