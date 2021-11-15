#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define f(i,a,n) for( int i = a; i<n; i++)

int c = 0;

// structure for connected verices
typedef struct adj_node {
    int vertex;
    struct adj_node *link;
} node;
// structure to store color time etc.
typedef struct adj_list {
    int color;
    node *head;
} list;

// structure to store all vertex
typedef struct Graph {
    int total_v;
    list *arr;
} graph;

node * create_node (int); // to create node
graph * create_graph (int);// to create graph
void print (graph *);// print graph
void print_color (graph *, int); // print color of specific vertex or node of planar graph
void add ( graph *, int , int);// add edge in case of undirected graph
bool back_track (graph *, int, int );
void five_color ( graph *);

int main () {
    graph *g;
    int vertex; // no. of regions in the map
    printf("No. of regions in the map: ");
    scanf("%d", &vertex);
    g = create_graph(vertex);
    printf("The regions with connected boundaries i and j (1,2,..no. of regions) and when you are done type -1 -1 to exit\n");
    int i, j;
    scanf("%d %d", &i, &j);
    while ( i >0 && j > 0 ) {
        add(g, i-1, j-1);
        scanf("%d %d", &i, &j);
    }
    five_color(g);
    print(g);
}

// creating graph with v vertices
graph * create_graph (int v) {
    graph *temp = (graph *) malloc (sizeof(graph));
    temp ->total_v = v;
    temp->arr = (list *) malloc(v*sizeof(graph));
    f(i,0,v) temp->arr[i].head = NULL;
    f(i,0,v) temp->arr[i].color = -1;
    return temp;
}

// creating node with vertex v
node * create_node (int v) {
    node *temp = (node *) malloc(sizeof(node));
    temp -> vertex = v;
    temp -> link = NULL;
    return temp;
}

// adding edges (s,v) and (v,s) in undirected graph g1
void add (graph *g1, int s, int v) {
    node *temp = create_node(v);
    list *temp1 = (g1->arr + s);
    // adding edge (s,v) in undirected graph g1
    if (temp1->head == NULL) {
        g1->arr[s].head = temp;
        
    }
    else {
        temp -> link = g1->arr[s].head;
        g1->arr[s].head = temp;
    }
    temp = create_node(s);
    // adding edge (v,s) in undirected graph g1
    if (g1->arr[v].head == NULL) g1->arr[v].head = temp;
    else {
        temp -> link = g1->arr[v].head;
        g1->arr[v].head = temp;
    }
}

// printing graph g
void print (graph * g) {
    printf("Your graph is as follows:\n");
    f(i,0,g->total_v) {
        char s[50];
        switch (g->arr[i].color) {
            case 0:
            {
                strcpy(s,"Red");
                break;
            }
            case 1:
            {
                strcpy(s, "Blue");
                break;
            }
            case 2:
            {
                strcpy(s, "Green");
                break;
            }
            case 3:
            {
                strcpy(s, "Yellow");
                break;
            }
            case 4:
            {
                strcpy(s, "Voilet");
                break;
            }
            default:
                break;
        }
        printf("vertex %d of %s color: ", i + 1, s);
        node *temp = g->arr[i].head;
        while(temp) {
            char s[50];
            switch (g->arr[temp->vertex].color) {
                case 0:
                {
                    strcpy(s,"Red");
                    break;
                }
                case 1:
                {
                    strcpy(s, "Blue");
                    break;
                }
                case 2:
                {
                    strcpy(s, "Green");
                    break;
                }
                case 3:
                {
                    strcpy(s, "Yellow");
                    break;
                }
                case 4:
                {
                    strcpy(s, "Voilet");
                    break;
                }
                default:
                    break;
            }
            if (temp == g->arr[i].head) printf("%d(%s)", temp ->vertex + 1, s);
            else printf(" -> %d(%s)", temp->vertex + 1, s);
            temp = temp->link;
        }
        printf("\n");
    }
}

bool back_track (graph *g,int s, int x) {
    list *l = &g->arr[s];
    node *temp = l->head;
    while ( temp != NULL ) {
        list *temp1 = &g->arr[temp->vertex];
        if (x == temp1->color) return 0;
        temp = temp->link;
    }
    return 1;
}

void five_color (graph *g) {
    f(i,0,g->total_v) {
        if ( g->arr[i].color <0) {
            while (!back_track(g, i, c)) {
                if ( c== 4) c = 0;
                else c++;
            }
            g->arr[i].color = c;
//            f(j,0,5) {
//                if (back_track(g, i, j)) {
//                    g->arr[i].color = j;
//                    break;
//                }
//            }
        }
    }
}


