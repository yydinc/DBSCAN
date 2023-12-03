#pragma once

#include "helpers.h"

void DBSCAN(const double* points, const size_t* dimensions, int* clusterIds,
            double epsilon, int minPts);