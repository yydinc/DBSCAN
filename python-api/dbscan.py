import numpy as np
import ctypes


lib_dbscan = ctypes.cdll.LoadLibrary("./libdbscan.dylib")

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



def DBSCAN(epsilon: float, min_pts: int, points: np.ndarray) -> np.ndarray:
    """
    Purpose of this function is to cluster the given data using DBSCAN (Density-based spatial clustering of
    applications with noise) algorithm with the given parameters.


    :param epsilon: Epsilon (ε) parameter of the DBSCAN algorithm. Defines the maximum distance between
    two epsilon-neighbor points.

    :param min_pts: MinPts parameter of the DBSCAN algorithm. Defines the minimum number of
    the neighbors of a core point.

    :param points: A numpy.ndarray object that represents an (d x n) matrix whose columns are the points.

    :return: A numpy.ndarray object that represents an (1 x n) matrix whose columns represent
    the cluster id that point belongs to (-1 means noise).
    """

    dimensions = np.array(data.shape, dtype=ctypes.c_size_t)

    cluster_ids = np.empty(data.shape[1], dtype=np.intc)

    return cluster_ids.reshape((1, cluster_ids.size))
