import random
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.cluster import KMeans

def main():
    data=pd.read_csv("normal/normal.txt",delimiter="	")
    data.columns=['x','y']
    kmeans=KMeans(n_clusters=4,max_iter=100,random_state=619)

    labels=kmeans.fit_predict(data)
    plt.figure(figsize=(10,6))

    ax = sns.scatterplot(x= data["x"], y= data["y"], hue = labels, data = data, palette='dark')
    plt.title('K-Means Clustering ')
    plt.show()
if __name__ == "__main__":
    main()