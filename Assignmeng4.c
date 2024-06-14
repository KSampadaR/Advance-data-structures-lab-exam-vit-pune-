// BFS and DFS traversals

#include <stdio.h>

#define MAX_NODES 10

struct Graph {
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    int numNodes;
};

void initializeGraph(struct Graph* graph, int numNodes) {
    graph->numNodes = numNodes;

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

void insertEdge(struct Graph* graph, int u, int v) {
    graph->adjacencyMatrix[u][v] = 1;
    graph->adjacencyMatrix[v][u] = 1; 
}

void displayAdjacencyMatrix(struct Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numNodes; i++) {
        for (int j = 0; j < graph->numNodes; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void BFS(struct Graph* graph, int start) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = -1;

    printf("BFS Traversal starting from vertex %d: ", start);

    queue[++rear] = start;
    visited[start] = 1;

    while (front <= rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < graph->numNodes; i++) {
            if (graph->adjacencyMatrix[current][i] && !visited[i]) {
                
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}


void DFS(struct Graph* graph, int start) {
    int visited[MAX_NODES] = {0};
    int stack[MAX_NODES];
    int top = -1;

    printf("DFS Traversal starting from vertex %d: ", start);

    stack[++top] = start;
    visited[start] = 1;

    while (top != -1) {
        int current = stack[top--];
        printf("%d ", current);

        for (int i = 0; i < graph->numNodes; i++) {
            if (graph->adjacencyMatrix[current][i] && !visited[i]) {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}


int main() {
    struct Graph graph;
    int numNodes, numEdges, u, v, start;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    initializeGraph(&graph, numNodes);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);

      //  if (u < 0 || u >= numNodes || v < 0 || v >= numNodes) {
         //   printf("Invalid vertices!\n");
        //    i--;
          //  continue;
        //}

        insertEdge(&graph, u, v);
    }

    displayAdjacencyMatrix(&graph);

    printf("Enter the starting vertex for BFS and DFS: ");
    scanf("%d", &start);

    BFS(&graph, start);

    printf("DFS Traversal starting from vertex %d: ", start);
    int visited[MAX_NODES] = {0};
    DFS(&graph, start);
    printf("\n");

    return 0;
}

//   (0)
//   / \
//  /   \
//(1)---(2)
// | \   |
// |  \  |
// |   \ |
//(4)---(3)
