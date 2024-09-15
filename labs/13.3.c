//3.Write a C program to perform the BFS traversal for a given graph (the program should be able to
//consider directed and undirected graph using the below representations:
//c.adjacency list
//d.adjacency matrix

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdgeUndirected(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void addEdgeDirected(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void BFS(struct Graph* graph, int startVertex) {
    struct Node* queue[graph->numVertices];
    int front = 0, rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear++] = graph->adjLists[startVertex];

    printf("BFS traversal starting from vertex %d: ", startVertex);

    while (front < rear) {
        struct Node* currentNode = queue[front++];
        printf("%d ", currentNode->vertex);

        while (currentNode != NULL) {
            int adjVertex = currentNode->vertex;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                queue[rear++] = graph->adjLists[adjVertex];
            }
            currentNode = currentNode->next;
        }
    }
}

void display(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        printf("\nAdjacency list of vertex %d\n ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int vertices, edges, choice, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &src, &dest);
        printf("Is the graph directed? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
        if (choice)
            addEdgeDirected(graph, src, dest);
        else
            addEdgeUndirected(graph, src, dest);
    }

    printf("\nAdjacency list representation of the graph:\n");
    display(graph);

    printf("\nEnter the starting vertex for BFS: ");
    scanf("%d", &src);
    BFS(graph, src);

    return 0;
}
