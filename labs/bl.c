#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode *head;
};

struct Graph {
    int numNodes;
    struct AdjList* array;
    int** matrix;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numNodes, int isDirected) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;
    graph->array = (struct AdjList*)malloc(numNodes * sizeof(struct AdjList));

    int i;
    for (i = 0; i < numNodes; ++i)
        graph->array[i].head = NULL;

    if (isDirected) {
        graph->matrix = (int**)malloc(numNodes * sizeof(int*));
        for (i = 0; i < numNodes; ++i) {
            graph->matrix[i] = (int*)malloc(numNodes * sizeof(int));
            for (int j = 0; j < numNodes; ++j)
                graph->matrix[i][j] = 0;
        }
    } else {
        graph->matrix = NULL;
    }

    return graph;
}

void addEdgeDirected(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    if (graph->matrix != NULL)
        graph->matrix[src][dest] = 1;
}

void addEdgeUndirected(struct Graph* graph, int src, int dest) {

    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;

    if (graph->matrix != NULL) {
        graph->matrix[src][dest] = 1;
        graph->matrix[dest][src] = 1;
    }
}

// Function to perform DFS traversal of a graph starting from a given vertex
void DFSUtil(int vertex, struct Graph* graph, int visited[]) {
    visited[vertex] = 1; // Mark the current vertex as visited
    printf("%d ", vertex); // Print the current vertex

    // Traverse all adjacent vertices of the current vertex
    struct AdjListNode* temp = graph->array[vertex].head;
    while (temp != NULL) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex]) // If adjacent vertex is not visited, recursively call DFSUtil
            DFSUtil(adjVertex, graph, visited);
        temp = temp->next;
    }
}

// Function to perform DFS traversal of a graph
void DFS(struct Graph* graph) {
    int visited[MAX_NODES] = {0}; // Mark all vertices as not visited
    int i;
    for (i = 0; i < graph->numNodes; ++i) {
        if (!visited[i])
            DFSUtil(i, graph, visited);
    }
}

int main() {
    int numNodes, numEdges, isDirected, i, src, dest;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &numNodes);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);

    printf("Is the graph directed? (1 for yes, 0 for no): ");
    scanf("%d", &isDirected);

    struct Graph* graph = createGraph(numNodes, isDirected);

    printf("Enter the edges (src dest):\n");
    for (i = 0; i < numEdges; ++i) {
        scanf("%d %d", &src, &dest);
        if (isDirected)
            addEdgeDirected(graph, src, dest);
        else
            addEdgeUndirected(graph, src, dest);
    }

    printf("\nAdjacency List Representation:\n");
    for (i = 0; i < numNodes; ++i) {
        struct AdjListNode* temp = graph->array[i].head;
        printf("Node %d: ", i);
        while (temp) {
            printf("%d -> ", temp->dest);
            temp = temp->next;
        }
        printf("NULL\n");
    }

    if (isDirected) {
        printf("\nAdjacency Matrix Representation:\n");
        for (i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j)
                printf("%d ", graph->matrix[i][j]);
            printf("\n");
        }
    }

    printf("\nDepth First Traversal: ");
    DFS(graph);

    return 0;
}
