#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stack.h"

void setClusterId(int* clusterIds, int index, int newId);

void setClusterIds(int* clusterIds, const int* indexes, int indexesSize, int newId);

int getClusterId(int* clusterIds, int index);

int* regionQuery(const double* points, const size_t * dimensions, int pointIndex, double epsilon, int* outReturnSize);
