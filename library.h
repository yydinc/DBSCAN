#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stack.h"

int* DBSCAN(const double* dataIn, const size_t* dimensions, int* clusterIds,
            double epsilon, int minPts);