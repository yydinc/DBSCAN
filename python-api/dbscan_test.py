import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from dbscan import DBSCAN


def generate_test_data():
    rng = np.random.default_rng()
    theta = np.linspace(0, np.pi, 500).reshape((1, 500))

    radius = 20

    x1 = radius * np.cos(theta) + rng.normal(size=500)
    y1 = (radius * np.sin(theta) + rng.normal(size=500))

    d1 = np.concatenate((x1, y1), axis=0)

    d2 = rng.normal(size=1000, loc=5).reshape(2, 500)

    d3 = rng.normal(size=1000, loc=-5).reshape(2, 500)

    x4 = radius * np.cos(theta) + rng.normal(size=500)
    y4 = -(radius * np.sin(theta) + rng.normal(size=500))

    d4 = np.concatenate((x4, y4), axis=0)

    d5 = rng.uniform(size=200, low=-20, high=20).reshape(2, 100)

    return np.concatenate((d1, d2, d3, d4, d5), axis=1)


test_data = generate_test_data()
dbscan_data = DBSCAN(epsilon=1.8, min_pts=15, points=test_data)

cluster_data_df = pd.Series(name="Cluster", data=dbscan_data[0])

data_x_df = pd.Series(name="X", data=test_data[0, :])
data_y_df = pd.Series(name="Y", data=test_data[1, :])

plot_data = pd.DataFrame(data=[data_x_df, data_y_df, cluster_data_df]).transpose()

sns.scatterplot(data=plot_data, x="X", y="Y", hue="Cluster")
plt.show()