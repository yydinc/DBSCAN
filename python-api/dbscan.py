import numpy as np
import ctypes

lib_dbscan = ctypes.cdll.LoadLibrary("./libdbscan.so")

c_DBSCAN = lib_dbscan.DBSCAN

c_DBSCAN.argtypes = (
    #: Data that represents datapoints
    np.ctypeslib.ndpointer(ctypes.c_double, flags="C_CONTIGUOUS"),

    # Dimensions of the data
    np.ctypeslib.ndpointer(ctypes.c_size_t, flags="C_CONTIGUOUS"),

    # Output cluster data
    np.ctypeslib.ndpointer(ctypes.c_int, flags="C_CONTIGUOUS"),

    # Epsilon (ε)
    ctypes.c_double,

    # Min points
    ctypes.c_int
)

c_DBSCAN.restype = None


def DBSCAN(epsilon: float, min_pts: int, data: np.ndarray) -> np.ndarray:
    """
    Purpose of this function is to cluster the given data using DBSCAN (Density-based spatial clustering of
    applications with noise) algorithm with the given parameters.

    :param epsilon: ε (epsilon) parameter of the DBSCAN algorithm. Defines the minimum distance between two neighbor
    points.

    :param min_pts: minPts parameter of the DBSCAN algorithm. Defines the minimum number of points for classifying a
    point as a core point.

    :param data: A numpy.ndarray object that represents an (m x n) matrix whose columns are the datapoints.

    :return: A numpy.ndarray object that represents an (1 x n) matrix whose columns represent the cluster id that
    datapoint belongs to (-1 means noise).
    """

    dimensions = np.array(data.shape, dtype=ctypes.c_size_t)

    cluster_ids = np.empty(data.shape[1], dtype=np.intc)

    c_DBSCAN(data, dimensions, cluster_ids, epsilon, min_pts)

    return cluster_ids.reshape((1, cluster_ids.size))
