//Write a Program to implement Dijkstra’s algorithm 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Node {
    int dest;
    int weight;
    struct Node* next;
};

struct Graph {
    struct Node* array[MAX_VERTICES];
    int V;
};

struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    for (int i = 0; i < V; ++i)
        graph->array[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

void dijkstra(struct Graph* graph, int src) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];

    for (int i = 0; i < graph->V; ++i) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < graph->V - 1; ++count) {
        int u, min = INT_MAX;

        for (int v = 0; v < graph->V; ++v) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        visited[u] = 1;

        struct Node* temp = graph->array[u];
        while (temp != NULL) {
            if (!visited[temp->dest] && dist[u] != INT_MAX &&
                dist[u] + temp->weight < dist[temp->dest]) {
                dist[temp->dest] = dist[u] + temp->weight;
            }
            temp = temp->next;
        }
    }

    printf("Shortest distances from source vertex %d:\n", src);
    for (int i = 0; i < graph->V; ++i) {
        printf("Vertex %d -> Distance: %d\n", i, dist[i]);
    }
}

int main() {
    int V, E;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph* graph = createGraph(V);

    printf("Enter edges in the format (source destination weight):\n");
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    dijkstra(graph, source);

    return 0;
}


