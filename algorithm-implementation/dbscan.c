/*
 * This is an implementation of the DBSCAN (Density-based spatial clustering for applications with noise) algorithm.
 *
 * The research paper that have been used as a reference for this implementation is the paper "(1996) Density-Based Algorithm
 * for Discovering Clusters in Large Spatial Databases with Noise. Knowledge Discovery and Data Mining".
 */


#include "dbscan.h"

#define UNCLASSIFIED 0
#define NOISE (-1)
#define CLUSTER(N) N
#define NEXT_CLUSTER(N) (N + 1)
#define TRUE 1
#define FALSE 0


/*
 * expandCluster - Purpose of this function is to classify the given point and expand the cluster if it is not noise.
 *
 * @points: A (d x n) array that represents the n points in the dth dimension.
 *
 * @dimensions: An array of 2 elements that contains the numbers d (number of dimensions) and n (number of points).
 *
 * @pointIndex: The index of the point to expand the cluster from.
 *
 * @currentClusterId: An integer value that represents the label of the current cluster.
 *
 * @clusterIds: A (1 x n) array that represents the labels of the n points. This array will be modified.
 *
 * @epsilon: Epsilon (ε) parameter of the DBSCAN algorithm. Defines the maximum distance between 2 epsilon-neighbor points.
 *
 * @minPts: MinPts parameter of the DBSCAN algorithm. Defines the minimum number of the neighbors of a core point.
 *
 * Returns: An integer that will represent a boolean (0 if false and any other number otherwise).
 */

int expandCluster(const double* points, const size_t* dimensions, int pointIndex, int currentClusterId,
                  double epsilon, int minPts, int * pointClusterIds) {

    int seedsSize = 0;

    // Epsilon (ε) neighborhood of the starting point.
    int* seeds = regionQuery(points, dimensions, pointIndex, epsilon, &seedsSize);

    if(seedsSize < minPts) { // Starting point is not a core point, so it is a noise
        pointClusterIds[pointIndex] = NOISE;
        free(seeds);
        return FALSE;
    }
    else {// Starting point is a core point

        struct ResizingStack* seedsStack = createStackFromArray(seeds, seedsSize);

        // Adding directly density-reachable points to the cluster
        setClusterIds(pointClusterIds, seeds, seedsSize, currentClusterId);

        // Looping through all points that are density-reachable
        while (!isEmpty(seedsStack)) {
            int resultSize = 0;

            int currentPoint = pop(seedsStack);

            int* result = regionQuery(points, dimensions, currentPoint, epsilon,
                                      &resultSize);

            // Checking if the current point is a core point
            if(resultSize >= minPts) {

                // Looping through all directly density-reachable points of the current point
                for(int j = 0; j < resultSize; j++) {

                    // A density reachable point from the starting point
                    int resultPoint = result[j];
                    int clusterId = getClusterId(pointClusterIds, resultPoint);


                    if(clusterId == UNCLASSIFIED || clusterId == NOISE) {
                        if(clusterId == UNCLASSIFIED) {
                            push(seedsStack, resultPoint);
                        }

                        //
                        setClusterId(pointClusterIds, resultPoint, currentClusterId);
                    }
                }
            }

            free(result);
        }
        freeStack(seedsStack);
    }
    return TRUE;
}


/*
 * DBSCAN - This is an implementation of the DBSCAN (Density Based Spatial Clustering of Applications with Noise) algorithm.
 * Purpose of this function is to label the points with their corresponding cluster id (-1 if noise).
 *
 * @points: A (d x n) array that represents the n points in the dth dimension.
 *
 * @dimensions: An array of 2 elements that contains the numbers d (number of dimensions) and n (number of points).
 *
 * @clusterIds: A (1 x n) array that represents the labels of the n points. This array will be modified.
 *
 * @epsilon: Epsilon (ε) parameter of the DBSCAN algorithm. Defines the maximum distance between 2 epsilon-neighbor points.
 *
 * @minPts: MinPts parameter of the DBSCAN algorithm. Defines the minimum number of the neighbors of a core point.
 */

void DBSCAN(const double* points, const size_t* dimensions, int* clusterIds,
            double epsilon, int minPts) {
    size_t m = dimensions[0];
    size_t n = dimensions[1];

    int currentClusterId = CLUSTER(1);

    memset(clusterIds, 0, n * sizeof(int));

    for (int i = 0; i < n; i++) {
        if(clusterIds[i] == UNCLASSIFIED) {
            if(expandCluster(points, dimensions, i, currentClusterId, epsilon, minPts, clusterIds)) {
                currentClusterId = NEXT_CLUSTER(currentClusterId);
            }
        }
    }
}