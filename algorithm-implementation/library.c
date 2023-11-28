#include "library.h"

#define UNCLASSIFIED 0
#define NOISE (-1)
#define CLUSTER(N) N
#define NEXT_CLUSTER(N) (N + 1)
#define TRUE 1
#define FALSE 0

//not like voronoi diagram

void printArray(const int* arr, size_t size) {
    printf("[ ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

double calculateDistance(const double* data_in, const size_t * dimensions, int i1, int i2) {
    double distance = 0;
    for(int j = 0; j < dimensions[0]; j++) {
        double distanceInDimensionJ = (data_in[i1+dimensions[1]*j] - data_in[i2+dimensions[1]*j]);
        distance += distanceInDimensionJ * distanceInDimensionJ;
    }
    return sqrt(distance);
}

void setClusterId(int* clusterIds, int index, int newId) {
    clusterIds[index] = newId;
}

void setClusterIds(int* clusterIds, const int* indexes, int indexes_size, int newId) {
    while (indexes_size--) {
        clusterIds[indexes[indexes_size]] = newId;
    }
}

int getClusterId(int* clusterIds, int index) {
    return clusterIds[index];
}

int* findNeighbors(const double* data_in, const size_t * dimensions, int index, double epsilon, int* outNeighborCount) {
//    printf("fn start\n");
    struct Stack* stack = createStack(5);

    for(int i = 0; i < dimensions[1]; i++) {
        double distance = calculateDistance(data_in, dimensions, i, index);
        if(distance < epsilon) {
            push(stack, i);
        }
    }

    (*outNeighborCount) = stack->top + 1;

//    free(*outNeighborIndexes);
//    printf("fn mid: %d\n", *outNeighborCount);
//    int* outNeighborIndexes = (int*) malloc((*outNeighborCount) * sizeof(int));
//
//    printf("fn mid2\n");
//
//    memcpy(outNeighborIndexes, stack->array, (*outNeighborCount) * sizeof(int));
//    printf("fn mid3\n");

//    freeStack(stack);
    int * data = stack->array;
//    printArray(stack->array, (*outNeighborCount));

    free(stack);
//    printArray(stack->array, (*outNeighborCount));

//    printf("fn end\n");
    return data;
}

int expandCluster(const double* points, const size_t * points_dimensions, int pointIndex, int currentClusterId,
                  double epsilon, int minPts, int * pointClusterIds) {
//    printf("expand cluster call\n");


     // = (int*) malloc(sizeof(int));
    int neighborCount = 0;

    int* neighbors = findNeighbors(points, points_dimensions, pointIndex, epsilon, &neighborCount);

    if(neighborCount < minPts) {
        pointClusterIds[pointIndex] = NOISE;
        free(neighbors);
        return FALSE;
    }
    else {
        struct Stack* neighborsStack = (struct Stack*) malloc(sizeof(struct Stack));
        neighborsStack->capacity = neighborCount;
        neighborsStack->array = neighbors;
        neighborsStack->top = neighborCount - 1;

        setClusterIds(pointClusterIds, neighbors, neighborCount, currentClusterId);

        while (!isEmpty(neighborsStack)) {
//            printf("iter\n");
            int secDegreeNeighborCount = 0;

            int currentPoint = pop(neighborsStack);

//            printf("point: %d\n", currentPoint);

            int* secDegreeNeighbors = findNeighbors(points, points_dimensions, currentPoint, epsilon, &secDegreeNeighborCount);

            if(secDegreeNeighborCount >= minPts) {
                for(int j = 0; j < secDegreeNeighborCount; j++) {
                    int secDegreeNeighbor = secDegreeNeighbors[j];
                    if(getClusterId(pointClusterIds, secDegreeNeighbor) == UNCLASSIFIED ||
                       getClusterId(pointClusterIds, secDegreeNeighbor) == NOISE) {
                        if(getClusterId(pointClusterIds, secDegreeNeighbor) == UNCLASSIFIED) {
                            push(neighborsStack, secDegreeNeighbor);
                        }
                        setClusterId(pointClusterIds, secDegreeNeighbor, currentClusterId);
                    }
                }
            }

            free(secDegreeNeighbors);
        }
        freeStack(neighborsStack);
    }
//    printf("expand cluster end\n");
    return TRUE;
}

int* DBSCAN(const double* dataIn, const size_t* dimensions, int* clusterIds,
            double epsilon, int minPts) {
//    printf("STARTED\n");

    size_t m = dimensions[0];
    size_t n = dimensions[1];

    int currentClusterId = CLUSTER(1);

//    clusterIds = (int *) malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++) {
        clusterIds[i] = UNCLASSIFIED;
    }

//    printArray(clusterIds, n);

    for (int i = 0; i < n; i++) {
        if(clusterIds[i] == UNCLASSIFIED) {
            if(expandCluster(dataIn, dimensions, i, currentClusterId, epsilon, minPts, clusterIds)) {
//                printf("expanded cluster\n");

                currentClusterId = NEXT_CLUSTER(currentClusterId);
            }
        }
    }
//    printf("ENDED\n");
    return clusterIds;
}