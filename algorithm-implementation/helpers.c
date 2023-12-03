#include "helpers.h"

/*
 * setClusterId - Purpose of this function is to find the cluster id of the given point.
 *
 * @clusterIds: A (1 x n) array that represents the labels of the n points.
 *
 * @index: The index of the point to set the cluster id of.
 *
 * @newId: New cluster id to set as the label of the point.
 */

void setClusterId(int* clusterIds, int index, int newId) {
    clusterIds[index] = newId;
}


/*
 * setClusterIds - Purpose of this function is to find the cluster id of the given point.
 *
 * @clusterIds: A (1 x n) array that represents the labels of the n points.
 *
 * @indexes: The indexes of the points to set the cluster ids of.
 *
 * @indexesSize: Size of the indexes array
 *
 * @newId: New cluster id to set as the label of the point.
 */

void setClusterIds(int* clusterIds, const int* indexes, int indexesSize, int newId) {
    while (indexesSize--) {
        clusterIds[indexes[indexesSize]] = newId;
    }
}


/*
 * getClusterId - Purpose of this function is to find the cluster id of the given point.
 *
 * @clusterIds: A (1 x n) array that represents the labels of the n points.
 *
 * @index: The index of the point to find the cluster id of.
 *
 * Returns: An integer that will represent the cluster id of the point.
 */

int getClusterId(int* clusterIds, int index) {
    return clusterIds[index];
}


/*
 * areEpsilonNeighbors - Purpose of this function is check if given two points are epsilon-neighbors.
 *
 * @points: A (d x n) array that represents the n points in the dth dimension.
 *
 * @dimensions: An array of 2 elements that contains the numbers d (number of dimensions) and n (number of points).
 *
 * @i1: The index of the first point to query.
 *
 * @i2: The index of the second point to query.
 *
 * @epsilon: Epsilon (ε) parameter of the DBSCAN algorithm. Defines the maximum distance between 2 epsilon-neighbor points.
 *
 * Returns: An integer that will represent a boolean (0 if false and any other number otherwise).
 */

int areEpsilonNeighbors(const double* points, const size_t * dimensions, int i1, int i2, double epsilon) {
    double distance = 0;
    for(int j = 0; j < dimensions[0]; j++) {
        double distanceInDimensionJ = (points[i1 + dimensions[1] * j] - points[i2 + dimensions[1] * j]);
        distance += distanceInDimensionJ * distanceInDimensionJ;
    }
    return distance <= (epsilon * epsilon);
}


/*
 * regionQuery - Purpose of this function is to find the epsilon-neighbors of the given point.
 *
 * @points: A (d x n) array that represents the n points in the dth dimension.
 *
 * @dimensions: An array of 2 elements that contains the numbers d (number of dimensions) and n (number of points).
 *
 * @pointIndex: The index of the point to find the epsilon-neighbors of.
 *
 * @epsilon: Epsilon (ε) parameter of the DBSCAN algorithm. Defines the maximum distance between 2 epsilon-neighbor points.
 *
 * @outReturnSize: An integer address to write the size of the return array.
 *
 * Returns: An integer array that will represent the indexes of the epsilon-neighbor points of the queried point.
 */

int* regionQuery(const double* points, const size_t * dimensions, int pointIndex, double epsilon, int* outReturnSize) {
    struct ResizingStack* stack = createStack(5);

    for(int i = 0; i < dimensions[1]; i++) {
        if(areEpsilonNeighbors(points, dimensions, i, pointIndex, epsilon)) {
            push(stack, i);
        }
    }

    (*outReturnSize) = stack->top + 1;

    int* data = stack->array;

    free(stack);

    return data;
}
